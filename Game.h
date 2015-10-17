//
//  Game.h
//  2048
//
//  Created by student on 15/8/22.
//
//

#ifndef ___048__Game__
#define ___048__Game__

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Card.h"
USING_NS_CC;
using namespace cocos2d;
using namespace ui;

class Game:public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Game);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
   
    
    void createCard();
    void createCardNumber();
    bool left();
    bool right();
    bool up();
    bool down();
    void gameOver();
    void restart();
    
    
    int score ;
    Card* arr[4][4];
    float beginX;
    float beginY;
    float endX;
    float endY;
    bool move = false;
    bool over=false;
    Label* scoreLabel;
};



#endif /* defined(___048__Game__) */
