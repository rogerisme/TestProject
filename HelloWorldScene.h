#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "cocoa/CCObject.h"

#include "CCScheduler.h"
#include <math.h>
#include<stdlib.h>
#include "cocoa/CCArray.h"

NS_CC_BEGIN
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
private:
	void runSprite(CCObject* pSender);

	void runBackSprite(CCObject* pSender);

	void setFishRount(CCNode* fish,float d);
	void lineRoute(CCNode* fish,CCPoint from,CCPoint to,float time,int dir);
	void bezierRoute(CCNode* fish,CCPoint from,CCPoint to,float time,int dir);
	void moveEnd(CCNode* pSender);
	void updateFishMove();
};
NS_CC_END
#endif  // __HELLOWORLD_SCENE_H__