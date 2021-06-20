#ifndef _PARSER_H__
#define _PARSER_H__
#include "AST.h"
#include "scan.h"
#include "symbol.h"
#include "TAC.h"
class ParseError : public std::exception {
public:
    ParseError() = default;
    ParseError(std::string);
    std::string errorMessage;
};
class Parse : public SCAN {
public:
    TOKEN Last;
	int inloops=0;
    TOKEN_TYPE returntype;
    Parse() = default;
    Parse(std::string);
    void NextTOKEN();
    TOKEN Match(TOKEN_TYPE);
    std::shared_ptr<BaseAST> getCompUnit();
    std::shared_ptr<BaseAST> getFunDecl(TOKEN_TYPE,std::string name="");
    std::shared_ptr<BaseAST> getAddExp();      // done
    std::shared_ptr<BaseAST> getMulExp();      // done
    std::shared_ptr<BaseAST> getUnaryExp();    // done
    std::shared_ptr<BaseAST> getPrimaryExp();  // done
    std::shared_ptr<BaseAST> getLOrExp();      // done
    std::shared_ptr<BaseAST> getLAndExp();     // done
    std::shared_ptr<BaseAST> getEqExp();       // done
    std::shared_ptr<BaseAST> getRelExp();      // done
    std::shared_ptr<BaseAST> getStmt();
    std::shared_ptr<BaseAST> getIfStmt();
    std::shared_ptr<BaseAST> getWhileStmt();
    std::shared_ptr<BaseAST> getBlock(bool =true);
    std::vector<std::shared_ptr<BaseAST>> getIntList();  // done
    std::shared_ptr<BaseAST> getVarDecl(bool,std::string name="");               // done
    std::shared_ptr<BaseAST> getConstDecl();    //done
    std::shared_ptr<BaseAST> getVarDef(bool,std::string name="");                // done
    std::shared_ptr<BaseAST> getAssign();
	std::shared_ptr<BaseAST> getGetint();
	std::shared_ptr<BaseAST> getPrintint();
    std::vector<std::shared_ptr<BaseAST>> getFunArgs(); //done
};
#endif
