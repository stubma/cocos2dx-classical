#include "tea.h"
#include <stdlib.h>
#include <memory.h>
#if !defined(__MACH__)
    #include <endian.h>
#endif

static char cipher[8];
static char* prePlain;
static char* output = NULL;
static char* output_bak = NULL;
static char* plain;
static int _pos;
static int _crypt;
static int preCrypt;
static int padding;
static int contextStart;
static bool header = true;
static char key[16];

static uint32_t getUInt32(const char* bytes, int offset, int length) {
    uint32_t ret = 0;
	int end = 0;
	int i;
	
	if(length > 4)
		end = offset + 4;
	else
		end = offset + length;
	for(i = offset; i < end; i++) {
		ret <<= 8;
		ret |= bytes[i] & 0xFF;
	}
	return ret;
}

static void writeUInt32(char* bytes, uint32_t value, int offset) {
    uint32_t u = htonl(value);
	memcpy(bytes + offset, &u, 4);
}

static char* encipher(const char* input, const char* key, char* output) {
    // iterate times
	int loop = 0x10;
	
	// variables
	uint32_t y = getUInt32(input, 0, 4);
	uint32_t z = getUInt32(input, 4, 4);
	uint32_t a = getUInt32(key, 0, 4);
	uint32_t b = getUInt32(key, 4, 4);
	uint32_t c = getUInt32(key, 8, 4);
	uint32_t d = getUInt32(key, 12, 4);
	
	// control variable
	// TEA delta，(sqr(5) - 1) * 2^31
	uint32_t sum = 0;
	uint32_t delta = 0x9E3779B9;
	
	// iterate
	while (loop-- > 0) {
		sum += delta;
		y += ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
		z += ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
	}
	
	// output crypted data
    writeUInt32(output, y, 0);
    writeUInt32(output, z, 4);
	return output;
}

static char* decipher(const char* bytes, int offset) {
	// iterate times
	int loop = 0x10;
	
	// variables
	uint32_t y = getUInt32(bytes, offset, 4);
	uint32_t z = getUInt32(bytes, offset + 4, 4);
	uint32_t a = getUInt32(key, 0, 4);
	uint32_t b = getUInt32(key, 4, 4);
	uint32_t c = getUInt32(key, 8, 4);
	uint32_t d = getUInt32(key, 12, 4);
    
	// control variable
	uint32_t sum = 0xE3779B90;
	uint32_t delta = 0x9E3779B9;
	
	// iterate
	while(loop-- > 0) {
		z -= ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
		y -= ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
		sum -= delta;
	}
	
	// output
    writeUInt32(cipher, y, 0);
    writeUInt32(cipher, z, 4);
	return cipher;
}

static char* decipher(const char* bytes) {
    return decipher(bytes, 0);
}

static void encrypt8Bytes() {
	// plain ^ preCrypt
	for(_pos = 0; _pos < 8; _pos++) {
		if(header)
			plain[_pos] ^= prePlain[_pos];
        else
            plain[_pos] ^= output[preCrypt + _pos];
    }
    
	// f(plain ^ preCrypt)
	memcpy(output + _crypt, encipher(plain, key, cipher), 8);
	
	// f(plain ^ preCrypt) ^ prePlain
	for(_pos = 0; _pos < 8; _pos++)
		output[_crypt + _pos] ^= prePlain[_pos];
    memcpy(prePlain, plain, 8);
    
    // finish
    preCrypt = _crypt;
    _crypt += 8;
    _pos = 0;
    header = false;
}

static bool decrypt8Bytes(const char* bytes, int offset, int length) {
	for(_pos = 0; _pos < 8; _pos++) {
		if(contextStart + _pos >= length)
			return true;
		prePlain[_pos] ^= bytes[offset + _crypt + _pos];
	}
	
	// d(crypt ^ prePlain)
	prePlain = decipher(prePlain);
	if(prePlain == NULL)
		return false;
	
	contextStart += 8;
	_crypt += 8;
	_pos = 0;
	return true;
}

const char* teaenc(const char* keyData, const int keyLen, const char* src, int srcLength,
                   int encOffset, int encLength, int* outLength) {
	plain = (char*)malloc(8 * sizeof(char));
	prePlain = (char*)calloc(8, sizeof(char));
	_pos = 1;
	padding = 0;
	_crypt = preCrypt = 0;
	header = true;
    memcpy(key, keyData, keyLen >= 16 ? 16 : keyLen);
    for(int i = keyLen; i < 16; i++) {
        key[i] = 0;
    }
	int i;
    
	// -1 means encrypt to end
	if(encLength == -1)
		encLength = srcLength - encOffset;
	
	int lengthbak = encLength;
	
	_pos = (encLength + 0x0A) % 8;
	if(_pos != 0)
		_pos = 8 - _pos;
            
    int count = encLength + _pos + 10;
    if(outLength)
        *outLength = _pos + 10 + srcLength;
    output_bak = output = (char*)malloc((_pos + 10 + srcLength) * sizeof(char));
    memcpy(output, src, encOffset);
    output += encOffset;
    
    plain[0] = (char)((rand() & 0xF8) | _pos);
            
    for(i = 1; i <= _pos; i++)
        plain[i] = (char)(rand() & 0xFF);
    _pos++;
	
	padding = 1;
	while(padding <= 2) {
		if(_pos < 8) {
			plain[_pos++] = (char)(rand() & 0xFF);
			padding++;
		}
		if(_pos == 8)
			encrypt8Bytes();
	}
	
	i = encOffset;
	while(encLength > 0) {
		if(_pos < 8) {
			plain[_pos++] = src[i++];
			encLength--;
		}
		if(_pos == 8)
			encrypt8Bytes();
	}
	
	padding = 1;
	while(padding <= 7) {
		if(_pos < 8) {
			plain[_pos++] = 0x0;
			padding++;
		}
		if(_pos == 8)
			encrypt8Bytes();
	}
	
	free(plain);
	free(prePlain);
	
	memcpy(output + count, src + encOffset + lengthbak, srcLength - encOffset - lengthbak);
	return output_bak;
}

const char* teadec(const char* keyData, const int keyLen, const char* src, int srcLength,
                   int decOffset, int decLength, int* outLength) {
	_crypt = preCrypt = 0;
    memcpy(key, keyData, keyLen >= 16 ? 16 : keyLen);
    for(int i = keyLen; i < 16; i++) {
        key[i] = 0;
    }
	
	int i;
	int count, countbak;
	int mlen = decOffset + 8;
	
	// -1 means decrypt to end
	if(decLength == -1)
		decLength = srcLength - decOffset;
        
    if((decLength % 8 != 0) || (decLength < 16))
        return NULL;
	
	prePlain = decipher(src, decOffset);
	_pos = prePlain[0] & 0x7;
	
	count = decLength - _pos - 10;
	countbak = count;
	if(count < 0)
		return NULL;
	
	char* m = (char*)calloc(mlen, sizeof(char));
	char* mbak = m;
	
    if(outLength)
        *outLength = count + srcLength - decLength;
    output_bak = output = (char*)malloc((count + srcLength - decLength) * sizeof(char));
	memcpy(output, src, decOffset);
	output += decOffset;
	
	preCrypt = 0;
	_crypt = 8;
	contextStart = 8;
	_pos++;
	
	padding = 1;
	while(padding <= 2) {
		if(_pos < 8) {
			_pos++;
			padding++;
		}
		if(_pos == 8) {
			m = (char*)src;
            if(!decrypt8Bytes(src, decOffset, decLength)) {
				free(mbak);
				return NULL;
			}
		}
	}
	
	i = 0;
	while(count != 0) {
		if(_pos < 8) {
			output[i] = (char)(m[decOffset + preCrypt + _pos] ^ prePlain[_pos]);
			i++;
			count--;
			_pos++;
		}
		if(_pos == 8) {
			m = (char*)src;
			preCrypt = _crypt - 8;
			if(!decrypt8Bytes(src, decOffset, decLength)) {
				free(mbak);
				return NULL;
			}
		}
	}
	
	for(padding = 1; padding < 8; padding++) {
		if(_pos < 8) {
			if((m[decOffset + preCrypt + _pos] ^ prePlain[_pos]) != 0) {
				free(mbak);
				return NULL;
			};
			_pos++;
		}
		if(_pos == 8) {
			m = (char*)src;
			preCrypt = _crypt;
			if(!decrypt8Bytes(src, decOffset, decLength)) {
				free(mbak);
				return NULL;
			}
		}
	}
	
	free(mbak);
	memcpy(output + countbak, src + decOffset + decLength, srcLength - decOffset - decLength);
	return output_bak;
}