#include "losePage.h"
#include "gamePage.h"
USING_NS_CC;

Scene* Lose::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Lose::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Lose::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	visibleHeight = visibleSize.height;
	visibleWidth = visibleSize.width;

	auto label = Label::createWithTTF("Game  over", "fonts/Marker Felt.ttf", 120);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + 20));
	label->setColor(ccc3(255, 255, 0));
	// add the label as a child to this layer
	this->addChild(label, 2);
	
	////ºìÉ«¹ÖÎï
	//red = Sprite::create("sprite/player1.png");
	//red->setPosition(Vec2(visibleSize.width / 2 + origin.x + 45, visibleSize.height / 2 + 15));
	//red->setScale(0.1);
	//this->addChild(red, 1);
	//auto mAnimation = Animation::create();
	//for (int i = 1; i < 3; i++) {
	//	char nameSize[100] = { 0 };
	//	sprintf(nameSize, "sprite/red-%d.png", i);
	//	mAnimation->addSpriteFrameWithFile(nameSize);
	//}
	//mAnimation->setDelayPerUnit(0.05f);
	//mAnimation->setLoops(-1);
	//auto mAnimate = Animate::create(mAnimation);
	//red->runAction(mAnimate);
	auto StartButton = Button::create();
	StartButton->setTitleText("Start");
	StartButton->setTitleFontSize(55);
	StartButton->setPosition(Size(visibleWidth / 2 + origin.x, visibleHeight / 4));
	StartButton->setTitleFontName("AR DELANEY");
	StartButton->addClickEventListener(CC_CALLBACK_0(Lose::start_function, this));
	this->addChild(StartButton, 2);
	return true;
}
void Lose::start_function() {
	auto gameScene = MainGame::createScene();
	//Director::getInstance()->runWithScene(gameScene);
	Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));
}
