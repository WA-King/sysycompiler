#ifndef _RA_H__
#define _RA_H__
#include "TAC.h"
#include "map"
class info {
public:
	int reg,pstack;
	bool instack;
	info();
};
class RA {
public:
	std::vector<std::string> rname={"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};
	int need_cnt=6;
	std::map<Var,info> biao;
	std::map<Var,int> endp;
	std::vector<bool> usedreg;
	std::vector<Var> reg;
	RA();
	void clear();
	int getunusedreg();
	void forceread(Var,int,std::vector<std::string>&);
	void declearVar(Var,std::vector<std::string>&);
	int readVar(Var,std::vector<std::string>&);
	int readID(Var,std::vector<std::string>&);
	int readGID(Var,std::vector<std::string>&);
	int readGARRAY(Var,std::vector<std::string>&);
	int readARRAY(Var,std::vector<std::string>&);
	void writeVar(Var,int,std::vector<std::string>&,bool);
	void writeID(Var,int,std::vector<std::string>&,bool);
	void writeGID(Var,int,std::vector<std::string>&,bool);
	void writeGARRAY(Var,int,std::vector<std::string>&,bool);
	void writeARRAY(Var,int,std::vector<std::string>&,bool);
};
std::string oprr(OP_TYPE,std::string,std::string,std::string);
std::string opri(OP_TYPE,std::string,std::string,int);
std::string oplsw(std::string,std::string,std::string,int);
#endif
