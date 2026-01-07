#include <iostream>
#include <string>

#if 0
class fridge{
public:
    fridge():m_isempty(true){}
    void open() const {
        std::cout << "open fridge door\n";
    }
    void close() const {
        std::cout << "close fridge door\n";
    }
    bool isfull() const {
        return !m_isempty;
    }

public:
    bool m_isempty;
};

class elephant{
public:
    elephant(const std::string& name): m_name(name) {}
    void walkIn(fridge &f1) const {
        std::cout << "walk in fridge\n";
        f1.m_isempty = false;   
    }

private:
    std::string m_name;
};
#endif

#if 1
using namespace std;
class plant{
public:
    plant()=default;
    plant(const plant & p1){
        cout<<"copy plant\n";
    }
    ~plant(){
        cout<<"plant destruct\n";
    };
    void gettype(){
        std::cout<<"plant\n";
    }
};
class forest{
public:
    forest(plant pl):m_Plant(pl){

    }
    ~forest(){
        cout<<"forest destru\n";
    };
    plant m_Plant;
};

#endif
int main(){
    plant p1;
{    forest f1(p1);}
    p1.gettype();

}
