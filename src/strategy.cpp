#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
/*
*策略模式：行为设计模式，它可以实现定义一系列算法，并将每种算法放入独立的类中，以使算法的对象能够相互替换
*优点：可以在运行时切换对象内的算法；
可以将算法的实现和使用算法的代码隔离开来；
可以使用组合来代替继承；
开闭原则
*/
/*
1.提供一个抽象策略类：定义抽象的函数算法让继承的子类实现；
2.提供具体策略类：封装了具体相关的算法和行为，即函数的具体功能实现；
3.提供一个策略的容器类：根据不同策略执行不同的行为，策略由外部环境决定；
*/
//简单计算器
template<class T>
class AbstractStrategy{
public:
    virtual ~AbstractStrategy(){}
    virtual T method(T a,T b)=0;
};
template<class T>
class Add : public AbstractStrategy<T>{
public:
    T method(T a,T b) override { 
        return a+b;
    }
};
template<class T>
class Sub : public AbstractStrategy<T>{
public:
    T method(T a,T b) override { 
        return a-b;
    }
};
template<class M>
class Manage{
public:
    void setStrategy(AbstractStrategy<M>* ptr){
        m_strategy=ptr;
    }
    M executeStrategy(M a,M b){
        return m_strategy->method(a,b);
    }
private:
    AbstractStrategy<M>* m_strategy=nullptr;
};
int main(){
    AbstractStrategy<int>* ptr=new Add<int>;
    Manage<int>* manage=new Manage<int>();
    manage->setStrategy(ptr);
    std::cout<<manage->executeStrategy(1,2)<<std::endl;
    AbstractStrategy<int>* subptr=new Sub<int>;
    manage->setStrategy(subptr);
    std::cout<<manage->executeStrategy(2,1)<<std::endl;
}