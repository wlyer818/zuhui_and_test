#include <iostream>
#include <string>

class single{
public:
   static single* getInstance(){
      return m_single;
   }
   void printfHello(std::string name){
      std::cout<<name;
      std::cout<<m_single<<std::endl;
   }
private:
   single()=default;
   ~single(){
      if(m_single)
         delete m_single;
   };
   single(const single&)=delete;
   single& operator=(const single&)=delete;
   static single* m_single;

};
single* single::m_single=new single();
int main(){

   single::getInstance()->printfHello("wly");
   single::getInstance()->printfHello("mt");
   return 0;
}