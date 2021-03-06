#include "PlaneLayer.h"
#include "GameOverScene.h"
PlaneLayer* PlaneLayer::sharedPlane = NULL;
PlaneLayer::PlaneLayer()
{
	isAlive = true;
	score = 0;

}


PlaneLayer::~PlaneLayer()
{
}


PlaneLayer* PlaneLayer::create()
{

	PlaneLayer *pRet = new PlaneLayer();
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		sharedPlane = pRet;
		return pRet;

	} 
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}

}

bool PlaneLayer::init()
{

	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!Layer::init());
		CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
		Sprite * plane = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
		plane->setPosition(Vec2(winsize.width/2,plane->getContentSize().height/2));
		this->addChild(plane,0,AIRPLANE);

		Blink* blink = Blink::create(1, 3);

		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
		animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
		Animate* animate = Animate::create(animation);

		plane->runAction(blink);
		plane->runAction(RepeatForever::create(animate));

		bRet = true;
	} while (0);


	return bRet;

}

void PlaneLayer::Blowup(int passScore)
{
	if (isAlive)
	{
		isAlive = false;
		score = passScore;
		CCAnimation* animation = CCAnimation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png"));

		CCAnimate* animate = CCAnimate::create(animation);
		CCCallFunc* removePlane = CCCallFunc::create(this, callfunc_selector(PlaneLayer::RemovePlane));
		CCSequence* sequence = CCSequence::create(animate, removePlane, NULL);
		this->getChildByTag(AIRPLANE)->stopAllActions();
		this->getChildByTag(AIRPLANE)->runAction(sequence);
	}


}
void PlaneLayer::RemovePlane()
{

	this->removeChildByTag(AIRPLANE, true);
	GameOverScene* pScene = GameOverScene::create(score);
	CCTransitionMoveInT* animateScene = CCTransitionMoveInT::create(0.8f, pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);


}