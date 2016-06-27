#include "gamePage.h"
#include "CCCircle.h"
#include "cocos2d.h" 
#include "SimpleAudioEngine.h" 
USING_NS_CC;
using namespace cocos2d;      
using namespace CocosDenshion;
Scene* MainGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainGame::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainGame::goToLosePage, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	addMap();
	addBean();
	addPlayer();
	addEnemy();
	addKeyboardListener();
	scheduleUpdate();
	monsterMove(0.1);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("1.WAV", true);
	return true;
}

void MainGame::addMap() {
	
	auto label = Label::createWithTTF("Packman", "fonts/ARLRDBD.TTF", 40);

	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	this->addChild(label, 1);

	map = TMXTiledMap::create("wallMap1.tmx");
	map->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setScale(640 / map->getContentSize().width);
	this->addChild(map, 0);
	p_x = map->getPosition().x;
	p_y = map->getPosition().y;
	wid = map->getContentSize().width;
	hei = map->getContentSize().height;

	wall = map->getObjectGroup("wall");
}

void MainGame::addPlayer() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	TMXObjectGroup* objectGroup = map->getObjectGroup("elements");
	ValueVector objects = objectGroup->getObjects();
	player = Sprite::create("GameSprite/Player1.png");
	player->setPosition(Vec2(beans[27]->getPosition().x, beans[3]->getPosition().y));
	//player->setScale(0.5);
	//for (auto &obj : objects) {
	//	ValueMap& values = obj.asValueMap();
	//	if (values["name"].asString() == "playerBirth")
	//	{
	//		float x = values["x"].asFloat();      // x×ø±ê
	//		float y = values["y"].asFloat();      // y×ø±ê
	//		player->setPosition(p_x - wid / 2 + x - 20, p_y - hei / 2 + y + 30);
	//		break;
	//	}
	//}
	////player->setPosition(Vec2(origin.x + 625, origin.y + 113));
	this->addChild(player, 1);

	auto playerAnimation = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "GameSprite/Player%d.png", i);
		playerAnimation->addSpriteFrameWithFile(nameSize);
	}
	playerAnimation->setDelayPerUnit(0.1f);
	playerAnimation->setLoops(-1);
	auto playerAnimate = Animate::create(playerAnimation);
	player->runAction(playerAnimate);
}

void MainGame::addEnemy() {
	enemyBlue = Sprite::create("GameSprite/Blue1.png");
	enemyBlue->setPosition(Vec2(425, 403));
	this->addChild(enemyBlue, 1);

	auto blueAnimation = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "GameSprite/Blue%d.png", i);
		blueAnimation->addSpriteFrameWithFile(nameSize);
	}
	blueAnimation->setDelayPerUnit(0.1f);
	blueAnimation->setLoops(-1);
	auto blueAnimate = Animate::create(blueAnimation);
	enemyBlue->runAction(blueAnimate);


	enemyOrange = Sprite::create("GameSprite/Orange1.png");
	enemyOrange->setPosition(Vec2(945, 483));
	this->addChild(enemyOrange, 1);

	auto orangeAnimation = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "GameSprite/Orange%d.png", i);
		orangeAnimation->addSpriteFrameWithFile(nameSize);
	}
	orangeAnimation->setDelayPerUnit(0.1f);
	orangeAnimation->setLoops(-1);
	auto orangeAnimate = Animate::create(orangeAnimation);
	enemyOrange->runAction(orangeAnimate);


	enemyPink = Sprite::create("GameSprite/Pink1.png");
	enemyPink->setPosition(Vec2(585, 643));
	this->addChild(enemyPink, 1);

	auto pinkAnimation = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "GameSprite/Pink%d.png", i);
		pinkAnimation->addSpriteFrameWithFile(nameSize);
	}
	pinkAnimation->setDelayPerUnit(0.1f);
	pinkAnimation->setLoops(-1);
	auto pinkAnimate = Animate::create(pinkAnimation);
	enemyPink->runAction(pinkAnimate);

	enemyRed = Sprite::create("GameSprite/Red1.png");
	enemyRed->setPosition(Vec2(785, 643));
	this->addChild(enemyRed, 1);

	auto redAnimation = Animation::create();
	for (int i = 1; i < 3; i++) {
		char nameSize[100] = { 0 };
		sprintf(nameSize, "GameSprite/Red%d.png", i);
		redAnimation->addSpriteFrameWithFile(nameSize);
	}
	redAnimation->setDelayPerUnit(0.1f);
	redAnimation->setLoops(-1);
	auto redAnimate = Animate::create(redAnimation);
	enemyRed->runAction(redAnimate);
}

void MainGame::addBean() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			auto bean = Sprite::create("GameSprite/bean1.png");
			bean->setPosition(Vec2(p_x - wid / 2 + wid / 10 * i + 70, p_y - hei / 2 + hei / 10 * j + 70));
			beans.push_back(bean);
			this->addChild(bean, 1);
		}
	}
	bigBean1 = Sprite::create("GameSprite/bean2.png");
	bigBean1->setPosition(Vec2(p_x - wid / 2 + wid / 10 * 1 + 70, p_y - hei / 2 + hei / 10 * 1 + 70));
	this->addChild(bigBean1, 1);
	bigBean2 = Sprite::create("GameSprite/bean2.png");
	bigBean2->setPosition(Vec2(p_x - wid / 2 + wid / 10 * 1 + 70, p_y - hei / 2 + hei / 10 * 7 + 70));
	this->addChild(bigBean2, 1);
	bigBean3 = Sprite::create("GameSprite/bean2.png");
	bigBean3->setPosition(Vec2(p_x - wid / 2 + wid / 10 * 7 + 70, p_y - hei / 2 + hei / 10 * 1 + 70));
	this->addChild(bigBean3, 1);
	bigBean4 = Sprite::create("GameSprite/bean2.png");
	bigBean4->setPosition(Vec2(p_x - wid / 2 + wid / 10 * 7 + 70, p_y - hei / 2 + hei / 10 * 7 + 70));
	this->addChild(bigBean4, 1);
	/*auto bigBean = Sprite::create("GameSprite/bean2.png");
	bigBean->setPosition(Vec2(100, 300));
	this->addChild(bigBean, 1);*/
}

void MainGame::addKeyboardListener() {
	// TODO
	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainGame::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MainGame::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void MainGame::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
		if (move == MOVE::RIGHT)
			player->setFlipX(true);
		else if (move == MOVE::UP) {
			player->setRotation(0);
			player->setFlipX(true);
		}
		else if (move == MOVE::DOWN) {
			player->setRotation(0);
			player->setFlipX(true);
		}
		if (move != MOVE::LEFT || player->getPosition().x > origin.x) {
			auto moveBy = MoveBy::create(0.1f, Vec2(-2, 0));
			player->runAction(moveBy);
			move = MOVE::LEFT;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
		if (move == MOVE::LEFT)
			player->setFlipX(false);
		else if (move == MOVE::UP)
			player->setRotation(0);
		else if (move == MOVE::DOWN)
			player->setRotation(0);
		if (move != MOVE::RIGHT || player->getPosition().x < origin.x + visibleSize.width) {
			auto moveBy = MoveBy::create(0.1f, Vec2(2, 0));
			player->runAction(moveBy);
			move = MOVE::RIGHT;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_UP_ARROW: {
		if (move == MOVE::LEFT) {
			player->setFlipX(false);
			player->setRotation(-90);
		}
		else if (move == MOVE::RIGHT) {
			player->setRotation(-90);
		}
		else if (move == MOVE::DOWN)
			player->setRotation(-90);
		if (move != MOVE::UP || player->getPosition().x < origin.x + visibleSize.width) {
			auto moveBy = MoveBy::create(0.1f, Vec2(0, 2));
			player->runAction(moveBy);
			move = MOVE::UP;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
		if (move == MOVE::LEFT) {
			player->setFlipX(false);
			player->setRotation(90);
		}
		else if (move == MOVE::RIGHT) {
			player->setRotation(90);
		}
		else if (move == MOVE::UP)
			player->setRotation(90);
		if (move != MOVE::DOWN || player->getPosition().x < origin.x + visibleSize.width) {
			auto moveBy = MoveBy::create(0.1f, Vec2(0, -2));
			player->runAction(moveBy);
			move = MOVE::DOWN;
		}
		break;
	}
	}
}

void MainGame::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
	//switch (code) {
	//case EventKeyboard::KeyCode::KEY_A:
	//case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	//case EventKeyboard::KeyCode::KEY_D:
	//case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	//case EventKeyboard::KeyCode::KEY_W:
	//case EventKeyboard::KeyCode::KEY_UP_ARROW:
	//case EventKeyboard::KeyCode::KEY_S:
	//case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
	//	move = MOVE::NO_DIRECTION;
	//}
	//}
}

void MainGame::becomeSuper() {
	issupered = true;
	float x, y;
	if (enemyBlue != NULL) {
		float x = enemyBlue->getPositionX(), y = enemyBlue->getPositionY();
		enemyBlue->removeFromParentAndCleanup(true);
		enemyBlue = Sprite::create("GameSprite/sprite_1.png");
		enemyBlue->setPosition(x, y);
		addChild(enemyBlue, 1);
	}
	if (enemyRed != NULL) {
		x = enemyRed->getPositionX(), y = enemyRed->getPositionY();
		enemyRed->removeFromParentAndCleanup(true);
		enemyRed = Sprite::create("GameSprite/sprite_1.png");
		enemyRed->setPosition(x, y);
		addChild(enemyRed, 1);
	}
	if (enemyOrange != NULL) {
		x = enemyOrange->getPositionX(), y = enemyOrange->getPositionY();
		enemyOrange->removeFromParentAndCleanup(true);
		enemyOrange = Sprite::create("GameSprite/sprite_1.png");
		enemyOrange->setPosition(x, y);
		addChild(enemyOrange, 1);
	}
	if (enemyPink != NULL) {
		x = enemyPink->getPositionX(), y = enemyPink->getPositionY();
		enemyPink->removeFromParentAndCleanup(true);
		enemyPink = Sprite::create("GameSprite/sprite_1.png");
		enemyPink->setPosition(x, y);
		addChild(enemyPink, 1);
	}
	schedule(schedule_selector(MainGame::becomenormal), 0, 0, 3);
}
void MainGame::becomenormal(float f) {
	float x, y;
	issupered = false;
	if (enemyBlue != NULL) {
		float x = enemyBlue->getPositionX(), y = enemyBlue->getPositionY();
		enemyBlue->removeFromParentAndCleanup(true);

		enemyBlue = Sprite::create("sprite/blue1.png");
		enemyBlue->setPosition(x, y);
		this->addChild(enemyBlue, 1);
		auto blueAnimation = Animation::create();
		for (int i = 1; i < 3; i++) {
			char nameSize[100] = { 0 };
			sprintf(nameSize, "GameSprite/Blue%d.png", i);
			blueAnimation->addSpriteFrameWithFile(nameSize);
		}
		blueAnimation->setDelayPerUnit(0.1f);
		blueAnimation->setLoops(-1);
		auto blueAnimate = Animate::create(blueAnimation);
		enemyBlue->runAction(blueAnimate);
	}
	if (enemyOrange != NULL) {
		x = enemyOrange->getPositionX(), y = enemyOrange->getPositionY();
		enemyOrange->removeFromParentAndCleanup(true);
		enemyOrange = Sprite::create("sprite/orange1.png");
		enemyOrange->setPosition(x, y);
		this->addChild(enemyOrange, 1);

		auto orangeAnimation = Animation::create();
		for (int i = 1; i < 3; i++) {
			char nameSize[100] = { 0 };
			sprintf(nameSize, "GameSprite/Orange%d.png", i);
			orangeAnimation->addSpriteFrameWithFile(nameSize);
		}
		orangeAnimation->setDelayPerUnit(0.1f);
		orangeAnimation->setLoops(-1);
		auto orangeAnimate = Animate::create(orangeAnimation);
		enemyOrange->runAction(orangeAnimate);
	}
	if (enemyPink != NULL) {
		x = enemyPink->getPositionX(), y = enemyPink->getPositionY();
		enemyPink->removeFromParentAndCleanup(true);
		enemyPink = Sprite::create("sprite/pink1.png");
		enemyPink->setPosition(x, y);
		this->addChild(enemyPink, 1);

		auto pinkAnimation = Animation::create();
		for (int i = 1; i < 3; i++) {
			char nameSize[100] = { 0 };
			sprintf(nameSize, "GameSprite/Pink%d.png", i);
			pinkAnimation->addSpriteFrameWithFile(nameSize);
		}
		pinkAnimation->setDelayPerUnit(0.1f);
		pinkAnimation->setLoops(-1);
		auto pinkAnimate = Animate::create(pinkAnimation);
		enemyPink->runAction(pinkAnimate);
	}
	if (enemyRed != NULL) {
		x = enemyRed->getPositionX(), y = enemyRed->getPositionY();
		enemyRed->removeFromParentAndCleanup(true);
		enemyRed = Sprite::create("sprite/red1.png");
		enemyRed->setPosition(x, y);
		this->addChild(enemyRed, 1);

		auto redAnimation = Animation::create();
		for (int i = 1; i < 3; i++) {
			char nameSize[100] = { 0 };
			sprintf(nameSize, "GameSprite/Red%d.png", i);
			redAnimation->addSpriteFrameWithFile(nameSize);
		}
		redAnimation->setDelayPerUnit(0.1f);
		redAnimation->setLoops(-1);
		auto redAnimate = Animate::create(redAnimation);
		enemyRed->runAction(redAnimate);
	}
}
void MainGame::update(float f)
{
	if (issupered == false && (collide(player, enemyBlue) || collide(player, enemyOrange) || collide(player, enemyPink) || collide(player, enemyRed)))
		goToLosePage(NULL);
	else if (issupered == true && collide(player, enemyRed)) {
		enemyRed->removeFromParentAndCleanup(true);
		enemyRed = NULL;
	}
	else if (issupered == true && collide(player, enemyOrange)) {
		enemyOrange->removeFromParentAndCleanup(true);
		enemyOrange = NULL;
	}
	else if (issupered == true && collide(player, enemyBlue)) {
		enemyBlue->removeFromParentAndCleanup(true);
		enemyBlue = NULL;
	}
	else if (issupered == true && collide(player, enemyPink)) {
		enemyPink->removeFromParentAndCleanup(true);
		enemyPink = NULL;
	}
	if (collide(player, wall))
		goToLosePage(NULL);
	if (bigBean1 != NULL &&  collide(player, bigBean1)) {
		//this->removeChild(bigBean1);
		bigBean1->removeFromParentAndCleanup(true);
		bigBean1 = NULL;
		becomeSuper();
	}
	if (bigBean2 != NULL &&  collide(player, bigBean2)) {
		bigBean2->removeFromParentAndCleanup(true);
		bigBean2 = NULL;
		becomeSuper();
	}
	if (bigBean3 != NULL && collide(player, bigBean3)) {
		bigBean3->removeFromParentAndCleanup(true);
		bigBean3 = NULL;
		becomeSuper();
	}
	if (bigBean4 != NULL && collide(player, bigBean4)) {
		bigBean4->removeFromParentAndCleanup(true);
		bigBean4 = NULL;
		becomeSuper();
	}
	if (move == MOVE::LEFT && player->getPosition().x > origin.x + player->getContentSize().width / 2) {
		auto moveBy = MoveBy::create(0.1f, Vec2(-2, 0));
		player->runAction(moveBy);
	}
	else if (move == MOVE::RIGHT && player->getPosition().x < origin.x + visibleSize.width - player->getContentSize().width / 2) {
		auto moveBy = MoveBy::create(0.1f, Vec2(2, 0));
		player->runAction(moveBy);
	}
	else if (move == MOVE::UP && player->getPosition().x < origin.x + visibleSize.width - player->getContentSize().width / 2) {
		auto moveBy = MoveBy::create(0.1f, Vec2(0, 2));
		player->runAction(moveBy);
	}
	else if (move == MOVE::DOWN && player->getPosition().x < origin.x + visibleSize.width - player->getContentSize().width / 2) {
		auto moveBy = MoveBy::create(0.1f, Vec2(0, -2));
		player->runAction(moveBy);
	}

	for (auto bean = beans.begin(); bean != beans.end(); bean++) {
		if (collide(player, *bean)) {
			removeChild(*bean, true);
			beans.erase(bean);
			//removeAllChildrenWithCleanup(true);
			break;
		}
	}

	if (beans.size() == 0)
		goToWinPage(NULL);
}

bool MainGame::collide(Sprite *s1, Sprite *s2)
{
	if (s2 == NULL) return false;
	if (CCCircle(CCPoint(Vec2(s2->getPosition().x, s2->getPosition().y)), s2->getContentSize().width / 2 - 10).intersectsCircle(CCCircle(CCPoint(Vec2(s1->getPosition().x,
		s1->getPosition().y)), s1->getContentSize().height / 2 - 10)))
		return true;
	return false;
}

bool MainGame::collide(Sprite * s1, TMXObjectGroup * w)
{
	auto container = w->getObjects();

	for (auto obj : container) {
		ValueMap values = obj.asValueMap();
		int x = values.at("x").asInt();
		int y = values.at("y").asInt();
		int width = values.at("width").asInt();
		int height = values.at("height").asInt();
		if (Rect(p_x - wid / 2 + x, p_y - hei / 2 + y, width, height).intersectsCircle(Vec2(s1->getPosition().x,
			s1->getPosition().y), s1->getContentSize().height / 2 - 4)) {
			return true;
		}
	}

	return false;
}

void MainGame::goToLosePage(Ref *pSender) {
	_eventDispatcher->removeEventListener(keyboardListener);
	auto sceneLose = Lose::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, sceneLose, Color3B(0, 0, 0)));
}

void MainGame::goToWinPage(Ref *pSender) {
	_eventDispatcher->removeEventListener(keyboardListener);
	auto sceneWin = Win::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, sceneWin, Color3B(0, 0, 0)));
}

void MainGame::menuCloseCallback(Ref *pSender) {
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainGame::monsterMove(float f) {
	schedule(schedule_selector(MainGame::pinkMove), 0.01f, kRepeatForever, 0);
	schedule(schedule_selector(MainGame::orangeMove), 1.0f, kRepeatForever, 0);
	schedule(schedule_selector(MainGame::redMove), 0.01f, kRepeatForever, 0);
	schedule(schedule_selector(MainGame::blueMove), 0.01f, kRepeatForever, 0);
}

void MainGame::redMove(float f) {
	if (issupered) return;
	if (enemyRed == NULL) return;
	if (collide(enemyOrange, wall) && t_f) {
		t_f = false;
		enemyOrange->stopAllActions();
		o_x = -o_x, o_y = -o_y;
		if (num) {
			if (o_x < 0) {
				enemyOrange->setFlipY(false);
				enemyOrange->setRotation(90);
			}
			else {
				enemyOrange->setFlipY(false);
				enemyOrange->setRotation(-90);
			}
			auto move = MoveBy::create(0.2, Vec2(o_x, 0));
			enemyOrange->runAction(move);
		}
		else {
			if (o_y > 0) {
				enemyOrange->setRotation(0);
				enemyOrange->setFlipY(true);
			}
			else {
				enemyOrange->setRotation(0);
				enemyOrange->setFlipY(false);
			}
			auto move = MoveBy::create(0.2, Vec2(0, o_y));
			enemyOrange->runAction(move);
		}
	}
	if (enemyRed->getPositionX() > player->getPositionX() + 10) {
		if (true) {
			enemyRed->setFlipX(false);
			enemyRed->setRotation(0);
			enemyRed->setPositionX(enemyRed->getPositionX() - 1);
		}
	}
	else if (enemyRed->getPositionX() < player->getPositionX() - 10) {
		if (true) {
			enemyRed->setFlipX(true);
			enemyRed->setRotation(0);
			enemyRed->setPositionX(enemyRed->getPositionX() + 1);
		}
	}
	else if (enemyRed->getPositionY() < player->getPositionY()) {
		if (true) {
			enemyRed->setFlipX(false);
			enemyRed->setRotation(90);
			enemyRed->setPositionY(enemyRed->getPositionY() + 1);
		}
	}
	else if (enemyRed->getPositionY() > player->getPositionY()) {
		if (true) {
			enemyRed->setFlipX(false);
			enemyRed->setRotation(-90);
			enemyRed->setPositionY(enemyRed->getPositionY() - 1);
		}
	}
}
void MainGame::orangeMove(float f) {
	if (enemyOrange == NULL) return;
	if (issupered) return;
	t_f = true;
	o_x = -100 + rand() % 200, o_y = -100 + rand() % 200, num = rand() % 2;
	if (num) {
		if (o_x < 0) {
			enemyOrange->setFlipY(false);
			enemyOrange->setRotation(90);
		}
		else {
			enemyOrange->setFlipY(false);
			enemyOrange->setRotation(-90);
		}
		auto move = MoveBy::create(1, Vec2(o_x, 0));
		enemyOrange->runAction(move);
	}
	else {
		if (o_y > 0) {
			enemyOrange->setRotation(0);
			enemyOrange->setFlipY(true);
		}
		else {
			enemyOrange->setRotation(0);
			enemyOrange->setFlipY(false);
		}
		auto move = MoveBy::create(1, Vec2(0, o_y));
		enemyOrange->runAction(move);
	}
}

void MainGame::blueMove(float f) {
	if (enemyBlue == NULL) return;
	if (issupered) return;
	if (enemyBlue->getPositionX() > player->getPositionX() + 10) {
		if (true) {
			enemyBlue->setFlipY(false);
			enemyBlue->setRotation(90);
			enemyBlue->setPositionX(enemyBlue->getPositionX() - 1);
		}
	}
	else if (enemyBlue->getPositionX() < player->getPositionX() - 10) {
		if (true) {
			enemyBlue->setFlipY(false);
			enemyBlue->setRotation(-90);
			enemyBlue->setPositionX(enemyBlue->getPositionX() + 1);
		}
	}
	else if (enemyBlue->getPositionY() < player->getPositionY()) {
		if (true) {
			enemyBlue->setFlipY(true);
			enemyBlue->setRotation(0);
			enemyBlue->setPositionY(enemyBlue->getPositionY() + 1);
		}
	}
	else if (enemyBlue->getPositionY() > player->getPositionY()) {
		if (true) {
			enemyBlue->setFlipY(false);
			enemyBlue->setRotation(0);
			enemyBlue->setPositionY(enemyBlue->getPositionY() - 1);
		}
	}
}

void MainGame::pinkMove(float f) {
	if (enemyPink == NULL) return;
	if (issupered) return;
	int x, y;
	if (MOVE::RIGHT) {
		x = player->getPositionX() + 30;
		y = player->getPositionY();
	}
	else if (MOVE::DOWN) {
		x = player->getPositionX();
		y = player->getPositionY() - 30;
	}
	else if (MOVE::UP) {
		x = player->getPositionX();
		y = player->getPositionY() + 30;
	}
	else if (MOVE::LEFT) {
		x = player->getPositionX() - 30;
		y = player->getPositionY();
	}

	int pinkX = enemyPink->getPositionX(), pinkY = enemyPink->getPositionY();
	if (pinkX > x + 10) {
		enemyPink->setFlipX(true);
		enemyPink->setRotation(0);
		enemyPink->setPositionX(pinkX - 1);
	}
	else if (pinkX < x - 10) {
		enemyPink->setFlipX(false);
		enemyPink->setRotation(0);
		enemyPink->setPositionX(pinkX + 1);
	}
	else if (pinkY > y) {
		enemyPink->setFlipX(false);
		enemyPink->setRotation(90);
		enemyPink->setPositionY(pinkY - 1);
	}
	else if (pinkY < y) {
		enemyPink->setFlipX(false);
		enemyPink->setRotation(-90);
		enemyPink->setPositionY(pinkY + 1);
	}
}

