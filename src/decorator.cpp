#include <iostream>
#include <string>
using namespace std;
/*
*装饰模式：动态的给一个对象绑定额外的属性（比如：能力、职责、功能等）
*装饰模式也可以称为封装模式，所谓的封装就是在原有行为之上进行拓展，并不会改变该行为
*优点：
*/
/*
1.提供一个抽象组件类：抽象被装饰者的行为
2.提供一个或多个具体组件类：被装饰者的行为具体实现
3.提供一个抽象装饰器类：抽象组件指针与抽象组件一致接口
4.提供一个具体的装饰器类：为具体组件附加责任
compent:组件，器件，元件
*/
//1.抽象组件类
class AbstractCompent{
public:
    virtual ~AbstractCompent(){};
    virtual void show()=0;
public:
    std::string m_pstr;
};
//2.具体组件类
class Girl : public AbstractCompent{
public:
    Girl(){
        m_pstr=std::string("Only girl");
    }
    void show() override {
        std::cout<<this->m_pstr<<std::endl;
    }
};
//3.抽象装饰器类(也是组件)
class AbstractDecorate : public AbstractCompent{
public:
    using AbstractCompent::AbstractCompent;
    virtual ~AbstractDecorate(){}
    virtual void show()=0;
protected:
    AbstractCompent* m_pbase=nullptr;
};
//4.具体的装饰器类（组件）
class LowShortSkirt : public AbstractDecorate{
public:
    using AbstractDecorate::AbstractDecorate;
    LowShortSkirt(AbstractCompent* base){
        this->m_pbase=base;
    }
    void show() override {
        m_pstr = m_pbase->m_pstr+" with lowshortskirt";
        std::cout<<m_pstr<<std::endl;
    }
};
class BlackSock : public AbstractDecorate{
public:
    using AbstractDecorate::AbstractDecorate;
    BlackSock(AbstractCompent* base){
        this->m_pbase=base;
    }
    void show() override {
        this->m_pstr = m_pbase->m_pstr+" with blacsock";
        std::cout<<this->m_pstr<<std::endl;
    }
};
int main(){
    Girl * girl = new Girl;
    girl->show();
    LowShortSkirt* skirtgirl=new LowShortSkirt(girl);
    skirtgirl->show();
    BlackSock* sockgirl = new BlackSock(skirtgirl);
    sockgirl->show();
    return 0;
}