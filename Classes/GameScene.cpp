#include "GameScene.h"
#include "SparseMatrix.h"
#include "GameTile.h"
#include "KeyboardControl.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	
	// Mouse stuff
	auto mouseListener = EventListenerMouse::create();
	mouseListener->setEnabled(true);
	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	mouseListener->onMouseScroll = [](Event* event) {
		auto e = (EventMouse*)event;
		CCLOG("Mouse Scroll detected, X: %f, Y: %f", e->getScrollX(), e->getScrollY());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	// Initialize the control to be the keyboard
	_control.reset(new KeyboardControl(this));

	// Turn on scheduler
	this->scheduleUpdate();

	// Create the player
	// Sprite will be created in a factory method:
	auto playerSprite = Sprite::create("player.png");
	this->addChild(playerSprite);
	_player.reset(new ActiveObject(playerSprite, Size(defs::SIZE, defs::SIZE * 2), Point(100,100)));





    return true;
}

void GameScene::update(float dt)
{
	CCLOG("update dt=%f", dt);
	if (_control->isKeyPressed(Control::LEFT)) {
		_player->setVelocity(Point(4, 0));
		//this->setPositionX(this->getPositionX() - 1);
	} else if (_control->isKeyPressed(Control::RIGHT)) {
		_player->setVelocity(Point(-4, 0));
		//this->setPositionX(this->getPositionX() + 1);
	}
	_player->update();
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameScene::addTile(IJ ij, GameTile::Type type, int time)
{
	GameTile t(ij, type, time, this);
	_level.setAt(ij, t);
}

void GameScene::removeTile(IJ ij)
{
	GameTile t = _level.getAt(ij);
	t.destroy();
	_level.delAt(ij);
}

void GameScene::onMouseDown(cocos2d::Event *event)
{
	EventMouse* e = (EventMouse*)event;
	CCLOG("Mouse Down detected, Key: %d", e->getMouseButton());

	IJ ij = IJ::fromPoint(e->getCursorX(), e->getCursorY() + this->getBoundingBox().size.height);
	CCLOG("IJ: %d, %d", ij.i, ij.j);
	if (!_level.hasAt(ij)) {
		addTile(ij, GameTile::SOLID, 10);
	} else {
		removeTile(ij);
	}
}