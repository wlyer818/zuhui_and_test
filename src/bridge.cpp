#include <iostream>
#include <string>
#include <map>
using namespace std;
/*
*桥接模式：将抽象部分和它的实现部分分离，使他们可以独立的变化
*优点：更容易维护与扩展
*/
struct Person{
    Person(string name,string job,string ability,string reward,string remark){
        this->name=name;
        this->job=job;
        this->ability;
        this->reaward=reward;
        this->remark=remark;
    }
    ~Person(){
        cout<<"destruction----"<<endl;
    }
    string name;
    string job;
    string ability;
    string reaward;
    string remark;
};
class AbstractTeam{
public:
    AbstractTeam(string name):m_teamname(name){}
    string getTeamName(){
        return m_teamname;
    }
    void addMember(Person* p){
        m_mapPerson.insert({p->name,p});
    }
    void show(){
        cout<<"TeamName : "<<m_teamname<<endl;
        for(auto& it: m_mapPerson){
            cout<<"[Name : "<<it.second->name
            <<",job : "<<it.second->job
            <<",ability : "<<it.second->ability
            <<",reward : "<<it.second->reaward
            <<",remark : "<<it.second->remark;
        }
    }
    virtual void executeTask()=0;
    virtual ~AbstractTeam(){
        for(auto& it : m_mapPerson){
            delete it.second;
        }
    }
protected:
    string m_teamname;
    map<string,Person*> m_mapPerson;
};
class CaoMaoTeam : public AbstractTeam{
public:
    using AbstractTeam::AbstractTeam;
    void executeTask() override {
        cout<<"出发伟大航路！"<<endl;
    }
};
class SmokerTeam : public AbstractTeam{
public:
    void exectueTask(){
        cout<<"抓住草帽"<<endl;
    }
};
class AbstractShip{
public:
    AbstractShip(AbstractTeam * team,string name){
        this->m_team=team;
        this->m_name=name;
    }   
    void showTeam(){
        m_team->show();
        m_team->executeTask();
    }
    virtual string getName(){
        return m_name;
    }
    //描述船的特点
    virtual void feature()=0;
    virtual ~AbstractShip(){}
protected:
    AbstractTeam* m_team=nullptr;
    string m_name;
};
class Woodenship : public AbstractShip{
public:
    using AbstractShip::AbstractShip;
    void feature(){
        cout<<m_name<<"--船首是羊头"<<endl;
    }

};
class HaaijunShip : public AbstractShip{
public:
    using AbstractShip::AbstractShip;
    void feature(){
        cout<<m_name<<"船底是海楼石"<<endl;
    }
};
int main(){
    CaoMaoTeam * caomao=new CaoMaoTeam("草帽海贼团");
    Person* lufei=new Person("路飞","船长","橡胶果实能力者","30亿贝利","爱吃肉");
    Person* suolong=new Person("索隆","剑士","三刀流","11亿贝利","路痴");
    caomao->addMember(lufei);
    caomao->addMember(suolong);
    Woodenship* meli =new Woodenship(caomao,"梅利");
    meli->feature();
    meli->showTeam();
    return 0;
}