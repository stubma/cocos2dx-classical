
#ifndef __COMPATIBLECLASSES_H__
#define __COMPATIBLECLASSES_H__

#include "cocos2d.h"
#include "../../BaseClasses/UIWidget.h"
#include "../Button.h"
#include "../UICheckBox.h"
#include "../ImageView.h"
#include "../Label.h"
#include "../LabelAtlas.h"
#include "../LabelBMFont.h"
#include "../UILoadingBar.h"
#include "../Slider.h"
#include "../TextField.h"
#include "../../Layouts/UILayout.h"
#include "../ScrollWidget/ListView.h"
#include "../ScrollWidget/PageView.h"
#include "../ScrollWidget/ScrollView.h"

//class type define
NS_CC_BEGIN
//
namespace ui {
  
typedef cocos2d::ui::Layout UILayout;
typedef cocos2d::ui::Widget UIWidget;

typedef cocos2d::ui::LayoutParameter UILayoutParameter;
typedef cocos2d::ui::Margin UIMargin;

typedef cocos2d::ui::Button UITextButton;
typedef cocos2d::ui::CheckBox UICheckBox;
typedef cocos2d::ui::LoadingBar UILoadingBar;

typedef cocos2d::ui::LinearGravity UILinearGravity;
typedef cocos2d::ui::RelativeAlign UIRelativeAlign;
typedef cocos2d::ui::LayoutParameter UILayoutParameter;
typedef cocos2d::ui::LinearLayoutParameter UILinearLayoutParameter;
typedef cocos2d::ui::RelativeLayoutParameter UIRelativeLayoutParameter;
}
NS_CC_END


#endif /* defined(__CompatibleClasses__) */
