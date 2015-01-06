/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-better
 
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
#include "CCShaders.h"
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
#include "shaders/CCGLProgram.h"

NS_CC_BEGIN

// uniform location
static GLint sUniformLocations[kCCUniform_MAX] = { -1 };

#define LOAD_PROGRAM_IF(name) \
    if(key == kCCShader_##name) \
        p->initWithVertexShaderByteArray(ccShader_##name##_vert, ccShader_##name##_frag)
#define ADD_UNIFORM(name) \
    sUniformLocations[kCCUniform_##name] = p->getUniformLocationForName(kCCUniformNames[kCCUniform_##name])

void CCShaders::loadCustomShader(const string& key) {
    if(!CCShaderCache::sharedShaderCache()->programForKey(key.c_str())) {
		// load shader
        CCGLProgram* p = new CCGLProgram();
		CC_SAFE_AUTORELEASE(p);
		LOAD_PROGRAM_IF(flash);
		LOAD_PROGRAM_IF(blur);
		LOAD_PROGRAM_IF(laser);
        LOAD_PROGRAM_IF(lighting);
        LOAD_PROGRAM_IF(matrix);
        LOAD_PROGRAM_IF(shine);
		
		// add attribute
		if(false) {
			// non-default situation
		} else {
			p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
			p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
			p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		}

		// link it
        p->link();
		
		// add custom uniform
		if(key == kCCShader_flash) {
			ADD_UNIFORM(flashColor);
			ADD_UNIFORM(flashTime);
		} else if(key == kCCShader_blur) {
			ADD_UNIFORM(blurSize);
			ADD_UNIFORM(blurSubtract);
		} else if(key == kCCShader_lighting) {
            ADD_UNIFORM(lightingMul);
            ADD_UNIFORM(lightingAdd);
        } else if(key == kCCShader_matrix) {
            ADD_UNIFORM(colorMatrix);
        } else if(key == kCCShader_shine) {
            ADD_UNIFORM(shineWidth);
            ADD_UNIFORM(shineXY1);
            ADD_UNIFORM(shineXY2);
            ADD_UNIFORM(shineColor1);
            ADD_UNIFORM(shineColor2);
            ADD_UNIFORM(shineColor3);
            ADD_UNIFORM(shinePositions);
            ADD_UNIFORM(shineTime);
        }
		
		// add standard uniforms
        p->updateUniforms();
		
		// add program
        CCShaderCache::sharedShaderCache()->addProgram(p, key.c_str());
    }
}

void CCShaders::loadCustomShaders() {
    loadCustomShader(kCCShader_flash);
    loadCustomShader(kCCShader_blur);
    loadCustomShader(kCCShader_lighting);
    loadCustomShader(kCCShader_matrix);
    loadCustomShader(kCCShader_shine);
    loadCustomShader(kCCShader_laser);
}

CCGLProgram* CCShaders::programForKey(const string& key) {
	return CCShaderCache::sharedShaderCache()->programForKey(key.c_str());
}

void CCShaders::setUniformValue(CCGLProgram* p, ccCustomUniformValue& v) {
    if(p->getKey() == kCCShader_blur) {
        p->setUniformLocationWith2f(sUniformLocations[kCCUniform_blurSize],
                                    v.blur.blurSize.width / v.blur.nodeSize.width,
                                    v.blur.blurSize.height / v.blur.nodeSize.height);
        p->setUniformLocationWith4f(sUniformLocations[kCCUniform_blurSubtract],
                                    v.blur.subtract.r, v.blur.subtract.g, v.blur.subtract.b, v.blur.subtract.a);
    } else if(p->getKey() == kCCShader_flash) {
        p->setUniformLocationWith3f(sUniformLocations[kCCUniform_flashColor], v.flash.r, v.flash.g, v.flash.b);
        p->setUniformLocationWith1f(sUniformLocations[kCCUniform_flashTime], v.flash.t);
    } else if(p->getKey() == kCCShader_lighting) {
        p->setUniformLocationWith4f(sUniformLocations[kCCUniform_lightingMul],
                                    v.lighting.mul.r / 255.0f,
                                    v.lighting.mul.g / 255.0f,
                                    v.lighting.mul.b / 255.0f,
                                    v.lighting.mul.a / 255.0f);
        p->setUniformLocationWith3f(sUniformLocations[kCCUniform_lightingAdd],
                                    v.lighting.add.r / 255.0f,
                                    v.lighting.add.g / 255.0f,
                                    v.lighting.add.b / 255.0f);
    } else if(p->getKey() == kCCShader_matrix) {
        p->setUniformLocationWithMatrix4fv(sUniformLocations[kCCUniform_colorMatrix], (GLfloat*)v.matrix.mat4.mat, 1);
    } else if(p->getKey() == kCCShader_shine) {
        p->setUniformLocationWith1f(sUniformLocations[kCCUniform_shineWidth], v.shine.width);
        p->setUniformLocationWith1f(sUniformLocations[kCCUniform_shineTime], v.shine.time);
        p->setUniformLocationWith2f(sUniformLocations[kCCUniform_shineXY1], v.shine.lb.x, v.shine.lb.y);
        p->setUniformLocationWith2f(sUniformLocations[kCCUniform_shineXY2], v.shine.rt.x, v.shine.rt.y);
        p->setUniformLocationWith4f(sUniformLocations[kCCUniform_shineColor1],
                                    v.shine.color1.r / 255.0f,
                                    v.shine.color1.g / 255.0f,
                                    v.shine.color1.b / 255.0f,
                                    v.shine.color1.a / 255.0f);
        p->setUniformLocationWith4f(sUniformLocations[kCCUniform_shineColor2],
                                    v.shine.color2.r / 255.0f,
                                    v.shine.color2.g / 255.0f,
                                    v.shine.color2.b / 255.0f,
                                    v.shine.color2.a / 255.0f);
        p->setUniformLocationWith4f(sUniformLocations[kCCUniform_shineColor3],
                                    v.shine.color3.r / 255.0f,
                                    v.shine.color3.g / 255.0f,
                                    v.shine.color3.b / 255.0f,
                                    v.shine.color3.a / 255.0f);
        p->setUniformLocationWith3f(sUniformLocations[kCCUniform_shinePositions],
                                    v.shine.gradientPositions.x, v.shine.gradientPositions.y, v.shine.gradientPositions.z);
    }
}

NS_CC_END