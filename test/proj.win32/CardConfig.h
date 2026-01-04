#ifndef CARD_CONFIG_H
#define CARD_CONFIG_H

// 花色类型
enum CardSuitType {
    CST_NONE = -1,
    CST_CLUBS,     // 梅花
    CST_DIAMONDS,  // 方块
    CST_HEARTS,    // 红桃
    CST_SPADES,    // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};

// 牌面类型
enum CardFaceType {
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

// 卡牌颜色
enum CardColorType {
    CCT_BLACK,
    CCT_RED
};

#endif // CARD_CONFIG_H
