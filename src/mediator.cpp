#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
/*
*中介者模式：行为设计模式，能减少对象之间混乱无序的依赖关系。该模式会限制对象之间的直接交互，迫使它们通过一个中介者对象进行合作；
（典型的如租房时，房东，中介，你）
*优点：单一职责；开闭原则；减轻应用中多个组件间的耦合情况；更方便地复用各个组件；
*缺点：一段时间后，中介者可能会演化成为上帝对象，即需要管理的对象与关系太过复杂；
*/
/*
1.抽象一个中介者类：定义对象到中介者对象的接口；
2.提供一个具体中介者类：实现抽象接口，并且实现关联类数据处理；
3.提供一个关联类的抽象基类：多个关联类之间的交互操作的抽象；
4.提供一个或多个具体的关联类：实现抽象，通过中介者类完成操作；
*/
//三平台通信
enum class Message : char{
    ATW_MESSAGE,    //app->win
    ATM_MESSAGE,    //app->Mac
    WIM_MESSAGE     //WIN->Mac
};
class AbstractMoudle;
class AbstractMediator{
public:
    virtual ~AbstractMediator(){}
    virtual void transmit(Message msg,AbstractMoudle* ptr)=0;
};


class AbstractMoudle{
public:
    AbstractMoudle(AbstractMediator* ptr) : m_mediator(ptr) {}
    void sendMsg(Message msg){
        m_mediator->transmit(msg,this);
    }
    virtual void acceptMsg(Message msg)=0;
protected:
    AbstractMediator* m_mediator=nullptr;
};
class App : public AbstractMoudle{
public:
    App(AbstractMediator* ptr) : AbstractMoudle(ptr){}
    void acceptMsg(Message msg) override {
        switch (msg)
        {
        case Message::ATM_MESSAGE :
            std::cout<<"Mac to app"<<std::endl;
            break;
        case Message::ATW_MESSAGE :
            std::cout<<"win to app"<<std::endl;
            break;
        case Message::WIM_MESSAGE :
            std::cout<<"error message"<<std::endl;
            break;
        default:
            break;
        }
    }
};
class Win : public AbstractMoudle{
public:
    Win(AbstractMediator* ptr) : AbstractMoudle(ptr){}
    void acceptMsg(Message msg) override {
        switch (msg)
        {
        case Message::ATM_MESSAGE :
            std::cout<<"error message"<<std::endl;
            break;
        case Message::ATW_MESSAGE :
            std::cout<<"App to win"<<std::endl;
            break;
        case Message::WIM_MESSAGE :
            std::cout<<"mac to win"<<std::endl;
            break;
        default:
            break;
        }
    }
};
class Mac : public AbstractMoudle{
public:
    Mac(AbstractMediator* ptr) : AbstractMoudle(ptr){}
    void acceptMsg(Message msg) override {
        switch (msg)
        {
        case Message::ATM_MESSAGE :
            std::cout<<"app to mac"<<std::endl;
            break;
        case Message::ATW_MESSAGE :
            std::cout<<"error message"<<std::endl;
            break;
        case Message::WIM_MESSAGE :
            std::cout<<"win to mac"<<std::endl;
            break;
        default:
            break;
        }
    }
};
class MediatorA : public AbstractMediator{
public:
    void setMoudleApp(AbstractMoudle* mod){
        this->m_app=mod;
    }
    void setMoudleWin(AbstractMoudle* mod){
        this->m_win=mod;
    }
    void setMoudleMac(AbstractMoudle* mod){
        this->m_mac=mod;
    }
    void transmit(Message msg,AbstractMoudle* mod) override {
        switch (msg)
        {
            case Message::ATM_MESSAGE :
            {
                App* ptr=dynamic_cast<App*>(mod);
                if(ptr!=nullptr){
                    m_mac->acceptMsg(msg);
                }
                else{
                    m_app->acceptMsg(msg);
                }
                break;
            }
            case Message::ATW_MESSAGE :
            {
                App* ptr=dynamic_cast<App*>(mod);
                if(ptr!=nullptr){
                    m_win->acceptMsg(msg);
                }
                else{
                    m_app->acceptMsg(msg);
                }
                break;
            }
            case Message::WIM_MESSAGE :
            {
                Win* ptr=dynamic_cast<Win*>(mod);
                if(ptr!=nullptr){
                    m_mac->acceptMsg(msg);
                }
                else{
                    m_win->acceptMsg(msg);
                }
                break;
            }
        }
    }
    ~MediatorA(){
        if(m_app)
            delete m_app;
        if(m_win)
            delete m_win;
        if(m_mac)
            delete m_mac;
    }
protected:
    AbstractMoudle* m_app=nullptr;
    AbstractMoudle* m_win=nullptr;
    AbstractMoudle* m_mac=nullptr;

};
int main(){
    AbstractMediator* pmediator = new MediatorA;
    AbstractMoudle* papp = new App(pmediator);
    AbstractMoudle* pwin = new Win(pmediator);
    AbstractMoudle* pmac = new Mac(pmediator);

    MediatorA* pmedA = dynamic_cast<MediatorA*>(pmediator);
    pmedA->setMoudleApp(papp);
    pmedA->setMoudleMac(pmac);
    pmedA->setMoudleWin(pwin);

    papp->sendMsg(Message::ATM_MESSAGE);
    std::cout<<"============"<<std::endl;
    papp->sendMsg(Message::ATW_MESSAGE);
    std::cout<<"============"<<std::endl;

    return 0;
}
