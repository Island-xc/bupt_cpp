#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene() { return HelloWorld::create(); }

bool HelloWorld::init() {
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 1. 背景颜色（让画面不那么单调）
    auto bg = LayerColor::create(Color4B(100, 150, 250, 255));
    this->addChild(bg, -1);

    // 2. 创建玩家（小球）
    _player = Sprite::create("ball_40.png");
    _player->setPosition(Vec2(visibleSize.width * 0.3f + origin.x, visibleSize.height / 2));
    _player->setScale(1.5f);
    this->addChild(_player, 2);

    // 3. 分数显示
    _scoreLabel = Label::createWithSystemFont("Score: 0", "Arial", 36);
    _scoreLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50));
    _scoreLabel->setTextColor(Color4B::WHITE);
    this->addChild(_scoreLabel, 10);

    // 4. 定时生成障碍物（每1.5秒一个）
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::spawnObstacle), 1.5f);

    // 5. 触摸和更新
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    this->scheduleUpdate();

    return true;
}

void HelloWorld::spawnObstacle(float dt) {
    if (_isGameOver) return;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float gap = 200.0f; // 上下障碍物的间隙大小
    float randY = (rand() % (int)(visibleSize.height / 2)) + visibleSize.height * 0.25f;

    // 创建一个容器装上下两个柱子
    auto container = Node::create();
    container->setPosition(Vec2(visibleSize.width + 100, 0));

    auto top = Sprite::create("HelloWorld.png");
    top->setAnchorPoint(Vec2(0.5, 0));
    top->setPosition(Vec2(0, randY + gap / 2));
    top->setScaleX(0.2f); // 把大图缩放成柱子形状

    auto bottom = Sprite::create("HelloWorld.png");
    bottom->setAnchorPoint(Vec2(0.5, 1));
    bottom->setPosition(Vec2(0, randY - gap / 2));
    bottom->setScaleX(0.2f);

    container->addChild(top);
    container->addChild(bottom);
    this->addChild(container);
    _obstacles.push_back(container);
}

void HelloWorld::update(float dt) {
    if (_isGameOver) return;

    // 1. 模拟重力
    _velocity -= 25.0f; // 重力加速度
    _player->setPositionY(_player->getPositionY() + _velocity * dt);

    // 2. 边界检测
    auto visibleSize = Director::getInstance()->getVisibleSize();
    if (_player->getPositionY() < 0 || _player->getPositionY() > visibleSize.height) {
        _isGameOver = true;
    }

    // 3. 障碍物移动与碰撞检测
    for (auto it = _obstacles.begin(); it != _obstacles.end(); ) {
        auto obs = *it;
        obs->setPositionX(obs->getPositionX() - 200 * dt); // 向左滚动

        // 简单的矩形碰撞检测
        Rect playerRect = _player->getBoundingBox();
        // 缩减判定范围，让游戏别太难
        playerRect.size.width *= 0.7f;
        playerRect.size.height *= 0.7f;

        for (auto child : obs->getChildren()) {
            // 将障碍物坐标转换为世界坐标进行比对
            Rect childRect = child->getBoundingBox();
            childRect.origin = obs->convertToWorldSpace(childRect.origin);
            if (playerRect.intersectsRect(childRect)) {
                _isGameOver = true;
            }
        }

        // 计分逻辑
        if (!_isGameOver && obs->getPositionX() < _player->getPositionX() && obs->getTag() != 100) {
            _score++;
            _scoreLabel->setString("Score: " + std::to_string(_score));
            obs->setTag(100); // 标记已计分
        }

        // 移除屏幕外的障碍物
        if (obs->getPositionX() < -200) {
            obs->removeFromParent();
            it = _obstacles.erase(it);
        }
        else {
            ++it;
        }
    }

    if (_isGameOver) {
        auto label = Label::createWithSystemFont("GAME OVER\nClick to Restart", "Arial", 48);
        label->setPosition(visibleSize / 2);
        label->setAlignment(TextHAlignment::CENTER);
        this->addChild(label, 20);
        this->unscheduleAllCallbacks();
    }
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
    if (_isGameOver) {
        Director::getInstance()->replaceScene(HelloWorld::createScene());
        return true;
    }
    _velocity = 450.0f; // 点击向上跳跃的速度
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender) { Director::getInstance()->end(); }