#include "HelloWorldScene.h"
#include "SecondScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        //CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
     //   CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
      //  CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
      //  pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
     //   this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));
		//UILayer* ul =UILayer::create();
		//ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("UIEditorTest_1.json"));


        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

		//

		CCSprite* pSprite2 = CCSprite::create("assist_box_friend.png");
		CC_BREAK_IF(! pSprite2);
		pSprite2->setPosition(ccp(20,size.height/2));
		this->addChild(pSprite2,100,1);

		//

		//
		CCMenuItemImage *runItem = CCMenuItemImage::create(
            "npc_dialog_nromal.png",
            "npc_dialog_selected.png",
            this,
            menu_selector(HelloWorld::runSprite));
        CC_BREAK_IF(! runItem);

        // Place the menu item bottom-right conner.
        runItem->setPosition(ccp(80, 200));

		//
		CCMenuItemImage *runItem2 = CCMenuItemImage::create(
            "login_normal.png",
            "login_selected.png",
            this,
            menu_selector(HelloWorld::runBackSprite));
        CC_BREAK_IF(! runItem2);
        runItem2->setPosition(ccp(80, 260));

	/*	CCMenuItemImage *runItem3 = CCMenuItemImage::create(
            "login_normal.png",
            "login_selected.png",
            this,
            menu_selector(HelloWorld::setFishRount));
        CC_BREAK_IF(! runItem3);
        runItem3->setPosition(ccp(80, 150));*/
		
		CCArray* seqItem = CCArray::create();
		seqItem->addObject(runItem);
		seqItem->addObject(runItem2);
		//seqItem->addObject(runItem3);
		CCMenu* rMenu2 = CCMenu::createWithArray(seqItem);
        rMenu2->setPosition(CCPointZero);
        CC_BREAK_IF(! rMenu2);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(rMenu2, 3);
		bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::runSprite(CCObject* pSender)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCNode* m_sprite = CCNode::create();
	m_sprite =this->getChildByTag(1);

	//CCFiniteTimeAction* placeAction = CCPlace::create(ccp(100,100));
	ccBezierConfig bezier;
	bezier.controlPoint_1 = ccp(20,150);
	bezier.controlPoint_2 = ccp(200,30);
	bezier.endPosition = ccp(60,30);

	CCFiniteTimeAction* baziAction = CCBezierTo::create(0.8,bezier);
	CCFiniteTimeAction* moveAction = CCMoveTo::create(1.0f,ccp(size.width,size.height/2 - 30));
	
	CCAction *action = CCSequence::create(baziAction,moveAction,moveAction->reverse(),NULL);
	m_sprite->runAction(action);
}

void HelloWorld::runBackSprite(CCObject* pSender)
{
	/*CCNode* m_sprite = CCNode::create();
	m_sprite =this->getChildByTag(1);*/
	/*CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCAction *action = CCMoveTo::create(1.0f,ccp(20,size.height/2));
	m_sprite->runAction(action);*/

	//setFishRount(m_sprite,3);
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCScene *pScene = SecondScene::scene();
	pDirector->replaceScene(CCTransitionFlipX::create(2,pScene));
}

void HelloWorld::setFishRount(CCNode* fish,float d)
{
	int direction = abs(rand()%2);
	int route = abs(rand()%2);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int height = size.height;
	int fromPot_y = abs(rand()%height);
	if (route == 0 )
	{
		lineRoute(fish,ccp(10,fromPot_y),ccp(size.width+10,fromPot_y),d,direction);
	}
	else
	{
		bezierRoute(fish,ccp(10,fromPot_y),ccp(size.width+10,fromPot_y),d,direction);
	}
}

void HelloWorld:: lineRoute(CCNode* fish,CCPoint from,CCPoint to,float time,int dir)
{
	((CCSprite*)fish)->setFlipX(dir);
	fish->setPosition(from);
	CCMoveTo* moveAction = CCMoveTo::create(time,to);
	CCCallFuncN *end = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::moveEnd));
	CCAction *action = CCSequence::create(moveAction,end,NULL);
	((CCSprite*)fish)->runAction(action);
};
void HelloWorld:: bezierRoute(CCNode* fish,CCPoint from,CCPoint to,float time,int dir)
{
	((CCSprite*)fish)->setFlipX(dir);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float h[] = {55.0f,size.height - 10.0f};
	float r[] = {(h[1] - h[0])/2,-(h[1] - h[0])/2};
	ccBezierConfig bezier1,bezier2;
	bezier1.controlPoint_1 = ccp(size.width/2 + r[!dir]/3,h[dir]);
	bezier1.controlPoint_2 = ccp(size.width/2 + r[!dir]/3,h[dir]);
	bezier1.endPosition = ccp(size.width/2,h[0]+r[0]);

	bezier2.controlPoint_1 = ccp(size.width/2 + r[!dir]/3,h[dir]);
	bezier2.controlPoint_2 = ccp(size.width/2 + r[!dir]/3,h[dir]);
	bezier2.endPosition = ccp(size.width/2+r[dir],h[!dir]);
	CCCallFuncN *end = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::moveEnd));
	CCFiniteTimeAction* move =  CCSequence::create(
		CCMoveTo::create(time/4,ccp(size.width/2 + r[!dir],h[dir])),
		CCBezierTo::create(time/4,bezier1),
		CCBezierTo::create(time/4,bezier2),
		CCMoveTo::create(time/4,to),
		NULL,
		end);
	CCAction *action = CCSequence::create(move,end,NULL);
	((CCSprite*)fish)->runAction(action);
};
void HelloWorld::moveEnd(CCNode* pSender)
{
	this->setFishRount(dynamic_cast<CCSprite*>(pSender),5);
};

void HelloWorld::updateFishMove()
{
	/*CCSprite* fish = NULL;
	CCARRAY_FOREACH(_fishs,fish)
	{
		this->setFishRount(fish,0.5);
	}*/
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

