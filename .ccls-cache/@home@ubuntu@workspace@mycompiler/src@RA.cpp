#include "RA.h"
info::info():instack(false),reg(-1),pstack(-1){};

RA::RA(){
    reg.resize(rname.size());
    usedreg.resize(rname.size());
}
void RA::clear() {
	endp.clear();
	biao.clear();
	for(int i=0;i<reg.size();i++) {
		reg[i]=Var();
		usedreg[i]=false;
	}
}
int RA::getunusedreg() {
	for(int i=0;i<need_cnt;i++) {
		if(usedreg[i]==false) {
			return i;
		}
	}
	printerror("can't find unusedreg");
}
void RA::forceread(Var now,int target,std::vector<std::string>& text) {
	if(now.spaceID==1) {
		if(now.type==ARRAYBASE) {
			text.push_back("la "+rname[target]+","+now.name);
		}
		else {
			text.push_back("la "+rname[target]+","+now.name);
			text.push_back(oplsw("lw",rname[target],rname[target],0));
		}
	}
	else {
		if(now.type==ARRAYBASE) {
			text.push_back("subi "+rname[target]+",$fp,"+std::to_string(4*biao[now].pstack));
		}
		else {
			//std::cout<<target<<' '<<rname[target]<<'\n';
			text.push_back(oplsw("lw",rname[target],"$fp",-biao[now].pstack));
		} 
	}
}
void RA::declearVar(Var now,std::vector<std::string>& text) {
    //Var not be used
    if(endp.find(now)==endp.end()) return ;
    for(int i=need_cnt;i<reg.size();i++) {
        if(reg[i].type==UNDEFINE) {
            reg[i]=now;
            biao[now].reg=i;
			if(now.type==ARRAYBASE||now.spaceID==1) {
				forceread(now,i,text);
			}
            return ;
        }
    }
    int Max=need_cnt;
    for(int i=need_cnt;i<reg.size();i++) {
        if(endp[reg[Max]]<endp[reg[i]]) {
            Max=i;
        }
    }
    if(endp[reg[Max]]>endp[now]) {
        writeVar(reg[Max],Max,text,true);
        reg[Max]=now;
        biao[now].reg=Max;
		if(now.type==ARRAYBASE||now.spaceID==1) {
			forceread(now,Max,text);
		}
    }
    return ;
}
int RA::readVar(Var now,std::vector<std::string>& text) {
	if(now.type==NUM) {
		int target=-1;
		for(int i=0;i<need_cnt;i++) {
			if(usedreg[i]==false) {
				target=i;
				break;
			}
		}
		if(target==-1) {
			printerror("can't find regstser for NUM");
		}
		text.push_back("addi "+rname[target]+", $zero,"+std::to_string(now.val));
		return target;
	}
    if(now.spaceID==1) {
        if(now.type==ARRAY) return readGARRAY(now,text);
        else if(now.type==ID||now.type==ARRAYBASE) return readGID(now,text);
    }
    else {
        if(now.type==ARRAY) return readARRAY(now,text);
        else if(now.type==ID||now.type==ARRAYBASE) return readID(now,text);
    }
}
int RA::readID(Var now,std::vector<std::string>& text) {
    if(biao[now].reg!=-1&&reg[biao[now].reg]==now) {
		return biao[now].reg;
	} 
    int target=-1;
    for(int i=0;i<need_cnt;i++) {
        if(usedreg[i]==false) {
            reg[i]=now;
            text.push_back(oplsw("lw",rname[i],"$fp",-biao[now].pstack));
            target=i;
			break;
        }
    }
    if(target==-1) {
        printerror("can't find a regsister for ID");
    }
    return target; 
}
int RA::readARRAY(Var now,std::vector<std::string>& text) {
    Var id=*now.index;
    int regid;
    if(id.type!=NUM) {
        regid=readVar(id,text);
        usedreg[regid]=true;
    }
    int base=readID(now.ArrayBase(),text);
    usedreg[base]=true;
    int target=getunusedreg();
    if(target==-1) {
        printerror("can't find a regsister for ARRAY");
    }
    if(id.type==NUM) {
        text.push_back(oplsw("lw",rname[target],rname[base],-id.val));
    }
    else {
       	text.push_back("mul "+rname[target]+","+rname[regid]+",4");
        text.push_back(oprr(OP_MINUS,rname[target],rname[base],rname[target]));
        text.push_back(oplsw("lw",rname[target],rname[target],0));
        usedreg[regid]=false;
    }
    usedreg[base]=false;
    return target;
}
int RA::readGID(Var now,std::vector<std::string>& text) {
	std::cout<<"##1"<<'\n';
	std::cout<<biao[now].reg<<'\n';
    if(biao[now].reg!=-1&&reg[biao[now].reg]==now) return biao[now].reg;
    int target=getunusedreg();
    if(target==-1) {
        printerror("can't find a regsister for GID");
    }
    text.push_back("la "+rname[target]+","+now.name);
    text.push_back(oplsw("lw",rname[target],rname[target],0));
    return target;
}
int RA::readGARRAY(Var now,std::vector<std::string>& text) {
    Var id=*now.index;
    int regid;
    if(id.type!=NUM) {
        regid=readVar(id,text);
        usedreg[regid]=true;
    }
    int base=readVar(now.ArrayBase(),text);
    usedreg[base]=true;
    int target=getunusedreg();
    if(target==-1) {
        printerror("can't find a regsister for GARRAY");
    }
    if(id.type==NUM) {
        text.push_back(oplsw("lw",rname[target],rname[base],id.val));
    }
    else {
       	text.push_back("mul "+rname[target]+","+rname[regid]+",4");
        text.push_back(oprr(OP_ADD,rname[target],rname[base],rname[target]));
        text.push_back(oplsw("lw",rname[target],rname[target],0));
        usedreg[regid]=false;
    }
    usedreg[base]=false;
    return target;
}
void RA::writeVar(Var now,int target,std::vector<std::string> &text,bool force) {
    if(now.type==NUM||now.type==ARRAYBASE) return ;
    if(now.spaceID==1) {
        if(now.type==ARRAY) writeGARRAY(now,target,text,force);
        else if(now.type==ID) writeGID(now,target,text,force);
    }
    else {
        if(now.type==ARRAY) writeARRAY(now,target,text,force);
        else if(now.type==ID) writeID(now,target,text,force);
    }
}
void RA::writeID(Var now,int target,std::vector<std::string> &text,bool force) {
    if(force==false&&biao[now].reg!=-1&&reg[biao[now].reg]==now) {
        if(biao[now].reg!=target) {
            text.push_back("move "+rname[biao[now].reg]+","+rname[target]);
        }
        return ;
    }
    text.push_back(oplsw("sw",rname[target],"$fp",-biao[now].pstack));
}
void RA::writeARRAY(Var now,int target,std::vector<std::string> &text,bool force) {
    Var id=*now.index;
    int regid;
    if(id.type!=NUM) {
        regid=readVar(now,text);
        usedreg[regid]=true;
    }
    int base=readVar(now.ArrayBase(),text);
    if(id.type==NUM) {
        text.push_back(oplsw("sw",rname[target],rname[base],-id.val));
    }
    else {
        int tmp=getunusedreg();
        if(tmp==-1) {
            printerror("can't find a tmp reg");
        }
        text.push_back(oprr(OP_MINUS,rname[tmp],rname[base],rname[regid]));
        text.push_back(oplsw("sw",rname[target],rname[tmp],0));
    }
    usedreg[regid]=false;
    return ;
}
void RA::writeGID(Var now,int target,std::vector<std::string> &text,bool force) {
    if(force==false&&biao[now].reg!=-1&&reg[biao[now].reg]==now) {
        if(biao[now].reg!=target) {
            text.push_back("move "+rname[biao[now].reg]+","+rname[target]);
        }
        return ;
    }
    int tmp=getunusedreg();
    text.push_back("la "+rname[tmp]+","+now.name);
    text.push_back("sw "+rname[target]+",0("+rname[tmp]+")");
}
void RA::writeGARRAY(Var now,int target,std::vector<std::string> &text,bool force) {
    Var id=*now.index;
    int regid;
    if(id.type!=NUM) {
        regid=readVar(id,text);
    }
    int base=readVar(now.ArrayBase(),text);
    if(id.type==NUM) {
        text.push_back(oplsw("sw",rname[target],rname[base],id.val));
    }
    else {
        int tmp=getunusedreg();
        if(tmp==-1) {
            printerror("can't find a tmp reg");
        }
       	text.push_back("mul "+rname[tmp]+","+rname[regid]+",4");
        text.push_back(oprr(OP_ADD,rname[tmp],rname[base],rname[tmp]));
        text.push_back(oplsw("sw",rname[target],rname[tmp],0));
    }
    usedreg[regid]=false;
    return ;
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
			ans+="mul";
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
