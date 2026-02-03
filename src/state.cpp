#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
/*
*状态模式：行为设计模式，让你能在一个对象的内部状态变化时改变其行为，使其看上去就像改变了自身所属的类一样
通过一个属性或者一个值的改变（状态的改变）来决定你使用什么形态（行为改变），类似状态机
*优点：单一职责原则，开闭原则；通过消除臃肿的状态机条件语句简化上下文代码
*缺点：如果状态机只有很少的几个状态，或者很少发生改变，那么应用该模式可能会显得小题大做
*/
/*
1.提供一个上下文环境类（操作类）：抽象一个客户程序需要的接口，将与状态相关的操作委托给当前的具体状态类对象来处理；
2.提供一个抽象状态类:定义一个接口以封装使用上下文环境的一个特定状态相关的行为；
3.提供一个具体状态类：实现抽象状态定义的接口；
*/
class Context;
class AbstractState{
public:
    virtual ~AbstractState()=default;
    virtual void handle(Context* p)=0;
};
class NoneState : public AbstractState{
public:
    void handle(Context* p) override {
        std::cout<<"exit"<<std::endl;
    }
};
class AState : public AbstractState{
public:
    void handle(Context* p) override {
        std::cout<<"A exists"<<std::endl;
    }
};
class Context{
public:
    Context(AbstractState* ptr) : m_state(ptr){}
    void request(){
        if(m_state){
            m_state->handle(this);
        }
    }
    void changeState(AbstractState* pstate){
        m_state=pstate;
    }
private:
    AbstractState* m_state=nullptr;
};

int main(){
    AbstractState* pNo=new NoneState;
    AbstractState* pA =new AState;
    Context* pmanage= new Context(pNo);
    pmanage->request();
    pmanage->changeState(pA);
    pmanage->request();
    return 0;
}