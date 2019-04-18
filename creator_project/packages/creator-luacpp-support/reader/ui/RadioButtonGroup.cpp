#include "RadioButtonGroup.h"

NS_CCR_BEGIN



CreatorRadioButtonGroup* CreatorRadioButtonGroup::create()
{
	CreatorRadioButtonGroup* widget = new (std::nothrow) CreatorRadioButtonGroup();
	if (widget && widget->init())
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}


CreatorRadioButtonGroup::CreatorRadioButtonGroup()
{


}

CreatorRadioButtonGroup::~CreatorRadioButtonGroup()
{
}


NS_CCR_END