#ifndef __WIN_PAGE_H__
#define __WIN_PAGE_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
class Win : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	// initialize game
	virtual bool init();
	// a selector callback
	void Win::start_function();
	// implement the "static create()" method manually
	CREATE_FUNC(Win);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float visibleHeight;
	float visibleWidth;
	cocos2d::Sprite* man;
	cocos2d::Sprite* red;
	cocos2d::Sprite* blue;
	cocos2d::Sprite* orange;
	cocos2d::Sprite* pink;
	Button *RestartButton;
};

#endif // __Win_PAGE_H__
