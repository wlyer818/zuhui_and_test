#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <string>
#include "tools.h"
using namespace std;
static std::unordered_map<string,int> IntRecords;
class AbstractParser{
public:
    AbstractParser(){}  
    ~AbstractParser()=default;
    virtual string parser(vector<string>& data)=0;
};
class SetParser : public AbstractParser{
public:
    using AbstractParser::AbstractParser;
    string parser(vector<string>& data) override {
        if(data.size()!=3) return string("Error: size is not correct!");
        if(isdigital(data[2])){
            IntRecords[data[1]]=stoi(data[2]);
            return string("Success : Exist "+to_string(IntRecords.size())+" numbers");
        }
        else return string("Error : not number!");
    }
};
class GetParser : public AbstractParser{
public:
    using AbstractParser::AbstractParser;
    string parser(vector<string>& data) override {
        if(data.size()!=2) return string("Error: size is not correct!");
        if(IntRecords.find(data[1])!=IntRecords.end()) return to_string(IntRecords[data[1]]);
        else return string("null");
    }
};
enum class Command : char{ //命令枚举
    SET,
    SETNX,
    SETEX,
    GET,
    SELECT,
    DBSIZE,
    EXISTS,
    DEL,
    RENAME,
    INCR,
    INCRBY,
    INCRBYFLOAT,
    DECR,
    DECRBY,
    MSET,
    MGET,
    STRLEN,
    APPEND,
    KEYS,
    LPUSH,
    RPUSH,
    LPOP,
    RPOP,
    LRANGE,
    HSET,
    HGET,
    HDEL,
    HKEYS,
    HVALS,
    INVALID_COMMAND
};
static std::unordered_map<std::string,enum class Command>commandMaps={ //命令映射
    {"set",Command::SET},
    {"setnx",Command::SETNX},
    {"setex",Command::SETEX},
    {"get",Command::GET},
    {"select",Command::SELECT},
    {"dbsize",Command::DBSIZE},
    {"exists",Command::EXISTS},
    {"del",Command::DEL},
    {"rename",Command::RENAME},
    {"incr",Command::INCR},
    {"incrby",Command::INCRBY},
    {"incrbyfloat",Command::INCRBYFLOAT},
    {"decr",Command::DECR},
    {"decrby",Command::DECRBY},
    {"mset",Command::MSET},
    {"mget",Command::MGET},
    {"strlen",Command::STRLEN},
    {"append",Command::APPEND},
    {"keys",Command::KEYS},
    {"lpush",Command::LPUSH},
    {"rpush",Command::RPUSH},
    {"lpop",Command::LPOP},
    {"rpop",Command::RPOP},
    {"lrange",Command::LRANGE},
    {"hset",Command::HSET},
    {"hget",Command::HGET},
    {"hdel",Command::HDEL},
    {"hkeys",Command::HKEYS},
    {"hvals",Command::HVALS}
};
class FlyWeightFactory{
private:
    std::shared_ptr<AbstractParser> createParser(string& str){
        switch (commandMaps[str])
        {
        case Command::SET:
            umap[str]=std::make_shared<SetParser>();
            break;
        case Command::GET:
            umap[str]=std::make_shared<GetParser>();
            break;
        default:
        return nullptr;
            break;
        }
        return umap[str];
    }
public:
    FlyWeightFactory(){}
    std::shared_ptr<AbstractParser> getParser(std::string& str){
        if(umap.find(str)!=umap.end()){
            return umap[str];
        }
        else return createParser(str);
    }
private:
    unordered_map<string,std::shared_ptr<AbstractParser>> umap;
};
int main(){
    auto factory = make_shared<FlyWeightFactory>();
    string line;
    while (cout << "cmd> " && getline(cin, line)) {   // 提示符 + 读行
        stringstream ss(line);
        vector<string> data{istream_iterator<string>(ss),
                            istream_iterator<string>{}};
        if (data.empty()) continue;        // 空行直接忽略

        auto parser = factory->getParser(data[0]);
        if (!parser) {
            cout << "error: unknown command\n";
            continue;
        }
        cout << parser->parser(data) << '\n';
    }
    cout << "bye\n";
}