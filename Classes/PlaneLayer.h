#pragma once
#include "cocos2d.h"
USING_NS_CC;
const int AIRPLANE = 747;
class PlaneLayer:public Layer
{
public:
	PlaneLayer();
	~PlaneLayer();
	static PlaneLayer* create();
	virtual bool init();
	void Blowup(int passScore);
	void RemovePlane();

public:
	static PlaneLayer * sharedPlane;
	bool isAlive;
	int score;
};

