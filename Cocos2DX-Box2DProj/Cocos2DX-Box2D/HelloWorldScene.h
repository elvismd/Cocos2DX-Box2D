#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <PhysicsManager.h>

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
	PhysicsManager* physicsManager;
	b2Body* body;
	b2Body* body2;
	b2Body* groundBody;

public:
	~HelloWorld();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void update(float dt);
	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
