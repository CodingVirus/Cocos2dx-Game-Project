/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

USING_NS_CC;

Vec2 velocity = Vec2::ZERO;

float movementSpeed = 0.0f;
int direction = 1;

Sprite* blue;
bool isKeyPressed = false;
float gravity = 2.0f;

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
    downSpeed = 0.0f;

    if ( !Scene::init() )
    {
        return false;
    }

    auto isMoving = false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto map = TMXTiledMap::create("package01.tmx");
    map->setName("Map");
    addChild(map);
    //map->runAction(RepeatForever::create(MoveBy::create(0.3f, Vec2(-16, 0))));

    /*auto touchEvent = EventListenerTouchOneByOne::create();
    touchEvent->onTouchBegan = [=](Touch* touch, Event* event)
    {
        return true;
    };
    touchEvent->onTouchEnded = [=](Touch* touch, Event* event)
    {
        blue->runAction(MoveBy::create(0.3f, Vec2(16, 0)));
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchEvent, this);*/

    Vector<SpriteFrame*> frames;
    frames.pushBack(SpriteFrame::create("charanim/player_idle1.png", Rect(0, 0, 56, 48)));
    frames.pushBack(SpriteFrame::create("charanim/player_idle2.png", Rect(0, 0, 56, 48)));
    frames.pushBack(SpriteFrame::create("charanim/player_idle3.png", Rect(0, 0, 56, 48)));
    frames.pushBack(SpriteFrame::create("charanim/player_idle4.png", Rect(0, 0, 56, 48)));
    frames.pushBack(SpriteFrame::create("charanim/player_idle5.png", Rect(0, 0, 56, 48)));
    frames.pushBack(SpriteFrame::create("charanim/player_idle6.png", Rect(0, 0, 56, 48)));

    for (auto frame : frames)
    {
        frame->getTexture()->setAliasTexParameters();
    }

    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
    // Animate 积己
    auto animate = Animate::create(animation);
   
    // Sprite俊 局聪皋捞记 咀记 利侩
    blue = Sprite::create("charanim/player_idle1.png");
    blue->getTexture()->setAliasTexParameters();
    blue->setPosition(130, 60);
    blue->setAnchorPoint(Vec2(0.5f, 0.15f));
    addChild(blue);

    auto repeatForever = RepeatForever::create(animate);
    blue->runAction(repeatForever);

    auto followTheSprite = Follow::createWithOffset(blue, -20.0f, -60.0f);
    this->runAction(followTheSprite);

    /*blue->schedule([=](float dt)
        {
            
            blue->setPosition(blue->getPosition() + Vec2(0, downSpeed));
            if (blue->getPosition().y < 0)
                downSpeed = 0.0f;
            else
                downSpeed -= 0.5f;

            auto groundLayer = map->getLayer("Ground");
            auto pos = blue->getPosition();
            auto tileSize = map->getTileSize();

            int tileX = (int)((pos.x - map->getPosition().x) / tileSize.width);
            int tileY = (int)((map->getContentSize().height - pos.y + map->getPosition().y) / tileSize.height);

            if ((0 <= tileX && tileX < map->getMapSize().width) && (0 <= tileY && tileY < map->getMapSize().height))
            {
                auto gid = groundLayer->getTileGIDAt(Vec2(tileX, tileY));
                if (gid >= 1)
                {
                    downSpeed = 0.0f;
                }
            }
        }, "BLUE");*/

    auto reddot = Sprite::create("reddot.png");
    reddot->setPosition(blue->getPosition());
    reddot->getTexture()->setAliasTexParameters();
    addChild(reddot, 1);

    reddot->schedule([=](float dt) {
        reddot->setPosition(blue->getPosition());
        }, "REDDOT");

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            isKeyPressed = true;
            direction = 1;
            log(movementSpeed);
            blue->setScaleX(1);
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            isKeyPressed = true;
            direction = -1;;
            blue->setScaleX(-1);
            break;
        case EventKeyboard::KeyCode::KEY_SPACE:
            blue->runAction(MoveBy::create(0.3f, Vec2(0, 50))); 

        default:
            break;
        }
        //blue->runAction(RepeatForever::create(MoveBy::create(0.3f, Vec2(-16, 0))));
    };

    keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            isKeyPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            isKeyPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_SPACE:          

        default:
            break;
        }
        //blue->runAction(RepeatForever::create(MoveBy::create(0.3f, Vec2(-16, 0))));
        //blue->setPosition(Vec2(movementSpeed, 0));
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    this->getScheduler()->scheduleUpdate(this, 0, false);

    return true;
}


void HelloWorld::update(float delta)
{
    
    if (isKeyPressed == false)
        movementSpeed = 0;  
    else
        movementSpeed = 2.0f;

    blue->setPosition(blue->getPosition() + Vec2(movementSpeed * direction, -gravity));
}

