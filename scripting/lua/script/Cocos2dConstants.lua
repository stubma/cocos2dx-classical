cc = cc or {}

-- touch event type
cc.TOUCH_EVENT_BEGAN = 0x0
cc.TOUCH_EVENT_MOVED = 0x1
cc.TOUCH_EVENT_ENDED = 0x2
cc.TOUCH_EVENT_CANCELED = 0x3

-- control event type
cc.ControlEventTouchDown = 0x1;
cc.ControlEventTouchDragInside = 0x2;
cc.ControlEventTouchDragOutside = 0x4;
cc.ControlEventTouchDragEnter = 0x8;
cc.ControlEventTouchDragExit = 0x10;
cc.ControlEventTouchUpInside = 0x20;
cc.ControlEventTouchUpOutside = 0x40;
cc.ControlEventTouchCancel = 0x80;
cc.ControlEventValueChanged = 0x100;