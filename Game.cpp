//
//  Game.cpp
//  2048
//
//  Created by student on 15/8/22.
//
//

#include "Game.h"


Scene* Game::createScene()
{
    auto scene = Scene::create();
    auto layer = Game::create();
    scene->addChild(layer);
    return scene;
}

bool Game::init()
{
    if (!Layer::init()) {
        return false;
    }
    auto size = Director::getInstance()->getVisibleSize();
    
    auto layerColor = LayerColor::create(Color4B(200, 150, 100, 200));
    addChild(layerColor);
    
    //标题
    auto titleLabel = Label::createWithTTF("2048 Game","fonts/Marker Felt.ttf",70);
    titleLabel->setColor(Color3B(200, 250, 100));
    titleLabel->setPosition(Vec2(size.width/2,size.height/2+550));
    auto letter = titleLabel->getLetter(1);
    auto letter1 = titleLabel->getLetter(3);
    auto rote = RepeatForever::create(RotateBy::create(1, 180));
    auto rote1 = RepeatForever::create(RotateBy::create(1, 180));
    letter->runAction(rote);
    letter1->runAction(rote1);//设置字体旋转
    addChild(titleLabel);
    
    auto Label = Label::createWithTTF("score:", "fonts/arial.ttf", 50);
    Label->setColor(Color3B::BLUE);
    Label->setPosition(Vec2(80,size.height/2+450));
    addChild(Label);
    
    char t[10];
    score=0;
    sprintf(t,"%d",score);
    scoreLabel = Label::createWithTTF(t, "fonts/Marker Felt.ttf", 40);
    scoreLabel->setColor(Color3B::BLUE);
    scoreLabel->setPosition(Vec2(170,size.height/2+450));
    addChild(scoreLabel);
    
    auto newGame = Label::createWithTTF("new Game", "fonts/Marker Felt.ttf",50);
    newGame->setColor(Color3B::GRAY);
    newGame->setPosition(Vec2(110,size.height/2+380));
    addChild(newGame);
    
    auto bt = Button::create("buttonreplay.png");
    bt->setPosition(Vec2(260,size.height/2+380));
    bt->addClickEventListener(CC_CALLBACK_0(Game::restart, this));
    addChild(bt);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan=CC_CALLBACK_2(Game::onTouchBegan, this)
    ;
    listener->onTouchEnded=CC_CALLBACK_2(Game::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    createCard();
    createCardNumber();
    createCardNumber();
    return true;
}

//创建小方格
void Game::createCard()
{
    auto size = Director::getInstance()->getVisibleSize();
    auto cardSize = (size.height-288)/6;
    for (int i = 0; i<4; i++) {
        for (int j = 0; j<4; j++) {
            Card* card = Card::createCard(0, cardSize, cardSize, cardSize*i+30, cardSize*j+size.height/3-300);
        arr[i][j] = card;
        this->addChild(card);
        }

    }
}

void Game::createCardNumber()
{
    int i = CCRANDOM_0_1()*4;
    int j = CCRANDOM_0_1()*4;
    if (arr[i][j] -> getNumber() > 0) {//如果有卡片就不需要创建
        createCardNumber();
    }
    else{//没有卡片就再创建
        arr[i][j]->setNumber(CCRANDOM_0_1()*10<1 ? 4:2);
    }
}

bool Game::onTouchBegan(Touch *touch, Event *unused_event)
{
    Point beginTouch = touch->getLocation();
    beginX = beginTouch.x;
    beginY = beginTouch.y;
    return true;
}

void Game::onTouchEnded(Touch* touch, Event* unused_event)
{
    Point endTouch = touch->getLocation();
    endX = beginX-endTouch.x;
    endY = beginY-endTouch.y;
    
    if (abs(endX) > abs(endY)) {
        if(endX + 5>0){
        if (left()) {
           createCardNumber();
           gameOver();
           }
        }else
        {
            if (right()) {
                createCardNumber();
                gameOver();
            }
        }
    }else if (abs(endX)<abs(endY)){
        if (endY+5>0) {
            if (down()) {
                createCardNumber();
                gameOver();
            }
        }else{
            if (up()) {
                createCardNumber();
                gameOver();
            }
        }
    }
   
}

//往左移
bool Game::left()
{ log("left");
    bool move = false;
    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            for (int x1=x+1; x1<4; x1++) {
                if (arr[x1][y]->getNumber()>0) {
                    if(arr[x][y]->getNumber()<=0){
                    //前后数字交换
                    arr[x][y]->setNumber(arr[x1][y]->getNumber());
                    arr[x1][y]->setNumber(0);
                    x--;
                    move = true;
                }else if (arr[x][y]->getNumber() == arr[x1][y]->getNumber())
                {
                    arr[x][y]->setNumber((arr[x][y]->getNumber())*2);
                    arr[x1][y]->setNumber(0);
                    score+=arr[x][y]->getNumber();
                    auto s = __String::createWithFormat("%d",score);
                    scoreLabel->setString(s->getCString());
                    move = true;
                }
                break;
              }
           }
       }
    }
    return  move;
}

bool Game::right()
{  log("right");
    bool move = false;
    for (int y=0; y<4; y++) {
        for (int x=3; x>=0; x--) {
            for (int x1=x-1; x1>0; x1--) {
                if (arr[x1][y]->getNumber()>0) {
                    if (arr[x][y]->getNumber()<=0) {
                        arr[x][y]->setNumber(arr[x1][y]->getNumber());
                        arr[x1][y]->setNumber(0);
                        x++;
                        move=true;
                    }else if (arr[x][y]->getNumber()==arr[x1][y]->getNumber()){
                        arr[x][y]->setNumber((arr[x][y]->getNumber())*2);
                        arr[x1][y]->setNumber(0);
                        
                        score+=arr[x][y]->getNumber();
                        
                        auto s = __String::createWithFormat("%d",score);
                        scoreLabel->setString(s->getCString());
                        move = true;
                    }
                    break;
                }
            }
        }
    }
    return move;
}

bool Game::up()
{
    bool move=false;
    for (int x=0; x<4; x++) {
        for (int y=3; y>=0; y--) {
            for (int y1=y-1; y1>=0; y1--) {
                if (arr[x][y1]->getNumber()>0) {
                    if (arr[x][y]->getNumber()<=0) {
                        arr[x][y]->setNumber(arr[x][y1]->getNumber());
                        arr[x][y1]->setNumber(0);
                        y++;
                        move= true;
                    }else if(arr[x][y]->getNumber() == arr[x][y1]->getNumber())
                    {
                        arr[x][y]->setNumber((arr[x][y]->getNumber())*2);
                        arr[x][y1]->setNumber(0);
                        score += arr[x][y]->getNumber();
                        auto s= __String::createWithFormat("%d",score);
                        scoreLabel->setString(s->getCString());
                        move=true;
                    }
                    break;
                }
            }
        }
    }
    return move;
}

bool Game::down()
{
    bool move=false;
    for (int x=0; x<4; x++) {
        for (int y=0; y<4; y++) {
            for (int y1=y+1; y1<4; y1++) {
                if (arr[x][y1]->getNumber()>0) {
                    if (arr[x][y]->getNumber()<=0) {
                        arr[x][y]->setNumber(arr[x][y1]->getNumber());
                        arr[x][y1]->setNumber(0);
                        y++;
                        move= true;
                    }else if(arr[x][y]->getNumber() == arr[x][y1]->getNumber())
                    {
                        arr[x][y]->setNumber((arr[x][y]->getNumber())*2);
                        arr[x][y1]->setNumber(0);
                        score += arr[x][y]->getNumber();
                        auto s= __String::createWithFormat("%d",score);
                        scoreLabel->setString(s->getCString());
                        move=true;
                    }
                    break;
                }
            }
        }
    }
    return move;
}

void Game::gameOver()
{
    bool over=true;
    for (int y=0; y<=3; y++) {
        for (int x=0; x<=3; x++) {
            if (arr[x][y]->getNumber()==0 ||
                (x>0 && (arr[x][y]->getNumber() == arr[x-1][y]->getNumber())) ||
                (x<3 && (arr[x][y]->getNumber() == arr[x+1][y]->getNumber()))  ||
                (y>0 && (arr[x][y]->getNumber() == arr[x][y-1]->getNumber()))  ||
                (y<3 && (arr[x][y]->getNumber() == arr[x][y+1]->getNumber()))
                )
            {
                over = false;
            }
        }
        
        
        }
    if (over) {
            MessageBox("游戏完毕", "游戏完毕");
    }
}

void Game::restart()
{
    Director::getInstance()->replaceScene(TransitionFadeDown::create(0.3, Game::createScene()));
}
