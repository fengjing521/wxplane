#pragma once
#include "cocos2d.h"
USING_NS_CC;
class BulletLayer:public Layer
{
public:
	BulletLayer();
	~BulletLayer();
public:
	CREATE_FUNC(BulletLayer);
	virtual bool init();
	void AddBullet(float dt);
	void bulletMoveFinished(Node* pSender);
	void RemoveBullet(Sprite* bullet);
	void StartShoot(float delay=0.0f);
	void StopShoot();

public:
	Array* m_pAllBullet;
	SpriteBatchNode* bulletBatchNode;

};

