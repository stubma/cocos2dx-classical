/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

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

#ifndef __CC_STD_C_H__
#define __CC_STD_C_H__

#include "platform/CCPlatformMacros.h"
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#if TARGET_IPHONE_SIMULATOR

#ifdef __cplusplus
extern "C" {
#endif

FILE *fopen$UNIX2003( const char *filename, const char *mode);
FILE *freopen$UNIX2003(const char *pathname, const char *mode, FILE *stream);
int fputs$UNIX2003(const char *res1, FILE *res2);
size_t fwrite$UNIX2003( const void *a, size_t b, size_t c, FILE *d);
char* strerror$UNIX2003(int errornum);
double strtod$UNIX2003(const char *nptr, char **endptr);
size_t strftime$UNIX2003(char *s, size_t max, const char *format, const struct tm *tm);
FILE *popen$UNIX2003(const char *command, const char *type);
time_t mktime$UNIX2003(struct tm *timeptr);
clock_t clock$UNIX2003();
int system$UNIX2003(const char *command);

#ifdef __cplusplus
}
#endif

#endif // #if TARGET_IPHONE_SIMULATOR

#endif  // __CC_STD_C_H__
