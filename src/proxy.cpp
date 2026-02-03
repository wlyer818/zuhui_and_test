#include <iostream>
#include <string>
#include <map>
using namespace std;
/*
*代理模式：为其他对象提供一种代理，以控制对这个对象的访问
*优点：可以在代理类中有效的管理被代理的对象的工作的时机，但是并没有改变被代理的对象的行为
*/
class Communcication{
public:
    virtual ~Communcication(){};
    virtual void communicate()=0;
};
class Speaker : public Communcication{
public:
    void communicate() override {
        std::cout<<"begin speaking...\n";
        std::cout<<"face changes...\n";
    }
};
class Proxy : public Communcication{
public:
    Proxy(std::shared_ptr<Speaker> sp) : m_speaker(sp){}
    ~Proxy(){};
    bool isStart(){
        return m_isStart;
    }
    void setStart(bool isstart){
        m_isStart=isstart;
    }
    void communicate() override {
        if(m_isStart){
            std::cout<<"dendenmushi begin mimic...\n";
            m_speaker->communicate();
        }
    }
private:
    std::shared_ptr<Speaker> m_speaker;
    bool m_isStart=false;
};
int main(){
    std::shared_ptr<Speaker> speaker=std::make_shared<Speaker>();
    std::unique_ptr<Proxy> proxy=std::make_unique<Proxy>(speaker);
    proxy->setStart(true);
    proxy->communicate();
}