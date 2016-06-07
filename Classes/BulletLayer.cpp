#include "BulletLayer.h"
#include "PlaneLayer.h"

BulletLayer::BulletLayer()
{
	bulletBatchNode = NULL;
	m_pAllBullet = Array::create();
	m_pAllBullet->retain();

}


BulletLayer::~BulletLayer()
{
	m_pAllBullet->release();
	m_pAllBullet = NULL;

}
bool BulletLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		Texture2D* textture = TextureCache::sharedTextureCache()->textureForKey("ui/shoot.png");
		bulletBatchNode = SpriteBatchNode::createWithTexture(textture);
		this->addChild(bulletBatchNode);


		bRet = true;
	} while (0);

	return bRet;

}
void BulletLayer::AddBullet(float dt)
{

	Sprite* bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	bulletBatchNode->addChild(bullet);
	this->m_pAllBullet->addObject(bullet);

	Point planePosition = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	Point bulletPosition = Vec2(planePosition.x, planePosition.y + PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height/2);
	bullet->setPosition(bulletPosition);

	float length = Director::sharedDirector()->getWinSize().height + bullet->getContentSize().height / 2 - bulletPosition.y;
	float veloc = 320 / 1;
	float movespeed = length / veloc;

	FiniteTimeAction* actionMove = MoveTo::create(movespeed, Vec2(bulletPosition.x,Director::sharedDirector()->getWinSize().height+bullet->getContentSize().height/2));
	FiniteTimeAction* actionDone = CallFuncN::create(this, callfuncN_selector(BulletLayer::bulletMoveFinished));

	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	bullet->runAction(sequence);
}
void BulletLayer::bulletMoveFinished(Node* pSender)
{
	Sprite* bullet = (Sprite*)pSender;
	m_pAllBullet->removeObject(bullet);
	this->bulletBatchNode->removeChild(bullet, true);

}
void BulletLayer::RemoveBullet(Sprite* bullet)
{
	if (bullet!=NULL)
	{
		this->m_pAllBullet->removeObject(bullet);
		this->bulletBatchNode->removeChild(bullet, true);

	}


}
void BulletLayer::StartShoot(float delay)
{

	this->schedule(schedule_selector(BulletLayer::AddBullet),0.20f,kRepeatForever,1.0f);


}
void BulletLayer::StopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::AddBullet));

}