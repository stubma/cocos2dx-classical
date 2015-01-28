require("script/cocos/Cocos2d")

cc = cc or {}

-- color constants
cc.cc4RED = { 255, 0, 0, 255 }
cc.cc4GREEN = { 0, 255, 0, 255 }
cc.cc4BLUE = { 0, 0, 255, 255 }
cc.cc4BLACK = { 0, 0, 0, 255 }
cc.cc4WHITE = { 255, 255, 255, 255 }
cc.cc4TRANSPARENT = { 0, 0, 0, 0 }
cc.cc4DIM = { 0, 0, 0, 127 }
cc.cc4YELLOW = { 255, 255, 0, 255 }
cc.cc4fRED = { 1, 0, 0, 1 }
cc.cc4fGREEN = { 0, 1, 0, 1 }
cc.cc4fBLUE = { 0, 0, 1, 1 }
cc.cc4fBLACK = { 0, 0, 0, 1 }
cc.cc4fWHITE = { 1, 1, 1, 1 }
cc.cc4fTRANSPARENT = { 0, 0, 0, 0 }
cc.cc4fDIM = { 0, 0, 0, 0.5 }
cc.cc4fYELLOW = { 1, 1, 0, 1 }

-- platform constants
cc.PLATFORM_UNKNOWN            = 0
cc.PLATFORM_IOS                = 1
cc.PLATFORM_ANDROID            = 2
cc.PLATFORM_WIN32              = 3
cc.PLATFORM_MARMALADE          = 4
cc.PLATFORM_LINUX              = 5
cc.PLATFORM_BADA               = 6
cc.PLATFORM_BLACKBERRY         = 7
cc.PLATFORM_MAC                = 8
cc.PLATFORM_NACL               = 9
cc.PLATFORM_EMSCRIPTEN        = 10
cc.PLATFORM_TIZEN             = 11
cc.PLATFORM_WINRT             = 12
cc.PLATFORM_WP8               = 13

-- node event type
cc.NodeOnEnter = "enter"
cc.NodeOnExit = "exit"
cc.NodeOnEnterTransitionDidFinish = "enterTransitionFinish"
cc.NodeOnExitTransitionDidStart = "exitTransitionStart"
cc.NodeOnCleanup = "cleanup"

-- touch event type
cc.TOUCH_EVENT_BEGAN = "began"
cc.TOUCH_EVENT_MOVED = "moved"
cc.TOUCH_EVENT_ENDED = "ended"
cc.TOUCH_EVENT_CANCELED = "canceled"

-- touch mode
cc.TouchesAllAtOnce = 0
cc.TouchesOneByOne = 1

-- keypad event type
cc.KeyEventMenu = "menu"
cc.KeyEventBack = "back"

-- control event type
cc.ControlEventTouchDown = 0x1
cc.ControlEventTouchDragInside = 0x2
cc.ControlEventTouchDragOutside = 0x4
cc.ControlEventTouchDragEnter = 0x8
cc.ControlEventTouchDragExit = 0x10
cc.ControlEventTouchUpInside = 0x20
cc.ControlEventTouchUpOutside = 0x40
cc.ControlEventTouchCancel = 0x80
cc.ControlEventValueChanged = 0x100

-- control state
cc.ControlStateNormal = 0x1
cc.ControlStateHighlighted  = 0x2
cc.ControlStateDisabled = 0x4
cc.ControlStateSelected = 0x8

-- editbox event type
cc.EditBoxTextChanged = "changed"
cc.EditBoxEditingDidBegin = "began"
cc.EditBoxEditingDidEnd = "ended"
cc.EditBoxReturn = "return"

-- editbox return key type
cc.KeyboardReturnTypeDefault = 0
cc.KeyboardReturnTypeDone = 1
cc.KeyboardReturnTypeSend = 2
cc.KeyboardReturnTypeSearch = 3
cc.KeyboardReturnTypeGo = 4

-- edit box input type
cc.EditBoxInputFlagPassword = 0
cc.EditBoxInputFlagSensitive = 1
cc.EditBoxInputFlagInitialCapsWord = 2
cc.EditBoxInputFlagInitialCapsSentence = 3
cc.EditBoxInputFlagInitialCapsAllCharacters = 4

-- resource loader event
cc.ResourceLoaderProgress = "progress"
cc.ResourceLoaderDone = "done"

-- point constants
cc.CENTER = cc.p(0.5, 0.5)
cc.RIGHT_TOP = cc.p(1, 1)
cc.RIGHT_BOTTOM = cc.p(1, 0)
cc.LEFT_BOTTOM = cc.p(0, 0)
cc.LEFT_TOP = cc.p(0, 1)
cc.RIGHT_MIDDLE = cc.p(1, 0.5)
cc.LEFT_MIDDLE = cc.p(0, 0.5)
cc.BOTTOM_MIDDLE = cc.p(0.5, 0)
cc.TOP_MIDDLE = cc.p(0.5, 1)
cc.NORTH = cc.TOP_MIDDLE
cc.SOUTH = cc.BOTTOM_MIDDLE
cc.EAST = cc.RIGHT_MIDDLE
cc.WEST = cc.LEFT_MIDDLE
cc.NORTH_EAST = cc.RIGHT_TOP
cc.NORTH_WEST = cc.LEFT_TOP
cc.SOUTH_EAST = cc.RIGHT_BOTTOM
cc.SOUTH_WEST = cc.LEFT_BOTTOM

-- geometry constant
cc.RectZero = cc.rect(0, 0, 0, 0)
cc.SizeZero = cc.size(0, 0)
cc.PointZero = cc.p(0, 0)

-- progress bar type
cc.ProgressTimerTypeRadial = 0
cc.ProgressTimerTypeBar = 1

-- repeat type
cc.RepeatForever = -1

-- label alignment
cc.VerticalTextAlignmentTop = 0
cc.VerticalTextAlignmentCenter = 1
cc.VerticalTextAlignmentBottom = 2
cc.TextAlignmentLeft = 0
cc.TextAlignmentCenter = 1
cc.TextAlignmentRight = 2

-- scrolview scrolling type
cc.ScrollViewDirectionNone = -1
cc.ScrollViewDirectionHorizontal = 0
cc.ScrollViewDirectionVertical = 1
cc.ScrollViewDirectionBoth = 2