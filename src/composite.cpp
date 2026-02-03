#include <iostream>
#include <string>
#include <list>
using namespace std;
/*
*组合模式：能将多个对象组合成一个树状结构，用以描述部分-整体的层次关系，使得用户对单个对象和组合对象的使用具有一致性（结构型设计模式）
*装饰模式也可以称为封装模式，所谓的封装就是在原有行为之上进行拓展，并不会改变该行为
*优点：可以利用多态和递归机制更方便地使用复杂树结构；开闭原则，无需更改现有代码，就可以在应用中添加新元素，使其成为对象树的一部分
*/
/*
1.提供一个组件类：描述复杂元素的通用接口和方法
2.创建一个叶子节点类：描述简单元素
3.提供一个容器类：表示复杂元素
4.容器类中定义添加和删除子元素的方法 
*/
class Root{
public:
    Root(string name) : m_name(name){}
    virtual ~Root(){};
    virtual void display(){
        std::cout<<m_name<<std::endl;
    };
    virtual void add(Root* file){}
    virtual void remove(Root* file){}
    virtual list<Root*> getChild()=0;
protected:
    string m_name;
}; 
//叶子节点类
class File : public Root{
public:
    using Root::Root;
    list<Root*> getChild(){return m_list;}
protected:
    list<Root*> m_list;
};
//容器类
class Folder : public Root{
public:
    using Root::Root;
    void add(Root* file) override {
        m_list.push_back(file);
    }
    void remove(Root* file) override {
        m_list.remove(file);
    }
    list<Root*> getChild() override {
        return m_list;
    }
private:
    list<Root*> m_list;
};
//统一一个接口
void showTree(Root* filetree,int level){
    list<Root*> root;
    for(int i=0;i<level; i++) {
        std::cout<<"--";
    }
    std::cout<<">";
    filetree->display();
    root=filetree->getChild();
    if(root.empty()){
        return;
    }
    if(!root.empty()){
        for(auto& it : root){
            showTree(it,level+1);
        }
    }

}
int main(){
    Folder* root =new Folder("C:");
    Folder* d1=new Folder("dir1");
    File* f1= new File("t1.txt");

    Folder* d2=new Folder("dir2");
    File* f2=new File("t2.txt");
    root->add(d1);
    d1->add(f1);
    d2->add(f2);
    d2->add(new File("t3.txt"));
    d1->add(d2);
    showTree(root,0);

    return 0;
}