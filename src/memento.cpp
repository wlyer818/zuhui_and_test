#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
/*
*备忘录模式：行为设计模式，允许在不暴露对象细节的情况下保存和恢复对象之前的状态。（浏览器回退，游戏悔棋，编辑器撤销等）
*优点：可以不破坏对象封装情况的前提下创建对象状态快照；可以通过让负责人维护原生器状态历史记录来简化原生器代码；
*缺点：频繁的创建备忘录，程序将消耗大量内存；负责人必须完整跟踪原生器的生命周期，这样才能销毁弃用的备忘录；
*/
/*
1.提供一个原生器类：真正要被保存或恢复的对象，其负责创建一个备忘录，可以存储、恢复需要状态信息；
2.提供一个备忘录类：用于存储原生器对象的内部状态，防止外部直接访问原生器对象；
3.提供一个管理者类：负责存储备忘录，但不能对备忘录内容进行操作和访问，只能将备忘录传递给其他对象；
*/
//备忘录类
class Memento{
public:
    Memento(std::string name,std::pair<int,int> pos) : m_name(name),m_pos(pos){

    }
    std::string getNmae(){
        return m_name;
    }
    std::pair<int,int> getPos(){
        return m_pos;
    }
    void show(){
        std::cout<<"Name:"<<m_name<<",("<<m_pos.first<<","<<m_pos.second<<")"<<std::endl;
    }
protected:
    std::string m_name;
    std::pair<int,int> m_pos;
};
//原生器类
class Chess{
public:
    Chess(std::string name,std::pair<int,int> pos) : m_name(name),m_pos(pos){}
    void setChessOneShot(std::string name,std::pair<int,int> pos){
        this->m_name=name;
        this->m_pos=pos;
    }
    void back(Memento* ptr){
        m_name=ptr->getNmae();
        m_pos=ptr->getPos();
    }
    Memento* save(){
        return new Memento(m_name,m_pos);
    }
protected:
    std::string m_name;
    std::pair<int,int> m_pos;
};
class Caretaker{
public:
    void addMemento(Memento* ptr){
        m_list.emplace_back(ptr);
        step++;
    }
    Memento* getMemento(int index){
        
        for(int i=step-1;i>=index;i--){
            delete m_list[i];
            m_list.pop_back();
        }
        step=index;
        return m_list[step-1];
    }
    void show(){
        for(int i=0;i<step;i++){
            std::cout<<"step:"<<i+1<<std::endl;
            m_list[i]->show();
        }
    }
protected:
    std::vector<Memento*> m_list;
    static int step;
};
int Caretaker::step = 0;
int main(){
    Chess* pc=new Chess("car",{4,3});
    Caretaker* pcaretaker=new Caretaker;
    pcaretaker->addMemento(pc->save());
    pcaretaker->show();
    std::cout<<std::endl;
    pc->setChessOneShot("horse",{4,8});
    pcaretaker->addMemento(pc->save());
    pcaretaker->show();
    std::cout<<std::endl;
    pc->setChessOneShot("pao",{2,2});
    pcaretaker->addMemento(pc->save());
    pcaretaker->show();  
    std::cout<<std::endl;
    pc->back(pcaretaker->getMemento(1));
    pcaretaker->show();
    std::cout<<std::endl;
    pc->setChessOneShot("bing",{6,6});
    pcaretaker->addMemento(pc->save());
    pcaretaker->show();  
    std::cout<<std::endl;
    pc->setChessOneShot("horse",{6,6});
    pcaretaker->addMemento(pc->save());
    pcaretaker->show();  
    return 0;
}