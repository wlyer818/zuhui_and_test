#ifndef TOOLS_H
#define TOOLS_H
#include <string>

bool isdigital(std::string& str){
    for(auto& ch : str){
        if(ch<'0' || ch>'9')
        return false;
    }
    return true;
}
#endif