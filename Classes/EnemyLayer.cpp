#include "EnemyLayer.h"
#include "GameLayer.h"



EnemyLayer::EnemyLayer()
{
	enemy1SpriteFrame = NULL;
	enemy2SpriteFrame = NULL;
	enemy3SpriteFrame_1 = NULL;
	enemy3SpriteFrame_2 = NULL;

	m_pAllEnemy1 = Array::create();
	m_pAllEnemy1->retain();
	m_pAllEnemy2 = Array::create();
	m_pAllEnemy2->retain();
	m_pAllEnemy3 = Array::create();
	m_pAllEnemy3->retain();

}


EnemyLayer::~EnemyLayer()
{
	
	m_pAllEnemy1->release();
	m_pAllEnemy1 =NULL;
	m_pAllEnemy2->release();
	m_pAllEnemy2 = NULL;
	m_pAllEnemy3->release();
	m_pAllEnemy3 = NULL;

}
bool EnemyLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		enemy1SpriteFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png");
		enemy2SpriteFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png");
		enemy3SpriteFrame_1 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png");
		enemy3SpriteFrame_2 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png");

		Animation* animation1 = Animation::create();
		animation1->setDelayPerUnit(0.1f);
		animation1->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
		animation1->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
		animation1->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
		animation1->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));

		Animation* animation2 = Animation::create();
		animation2->setDelayPerUnit(0.1f);
		animation2->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down1.png"));
		animation2->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down2.png"));
		animation2->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down3.png"));
		animation2->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down4.png"));

		Animation* animation3 = Animation::create();
		animation3->setDelayPerUnit(0.1f);
		animation3->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
		animation3->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
		animation3->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
		animation3->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
		animation3->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
		animation3->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));

		AnimationCache::sharedAnimationCache()->addAnimation(animation1, "Enemy1Blowup");
		AnimationCache::sharedAnimationCache()->addAnimation(animation2, "Enemy2Blowup");
		AnimationCache::sharedAnimationCache()->addAnimation(animation3, "Enemy3Blowup");

		this->schedule(schedule_selector(EnemyLayer::addEnemy1), 0.5f);
		this->schedule(schedule_selector(EnemyLayer::addEnemy2), 3.0f);
		this->schedule(schedule_selector(EnemyLayer::addEnemy3), 6.0f);

		bRet = true;
	} while (0);
	return bRet;
	 
}

void EnemyLayer::addEnemy1(float dt)
{
	Enemy* enemy1 = Enemy::create();
	enemy1->bindSprite(Sprite::createWithSpriteFrame(enemy1SpriteFrame), ENEMY1_MAXLIFE);

	Size enemy1Size = enemy1->getSprite()->getContentSize();
	Size winSize = Director::sharedDirector()->getWinSize();
	int minX = enemy1Size.width / 2;
	int maxX = winSize.width - enemy1Size.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;

	enemy1->setPosition(Vec2(actualX, winSize.height + enemy1Size.height / 2));
	this->addChild(enemy1);
	this->m_pAllEnemy1->addObject(enemy1);

	float minDuration, maxDuration;
	switch (GameLayer::getCurLevel())
	{
	case EASY:
		minDuration = 2.0;
		maxDuration = 4.0;
		break;
	case MIDDLE:
		minDuration = 1.8;
		maxDuration = 3.6;
		break;
	case HARD:
		minDuration = 1.6;
		maxDuration = 3.2;
		break;
	default:
		minDuration = 2.0;
		maxDuration = 4.0;
		break;
	}


	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration) + minDuration;

	FiniteTimeAction* actionMove =MoveTo::create(actualDuration,Vec2(actualX, 0 - enemy1->getSprite()->getContentSize().height / 2));
	FiniteTimeAction* actionDone =CallFuncN::create(this, callfuncN_selector(EnemyLayer::enemy1MoveFinished));

	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	enemy1->runAction(sequence);
}

	void EnemyLayer::enemy1MoveFinished(Node* pSender)
	{
		Enemy* enmey1 = (Enemy*)pSender;
		this->removeChild(enmey1, true);
		this->m_pAllEnemy1->removeObject(enmey1);
	}

	void EnemyLayer::enemy1Blowup(Enemy* enemy1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy1_down.mp3");
		Animation* animation = AnimationCache::sharedAnimationCache()->animationByName("Enemy1Blowup");
		Animate* animate = Animate::create(animation);
		CCCallFuncND* removeEnemy1 =CCCallFuncND::create(this, callfuncND_selector(EnemyLayer::removeEnemy1), (void*)enemy1);
		Sequence* sequence = Sequence::create(animate, removeEnemy1, NULL);
		enemy1->getSprite()->runAction(sequence);
	}

	void EnemyLayer::removeEnemy1(Node* pTarget, void* data)
	{
		Enemy* enemy1 = (Enemy*)data;
		if (enemy1 != NULL)
		{
			m_pAllEnemy1->removeObject(enemy1);
			this->removeChild(enemy1, true);
		}
	}

	void EnemyLayer::removeAllEnemy1()
	{
		Object* obj;
		CCARRAY_FOREACH(m_pAllEnemy1, obj)
		{
			Enemy* enemy1 = (Enemy*)obj;
			if (enemy1->getLife() > 0)
			{
				enemy1Blowup(enemy1);
			}
		}
	}


	void EnemyLayer::addEnemy2(float dt)
	{
		Enemy* enemy2 = Enemy::create();
		enemy2->bindSprite(Sprite::createWithSpriteFrame(enemy2SpriteFrame), ENEMY2_MAXLIFE);

		Size enemy2Size = enemy2->getSprite()->getContentSize();
		Size winSize = Director::sharedDirector()->getWinSize();
		int minX = enemy2Size.width / 2;
		int maxX = winSize.width - enemy2Size.width / 2;
		int rangeX = maxX - minX;
		int actualX = (rand() % rangeX) + minX;

		enemy2->setPosition(Vec2(actualX, winSize.height + enemy2Size.height / 2));
		this->addChild(enemy2);
		this->m_pAllEnemy2->addObject(enemy2);

		float minDuration, maxDuration;
		switch (GameLayer::getCurLevel())
		{
		case EASY:
			minDuration = 3.0;
			maxDuration = 6.0;
			break;
		case MIDDLE:
			minDuration = 2.7;
			maxDuration = 5.4;
			break;
		case HARD:
			minDuration = 2.5;
			maxDuration = 5.0;
			break;
		default:
			minDuration = 3.0;
			maxDuration = 6.0;
			break;
		}
		int rangeDuration = maxDuration - minDuration;
		int actualDuration = (rand() % rangeDuration) + minDuration;

		FiniteTimeAction* actionMove = MoveTo::create(actualDuration, Vec2(actualX, 0 - enemy2->getSprite()->getContentSize().height / 2));
		FiniteTimeAction* actionDone = CallFuncN::create(this, callfuncN_selector(EnemyLayer::enemy2MoveFinished));

		Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
		enemy2->runAction(sequence);
	}

	void EnemyLayer::enemy2MoveFinished(Node* pSender)
	{
		Enemy* enmey2 = (Enemy*)pSender;
		this->removeChild(enmey2, true);
		this->m_pAllEnemy2->removeObject(enmey2);
	}

	void EnemyLayer::enemy2Blowup(Enemy* enemy2)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy2_down.mp3");
		Animation* animation = AnimationCache::sharedAnimationCache()->animationByName("Enemy2Blowup");
		Animate* animate = Animate::create(animation);

		CCCallFuncND* removeEnemy2 = CCCallFuncND::create(this, callfuncND_selector(EnemyLayer::removeEnemy2), (void*)enemy2);
		Sequence* sequence = Sequence::create(animate, removeEnemy2, NULL);
		enemy2->getSprite()->runAction(sequence);
	}

	void EnemyLayer::removeEnemy2(Node* pTarget, void* data)
	{
		Enemy* enemy2 = (Enemy*)data;
		if (enemy2 != NULL)
		{
			m_pAllEnemy2->removeObject(enemy2);
			this->removeChild(enemy2, true);
		}
	}

	void EnemyLayer::removeAllEnemy2()
	{
		Object* obj;

		CCARRAY_FOREACH(m_pAllEnemy2, obj)
		{
			Enemy* enemy2 = (Enemy*)obj;
			if (enemy2->getLife() > 0)
			{
				enemy2Blowup(enemy2);
			}
		}
	}


	void EnemyLayer::addEnemy3(float dt)
	{
		Enemy* enemy3 = Enemy::create();
		enemy3->bindSprite(Sprite::createWithSpriteFrame(enemy3SpriteFrame_1), ENEMY3_MAXLIFE);

		Size enemy3Size = enemy3->getSprite()->getContentSize();
		Size winSize = Director::sharedDirector()->getWinSize();
		int minX = enemy3Size.width / 2;
		int maxX = winSize.width - enemy3Size.width / 2;
		int rangeX = maxX - minX;
		int actualX = (rand() % rangeX) + minX;

		enemy3->setPosition(Vec2(actualX, winSize.height + enemy3Size.height / 2));
		this->addChild(enemy3);
		this->m_pAllEnemy3->addObject(enemy3);

		float minDuration, maxDuration;
		switch (GameLayer::getCurLevel())
		{
		case EASY:
			minDuration = 4.0;
			maxDuration = 8.0;
			break;
		case MIDDLE:
			minDuration = 3.6;
			maxDuration = 7.2;
			break;
		case HARD:
			minDuration = 3.2;
			maxDuration = 6.4;
			break;
		default:
			minDuration = 4.0;
			maxDuration = 8.0;
			break;
		}

		int rangeDuration = maxDuration - minDuration;
		int actualDuration = (rand() % rangeDuration) + minDuration;

		FiniteTimeAction* actionMove = MoveTo::create(actualDuration, Vec2(actualX, 0 - enemy3->getSprite()->getContentSize().height / 2));
		FiniteTimeAction* actionDone = CallFuncN::create(this, callfuncN_selector(EnemyLayer::enemy3MoveFinished));

		Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
		enemy3->runAction(sequence);

		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(enemy3SpriteFrame_1);
		animation->addSpriteFrame(enemy3SpriteFrame_2);
		Animate* animate = Animate::create(animation);
		enemy3->getSprite()->runAction(RepeatForever::create(animate));
	}

	void EnemyLayer::enemy3MoveFinished(Node* pSender)
	{
		Enemy* enmey3 = (Enemy*)pSender;
		this->removeChild(enmey3, true);
		this->m_pAllEnemy3->removeObject(enmey3);
	}

	void EnemyLayer::enemy3Blowup(Enemy* enemy3)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy3_down.mp3");
		Animation* animation = AnimationCache::sharedAnimationCache()->animationByName("Enemy3Blowup");

		Animate* animate = Animate::create(animation);
		CCCallFuncND* removeEnemy3 = CCCallFuncND::create(this, callfuncND_selector(EnemyLayer::removeEnemy3), (void*)enemy3);
		Sequence* sequence = Sequence::create(animate, removeEnemy3, NULL);
		enemy3->getSprite()->runAction(sequence);
	}

	void EnemyLayer::removeEnemy3(Node* pTarget, void* data)
	{
		Enemy* enemy3 = (Enemy*)data;
		if (enemy3 != NULL)
		{
			enemy3->stopAllActions();
			m_pAllEnemy3->removeObject(enemy3);
			this->removeChild(enemy3, true);
		}
	}

	void EnemyLayer::removeAllEnemy3()
	{
		Object* obj;
		CCARRAY_FOREACH(m_pAllEnemy3, obj)
		{
			Enemy* enemy3 = (Enemy*)obj;
			if (enemy3->getLife() > 0)
			{
				enemy3Blowup(enemy3);
			}
		}
	}

	void EnemyLayer::removeAllEnemy()
	{
		removeAllEnemy1();
		removeAllEnemy2();
		removeAllEnemy3();
	}
