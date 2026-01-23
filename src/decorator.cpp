#include <iostream>
#include <string>
using namespace std;
/*
*装饰模式：动态的给一个对象绑定额外的属性（比如：能力、职责、功能等）
*装饰模式也可以称为封装模式，所谓的封装就是在原有行为之上进行拓展，并不会改变该行为
*优点：适配不兼容的两个对象
*/
//抽象类，不能实例化
class Soldier{
public:
    Soldier(){}
    Soldier(string& name) : m_name(name){}
    string getName(){return m_name;}
    virtual void fight()=0;
    virtual ~Soldier(){}
private:
    std::string m_name=std::string();
};

int mian(){
    return 1;
}