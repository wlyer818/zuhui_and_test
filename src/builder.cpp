#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;
/*
*建造者（生成器）模式：分步骤创建复杂对象，并且允许使用相同的代码生成不用类型和形式的对象；（对象创建型模式）
用来隐藏复合对象的创建过程，它把复合对象的创建过程加以抽象，通过子类继承和重载的方式，动态的创建具有复合属性的对象。
*优点：封装好，构建与表示分离；扩展性好，各个具体的建造者相互独立，有利于系统的解耦
*/
/*
1.提供抽象建造者类：为创建产品各个部分，统一抽象接口
2.提供具体建造者类：具体实现抽象建造者各个部件的接口
3.提供多个具体产品类：具体的创建产品的各个部分
4.提供一个指挥类：负责安排与调度复杂对象的各个建造过程
*/
class SunnyShip{
public:
    void addParts(string name){
        m_parts.push_back(name);
    }
    void showParts(){
        for(auto& it : m_parts){
            std::cout<<it<<"--";
        }
        std::cout<<"\n";
    }
private:
    vector<string> m_parts;
};
class MerryShip{
public:
    void assemble(string name,string parts){
        m_parts.insert(std::make_pair(name,parts));
    }
    void showParts(){
        for(auto& it : m_parts){
            std::cout<<it.first<<":"<<it.second<<"--";
        }
        std::cout<<std::endl;
    }
private:
    map<string,string> m_parts;
};
class ShipBuilder{
public:
    virtual ~ShipBuilder(){}
    virtual void reset()=0;
    virtual void buildBody()=0;
    virtual void buildWeapon()=0;
    virtual void buildEngine()=0;
    virtual void buildInterior()=0;
};
class SunnyBuilder : public ShipBuilder{
public:
    SunnyBuilder(){
        reset();
    }
    ~SunnyBuilder(){
        if(m_sunny!=nullptr){
            delete m_sunny;
        }
    }
    void reset() override {
        m_sunny=new SunnyShip;
    }
    void buildBody(){
        m_sunny->addParts("神树亚当的树干");
    }
    void buildWeapon(){
        m_sunny->addParts("狮吼炮");
    }
    void buildEngine(){
        m_sunny->addParts("可乐驱动");
    }
    void buildInterior(){
        m_sunny->addParts("豪华室内");
    }
    SunnyShip* getSunny(){
        SunnyShip* ship=m_sunny;
        m_sunny=nullptr;
        return ship;
    }
private:
    SunnyShip* m_sunny=nullptr;
};
class MerryBuilder : public ShipBuilder{
public:
    MerryBuilder(){
        reset();
    }
    ~MerryBuilder(){
        if(m_merry!=nullptr){
            delete m_merry;
        }
    }
    void reset() override {
        m_merry=new MerryShip;
    }
    void buildBody(){
        m_merry->assemble("船体","木材");
    }
    void buildWeapon(){
        m_merry->assemble("武器","四门大炮");
    }
    void buildEngine(){
        m_merry->assemble("动力","蒸汽机");
    }
    void buildInterior(){
        m_merry->assemble("内饰","精装");
    }
    MerryShip* getSunny(){
        MerryShip* ship=m_merry;
        m_merry=nullptr;
        return m_merry;
    }
private:
    MerryShip* m_merry=nullptr;
};

class Director{
public:
    void setbuilder(ShipBuilder* builder){
        m_builder=builder;
    }
    void buildSimpleShip(){
        m_builder->buildBody();
        m_builder->buildEngine();
    }
    void buildStandardShip(){
        buildSimpleShip();
        m_builder->buildWeapon();
    }
    void buildRegalShip(){
        buildStandardShip();
        m_builder->buildInterior();
    }
private:
    ShipBuilder* m_builder=nullptr;
};
void buildSunny(){
    Director* dir=new Director;
    SunnyBuilder* sunBuilder=new SunnyBuilder;
    dir->setbuilder(sunBuilder);
    dir->buildSimpleShip();
    SunnyShip* sunny=sunBuilder->getSunny();
    sunny->showParts();
    delete sunny;
    sunny=nullptr;

    sunBuilder->reset();
    dir->buildStandardShip();
    sunny=sunBuilder->getSunny();
    sunny->showParts();
    delete sunny;
    sunny=nullptr;

}
int main(){
    buildSunny();
    return 0;
}