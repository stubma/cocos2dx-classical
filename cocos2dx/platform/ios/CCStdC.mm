/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 by Luma
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "CCStdC.h"

#ifdef __cplusplus
extern "C" {
#endif
    
FILE *fopen$UNIX2003( const char *filename, const char *mode) {
    return fopen(filename, mode);
}

FILE *freopen$UNIX2003(const char *pathname, const char *mode, FILE *stream) {
    return freopen(pathname, mode, stream);
}

int fputs$UNIX2003(const char *res1, FILE *res2){
    return fputs(res1,res2);
}

size_t fwrite$UNIX2003( const void *a, size_t b, size_t c, FILE *d ) {
    return fwrite(a, b, c, d);
}

char* strerror$UNIX2003(int errornum) {
    return strerror(errornum);
}

double strtod$UNIX2003(const char *nptr, char **endptr) {
    return strtod(nptr, endptr);
}

size_t strftime$UNIX2003(char *s, size_t max, const char *format, const struct tm *tm) {
    return strftime(s, max, format, tm);
}

FILE *popen$UNIX2003(const char *command, const char *type) {
    return popen(command, type);
}

time_t mktime$UNIX2003(struct tm *timeptr) {
    return mktime(timeptr);
}

clock_t clock$UNIX2003() {
    return clock();
}

int system$UNIX2003(const char *command) {
    return system(command);
}

#ifdef __cplusplus
}
#endif
