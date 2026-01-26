#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;
/*
*模板方法模式：行为设计模式，它在基类中定义了一个算法的框架，允许子类在不修改结构的情况下重写算法的特定步骤
在基类中统一操作步骤，并规定好接口，让子类实现接口。这样可以把各个具体的，子类和操作步骤解耦合。
*优点：你可仅允许客户端重写一个大型算法中的特定部分，使得算法其他部分修改对其所造成的影响减小
你可将重复代码提取到一个超类中
*/
/*
1.提供一个抽象类：负责规定好接口，让子类实现接口，定义一个模板方法
2.提供具体实现子类：实现抽象类的抽象接口即可
*/
class AbstractMakeObject{
public:
    virtual ~AbstractMakeObject()=default;
    virtual void makeHead()=0;
    virtual void makeBody()=0;
    virtual void WearClothes()=0;
    void make(){
        makeHead();
        makeBody();
        WearClothes();
    }
};
class MakeMan : public AbstractMakeObject{
public:
    void makeHead(){
        std::cout<<"man's head"<<std::endl;
    }
    void makeBody(){
        std::cout<<"man's body"<<std::endl;
    }
    void WearClothes(){
        std::cout<<"wear suit"<<std::endl;
    }
};
class MakeWoamn : public AbstractMakeObject{
public:
    void makeHead(){
        std::cout<<"woman's head"<<std::endl;
    }
    void makeBody(){
        std::cout<<"woman's body"<<std::endl;
    }
    void WearClothes(){
        std::cout<<"wear skirt"<<std::endl;
    } 
};
int main(){
    AbstractMakeObject* obj=new MakeMan;
    obj->make();
    delete obj;
    cout<<"===========\n";
    obj=new MakeWoamn;
    obj->make();
    delete obj;
}