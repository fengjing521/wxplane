#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "ControlLayer.h"
USING_NS_CC;
const int ENEMY1_SCORE = 1000;
const int ENEMY2_SCORE = 6000;
const int ENEMY3_SCORE = 30000;

const int MAX_BIGBOOM_COUNT = 100000;
const int TAG_BIGBOOM_MENUITEM = 1;
const int TAG_BIGBOOMCOUNT_LABEL = 2;
class GameLayer:public Layer
{
public:
	GameLayer();
	~GameLayer();
	CREATE_FUNC(GameLayer);

	virtual bool init();
	void backgroundMove(float dt);
	bool onTouchBegan(Touch * touch, Event * event);
	void onTouchMoved(Touch * touch, Event * event);
	void onTouchEnded(Touch * touch, Event * event);
	 


	static Level getCurLevel();
	void GameLayer::update(float dt);
private:
	Sprite* bground1;
	Sprite* bground2;

	PlaneLayer* planeLayer;
	BulletLayer* bulletLayer;
	EnemyLayer* enemyLayer;
	
	ControlLayer* controlLayer;


	int score;
	int bigBoomCount;
	static Level level;
};

