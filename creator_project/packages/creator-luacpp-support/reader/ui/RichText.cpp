#include "RichText.h"

NS_CCR_BEGIN

CreatorRichText* CreatorRichText::create()
{
	CreatorRichText* widget = new (std::nothrow) CreatorRichText();
	if (widget && widget->init())
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}

CreatorRichText::CreatorRichText()
{

}

CreatorRichText::~CreatorRichText()
{
}


ui::RichElement *CreatorRichText::getElement(int index)
{
	return _richElements.at(index);
}


void CreatorRichText::setElementText(int index, std::string sContent)
{
	auto pElement = getElement(index);
	if (pElement)
	{
		auto pElementText = dynamic_cast<ui::RichElementText*>(pElement);
		if (pElementText)
		{
			pElementText->setText(sContent);
			_formatTextDirty = true;
		}

	}
}




NS_CCR_END