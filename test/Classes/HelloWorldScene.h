#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>

class HelloWorld : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float dt) override;
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);

private:
    cocos2d::Sprite* _player;
    cocos2d::Label* _scoreLabel;
    std::vector<cocos2d::Node*> _obstacles;
    float _velocity = 0; // 小球下落速度
    int _score = 0;
    bool _isGameOver = false;
    void spawnObstacle(float dt); // 定时生成障碍物
};

#endif