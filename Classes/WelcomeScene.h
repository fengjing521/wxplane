#pragma once
#include "cocos2d.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
class WelcomeScene:public Scene
{
public:
	WelcomeScene();
	~WelcomeScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
	void PreloadMusic();
	WelcomeLayer* _welcomeLayer;
};

