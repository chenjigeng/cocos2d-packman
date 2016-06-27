#ifndef _STARTPAGE_H_
#define _STARTPAGE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
class StartPage : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void start_function();


	// implement the "static create()" method manually
	CREATE_FUNC(StartPage);


private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float visibleHeight;
	float visibleWidth;
	Button *StartButton;
	Button *RuleButton;
	cocos2d::Sprite* man;
	cocos2d::Sprite* red;
	cocos2d::Sprite* blue;
	cocos2d::Sprite* orange;
	cocos2d::Sprite* pink;
};

#endif
