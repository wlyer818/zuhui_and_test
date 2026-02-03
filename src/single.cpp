#include <iostream>
#include <string>
/*饿汉式单例模式实现四步骤：
1.构造函数私有化，禁止外部创建;
2.禁止拷贝与赋值；
3.声明一个私有静态成员，类加载时立即初始化
4.公有静态方法获取唯一实例getInstance
5.类外定义并初始化静态成员
*/
class Singleton{
private:
   Singleton(std::string str) : m_str(str){}
   Singleton(const Singleton& other)=delete;
   Singleton& operator=(const Singleton& other)=delete;
   static Singleton instance;
   std::string m_str;
public:
   static Singleton& getInstance(){
      return instance;
   }
   void display(){
      std::cout<<m_str<<std::endl;
   }
};
Singleton Singleton::instance("only");

int main(){
   Singleton::getInstance().display();
}