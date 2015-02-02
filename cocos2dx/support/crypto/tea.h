#ifndef __TEA__
#define __TEA__

/**
 * tea encrypt
 *
 * @param keyData key, 16 bytes
 * @param src plain text
 * @param srcLength byte length of plain text
 * @param encOffset offset in plain text to start encryption
 * @param encLength length in plain text to get encrypted
 * @param outLength byte length of returned encrypted content
 * @return encrypted content, caller should not free it. If want to keep for later
 *      use, must copy it. If failed, returns nullptr
 */
const char* teaenc(const char* keyData, const char* src, int srcLength,
                   int encOffset, int encLength, int* outLength);

/**
 * tea decrypt
 *
 * @param keyData key, 16 bytes
 * @param src encrypted text
 * @param srcLength byte length of src
 * @param decOffset decrypt offset in encrypted text
 * @param decLength length of encrypted content to be decrypted
 * @param outLength byte length of returned plain content
 * @return plain content, caller should not free it. If want to keep for later
 *      use, must copy it. If failed, returns nullptr
 */
const char* teadec(const char* keyData, const char* src, int srcLength,
                   int decOffset, int decLength, int* outLength);

#endif /* defined(__TEA__) */
