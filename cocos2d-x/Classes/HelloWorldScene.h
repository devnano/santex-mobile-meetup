#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
    // Player sprite
    cocos2d::CCSprite* m_player;
    
    cocos2d::CCActionInterval* getAnimateFrameRange(int location, int len, float duration, bool pingPong, bool restoreOriginalFrame);
    
    void playSwimAnimation();
    
    void playKickAnimation();
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // override touche related method...
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
