#include "GameScene.h"


GameScene::GameScene()
{
	_gameLayer = nullptr;
}


GameScene::~GameScene()
{
}

bool GameScene::init()
{

	bool bRet = false;
	do 
	{

		CC_BREAK_IF(!Scene::init());
		_gameLayer = GameLayer::create();
		CC_BREAK_IF(!_gameLayer);
		this->addChild(_gameLayer);
		bRet = true;
	} while (0);

	return bRet;


}