#pragma once
#include "cocos2d.h"
USING_NS_CC;
class WelcomeLayer:public Layer
{
public:
	WelcomeLayer();
	~WelcomeLayer();
	virtual bool init();

	CREATE_FUNC(WelcomeLayer);

	void loadingDone(CCNode* pNode);

	//virtual void keyBackClicked();//Android���ؼ�

	bool isHaveSaveFile();

	void getHighestHistorySorce();
};

