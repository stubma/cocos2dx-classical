这是什么
===

这是一个私人定制的cocos2dx版本, 基于cocos2dx v2分支的最新代码, 目标是创造一个cocos2dx的古典经典版. cocos2dx目前已经全面发力于3.x版本, 2.x版本已经被抛弃, 当然, 如果他们不抛弃2.x, 我也不会创建这个项目.

我觉得2.x仍然还有价值, 同时3.x并不让我感到多大兴趣. 实际上cocos2d作为一个2d引擎, 还有很多不完善的地方, 相信无数的人已经在2.x时代踩过了很多的坑, 也不得不自己去填上这些坑, 我也一样, 为了填这些坑, 我创建了cocos2dx-better项目, 把这些坑通过外挂的方式填掉, 但是总有一些坑, 外挂解决不了, 只能改原始代码. 对于我个人而言, 目前更需要一个好用的2.x, 而不是一个有未知新坑的3.x.

另外, 我日常使用mac, 主要做iOS和Android开发, 所以其它的平台我都会删掉. 我也删掉了很多没用的东西, 比如没用的工具, 没用的模板, 没用的插件, 没用的脚本, 没用的sample, 要创建新项目就复制个HelloLua改改就完啦! cocos2dx最大的优点就是简单, 我就是要把这玩意搞简单点, 当然我一个人也维护不了那么多没用的玩意儿, 也是为了减负.

所以, 如果你正好也是一个iOS/Android开发者, 也正好还在使用cocos2dx 2.x, 不妨可以看几眼.

What is this
===

It is a customized cocos2dx, based on latest code of cocos2dx v2 branch. Its purpose is creating a classical cocos2dx branch. I created it because cocos2dx already gave up v2 but v2 is still valuable to me. v3 doesn't interest me much because it may have more bugs. So I need a better v2, not a creepy v3.

To get a better v2, I created a cocos2dx-better project to overcome limitations of v2. Now I start this project to merge cocos2dx-better code to v2 branch, and more.

I deleted many useless stuff so you may find the directory structure is very different with original cocos2dx. Yes, I want it simple, and simplicity is the best virtue of cocos2dx. If you want to create a new project, just copy HelloLua! I don't need any script to do that because cocos2dx is so simple. Of coz I don't want to maintain a whole bunch of garbage. I can't do that on my own.

I care about iOS/Android only so other platform implementation will be deleted. Are you same with me? If so, take a look at this project.

目标
===
1. 基于cocos2dx 2.x最新代码 **(已完成)**
2. 将我个人的cocos2dx-better代码融入 **(已完成)**
3. 把quick-cocos2dx那一套lua支持拷贝过来改吧改吧 **(已完成)**
4. 专注于填坑改bug, 而非大刀阔斧的修改架构 **(随时进行中)**

Purpose
===

1. based on cocos2dx v2 **(Done)**
2. merge my cocos2dx-better **(Done)**
3. provide full lua support, in quick-cocos2dx 3.x style **(Done)**
4. fix v2 bugs **(Always in progress)**	

何时结束
===
可能某天就结束了吧, 估计我也不会去用cocos2dx 3.x, 从触控的尿性和水平来看, cocos2dx没什么前途, 让我的版本成为经典吧! 有新项目还是玩玩unity吧.

Everything that has a beginning has an end
===

Maybe it ends at some day, and I won't touch cocos2dx 3.x because I don't think it has a future. All Hail 2.x! All Hail Classical! Go play Unity.

这些年, 已经填过的坑
===

* 修正工程的64位编译设置
* 使用c++11编译所有代码
* 重新实现CCLabelTTF(来自cocos2dx-better的CCRichLabelTTF):
	* 完全兼容CCLabelTTF的原有功能
	* 支持字符串中嵌入格式控制, 包括颜色, 字体, 大小, 样式, 图片, 链接, 甚至任意节点也可以(可以参看cocos2dx-better的demo)
	* 支持渲染外描边(原始的CCLabelTTF只能做内描边,基本没法看)
* CocoStudio的调整
	* 去掉了CocoStudio类的UI前缀兼容设置, 去掉了一些文件的UI前缀
	* 修正对CocoStudio Mac 1.0.0.0 beta的支持问题, 具体修改为:
		* Label构造函数中_fontSize缺省改为20, 因为mac版cocostudio默认字体大小为20, 当为20时, 不会序列化到json中
		* 对类名称"Node"的节点, 一律创建Layout
		* WidgetPropertiesReader0300::createWidget中, 检查文件版本, 如果为1.0.0.0, 认为其为mac版, 如果为mac版, 根元素读取nodeTree, 而非widgetTree
		* WidgetPropertiesReader0300::widgetFromJsonDictionary中添加page item的代码注释掉, 因为PageView重新实现后采用动态方式创建page item
		* Layout的缺省背景色类型改成NONE
		* PageView重新实现:
			* 支持动态创建页, 解决了page比较多时的性能问题
			* 使用了cocos2dx-better的VelocityTracker跟踪滑动速度, 解决了页间滑动很别扭的问题
			* 注: 不再支持从CocoStudio中直接添加page item, 必须使用PageViewDataSource接口
	* 修正LabelBMFont::setFntFile方法中的内存泄露
	* ListView的pushBackDefaultItem返回新item
	* 修正CCArmature有时候帧事件触发两次的问题
	* 修正CCArmature单帧动画不触发完成事件的问题
	* 由于CocoStudio Mac 1.0.0.0 beta没有骨骼动画功能, 需要使用骨骼动画时, 可以使用CocoStudio Windows版1.4.0.1, 1.4.0.1以上版本我没有测试过.
	* Widget添加addScriptTouchEventListener以支持在lua处理Widget的触摸事件
	* 修正Widget.removeChild的内存泄露
	* CCArmatureAnimation添加hasFrameEvent用于检测是否存在某个帧事件 
	* 看不见的widget不再响应touch事件
	* 让查找路径对CocoStudio生效, 不再只从界面文件json所在目录查找图片
	* 为CocoStudio添加了国际化支持, 如果文本以@开头, 则会认为是一个字符串键值, 将通过CCLocalization获得字符串.
* 重新实现TMX地图, 支持一个层有多张贴图的情况(来自cocos2dx-better的CBTMXTileMap)
* 重新实现CCTableView(来自cocos2dx-better中的CCGridView代码):
	* CCTableView支持多列
	* 支持cell重用, cell可以设置名称
	* 支持不等宽度的行或列
	* 支持设置行间距, 列间距, 边界间距
* CCProtocols.h增加CCMeasurableProtocol, 让LoadingBar, CCProgressTimer实现CCMeasurableProtocol. 从而让CCProgressTo, CCProgressFromTo支持UILoadingBar
* CCLabelBMFont添加了setLineKerning, 用于调整行间距
* CCScrollView添加方法可以设置min/max scale
* CCScrollView.setContentOffsetInDuration会检测偏移值, 确保不会超过边界
* CCScrollView添加getNodeFullyVisibleOffset方法
* 重新实现CCLayerMultiplex以避免某些情况下发生的内存泄露
* CCLayer增加is/setSwallowTouch, 从而可以控制CCScrollView是否吞掉touch
* CCSpriteBatchNode的insertQuadFromSprite, updateQuadFromSprite, addSpriteWithoutQuad改为public
* CCScrollView增加getTouchPoint方法获得最后一次点击位置
* 修正CCScrollView的isNodeVisible方法
* CCRepeatForever覆盖stop方法, 停掉内部动作
* copy()返回的对象不再需要release
* setShaderProgram可以设置参数, 从而支持多个节点使用同一个shader但参数不同
* CCNode添加了nodeToAncestorTransform, ancestorToNodeTransform, convertToParentSpace, convertToParentSpaceAR方法
* CCNode添加了onChildWillDetach方法, 可以设置一个子节点在删除自身时父节点获得通知, 支持lua端收到通知
* CCNode添加了isVisibleInTree方法, 用来判断节点是否在ui树中可见
* 设计了一个资源打包工具, lpk_ui是它的图形界面, lpk_console是命令行工具, 不过这个工具我只是调试完成, 尚未在实际项目中验证, 而且引擎也需要修改来支持这个工具, 所以目前仅供参考
* 集成了SuperAnimConverter工具和它的代码, 改名为CCSuperAnim, 为其添加了lua支持, HelloLua工程增加了SuperAnim的演示
* CCEGLViewProtocol添加了setMultipleTouchEnabled方法
* CCFileUtils增加enableMain/PatchApkExpansion方法, CocosdxHelper增加若干XApk相关方法, 在Android上支持从apk expansion读取资源.
* Keypad事件添加了优先级支持
* 修正了对ETC1格式贴图的支持, HelloLua演示了ETC1贴图的使用
* CCScale9Sprite.h/cpp挪到了sprite_nodes目录下, 添加了getSpriteFrame方法
* CCAnimate支持CCScale9Sprite
* Lua相关修改
	* quick 3.x的binding generator工具移植完成, 名叫autolua, 引擎的lua绑定已经全部生成. 如果想要重新生成绑定, 可以到autolua目录下执行```./autolua.py cocos2dx.conf```. 这个目录下还有一个简单的test.conf可以用于测试autolua.
	* Cocos2dxLuaLoader的逻辑被修改, 会优先从~/Library寻找lua脚本, 如果没有找到则载入app的.
	* lua和luajit的库都已经预编译, 缺省使用luajit库, 如果想切换成lua, 可以编辑scripting/lua/Android.mk(for android)或cocos2dx/proj.ios/cocos2dx.xcodeproj(for ios)
	* HelloLua工程修改调试通过, 在Android上已经采用gradle对HelloLua进行打包, 注意你可能需要修改local.properties上的sdk.dir/ndk.dir配置.
	* 使用ccScriptFunction代表一个脚本方法, 替代了原来使用int的方式. 引擎中注册脚本方法相关的代码都改成使用ccScriptFunction, 相应的牵涉到CCLuaEngine, CCLuaStack等都有不少修改, 脚本回调方法可以获得self参数, 解决了脚本回调方法中获取self不方便的问题
	* 逐渐完善一些公用库, 都放在scripting/lua/script下, 提供一些基本的封装
	* 加入了lfs方便载入脚本, 修正了Cocos2dxLuaLoader和lfs冲突的问题
	* 加入了位操作库
	* 修正了一些tolua_fix的bug
	* 添加了tolua.isa方法
	* script端的CCNotification监听方法现在可以收到额外参数
	* 修改了extern.lua, 添加了dtor方法, 会在C++对象析构时调用. 对于纯lua对象dtor方法暂时无用.
	* CCDirector/CCEGLView的end方法改名为terminate, 避免和lua的关键字冲突
	* CCObject添加了set/getScriptUserData, 支持在lua端为CCObject关联一个lua table
	* string包增加了split, tonumber, toint, tobool, empty方法
	* table包增加了print, hasnumber, hasstring, fill, fillnew, enum方法
	* debug包增加了addtrace, removetrace方法
	* tools下有xcode_lua_support工具, 可以为Xcode添加lua语法高亮
	* 添加CCApplicationLua, 封装通用的初始化逻辑, AppDelegate可以不再需要. applicationDidEnterBackground和applicationWillEnterForeground被导引到lua端.
	* 在Cocos2dxLuaLoader.cpp中添加lua脚本解密支持. 可以通过CCScriptEngineManager设置一个外部解密方法.
	* CCLuaStack.executeScriptFile方法添加解密支持

cocos2dx-better新加的其它功能我就不列举了, 目前cocos2dx-better的代码已经合并完成, 有一部分代码我感觉写的用处不大就没有合并了, 不过只是一小部分, 95%的cocos2dx-better代码已经合并.

Things Improved
===

* fixed project 64bits compiling
* reimplement CCLabelTTF (merge code from cocos2dx-better CCRichLabelTTF)
	* fully compatibile with old CCLabelTTF
	* support attibuted style, such as color, font, size, style, image, link, even CCNode can be inserted(you can view cocos2dx-better demo)
	* support outer stroke, it is better than original CCLabelTTF which only supports inner stroke
* polish CocoStudio
	* remove UI prefix
	* fix json parsing bug for CocoStudio Mac 1.0.0.0 beta, what I did:
		* set Label default _fontSize to 20 because CocoStudio Mac use 20 by default
		* create Layout for node whose name is "Node"
		* check version in WidgetPropertiesReader0300::createWidget to detect CocoStudio Mac json. If Mac version, need read nodeTree tag, not widgetTree tag
		* because PageView is reimplemented, comment out page item code in WidgetPropertiesReader0300::widgetFromJsonDictionary
		* set Layout default background color style to NONE
		* reimplement PageView
			* use data source to create page item dynamically, and reuseable
			* use VelocityTracker (from cocos2dx-better) to improve page slide experience
			* Note: don't support add page item in CocoStudio
	* fix memory leak in LabelBMFont::setFntFile
	* return created item in Listview::pushBackDefaultItem
	* fix bug: CCArmature frame event may be triggered more than once
	* fix bug: CCArmature single frame animation doesn't trigger complete event
	* Note: if you want to use skeleton animation, please still use CocoStudio Windows version, 1.4.0.1 is recommended.
	* Widget adds addScriptTouchEventListener to support process widget touch event in lua side
	* fix memory leak in Widget.removeChild
	* CCArmatureAnimation adds hasFrameEvent to detect existence of a frame event
	* Invisible widget won't response to touch event
	* fix CocoStudio image search logic, now search paths works for it
	* add localization support for CocoStudio, any text starts with @ will be treat as a string key and engine will use CCLocalization to get final string, based on system current locale setting.
* reimplement TMX, support multi-tileset for one layer(merge from cocos2dx-better CBTMXTileMap)
* reimplement CCTableView(merge from cocos2dx-better CCGridView):
	* support multi-column
	* support cell reuse, cell can set name
	* columns or rowr can be different size
	* support to set row spacing, col spacing and border spacing
* add CCMeasurableProtocol class to abstract LoadingBar and CCProgressTimer, so that CProgressTo, CCProgressFromTo can be used on LoadingBar
* CCLabelBMFont adds setLineKerning to adjust line spacing
* CCScrollView add methods to set min/max scale
* reimplement CCLayerMultiplex to avoid memory leak
* CCLayer adds is/setSwallowTouch to control swallowing touch or not
* CCSpriteBatchNode insertQuadFromSprite, updateQuadFromSprite, addSpriteWithoutQuad are changed to public
* CCScrollView adds getTouchPoint to get last touch position
* CCScrollView.setContentOffsetInDuration will ensure offset is in bound
* CCScrollView adds getNodeFullyVisibleOffset method
* fix CCScrollView isNodeVisible method
* CCRepeatForever override stop method
* setShaderProgram can specify uniform values so that one shader can be shared by many nodes
* CCNode adds nodeToAncestorTransform, ancestorToNodeTransform, convertToParentSpace, convertToParentSpaceAR
* CCNode add onChildWillDetach, a child can notify parent when it removes self.
* CCNode add isVisibleInTree method
* add a tool for resource pack, lpk_ui is UI tool, lpk_console is command tool. However, it is not tested in a real project. It is only for your reference by so far.
* Merge SuperAnimConverter.app and its code, rename it as CCSuperAnim and add lua support. There is a sample in HelloLua project
* CCEGLViewProtocol add setMultipleTouchEnabled method
* Android apk expansion is supported, CCFileUtils add enableMain/PatchApkExpansion method.
* Support setting priority for keypad event
* Fix ETC1 texture support, HelloLua demos the usage of ETC1 texture
* moved CCScale9Sprite.h/cpp to sprite_nodes folder, add getSpriteFrame method to it
* CCAnimate supports CCScale9Sprite
* Lua related
	* quick 3.x binding generator is migrated and renamed to autolua. Engine lua binding is completely generated. If you want to re-generate it, you can execute ```./autolua.py cocos2dx.conf``` in autolua folder
	* lua and luajit are both precompiled, by default we use luajit. if you want to use lua, you can modify scripting/lua/Android.mk(for android) or cocos2dx/proj.ios/cocos2dx.xcodeproj(for ios)
	* HelloLua project is debugged and fine. In Android, I use gradle to package HelloLua, so you may need change sdk.dir/ndk.dir in local.properties
	* Cocos2dxLuaLoader is modified so that it will try to load lua script from ~/Library first. If not found, load from app bundle.
	* use ccScriptFunction struct to replace int handler, modified all related code. So now it is easy to access self in script callback.
	* adding more shared library, in scripting/lua/script
	* add lfs to easily load lua files under a folder, fix conflict between Cocos2dxLuaLoader and lfs
	* add bit operation library
	* fix some bugs of tolua_fix
	* add tolua.isa method
	* CCNotification script observer can get extra parameters now
	* lua class add a dtor method to receive CCObject destruction event. For lua object, dtor is never called.
	* rename CCDirector/CCEGLView end method to terminate, to avoid name conflict with lua keyword
	* add set/getScriptUserData for CCObject so that we can associate a lua table to CCObject
	* string package adds split, tonumber, toint, tobool, empty methods
	* table package adds print, hasnumber, hasstring, fill, fillnew, enum methods
	* debug package adds addtrace, removetrace method
	* xcode_lua_support tool, can add lua syntax highlight for Xcode
	* add CCApplicationLua to encapsulate basic logic of lua app, so that AppDelegate can be eliminated. applicationDidEnterBackground and applicationWillEnterForeground are dispatched to lua side.
	* add lua decryption support in Cocos2dLuaLoader.cpp, you can set an eternal decrypt function through CCScriptEngineManager
	* CCLuaStack.executeScriptFile supports encrypted lua file
	
I don't want to list all new classes in cocos2dx-better. To get a overview about cocos2dx-better features, go to it and run its demo.

额外说明: CCImagePicker使用方法
=============================
我实现了一个CCImagePicker作为通用的图片选择/拍摄接口, 支持返回任意大小的图片, 具体可以看cocos2dx-better里的demo, 至少我觉得还是相当好用的. 在iOS里不需要什么配置, 直接用就行. 在Android上, 需要配置一下:

* 在AndroidManifest.xml注册activity, 屏幕朝向你可以自己选择, 横竖都支持.

```
<activity
    android:name="org.cocos2dx.lib.cropimage.CropImage"
    android:configChanges="keyboardHidden|orientation"
    android:screenOrientation="portrait"
    android:theme="@android:style/Theme.NoTitleBar.Fullscreen" >
</activity>
<activity
    android:name="org.cocos2dx.lib.ImagePickerActivity"
    android:configChanges="keyboardHidden|orientation"
    android:screenOrientation="portrait"
    android:theme="@android:style/Theme.NoTitleBar.Fullscreen" >
</activity>
```

* 添加相机的权限

```
<uses-permission android:name="android.permission.CAMERA" />
```

* 添加相机的特性需求

```
<uses-feature
    android:name="android.hardware.camera"
    android:required="false" />
<uses-feature
    android:name="android.hardware.camera.front"
    android:required="false" />
```

OK了. 具体使用参考cocos2dx-better的demo.
	
Extra: How to use CCImagePicker
==========================
There is a CCImagePicker merged from cocos2dx-better, it can take image from camera or album and return it in any size. It is very handy, but you need more setup before using it. In iOS, just use it. In Android, don't forget to config something:
* register activities in AndroidManifest.xml, below is an example, you can change some attribute if you like, such as screenOrientation.

```
<activity
    android:name="org.cocos2dx.lib.cropimage.CropImage"
    android:configChanges="keyboardHidden|orientation"
    android:screenOrientation="portrait"
    android:theme="@android:style/Theme.NoTitleBar.Fullscreen" >
</activity>
<activity
    android:name="org.cocos2dx.lib.ImagePickerActivity"
    android:configChanges="keyboardHidden|orientation"
    android:screenOrientation="portrait"
    android:theme="@android:style/Theme.NoTitleBar.Fullscreen" >
</activity>
```

* add necessary permission

```
<uses-permission android:name="android.permission.CAMERA" />
```

* add feature declaration

```
<uses-feature
    android:name="android.hardware.camera"
    android:required="false" />
<uses-feature
    android:name="android.hardware.camera.front"
    android:required="false" />
```

And that is it! No more settings needed.