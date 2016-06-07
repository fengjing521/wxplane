#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

const int MAX_SCORE = 1000000000;
class ControlLayer:public Layer
{
public:
	ControlLayer();
	~ControlLayer();
	virtual bool init();
	CREATE_FUNC(ControlLayer);
	void menuPauseCallback(CCObject* pSender);

	void updateScore(int score);

public:

	CCLabelBMFont* scoreItem;

	/*CCMenuItemImage* pPauseItem;*/

	MenuItemSprite* pPauseItem;

	/*NoTouchLayer* noTouchLayer;*/
};

