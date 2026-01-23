#include <iostream>
using namespace std;
enum class Color : char {
    red,
    green,
    blue
};
int main(){
    Color color=Color::red;
    switch (color)
    {
    case Color::blue:
        cout<<"this is blue"<<endl;
        cout<<"blue----"<<endl;
        break;
    case Color ::red:
        cout<<"this is red"<<endl;
        cout<<"red----"<<endl;
        break;
    default:
        break;
    }
}