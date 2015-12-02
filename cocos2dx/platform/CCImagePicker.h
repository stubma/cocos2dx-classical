/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-classical
 
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
#ifndef __CCImagePicker__
#define __CCImagePicker__

#include "ccTypes.h"
#include "CCImagePickerCallback.h"
#include "script_support/CCScriptSupport.h"

using namespace std;

NS_CC_BEGIN

/**
 * Image picker wrapper. Picked image will be saved into a file and caller should provide a callback
 * to get the file path.
 *
 * for lua side callback, it should looks like below:
     function XXX:onImagePickerEvent(picker, e)
         if e == cc.ImagePickerEventOK then
         elseif e == cc.ImagePickerEventCancelled then
         end
     end
 *
 * \note
 * It supports Android 2.3+, but parameter keepRatio is not supported in Android.
 */
class CC_DLL CCImagePicker : public CCObject {
private:
    /// script side table data source and delegate
    ccScriptFunction m_scriptHandler;
    
    /// c callback
    CCImagePickerCallback* m_callback;
    
    /// expected output image width
    int m_expectedWidth;
    
    /// expected output image height
    int m_expectedHeight;
    
    /// keep ratio or not
    bool m_keepRatio;
    
    /// use front camera if has
    bool m_useFrontCamera;
    
    /// output image path, it will be mapped to platform writable path. In iOS, it is ~/Documents
    string m_path;
    
    /// output image full path, it should be set when image picking done
    string m_fullPath;
    
protected:
    // unregister handler
    void unregisterScriptHandler();
	
public:
    CCImagePicker();
    virtual ~CCImagePicker();
    
    static CCImagePicker* create();
    
	/**
	 * does device have camera
	 *
	 * @return true means device has at least one camera
	 */
	static bool hasCamera();
	
	/**
	 * does device have front camera
	 *
	 * @return true means device has front camera
	 */
	static bool hasFrontCamera();
	
    /**
     * pick a image from camera and save it to file
     */
    void pickFromCamera();
	
	/**
	 * pick a image from album and save it to a file
	 */
	void pickFromAlbum();
    
    // setter and getter
    void setCallback(CCImagePickerCallback* c) { m_callback = c; }
    CCImagePickerCallback* getCallback() { return m_callback; }
    void setExpectedWidth(int w) { m_expectedWidth = w; }
    int getExpectedWidth() { return m_expectedWidth; }
    void setExpectedHeight(int h) { m_expectedHeight = h; }
    int getExpectedHeight() { return m_expectedHeight; }
    void setKeepRatio(bool v) { m_keepRatio = v; }
    bool isKeepRatio() { return m_keepRatio; }
    void setUseFrontCamera(bool v) { m_useFrontCamera = v; }
    bool isUseFrontCamera() { return m_useFrontCamera; }
    void setPath(const string& p) { m_path = p; }
    const string& getPath() { return m_path; }
    void setFullPath(const string& p) { m_fullPath = p; }
    const string& getFullPath() { return m_fullPath; }
    void setScriptHandler(ccScriptFunction handler);
    ccScriptFunction getScriptHandler() { return m_scriptHandler; }
    
    // for internal use only
    void notifyImagePickedOK();
    void notifyImagePickingCancelled();
};

NS_CC_END

#endif // __CCImagePicker__
