#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "./base/CCEventListenerTouch.h"
#include "pb/test.pb.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    test::foo foo;
    foo.set_id(1);
    std::string buff;
    if (!foo.SerializeToString(&buff))
    {
        exit(-1);
    }

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    
    
    pk = Sprite::create("Cards/kb_0_1-hd.png");
    //pk->setAnchorPoint(Vec2(0, 0));
    pk->setPosition(origin.x + pk->getContentSize().width/2, origin.y + pk->getContentSize().height/2);
    addChild(pk, 1);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    //touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    //listener->on
    
    isSelect = false;
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    if (pk->getBoundingBox().containsPoint(touch->getLocation()))
    {
        //Vec2 origin = Director::getInstance()->getVisibleOrigin();
        isSelect = true;
    }
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{

        //Vec2 origin = Director::getInstance()->getVisibleOrigin();
        //Vec2 old = pk->getPosition();
    if (isSelect)
    {
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto visibleSize = Director::getInstance()->getVisibleSize();
        //监测是否超出屏幕范围
        float moveX = 0.0f;
        float moveY = 0.0f;
        auto rect = pk->getBoundingBox();
        if (rect.size.width/2 + (touch->getLocation().x - origin.x) > visibleSize.width)
        {
            //右边超出
            moveX = visibleSize.width - rect.size.width/2 + origin.x;
        } else if ((touch->getLocation().x - origin.x) - rect.size.width/2 < 0)
        {
            //左边超出
            //moveX = touch->getLocation().x + (rect.size.width/2 - touch->getLocation().x);
            moveX = rect.size.width/2 + origin.x;
        } else
        {
            moveX = touch->getLocation().x;
        }
        
        if (rect.size.height/2 + (touch->getLocation().y - origin.y) > visibleSize.height)
        {
            //上面超出
            moveY = visibleSize.height - rect.size.height/2 + origin.y;
        }
        else if ((touch->getLocation().y - origin.y) - rect.size.height/2 < 0)
        {
            moveY = rect.size.height/2 + origin.y;
        } else
        {
            moveY = touch->getLocation().y;
        }
        pk->setPosition(moveX, moveY);
    }

}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    isSelect = false;
}
