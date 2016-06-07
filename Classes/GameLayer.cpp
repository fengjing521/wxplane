#include "GameLayer.h"
Level GameLayer::level = EASY;

GameLayer::GameLayer()
{
	bground1 = NULL;
	bground2 = NULL;
	planeLayer = NULL;
	bulletLayer = NULL;
	
	enemyLayer = NULL;

	score = 0;
	bigBoomCount = 0;
}


GameLayer::~GameLayer()
{
}
bool GameLayer::init()
{

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.mp3", true);//背景音乐
			//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3", true);//这两种方法均可以
		}
		
		 
	 bground1 = Sprite::createWithSpriteFrameName("background.png");
	bground1->setAnchorPoint(Vec2(0,0));
	bground1->setPosition(Vec2(0,0));
	this->addChild(bground1);

	bground2 = Sprite::createWithSpriteFrameName("background.png");
	bground2->setAnchorPoint(Vec2(0, 0));
	bground2->setPosition(Vec2(0,bground1->getContentSize().height-2));
	this->addChild(bground2);
	this->schedule(schedule_selector(GameLayer::backgroundMove),0.01f);
	

	this->planeLayer = PlaneLayer::create();
	this->addChild(planeLayer);

	this->bulletLayer = BulletLayer::create();
	this->addChild(bulletLayer);
	this->bulletLayer->StartShoot();


	this->enemyLayer = EnemyLayer::create();
	this->addChild(enemyLayer);


	this->controlLayer = ControlLayer::create();
	this->addChild(controlLayer);

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	this->setKeyboardEnabled(true);
	this->scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;


}
void GameLayer::backgroundMove(float dt)
{
	
	bground1->setPositionY(bground1->getPositionY() - 2);
	bground2->setPositionY(bground1->getPositionY()+bground1->getContentSize().height - 2);
	if (bground2->getPositionY()==0)
	{
		bground1->setPositionY(0);
     }

}
bool GameLayer::onTouchBegan(Touch * touch, Event * event)
{
	CCLOG("began");
	return true;

}
void GameLayer::onTouchMoved(Touch * touch, Event * event)
{
	CCLOG("move");
	if (this->planeLayer->isAlive)
	{
		
		auto planehero = this->planeLayer->getChildByTag(AIRPLANE);
		Rect planeRect = planehero->boundingBox();
		planeRect.origin.x -= 15;
		planeRect.origin.y -= 15;
		planeRect.size.width += 30;
		planeRect.size.height += 30;
		
		Point pointm = planehero->getPosition() + touch->getDelta();
		Size winsize = CCDirector::sharedDirector()->getWinSize();
		if (planeRect.containsPoint(touch->getLocation()))//去掉if 既是飞机在整个层任意位置都可以移动
		{
			if (pointm.x >planehero->boundingBox().size.width / 2&& pointm.x <winsize.width-planehero->boundingBox().size.width / 2&&
			
				pointm.y>planehero->boundingBox().size.height / 2 && pointm.y<winsize.height - planehero->boundingBox().size.height / 2)
			{
				
				planehero->setPosition(Vec2(pointm));
			}
		
		}
		
	

	}
}
void GameLayer::onTouchEnded(Touch * touch, Event * event)
{

	CCLOG("end");



}
Level GameLayer::getCurLevel()
{
	return level;
}
void GameLayer::update(float dt)
{

	if (level == EASY && score >= 1000000)
	{
		level = MIDDLE;
	}
	else if (level == MIDDLE && score >= 2000000)
	{
		level = HARD;
	}

	CCArray* bulletsToDelete = CCArray::create();
	bulletsToDelete->retain();
	CCObject* bt, *et, *ut;

	//enemy1 & bullet CheckCollosion
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
	{
		CCSprite* bullet = (CCSprite*)bt;

		CCArray* enemy1sToDelete = CCArray::create();
		enemy1sToDelete->retain();
		int a = this->enemyLayer->m_pAllEnemy1->capacity();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
		{
			Enemy* enemy1 = (Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				if (enemy1->getLife() == 1)
				{
					enemy1->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy1sToDelete->addObject(enemy1);
					score += ENEMY1_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy1sToDelete, et)
		{
			Enemy* enemy1 = (Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete, bt)
	{
		CCSprite* bullet = (CCSprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();

	
	//enemy2 & bullet CheckCollosion
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
	{
		CCSprite* bullet = (CCSprite*)bt;

		CCArray* enemy2sToDelete = CCArray::create();
		enemy2sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2, et)
		{
			Enemy* enemy2 = (Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife() > 1)
				{
					enemy2->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				else if (enemy2->getLife() == 1)
				{
					enemy2->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy2sToDelete->addObject(enemy2);
					score += ENEMY2_SCORE;
					this->controlLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy2sToDelete, et)
		{
			Enemy* enemy2 = (Enemy*)et;
			this->enemyLayer->enemy2Blowup(enemy2);
		}
		enemy2sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete, bt)
	{
		CCSprite* bullet = (CCSprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();

	//enemy3 & bullet CheckCollosion
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
	{
		CCSprite* bullet = (CCSprite*)bt;

		CCArray* enemy3sToDelete = CCArray::create();
		enemy3sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3, et)
		{
			Enemy* enemy3 = (Enemy*)et;
			if (bullet->boundingBox().intersectsRect(enemy3->getBoundingBox()))
			{
				//如果life>1,移除bullet
				if (enemy3->getLife() > 1)
				{
					enemy3->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				//如果life==1,移除enemy3
				else if (enemy3->getLife() == 1)
				{
					enemy3->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy3sToDelete->addObject(enemy3);
					score += ENEMY3_SCORE;
					this->controlLayer->updateScore(score);
				}
				//此时处在animate阶段,不做处理
				else;
			}
		}
		CCARRAY_FOREACH(enemy3sToDelete, et)
		{
			Enemy* enemy3 = (Enemy*)et;
			this->enemyLayer->enemy3Blowup(enemy3);
		}
		enemy3sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete, bt)
	{
		CCSprite* bullet = (CCSprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();
	bulletsToDelete->release();
	//飞机被碰
	CCRect airplaneRect = this->planeLayer->getChildByTag(AIRPLANE)->boundingBox();
	airplaneRect.origin.x += 30;
	airplaneRect.size.width -= 60;
	//enemy1 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
	{
		Enemy* enemy1 = (Enemy*)et;
		if (enemy1->getLife() > 0)
		{
			if (airplaneRect.intersectsRect(enemy1->getBoundingBox()))
			{
				//卸载所有任务计划
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				
				this->planeLayer->Blowup(score);
				return;
			}
		}
	}

	//enemy2 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2, et)
	{
		Enemy* enemy2 = (Enemy*)et;
		if (enemy2->getLife() > 0)
		{
			if (airplaneRect.intersectsRect(enemy2->getBoundingBox()))
			{
				//卸载所有任务计划
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				
				this->planeLayer->Blowup(score);
				return;
			}
		}
	}

	//enemy3 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3, et)
	{
		Enemy* enemy3 = (Enemy*)et;
		if (enemy3->getLife() > 0)
		{
			if (airplaneRect.intersectsRect(enemy3->getBoundingBox()))
			{
				//卸载所有任务计划
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				
				this->planeLayer->Blowup(score);
				return;
			}
		}
	}

	
	
}