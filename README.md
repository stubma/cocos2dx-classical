这是什么
===

这是一个私人定制的cocos2dx版本, 基于cocos2dx v2分支的最新代码, 目标是创造一个cocos2dx的古典经典版. cocos2dx目前已经全面发力于3.x版本, 2.x版本已经被抛弃, 当然, 如果他们不抛弃2.x, 我也不会创建这个项目.

我觉得2.x仍然还有价值, 同时3.x并不让我感到多大兴趣. 实际上cocos2d作为一个2d引擎, 还有很多不完善的地方, 相信无数的人已经在2.x时代踩过了很多的坑, 也不得不自己去填上这些坑, 我也一样, 为了填这些坑, 我创建了cocos2dx-better项目, 把这些坑通过外挂的方式填掉, 但是总有一些坑, 外挂解决不了, 只能改原始代码. 对于我个人而言, 目前更需要一个好用的2.x, 而不是一个有未知新坑的3.x.

另外, 我日常使用mac, 主要做iOS和Android开发, 所以其它的平台我都会删掉. 

所以, 如果你正好也是一个Mac/iOS/Android开发者, 也正好还在使用cocos2dx 2.x, 不妨可以看几眼.

What is this
===

It is a customized cocos2dx, based on latest code of cocos2dx v2 branch. The purpose of it is creating a classical cocos2dx version. I created it because cocos2dx already gave up v2 but v2 is still valuable to me. v3 doesn't interest me much because it may have more bugs. So I need a better v2, not a creepy v3.

To get a bette v2, I created a cocos2dx-better project to overcome limitations of v2. Now I start this project to merge cocos2dx-better code to v2 branch, and more.

I only care iOS/Android platform, so other platform code will be deleted. Are you same with me? If so, take a look at this project.

目标
===
1. 基于cocos2dx 2.x最新代码 **(已完成)**
2. 将我个人的cocos2dx-better代码融入 **(已完成)**
3. 把quick-cocos2dx那一套lua支持拷贝过来改吧改吧 **(已完成)**
	* quick 3.x的binding generator工具已经被我移植了过来, 名字叫autolua, 引擎的绑定已经全部生成, HelloLua工程已经调试通过, 尚需更多实践检验
4. 专注于填坑改bug, 而非大刀阔斧的修改架构 **(随时进行中)**

Purpose
===

1. base on cocos2dx v2 **(Done)**
2. merge my cocos2dx-better **(Done)**
3. provide fully lua support, in quick-cocos2dx 3.x way **(Done)**
	* quick 3.x binding generator is migrated as autolua, and all lua binding for cocos2dx-classical is generated. HelloLua sample is tested and result is fine. Sure it needs more testing but basically it works.
4. fix v2 bugs **(Always in progress)**	

何时结束
===
等有一天我也开始使用3.x的时候, 这个项目就结束了, 即使到了那一天, 我也希望这个项目留下了一个好用的2.x. 就像名字希望的一样, 这会成为cocos2dx的古典经典版.

Everything that has a beginning has an end
===

At the day when I switch to v3, this project will be stopped. But, I hope its corpse is still valuable to somebody because it is better than v2 corpse.

这些年, 已经填过的坑
===

* 修正工程的64位编译设置
* 使用c++11编译所有代码
* 重新实现CCLabelTTF(来自cocos2dx-better的CCRichLabelTTF):
	* 完全兼容CCLabelTTF的原有功能
	* 支持字符串中嵌入格式控制, 包括颜色, 字体, 大小, 样式, 图片, 链接等 
* CocoStudio的调整
	* 去掉了CocoStudio类的UI前缀兼容设置, 去掉了一些文件的UI前缀
	* 修正对CocoStudio Mac 1.0.0.0 beta的支持问题, 具体修改为:
		* UILabel构造函数中_fontSize缺省改为20, 因为mac版cocostudio默认字体大小为20, 当为20时, 不会序列化到json中
		* 对类名称"Node"的节点, 一律创建Layout
		* WidgetPropertiesReader0300::createWidget中, 检查文件版本, 如果为1.0.0.0, 认为其为mac版
		* WidgetPropertiesReader0300::widgetFromJsonDictionary中添加page item的代码注释掉, 因为PageView重新实现后采用动态方式创建page item
		* Layout的缺省背景色类型改成NONE
		* UIPageView重新实现:
			* 支持动态创建页, 解决了page比较多时的性能问题
			* 使用了cocos2dx-better的VelocityTracker跟踪滑动速度, 解决了页间滑动很别扭的问题
			* 注: 不再支持从CocoStudio中直接添加page item, 必须使用PageViewDataSource接口
	* 修正UILabelBMFont::setFntFile方法中的内存泄露
	* ListView的pushBackDefaultItem返回新item
	* 修正CCArmature有时候帧事件触发两次的问题
	* 由于CocoStudio Mac 1.0.0.0 beta没有骨骼动画功能, 需要使用骨骼动画时, 可以使用CocoStudio Windows版1.4.0.1, 1.4.0.1以上版本我没有测试过.
* 重新实现TMX地图, 支持一个层有多张贴图的情况(来自cocos2dx-better的CBTMXTileMap)
* 重新实现CCTableView(来自cocos2dx-better中的CCGridView代码):
	* CCTableView支持多列
	* 支持cell重用, cell可以设置名称
	* 支持不等宽度的行或列
* CCProtocols.h增加CCMeasurableProtocol, 让LoadingBar, CCProgressTimer实现CCMeasurableProtocol. 从而让CCProgressTo, CCProgressFromTo支持UILoadingBar
* CCLabelBMFont添加了setLineKerning, 用于调整行间距
* CCScrollView添加方法可以设置min/max scale
* 重新实现CCLayerMultiplex以避免某些情况下发生的内存泄露
* CCLayer增加is/setSwallowTouch, 从而可以控制CCScrollView是否吞掉touch
* CCSpriteBatchNode的insertQuadFromSprite, updateQuadFromSprite, addSpriteWithoutQuad改为public
* CCScrollView增加getTouchPoint方法获得最后一次点击位置
* CCRepeatForever覆盖stop方法, 停掉内部动作
* copy()返回的对象不再需要release
* setShaderProgram可以设置参数, 从而支持多个节点使用同一个shader但参数不同

cocos2dx-better新加的其它功能我就不列举了, 目前cocos2dx-better的代码已经合并完成, 有一部分代码我感觉写的用处不大就没有合并了, 不过只是一小部分, 95%的cocos2dx-better代码已经合并.

Things Improved
===

* fixed project 64bits compiling
* reimplement CCLabelTTF (merge code from cocos2dx-better CCRichLabelTTF)
	* fully compatibile with old CCLabelTTF
	* support attibuted style, such as color, font, size, style, image, link
* polish CocoStudio
	* remove UI prefix
	* fix json parsing bug for CocoStudio Mac 1.0.0.0 beta, how to do:
		* set Label default _fontSize to 20 because CocoStudio Mac use 20 by default
		* create Layout for node whose name is "Node"
		* check version in WidgetPropertiesReader0300::createWidget to detect CocoStudio Mac json
		* because PageView is reimplemented, comment out page item code in WidgetPropertiesReader0300::widgetFromJsonDictionary
		* set Layout default background color style to NONE
		* reimplement PageView
			* use data source to create page item dynamically, and reuseable
			* use VelocityTracker (from cocos2dx-better) to improve page slide experience
			* Note: don't support add page item in CocoStudio
	* fix memory leak in UILabelBMFont::setFntFile
	* return created item in Listview::pushBackDefaultItem
	* fix bug: CCArmature frame event may be triggered more than once
	* Note: if you want to use skeleton animation, please still use CocoStudio Windows version, 1.4.0.1 is recommended.
* reimplement TMX, support multi-tileset for one layer(merge from cocos2dx-better CBTMXTileMap)
* reimplement CCTableView(merge from cocos2dx-better CCGridView):
	* support multi-column
	* support cell reuse, cell can set name
	* column or row can be different size
* add CCMeasurableProtocol class to abstract LoadingBar and CCProgressTimer, so that CProgressTo, CCProgressFromTo can be used on LoadingBar
* CCLabelBMFont adds setLineKerning to adjust line spacing
* CCScrollView add methods to set min/max scale
* reimplement CCLayerMultiplex to avoid memory leak
* CCLayer adds is/setSwallowTouch to control swallowing touch or not
* CCSpriteBatchNode insertQuadFromSprite, updateQuadFromSprite, addSpriteWithoutQuad are changed to public
* CCScrollView adds getTouchPoint to get last touch position
* CCRepeatForever override stop method
* setShaderProgram can specify uniform values so that one shader can be shared by many nodes

How to use CCImagePicker
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