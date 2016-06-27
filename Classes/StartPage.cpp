#include "StartPage.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "gamePage.h"
#include "losePage.h"
#include "winPage.h"
using namespace cocos2d::ui;
USING_NS_CC;

Scene* StartPage::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartPage::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartPage::init() {
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	visibleHeight = visibleSize.height;
	visibleWidth = visibleSize.width;

	auto label = Label::createWithTTF("Packman", "fonts/Marker Felt.ttf", 80);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(ccc3(255, 255, 0));
	// add the label as a child to this layer
	this->addChild(label, 2);

	//红色怪物
	red = Sprite::create("sprite/player-1.png");
	red->setPosition(Vec2(visibleSize.width / 2 + origin.x- 250, visibleSize.height / 2 + 100));
	red->setScale(0.15);
	this->addChild(red, 1);
	auto mAnimation = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "sprite/red-%d.png", i);
		mAnimation->addSpriteFrameWithFile(nameSize);
	}
	mAnimation->setDelayPerUnit(0.05f);
	mAnimation->setLoops(-1);
	auto mAnimate = Animate::create(mAnimation);
	red->runAction(mAnimate);

	//蓝色怪物
	blue = Sprite::create("sprite/player-1.png");
	blue->setPosition(Vec2(visibleSize.width / 2 + origin.x - 60, visibleSize.height / 2 + 100));
	blue->setScale(0.15);
	this->addChild(blue, 1);
	auto mAnimation2 = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "sprite/blue-%d.png", i);
		mAnimation2->addSpriteFrameWithFile(nameSize);
	}
	mAnimation2->setDelayPerUnit(0.05f);
	mAnimation2->setLoops(-1);
	auto mAnimate2 = Animate::create(mAnimation2);
	blue->runAction(mAnimate2);

	//橘黄色怪物
	orange = Sprite::create("sprite/player-1.png");
	orange->setPosition(Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + 100));
	orange->setScale(0.15);
	this->addChild(orange, 1);
	auto mAnimation3 = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "sprite/orange-%d.png", i);
		mAnimation3->addSpriteFrameWithFile(nameSize);
	}
	mAnimation3->setDelayPerUnit(0.05f);
	mAnimation3->setLoops(-1);
	auto mAnimate3 = Animate::create(mAnimation3);
	orange->runAction(mAnimate3);

	//紫色怪物
	pink = Sprite::create("sprite/player-1.png");
	pink->setPosition(Vec2(visibleSize.width / 2 + origin.x + 280, visibleSize.height / 2 + 100));
	pink->setScale(0.15);
	this->addChild(pink, 15);
	auto mAnimation4 = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "sprite/pink-%d.png", i);
		mAnimation4->addSpriteFrameWithFile(nameSize);
	}
	mAnimation4->setDelayPerUnit(0.05f);
	mAnimation4->setLoops(-1);
	auto mAnimate4 = Animate::create(mAnimation4);
	pink->runAction(mAnimate4);

	//吃豆人
	man = Sprite::create("sprite/player-1.png");
	man->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y-60));
	man->setScale(0.18);
	this->addChild(man, 1);
	auto mAnimation1 = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "sprite/player-%d.png", i);
		mAnimation1->addSpriteFrameWithFile(nameSize);
	}
	mAnimation1->setDelayPerUnit(0.1f);
	mAnimation1->setLoops(-1);
	auto mAnimate1 = Animate::create(mAnimation1);
	man->runAction(mAnimate1);
	/*man = Sprite::create("sprite/player201.png");
	man->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 30));
	man->setScale(4);
	this->addChild(man, 1);*/

	//开始按钮
	StartButton = Button::create();
	StartButton->setTitleText("Start");
	StartButton->setTitleFontSize(55);
	StartButton->setPosition(Size(visibleWidth / 2 + origin.x, visibleHeight / 4));
	StartButton->setTitleFontName("AR DELANEY");
	StartButton->addClickEventListener(CC_CALLBACK_0(StartPage::start_function, this));
	this->addChild(StartButton, 2);

}

void StartPage::start_function() {
	auto gameScene = MainGame::createScene();
	//Director::getInstance()->runWithScene(gameScene);
	Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));
}