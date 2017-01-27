#include "HelloWorldScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

HelloWorld::~HelloWorld()
{
	physicsManager->GetWorld()->DestroyBody(body);
	delete physicsManager;
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
	scene->addChild(layer);

	layer->scheduleUpdate();
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Layer::init()) return false;

	physicsManager = new PhysicsManager();

	{
		Vec2 pos(Director::getInstance()->getWinSize().width / 2 - 150, Director::getInstance()->getWinSize().height / 2);
		Vec2 pos2(Director::getInstance()->getWinSize().width / 2 + 150, Director::getInstance()->getWinSize().height / 2);

		b2BodyDef bodyDef;
		bodyDef.fixedRotation = true;
		bodyDef.type = b2_dynamicBody;
		body = physicsManager->GetWorld()->CreateBody(&bodyDef);
		body->SetGravityScale(2);
		body->SetTransform(b2Vec2(pos.x / SCALE_RATIO, pos.y / SCALE_RATIO), body->GetAngle());

		body2 = physicsManager->GetWorld()->CreateBody(&bodyDef);
		body2->SetGravityScale(2.5f);
		body2->SetTransform(b2Vec2(pos2.x / SCALE_RATIO, pos2.y / SCALE_RATIO), body->GetAngle());

		Vec2 size = Vec2(50, 50);
		b2FixtureDef fixDef;
		b2PolygonShape shape;
		fixDef.restitution = 0.2f;
		fixDef.shape = &shape;
		shape.SetAsBox(size.x / SCALE_RATIO, size.y / SCALE_RATIO);

		fixDef.restitution = 1.0f;

		body->CreateFixture(&fixDef);

		body2->CreateFixture(&fixDef);
	}

	{
		Vec2 pos(Director::getInstance()->getWinSize().width / 2, 
			Director::getInstance()->getWinSize().height / 2 - 200);
		b2BodyDef bodyDef;
		bodyDef.fixedRotation = true;
		bodyDef.type = b2_staticBody;

		groundBody = physicsManager->GetWorld()->CreateBody(&bodyDef);
		groundBody->SetTransform(b2Vec2(pos.x / SCALE_RATIO, pos.y / SCALE_RATIO), groundBody->GetAngle());

		Vec2 size = Vec2(300, 50);
		b2FixtureDef fixDef;
		b2PolygonShape shape;
		fixDef.restitution = 0.2f;
		fixDef.shape = &shape;
		shape.SetAsBox(size.x / SCALE_RATIO, size.y / SCALE_RATIO);

		groundBody->CreateFixture(&fixDef);
	}

    return true;
}

void HelloWorld::update(float dt)
{
	physicsManager->Update();
}

void HelloWorld::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	physicsManager->RenderDebug();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
