#ifndef _AST_h__
#define _AST_h__
#include <memory>
#include <vector>
#include "symbol.h"
#include "TOKEN.h"
#include "TAC.h"
extern Symbol smb;
class ASTIf : public BaseAST {
public:
    std::shared_ptr<BaseAST> Condition, Then, Else;
    ASTIf() = default;
    ASTIf(std::shared_ptr<BaseAST>, std::shared_ptr<BaseAST>,
          std::shared_ptr<BaseAST>);
    Var toTAC(std::vector<address>&) override;
};

class ASTWhile : public BaseAST {
public:
    std::shared_ptr<BaseAST> Condition, Body;
    ASTWhile() = default;
    ASTWhile(std::shared_ptr<BaseAST>, std::shared_ptr<BaseAST>);
    Var toTAC(std::vector<address>&) override;
};
class ASTCallArray : public BaseAST {
public:
    std::string name;
    std::shared_ptr<BaseAST> index;
    int sid;
    ASTCallArray() = default;
    ASTCallArray(std::string, std::shared_ptr<BaseAST>,int =0);
    int getval() override;
    void print() override;
    Var toTAC(std::vector<address>&) override;
};
class ASTCallFun : public BaseAST {
public:
    std::string name;
    std::vector<std::shared_ptr<BaseAST>> args;
    ASTCallFun() = default;
    ASTCallFun(std::string, std::vector<std::shared_ptr<BaseAST>>);
    void print() override;
    int getval() override;
    Var toTAC(std::vector<address>&) override;
};
class ASTExp : public BaseAST {
public:
    std::shared_ptr<BaseAST> expression1, expression2;
    TOKEN_TYPE op;
    ASTExp() = default;
    ASTExp(std::shared_ptr<BaseAST>, std::shared_ptr<BaseAST>, TOKEN_TYPE);
    void print() override;
    int getval() override;
    Var toTAC(std::vector<address>&) override;
};

class ASTLeaf : public BaseAST {
public:
    TOKEN_TYPE valuetype;
    std::string value;
    int sid;
    ASTLeaf() = default;
    ASTLeaf(TOKEN_TYPE, std::string,int =0);
    void print() override;
    int getval() override;
    Var toTAC(std::vector<address>&) override;
};
class ASTDeclareValue : public BaseAST {
public:
    bool isConst;
    TOKEN_TYPE valueType;
    int sid;
    std::string name;
    std::shared_ptr<BaseAST> value;
    ASTDeclareValue() = default;
    ASTDeclareValue(bool, TOKEN_TYPE, std::string, std::shared_ptr<BaseAST>,int);
    void print() override;
    Var toTAC(std::vector<address>&) override;
};

class ASTDeclareArray : public BaseAST {
public:
    bool isConst;
    TOKEN_TYPE valueType;
    int sid,len;
    std::string name;
    std::vector<std::shared_ptr<BaseAST>> value;
    ASTDeclareArray() = default;
    ASTDeclareArray(bool, TOKEN_TYPE, std::string, int,
                    std::vector<std::shared_ptr<BaseAST>>,int);
    void print() override;
    Var toTAC(std::vector<address>&) override;
};
class ASTDeclareFun : public BaseAST {
public:
    TOKEN_TYPE returnType;
    std::string name;
    std::vector<std::pair<std::string,int>> args;
    std::shared_ptr<BaseAST> body;
    ASTDeclareFun() = default;
    ASTDeclareFun(TOKEN_TYPE, std::string,
                  std::vector<std::pair<std::string,int>>,
                  std::shared_ptr<BaseAST>);
    Var toTAC(std::vector<address>&) override;
};
class ASTAssign : public BaseAST {
public:
    TOKEN_TYPE type;
    int sid;
    std::string name;
    std::shared_ptr<BaseAST> index, exp;
    ASTAssign() = default;
    ASTAssign(TOKEN_TYPE, std::string, std::shared_ptr<BaseAST>,
              std::shared_ptr<BaseAST>,int=0);
    Var toTAC(std::vector<address>&) override;
};
class ASTReturn : public BaseAST {
public:
    std::shared_ptr<BaseAST> returnval;
    ASTReturn() = default;
    ASTReturn(std::shared_ptr<BaseAST>);
    Var toTAC(std::vector<address>&) override;
};
class ASTGetint :public BaseAST {
public:
	TOKEN_TYPE type;
	std::string name;
	std::shared_ptr<BaseAST> index;
	int sid;
	ASTGetint()=default;
	ASTGetint(TOKEN_TYPE,std::string,std::shared_ptr<BaseAST>,int);
    Var toTAC(std::vector<address>&) override;
};
class ASTPrintint :public BaseAST {
public:
	TOKEN_TYPE type;
	std::string name;
	int sid;
	std::shared_ptr<BaseAST> index;
	ASTPrintint()=default;
	ASTPrintint(TOKEN_TYPE,std::string,std::shared_ptr<BaseAST>,int);
    Var toTAC(std::vector<address>&) override;
};
#endif
