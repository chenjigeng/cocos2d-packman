#ifndef __LOSE_PAGE_H__
#define __LOSE_PAGE_H__

#include "cocos2d.h"

class Lose : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	// initialize game
	virtual bool init();
	// a selector callback
	
	// implement the "static create()" method manually
	CREATE_FUNC(Lose);
	void Lose::start_function();
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite* red;
	float visibleHeight;
	float visibleWidth;
};

#endif // __LOSE_PAGE_H__
