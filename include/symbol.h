#ifndef _symbol_h__
#define _symbol_h__
#include <memory>
#include <unordered_map>
#include <vector>

#include "global.h"
class BaseVar {
public:
    TOKEN_TYPE type;
    bool isconst;
    int sid;
    TOKEN_TYPE gettype();
    bool getconst();
    BaseVar()=default;
    BaseVar(TOKEN_TYPE,bool,int=0);
    virtual ~BaseVar()=default;
};
class VarInt : public BaseVar {
public:
    int val;
    VarInt()=default;
    VarInt(bool,int,int);
    int getval();
};
class VarFun:public BaseVar {
public:
    int len;//参数个数
    TOKEN_TYPE returntype;
    VarFun()=default;
    VarFun(int,TOKEN_TYPE);
};
class VarArray : public BaseVar {
public:
    std::vector<int> val;
    int len;
    VarArray()=default;
    VarArray(bool,int,std::vector<int>,int);
    int getval(int);
};
class table {
    std::unordered_map<std::string, std::shared_ptr<BaseVar>> tb;
public:
    table() = default;
    std::shared_ptr<BaseVar> getVar(std::string);
    TOKEN_TYPE find(std::string);
    bool insertInt(std::string,bool, int,int);
    bool insertArray(std::string,bool,int,std::vector<int>,int);
    bool insertFun(std::string,int,TOKEN_TYPE);
};
class Symbol {
public:
    std::vector<std::shared_ptr<table>> st;
    std::vector<int> spaceid;
    std::unordered_map<std::string,int> funlable;
    int id_cnt,id_tmp;
    Symbol();
    void init();
    void inspace();
    void outspace();
    bool insertInt(std::string,bool, int);
    bool insertArray(std::string,bool,int,std::vector<int>);
    bool insertFun(std::string,int,TOKEN_TYPE);
    TOKEN_TYPE find(std::string);
    std::shared_ptr<BaseVar> getVar(std::string);
    void insertfunlable(std::string ,int);
    int getfunlable(std::string name);
};
#endif
