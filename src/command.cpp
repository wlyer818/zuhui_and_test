#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <unordered_set>
#include <queue>
#include <unordered_map>
/*
*命令模式：行为设计模式，将请求转换为一个包含与请求相关的所有信息的独立对象。
该转换能根据不同的请求将方法参数化、延迟请求执行或将其放入队列中，且能实现可撤销操作；
*优点：单一职责；开闭原则；方便实现撤销与恢复；实现操作的延迟执行；可以将一组简单命令组合成一个复杂命令；
*缺点：代码可能会变得更加复杂，因为在发送者与接收者之间增加了一个全新的层次；
*/
/*
1.声明仅有一个执行方法的命令抽象类；
2.抽取请求并使之成为实现命令接口的具体命令类；
3.找到担任发送者职责的类；
4.修改发送者使其执行命令，而非直接将请求发送给接收者；
5.客户端必须按照以下顺序来初始化对象；
创建接收者；
创建命令，如有需要可将其关联至接收者；
创建发送者并将其与特定命令关联；
*/
class Cook{
public:
    void MakeVegetable(){
        std::cout<<"蔬菜一份"<<std::endl;
    }
    void MakeSteak(){
        std::cout<<"牛排一份"<<std::endl;
    }
    void UnMakeVegetable(){
        std::cout<<"蔬菜不要了"<<std::endl;
    }
    void UnMakeSteak(){
        std::cout<<"牛排不要了"<<std::endl;
    }
};

class AbstractCommand{
public:
    AbstractCommand(Cook* ptr) : m_cook(ptr){}
    virtual void executeCommand() = 0;
    virtual void unCommand() = 0;
protected:
    Cook* m_cook = nullptr;
};

class MakeVegetableCommand : public AbstractCommand{
public:
    MakeVegetableCommand(Cook* pcook) : AbstractCommand(pcook){}
    void executeCommand() override {
        m_cook->MakeVegetable();
    }
    void unCommand() override {
        m_cook->UnMakeVegetable();
    }
};
class MakeSteakCommand : public AbstractCommand{
public:
    MakeSteakCommand(Cook* pcook) : AbstractCommand(pcook){}
    void executeCommand() override {
        m_cook->MakeSteak();
    }
        void unCommand() override {
        m_cook->UnMakeSteak();
    }
};
class Order{
public:
    void setOrder(int num,AbstractCommand* pcom){
        m_listcommand[num].insert(pcom);
    }
    void unOrder(int num,AbstractCommand* pcom){
        m_listcommand[num].erase(pcom);
    }
    void notify(){
        for(auto& it : m_listcommand){
            for(auto& v : it.second){
                v->executeCommand();
            }
        }
    }
protected:
    std::unordered_map<int,std::unordered_set<AbstractCommand*>> m_listcommand;
};
int main(){
    Cook* pcook = new Cook;
    AbstractCommand* pvegetable = new MakeVegetableCommand(pcook);
    AbstractCommand* psteak = new MakeSteakCommand(pcook);

    Order* porder = new Order;
    porder->setOrder(1,pvegetable);
    porder->setOrder(1,psteak);
    porder->setOrder(2,psteak);

    porder->notify();
    std::cout<<"============\n";
    porder->unOrder(1,psteak);
    porder->notify();
    return 0;
}
