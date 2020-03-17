/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#pragma once


#include <vector>
#include <tuple>

#include "Macros.h"
#include "AnimationClip.h"

NS_CCR_BEGIN

class AnimateClip;

class AnimationInfo : public cocos2d::Ref
{
public:
	bool haveAnimation() { return clips.size() > 0; };
	std::string nodeName;
	AnimationInfo();
	~AnimationInfo();
private:
	friend class CreatorReader;
	friend class AnimationComponent;
	AnimationClip* defaultClip;
	cocos2d::Vector<AnimationClip*> clips;
	bool playOnLoad;
};

class AnimationComponent : public cocos2d::Component
{
public:

	AnimationComponent();

	~AnimationComponent();
	typedef std::function<void()> AnimationCallback;

    void playAnimationClip(const std::string &animationClipName, AnimationCallback cb= nullptr, int modeType = -1);
    // if AnimationClip is stopped, can not run it again.
    void stopAnimationClip(const std::string &animationClipName);
    void pauseAnimationClip(const std::string &animationClipName);
    void resumeAnimationClip(const std::string &animationClipName);
    // if a "Play On Load" animation is a loop animation, please stop it manually.
    void stopAnimationClipsRunByPlayOnLoad();
	void stopAllAnimationClips();

	AnimateClip * getCurrentAnimation() const;

	virtual void onEnter();
	virtual void onExit();
	virtual void onAdd();
	virtual void onRemove();

	virtual void update(float delta);

private:
    friend class CreatorReader;
    
    // functions invoked by CreatorReader only
	void addAnimation(AnimationClip* animationClip);
	void addAnimation(AnimationInfo * aInfo);
    void playOnLoad();

	AnimationClip* _defaultClip;

	AnimateClip *_runningClip;

	bool _playOnLoad;

    void runAnimationClip(AnimationClip* animationClip, AnimationCallback cb);
    // AnimateClip will be released
    void removeAnimateClip(const std::string &animationClipName);
	AnimateClip* getAnimateClip(const std::string &animationClipName);

	cocos2d::Vector<AnimationClip *> _animations;
	cocos2d::Vector<AnimateClip *> _runningAnimations;

};

NS_CC_END
