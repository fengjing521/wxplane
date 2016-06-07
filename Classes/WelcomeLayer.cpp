#include "WelcomeLayer.h"
#include "GameScene.h"
#include "GameOverScene.h"
WelcomeLayer::WelcomeLayer()
{
}


WelcomeLayer::~WelcomeLayer()
{
}
bool WelcomeLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		//png加入全局cache中
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");

		Size winSize = Director::sharedDirector()->getWinSize();

		//加入background
		Sprite* background =Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		this->addChild(background);

		//加入copyright
		auto copyright = Sprite::createWithSpriteFrameName("shoot_copyright.png");
		copyright->setAnchorPoint(Vec2(0.5, 0));
		copyright->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		this->addChild(copyright);

		//加入loading
		auto loading = Sprite::createWithSpriteFrameName("game_loading1.png");
		loading->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 40));
		this->addChild(loading);

		Animation* animation = CCAnimation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
		animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
		animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
		animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));

		Animate* animate = Animate::create(animation);
		Repeat* repeat = Repeat::create(animate, 2);
		CCCallFuncN* repeatdone = CCCallFuncN::create(this, callfuncN_selector(WelcomeLayer::loadingDone));
		Sequence* sequence = Sequence::create(repeat, repeatdone, NULL);
		loading->runAction(sequence);

		getHighestHistorySorce();

		this->setKeypadEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void WelcomeLayer::loadingDone(CCNode* pNode)
{
	Scene* pScene = GameScene::create();
	TransitionMoveInB *animateScene = TransitionMoveInB::create(0.5f, pScene);
	Director::sharedDirector()->replaceScene(animateScene);
}

//void WelcomeLayer::keyBackClicked()
//{
//	CCDirector::sharedDirector()->end();
//}

bool WelcomeLayer::isHaveSaveFile()
{
	if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true);
		
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore", 0);
		CCUserDefault::sharedUserDefault()->flush();
		return false;
	}
	else
	{
		return true;
	}
}

void WelcomeLayer::getHighestHistorySorce()
{
	if (isHaveSaveFile())
	{
		GameOverLayer::highestHistoryScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("HighestScore", 0);
	}
}