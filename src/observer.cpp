#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
/*
*观察者模式：行为模式，当一个对象的行为发生变化，能够自动通知其他关联的对象，自动刷新对象状态；
*优点：开闭原则；可以在运行时建立对象之间的联系；依赖倒置，让耦合的双方都依赖于抽象而不是依赖于具体；
*缺点：被观察者对象有很多的直接和间接的观察者的话，将所有的观察者都通知到会花费很多时间；
*/
/*
1.提供一个抽象目标类：被观察的对象，抽象基本的属性状态及其他操作；
2.提供一个具体目标类：被观察的对象的具体实现；
3.提供一个抽象观察者类：抽象观察者的具体业务逻辑处理；
4.提供一个具体观察者类：观察者的具体实现，得到通知后将完成一些具体的业务逻辑处理；
*/
class AbstractBoss;
class AbstractStuff{
public:    
    AbstractStuff(std::string name,AbstractBoss* ptr) : m_name(name),m_boss(ptr){}
    virtual void update(std::string action)=0;
    virtual ~AbstractStuff(){}
protected:
    AbstractBoss* m_boss=nullptr;
    std::string m_name;
};
class Stuff : public AbstractStuff{
public: 
    using AbstractStuff::AbstractStuff;
    void update(std::string action) override {
        std::cout<<m_name<<" changes"<<std::endl;
        if(action=="in"){
            std::cout<<"working"<<std::endl;
        }
        else if(action=="out"){
            std::cout<<"moyu"<<std::endl;
        }
    }
};
class AbstractBoss{
public:
    virtual ~AbstractBoss(){}
    virtual void walkIn()=0;
    virtual void walkOut()=0;
    virtual void addObserver(AbstractStuff*ptr)=0;
    virtual void notify()=0;
};
class Boss : public AbstractBoss{
public:
    void addObserver(AbstractStuff* ptr) override {
        m_list.emplace_back(ptr);
    }
    void walkIn() override {
        std::cout<<"boss walk in"<<std::endl;
        m_action="in";
        notify();
    }
    void walkOut() override {
        std::cout<<"boss walk out"<<std::endl;
        m_action="out";
        notify();
    }
    void notify() override {
        for(auto& it : m_list){
            it->update(m_action);
        }
    }
private:
    std::string m_action;
    std::vector<AbstractStuff*> m_list;
};

int main(){
    AbstractBoss* pboss= new Boss;
    AbstractStuff* p1=new Stuff("wly",pboss);
    AbstractStuff* p2=new Stuff("nutton",pboss);
    pboss->addObserver(p1);
    pboss->addObserver(p2);

    pboss->walkIn();
    std::cout<<"================"<<std::endl;
    pboss->walkOut();
}