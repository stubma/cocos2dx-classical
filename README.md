这是什么
===

这是一个私人定制的cocos2dx版本, 基于cocos2dx v2分支的最新代码, 目标是创造一个cocos2dx的古典经典版. cocos2dx目前已经全面发力于3.x版本, 2.x版本已经被抛弃, 当然, 如果他们不抛弃2.x, 我也不会创建这个项目.

我觉得2.x仍然还有价值, 同时3.x并不让我感到多大兴趣. 实际上cocos2d作为一个2d引擎, 还有很多不完善的地方, 相信无数的人已经在2.x时代踩过了很多的坑, 也不得不自己去填上这些坑, 我也一样, 为了填这些坑, 我创建了cocos2dx-better项目, 把这些坑通过外挂的方式填掉, 但是总有一些坑, 外挂解决不了, 只能改原始代码. 对于我个人而言, 目前更需要一个好用的2.x, 而不是一个有未知新坑的3.x.

另外, 我日常使用mac, 主要做iOS和Android开发, 所以其它的平台我都会删掉, 也许mac会留着, Windows Phone嘛, 后面再说. 

所以, 如果你正好也是一个Mac/iOS/Android开发者, 也正好还在使用cocos2dx 2.x, 不妨可以看几眼.

目标
===
1. 基于cocos2dx 2.x最新代码
2. 将我个人的cocos2dx-better代码融入
3. 提供类似于quick-cocos2dx那样的lua支持, 可借鉴之, 可超越之
4. 专注于填坑改bug, 而非大刀阔斧的修改架构. 兼容性是肯定要保持的.

何时结束
===
等有一天我也开始使用3.x的时候, 这个项目就结束了, 即使到了那一天, 我也希望这个项目留下了一个好用的2.x. 就像名字希望的一样, 这会成为cocos2dx的古典经典版.


这些年, 已经填过的坑
===
* 修正对CocoStudio Mac 1.0.0.0 beta的支持问题, 但是由于Mac下的CocoStudio 1.0.0.0 beta没有动画编辑功能, 需要使用骨骼动画的还是需要使用Windows版本编辑. 但是至少在Mac下终于有一个可用的界面编辑器了, 之前的cocos2d-x v2版本存在若干解析问题, 导致虽然有Mac版却无法用.
* 修正UILabel的内存泄露
* UIPageView重新实现, 使用datasource动态创建内容, 解决了page比较多时的性能问题. 注: 不再支持从CocoStudio中添加page
* CCTableView重新实现, 支持多列
* CCProgressTo, CCProgressFromTo支持UILoadingBar
* CCLabelBMFont添加了setLineKerning, 可以调整行间距
* CCScrollView添加方法可以设置min/max scale
* 持续更新中...

已陆续合并若干cocos2dx-better代码, 新类不一一列举.