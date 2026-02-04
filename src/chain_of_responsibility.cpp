#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
/*
*责任链模式：行为型设计模式，允许将请求沿着处理者链进行发送，收到请求后，每个处理者都可对请求进行处理，或将其传递给链上的下个处理者；
*优点：可以控制请求处理的顺序；单一职责；开闭原则
*缺点：部分请求可能违背处理；
*/
/*
1.提供处理类的抽象父类：抽象客户端如何将请求数据传递给方法；
2.依次创建具体处理者子类并实现处理方法
    是否自行处理这个请求
    是否将该请求沿着链进行传递
3.客户端处理链（组装链+触发处理者），客户端需要准备好处理以下情况；
    链中可能只有单个链接；
    部分请求可能无法到达链尾；
    其他请求可能直到链尾都未被处理；
*/
enum class RequestType : char{
    qingjia,
    zhangxin,
    cizhi
};

class AbstractManager{
public:
    void setNext(AbstractManager* pmanager){
        m_next = pmanager;
    }
    virtual void handleRequest(RequestType type)=0;
    virtual ~AbstractManager(){}
protected:
    AbstractManager* m_next = nullptr;
};

class Manager : public AbstractManager{
public:
    void handleRequest(RequestType type) override {
        switch (type)
        {
        case RequestType::qingjia :{
            std::cout<<"请假：同意请假"<<std::endl;
            break;
        }
        case RequestType::zhangxin :{
            std::cout<<"涨薪：我要去请示一下"<<std::endl;
            m_next->handleRequest(type);
            break;
        }
        case RequestType::cizhi :{
            std::cout<<"辞职：我会向上级反应"<<std::endl;
            m_next->handleRequest(type);
            break;
        }
        default:
            break;
        }
    }
};
class CEO : public AbstractManager{
public:
    void handleRequest(RequestType type) override {
        switch (type)
        {
        case RequestType::qingjia :{
            std::cout<<"请假：同意请假"<<std::endl;
            break;
        }
        case RequestType::zhangxin :{
            std::cout<<"涨薪：你的工资不少了，给你优惠券"<<std::endl;
            break;
        }
        case RequestType::cizhi :{
            std::cout<<"辞职：我会向上级反应"<<std::endl;
            m_next->handleRequest(type);
            break;
        }
        default:
            break;
        }
    }
};
class BOSS : public AbstractManager{
public:
    void handleRequest(RequestType type) override {
        switch (type)
        {
        case RequestType::qingjia :{
            std::cout<<"请假：同意请假"<<std::endl;
            break;
        }
        case RequestType::zhangxin :{
            std::cout<<"涨薪：不行"<<std::endl;
            break;
        }
        case RequestType::cizhi :{
            std::cout<<"辞职：这里是你的家"<<std::endl;
            m_next->handleRequest(type);
            break;
        }
        default:
            break;
        }
    }
};
class client{
public:
    client(AbstractManager* pmanager) : m_next(pmanager){}
    void request(RequestType type){
        m_next->handleRequest(type);
    }
protected:
    AbstractManager* m_next = nullptr;
};
int main(){
    AbstractManager* pmanager = new Manager;
    AbstractManager* pceo = new CEO;
    AbstractManager* pboss = new BOSS;
    pmanager->setNext(pceo);
    pceo->setNext(pboss);

    client* pclient = new client(pmanager);
    pclient->request(RequestType::qingjia);
    std::cout<<"==============\n";
    pclient->request(RequestType::zhangxin);
    std::cout<<"==============\n";
    pclient->request(RequestType::cizhi);
    return 0;
}
