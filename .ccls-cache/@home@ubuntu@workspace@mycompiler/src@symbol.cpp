#include "symbol.h"
#include <algorithm>
BaseVar::BaseVar(TOKEN_TYPE type, bool Const,int x) : type(type), isconst(Const),sid(x) {}
TOKEN_TYPE BaseVar::gettype() { return type; }
bool BaseVar::getconst() { return isconst; }
VarInt::VarInt(bool Const, int x,int y) : BaseVar(INT, Const,y), val(x) {}
VarArray::VarArray(bool Const,int len, std::vector<int> x,int y)
    : BaseVar(ARRAY, Const,y),len(len), val(x) {}
VarFun::VarFun(int x,TOKEN_TYPE y) :BaseVar(FUNCTION,false),len(x),returntype(y){}

Symbol::Symbol():id_cnt(0),id_tmp(0) { 
	inspace(); 
	insertFun("getint",1,VOID);
	insertFun("printint",1,VOID);
}
void Symbol::init() {
    st.clear();
    spaceid.clear();
    id_cnt=0;
    inspace();
}
std::shared_ptr<BaseVar> table::getVar(std::string s) {
    if (tb.find(s) == tb.end())
        return nullptr;
    else
        return tb[s];
}
TOKEN_TYPE table::find(std::string s) {
    if (tb.find(s) == tb.end()) return UNDEFINE;
    return tb[s]->gettype();
}
bool table::insertInt(std::string s, bool Const, int x,int sid) {
    if (find(s) != UNDEFINE) return false;
    tb[s] = std::make_shared<VarInt>(Const, x,sid);
    return true;
}
bool table::insertArray(std::string s, bool Const,int len, std::vector<int> x,int sid) {
    if (find(s) != UNDEFINE) return false;
    tb[s] = std::make_shared<VarArray>(Const,len, x,sid);
    return true;
}
bool table::insertFun(std::string s,int len,TOKEN_TYPE y) {
    if(find(s)!=UNDEFINE) {
        printerror("Funtion \" "+s+" \" redeclare");
        return false;
    }
    tb[s]=std::make_shared<VarFun>(len,y);
    return true;
}
void Symbol::inspace() { 
    st.push_back(std::make_shared<table>()); 
    spaceid.push_back(++id_cnt);
}
void Symbol::outspace() { 
    st.pop_back(); 
    spaceid.pop_back();
}
bool Symbol::insertInt(std::string s, bool Const, int x = 0) {
    if (st.empty()) return false;
    return (*st.back()).insertInt(s, Const, x,spaceid.back());
}
bool Symbol::insertArray(std::string s, bool Const,int len, std::vector<int> x = {}) {
    if (st.empty()) return false;
    return (*st.back()).insertArray(s, Const,len, x,spaceid.back());
}
bool Symbol::insertFun(std::string s,int len,TOKEN_TYPE y) {
    if (st.empty()) return false;
    if(st.size()!=2&&st.size()!=1) {
        printerror("only declare fun in wrong space");
        return false;
    }
    return (*st.back()).insertFun(s,len,y);
}
TOKEN_TYPE Symbol::find(std::string s) {
    for (int i = st.size() - 1; i >= 0; i--) {
        TOKEN_TYPE tmp = st[i]->find(s);
        if (tmp != UNDEFINE) return tmp;
    }
    return UNDEFINE;
}
std::shared_ptr<BaseVar> Symbol::getVar(std::string s) {
    for (int i = st.size() - 1; i >= 0; i--) {
        std::shared_ptr<BaseVar> tmp = st[i]->getVar(s);
        if (tmp != nullptr) return tmp;
    }
    printerror("name: \" "+s+" \" is not declared");
    return nullptr;
}
void Symbol::insertfunlable(std::string name,int lable) {
    funlable[name]=lable;
}
int Symbol::getfunlable(std::string name) {
    return funlable[name];
}