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
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#define __CC_PLATFORM_IMAGE_CPP__
#include "platform/CCImageCommon_cpp.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCImage.h"
#include "platform/CCFileUtils.h"
#include "jni/JniHelper.h"
#include "jni/CLBitmapDC.h"
#include <android/log.h>
#include <string.h>
#include <jni.h>

// swap the alpha channel in an 32 bit image (from ARGB to RGBA)
static void swapAlphaChannel(unsigned int *pImageMemory, unsigned int numPixels) {
	for(int c = 0; c < numPixels; ++c, ++pImageMemory) {
		// copy the current pixel
		unsigned int currenPixel = (*pImageMemory);

		// swap channels and store back
		char *pSource = (char *) &currenPixel;
		*pImageMemory = (pSource[0] << 24) | (pSource[3] << 16) | (pSource[2] << 8) | pSource[1];
	}
}

NS_CC_BEGIN

bool CCImage::initWithString(
                               const char *    pText, 
                               int             nWidth/* = 0*/, 
                               int             nHeight/* = 0*/,
                               ETextAlign      eAlignMask/* = kAlignCenter*/,
                               const char *    pFontName/* = nil*/,
                               int             nSize/* = 0*/)
{
    bool bRet = false;

    do 
    {
        CC_BREAK_IF(! pText);
        
        CLBitmapDC &dc = CLBitmapDC::sharedCLBitmapDC();

        CC_BREAK_IF(! dc.getBitmapFromJava(pText, nWidth, nHeight, eAlignMask, pFontName, nSize));

        // assign the dc.m_pData to m_pData in order to save time
        m_pData = dc.m_pData;
        CC_BREAK_IF(! m_pData);

        m_nWidth    = (short)dc.m_nWidth;
        m_nHeight   = (short)dc.m_nHeight;
        m_bHasAlpha = true;
        m_bPreMulti = true;
        m_nBitsPerComponent = 8;

        bRet = true;
    } while (0);

    return bRet;
}

bool CCImage::initWithStringShadowStroke(const char * pText, int nWidth, int nHeight, ETextAlign eAlignMask, const char * pFontName, int nSize,
		float textTintR, float textTintG, float textTintB, bool shadow, float shadowOffsetX, float shadowOffsetY, int shadowColor, float shadowBlur,
		bool stroke, float strokeR, float strokeG, float strokeB, float strokeSize, float lineSpacing, float globalImageScaleFactor, int toCharIndex, float elapsedTime, CC_DECRYPT_FUNC decryptFunc) {
	bool bRet = false;
	do {
		CC_BREAK_IF(!pText);

		CLBitmapDC &dc = CLBitmapDC::sharedCLBitmapDC();

		CC_BREAK_IF(!dc.getBitmapFromJavaShadowStroke(pText,
                                                      nWidth,
                                                      nHeight,
                                                      eAlignMask,
                                                      pFontName,
                                                      nSize,
                                                      textTintR,
                                                      textTintG,
                                                      textTintB,
                                                      shadow,
                                                      shadowOffsetX,
                                                      shadowOffsetY,
                                                      shadowColor,
                                                      shadowBlur,
                                                      stroke,
                                                      strokeR,
                                                      strokeG,
                                                      strokeB,
                                                      strokeSize,
                                                      lineSpacing,
                                                      globalImageScaleFactor,
                                                      toCharIndex,
                                                      elapsedTime,
                                                      decryptFunc,
                                                      false));

		// assign the dc.m_pData to m_pData in order to save time
		m_pData = dc.m_pData;

		CC_BREAK_IF(!m_pData);

		m_nWidth = (short) dc.m_nWidth;
		m_nHeight = (short) dc.m_nHeight;
		m_bHasAlpha = true;
		m_bPreMulti = true;
		m_nBitsPerComponent = 8;
		m_realLength = dc.m_realLength;
		m_needTime = dc.m_needTime;

		// swap the alpha channel (ARGB to RGBA)
		swapAlphaChannel((unsigned int *)m_pData, (m_nWidth * m_nHeight));

		// ok
		bRet = true;

		// save info needed by label
		m_linkMetas = dc.m_linkMetas;
		m_imageRects = dc.m_imageRects;
		m_shadowStrokePadding = dc.m_shadowStrokePadding;
	} while(0);

	return bRet;
}

CCSize CCImage::measureString(const char* pText,
								const char* pFontName,
								int nSize,
								int maxWidth,
								float shadowOffsetX,
								float shadowOffsetY,
								float strokeSize,
								float lineSpacing,
								float globalImageScaleFactor,
								CC_DECRYPT_FUNC decryptFunc) {
    CCSize size = CCSizeZero;
	do {
		CC_BREAK_IF(!pText);

		CLBitmapDC& dc = CLBitmapDC::sharedCLBitmapDC();

		CC_BREAK_IF(!dc.getBitmapFromJavaShadowStroke(pText,
                                                      maxWidth,
                                                      0,
                                                      kAlignCenter,
                                                      pFontName,
                                                      nSize,
                                                      0,
                                                      0,
                                                      0,
                                                      shadowOffsetX != 0 || shadowOffsetY != 0,
                                                      shadowOffsetX,
                                                      shadowOffsetY,
                                                      0,
                                                      0,
                                                      strokeSize != 0,
                                                      0,
                                                      0,
                                                      0,
                                                      strokeSize,
                                                      lineSpacing,
                                                      globalImageScaleFactor,
                                                      -1,
                                                      0,
                                                      decryptFunc,
                                                      true));
		size.width = dc.m_nWidth;
		size.height = dc.m_nHeight;
	} while(0);

	return size;
}

NS_CC_END

// this method is called by Cocos2dxBitmap
extern "C"
{
    /**
    * this method is called by java code to init width, height and pixels data
    */
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxBitmap_nativeInitBitmapDC(JNIEnv*  env, jobject thiz, int width, int height, jbyteArray pixels)
    {
        int size = width * height * 4;
        CLBitmapDC& bitmapDC = CLBitmapDC::sharedCLBitmapDC();
        bitmapDC.m_nWidth = width;
        bitmapDC.m_nHeight = height;
        bitmapDC.m_pData = new unsigned char[size];
        env->GetByteArrayRegion(pixels, 0, size, (jbyte*)bitmapDC.m_pData);

        // swap data
        unsigned int *tempPtr = (unsigned int*)bitmapDC.m_pData;
        unsigned int tempdata = 0;
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                tempdata = *tempPtr;
                *tempPtr++ = bitmapDC.swapAlpha(tempdata);
            }
        }
    }
};

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
