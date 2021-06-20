#include "parser.h"

#include <iostream>

Parse::Parse(std::string filename) : returntype(UNDEFINE),SCAN(filename) {}
void Parse::NextTOKEN() {
    Last = getToken();
    //PrintTOKEN_TYPE(Last.type);
    //std::cout << '\n';
    //std::cout<<' '<<Last.val<<'\n';
}
TOKEN Parse::Match(TOKEN_TYPE t) {
    if (Last.type == t) {
        TOKEN tmp = Last;
        NextTOKEN();
        return tmp;
    } else {
        std::cout<<Last.type<<'\n';
        PrintTOKEN_TYPE(Last.type);
        std::cout << "->";
        PrintTOKEN_TYPE(t);
        std::cout << '\n';
        std::cout << "FUCK" << '\n';
        exit(0);
    }
}
std::shared_ptr<BaseAST> Parse::getFunDecl(TOKEN_TYPE type,std::string name) {
    if(name=="") name=Match(ID).val;
	//std::cout<<name<<'\n';
    if(smb.find(name)!=UNDEFINE) {
        printerror("this function has been declared");
    }
    returntype=type;
    smb.inspace();
    Match(LSBRACKETS);
    std::vector<std::pair<std::string,int>> args;
    while(Last.type==INT) {
        Match(INT);
        std::string name_arg=Match(ID).val;
        smb.insertInt(name_arg,false,0);
        args.push_back({name_arg,smb.getVar(name_arg)->sid});
        if(Last.type==COMMA) Match(COMMA);
        else break;
    }
    Match(RSBRACKETS);
    smb.insertFun(name,args.size(),type);
    std::shared_ptr<BaseAST> body=getBlock(false);
    returntype=UNDEFINE;
    smb.outspace();
    smb.insertFun(name,args.size(),type);
    return std::make_shared<ASTDeclareFun>(type,name,args,body);
}
std::shared_ptr<BaseAST> Parse::getCompUnit() {
    std::shared_ptr<BaseAST> rt=nullptr,nex=nullptr;
    while(Last.type==INT||Last.type==CONST||Last.type==VOID) {
        std::shared_ptr<BaseAST> tmp;
        if(Last.type==CONST) {
            tmp=getConstDecl();
        }
        else if(Last.type==VOID) {
            Match(VOID);
            tmp=getFunDecl(VOID);
        }
        else if(Last.type==INT) {
            Match(INT);
            std::string name=Match(ID).val;
            if(Last.type==LSBRACKETS) { 
                tmp=getFunDecl(INT,name);
            }
            else {
                tmp=getVarDecl(false,name);
            }
        }
        if(rt==nullptr) {
            rt=tmp;
            nex=tmp;
        }
        else {
            nex->nex=tmp;
            nex=tmp;
        }
        while(nex->nex!=nullptr) nex=nex->nex;
    }
    return rt;
}
std::shared_ptr<BaseAST> Parse::getAddExp() {
    std::shared_ptr<BaseAST> rt = getMulExp();
    while (Last.type == ADD || Last.type == MINUS) {
        TOKEN_TYPE op = Last.type;
        NextTOKEN();
        rt = std::make_shared<ASTExp>(rt, getMulExp(), op);
    }
    if(rt==nullptr) {
        printerror("get null exp");
    }
    return rt;
}
std::shared_ptr<BaseAST> Parse::getMulExp() {
    std::shared_ptr<BaseAST> rt = getUnaryExp();
    while (Last.type == MUL || Last.type == DIV || Last.type == MOD) {
        TOKEN_TYPE op = Last.type;
        NextTOKEN();
        rt = std::make_shared<ASTExp>(rt, getUnaryExp(), op);
    }
    return rt;
}
std::vector<std::shared_ptr<BaseAST>> Parse::getFunArgs() {
    Match(LSBRACKETS);
    std::vector<std::shared_ptr<BaseAST>> tmp;
    if (Last.type == RSBRACKETS) {
        Match(RSBRACKETS);
        return tmp;
    }
    tmp.push_back(getAddExp());
    while (Last.type == COMMA) {
        Match(COMMA);
        tmp.push_back(getAddExp());
    }
    Match(RSBRACKETS);
    return tmp;
}
std::shared_ptr<BaseAST> Parse::getUnaryExp() {
    std::shared_ptr<BaseAST> rt;
    switch (Last.type) {
        case LSBRACKETS: {
            Match(LSBRACKETS);
            rt = getAddExp();
            Match(RSBRACKETS);
            break;
        }
        case NUM: {
            rt = std::make_shared<ASTLeaf>(Last.type, Last.val);
            NextTOKEN();
            break;
        }
        case ADD:
        case MINUS: {
            TOKEN_TYPE op = Last.type;
            NextTOKEN();
            rt = std::make_shared<ASTExp>(nullptr, getUnaryExp(), op);
            break;
        }
        case ID: {
            std::string name = Match(ID).val;
            if(smb.find(name)==UNDEFINE) {
                printerror("\" "+name+" \"is not declare"); 
            }
            std::shared_ptr<BaseVar> tmp=smb.getVar(name);
            if (Last.type == LMBRACKETS) {
                if(tmp->gettype()!=ARRAY) {
                    printerror("\" "+name+" \"is not a ARRAY"); 
                }
                Match(LMBRACKETS);
                rt = std::make_shared<ASTCallArray>(name, getAddExp(),smb.getVar(name)->sid);
                Match(RMBRACKETS);
            } else if (Last.type == LSBRACKETS) {
                if(tmp->gettype()!=FUNCTION) {
                    printerror("\" "+name+" \"is not a FUNCTION"); 
                }
				std::vector<std::shared_ptr<BaseAST>> args=getFunArgs();
				std::shared_ptr<BaseVar> tmp=smb.getVar(name);
				std::shared_ptr<VarFun> fun=std::dynamic_pointer_cast<VarFun>(tmp);
				if(fun->len!=args.size()) {
					printerror(name+" the number of funargs is wrong");
				}
				if(fun->returntype==VOID) {
					printerror("can't call VOID function in EXP");
				}
                rt = std::make_shared<ASTCallFun>(name, args);

            } else {
                if(tmp->gettype()!=INT) {
                    printerror("\" "+name+" \"is not a INT"); 
                }
                rt = std::make_shared<ASTLeaf>(ID, name,smb.getVar(name)->sid);
            }
            break;
        }
        default:
            break;
    }
    return rt;
}
std::shared_ptr<BaseAST> Parse::getLOrExp() {
    std::shared_ptr<BaseAST> rt = getLAndExp();
    while (Last.type == OR) {
        NextTOKEN();
        rt = std::make_shared<ASTExp>(rt, getLAndExp(), OR);
    }
    return rt;
}
std::shared_ptr<BaseAST> Parse::getLAndExp() {
    std::shared_ptr<BaseAST> rt = getEqExp();
    while (Last.type == AND) {
        NextTOKEN();
        rt = std::make_shared<ASTExp>(rt, getEqExp(), AND);
    }
    return rt;
}
std::shared_ptr<BaseAST> Parse::getEqExp() {
    std::shared_ptr<BaseAST> rt = getRelExp();
    while (Last.type == EQ || Last.type == NE) {
        TOKEN_TYPE op = Last.type;
        NextTOKEN();
        rt = std::make_shared<ASTExp>(rt, getRelExp(), op);
    }
    return rt;
}
std::shared_ptr<BaseAST> Parse::getRelExp() {
    std::shared_ptr<BaseAST> rt = getAddExp();
    while (Last.type == GT || Last.type == GE || Last.type == LT ||
           Last.type == LE) {
        TOKEN_TYPE op = Last.type;
        NextTOKEN();
        rt = std::make_shared<ASTExp>(rt, getAddExp(), op);
    }
    return rt;
}
std::shared_ptr<BaseAST> Parse::getBlock(bool f) {
    std::shared_ptr<BaseAST> rt=nullptr,nex;
    Match(LBBRACKETS);
    if(f) smb.inspace();
    while(Last.type!=RBBRACKETS) {
        std::shared_ptr<BaseAST> tmp;
        switch (Last.type) {
            case INT:{
                tmp = getVarDecl(false);
                break;
            }
            case CONST: {
                tmp = getConstDecl();
                break;
            }
            default: {
                tmp = getStmt();
                break;
			}
        }
        if(rt==nullptr) {
            rt=tmp;
            nex=rt;
        }
        else {
            nex->nex=tmp;
            nex=tmp;
        }
        while(nex->nex!=nullptr) {
			nex=nex->nex;
		} 
    }
    if(f) smb.outspace();
    Match(RBBRACKETS);
    return rt;
}
std::vector<std::shared_ptr<BaseAST>> Parse::getIntList() {
    Match(LBBRACKETS);
    std::vector<std::shared_ptr<BaseAST>> tmp;
    if (Last.type == RBBRACKETS) {
        Match(RBBRACKETS);
        return tmp;
    }
    tmp.push_back(getAddExp());
    while (Last.type == COMMA) {
        Match(COMMA);
        tmp.push_back(getAddExp());
    }
    Match(RBBRACKETS);
    return tmp;
}
std::shared_ptr<BaseAST> Parse::getVarDef(bool isconst,std::string name) {
    if(name=="") name = Match(ID).val;
    std::shared_ptr<BaseAST> rt;
    if (Last.type == LMBRACKETS) {//ARRAY
        Match(LMBRACKETS);
        std::shared_ptr<BaseAST> len = getAddExp();
        Match(RMBRACKETS);
        std::vector<std::shared_ptr<BaseAST>> val;
        if (Last.type == ASSIGN) {
            Match(ASSIGN);
            val = getIntList();
        }
        if(isconst) {
            std::vector<int> constval;
            for(auto x:val) {
                constval.push_back(x->getval());
            }
            smb.insertArray(name,isconst,len->getval(),constval);
        }
        else smb.insertArray(name,isconst,len->getval(),{});
        rt = std::make_shared<ASTDeclareArray>(isconst, INT, name, len->getval(), val,smb.getVar(name)->sid);
    } else {//INT
        std::shared_ptr<BaseAST> val(nullptr);
        if (Last.type == ASSIGN) {
            Match(ASSIGN);
            val = getAddExp();
        }
        if(isconst) smb.insertInt(name,isconst,val==nullptr?0:val->getval());
        else  smb.insertInt(name,isconst,0);
        rt = std::make_shared<ASTDeclareValue>(isconst, INT, name, val,smb.getVar(name)->sid);
    }
    return rt;
}
std::shared_ptr<BaseAST> Parse::getVarDecl(bool isconst,std::string name) {
    if(name=="") {
        Match(INT);
        name=Match(ID).val;
    }
    std::shared_ptr<BaseAST> rt = getVarDef(isconst,name);
    std::shared_ptr<BaseAST> tmp = rt;
    while (Last.type == COMMA) {
        Match(COMMA);
        tmp->nex = getVarDef(isconst);
        tmp = tmp->nex;
    }
    Match(SEMICOLON);
    return rt;
}
std::shared_ptr<BaseAST> Parse::getConstDecl() {
    Match(CONST);
    return getVarDecl(true);
}
std::shared_ptr<BaseAST> Parse::getStmt() {
    std::shared_ptr<BaseAST> rt;
    switch (Last.type) {
        case IF:
            rt = getIfStmt();
            break;
        case WHILE: {
            rt = getWhileStmt();
            break;
		}
        case LBBRACKETS:
            rt = getBlock();
            break;
        case ID: {
            std::string name = Match(ID).val;
            std::shared_ptr<BaseAST> index;
            TOKEN_TYPE type;
            if (Last.type == LMBRACKETS) {
                type = ARRAY;
                Match(LMBRACKETS);
                index = getAddExp();
                Match(RMBRACKETS);
            } else
                type = ID;
            if (Last.type == ASSIGN) {
				Match(ASSIGN);
                rt = std::make_shared<ASTAssign>(type, name, index, getAddExp(),smb.getVar(name)->sid);
            } else if (Last.type == LSBRACKETS && type == ID) {
				if(smb.find(name)==UNDEFINE) {
					printerror(name+" function is not declare");
				}
				if(name=="getint") {
					rt=getGetint();	
				}
				else if(name=="printint") {
					rt=getPrintint();	
				}
				else {
					std::vector<std::shared_ptr<BaseAST>> args=getFunArgs();
					std::shared_ptr<BaseVar> tmp=smb.getVar(name);
					std::shared_ptr<VarFun> fun=std::dynamic_pointer_cast<VarFun>(tmp);
					if(fun->len!=args.size()) {
						printerror(name+" the number of funargs is wrong");
					}
					rt = std::make_shared<ASTCallFun>(name, args);
				}
            }
            Match(SEMICOLON);
            break;
        }
        case RETURN: {
            Match(RETURN);
            if(returntype==INT) {
                rt = std::make_shared<ASTReturn>(getAddExp());
            }
			else {
                rt = std::make_shared<ASTReturn>(nullptr);
			}
            Match(SEMICOLON);
            break;
        }
		case BREAK : {
			if(inloops<=0) {
				printerror("break not in loops statements");
			}
			Match(BREAK);
			rt=std::make_shared<ASTBreak>();
			Match(SEMICOLON);
			break;
		}
		case CONTINUE : {
			if(inloops<=0) {
				printerror("continue not in loops statements");
			}
			Match(CONTINUE);
			rt=std::make_shared<ASTContinue>();
			Match(SEMICOLON);
			break;
		}
        default:
            break;
    }
    return rt;
}
std::shared_ptr<BaseAST> Parse::getIfStmt() {
    std::shared_ptr<BaseAST> Condition, Then, Else(nullptr);
    Match(IF);
    Match(LSBRACKETS);
    Condition = getLOrExp();
    Match(RSBRACKETS);
    Then = getStmt();
    if (Last.type == ELSE) {
        Match(ELSE);
        Else = getStmt();
    }
    return std::make_shared<ASTIf>(Condition, Then, Else);
}
std::shared_ptr<BaseAST> Parse::getWhileStmt() {
    std::shared_ptr<BaseAST> Condition, Body;
    Match(WHILE);
    Match(LSBRACKETS);
    Condition = getLOrExp();
    Match(RSBRACKETS);
	inloops++;
    Body = getStmt();
	inloops--;
    return std::make_shared<ASTWhile>(Condition, Body);
}
std::shared_ptr<BaseAST> Parse::getGetint() {
	Match(LSBRACKETS);
	std::string name=Match(ID).val;
	std::shared_ptr<BaseAST> rt;
	if(Last.type==LMBRACKETS) {
		Match(LMBRACKETS);
		rt=std::make_shared<ASTGetint>(ARRAY,name,getAddExp(),smb.getVar(name)->sid);
		Match(RMBRACKETS);
	}
	else {
		rt=std::make_shared<ASTGetint>(INT,name,nullptr,smb.getVar(name)->sid);
	}
	Match(RSBRACKETS);
	return rt;
}
std::shared_ptr<BaseAST> Parse::getPrintint() {
	Match(LSBRACKETS);
	std::string name=Match(ID).val;
	std::shared_ptr<BaseAST> rt;
	if(Last.type==LMBRACKETS) {
		Match(LMBRACKETS);
		rt=std::make_shared<ASTPrintint>(ARRAY,name,getAddExp(),smb.getVar(name)->sid);
		Match(RMBRACKETS);
	}
	else {
		rt=std::make_shared<ASTPrintint>(INT,name,nullptr,smb.getVar(name)->sid);
	}
	Match(RSBRACKETS);
	return rt;
}