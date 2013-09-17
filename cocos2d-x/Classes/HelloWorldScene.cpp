#include "HelloWorldScene.h"

USING_NS_CC;

const int BCSwimAnimationTag = 1;
const float BCSwimAnimationTime = 0.25;

const int BCKickAnimationTag = 2;
const float BCKickAnimationTime = 0.5;



CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("background.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    // Create player sprite frames    
    CCSpriteBatchNode *playerBatchNode = CCSpriteBatchNode::create("octopus.png");
    
    this->addChild(playerBatchNode);

    // Save player sprite frames into cache 
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("octopus.plist");
    
    // Load the first frame as player default image
    m_player =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("octopus1.png"));
    
    

    // add the player sprite centered on the obottom of visible area
    m_player->setPosition(ccp(origin.x + visibleSize.width/2,
                                     m_player->getContentSize().height/2) );
    
    this->addChild(m_player);
    
    this->playSwimAnimation();
    
    // Enable touches for actions
    this->setTouchEnabled(true);
    
    this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    this->playKickAnimation();
}

void HelloWorld::gameLogic(float dt)
{
	this->addTarget();
}

const char *HelloWorld::randomTargetName()
{
    
    int i = ( rand() % 6) + (int)0;
    const char *name = "bubble_translucent.png";
    switch (i) {
        case 0:
            name = "bubble_blue.png";
            break;
        case 1:
            name = "bubble_green.png";
            break;
        case 2:
            name = "bubble_red.png";
            break;
        case 3:
            name = "bubble_yellow.png";
            break;
        case 4:
            name = "bubble_energy.png";
            break;
    }
    
    return name;
}

// cpp with cocos2d-x
void HelloWorld::addTarget()
{
    const char *name = this->randomTargetName();
	CCSprite *target = CCSprite::create(name, CCRectMake(0,0,32,32) );
    
	// Determine where to spawn the target along the X axis
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	float minX = target->getContentSize().width/2;
	float maxX = winSize.width -  target->getContentSize().width/2;
	int rangeX = (int)(maxX - minX);
	// srand( TimGetTicks() );
	int actualX = ( rand() % rangeX ) + (int)minX;
    
	// Create the target slightly off-screen along the top edge,
	// and along a random position along the X axis as calculated
	target->setPosition(ccp(CCDirector::sharedDirector()->getVisibleOrigin().x + actualX, winSize.height + (target->getContentSize().height/2)));
	this->addChild(target);
    
	// Determine speed of the target
	int minDuration = (int)3.0;
	int maxDuration = (int)6.0;
	int rangeDuration = maxDuration - minDuration;
	// srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration ) + minDuration;
    
	// Create the actions
	CCFiniteTimeAction* actionMove = CCMoveTo::create( (float)actualDuration,
                                                      ccp(actualX, 0 - target->getContentSize().height/2));

	target->runAction( CCSequence::create(actionMove, CCDelayTime::create(0.0), NULL) );
}

// Get CCActionInterval given a set of frames, duration, animation name...
CCActionInterval* HelloWorld::getAnimateFrameRange(int location, int len, float duration, bool pingPong, bool restoreOriginalFrame)
{
	CCArray* frames = new CCArray(len);
    frames->autorelease();
    
    // Buid sprite frames from names and indexes given the location and the len
    std::string spriteName = "octopus";
	for(int i = location; i < location + len; ++i) {
        std::ostringstream oss;
        oss << i;
        std::string frameName = spriteName + oss.str() + ".png";
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
        frames->addObject(frame);
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, duration/frames->count());
    animation->setRestoreOriginalFrame(restoreOriginalFrame);
    
	CCAnimate *animate = CCAnimate::create(animation);
    
    
	CCActionInterval *action = animate;
	
	if (pingPong)
		action = CCSequence::createWithTwoActions(animate, animate->reverse());
	
	return action;
}

void HelloWorld::playSwimAnimation()
{
    int location = 1;
    int length = 3;	
    bool isWalking = m_player->getActionByTag(BCSwimAnimationTag) != NULL;
    CCActionInterval* swimAction = NULL;    
    bool isKicking = m_player->getActionByTag(BCKickAnimationTag) != NULL;    
   
	
	if (!isWalking  && !isKicking) {
        // if is not already walking or kicking, create swim animation
        swimAction = this->getAnimateFrameRange(location, length, BCSwimAnimationTime, true, false);
		swimAction->setTag(BCSwimAnimationTag);
	} else {
        // if can't run the swim animation, just wait
        swimAction = CCDelayTime::create(BCSwimAnimationTime);
    }
    
    // first swim (or wait) and then call the playSwimAnimation selector again to generate a continuous loop...
    CCSequence* sequence = CCSequence::createWithTwoActions(swimAction, CCCallFunc::create(this, callfunc_selector(HelloWorld::playSwimAnimation)));
    
    m_player->runAction(sequence);
}

void HelloWorld::playKickAnimation(){
    m_player->stopActionByTag(BCSwimAnimationTag);
    
    CCActionInterval *animation = this->getAnimateFrameRange(4, 7, BCKickAnimationTime, false, true);
    animation->setTag(BCKickAnimationTag);
    
    m_player->runAction(animation);
}

