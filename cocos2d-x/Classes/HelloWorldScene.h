#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayer
{
    // Player sprite
    cocos2d::CCSprite* m_player;
    
    float m_speed;
    
    bool m_isPressedLeft;
    bool m_isPressedRight;
    
    cocos2d::CCSprite *m_leftItem;
    cocos2d::CCSprite *m_rightItem;
    // reference to all the target currently falling
    cocos2d::CCArray *m_targets;
    
    cocos2d::CCActionInterval* getAnimateFrameRange(int location, int len, float duration, bool pingPong, bool restoreOriginalFrame);
    
    void addTarget();

    void gameLogic(float dt);
    
    void updatePlayer(float dt);
    
    void updateGame(float dt);
    
    void playSwimAnimation();
    
    void playKickAnimation();
    
    const char *randomTargetName();
    
    void setupJoystick();
    
    void targetMoveFinished(CCNode* sender);
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // override touches related method...
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
