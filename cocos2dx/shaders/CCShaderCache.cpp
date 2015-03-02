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
const GLchar * ccPosition_uColor_frag =
#include "ccShader_Position_uColor_frag.h"
const GLchar * ccPosition_uColor_vert =
#include "ccShader_Position_uColor_vert.h"

//
const GLchar * ccPositionColor_frag =
#include "ccShader_PositionColor_frag.h"
const GLchar * ccPositionColor_vert =
#include "ccShader_PositionColor_vert.h"

//
const GLchar * ccPositionTexture_frag =
#include "ccShader_PositionTexture_frag.h"
const GLchar * ccPositionTexture_vert =
#include "ccShader_PositionTexture_vert.h"

//
const GLchar * ccPositionTextureA8Color_frag =
#include "ccShader_PositionTextureA8Color_frag.h"
const GLchar * ccPositionTextureA8Color_vert =
#include "ccShader_PositionTextureA8Color_vert.h"

//
const GLchar * ccPositionTextureColor_frag =
#include "ccShader_PositionTextureColor_frag.h"
const GLchar * ccPositionTextureColor_vert =
#include "ccShader_PositionTextureColor_vert.h"

//
const GLchar * ccPositionTextureColorAlphaTest_frag =
#include "ccShader_PositionTextureColorAlphaTest_frag.h"

//
const GLchar * ccPositionTexture_uColor_frag =
#include "ccShader_PositionTexture_uColor_frag.h"
const GLchar * ccPositionTexture_uColor_vert =
#include "ccShader_PositionTexture_uColor_vert.h"

const GLchar * ccExSwitchMask_frag =
#include "ccShaderEx_SwitchMask_frag.h"

const GLchar * ccPositionColorLengthTexture_frag =
#include "ccShader_PositionColorLengthTexture_frag.h"
const GLchar * ccPositionColorLengthTexture_vert =
#include "ccShader_PositionColorLengthTexture_vert.h"

// custom shaders
#include "shaders/ccShader_flash_vert.h"
#include "shaders/ccShader_flash_frag.h"
#include "shaders/ccShader_blur_vert.h"
#include "shaders/ccShader_blur_frag.h"
#include "shaders/ccShader_laser_vert.h"
#include "shaders/ccShader_laser_frag.h"
#include "shaders/ccShader_lighting_frag.h"
#include "shaders/ccShader_lighting_vert.h"
#include "shaders/ccShader_matrix_vert.h"
#include "shaders/ccShader_matrix_frag.h"
#include "shaders/ccShader_shine_vert.h"
#include "shaders/ccShader_shine_frag.h"

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
