#include "gen.h"
info::info():instack(false),reg(-1),pstack(-1){};
void GEN::init() {
	biao.clear();
	endp.clear();
	st.clear();
	for(int i=0;i<reg.size();i++) {
		reg[i]=Var();
		usedreg[i]=false;
	} 
}
GEN::GEN(){
	init();
}
void GEN::pre() {
	reg.resize(rname.size());
	usedreg.resize(rname.size());
	if(smb.funlable.find("main")!=smb.funlable.end()) {
		text.push_back("jal "+code[smb.funlable["main"]].lable);
		text.push_back("li $v0 ,10");
		text.push_back("syscall");
	}
}
//TODO: 全局变量
void GEN::delreg(Var a,int index) {
	if(biao[a].reg==-1) return ;
	if(index<=endp[a]) {
		if(biao[a].instack==false) {
			std::string rn=rname[biao[a].reg],ps=std::to_string(-biao[a].pstack*4)+"($fp)";
			text.push_back("sw "+rn+','+ps);
		}
	} 
	reg[biao[a].reg]=Var();
	biao[a].reg=-1;
}
void GEN::delallreg(int index) {
	for(int i=0;i<reg.size();i++) {
		if(reg[i].type!=UNDEFINE) {
			//std::cout<<i<<' '<<endp[reg[i]]<<' '<<biao[reg[i]].reg<<' '<<biao[reg[i]].instack<<' '<<index<<'\n';
			delreg(reg[i],index);
		}
	}
}
int GEN::getreg(int index) {
	for(int i=0;i<reg.size();i++) {
		if(usedreg[i]) continue;
		if(reg[i].type==UNDEFINE) return i;
		if(endp[reg[i]]<index) {
			//std::cout<<endp[reg[i]]<<'\n';
			return i;
		} 
	}
	int Max=-1;
	for(int i=0;i<reg.size();i++) {
		if(usedreg[i]) continue;
		if(Max==-1||endp[reg[Max]]>endp[reg[i]]) Max=i;
	}
	if(Max==-1) {
		printerror("can't get a new reg");
	}
	delreg(reg[Max],index);
	return Max;
}
int GEN::allpstack(int index) {
	int pos=1;
	if(code[index].op==OP_SETPARAM) {
		for(Var now:code[index].args) {
			if(now.type==ID) {
				if(biao.find(now)==biao.end()) {
					biao[now]=info();
					biao[now].pstack=pos++;
				}
			}
		}
		index++;
	}
	// rt fp sp;
	pos+=3;
	while(index<code.size()&&code[index].op!=OP_OUTFUN) {
		switch (code[index].op) {
			case OP_DECLARE: {
				//INT;
				if(code[index].arg1.type==UNDEFINE) {
					biao[code[index].result]=info();
					biao[code[index].result].pstack=pos++;
				}
				else {
					//ARRAY
					biao[code[index].result]=info();
					biao[code[index].result].pstack=pos;
					pos+=code[index].arg1.val;
				}
				break;
			}
			default: {
				Var now=code[index].result;
				if(now.type==ID) {
					if(biao.find(now)==biao.end()) {
						biao[now]=info();
						biao[now].pstack=pos++;
					}
				}
				now=code[index].arg1;
				if(now.type==ID) {
					if(biao.find(now)==biao.end()) {
						biao[now]=info();
						biao[now].pstack=pos++;
					}
				}
				now=code[index].arg2;
				if(now.type==ID) {
					if(biao.find(now)==biao.end()) {
						biao[now]=info();
						biao[now].pstack=pos++;
					}
				}
				for(Var now:code[index].args) {
					if(now.type==ID) {
						if(biao.find(now)==biao.end()) {
							biao[now]=info();
							biao[now].pstack=pos++;
						}
					}
				}
				break;
			}
		}
		index++;
	}
	return pos;
}
int GEN::isinreg(Var now) {
	for(int i=0;i<reg.size();i++) {
		if(reg[i]==now) {
			if(biao[now.ArraytoVar()].reg==i) return i;
		} 
	}
	return -1;
}
int GEN::readVar(Var now,int index,bool f) {
	if(now.type==NUM) {
		int tmp=getreg(index);
		text.push_back("li "+rname[tmp]+","+std::to_string(now.val));
		return tmp;
	}
	//是否在reg中
	if(now.type==ID) {
		int tmp=isinreg(now);
		if(tmp!=-1) return tmp;
	}
	if(f) {
		if(now.spaceID==1) {
			if(now.type==ARRAY) {
				Var id=*now.index;
				if(id.type==NUM) {
					int r1=getreg(index);
					usedreg[r1]=true;
					text.push_back("la "+rname[r1]+", gl"+now.name);
					// lw r1 val*4(r1);
					text.push_back(oplsw("lw",rname[r1],rname[r1],-id.val));
					usedreg[r1]=false;
					return r1;
				}
				else {
					int r2=readVar(id,index,true);
					usedreg[r2]=true;
					int r1=getreg(index);
					usedreg[r1]=true;
					text.push_back("la "+rname[r1]+", gl"+now.name);
					//muli r2 r2 4
					text.push_back(opri(OP_MUL,rname[r2],rname[r2],4));
					//add r2 r1 r2;
					text.push_back(oprr(OP_ADD,rname[r2],rname[r2],rname[r1]));
					//lw r2 0(r2)
					text.push_back(oplsw("lw",rname[r2],rname[r2],0));
					usedreg[r1]=false;
					usedreg[r2]=false;
					return r2;
				}
			}
			else {
				int r1=getreg(index);
				usedreg[r1]=true;
				text.push_back("la "+rname[r1]+", gl"+now.name);
				text.push_back(oplsw("lw",rname[r1],rname[r1],0));
				usedreg[r1]=false;
				return r1;
			}
		}
		//临时
		else {
			if(now.type==ARRAY) {
				Var id=*now.index;
				if(id.type==NUM) {
					int base=readVar(now.ArraytoVar(),index,true);
					text.push_back(oplsw("lw",rname[base],rname[base],-id.val));
					return base;
				}
				else {
					int ix=readVar(id,index,true);
					usedreg[ix]=true;
					int base=readVar(now.ArraytoVar(),index,true);
					usedreg[base]=true;
					text.push_back(opri(OP_MUL,rname[ix],rname[ix],4));
					text.push_back(oprr(OP_MUL,rname[base],rname[base],rname[ix]));
					usedreg[ix]=false;
					usedreg[base]=false;
					return base;
				}
			}
			else {
				int tmp=getreg(index);
				text.push_back(oplsw("lw",rname[tmp],"$fp",-biao[now].pstack));
				biao[now].reg=tmp;
				reg[tmp]=now;
				return tmp;
			}
		}
	}
	else {
		return getreg(index);
	}
}
void GEN::writeVar(std::string re,int index,Var now) {
	if(now.spaceID==1) {
	}
	else {
		if(now.type==ARRAY) {
			int id=readVar(*now.index,index,true);
			usedreg[id]=true;
			int base=readVar(now.ArraytoVar(),index,true);
			usedreg[base]=true;
			text.push_back(oprr(OP_MINUS,rname[base],rname[base],rname[id]));
			text.push_back(oplsw("sw",re,rname[base],0));
			usedreg[id]=false;
			usedreg[base]=false;
			return ;
		}
		else if(now.type==ID) {
			text.push_back(oplsw("sw",re,"$fp",-biao[now].pstack));
			biao[now].instack=true;
			if(biao[now].reg!=-1) {
				reg[biao[now].reg]=Var();
			}
			biao[now].reg=-1;
		}
	}
}
void GEN::getendp(int index) {
	endp.clear();
	while(index<code.size()) {
		if(code[index].op==OP_OUTFUN) break;
		if(code[index].lable.size()) {
			index++;
			continue;
		}
		switch (code[index].op) {
			case OP_ADD:
			case OP_MINUS:	
			case OP_MUL:	
			case OP_DIV:	
			case OP_MOD:	
			case OP_EQ:	
			case OP_NE:	
			case OP_GE:	
			case OP_GT:	
			case OP_LE:	
			case OP_LT:	
			case OP_AND:
			case OP_OR: {
				if(code[index].arg1.type==ID) {
					endp[code[index].arg1]=index;
				}
				if(code[index].arg1.type==ARRAY) {
					endp[code[index].arg1.ArraytoVar()]=index;
				}
				if(code[index].arg2.type==ID) {
					endp[code[index].arg2]=index;
				}
				if(code[index].arg2.type==ARRAY) {
					endp[code[index].arg2.ArraytoVar()]=index;
				}
				break;
			}
			case OP_ASSIGN: {
				if(code[index].arg1.type==ID) {
					endp[code[index].arg1]=index;
				}
				if(code[index].arg1.type==ARRAY) {
					endp[code[index].arg1.ArraytoVar()]=index;
				}
				break;
			}
			default:
				break;
		}
		index++;
	}
}
int GEN::gendata(int index) {
	while(index<code.size()&&code[index].op==OP_DECLARE) {
		data.push_back("gl"+code[index].arg1.name+":");
		int size=4;
		if(code[index].arg2.type==NUM) {
			size=4*code[index].arg2.val;
		}
		index++;
		while(index<code.size()) {
			address now=code[index];
			if(now.op!=OP_ASSIGN) break;
			if(now.arg1.type!=NUM) {
				printerror("global var value is not NUM");
			}
			size-=4;
			data.push_back(".word "+std::to_string(now.arg1.val));
			index++;
		}
		if(size!=0) {
			data.push_back(".space "+std::to_string(size));
		}
	}
	return index;
}
int GEN::gentext(int index) {
	while(index<code.size()&&code[index].lable.size()&&code[index].lable.substr(0,3)=="FUN") {
		//std::cout<<"#1"<<'\n';
		init();
		getendp(index);
		//std::cout<<"#2"<<'\n';
		text.push_back(code[index].lable+": ");
		index++;
		int len=allpstack(index),numargs=code[index].args.size();
		//sw $ra numargs+1(sp)
		text.push_back(oplsw("sw","$ra","$sp",-numargs-1));
		text.push_back(oplsw("sw","$fp","$sp",-numargs-2));
		text.push_back(oplsw("sw","$sp","$sp",-numargs-3));
		text.push_back("move $fp, $sp");
		text.push_back(opri(OP_MINUS,"$sp","$sp",len));
		index++;
		//std::cout<<"#3"<<'\n';
		while(index<code.size()) {
			//std::cout<<index<<'\n';
			if(code[index].lable.size()) {
				text.push_back(code[index].lable+":");
				for(int i=0;i<reg.size();i++) {
					if(reg[i].type!=UNDEFINE) delreg(reg[i],index);
				}
				index++;
				continue;
			}
			switch(code[index].op) {
				case OP_ADD:
				case OP_MINUS:
				case OP_MUL:
				case OP_DIV:
				case OP_LE:
				case OP_LT:
				case OP_GE:
				case OP_GT:
				case OP_EQ:
				case OP_NE:
				case OP_AND:
				case OP_OR:
				case OP_MOD: {
					int r1=readVar(code[index].result,index,false);
					usedreg[r1]=true;
					int r2=readVar(code[index].arg1,index,true);
					usedreg[r2]=true;
					int r3=readVar(code[index].arg2,index,true);
					usedreg[r3]=true;
					text.push_back(oprr(code[index].op,rname[r1],rname[r2],rname[r3]));
					if(code[index].op==OP_MOD) {
						text.push_back("mfhi "+rname[r1]);
					}
					usedreg[r1]=false;
					usedreg[r2]=false;
					usedreg[r3]=false;
					reg[r1]=code[index].result;
					biao[code[index].result].reg=r1;
					biao[code[index].result].instack=false;
					break; 
				}
				case OP_ASSIGN: {
					int tmp=readVar(code[index].arg1,index,true);
					usedreg[tmp]=true;
					if(code[index].result.type==ID) {
						text.push_back(oplsw("sw",rname[tmp],"$fp",-biao[code[index].result].pstack));
						biao[code[index].result].instack=true;
						if(biao[code[index].result].reg!=-1) {
							reg[biao[code[index].result].reg]=Var();
						}
						biao[code[index].result].reg=-1;
					}
					else if(code[index].result.type==ARRAY) {
						int id=readVar(*code[index].result.index,index,true);
						usedreg[id]=true;
						int base=readVar(code[index].result.ArraytoVar(),index,true);
						usedreg[base]=true;
						text.push_back(oprr(OP_MINUS,rname[base],rname[base],rname[id]));
						text.push_back(oplsw("sw",rname[tmp],rname[base],0));
						usedreg[id]=false;
						usedreg[base]=false;
					}
					usedreg[tmp]=false;
					break;
				}
				case OP_GETINT: {
					text.push_back("li $v0, 5");
					text.push_back("syscall");
					writeVar("$v0",index,code[index].result);
					break;
				}
				case OP_PINRTINT: {
					int r1=readVar(code[index].result,index,true);
					text.push_back("move $a0, "+rname[r1]);
					text.push_back("li $v0, 1");
					text.push_back("syscall");
					break;
				}
				case OP_J: {
					text.push_back("j "+code[code[index].target].lable);
					break;
				}
				case OP_JF: {
					int r1=readVar(code[index].arg1,index,true);
					text.push_back("beq "+rname[r1]+", $zero,"+code[code[index].target].lable);
					break;
				}
				case OP_JT: {
					int r1=readVar(code[index].arg1,index,true);
					text.push_back("bne "+rname[r1]+", $zero,"+code[code[index].target].lable);
					break;
				}
				case OP_OUTFUN: {
					text.push_back(oplsw("lw","$ra","$fp",-numargs-1));
					text.push_back(oplsw("lw","$sp","$fp",-numargs-3));
					text.push_back(oplsw("lw","$fp","$fp",-numargs-2));
					text.push_back("jr $ra");
					break;
				}
				case OP_PUSHPARAM: {
					for(int i=0;i<code[index].args.size();i++) {
						int tmp=readVar(code[index].args[i],index,true);
						text.push_back(oplsw("sw",rname[tmp],"$sp",-i-1));
					}
					break;
				}
				case OP_CALL: {
					delallreg(index);
					text.push_back("jal "+code[code[index].target].lable);
					break;
				}
				case OP_SETRETURN: {
					int tmp=readVar(code[index].result,index,true);
					text.push_back("move $v0, "+rname[tmp]);
					break;
				}
				case OP_GETRETURN: {
					int tmp=readVar(code[index].result,index,false);
					text.push_back("move "+rname[tmp]+",$v0");
					biao[code[index].result].instack=false;
					biao[code[index].result].reg=tmp;
					reg[tmp]=code[index].result;
					//std::cout<<tmp<<' '<<"#"<<endp[code[index].result]<<'\n';
					break;
				}
				default:
					break;
			}
			if(code[index].op==OP_OUTFUN) {
				index++;
				break;
			}
			index++;
		}
	}
	return index;
}
void GEN::gen(std::string file) {
	outfile.open(file);
	pre();
	if(outfile.is_open()==false) {
		printerror("outfile not open");
	}
	int index=0;
	while(index<code.size()) {
		if(code[index].lable.size()) {
			std::cout<<"in"<<'\n';
			index=gentext(index);
		}
		else index=gendata(index);
	}
	outfile<<".text"<<'\n';
	for(auto x: text) outfile<<x<<'\n';
	outfile.close();
}
std::string oprr(OP_TYPE op,std::string r1,std::string r2,std::string r3) {
	std::string ans="";
	switch (op) {
		case OP_ADD:
			ans+="add";
			break;
		case OP_MINUS:
			ans+="sub";
			break;
		case OP_MUL:
			ans+="mul";
			break;
		case OP_MOD:
		case OP_DIV:
			ans+="div";
			break;
		case OP_LE:
			ans+="sle";
			break;
		case OP_LT:
			ans+="slt";
			break;
		case OP_GE:
			ans+="sge";
			break;
		case OP_GT:
			ans+="sgt";
			break;
		case OP_EQ:
			ans+="seq";
			break;
		case OP_NE:
			ans+="sne";
			break;
		case OP_AND:
			ans+="and";
			break;
		case OP_OR:
			ans+="or";
			break;
		default:
			printerror("oprr erro");
			break;
	}
	if(op==OP_MOD) {
		ans+=" "+r2;
		ans+=","+r3;
	}
	else {
		ans+=" "+r1;
		ans+=","+r2;
		ans+=","+r3;
	}
	return ans;
}
std::string opri(OP_TYPE op,std::string r1,std::string r2,int im) {
	std::string ans="";
	switch (op) {
		case OP_ADD:
			ans+="addi";
			break;
		case OP_MINUS:
			ans+="subi";
			break;
		case OP_MUL:
			ans+="muli";
			break;
		case OP_DIV:
			ans+="divi";
			break;
		default:
			printerror("oprr erro");
			break;
	}
	ans+=" "+r1;
	ans+=","+r2;
	ans+=","+std::to_string(im*4);
	return ans;
}
std::string oplsw(std::string op,std::string r1,std::string r2,int im) {
	std::string ans=op;
	ans+=" "+r1;
	ans+=","+std::to_string(im*4)+"("+r2+")";
	return ans;
}
