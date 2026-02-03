#include <iostream>
#include <string>

using namespace std;

void ProcessString(string&& str){
    cout<<"right"<<endl;
    cout<<str<<endl;
}
void ProcessString(const string& str){
    cout<<"left"<<endl;
    cout<<str<<endl;
}
int main(){
    string s1{"hello world"};
    ProcessString(s1.substr(2));
}