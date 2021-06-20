#include "AST.h"

#include "iostream"
Symbol smb;
#define LZNB(x)                  \
    case (x):                    \
        std::cout << #x << '\n'; \
        break;
void PrintTOKEN_TYPE(TOKEN_TYPE x) {
    switch (x) {
        LZNB(ID);
        LZNB(NUM);
        LZNB(ADD);
        LZNB(MINUS);
        LZNB(MUL);
        LZNB(DIV);
        LZNB(MOD);
        LZNB(AND);
        LZNB(OR);
        LZNB(EQ);
        LZNB(NE);
        LZNB(GT);
        LZNB(GE);
        LZNB(LT);
        LZNB(LE);
        default:
            std::cout << "print erro" << '\n';
            break;
    }
}
ASTDeclareValue::ASTDeclareValue(bool Const, TOKEN_TYPE type, std::string name,
                                 std::shared_ptr<BaseAST> val,int sid)
    : isConst(Const), valueType(type), name(name), value(val),sid(sid) {}

ASTDeclareArray::ASTDeclareArray(bool isconst, TOKEN_TYPE type,
                                 std::string name, int len,
                                 std::vector<std::shared_ptr<BaseAST>> val,int sid)
    : isConst(isconst), valueType(type), name(name), len(len), value(val),sid(sid) {}

ASTDeclareFun::ASTDeclareFun(
    TOKEN_TYPE type, std::string name,
    std::vector<std::pair<std::string,int>> args,
    std::shared_ptr<BaseAST> body)
    : returnType(type), name(name), args(args), body(body) {}
ASTCallArray::ASTCallArray(std::string name, std::shared_ptr<BaseAST> idx,int x)
    : name(name), index(idx),sid(x){};
void ASTCallArray::print() {
    std::cout<<"array: "<<name<<'\n';
    std::cout<<"index: "<<'\n';
    index->print();
}
int ASTCallArray::getval() {
    std::shared_ptr<BaseVar> tmp=smb.getVar(name);
    if(tmp==nullptr) {
        printerror("\" "+name+" \" not defined");
    }
    if(tmp->gettype()!=ARRAY) {
        printerror("\" "+name+" \" is not a ARRAY");
    }
    if(tmp->getconst()==false) {
        printerror("\" "+name+" \" is not a const Var");
    }
    std::shared_ptr<VarArray> var=std::dynamic_pointer_cast<VarArray>(tmp);
    int len=index->getval();
    if(var->len<=len) {
        std::cout<<var->len<<' '<<len<<'\n';
        printerror("ARRAY index off");
    }
    if(var->val.size()>len) return var->val[len];
    else return 0;
}
ASTCallFun::ASTCallFun(std::string name,
                       std::vector<std::shared_ptr<BaseAST>> args)
    : name(name), args(args) {}
void ASTCallFun::print() {
    std::cout << "Funname: " << name << '\n';
    std::cout << "Funval: " << '\n';
    for (auto x : args) {
        x->print();
        std::cout << "######\n";
    }
    std::cout << "EndFunval: " << '\n';
}
int ASTCallFun::getval() {
    printerror("fun val is not const");
    return 0;
}
ASTIf::ASTIf(std::shared_ptr<BaseAST> Condition, std::shared_ptr<BaseAST> ThenB,
             std::shared_ptr<BaseAST> ElseB)
    : Condition(Condition), Then(ThenB), Else(ElseB) {}

ASTWhile::ASTWhile(std::shared_ptr<BaseAST> Condition,
                   std::shared_ptr<BaseAST> Body)
    : Condition(Condition), Body(Body){};

ASTExp::ASTExp(std::shared_ptr<BaseAST> expression1,
               std::shared_ptr<BaseAST> expression2, TOKEN_TYPE op)
    : expression1(expression1), expression2(expression2), op(op) {}
int ASTExp::getval() {
    if (expression1 == nullptr) {
        int val1=expression2->getval();
        switch(op) {
            case ADD:
                break;
            case MINUS:
                val1=-val1;
                break;
            default:
                printerror("single exp error");
                break;
        }
        return val1;
    }
    int val1=expression1->getval(),val2=expression2->getval();
    //std::cout<<"VAL:"<<val1<<' '<<val2<<'\n';
    int ans;
    switch(op) {
        case ADD:
            ans=val1+val2;
            break;
        case MINUS:
            ans=val1-val2;
            break;
        case MUL:
            ans=val1*val2;
            break;
        case DIV: {
            if(val2==0) {
                printerror("erro is div 0 ");
            }
            ans=val1/val2;
            break;
        } 
        case MOD:
            ans=val1%val2;
            break;
        default:
            printerror("double exp error");
            break;
    }
    return ans;
}
void ASTExp::print() {
    if (expression1 != nullptr)
        expression1->print();
    else
        std::cout << "single ";
    if (expression2 != nullptr) expression2->print();
    PrintTOKEN_TYPE(op);
}
ASTLeaf::ASTLeaf(TOKEN_TYPE type, std::string value,int x)
    : valuetype(type), value(value),sid(x) {}
void ASTLeaf::print() { std::cout << "leaf:" << value << '\n'; }
int ASTLeaf::getval() {
    if(valuetype==NUM) {
        int num=0;
        for(char c:value) num=num*10+c-'0';
        return num;
    }
    else if(valuetype==ID) {
        std::shared_ptr<BaseVar> tmp=smb.getVar(value);
        if(tmp->gettype()!=INT) {
            printerror("\" "+value+" \" is not INT");
        }
        if(tmp->getconst()==false) {
            printerror("\" "+value+" \" is not const Var");
        }
        std::shared_ptr<VarInt> var=std::dynamic_pointer_cast<VarInt>(tmp);
        return var->val;
    }
}
void ASTDeclareValue::print() {
    std::cout << "VAR: " << name << "= " << '\n';
    if (value != nullptr) value->print();
    if (nex != nullptr) nex->print();
}
void ASTDeclareArray::print() {
    std::cout << "ARRAY: " << name << '\n';
    std::cout << "len: " << len <<'\n';
    std::cout << "VALUE: " << '\n';
    for (auto x : value) {
        x->print();
        std::cout << "###############" << '\n';
    }
    if (nex != nullptr) nex->print();
}
ASTAssign::ASTAssign(TOKEN_TYPE type, std::string name,
                     std::shared_ptr<BaseAST> index,
                     std::shared_ptr<BaseAST> exp,int x)
    : type(type), name(name), index(index), exp(exp),sid(x) {}

ASTReturn::ASTReturn(std::shared_ptr<BaseAST> exp) : returnval(exp) {}

ASTGetint::ASTGetint(TOKEN_TYPE type,
					std::string name,
					std::shared_ptr<BaseAST> index,int sid)
	: type(type),name(name),index(index),sid(sid){}

ASTPrintint::ASTPrintint(TOKEN_TYPE type,
					std::string name,
					std::shared_ptr<BaseAST> index,int sid)
	: type(type),name(name),index(index),sid(sid){}
/*
1.
cond
jf cond to lable1
THEN
jmp lable2
label1 
Else
lable 2

2.
cond
jf cond to lable1
THEN
label1 
*/
Var ASTIf::toTAC(std::vector<address>&ans) {
    //cond
    Var cond=Condition->toTAC(ans);
    //add jmp
    int L1=ans.size();
    address tmp=address();
    tmp.setjmp(OP_JF,-1,cond);
    ans.push_back(tmp);
    //then
    if(Then!=nullptr) Then->toTAC(ans);
    if(Else!=nullptr) {
        //add jmp
        tmp=address();
        int L2=ans.size();
        tmp.setjmp(OP_J,-1);
        ans.push_back(tmp);
        //add lable1
        ans[L1].target=ans.size();
        ans.push_back(getlable());
        //Else
        Else->toTAC(ans);
        //add label2
        ans[L2].target=ans.size();
        ans.push_back(getlable());
    }
    else {
        //add lable1
        ans[L1].target=ans.size();
        ans.push_back(getlable());
    }
    if(nex!=nullptr) this->nex->toTAC(ans);
    return Var();
}
/*
lable 1
cond
jf cond to labl2 
body
jmp lable1
lable 2
*/
Var ASTWhile::toTAC(std::vector<address>& ans) {
    //add label1
    int lable1=ans.size();
    ans.push_back(getlable());
    //cond
    Var cond=Condition->toTAC(ans);
    //add jmp to label2
    int L2=ans.size();
    address tmp=address();
    tmp.setjmp(OP_JF,-1,cond);
	ans.push_back(tmp);
    // body
    Body->toTAC(ans);
    //add jmp to lable1
    tmp=address();
    tmp.setjmp(OP_J,lable1);
	ans.push_back(tmp);
	int lable2=ans.size();
    ans[L2].target=lable2;
    ans.push_back(getlable());
	for(int i=lable1;i<=lable2;i++) {
		if(ans[i].op==OP_BREAK&&ans[i].target==-1) {
			ans[i].op=OP_J;
			ans[i].target=lable2;
		}
		if(ans[i].op==OP_CONTINUE&&ans[i].target==-1) {
			ans[i].op=OP_J;
			ans[i].target=lable1;
		}
	}
    if(nex!=nullptr) this->nex->toTAC(ans);
    return Var();
}
/*
index
exp
OP_AS result exp
*/
Var ASTAssign::toTAC(std::vector<address>&ans) {
    if(type==ARRAY) {
        Var idx=index->toTAC(ans);
        Var ep=exp->toTAC(ans);
        Var result=Var();
        result.setArray(name,new Var(idx),sid);
        address tmp=address();
        tmp.setop(OP_ASSIGN,result,ep);
        ans.push_back(tmp);
    }
    else if(type==ID) {
        Var result=Var();
        result.setID(name,sid);
        Var ep=exp->toTAC(ans);
        address tmp;
        tmp.setop(OP_ASSIGN,result,ep);
        ans.push_back(tmp);
    }
    if(nex!=nullptr) this->nex->toTAC(ans);
    return Var();
}
Var ASTExp::toTAC(std::vector<address>& ans) {
    Var tmpVar=gettmpVar();
    //single
    if(expression1==nullptr) {
        Var exp2=expression2->toTAC(ans);
		int val=exp2.val;
        address tmp;
        switch (op) {
            case MINUS:{
                tmp.setop(OP_NEG,tmpVar,exp2);
        		ans.push_back(tmp);
				val=-val;
                break;
			}
            case ADD:
                tmpVar=exp2;
                break;
            default:
                printerror("ASTExp to TAC wrong");
        }
		if(exp2.type==NUM) {
			tmpVar=Var();
			tmpVar.setNUM(val);
		}
    }
    else if(expression1!=nullptr&&expression2!=nullptr) {
        Var exp1=expression1->toTAC(ans),exp2=expression2->toTAC(ans);
		int val1=exp1.val,val2=exp2.val,val;
        address tmp;
        switch(op) {
            case ADD : {
                tmp.setop(OP_ADD,tmpVar,exp1,exp2);
				val=val1+val2;
                break;
			}
            case MINUS : {
                tmp.setop(OP_MINUS,tmpVar,exp1,exp2);
				val=val1-val2;
                break;
			}
            case MUL : {
                tmp.setop(OP_MUL,tmpVar,exp1,exp2);
				val=val1*val2;
                break;
			}
            case DIV : {
				if(exp2.type==NUM) {
					if(val2==0) {
						printerror("toTAC: div 0");
					}
					val=val1/val2;
				}
                tmp.setop(OP_DIV,tmpVar,exp1,exp2);
                break;
			}
            case MOD : {
				if(exp2.type==NUM) {
					if(val2==0) {
						printerror("toTAC: mod 0");
					}
					val=val1%val2;
				}
                tmp.setop(OP_MOD,tmpVar,exp1,exp2);
                break;
			}
            case OR : {
                tmp.setop(OP_OR,tmpVar,exp1,exp2);
				val=val1|val2;
                break;
			}
            case AND : {
				val=val1&val2;
                tmp.setop(OP_AND,tmpVar,exp1,exp2);
                break;
			}
            case EQ : {
				val=(val1==val2);	
                tmp.setop(OP_EQ,tmpVar,exp1,exp2);
                break;
			}
            case NE : {
				val=(val1!=val2);
                tmp.setop(OP_NE,tmpVar,exp1,exp2);
                break;
			}
            case GE : {
				val=(val1>=val2);
                tmp.setop(OP_GE,tmpVar,exp1,exp2);
                break;
			}
            case GT : {
				val=(val1>val2);	
                tmp.setop(OP_GT,tmpVar,exp1,exp2);
                break;
			}
            case LE : {
				val=(val1<=val2);
                tmp.setop(OP_LE,tmpVar,exp1,exp2);
                break;
			}
            case LT: {
				val=(val1<val2);
                tmp.setop(OP_LT,tmpVar,exp1,exp2);
                break;
			}
            default:
                printerror("ASTExp to TAC wrong");
        }
		if(exp1.type==NUM&&exp2.type==NUM) {
			tmpVar=Var();
			tmpVar.setNUM(val);
		}
        else ans.push_back(tmp);
    }
    if(nex!=nullptr) this->nex->toTAC(ans);
    return tmpVar;
}
Var ASTLeaf::toTAC(std::vector<address>& ans) {
    Var re;
    if(valuetype==NUM) {
        int val=getval();
        re.setNUM(val);
    }
    else if(valuetype==ID) {
        re.setID(value,sid);
    }
    return re;
}
Var ASTCallArray::toTAC(std::vector<address> &ans) {
    Var re,idx=index->toTAC(ans);
    re.setArray(name,new Var(idx),sid);
    return re;
}
Var ASTDeclareValue::toTAC(std::vector<address> &ans) {
	address tmp=address();
	Var Lval;
	Lval.setID(name,sid);
	tmp.setop(OP_DECLARE,Lval,Var());
	ans.push_back(tmp);
    if(value!=nullptr) {
		Var val=value->toTAC(ans);
		Lval=Var();
		Lval.setID(name,sid);
		tmp=address();
		tmp.setop(OP_ASSIGN,Lval,val);
		ans.push_back(tmp);
	}
    if(nex!=nullptr) nex->toTAC(ans);
    return Var();
}
Var ASTDeclareArray::toTAC(std::vector<address> &ans) {
	address tmp=address();
	Var Lval,Len;
	Lval.setID(name,sid);
	Len.setNUM(len);
	tmp.setop(OP_DECLARE,Lval,Len);
	ans.push_back(tmp);
    if(value.size()!=0) {
		for(int i=0;i<value.size();i++) {
			Var Lval,Rval=value[i]->toTAC(ans);
			Var idx;
			idx.setNUM(i);
			Lval.setArray(name,new Var(idx),sid);
			address tmp=address();
			tmp.setop(OP_ASSIGN,Lval,Rval);
			ans.push_back(tmp);
		}
	}
    if(nex!=nullptr) nex->toTAC(ans);
    return Var();
}
/*
lable fun
set param1 ...
body
lable return
return
*/
Var ASTDeclareFun::toTAC(std::vector<address>& ans) {
    smb.insertfunlable(name,ans.size());
    ans.push_back(getfunlable());
    std::vector<Var> funargs;
    for(auto x:args) {
        Var Lval;
        Lval.setID(x.first,x.second);
        funargs.push_back(Lval);
    }
    address tmp;
    tmp.setfunargs(OP_SETPARAM,funargs);
    ans.push_back(tmp);
    int l=ans.size();
    body->toTAC(ans);
    int returnlabel=ans.size();
    for(int i=l;i<ans.size();i++) {
        if(ans[i].op==OP_J&&ans[i].target==-1) 
            ans[i].target=returnlabel;
    }
    ans.push_back(getlable());
    tmp=address();
    tmp.setop(OP_OUTFUN,Var(),Var());
    ans.push_back(tmp);
    if(nex!=nullptr) nex->toTAC(ans);
    return Var();
}
Var ASTReturn::toTAC(std::vector<address>& ans) {
    address tmp;
    if(returnval!=nullptr) {
        Var val=returnval->toTAC(ans);
        tmp.setop(OP_SETRETURN,val,Var());
        ans.push_back(tmp);
    }
    tmp.setjmp(OP_J,-1);
    ans.push_back(tmp);
    if(nex!=nullptr) nex->toTAC(ans);
    return Var();
}
Var ASTCallFun::toTAC(std::vector<address>& ans) {
    std::vector<Var> funargs;
    for(auto x:args) {
        Var y=x->toTAC(ans);
        funargs.push_back(y);
    }
    address tmp;
    tmp.setfunargs(OP_PUSHPARAM,funargs);
    ans.push_back(tmp);
    tmp=address();
    tmp.setjmp(OP_CALL,smb.getfunlable(name));
    ans.push_back(tmp);
	std::shared_ptr<BaseVar> f1=smb.getVar(name);
	std::shared_ptr<VarFun> fun=std::dynamic_pointer_cast<VarFun>(f1);
	Var re=Var();
	if(fun->returntype==INT) {
		re=gettmpVar();
		tmp=address();
		tmp.setop(OP_GETRETURN,re,Var());
		ans.push_back(tmp);
	}
    if(nex!=nullptr) nex->toTAC(ans);
	return re;
}
Var ASTGetint::toTAC(std::vector<address>& ans) {
	address tmp;
	Var Lval;
	if(type==INT) {
		Lval.setID(name,sid);
	}
	else {
		Var id=index->toTAC(ans);
		Lval.setArray(name,new Var(id),sid);
	}
	tmp.setop(OP_GETINT,Lval,Var());
	ans.push_back(tmp);
	if(nex!=nullptr) nex->toTAC(ans);
	return Var();
}
Var ASTPrintint::toTAC(std::vector<address>& ans) {
	address tmp;
	Var Lval;
	if(type==INT) {
		Lval.setID(name,sid);
	}
	else {
		Var id=index->toTAC(ans);
		Lval.setArray(name,new Var(id),sid);
	}
	tmp.setop(OP_PINRTINT,Lval,Var());
	ans.push_back(tmp);
	if(nex!=nullptr) nex->toTAC(ans);
	return Var();
}
Var ASTBreak::toTAC(std::vector<address>& ans) {
	address tmp;
	tmp.setjmp(OP_BREAK,-1);
	ans.push_back(tmp);
	if(nex!=nullptr) nex->toTAC(ans);
	return Var();
}
Var ASTContinue::toTAC(std::vector<address>& ans) {
	address tmp;
	tmp.setjmp(OP_CONTINUE,-1);
	ans.push_back(tmp);
	if(nex!=nullptr) nex->toTAC(ans);
	return Var();
}
