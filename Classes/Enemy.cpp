#include "Enemy.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;



Enemy::Enemy()
{
	m_sprite = NULL;
	m_life = 0;
}


Enemy::~Enemy()
{
}
 Enemy* Enemy::create()
{

	 Enemy* pRet = new Enemy;
	 pRet->autorelease();
	 return pRet;

}
 void Enemy::bindSprite(Sprite* sprite, int life)
{
	 m_sprite = sprite;
	 m_life = life;
	 this->addChild(m_sprite);

}
 Sprite* Enemy::getSprite()
{
	 return m_sprite;
}
 int Enemy::getLife()
{
	 return m_life;
}
 void Enemy::loseLife()

	{
	 m_life--;

	}

 Rect Enemy::getBoundingBox()
 {
 
	 Rect rect = m_sprite->boundingBox();
	 Point pos = this->convertToWorldSpace(rect.origin);
	 Rect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);
 
	 return enemyRect;
 
 }