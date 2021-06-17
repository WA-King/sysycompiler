#include "symbol.h"
BaseVar::BaseVar(TOKEN_TYPE type, bool Const) : type(type), isconst(Const) {}
TOKEN_TYPE BaseVar::gettype() { return type; }
bool BaseVar::getconst() { return isconst; }
VarInt::VarInt(bool Const, int x) : BaseVar(INT, Const), val(x) {}
VarArray::VarArray(bool Const,int len, std::vector<int> x)
    : BaseVar(ARRAY, Const),len(len), val(x) {}
VarFun::VarFun(int x) :len(x){}
Symbol::Symbol() { inspace(); }
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
bool table::insertInt(std::string s, bool Const, int x = 0) {
    if (find(s) != UNDEFINE) return false;
    tb[s] = std::make_shared<VarInt>(Const, x);
    return true;
}
bool table::insertArray(std::string s, bool Const,int len, std::vector<int> x = {}) {
    if (find(s) != UNDEFINE) return false;
    tb[s] = std::make_shared<VarArray>(Const,len, x);
    return true;
}
bool table::insertFun(std::string s,int len) {
    if(find(s)!=UNDEFINE) {
        perror("Funtion \" "+s+" \" redeclare");
        return false;
    }
    tb[s]=std::make_shared<VarFun>(len);
    return true;
}
void Symbol::inspace() { st.push_back(std::make_shared<table>()); }
void Symbol::outspace() { st.pop_back(); }
bool Symbol::insertInt(std::string s, bool Const, int x = 0) {
    if (st.empty()) return false;
    return (*st.back()).insertInt(s, Const, x);
}
bool Symbol::insertArray(std::string s, bool Const,int len, std::vector<int> x = {}) {
    if (st.empty()) return false;
    return (*st.back()).insertArray(s, Const,len, x);
}
bool Symbol::insertFun(std::string s,int len) {
    if (st.empty()) return false;
    if(st.size()!=1) {
        perror("only declare fun in global space");
        return false;
    }
    return (*st.back()).insertFun(s,len);
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
    perror("name: \" "+s+" \" is not declared");
    return nullptr;
}
