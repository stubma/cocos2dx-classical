/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) Microsoft Open Technologies, Inc.

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

#ifndef __COCOS2D_H__
#define __COCOS2D_H__

// 0x00 HI ME LO
// 00   02 02 05
#define COCOS2D_VERSION 0x00020205

//
// all cocos2d include files
//
#include "ccConfig.h"

// actions
#include "actions/CCAction.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionCamera.h"
#include "actions/CCActionManager.h"
#include "actions/CCActionEase.h"
#include "actions/CCActionPageTurn3D.h"
#include "actions/CCActionGrid.h"
#include "actions/CCActionProgressTimer.h"
#include "actions/CCActionGrid3D.h"
#include "actions/CCActionTiledGrid.h"
#include "actions/CCActionInstant.h"
#include "actions/CCActionTween.h"
#include "actions/CCActionCatmullRom.h"
#include "actions/CCTreeFadeIn.h"
#include "actions/CCTreeFadeOut.h"
#include "actions/CCClipIn.h"
#include "actions/CCClipOut.h"
#include "actions/CCBlur.h"
#include "actions/CCCount.h"
#include "actions/CCCurl.h"
#include "actions/CCFlash.h"
#include "actions/CCShine.h"
#include "actions/CCShake.h"
#include "actions/CCMissile.h"
#include "actions/CCTrailMoveTo.h"
#include "actions/CCCallFuncT.h"
#include "actions/CCCallFuncNT.h"

// base_nodes
#include "base_nodes/CCNode.h"
#include "base_nodes/CCAtlasNode.h"

// cocoa
#include "cocoa/CCAffineTransform.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCGeometry.h"
#include "cocoa/CCSet.h"
#include "cocoa/CCAutoreleasePool.h"
#include "cocoa/CCInteger.h"
#include "cocoa/CCFloat.h"
#include "cocoa/CCDouble.h"
#include "cocoa/CCBool.h"
#include "cocoa/CCString.h"
#include "cocoa/CCNS.h"
#include "cocoa/CCZone.h"

// draw nodes
#include "draw_nodes/CCDrawingPrimitives.h"
#include "draw_nodes/CCDrawNode.h"

// effects
#include "effects/CCGrabber.h"
#include "effects/CCGrid.h"

// include
#include "CCEventType.h"
#include "CCProtocols.h"
#include "ccConfig.h"
#include "ccMacros.h"
#include "ccTypes.h"

// kazmath
#include "kazmath/include/kazmath/kazmath.h"
#include "kazmath/include/kazmath/GL/matrix.h"

// keypad_dispatcher
#include "keypad_dispatcher/CCKeypadDelegate.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"

// label_nodes
#include "label_nodes/CCLabelAtlas.h"
#include "label_nodes/CCLabelTTF.h"
#include "label_nodes/CCLabelBMFont.h"
#include "label_nodes/CCLabelTTFLinkStateSynchronizer.h"

// layers_scenes_transitions_nodes
#include "layers_scenes_transitions_nodes/CCLayer.h"
#include "layers_scenes_transitions_nodes/CCScene.h"
#include "layers_scenes_transitions_nodes/CCTransition.h"
#include "layers_scenes_transitions_nodes/CCTransitionPageTurn.h"
#include "layers_scenes_transitions_nodes/CCTransitionProgress.h"
#include "layers_scenes_transitions_nodes/CCLayerClip.h"

// menu_nodes
#include "menu_nodes/CCMenu.h"
#include "menu_nodes/CCMenuItem.h"
#include "menu_nodes/CCMenuItemColorStateListener.h"
#include "menu_nodes/CCMenuItemColor.h"

// misc_nodes
#include "misc_nodes/CCClippingNode.h"
#include "misc_nodes/CCMotionStreak.h"
#include "misc_nodes/CCProgressTimer.h"
#include "misc_nodes/CCRenderTexture.h"
#include "misc_nodes/CCProgressHUD.h"
#include "misc_nodes/CCToast.h"

// particle_nodes
#include "particle_nodes/CCParticleBatchNode.h"
#include "particle_nodes/CCParticleSystem.h"
#include "particle_nodes/CCParticleExamples.h"
#include "particle_nodes/CCParticleSystemQuad.h"

// platform
#include "platform/CCDevice.h"
#include "platform/CCCommon.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
#include "platform/CCThread.h"
#include "platform/platform.h"
#include "platform/CCPlatformConfig.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCUUID.h"
#include "platform/CCLocale.h"
#include "platform/CCAssetInputStream.h"
#include "platform/CCAssetOutputStream.h"
#include "platform/CCMemoryInputStream.h"
#include "platform/CCMemoryOutputStream.h"
#include "platform/CCCalendar.h"
#include "platform/CCImagePicker.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "platform/ios/CCAccelerometer.h"
    #include "platform/ios/CCApplication.h"
    #include "platform/ios/CCEGLView.h"
    #include "platform/ios/CCGL.h"
    #include "platform/ios/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/CCAccelerometer.h"
    #include "platform/android/CCApplication.h"
    #include "platform/android/CCEGLView.h"
    #include "platform/android/CCGL.h"
    #include "platform/android/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

// script_support
#include "script_support/CCScriptSupport.h"

// shaders
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCShaders.h"

// sprite_nodes
#include "sprite_nodes/CCAnimation.h"
#include "sprite_nodes/CCAnimationCache.h"
#include "sprite_nodes/CCSprite.h"
#include "sprite_nodes/CCSpriteBatchNode.h"
#include "sprite_nodes/CCSpriteFrame.h"
#include "sprite_nodes/CCSpriteFrameCache.h"
#include "sprite_nodes/CCGradientSprite.h"
#include "sprite_nodes/CCTiledSprite.h"
#include "sprite_nodes/CCCatmullRomSprite.h"

// afcanim
#include "afcanim/CCAFCConstants.h"
#include "afcanim/CCAFCAnimation.h"
#include "afcanim/CCAFCClip.h"
#include "afcanim/CCAFCClipMapping.h"
#include "afcanim/CCAFCFileData.h"
#include "afcanim/CCAFCFrame.h"
#include "afcanim/CCAFCSprite.h"
#include "afcanim/CCArcticFileData.h"
#include "afcanim/CCArcticManager.h"
#include "afcanim/CCArcticSprite.h"
#include "afcanim/CCArcticLoader.h"
#include "afcanim/CCAuroraFileData.h"
#include "afcanim/CCAuroraManager.h"
#include "afcanim/CCAuroraSprite.h"
#include "afcanim/CCAuroraLoader.h"
#include "afcanim/CCMWFileData.h"
#include "afcanim/CCMWManager.h"
#include "afcanim/CCMWSprite.h"
#include "afcanim/CCMWLoader.h"
#include "afcanim/CCSPX3FileData.h"
#include "afcanim/CCSPX3Manager.h"
#include "afcanim/CCSPX3Sprite.h"
#include "afcanim/CCSPX3Loader.h"
#include "afcanim/CCSPXFileData.h"
#include "afcanim/CCSPXManager.h"
#include "afcanim/CCSPXSprite.h"
#include "afcanim/CCSPXLoader.h"

// support
#include "support/ccUTF8.h"
#include "support/CCNotificationCenter.h"
#include "support/CCPointExtension.h"
#include "support/profile/CCProfiling.h"
#include "support/profile/CCMemory.h"
#include "support/user_default/CCUserDefault.h"
#include "support/user_default/CCSecureUserDefault.h"
#include "support/CCVertex.h"
#include "support/tinyxml2/tinyxml2.h"
#include "support/CCSAXParser.h"
#include "support/CCBase64.h"
#include "support/CCMD5.h"
#include "support/locale/CCLocalization.h"
#include "support/utils/CCUtils.h"
#include "support/utils/CCPinyinUtils.h"
#include "support/ui_support/CCScroller.h"
#include "support/ui_support/CCVelocityTracker.h"
#include "support/data_support/CCPointList.h"
#include "support/json/CCJSONValue.h"
#include "support/json/CCJSONObject.h"
#include "support/json/CCJSONArray.h"
#include "support/json/CCJSONParser.h"
#include "support/db/CCDatabase.h"
#include "support/db/CCResultSet.h"
#include "support/db/CCStatement.h"
#include "support/res_support/CCResourceLoader.h"
#include "support/network/CCFileDownloader.h"
#include "support/network/CCByteBuffer.h"
#include "support/network/CCTCPSocket.h"
#include "support/network/CCTCPSocketHub.h"
#include "support/network/CCUDPSocket.h"
#include "support/network/CCUDPSocketHub.h"
#include "support/network/CCPacket.h"

// text_input_node
#include "text_input_node/CCIMEDelegate.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "text_input_node/CCTextFieldTTF.h"

// textures
#include "textures/CCTexture2D.h"
#include "textures/CCTextureAtlas.h"
#include "textures/CCTextureCache.h"
#include "textures/CCTexturePVR.h"
#include "textures/CCTextureETC.h"

// tilemap_parallax_nodes
#include "tilemap_parallax_nodes/CCParallaxNode.h"
#include "tilemap_parallax_nodes/CCTMXLayer.h"
#include "tilemap_parallax_nodes/CCTMXObjectGroup.h"
#include "tilemap_parallax_nodes/CCTMXTiledMap.h"
#include "tilemap_parallax_nodes/CCTMXLoader.h"
#include "tilemap_parallax_nodes/CCTileMapAtlas.h"
#include "tilemap_parallax_nodes/CCTMXObjectDebugRenderer.h"
#include "tilemap_parallax_nodes/CCTMXTileSetInfo.h"
#include "tilemap_parallax_nodes/CCTMXMapInfo.h"
#include "tilemap_parallax_nodes/CCTMXLayerInfo.h"

// touch_dispatcher
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouchHandler.h"

// root
#include "CCCamera.h"
#include "CCConfiguration.h"
#include "CCDirector.h"
#include "CCScheduler.h"

// component
#include "support/component/CCComponent.h"
#include "support/component/CCComponentContainer.h"

NS_CC_BEGIN

CC_DLL const char* cocos2dVersion();

NS_CC_END

#endif // __COCOS2D_H__
