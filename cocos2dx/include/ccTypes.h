/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#ifndef __CCTYPES_H__
#define __CCTYPES_H__

#include <string>
#include "cocoa/CCGeometry.h"
#include "CCGL.h"


NS_CC_BEGIN

// general function type
typedef const char* (*CC_DECRYPT_FUNC)(const char* enc, int encLen, int* plainLen);
typedef const char* (*CC_ENCRYPT_FUNC)(const char* plain, int plainLen, int* encLen);
typedef const char* (*CC_MULTI_ENCRYPT_FUNC)(const char* enc, size_t encLen, size_t* plainLen, int algorithm);
typedef const char* (*CC_MULTI_DECRYPT_FUNC)(const char* plain, size_t plainLen, size_t* encLen, int algorithm);

/** RGB color composed of bytes 3 bytes
@since v0.8
 */
typedef struct _ccColor3B
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
} ccColor3B;

//! helper macro that creates an ccColor3B type
static inline ccColor3B
ccc3(const GLubyte r, const GLubyte g, const GLubyte b)
{
    ccColor3B c = {r, g, b};
    return c;
}

/** returns true if both ccColor3B are equal. Otherwise it returns false.
 */
static inline bool ccc3BEqual(const ccColor3B &col1, const ccColor3B &col2)
{
    return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
}

/** RGBA color composed of 4 bytes
@since v0.8
*/
typedef struct _ccColor4B
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
} ccColor4B;

//! helper macro that creates an ccColor4B type
static inline ccColor4B
ccc4(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte o)
{
    ccColor4B c = {r, g, b, o};
    return c;
}


/** RGBA color composed of 4 floats
@since v0.8
*/
typedef struct _ccColor4F {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
} ccColor4F;

/// hsv color
typedef struct ccColorHSV {
    float h, s, v;
} ccColorHSV;

// create hsv color
static inline ccColorHSV cchsv(const float h, const float s, const float v) {
    ccColorHSV c = { h, s, v };
    return c;
}

/** Returns a ccColor4F from a ccColor3B. Alpha will be 1.
 @since v0.99.1
 */
static inline ccColor4F ccc4FFromccc3B(ccColor3B c)
{
    ccColor4F c4 = {c.r/255.f, c.g/255.f, c.b/255.f, 1.f};
    return c4;
}

//! helper that creates a ccColor4f type
static inline ccColor4F 
ccc4f(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a) {
    ccColor4F c4 = {r, g, b, a};
    return c4;
}

/** Returns a ccColor4F from a ccColor4B.
 @since v0.99.1
 */
static inline ccColor4F ccc4FFromccc4B(ccColor4B c) {
    ccColor4F c4 = {c.r/255.f, c.g/255.f, c.b/255.f, c.a/255.f};
    return c4;
}

static inline ccColor4B ccc4BFromccc4F(ccColor4F c)
{
    ccColor4B ret = {(GLubyte)(c.r*255), (GLubyte)(c.g*255), (GLubyte)(c.b*255), (GLubyte)(c.a*255)};
	return ret;
}

/** returns YES if both ccColor4F are equal. Otherwise it returns NO.
 @since v0.99.1
 */
static inline bool ccc4FEqual(ccColor4F a, ccColor4F b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

/// convert int color 0xaarrggbb to ccColor4B
static inline ccColor4B ccc4FromInt(int c) {
    return ccc4((c >> 16) & 0xff,
                (c >> 8) & 0xff,
                c & 0xff,
                (c >> 24) & 0xff);
}

/// convert int color 0xaarrggbb to ccColor3B, alpha is discarded
static inline ccColor3B ccc3FromInt(int c) {
    return ccc3((c >> 16) & 0xff,
                (c >> 8) & 0xff,
                c & 0xff);
}

/// convert ccColor4B to ccColor3B
static inline ccColor3B ccc3FromCCC4(const ccColor4B& c4) {
    return ccc3(c4.r, c4.g, c4.b);
}

/// convert int color 0xaarrggbb to ccColor4F
static inline ccColor4F ccc4fFromInt(int c) {
    return ccc4f(((c >> 16) & 0xff) / 255.0f,
                 ((c >> 8) & 0xff) / 255.0f,
                 (c & 0xff) / 255.0f,
                 ((c >> 24) & 0xff) / 255.0f);
}

/// convert ccColor4B to int color 0xaarrggbb
static inline int ccIntFromC4(const ccColor4B& c) {
    return ((c.a & 0xff) << 24) |
    ((c.r & 0xff) << 16) |
    ((c.g & 0xff) << 8) |
    (c.b & 0xff);
}

/// convert ccColor3B to int color 0xaarrggbb
static inline int ccIntFromC3(const ccColor3B& c) {
    return 0xff000000 |
    ((c.r & 0xff) << 16) |
    ((c.g & 0xff) << 8) |
    (c.b & 0xff);
}

/// convert ccColor4F to int color 0xaarrggbb
static inline int ccIntFromC4f(const ccColor4F& c) {
    return (((int)(c.a * 255) & 0xff) << 24) |
    (((int)(c.r * 255) & 0xff) << 16) |
    (((int)(c.g * 255) & 0xff) << 8) |
    ((int)(c.b * 255) & 0xff);
}

//ccColor3B predefined colors
//! White color (255,255,255)
static const ccColor3B ccWHITE={255,255,255};
//! Yellow color (255,255,0)
static const ccColor3B ccYELLOW={255,255,0};
//! Blue color (0,0,255)
static const ccColor3B ccBLUE={0,0,255};
//! Green Color (0,255,0)
static const ccColor3B ccGREEN={0,255,0};
//! Red Color (255,0,0,)
static const ccColor3B ccRED={255,0,0};
//! Magenta Color (255,0,255)
static const ccColor3B ccMAGENTA={255,0,255};
//! Black Color (0,0,0)
static const ccColor3B ccBLACK={0,0,0};
//! Orange Color (255,127,0)
static const ccColor3B ccORANGE={255,127,0};
//! Gray Color (166,166,166)
static const ccColor3B ccGRAY={166,166,166};

// color constants
static const ccColor4B cc4RED = { 255, 0, 0, 255 };
static const ccColor4B cc4GREEN = { 0, 255, 0, 255 };
static const ccColor4B cc4BLUE = { 0, 0, 255, 255 };
static const ccColor4B cc4BLACK = { 0, 0, 0, 255 };
static const ccColor4B cc4WHITE = { 255, 255, 255, 255 };
static const ccColor4B cc4TRANSPARENT = { 0, 0, 0, 0 };
static const ccColor4B cc4DIM = { 0, 0, 0, 127 };
static const ccColor4B cc4YELLOW = { 255, 255, 0, 255 };
static const ccColor4F cc4fRED = { 1, 0, 0, 1 };
static const ccColor4F cc4fGREEN = { 0, 1, 0, 1 };
static const ccColor4F cc4fBLUE = { 0, 0, 1, 1 };
static const ccColor4F cc4fBLACK = { 0, 0, 0, 1 };
static const ccColor4F cc4fWHITE = { 1, 1, 1, 1 };
static const ccColor4F cc4fTRANSPARENT = { 0, 0, 0, 0 };
static const ccColor4F cc4fDIM = { 0, 0, 0, 0.5f };
static const ccColor4F cc4fYELLOW = { 1, 1, 0, 1 };

/** A vertex composed of 2 floats: x, y
 @since v0.8
 */
typedef struct _ccVertex2F {
    GLfloat x;
    GLfloat y;
} ccVertex2F;

static inline ccVertex2F vertex2(const float x, const float y) {
    ccVertex2F c = {x, y};
    return c;
}

/** A vertex composed of 2 floats: x, y
 @since v0.8
 */
typedef struct _ccVertex3F
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} ccVertex3F;

static inline ccVertex3F vertex3(const float x, const float y, const float z)
{
    ccVertex3F c = {x, y, z};
    return c;
}
        
/** A texcoord composed of 2 floats: u, y
 @since v0.8
 */
typedef struct _ccTex2F {
     GLfloat u;
     GLfloat v;
} ccTex2F;

static inline ccTex2F tex2(const float u, const float v)
{
    ccTex2F t = {u , v};
    return t;
}

 
//! Point Sprite component
typedef struct _ccPointSprite
{
    ccVertex2F    pos;        // 8 bytes
    ccColor4B    color;        // 4 bytes
    GLfloat        size;        // 4 bytes
} ccPointSprite;

/// aabb box
typedef struct ccAABB {
    CCPoint min, max;
} ccAABB;

/// create aabb
static inline ccAABB ccaabb(const CCPoint min, const CCPoint max) {
    ccAABB b = {
        min,
        max
    };
    return b;
}

/// position
typedef struct ccPosition {
    int x, y;
} ccPosition;
static const ccPosition ccposZero = { 0, 0 };
static inline ccPosition ccpos(const int x, const int y) {
    ccPosition p = {
        x, y
    };
    return p;
}

// point struct
typedef struct ccPoint { float x, y; } ccPoint;
static const ccPoint ccpZero = { 0, 0 };
static inline ccPoint ccpt(const float x, const float y) {
    ccPoint p = { x, y };
    return p;
}
static inline ccPoint ccptAdd(const ccPoint& p1, const ccPoint& p2) {
    return ccpt(p1.x + p2.x, p1.y + p2.y);
}
static inline ccPoint ccptSub(const ccPoint& p1, const ccPoint& p2) {
    return ccpt(p1.x - p2.x, p1.y - p2.y);
}
static inline float ccptLengthSQ(const ccPoint& p) {
    return p.x * p.x + p.y * p.y;
}
static inline float ccptLength(const ccPoint& p) {
    return sqrtf(ccptLengthSQ(p));
}

// rect struct
typedef struct ccRect { float x, y, width, height; } ccRect;
static const ccRect ccrZero = { 0, 0, 0, 0 };
static inline ccRect ccr(const float x, const float y, const float w, const float h) {
    ccRect r = { x, y, w, h };
    return r;
}
static inline CCRect ccr2CCR(const ccRect& r) {
    return CCRectMake(r.x, r.y, r.width, r.height);
}

// size struct
typedef struct ccSize { float width, height; } ccSize;
static const ccSize ccsZero = { 0, 0 };
static inline ccSize ccsz(const float w, const float h) {
    ccSize s = { w, h };
    return s;
}

// insets
typedef struct ccInsets {
    float top;
    float left;
    float right;
    float bottom;
} ccInsets;
static const ccInsets cciZero = { 0, 0, 0, 0 };
static inline ccInsets cci(float t, float l, float r, float b) {
    ccInsets i = {
        t, l, r, b
    };
    return i;
}

//!    A 2D Quad. 4 * 2 floats
typedef struct _ccQuad2 {
    ccVertex2F        tl;
    ccVertex2F        tr;
    ccVertex2F        bl;
    ccVertex2F        br;
} ccQuad2;


//!    A 3D Quad. 4 * 3 floats
typedef struct _ccQuad3 {
    ccVertex3F        bl;
    ccVertex3F        br;
    ccVertex3F        tl;
    ccVertex3F        tr;
} ccQuad3;

//! a Point with a vertex point, a tex coord point and a color 4B
typedef struct _ccV2F_C4B_T2F
{
    //! vertices (2F)
    ccVertex2F        vertices;
    //! colors (4B)
    ccColor4B        colors;
    //! tex coords (2F)
    ccTex2F            texCoords;
} ccV2F_C4B_T2F;

//! a Point with a vertex point, a tex coord point and a color 4F
typedef struct _ccV2F_C4F_T2F
{
    //! vertices (2F)
    ccVertex2F        vertices;
    //! colors (4F)
    ccColor4F        colors;
    //! tex coords (2F)
    ccTex2F            texCoords;
} ccV2F_C4F_T2F;

//! a Point with a vertex point, a tex coord point and a color 4B
typedef struct _ccV3F_C4B_T2F
{
    //! vertices (3F)
    ccVertex3F        vertices;            // 12 bytes
//    char __padding__[4];

    //! colors (4B)
    ccColor4B        colors;                // 4 bytes
//    char __padding2__[4];

    // tex coords (2F)
    ccTex2F            texCoords;            // 8 bytes
} ccV3F_C4B_T2F;

//! A Triangle of ccV2F_C4B_T2F
typedef struct _ccV2F_C4B_T2F_Triangle
{
	//! Point A
	ccV2F_C4B_T2F a;
	//! Point B
	ccV2F_C4B_T2F b;
	//! Point B
	ccV2F_C4B_T2F c;
} ccV2F_C4B_T2F_Triangle;

//! A Quad of ccV2F_C4B_T2F
typedef struct _ccV2F_C4B_T2F_Quad
{
    //! bottom left
    ccV2F_C4B_T2F    bl;
    //! bottom right
    ccV2F_C4B_T2F    br;
    //! top left
    ccV2F_C4B_T2F    tl;
    //! top right
    ccV2F_C4B_T2F    tr;
} ccV2F_C4B_T2F_Quad;

//! 4 ccVertex3FTex2FColor4B
typedef struct _ccV3F_C4B_T2F_Quad
{
    //! top left
    ccV3F_C4B_T2F    tl;
    //! bottom left
    ccV3F_C4B_T2F    bl;
    //! top right
    ccV3F_C4B_T2F    tr;
    //! bottom right
    ccV3F_C4B_T2F    br;
} ccV3F_C4B_T2F_Quad;

//! 4 ccVertex2FTex2FColor4F Quad
typedef struct _ccV2F_C4F_T2F_Quad
{
    //! bottom left
    ccV2F_C4F_T2F    bl;
    //! bottom right
    ccV2F_C4F_T2F    br;
    //! top left
    ccV2F_C4F_T2F    tl;
    //! top right
    ccV2F_C4F_T2F    tr;
} ccV2F_C4F_T2F_Quad;

//! Blend Function used for textures
typedef struct _ccBlendFunc
{
    //! source blend function
    GLenum src;
    //! destination blend function
    GLenum dst;
} ccBlendFunc;

static const ccBlendFunc kCCBlendFuncDisable = {GL_ONE, GL_ZERO};

// XXX: If any of these enums are edited and/or reordered, update CCTexture2D.m
//! Vertical text alignment type
typedef enum
{
    kCCVerticalTextAlignmentTop,
    kCCVerticalTextAlignmentCenter,
    kCCVerticalTextAlignmentBottom,
} CCVerticalTextAlignment;

// XXX: If any of these enums are edited and/or reordered, update CCTexture2D.m
//! Horizontal text alignment type
typedef enum
{
    kCCTextAlignmentLeft,
    kCCTextAlignmentCenter,
    kCCTextAlignmentRight,
} CCTextAlignment;

// types for animation in particle systems

// texture coordinates for a quad
typedef struct _ccT2F_Quad
{
    //! bottom left
    ccTex2F    bl;
    //! bottom right
    ccTex2F    br;
    //! top left
    ccTex2F    tl;
    //! top right
    ccTex2F    tr;
} ccT2F_Quad;

// struct that holds the size in pixels, texture coordinates and delays for animated CCParticleSystemQuad
typedef struct
{
    ccT2F_Quad texCoords;
    float delay;
    CCSize size; 
} ccAnimationFrameData;



/**
 types used for defining fonts properties (i.e. font name, size, stroke or shadow)
 */

// shadow attributes
typedef struct _ccFontShadow
{
public:
    
    // shadow is not enabled by default
    _ccFontShadow(): m_shadowEnabled(false) {}
    
    // true if shadow enabled
    bool   m_shadowEnabled;
    // shadow x and y offset
	CCSize m_shadowOffset;
    // shadow blurrines
	float  m_shadowBlur;
    // shadow opacity
	float  m_shadowOpacity;
    
} ccFontShadow;

// stroke attributes
typedef struct _ccFontStroke
{
public:
    
    // stroke is disabled by default
    _ccFontStroke(): m_strokeEnabled(false) {}
    
    // true if stroke enabled
    bool        m_strokeEnabled;
    // stroke color
	ccColor3B   m_strokeColor;
    // stroke size
    float       m_strokeSize;
    
} ccFontStroke;

// font attributes
/**
 *  @js NA
 *  @lua NA
 */
typedef struct _ccFontDefinition {
public:
    _ccFontDefinition() :
    m_alignment(kCCTextAlignmentCenter),
    m_vertAlignment(kCCVerticalTextAlignmentTop),
    m_fontFillColor(ccWHITE),
    decryptFunc(NULL),
    m_globalImageScaleFactor(1),
    m_lineSpacing(0),
    m_shadowColor(0),
    m_toCharIndex(0),
    m_elapsed(0),
    m_dimensions(CCSizeZero) {
        m_dimensions = CCSizeMake(0, 0);
    }
    
    // font name
    std::string             m_fontName;
    
    // font size
    int                     m_fontSize;
    
    // horizontal alignment
    CCTextAlignment         m_alignment;
    
    // vertical alignment
    CCVerticalTextAlignment m_vertAlignment;
    
    // renering box
    CCSize                  m_dimensions;
    
    // font color
    ccColor3B               m_fontFillColor;
    
    // font shadow
    ccFontShadow            m_shadow;
    
    // font stroke
    ccFontStroke            m_stroke;
    
    // font shadow color
    int m_shadowColor;
    
    // line spacing
    float m_lineSpacing;
    
    // default image scale factor
    float m_globalImageScaleFactor;
    
    // shown letter to index
    int m_toCharIndex;
    
    // decrypt func for embedded image
    CC_DECRYPT_FUNC decryptFunc;
    
    // elapsed time
    float m_elapsed;
} ccFontDefinition;

// for lua function
typedef struct {
    unsigned int handler;
} ccLuaFunction;

NS_CC_END

#endif //__CCTYPES_H__
