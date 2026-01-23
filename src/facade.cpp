#include <iostream>
#include <string>
#include <map>
using namespace std;
/*
*外观模式：给很多的子系统提供一个简单的上层接口，并在这些接口中包含用户真正关心的功能
*优点：针对用户来说，简便了操作
*/
class CokeSystem{
public:
    void immitCoke(){
        std::cout<<"狮吼炮原料<可乐>注入完毕...\n";
    }
};
class EnergySystem{
public :
    void energyConvert(){
        std::cout<<"已经将所有可乐转换为能量...\n";
    }
};
class AimSystem{
public:
    void aimLock(){
        std::cout<<"瞄准完成...\n";
    }
};
class Cannon{
public:
    void ccannonFire(){
        std::cout<<"狮吼炮发射...\n";
    }
};
class WindCannon{
public:
    void windCannonFire(){
        std::cout<<"发射风来炮抵消后坐力稳定船身...\n";
    }
};
class LionCannon{
private:
    CokeSystem* m_coke=nullptr;
    EnergySystem* m_energy=nullptr;
    AimSystem* m_ainlock=nullptr;
    Cannon* m_cannon=nullptr;
    WindCannon* m_wind=nullptr;
public:
    LionCannon(){
        m_cannon=new Cannon;
        m_coke=new CokeSystem;
        m_ainlock=new AimSystem;
        m_energy=new EnergySystem;
        m_wind=new WindCannon;
    }
    ~LionCannon(){
        delete m_cannon;
        delete m_coke;
        delete m_ainlock;
        delete m_energy;
        delete m_wind;
    }
    void aimAndLock(){
        m_coke->immitCoke();
        m_energy->energyConvert();
        m_ainlock->aimLock();
    }
    void fire(){
        m_cannon->ccannonFire();
        m_wind->windCannonFire();
    }
};
int main(){
    std::shared_ptr<LionCannon> lion=make_shared<LionCannon>();
    lion->aimAndLock();
    lion->fire();
    return 0;

}