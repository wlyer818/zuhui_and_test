#include <iostream>
#include <string>
using namespace std;
/*
*适配器模式：将一个类的接口转换成用户希望的另一个接口，使不兼容的对象能够相互配合一起工作（适配器模式相当于翻译）
*优点：适配不兼容的两个对象
*/
class foreign{
public :
    foreign(string n):name(n){

    }
    ~foreign(){

    }
    virtual void speak(const string &msg)=0;
    string name;
};
class English : public foreign{
public:
    English(string n):foreign(n){

    }
    ~English(){

    }
    void speak(const string &msg){
        cout<<"hello,"<<msg<<" My name is "<<name<<endl;
    }
    void say(){
        cout<<"say english"<<endl;
    }
};

class fench : public foreign{
public:
    fench(string n):foreign(n){

    }
    ~fench(){

    }
    void speak(const string &msg){
        cout<<"hello,"<<msg<<" My name is "<<name<<endl;
    }
};

class monkey{
public:
    string m_name;
    monkey(string n) : m_name(n){};
    ~monkey()=default;
    void  sendmsg(){
        cout<<"Hello, I am a monkey! My name is "<<m_name<<endl;
    }
    void recievemsg(const string &msg){
        cout<<"Monkey received message: "<<msg<<endl;
    }
};
class AbstractAdapter{
public:
    AbstractAdapter()=default;
    virtual ~AbstractAdapter()=default;
    virtual void translatetomonkey()=0;
    virtual void translatetoforeign()=0;
protected:
    monkey* m_monkey;
    foreign* m_foreign;

};
class englishAdapter : public AbstractAdapter{
public:
    englishAdapter(monkey* m, foreign* f){
        m_monkey = m;
        m_foreign = f;
    }
    ~englishAdapter()=default;
    void translatetoforeign() override {
       m_monkey->sendmsg();
       m_foreign->speak(m_monkey->m_name);
    }
    void translatetomonkey() override {

    }
};
int main(){
    foreign* f1=new English("jack");
    f1->speak("jiji");

    
}