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
        default:
            std::cout << "print erro" << '\n';
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
address::address():lable(""),op(NUL),target(-1) {}
void address::setlable(std::string x) {
    lable=x;
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
    re.setID("%tmp"+tmp,-1);
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
    re.setlable("lable"+tmp);
    return re;
}
void Var::print() {
    if(type==ID) {
        std::cout<<name;
        std::cout<<"|"<<spaceID<<"|"<<version;
    }
    else if(type==ARRAY) {
        if(index==nullptr) {
            printerror("Varprint ARRAY index is null");
        }
        std::cout<<'[';
        index->print();
        std::cout<<']';
        std::cout<<name;
        std::cout<<"|"<<spaceID<<"|"<<version;
    }
    else if(type==NUM) std::cout<<val;
}
void address::print() {
    if(lable.size()>0) {
        std::cout<<lable<<":\n";
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
