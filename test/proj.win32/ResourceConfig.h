#ifndef RESOURCE_CONFIG_H
#define RESOURCE_CONFIG_H

#include "CardConfig.h"
#include "cocos2d.h"
#include <string>

class ResourceConfig {
public:
    static std::string getCardFrontFilename(CardSuitType suit, CardFaceType face, bool isBig = true) {
        // 确定颜色
        CardColorType color = CCT_BLACK;
        if (suit == CST_HEARTS || suit == CST_DIAMONDS) {
            color = CCT_RED;
        }

        // 获取点数字符串
        std::string faceStr = getFaceString(face);

        // 构建文件名
        std::string sizePrefix = isBig ? "big" : "small";
        std::string colorStr = (color == CCT_BLACK) ? "black" : "red";

        return sizePrefix + "_" + colorStr + "_" + faceStr + ".png";
    }

    // 获取卡牌背面文件名
    static std::string getCardBackFilename() {
        return "card_back.png"; 
    }

    // 获取花色图标文件名
    static std::string getSuitIconFilename(CardSuitType suit) {
        switch (suit) {
        case CST_CLUBS:    return "_club.png";
        case CST_DIAMONDS: return "_diamond.png";
        case CST_HEARTS:   return "_heart.png";
        case CST_SPADES:   return "_spade.png";
        default:           return "";
        }
    }

    // 获取UI按钮资源
    static std::string getButtonFilename(const std::string& buttonName, bool pressed = false) {
        if (pressed) {
            return buttonName + "_pressed.png";
        }
        return buttonName + "_normal.png";
    }

    // 卡牌尺寸配置
    static constexpr int CARD_WIDTH = 120;
    static constexpr int CARD_HEIGHT = 180;
    static constexpr int CARD_SPACING = 20;

    // 屏幕布局
    static inline cocos2d::Vec2 getMainDeckPosition() {
        return cocos2d::Vec2(240, 320);
    }

    static inline cocos2d::Vec2 getBottomDeckPosition() {
        return cocos2d::Vec2(480, 320);
    }

    static inline cocos2d::Vec2 getReserveDeckPosition() {
        return cocos2d::Vec2(720, 320);
    }

    // 游戏规则配置
    static constexpr int MAX_UNDO_STEPS = 50;
    static constexpr int INITIAL_MAIN_CARDS = 10;
    static constexpr int CARD_SCORE = 10;

    // 匹配规则
    static inline bool canMatch(int card1Value, int card2Value) {
        return abs(card1Value - card2Value) == 1;
    }

private:
    static std::string getFaceString(CardFaceType face) {
        switch (face) {
        case CFT_ACE:   return "A";
        case CFT_TWO:   return "2";
        case CFT_THREE: return "3";
        case CFT_FOUR:  return "4";
        case CFT_FIVE:  return "5";
        case CFT_SIX:   return "6";
        case CFT_SEVEN: return "7";
        case CFT_EIGHT: return "8";
        case CFT_NINE:  return "9";
        case CFT_TEN:   return "10";
        case CFT_JACK:  return "J";
        case CFT_QUEEN: return "Q";
        case CFT_KING:  return "K";
        default:        return "?";
        }
    }
};

#endif // RESOURCE_CONFIG_H
