#include "Button.h"

NS_CCR_BEGIN



CreatorButton* CreatorButton::create()
{
	CreatorButton* widget = new (std::nothrow) CreatorButton();
	if (widget && widget->init())
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}


CreatorButton* CreatorButton::create(const std::string &normalImage,
	const std::string& selectedImage,
	const std::string& disableImage,
	TextureResType texType)
{
	CreatorButton *btn = new (std::nothrow) CreatorButton;
	if (btn && btn->init(normalImage, selectedImage, disableImage, texType))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}



CreatorButton::CreatorButton()
{
	_actionDuration = 0.1;
	_transitionType = TransitionType::NONE;
	_enableAutoGrayEffect = false;
	_orignScale = 1.0;

}

CreatorButton::~CreatorButton()
{
}


void CreatorButton::onPressStateChangedToNormal()
{
	_buttonNormalRenderer->setVisible(true);
	_buttonClickedRenderer->setVisible(false);
	_buttonDisabledRenderer->setVisible(false);
	_buttonNormalRenderer->setState(ui::Scale9Sprite::State::NORMAL);

	if (_pressedTextureLoaded)
	{
		if (_transitionType == TransitionType::COLOR)
		{
			//this->stopAllActions();
			//this->setColor(Color3B(_normalColor.r, _normalColor.b, _normalColor.g));
			//this->setOpacity(_normalColor.a);


			this->stopAllActions();
			auto action = TintTo::create(_actionDuration, Color3B(_normalColor.r, _normalColor.b, _normalColor.g));
			auto fadeAction = FadeTo::create(_actionDuration, _normalColor.a);
			auto spwan = Spawn::create(action, fadeAction, nullptr);

			this->runAction(EaseSineOut::create(spwan));

		}
		else if (_pressedActionEnabled)
		{
			
			float orignScale = this->getOrignScale();
			//float childScale = (orignScale == -1.0f ? this->getScale() : orignScale);
			//this->setScale(childScale);
			//this->setOrignScale(-1);

			this->stopAllActions();
			this->runAction(EaseSineOut::create(ScaleTo::create(_actionDuration, orignScale, orignScale)));
		}


	}
	else
	{
		_buttonNormalRenderer->stopAllActions();
		_buttonNormalRenderer->setScale(1.0);

		if (nullptr != _titleRenderer)
		{
			_titleRenderer->stopAllActions();
			_titleRenderer->setScaleX(1.0f);
			_titleRenderer->setScaleY(1.0f);
		}

	}
}

void CreatorButton::onPressStateChangedToPressed()
{
	_buttonNormalRenderer->setState(ui::Scale9Sprite::State::NORMAL);

	if (_pressedTextureLoaded)
	{
		_buttonNormalRenderer->setVisible(false);
		_buttonClickedRenderer->setVisible(true);
		_buttonDisabledRenderer->setVisible(false);


		if (_transitionType == TransitionType::COLOR)
		{
			this->stopAllActions();


			auto action = TintTo::create(_actionDuration, Color3B(_pressedColor.r, _pressedColor.b, _pressedColor.g));
			auto fadeAction = FadeTo::create(_actionDuration, _pressedColor.a);
			auto spwan = Spawn::create(action, fadeAction, nullptr);

			this->runAction(EaseSineOut::create(spwan));
			//this->setColor(Color3B(_normalColor.r, _normalColor.b, _normalColor.g));
			//this->setOpacity(_normalColor.a);
		}
		else if (_pressedActionEnabled)
		{


			this->stopAllActions();
			float orignScale = this->getOrignScale();
			//float childScale = (orignScale == -1.0f ? this->getScale() : orignScale);
			//this->setOrignScale(childScale);

			ScaleTo *zoomChildAction = ScaleTo::create(_actionDuration,
				orignScale * (1.0f + _zoomScale),
				orignScale * (1.0f + _zoomScale));

			this->runAction(EaseSineOut::create(zoomChildAction));

		}
	}
	else
	{
		_buttonNormalRenderer->setVisible(true);
		_buttonClickedRenderer->setVisible(true);
		_buttonDisabledRenderer->setVisible(false);

		_buttonNormalRenderer->stopAllActions();
		_buttonNormalRenderer->setScale(1.0f + _zoomScale, 1.0f + _zoomScale);

		if (nullptr != _titleRenderer)
		{
			_titleRenderer->stopAllActions();
			_titleRenderer->setScaleX(1.0f + _zoomScale);
			_titleRenderer->setScaleY(1.0f + _zoomScale);
		}
	}
}

void CreatorButton::onPressStateChangedToDisabled()
{
	//if disable resource is null
	if (!_disabledTextureLoaded)
	{
		if (_normalTextureLoaded)
		{
			_buttonNormalRenderer->setState(ui::Scale9Sprite::State::GRAY);
		}
	}
	else
	{
		_buttonNormalRenderer->setVisible(false);
		_buttonDisabledRenderer->setVisible(true);
	}

	if (_transitionType == TransitionType::COLOR)
	{
		this->stopAllActions();


		auto action = TintTo::create(_actionDuration, Color3B(_disableColor.r, _disableColor.b, _disableColor.g));
		auto fadeAction = FadeTo::create(_actionDuration, _disableColor.a);
		auto spwan = Spawn::create(action, fadeAction, nullptr);

		this->runAction(EaseSineOut::create(spwan));
		//this->setColor(Color3B(_normalColor.r, _normalColor.b, _normalColor.g));
		//this->setOpacity(_normalColor.a);
	}

	_buttonClickedRenderer->setVisible(false);
	_buttonNormalRenderer->setScale(1.0);
	_buttonClickedRenderer->setScale(1.0);
}


void CreatorButton::setTransitionType(CreatorButton::TransitionType transitionType)
{
	_transitionType = transitionType;
	if (_transitionType == TransitionType::COLOR)
	{
		this->setCascadeColorEnabled(true);
		this->setCascadeOpacityEnabled(true);
	}
}

CreatorButton::TransitionType CreatorButton::getTransitionType()
{
	return _transitionType;
}


void CreatorButton::setNormalColor(Color4B& color)
{
	_normalColor = color;
}

Color4B CreatorButton::getNormalColor()const
{
	return _normalColor;
}

void CreatorButton::setPressedColor(Color4B& color)
{
	_pressedColor = color;
}

Color4B CreatorButton::getPressedColor()const
{
	return _pressedColor;
}

void CreatorButton::setDisableColor(Color4B& color)
{
	_disableColor = color;
}

Color4B CreatorButton::getDisableColor()const
{
	return _disableColor;
}




NS_CCR_END