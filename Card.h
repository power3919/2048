//
//  Card.h
//  2048
//
//  Created by student on 15/8/22.
//
//

#ifndef ___048__Card__
#define ___048__Card__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class Card :public Sprite
{
public:
    CREATE_FUNC(Card);
    virtual bool init();
    //CC_SYNTHESIZE(int, number, number);  //自动创建number方法
    static Card* createCard(int number,int wight,int height,float x,float y);
    void cardInit(int number,int wight,int height,float x,float y);
    int getNumber();
    void setNumber(int num);
    
    int number;  //卡片数字
    Label* labelCardNumber;    //显示数字
    LayerColor* layerColor;   //字体颜色
};

#endif /* defined(___048__Card__) */
