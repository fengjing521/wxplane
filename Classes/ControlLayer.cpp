#include "ControlLayer.h"


ControlLayer::ControlLayer()
{
	scoreItem = NULL;
	pPauseItem = NULL;
}


ControlLayer::~ControlLayer()
{
}
bool ControlLayer::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		//加入PauseMenu
		Sprite* normalPause = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
		Sprite* pressedPause = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
	/*	Sprite * normalPause = Sprite::createWithSpriteFrameName("game_pause_nor.png");
		Sprite * pressedPause = Sprite::createWithSpriteFrameName("game_pause_pressed.png");*/
		pPauseItem = MenuItemSprite::create(normalPause, pressedPause, NULL, this, menu_selector(ControlLayer::menuPauseCallback));
		pPauseItem->setPosition(Vec2(normalPause->getContentSize().width / 2 + 10, winSize.height - normalPause->getContentSize().height / 2 - 10));
		Menu *menuPause = Menu::create(pPauseItem, NULL);
		menuPause->setPosition(Vec2(0,0));
		this->addChild(menuPause, 101);

	
		//加入score
		scoreItem = CCLabelBMFont::create("0", "font/font.fnt");
		scoreItem->setColor(ccc3(143, 146, 147));
		scoreItem->setAnchorPoint(Vec2(0, 0.5));
		scoreItem->setPosition(Vec2(pPauseItem->getPositionX() + normalPause->getContentSize().width / 2 + 5, pPauseItem->getPositionY()));
		this->addChild(scoreItem);



		return true;
	} while (0);



	return bRet;

}
void ControlLayer::menuPauseCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3");
	if (!CCDirector::sharedDirector()->isPaused())
	{
	/*	pPauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_resume_nor.png"));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_resume_pressed"));*/

		pPauseItem->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png")));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png")));
		
	
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		CCDirector::sharedDirector()->pause();
		
	
	}
	else
	{
		pPauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_pause_nor.png"));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_pause_pressed.png"));

		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		CCDirector::sharedDirector()->resume();
		
	}
}

void ControlLayer::updateScore(int score)
{
	if (score >= 0 && score <= MAX_SCORE)
	{
		CCString* strScore = CCString::createWithFormat("%d", score);
		scoreItem->setString(strScore->getCString());

	}
}
