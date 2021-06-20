#ifndef _GEN_H__
#define _GEN_H__
#include"TAC.h"
#include<map>
#include "RA.h"
class GEN{
public:
	std::vector<std::string> rname={"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};
	RA reg;
	std::vector<address> code;
	std::map<Var,info> biao;
	std::ofstream outfile;
	std::vector<Var> st,gl;
	std::vector<bool> usedreg;
	std::vector<std::string> data,text;
	GEN();
	void init();
	void pre();
	void getendp(int);
	int readVar(Var,int);
	void writeVar(std::string,int,Var);
	int allpstack(int);
	int gendata(int);
	int gentext(int);
	void gen(std::string file);
};
#endif