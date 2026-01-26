#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;
/*
*访问者模式：行为模式之一，它分离对象的数据和行为，使用访问者模式，可以在不修改已有类的情况下，增加新的操作角色和职责
通过在访问这对象中为多个目标类提供相同操作的变体，让你能在属于不同类的一组对象上执行统一操作；
*优点：
*/
/*
1.提供一个抽象访问者类：声明一个或者多个访问操作，形成所有的具体元素角色必须实现的抽象方法；
2.提供一个具体的访问者类：实现访问者角色所声明的抽象方法，也就是抽象访问者所声明的各个访问操作
3.提供一个抽象被访问者类：声明一个接受操作，接收一个访问者对象作为一个变量的抽象方法
4.提供一个或多个被访问者类：被访问者的抽象方法的具体实现
5.提供一个结构对象类：可以遍历结构中的所有元素；如果有需要，可以提供访问元素接口，元素可以存储到容器中
*/
class ParkElement;
class Visitor{
public:
    virtual void visit(ParkElement* park)=0;
    virtual ~Visitor()=default;
protected:
    string m_name;
};
class ParkElement{
public:
    virtual void acceptVisit(Visitor* visitor)=0;
    string getAddr(){
        return m_addr;
    }
protected:
    string m_addr;
};
class Forest : public ParkElement{
public:
    Forest(){
        this->m_addr="forset";
    }
    void acceptVisit(Visitor* visitor) override {
        visitor->visit(this);
    }
};
class Lake : public ParkElement{
public:
    Lake(){this->m_addr="lake";}
    void acceptVisit(Visitor* visitor) override {
        visitor->visit(this);
    }
};
class Wly : public Visitor{
public:
    using Visitor::Visitor;
    Wly(){
        this->m_name="wly";
    }
    void visit(ParkElement* park) override {    
        std::cout<<m_name<<"在"<<park->getAddr()<<"看风景"<<std::endl;
    }
};
class Man : public Visitor{
public:
    using Visitor::Visitor;
    Man(){
        this->m_name="a man";
    }
    void visit(ParkElement* park) override {    
        std::cout<<m_name<<"在"<<park->getAddr()<<"散步"<<std::endl;
    }
};
//结构对象类:综合管理类
class Manage {
public:
    Manage(){}
    void setElement(ParkElement* park){
        m_list.insert(m_list.end(),park);

    }
    void accept(Visitor* visitor){
        for(auto& it : m_list){
            it->acceptVisit(visitor);
        }
    }
private:
    list<ParkElement*> m_list;
};

int main(){
    std::cout<<"直接访问：======="<<std::endl;
    //访问者
    Wly* wly = new Wly;
    Man* aman = new Man;
    //被访问者
    Forest* forest = new Forest;
    Lake* lake = new Lake;
    
    forest->acceptVisit(wly);
    forest->acceptVisit(aman);

    lake->acceptVisit(wly);
    lake->acceptVisit(aman);
    std::cout<<"通过结构类对象访问：======="<<std::endl;
    Manage* manage = new Manage;
    manage->setElement(forest);
    manage->setElement(lake);
    manage->accept(wly);
    manage->accept(aman);
}