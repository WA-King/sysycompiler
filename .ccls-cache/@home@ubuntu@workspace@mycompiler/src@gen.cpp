#include "gen.h"
void GEN::init() {
	biao.clear();
	st.clear();
}
GEN::GEN(){
	init();
}
void GEN::pre() {
	usedreg.resize(rname.size());
	if(smb.funlable.find("main")!=smb.funlable.end()) {
		text.push_back("jal "+code[smb.funlable["main"]].lable);
		text.push_back("li $v0 ,10");
		text.push_back("syscall");
	}
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
				if(code[index].arg1.type==UNDEFINE) {
					//INT;
					biao[code[index].result]=info();
					biao[code[index].result].pstack=pos++;
				}
				else {
					//ARRAY
					biao[code[index].result.ArrayBase()]=info();
					biao[code[index].result.ArrayBase()].pstack=pos;
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
void GEN::getendp(int index) {
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
					reg.endp[code[index].arg1]=index;
				}
				if(code[index].arg1.type==ARRAY) {
					reg.endp[code[index].arg1.ArrayBase()]=index;
				}
				if(code[index].arg2.type==ID) {
					reg.endp[code[index].arg2]=index;
				}
				if(code[index].arg2.type==ARRAY) {
					reg.endp[code[index].arg2.ArrayBase()]=index;
				}
				if(code[index].result.type==ARRAY) {
					reg.endp[code[index].result.ArrayBase()]=index;
				}
				break;
			}
			case OP_ASSIGN: {
				if(code[index].arg1.type==ID) {
					reg.endp[code[index].arg1]=index;
				}
				if(code[index].arg1.type==ARRAY) {
					reg.endp[code[index].arg1.ArrayBase()]=index;
				}
				if(code[index].result.type==ARRAY) {
					reg.endp[code[index].result.ArrayBase()]=index;
				}
				break;
			}
			case OP_PINRTINT: {
				if(code[index].result.type==ARRAY) {
					reg.endp[code[index].result.ArrayBase()]=index;
				}
				else {
					reg.endp[code[index].result]=index;
				}
			}
			default:
				break;
		}
		index++;
	}
}
int GEN::gendata(int index) {
	while(index<code.size()&&code[index].op==OP_DECLARE) {
		data.push_back(code[index].result.name+":");
		int size=4;
		if(code[index].arg1.type==NUM) {
			size=4*code[index].arg1.val;
			Var tmp=code[index].result;
			tmp=tmp.ArrayBase();
			gl.push_back(tmp);
		}
		else {
			gl.push_back(code[index].result);
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
		reg.clear();
		init();
		getendp(index);
		text.push_back(code[index].lable+": ");
		index++;
		int len=allpstack(index),numargs=code[index].args.size();
		reg.biao=biao;
		//sw $ra numargs+1(sp)
		text.push_back(oplsw("sw","$ra","$sp",-numargs-1));
		text.push_back(oplsw("sw","$fp","$sp",-numargs-2));
		text.push_back(oplsw("sw","$sp","$sp",-numargs-3));
		text.push_back("move $fp, $sp");
		text.push_back(opri(OP_MINUS,"$sp","$sp",len));
		for(Var x:code[index].args) {
			if(x.type==ARRAY) {
				x=x.ArrayBase();
			}
			reg.declearVar(x,text);
		}
		index++;
		for(Var x:gl) {
			if(x.type==ARRAY) {
				x=x.ArrayBase();
			}
			reg.declearVar(x,text);
			//std::cout<<x.name<<' '<<reg.biao[x].reg<<' '<<reg.endp[x]<<'\n';
		}
		while(index<code.size()) {
			if(code[index].lable.size()) {
				text.push_back(code[index].lable+":");
				index++;
				continue;
			}
			switch(code[index].op) {
				case OP_DECLARE: {
					if(code[index].arg1.type==NUM) {
						reg.declearVar(code[index].result.ArrayBase(),text);
					}
					else {
						reg.declearVar(code[index].result,text);
					}
					break;
				}
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
					int rarg1=reg.readVar(code[index].arg1,text);
					reg.usedreg[rarg1]=true;
					int rarg2=reg.readVar(code[index].arg2,text);
					reg.usedreg[rarg2]=true;
					int rresult=reg.readVar(code[index].result,text);
					reg.usedreg[rresult]=true;
					text.push_back(oprr(code[index].op,rname[rresult],rname[rarg1],rname[rarg2]));
					if(code[index].op==OP_MOD) {
						text.push_back("mfhi "+rname[rresult]);
					}
					reg.usedreg[rarg1]=false;
					reg.usedreg[rarg2]=false;
					reg.writeVar(code[index].result,rresult,text,false);
					reg.usedreg[rresult]=false;
					break; 
				}
				case OP_ASSIGN: {
					int rarg1=reg.readVar(code[index].arg1,text);
					reg.usedreg[rarg1]=true;
					reg.writeVar(code[index].result,rarg1,text,false);
					reg.usedreg[rarg1]=false;
					break;
				}
				case OP_GETINT: {
					text.push_back("li $v0, 5");
					text.push_back("syscall");
					text.push_back("move $t0,$v0");
					usedreg[0]=true;
					reg.writeVar(code[index].result,0,text,false);
					usedreg[0]=false;
					break;
				}
				case OP_PINRTINT: {
					int r1=reg.readVar(code[index].result,text);
					text.push_back("move $a0, "+rname[r1]);
					text.push_back("li $v0, 1");
					text.push_back("syscall");
					text.push_back("li $a0, 10");
					text.push_back("li $v0, 11");
					text.push_back("syscall");
					break;
				}
				case OP_J: {
					text.push_back("j "+code[code[index].target].lable);
					break;
				}
				case OP_JF: {
					int r1=reg.readVar(code[index].arg1,text);
					text.push_back("beq "+rname[r1]+", $zero,"+code[code[index].target].lable);
					break;
				}
				case OP_JT: {
					int r1=reg.readVar(code[index].arg1,text);
					text.push_back("bne "+rname[r1]+", $zero,"+code[code[index].target].lable);
					break;
				}
				case OP_OUTFUN: {
					for(int i=0;i<reg.reg.size();i++) {
						if(reg.reg[i].spaceID==1) {
							reg.writeVar(reg.reg[i],i,text,true);
						}
					}
					text.push_back(oplsw("lw","$ra","$fp",-numargs-1));
					text.push_back(oplsw("lw","$sp","$fp",-numargs-3));
					text.push_back(oplsw("lw","$fp","$fp",-numargs-2));
					text.push_back("jr $ra");
					break;
				}
				case OP_PUSHPARAM: {
					for(int i=0;i<code[index].args.size();i++) {
						int tmp=reg.readVar(code[index].args[i],text);
						text.push_back(oplsw("sw",rname[tmp],"$sp",-i-1));
					}
					break;
				}
				case OP_CALL: {
					for(int i=reg.need_cnt;i<reg.reg.size();i++) {
						if(reg.reg[i].type!=UNDEFINE) {
							reg.writeVar(reg.reg[i],i,text,true);
						}
					}
					text.push_back("jal "+code[code[index].target].lable);
					for(int i=reg.need_cnt;i<reg.reg.size();i++) {
						if(reg.reg[i].type!=UNDEFINE) {
							reg.forceread(reg.reg[i],i,text);
						}
					}
					break;
				}
				case OP_SETRETURN: {
					int tmp=reg.readVar(code[index].result,text);
					text.push_back("move $v0, "+rname[tmp]);
					break;
				}
				case OP_GETRETURN: {
					int tmp=reg.readVar(code[index].result,text);
					text.push_back("move "+rname[tmp]+",$v0");
					reg.writeVar(code[index].result,tmp,text,false);
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
			index=gentext(index);
		}
		else index=gendata(index);
	}
	outfile<<".text"<<'\n';
	for(auto x: text) outfile<<x<<'\n';
	outfile<<".data"<<'\n';
	for(auto x: data) outfile<<x<<'\n';
	outfile.close();
}
