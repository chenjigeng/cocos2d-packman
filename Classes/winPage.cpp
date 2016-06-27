#include "winPage.h"
#include "ui/CocosGUI.h"
#include "StartPage.h"
#include "gamePage.h"
using namespace cocos2d::ui;
USING_NS_CC;

Scene* Win::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Win::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Win::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	visibleHeight = visibleSize.height;
	visibleWidth = visibleSize.width;

	auto label = Label::createWithTTF("Congratulation!", "fonts/Marker Felt.ttf", 120);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2 + 30,
		origin.y + visibleSize.height / 2 + 60));
	label->setColor(ccc3(255, 255, 0));
	// add the label as a child to this layer
	this->addChild(label, 0);

	//RestartButton = Button::create();
	//RestartButton->setTitleText("Play again");
	//RestartButton->setTitleFontSize(25);
	//RestartButton->setPosition(Size(visibleWidth / 2, visibleHeight / 3));
	//RestartButton->setTitleFontName("Marker Felt");
	//RestartButton->addClickEventListener(CC_CALLBACK_0(StartPage::start_function, this));
	//this->addChild(RestartButton, 2);
	auto StartButton = Button::create();
	StartButton->setTitleText("Start");
	StartButton->setTitleFontSize(55);
	StartButton->setPosition(Size(visibleWidth / 2 + origin.x, visibleHeight / 4));
	StartButton->setTitleFontName("AR DELANEY");
	StartButton->addClickEventListener(CC_CALLBACK_0(Win::start_function, this));
	this->addChild(StartButton, 2);
	return true;
}
void Win::start_function() {
	auto gameScene = MainGame::createScene();
	//Director::getInstance()->runWithScene(gameScene);
	Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));
}