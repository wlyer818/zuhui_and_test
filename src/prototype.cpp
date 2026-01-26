#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;
/*
*原型模式：用原型实例指定创建对象的种类，并通过拷贝这些原型创建新的对象，简单的理解就是“克隆指定对象”
某些结构复杂的对象的创建工作由于需求的变化，这些对象经常面临着剧烈的变化，但是他们却拥有比较稳定一致的接口。
*优点：简化对象的创建，无需理会创建过程；
如果创建新的对象比较复杂，可以使用原型模式简化对象的创建过程，提高效率；
可以在程序运行时获取一份内容相同的实例，他们之间不会相互干扰
*/
/*
1.提供一个抽象原型类：规定了具体原型对象必须实现的接口
2.提供多个具体原型类：实现抽象原型类的clone()方法，它是可被复制的对象
3.提供访问类：使用具体原型类中的clone()方法来复制新的对象
*/
//1.抽象原型类
class Monkey{
public:
    Monkey()=default;
    virtual ~Monkey(){};
    virtual Monkey* clone()=0;
    virtual void display()=0;
};
//2.具体原型类
class Woamn : public Monkey{
public:
    Woamn(string name) : m_name(name){}
    //注意深浅拷贝问题（指针，并且做了内存申请）
    Woamn(const Woamn& other){
        this->m_name=other.m_name;
    }
    Monkey* clone() override {
        //调用拷贝构造函数
        return new Woamn(*this);
    }
    void display() override {
        std::cout<<"change to a "<<m_name<<endl;
    }
private:
    string m_name;
};
class Horse : public Monkey{
public:
    Horse(string name) : m_name(name){}
    Horse(const Horse& other){
        m_name=other.m_name;
    }
    Monkey* clone() override {
        return new Horse(*this);
    }
    void display() override {
        std::cout<<"change to a "<<m_name<<std::endl;
    }
private:
    string m_name;
};
int main(){
    Monkey* sun=new Woamn("woman1");
    Monkey* s1=sun->clone();
    sun->display();
    s1->display();
    delete  sun;
    delete s1;
    sun=new Horse("horse111");
    s1=sun->clone();
    sun->display();
    s1->display();
    delete  sun;
    delete s1;
    return 0;
}