#ifndef _symbol_h__
#define _symbol_h__
#include<unordered_map>
#include<vector>
#include<memory>
#include"global.h"
class table {
    std::unordered_map<std::string,TOKEN_TYPE> tb;
public:
    table()=default;
    TOKEN_TYPE find(std::string);
    bool insert(std::string,TOKEN_TYPE);
};
class Symbol {
public:
    std::vector<std::shared_ptr<table>> st;
    Symbol()=default;
    void inspace();
    void outspace();
    bool insert(std::string,TOKEN_TYPE);
    TOKEN_TYPE find(std::string);
};
#endif
