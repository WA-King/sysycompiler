#ifndef SCAN_H__
#define SCAN_H__
#include <fstream>
#include <unordered_map>

#include "TOKEN.h"
#include "global.h"
#define BUFSIZE 2048
class state {
public:
    int nex[300];
    bool end;
    TOKEN_TYPE tokentype;
    state();
    void addnext(int p, char c);
    int go(char c);
};
class SCAN {
public:
    state states[100];
    std::unordered_map<std::string, TOKEN_TYPE> table;
    bool eof;
    char buf[BUFSIZE];
    int index, linenubmber, bufLen;
    std::ifstream input;
    SCAN() = default;
    SCAN(std::string);
    char getNextchar();
    bool getNewbuf();
	void linenote();
    char popNextchar();
    void init();
    void PrintTOKEN_TYPE(TOKEN_TYPE);
    TOKEN_TYPE checkID(std::string);
    TOKEN getToken();
};
#endif
