/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Ricardo Quesada
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

#include "CCShaderCache.h"
#include "ccMacros.h"

NS_CC_BEGIN

static CCShaderCache *_sharedShaderCache = 0;

//
const GLchar * ccPosition_uColor_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec4 v_fragmentColor;
                       void main() {
                           gl_FragColor = v_fragmentColor;
                       });
const GLchar * ccPosition_uColor_vert
    = CC_SHADER_STRING(attribute vec4 a_position;
                       uniform vec4 u_color;
                       uniform float u_pointSize;
                       varying lowp vec4 v_fragmentColor;
                       
                       void main() {
                           gl_Position = CC_MVPMatrix * a_position;
                           gl_PointSize = u_pointSize;
                           v_fragmentColor = u_color;
                       });

//
const GLchar * ccPositionColor_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec4 v_fragmentColor;
                       
                       void main() {
                           gl_FragColor = v_fragmentColor;
                       });
const GLchar * ccPositionColor_vert
    = CC_SHADER_STRING(attribute vec4 a_position;
                       attribute vec4 a_color;
                       varying lowp vec4 v_fragmentColor;
                       
                       void main() {
                           gl_Position = CC_MVPMatrix * a_position;
                           v_fragmentColor = a_color;
                       });

//
const GLchar * ccPositionTexture_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec2 v_texCoord;
                       uniform sampler2D CC_Texture0;
                       
                       void main() {
                           gl_FragColor =  texture2D(CC_Texture0, v_texCoord);
                       });
const GLchar * ccPositionTexture_vert
    = CC_SHADER_STRING(attribute vec4 a_position;
                       attribute vec2 a_texCoord;
                       varying mediump vec2 v_texCoord;
                       
                       void main()	{
                           gl_Position = CC_MVPMatrix * a_position;
                           v_texCoord = a_texCoord;
                       });

//
const GLchar * ccPositionTextureA8Color_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec4 v_fragmentColor;
                       varying vec2 v_texCoord;
                       uniform sampler2D CC_Texture0;
                       
                       void main()	{
                           // RGB from uniform, A from texture & uniform
                           gl_FragColor = vec4(v_fragmentColor.rgb,
                                               v_fragmentColor.a * texture2D(CC_Texture0, v_texCoord).a);
                       });
const GLchar * ccPositionTextureA8Color_vert
    = CC_SHADER_STRING(attribute vec4 a_position;
                       attribute vec2 a_texCoord;
                       attribute vec4 a_color;
                       varying lowp vec4 v_fragmentColor;
                       varying mediump vec2 v_texCoord;
                       
                       void main()	{
                           gl_Position = CC_MVPMatrix * a_position;
                           v_fragmentColor = a_color;
                           v_texCoord = a_texCoord;
                       });

//
const GLchar * ccPositionTextureColor_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec4 v_fragmentColor;
                       varying vec2 v_texCoord;
                       uniform sampler2D CC_Texture0;
                       
                       void main()	{
                           gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
                       });
const GLchar * ccPositionTextureColor_vert
    = CC_SHADER_STRING(attribute vec4 a_position;
                       attribute vec2 a_texCoord;
                       attribute vec4 a_color;
                       varying lowp vec4 v_fragmentColor;
                       varying mediump vec2 v_texCoord;
                       
                       void main() {
                           gl_Position = CC_MVPMatrix * a_position;
                           v_fragmentColor = a_color;
                           v_texCoord = a_texCoord;
                       });

//
const GLchar * ccPositionTextureColorAlphaTest_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec4 v_fragmentColor;
                       varying vec2 v_texCoord;
                       uniform sampler2D CC_Texture0;
                       uniform float CC_alpha_value;
                       
                       void main() {
                           vec4 texColor = texture2D(CC_Texture0, v_texCoord);
                           
                           // mimic: glAlphaFunc(GL_GREATER)
                           // pass if ( incoming_pixel >= CC_alpha_value ) => fail if incoming_pixel < CC_alpha_value
                           
                           if(texColor.a <= CC_alpha_value) {
                               discard;
                           }
                           
                           gl_FragColor = texColor * v_fragmentColor;
                       });

//
const GLchar * ccPositionTexture_uColor_frag
    = CC_SHADER_STRING(precision lowp float;
                       uniform vec4 u_color;
                       varying vec2 v_texCoord;
                       uniform sampler2D CC_Texture0;
                       
                       void main() {
                           gl_FragColor =  texture2D(CC_Texture0, v_texCoord) * u_color;
                       });
const GLchar * ccPositionTexture_uColor_vert
    = CC_SHADER_STRING(attribute vec4 a_position;
                       attribute vec2 a_texCoord;
                       varying mediump vec2 v_texCoord;
                       
                       void main()	{
                           gl_Position = CC_MVPMatrix * a_position;
                           v_texCoord = a_texCoord;
                       });

const GLchar * ccExSwitchMask_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec4        v_fragmentColor;
                       varying vec2        v_texCoord;
                       uniform sampler2D   u_texture;
                       uniform sampler2D   u_mask;
                       
                       void main() {
                           vec4 texColor   = texture2D(u_texture, v_texCoord);
                           vec4 maskColor  = texture2D(u_mask, v_texCoord);
                           vec4 finalColor = vec4(texColor.r, texColor.g, texColor.b, maskColor.a * texColor.a);
                           gl_FragColor    = v_fragmentColor * finalColor;
                       });

const GLchar * ccPositionColorLengthTexture_frag
    = CC_SHADER_STRING(// #extension GL_OES_standard_derivatives : enable
                       varying mediump vec4 v_color;
                       varying mediump vec2 v_texcoord;
                       
                       void main() {
                           // #if defined GL_OES_standard_derivatives
                           // gl_FragColor = v_color*smoothstep(0.0, length(fwidth(v_texcoord)), 1.0 - length(v_texcoord));
                           // #else
                           gl_FragColor = v_color*step(0.0, 1.0 - length(v_texcoord));
                           // #endif
                       });
const GLchar * ccPositionColorLengthTexture_vert
    = CC_SHADER_STRING(attribute mediump vec4 a_position;
                       attribute mediump vec2 a_texcoord;
                       attribute mediump vec4 a_color;
                       varying mediump vec4 v_color;
                       varying mediump vec2 v_texcoord;
                       
                       void main() {
                           v_color = vec4(a_color.rgb * a_color.a, a_color.a);
                           v_texcoord = a_texcoord;
                           gl_Position = CC_MVPMatrix * a_position;
                       });

// custom shaders

// flash
const char* ccShader_flash_vert = ccPositionTextureColor_vert;
const char* ccShader_flash_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec4 v_fragmentColor;
                       varying vec2 v_texCoord;
                       uniform sampler2D CC_Texture0;
                       uniform vec3 CC_flashColor;
                       uniform float CC_flashTime;
                       
                       void main() {
                           gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
                           if(gl_FragColor.a > 0.0) {
                               vec3 deltaColor = (CC_flashColor - gl_FragColor.xyz) * CC_flashTime * gl_FragColor.a;
                               gl_FragColor.xyz += deltaColor;
                           }
                       });

// blur
const char* ccShader_blur_vert = ccPositionTextureColor_vert;
const char* ccShader_blur_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec4 v_fragmentColor;
                       varying vec2 v_texCoord;
                       uniform sampler2D CC_Texture0;
                       uniform vec2 CC_blurSize;
                       uniform vec4 CC_blurSubtract;
                       
                       void main() {
                           vec4 sum = vec4(0.0);
                           sum += texture2D(CC_Texture0, v_texCoord - 4.0 * CC_blurSize) * 0.05;
                           sum += texture2D(CC_Texture0, v_texCoord - 3.0 * CC_blurSize) * 0.09;
                           sum += texture2D(CC_Texture0, v_texCoord - 2.0 * CC_blurSize) * 0.12;
                           sum += texture2D(CC_Texture0, v_texCoord - 1.0 * CC_blurSize) * 0.15;
                           sum += texture2D(CC_Texture0, v_texCoord) * 0.16;
                           sum += texture2D(CC_Texture0, v_texCoord + 1.0 * CC_blurSize) * 0.15;
                           sum += texture2D(CC_Texture0, v_texCoord + 2.0 * CC_blurSize) * 0.12;
                           sum += texture2D(CC_Texture0, v_texCoord + 3.0 * CC_blurSize) * 0.09;
                           sum += texture2D(CC_Texture0, v_texCoord + 4.0 * CC_blurSize) * 0.05;
                           
                           gl_FragColor = (sum - CC_blurSubtract) * v_fragmentColor;
                       });

// laser
const char* ccShader_laser_vert = ccPositionTextureColor_vert;
const char* ccShader_laser_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec2 v_texCoord;
                       varying vec4 v_fragmentColor;
                       
                       void main()	{
                           float fPosX = v_texCoord.x;
                           float fPosY = v_texCoord.y;
                           
                           float fR = 1.0;
                           float fG = 1.0;
                           float fB = 1.0;
                           float fA = 1.0;
                           
                           float fTime = abs(sin(CC_Time.y));
                           if(fTime < 0.3)	{
                               fTime = 0.3;
                           }
                           
                           fR = fTime / abs(fPosX - 0.5) * 0.6;
                           fG = fR * 0.3 * fTime;
                           fB = fR * (1.0 - fPosY) * fTime;
                           vec3 Color = vec3(fR, fG, fB);
                           
                           float fScale = 1.0;
                           float fPercent = 0.2;
                           float fDis = fPercent;
                           if(fPosX < fPercent) {
                               fDis = fPosX;
                           }
                           if(fPosX > 1.0 - fPercent) {
                               fDis = 1.0 - fPosX;
                           }
                           fScale = fDis / fPercent;
                           fA *= fScale;
                           
                           gl_FragColor.rgb = Color;
                           gl_FragColor.a = fA;
                       });

// lighting
const char* ccShader_lighting_vert = ccPositionTextureColor_vert;
const char* ccShader_lighting_frag
    = CC_SHADER_STRING(precision lowp float;
                       varying vec4 v_fragmentColor;
                       varying vec2 v_texCoord;
                       uniform sampler2D CC_Texture0;
                       uniform vec4 CC_lightingMul;
                       uniform vec3 CC_lightingAdd;
                       
                       void main()	{
                           gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
                           vec3 c = CC_lightingAdd * gl_FragColor.a;
                           gl_FragColor *= CC_lightingMul; 
                           gl_FragColor.xyz += c; 
                       });

// color matrix
const char* ccShader_matrix_vert = ccPositionTextureColor_vert;
const char* ccShader_matrix_frag
    = CC_SHADER_STRING(precision lowp float;
                       
                       varying vec4 v_fragmentColor;
                       varying vec2 v_texCoord;
                       uniform sampler2D CC_Texture0;
                       uniform mat4 CC_colorMatrix;
                       
                       void main()	{
                           gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
                           gl_FragColor = CC_colorMatrix * gl_FragColor; 
                       });

// shine
const char* ccShader_shine_vert
    = CC_SHADER_STRING(attribute vec4 a_position;
                       attribute vec2 a_texCoord;
                       attribute vec4 a_color;
                       
                       varying lowp vec4 v_fragmentColor;
                       varying mediump vec2 v_texCoord;
                       varying lowp vec4 v_position;
                       
                       void main()	{
                           gl_Position = CC_MVPMatrix * a_position;
                           v_position = a_position;
                           v_fragmentColor = a_color;
                           v_texCoord = a_texCoord;
                       });
const char* ccShader_shine_frag
    = CC_SHADER_STRING(precision lowp float;
                       
                       varying vec4 v_fragmentColor;
                       varying vec2 v_texCoord;
                       varying vec4 v_position;
                       uniform sampler2D CC_Texture0;
                       uniform float CC_shineWidth;
                       uniform float CC_shineTime;
                       uniform vec2 CC_shineXY1;
                       uniform vec2 CC_shineXY2;
                       uniform vec4 CC_shineColor1;
                       uniform vec4 CC_shineColor2;
                       uniform vec4 CC_shineColor3;
                       uniform vec3 CC_shinePositions;
                       
                       void main() {
                           gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
                           
                           // pattern width
                           float patternWidth = abs(CC_shineXY2.x - CC_shineXY1.x);
                           
                           // pattern offset
                           float patternOffsetX = CC_shineTime * (patternWidth + CC_shineWidth) - patternWidth;
                           
                           // get checking area
                           float minX = min(CC_shineXY1.x, CC_shineXY2.x) + patternOffsetX - patternWidth;
                           float minY = min(CC_shineXY1.y, CC_shineXY2.y);
                           float maxX = max(CC_shineXY1.x, CC_shineXY2.x) + patternOffsetX + patternWidth;
                           float maxY = max(CC_shineXY1.y, CC_shineXY2.y);
                           
                           // if pixel is in rect
                           if(v_position.x >= minX && v_position.x <= maxX && v_position.y >= minY && v_position.y <= maxY) {
                               // get gradient position
                               vec2 v = CC_shineXY2 - CC_shineXY1;
                               vec2 pv = v_position.xy - vec2(CC_shineXY1.x + patternOffsetX, CC_shineXY1.y);
                               float vLen = length(v);
                               float gradient = dot(v, pv) / vLen / vLen;
                               
                               // calculate color
                               vec4 color;
                               if(gradient >= CC_shinePositions.x && gradient <= CC_shinePositions.y) {
                                   float g = (gradient - CC_shinePositions.x) / (CC_shinePositions.y - CC_shinePositions.x);
                                   color = CC_shineColor1 * (1.0 - g) + CC_shineColor2 * g;
                                   gl_FragColor.xyz += gl_FragColor.a * color.a * color.xyz;
                               } else if(gradient > CC_shinePositions.y && gradient <= CC_shinePositions.z) {
                                   float g = (gradient - CC_shinePositions.y) / (CC_shinePositions.z - CC_shinePositions.y);
                                   color = CC_shineColor2 * (1.0 - g) + CC_shineColor3 * g;
                                   gl_FragColor.xyz += gl_FragColor.a * color.a * color.xyz;
                               }
                           }
                       });

#define LOAD_PROGRAM(name) \
    p->initWithVertexShaderByteArray(ccShader_##name##_vert, ccShader_##name##_frag); \
    p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position); \
    p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color); \
    p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords)

CCShaderCache* CCShaderCache::sharedShaderCache()
{
    if (!_sharedShaderCache) {
        _sharedShaderCache = new CCShaderCache();
        if (!_sharedShaderCache->init())
        {
            CC_SAFE_DELETE(_sharedShaderCache);
        }
    }
    return _sharedShaderCache;
}

void CCShaderCache::purgeSharedShaderCache()
{
    CC_SAFE_RELEASE_NULL(_sharedShaderCache);
}

CCShaderCache::CCShaderCache()
{

}

CCShaderCache::~CCShaderCache()
{
    for(auto& pair : m_pPrograms) {
        CC_SAFE_RELEASE(pair.second);
    }
}

bool CCShaderCache::init()
{
    loadDefaultShaders();
    return true;
}

void CCShaderCache::loadDefaultShaders()
{
    // Position Texture Color shader
    CCGLProgram *p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_PositionTextureColor);
    addProgram(p, kCCShader_PositionTextureColor);
    CC_SAFE_RELEASE(p);

    // Position Texture Color alpha test
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_PositionTextureColorAlphaTest);
    addProgram(p, kCCShader_PositionTextureColorAlphaTest);
    CC_SAFE_RELEASE(p);

    // Position, Color shader
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_PositionColor);
    addProgram(p, kCCShader_PositionColor);
    CC_SAFE_RELEASE(p);

    // Position Texture shader
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_PositionTexture);
    addProgram(p, kCCShader_PositionTexture);
    CC_SAFE_RELEASE(p);

    // Position, Texture attribs, 1 Color as uniform shader
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_PositionTexture_uColor);
    addProgram(p, kCCShader_PositionTexture_uColor);
    CC_SAFE_RELEASE(p);

    // Position Texture A8 Color shader
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_PositionTextureA8Color);
    addProgram(p, kCCShader_PositionTextureA8Color);
    CC_SAFE_RELEASE(p);

    // Position and 1 color passed as a uniform (to simulate glColor4ub )
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_Position_uColor);
    addProgram(p, kCCShader_Position_uColor);
    CC_SAFE_RELEASE(p);
    
	// Position, Legth(TexCoords, Color (used by Draw Node basically )
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_PositionLengthTexureColor);
    addProgram(p, kCCShader_PositionLengthTexureColor);
    CC_SAFE_RELEASE(p);

	// ControlSwitch
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_ControlSwitch);
    addProgram(p, kCCShader_ControlSwitch);
    CC_SAFE_RELEASE(p);
    
    // blur
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_blur);
    addProgram(p, kCCShader_blur);
    CC_SAFE_RELEASE(p);
    
    // flash in a color
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_flash);
    addProgram(p, kCCShader_flash);
    CC_SAFE_RELEASE(p);
    
    // laser
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_laser);
    addProgram(p, kCCShader_laser);
    CC_SAFE_RELEASE(p);
    
    // color operation
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_lighting);
    addProgram(p, kCCShader_lighting);
    CC_SAFE_RELEASE(p);
    
    // matrix color operation
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_matrix);
    addProgram(p, kCCShader_matrix);
    CC_SAFE_RELEASE(p);
    
    // shining
    p = new CCGLProgram();
    loadDefaultShader(p, kCCShader_shine);
    addProgram(p, kCCShader_shine);
    CC_SAFE_RELEASE(p);
}

void CCShaderCache::reloadDefaultShaders()
{
    // reset all programs and reload them
    
    // Position Texture Color shader
    CCGLProgram *p = programForKey(kCCShader_PositionTextureColor);    
    p->reset();
    loadDefaultShader(p, kCCShader_PositionTextureColor);

    // Position Texture Color alpha test
    p = programForKey(kCCShader_PositionTextureColorAlphaTest);
    p->reset();    
    loadDefaultShader(p, kCCShader_PositionTextureColorAlphaTest);
    
    // Position, Color shader
    p = programForKey(kCCShader_PositionColor);
    p->reset();
    loadDefaultShader(p, kCCShader_PositionColor);
    
    // Position Texture shader
    p = programForKey(kCCShader_PositionTexture);
    p->reset();
    loadDefaultShader(p, kCCShader_PositionTexture);
    
    // Position, Texture attribs, 1 Color as uniform shader
    p = programForKey(kCCShader_PositionTexture_uColor);
    p->reset();
    loadDefaultShader(p, kCCShader_PositionTexture_uColor);
    
    // Position Texture A8 Color shader
    p = programForKey(kCCShader_PositionTextureA8Color);
    p->reset();
    loadDefaultShader(p, kCCShader_PositionTextureA8Color);
    
    // Position and 1 color passed as a uniform (to simulate glColor4ub )
    p = programForKey(kCCShader_Position_uColor);
    p->reset();
    loadDefaultShader(p, kCCShader_Position_uColor);
    
	// Position, Legth(TexCoords, Color (used by Draw Node basically )
    p = programForKey(kCCShader_PositionLengthTexureColor);
    p->reset();
    loadDefaultShader(p, kCCShader_PositionLengthTexureColor);
    
    // blur
    p = programForKey(kCCShader_blur);
    p->reset();
    loadDefaultShader(p, kCCShader_blur);
    
    // flash
    p = programForKey(kCCShader_flash);
    p->reset();
    loadDefaultShader(p, kCCShader_flash);
    
    // laser
    p = programForKey(kCCShader_laser);
    p->reset();
    loadDefaultShader(p, kCCShader_laser);
    
    // lighting
    p = programForKey(kCCShader_lighting);
    p->reset();
    loadDefaultShader(p, kCCShader_lighting);
    
    // matrix
    p = programForKey(kCCShader_matrix);
    p->reset();
    loadDefaultShader(p, kCCShader_matrix);
    
    // shine
    p = programForKey(kCCShader_shine);
    p->reset();
    loadDefaultShader(p, kCCShader_shine);
}

void CCShaderCache::loadDefaultShader(CCGLProgram *p, ccShaderType type)
{
    switch (type) {
        case kCCShader_PositionTextureColor:
            p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccPositionTextureColor_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            
            break;
        case kCCShader_PositionTextureColorAlphaTest:
            p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccPositionTextureColorAlphaTest_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

            break;
        case kCCShader_PositionColor:  
            p->initWithVertexShaderByteArray(ccPositionColor_vert ,ccPositionColor_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);

            break;
        case kCCShader_PositionTexture:
            p->initWithVertexShaderByteArray(ccPositionTexture_vert ,ccPositionTexture_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

            break;
        case kCCShader_PositionTexture_uColor:
            p->initWithVertexShaderByteArray(ccPositionTexture_uColor_vert, ccPositionTexture_uColor_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

            break;
        case kCCShader_PositionTextureA8Color:
            p->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, ccPositionTextureA8Color_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

            break;
        case kCCShader_Position_uColor:
            p->initWithVertexShaderByteArray(ccPosition_uColor_vert, ccPosition_uColor_frag);    
            
            p->addAttribute("aVertex", kCCVertexAttrib_Position);    
            
            break;
        case kCCShader_PositionLengthTexureColor:
            p->initWithVertexShaderByteArray(ccPositionColorLengthTexture_vert, ccPositionColorLengthTexture_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            
            break;

       case kCCShader_ControlSwitch:
            p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccExSwitchMask_frag);

            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

            break;
        case kCCShader_blur:
            LOAD_PROGRAM(blur);
            break;
        case kCCShader_flash:
            LOAD_PROGRAM(flash);
            break;
        case kCCShader_laser:
            LOAD_PROGRAM(laser);
            break;
        case kCCShader_lighting:
            LOAD_PROGRAM(lighting);
            break;
        case kCCShader_matrix:
            LOAD_PROGRAM(matrix);
            break;
        case kCCShader_shine:
            LOAD_PROGRAM(shine);
            break;
        default:
            CCLOG("cocos2d: %s:%d, error shader type", __FUNCTION__, __LINE__);
            return;
    }
    
    p->setKey(type);
    p->link();
    p->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
}

CCGLProgram* CCShaderCache::programForKey(ccShaderType key)
{
    std::map<int, CCGLProgram*>::iterator iter = m_pPrograms.find(key);
    if(iter != m_pPrograms.end()) {
        return iter->second;
    } else {
        return NULL;
    }
}

void CCShaderCache::addProgram(CCGLProgram* program, ccShaderType key)
{
    program->setKey(key);
    std::map<int, CCGLProgram*>::iterator iter = m_pPrograms.find(key);
    if(iter != m_pPrograms.end()) {
        CC_SAFE_RELEASE(iter->second);
        m_pPrograms.erase(iter);
    }
    m_pPrograms[key] = program;
    CC_SAFE_RETAIN(program);
}

NS_CC_END
