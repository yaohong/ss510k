#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);

    virtual void onTouchMoved(Touch *touch, Event *unused_event);

    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    Sprite *pk;
    
    
    bool isSelect;
};

#endif // __HELLOWORLD_SCENE_H__
