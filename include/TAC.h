#ifndef _TAC_h__
#define _TAC_h__
#include"global.h"
#include<set>
#include"symbol.h"
class Var {
public:
    TOKEN_TYPE type;
    int spaceID,version;
    std::string name;
    Var* index;
    int val;
    Var();
	bool operator ==(Var &x);
	bool operator <(const Var &x) const;
    void setID(std::string name,int spaceid,int version=0);
    void setNUM(int val);
	Var ArraytoVar();
    void setArray(std::string name,Var* index,int spaceid,int version=0);
    void print();
};
class address {
public: 
    std::string lable;
    OP_TYPE op;
    Var result,arg1,arg2;
    std::vector<Var> args;
    int target;
    address();
    void setlable(std::string);
    void setfunargs(OP_TYPE,std::vector<Var>);
    void setop(OP_TYPE,Var,Var,Var arg2=Var());
    void setjmp(OP_TYPE,int ,Var cond=Var());
    void print();
};
class BaseAST {
public:
    std::shared_ptr<BaseAST> nex;
    void virtual print(){};
    int virtual getval(){};
    Var virtual toTAC(std::vector<address>&){};
    BaseAST() : nex(nullptr){};
};
extern Symbol smb;
class BLOCK {
public:
    std::vector<address> code;
    std::vector<int> to;
    std::set<Var> def,use,IN,OUT;
    BLOCK()=default;
    BLOCK(std::vector<address> x);
    void getDU();
};
class TAC {
public:
    std::vector<address> code;
    std::vector<BLOCK> blocks;
    std::vector<int> codebid;
    TAC()=default;
    void ASTtoTAC(std::shared_ptr<BaseAST> rt);
    void getBlocks();
    void getBlockto();
    void print();
};
address getlable();
address getfunlable();
Var gettmpVar();
#endif
