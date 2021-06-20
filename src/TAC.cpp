#include"TAC.h"
#include"algorithm"
#define printOP(x)               \
    case (x):                    \
        std::cout << #x ;        \
        break;
void PrintOP_TYPE(OP_TYPE x) {
    switch (x) {
        printOP(NUL);
        printOP(OP_ADD);
        printOP(OP_MINUS);
        printOP(OP_NEG);
        printOP(OP_MUL);
        printOP(OP_DIV);
        printOP(OP_MOD);
        printOP(OP_AND);
        printOP(OP_OR);
        printOP(OP_EQ);
        printOP(OP_NE);
        printOP(OP_GT);
        printOP(OP_GE);
        printOP(OP_LT);
        printOP(OP_LE);
        printOP(OP_JF);
        printOP(OP_JT);
        printOP(OP_J);
        printOP(OP_OUTFUN);
        printOP(OP_SETPARAM);
        printOP(OP_ASSIGN);
        printOP(OP_SETRETURN);
        printOP(OP_PUSHPARAM);
        printOP(OP_CALL);
		printOP(OP_DECLARE);
		printOP(OP_PINRTINT);
		printOP(OP_GETINT);
		printOP(OP_GETRETURN);
		printOP(OP_CONTINUE);
		printOP(OP_BREAK);
        default:
			printerror("PrintOP_TYPE erro");
            break;
    }
}
Var::Var():type(UNDEFINE){}
void Var::setID(std::string name,int spaceID,int version) {
    type=ID;
    this->name=name;
    this->spaceID=spaceID;
    this->version=version;
}
void Var::setNUM(int val) {
    type=NUM;
    this->val=val;
}
void Var::setArray(std::string name,Var* index,int spaceID,int version) {
    type=ARRAY;
    this->name=name;
    this->index=index;
    this->spaceID=spaceID;
    this->version=version;
}
bool Var::operator ==(Var &x) {
	if(x.type!=this->type) return false;
	if(x.type==ID||x.type==ARRAYBASE) {
		return x.name==this->name&&x.spaceID==this->spaceID&&x.version==this->version;
	}
	if(x.type==NUM) {
		return x.val==this->val;
	}
}
bool Var::operator <(const Var &x)const {
	if(x.type!=this->type) {
		return this->type<x.type;
	}
	if(x.type==ID||x.type==ARRAYBASE||x.type==ARRAY) {
		return this->name<x.name;
	}
	if(x.type==NUM) {
		return this->val<x.val;
	}
}
Var Var::ArrayBase() {
	Var tmp=Var();
	tmp.setID(this->name,this->spaceID,this->version);
    tmp.type=ARRAYBASE;
	return tmp;
}
address::address():lable(""),op(NUL),target(-1) {}
void address::setlable(std::string x) {
    lable=x;
}
void address::setfunargs(OP_TYPE type,std::vector<Var> x) {
    op=type;
    args=x;
}
void address::setop(OP_TYPE type,Var re,Var a,Var b) {
    op=type;
    result=re;
    arg1=a;
    arg2=b;
}
void address::setjmp(OP_TYPE type,int to,Var cond) {
    op=type;
    arg1=cond;
    target=to;
}

void TAC::ASTtoTAC(std::shared_ptr<BaseAST>rt) {
    rt->toTAC(code);
}
Var gettmpVar() {
    static int id_cnt=1;
    int now=1;
    std::string tmp="";
    while(now<=id_cnt){
        tmp+=(id_cnt/now%10)+'0';
        now*=10;
    }
    id_cnt++;
    reverse(tmp.begin(),tmp.end());
    Var re=Var();
    re.setID("%T"+tmp,-1);
    return re;
}
address getlable() {
    static int id_cnt=1;
    int now=1;
    std::string tmp="";
    while(now<=id_cnt){
        tmp+=(id_cnt/now%10)+'0';
        now*=10;
    }
    id_cnt++;
    reverse(tmp.begin(),tmp.end());
    address re=address();
    re.setlable("L"+tmp);
    return re;
}
address getfunlable() {
	static int id_cnt=1;
	int now=1;
	std::string tmp="";
	while(now<=id_cnt) {
		tmp+=(id_cnt/now%10)+'0';
		now*=10;
	}
	id_cnt++;
	reverse(tmp.begin(),tmp.end());
	address re=address();
	re.setlable("FUN"+tmp);
	return re;
}
void Var::print() {
    if(type==UNDEFINE) {
        return ;
    }
    if(type==ID) {
        std::cout<<name;
        std::cout<<spaceID<<"_"<<version;
    }
    else if(type==ARRAY) {
        if(index==nullptr) {
            printerror("Varprint ARRAY index is null");
        }
        std::cout<<name;
        std::cout<<'[';
        index->print();
        std::cout<<']';
        std::cout<<spaceID<<"_"<<version;
    }
    else if(type==NUM) std::cout<<val;
}
void address::print() {
    if(lable.size()>0) {
        std::cout<<lable<<":\n";
    }
    else if(op==OP_J) {
        PrintOP_TYPE(op);
        std::cout<<' '<<target;
    }
    else {
        PrintOP_TYPE(op);
        std::cout<<' ';
        result.print();
        std::cout<<' ';
        arg1.print();
        std::cout<<' ';
        arg2.print();
        std::cout<<'\n';
    }
}
void TAC::print() {
    for(address &x:code) {
        if(x.lable.size()>0) {
            std::cout<<x.lable<<":\n";
            continue;
        }
        switch (x.op) {
            case OP_CALL:
            case OP_J:{
                PrintOP_TYPE(x.op);
                std::cout<<' '<<code[x.target].lable<<'\n';
                break;
            }
            case OP_JF:
            case OP_JT:{
                PrintOP_TYPE(x.op);
                std::cout<<' ';
                x.arg1.print();
                std::cout<<' '<<code[x.target].lable<<'\n';
                break;
            }
            case OP_PUSHPARAM :
            case OP_SETPARAM: {
                PrintOP_TYPE(x.op);
                std::cout<<' '<<x.args.size()<<'\n';
                break;
            }
			case OP_BREAK:
			case OP_CONTINUE: {
				PrintOP_TYPE(x.op);
				break;
			}
            default: {
                PrintOP_TYPE(x.op);
                std::cout<<' ';
                x.result.print();
                std::cout<<' ';
                x.arg1.print();
                std::cout<<' ';
                x.arg2.print();
                std::cout<<'\n';
                break;
            }
        }
    }
}
void TAC::getBlocks() {
    blocks.clear();
    std::vector<address> tmp;
    for(address x:code) {
        if(x.lable.size()) {
            if(tmp.empty()) tmp.push_back(x);
            else {
                blocks.push_back(BLOCK(tmp));
                tmp.clear();
                tmp.push_back(x);
            }
        }
        else tmp.push_back(x);
        codebid.push_back(blocks.size());
    }
    if(!tmp.empty()) blocks.push_back(BLOCK(tmp));
}
void TAC::getBlockto() {
    for(BLOCK &x:blocks) {
        bool nex=true;
        for(address y:x.code) {
            switch(y.op) {
                case OP_J: {
                    nex=false;
                    x.to.push_back(codebid[y.target]);
                    break;
                }
                case OP_JF:
                case OP_JT:
                case OP_CALL: {

                }
            }
        }
    }
}
BLOCK::BLOCK(std::vector<address> x):code(x){}