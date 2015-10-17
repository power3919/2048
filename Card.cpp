//
//  Card.cpp
//  2048
//
//  Created by student on 15/8/22.
//
//

#include "Card.h"

//通过此方法来调用初始化卡片
Card* Card::createCard(int number,int wight,int height,float x,float y)
{
   
    auto c = new(std::nothrow) Card();
    
       c->cardInit(number, wight, height, x, y);
        
        return c;
    
}

void Card::cardInit(int number,int wight,int height,float x,float y)
{
    this->number = number;
    layerColor = LayerColor::create(Color4B(255, 230, 200, 250), wight-15, height-15);
    layerColor->setPosition(x, y);
    
    if (number>0) {
        auto s = __String::createWithFormat("%d",number);
        labelCardNumber = Label::createWithSystemFont(s->getCString(), "fonts/arial.ttf", 100);
        labelCardNumber->setPosition(layerColor->getContentSize().width/2,layerColor->getContentSize().height/2);
        layerColor->addChild(labelCardNumber);
    }else{
        labelCardNumber = Label::createWithSystemFont("", "fonts/arial.ttf", 100);
        labelCardNumber->setPosition(layerColor->getContentSize().width/2,layerColor->getContentSize().height/2);
        layerColor->addChild(labelCardNumber);
    }
    addChild(layerColor);

}

int Card::getNumber()
{
    return number;
}

bool Card::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    return true;
}


void Card::setNumber(int num)
{
    number = num;
    if (number > 0) {
        labelCardNumber->setString(__String::createWithFormat("%d",number)->getCString());//转型成字符串
        labelCardNumber->setColor(Color3B::MAGENTA);
        labelCardNumber->enableGlow(Color4B(255, 0, 0, 255));//设置荧光效果
    }else{
        labelCardNumber->setString("");
    }
    
    //设置不同字体的大小
    if (num >= 0) {
        labelCardNumber->setSystemFontSize(100);
    }
    if (num >= 16) {
        labelCardNumber->setSystemFontSize(90);
    }
    if (num >= 128) {
        labelCardNumber->setSystemFontSize(60);
    }
    if (num >= 1024) {
        labelCardNumber->setSystemFontSize(40);
    }
    
    //设置不同数字的颜色
    if (number == 0) {
        layerColor->setColor(Color3B(255,230,200));
    }
    if (number == 2) {
        layerColor->setColor(Color3B(240,230,220));
    }
    if (number == 4) {
        layerColor->setColor(Color3B(240,220,200));
    }
    if (number == 8) {
        layerColor->setColor(Color3B(240,180,200));
    }
    if (number == 16) {
        layerColor->setColor(Color3B(240,140,120));
    }
    if (number == 32) {
        layerColor->setColor(Color3B(240,120,90));
    }
    if (number == 64) {
        layerColor->setColor(Color3B(240,90,60));
    }
    if (number == 128) {
        layerColor->setColor(Color3B(240,90,60));
    }
    if (number == 256) {
        layerColor->setColor(Color3B(240,200,70));
    }
    if (number == 1024) {
        layerColor->setColor(Color3B(0,130,0));
    }
    if (number == 2048) {
        layerColor->setColor(Color3B(0,130,0));
    }
    
    
}

