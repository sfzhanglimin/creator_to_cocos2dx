
#include "AnimationComponent.h"
#include "AnimateClip.h"

NS_CCR_BEGIN

AnimationInfo::AnimationInfo():playOnLoad(false)
{
}

AnimationInfo::~AnimationInfo()
{
}


///================================================


AnimationComponent::AnimationComponent() :
	_playOnLoad(false)
	,_defaultClip(nullptr), _runningClip(nullptr)
{
	this->setName("AnimationComponent");
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::onRemove()
{
	Component::onRemove();
	//stopAllAnimationClips();
}

void AnimationComponent::addAnimation(AnimationClip* animationInfo)
{
	if (animationInfo)
	{
		_animations.pushBack(animationInfo);
	}
}

void AnimationComponent::addAnimation(AnimationInfo* aInfo)
{
	if (aInfo != nullptr)
	{
		for (auto it = aInfo->clips.begin(), end = aInfo->clips.end(); it != end; ++it)
		{
			addAnimation((*it));
		}

		_playOnLoad = aInfo->playOnLoad;
		_defaultClip = aInfo->defaultClip;
	}
}



void AnimationComponent::playOnLoad()
{
	if (_playOnLoad && _defaultClip)
	{
		runAnimationClip(_defaultClip,nullptr);
	}
}

void AnimationComponent::stopAnimationClipsRunByPlayOnLoad()
{
	if (_playOnLoad && _defaultClip)
		stopAnimationClip(_defaultClip->getName());
}

void AnimationComponent::stopAllAnimationClips()
{
	if (!_runningAnimations.empty())
	{
		for (auto iter = _runningAnimations.begin(), end = _runningAnimations.end(); iter != end; ++iter)
		{
			auto&& e = *iter;
			// release AnimateClip
			e->stopAnimate();
		}

		_runningAnimations.clear();
	}
	
	CC_SAFE_RELEASE_NULL(_runningClip);
}


void AnimationComponent::playAnimationClip(const std::string &animationClipName, AnimationCallback cb, int modeType)
{
    bool foundAnimationClip = false;
    
    for (auto& animationClip : _animations)
    {
		if (animationClip->getName() == animationClipName)
		{
			if (modeType != -1)
			{
				animationClip->setWrapMode((AnimationClip::WrapMode)modeType);
			}
			runAnimationClip(animationClip, cb);
			foundAnimationClip = true;
			break;
		}       
    }
   
        if (!foundAnimationClip)
            CCLOG("can not found animation clip name %s", animationClipName.c_str());
}

void AnimationComponent::stopAnimationClip(const std::string &animationClipName)
{
    auto animateClip = getAnimateClip(animationClipName);
    if (animateClip)
    {
        animateClip->stopAnimate();
        removeAnimateClip(animationClipName);
    }
}

void AnimationComponent::pauseAnimationClip(const std::string &animationClipName)
{
    auto animateClip = getAnimateClip(animationClipName);
    if (animateClip)
        animateClip->pauseAnimate();
}

void AnimationComponent::resumeAnimationClip(const std::string &animationClipName)
{
    auto animateClip = getAnimateClip(animationClipName);
    if (animateClip)
        animateClip->resumeAnimate();
}

void AnimationComponent::runAnimationClip(AnimationClip* animationClip,AnimationCallback cb)
{
    auto animate = AnimateClip::createWithAnimationClip(_owner, animationClip);
    animate->setCallbackForEndevent([=]() {
		animate;
		if (cb){
			cb();
		}
    });

    animate->startAnimate();

	CC_SAFE_RELEASE_NULL(_runningClip);

	_runningClip = animate;
	CC_SAFE_RETAIN(_runningClip);

	_runningAnimations.pushBack(animate);
}

AnimateClip* AnimationComponent::getCurrentAnimation() const
{
	return _runningClip;
}

void AnimationComponent::removeAnimateClip(const std::string &animationClipName)
{
	if (_runningClip && _runningClip->getAnimationClip()->getName() == animationClipName)
	{
		_runningClip->stopAnimate();
		CC_SAFE_RELEASE_NULL(_runningClip);
	}

	for (auto iter = _animations.begin(), end = _animations.end(); iter != end; ++iter)
	{
		auto&& e = *iter;
		if (e->getName() == animationClipName)
		{
			// release AnimateClip
			_animations.erase(iter);
			break;
		}
	}
}

AnimateClip* AnimationComponent::getAnimateClip(const std::string &animationClipName)
{
    for (auto& e : _runningAnimations)
    {
        if (e->getAnimationClip()->getName() == animationClipName)
            return e;
    }
    
    return nullptr;
}

void AnimationComponent::onEnter(){
	Component::onEnter();
	this->playOnLoad();
}

void AnimationComponent::onAdd() {
	Component::onAdd();
	this->getOwner()->scheduleUpdate();
}

void AnimationComponent::update(float delta)
{
	if (!_runningAnimations.empty())
	{
		for (auto it = _runningAnimations.begin(), end = _runningAnimations.end(); it != end; ++it)
		{
			(*it)->update(delta);
		}
	}
}

void AnimationComponent::onExit()
{
	Component::onExit();
	stopAllAnimationClips();
}

NS_CCR_END
