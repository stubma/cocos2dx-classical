这是什么
===

这是一个私人定制的cocos2dx版本, 基于cocos2dx v2分支的最新代码, 目标是创造一个cocos2dx的古典经典版. cocos2dx目前已经全面发力于3.x版本, 2.x版本已经被抛弃, 当然, 如果他们不抛弃2.x, 我也不会创建这个项目.

我觉得2.x仍然还有价值, 同时3.x并不让我感到多大兴趣. 实际上cocos2d作为一个2d引擎, 还有很多不完善的地方, 相信无数的人已经在2.x时代踩过了很多的坑, 也不得不自己去填上这些坑, 我也一样, 为了填这些坑, 我创建了cocos2dx-better项目, 把这些坑通过外挂的方式填掉, 但是总有一些坑, 外挂解决不了, 只能改原始代码. 对于我个人而言, 目前更需要一个好用的2.x, 而不是一个有未知新坑的3.x.

另外, 我日常使用mac, 主要做iOS和Android开发, 所以其它的平台我都会删掉, 其它的平台嘛, 后面再说. 

所以, 如果你正好也是一个Mac/iOS/Android开发者, 也正好还在使用cocos2dx 2.x, 不妨可以看几眼.

目标
===
1. 基于cocos2dx 2.x最新代码
2. 将我个人的cocos2dx-better代码融入
3. 把quick-cocos2dx那一套lua支持拷贝过来改吧改吧
4. 专注于填坑改bug, 而非大刀阔斧的修改架构

注意, 由于这是私人定制版, 我会加东西, 也会删东西, 主要删得都是一些我用不上的玩意, 主要都是extension里面的, 基本上我就留下了CocoStudio和GUI, 其它的我都咔嚓掉了, 有的我在cocos2dx-better里也实现过一份.


何时结束
===
等有一天我也开始使用3.x的时候, 这个项目就结束了, 即使到了那一天, 我也希望这个项目留下了一个好用的2.x. 就像名字希望的一样, 这会成为cocos2dx的古典经典版.

这些年, 已经填过的坑
===

* 修正工程的64位编译设置
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
	* 由于CocoStudio Mac 1.0.0.0 beta没有骨骼动画功能, 需要使用骨骼动画时, 可以使用CocoStudio Windows版1.4.0.1, 1.4.0.1以上版本我没有测试过.
* 重新实现TMX地图, 支持一个层有多张贴图的情况
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

cocos2dx-better的代码已经合并完成, 有一部分代码我感觉写的用处不大就没有合并了, 不过只是一小部分, 95%的cocos2dx-better代码已经合并.

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