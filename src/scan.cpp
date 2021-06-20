#include "scan.h"

#include <cstring>
#include <iostream>
#define LZNB(x)                 \
    case (x):                   \
        std::cerr << #x << ' '; \
        break;
void SCAN::PrintTOKEN_TYPE(TOKEN_TYPE x) {
    switch (x) {
        LZNB(ID);
        LZNB(NUM);
        LZNB(ADD);
        LZNB(MINUS);
        LZNB(MUL);
        LZNB(DIV);
        LZNB(MOD);
        LZNB(AND);
        LZNB(OR);
        LZNB(EQ);
        LZNB(NE);
        LZNB(GT);
        LZNB(GE);
        LZNB(LT);
        LZNB(LE);
        LZNB(LSBRACKETS);
        LZNB(LMBRACKETS);
        LZNB(LBBRACKETS);
        LZNB(RSBRACKETS);
        LZNB(RMBRACKETS);
        LZNB(RBBRACKETS);
        LZNB(COMMA);
        LZNB(SEMICOLON);
        LZNB(FILEEND);
        default:
            std::cout << "print erro" << '\n';
            break;
    }
}
state::state() {
    memset(nex, 0, sizeof(nex));
    end = false;
}
void state::addnext(int p, char c) { nex[c] = p; }
int state::go(char c) { return nex[c]; }
SCAN::SCAN(std::string s) {
    input.open(s);
    bufLen = 0;
    index = 0;
    eof = false;
}
void SCAN::init() {
	states[17].end=true;
	states[17].tokentype=NOT;
	states[18].end=true;
	states[18].tokentype=MOD;
	states[11].end=true;
	states[11].tokentype=LSBRACKETS;
	states[12].end=true;
	states[12].tokentype=RSBRACKETS;
	states[5].end=true;
	states[5].tokentype=MUL;
	states[15].end=true;
	states[15].tokentype=ADD;
	states[8].end=true;
	states[8].tokentype=COMMA;
	states[16].end=true;
	states[16].tokentype=MINUS;
	states[2].end=true;
	states[2].tokentype=DIV;
	states[31].end=true;
	states[31].tokentype=NUM;
	states[7].end=true;
	states[7].tokentype=SEMICOLON;
	states[26].end=true;
	states[26].tokentype=LT;
	states[19].end=true;
	states[19].tokentype=ASSIGN;
	states[28].end=true;
	states[28].tokentype=GT;
	states[30].end=true;
	states[30].tokentype=ID;
	states[9].end=true;
	states[9].tokentype=LMBRACKETS;
	states[10].end=true;
	states[10].tokentype=RMBRACKETS;
	states[13].end=true;
	states[13].tokentype=LBBRACKETS;
	states[14].end=true;
	states[14].tokentype=RBBRACKETS;
	states[21].end=true;
	states[21].tokentype=NE;
	states[23].end=true;
	states[23].tokentype=AND;
	states[6].end=true;
	states[6].tokentype=RBLOCK_NOTE;
	states[4].end=true;
	states[4].tokentype=LBLOCK_NOTE;
	states[3].end=true;
	states[3].tokentype=LINE_NOTE;
	states[27].end=true;
	states[27].tokentype=LE;
	states[20].end=true;
	states[20].tokentype=EQ;
	states[29].end=true;
	states[29].tokentype=GE;
	states[25].end=true;
	states[25].tokentype=OR;
	states[1].addnext(17,'!');
	states[1].addnext(18,'%');
	states[1].addnext(22,'&');
	states[1].addnext(11,'(');
	states[1].addnext(12,')');
	states[1].addnext(5,'*');
	states[1].addnext(15,'+');
	states[1].addnext(8,',');
	states[1].addnext(16,'-');
	states[1].addnext(2,'/');
	states[1].addnext(31,'0');
	states[1].addnext(31,'1');
	states[1].addnext(31,'2');
	states[1].addnext(31,'3');
	states[1].addnext(31,'4');
	states[1].addnext(31,'5');
	states[1].addnext(31,'6');
	states[1].addnext(31,'7');
	states[1].addnext(31,'8');
	states[1].addnext(31,'9');
	states[1].addnext(7,';');
	states[1].addnext(26,'<');
	states[1].addnext(19,'=');
	states[1].addnext(28,'>');
	states[1].addnext(30,'A');
	states[1].addnext(30,'B');
	states[1].addnext(30,'C');
	states[1].addnext(30,'D');
	states[1].addnext(30,'E');
	states[1].addnext(30,'F');
	states[1].addnext(30,'G');
	states[1].addnext(30,'H');
	states[1].addnext(30,'I');
	states[1].addnext(30,'J');
	states[1].addnext(30,'K');
	states[1].addnext(30,'L');
	states[1].addnext(30,'M');
	states[1].addnext(30,'N');
	states[1].addnext(30,'O');
	states[1].addnext(30,'P');
	states[1].addnext(30,'Q');
	states[1].addnext(30,'R');
	states[1].addnext(30,'S');
	states[1].addnext(30,'T');
	states[1].addnext(30,'U');
	states[1].addnext(30,'V');
	states[1].addnext(30,'W');
	states[1].addnext(30,'X');
	states[1].addnext(30,'Y');
	states[1].addnext(30,'Z');
	states[1].addnext(9,'[');
	states[1].addnext(10,']');
	states[1].addnext(30,'_');
	states[1].addnext(30,'a');
	states[1].addnext(30,'b');
	states[1].addnext(30,'c');
	states[1].addnext(30,'d');
	states[1].addnext(30,'e');
	states[1].addnext(30,'f');
	states[1].addnext(30,'g');
	states[1].addnext(30,'h');
	states[1].addnext(30,'i');
	states[1].addnext(30,'j');
	states[1].addnext(30,'k');
	states[1].addnext(30,'l');
	states[1].addnext(30,'m');
	states[1].addnext(30,'n');
	states[1].addnext(30,'o');
	states[1].addnext(30,'p');
	states[1].addnext(30,'q');
	states[1].addnext(30,'r');
	states[1].addnext(30,'s');
	states[1].addnext(30,'t');
	states[1].addnext(30,'u');
	states[1].addnext(30,'v');
	states[1].addnext(30,'w');
	states[1].addnext(30,'x');
	states[1].addnext(30,'y');
	states[1].addnext(30,'z');
	states[1].addnext(13,'{');
	states[1].addnext(24,'|');
	states[1].addnext(14,'}');
	states[17].addnext(21,'=');
	states[22].addnext(23,'&');
	states[5].addnext(6,'/');
	states[2].addnext(4,'*');
	states[2].addnext(3,'/');
	states[31].addnext(31,'0');
	states[31].addnext(31,'1');
	states[31].addnext(31,'2');
	states[31].addnext(31,'3');
	states[31].addnext(31,'4');
	states[31].addnext(31,'5');
	states[31].addnext(31,'6');
	states[31].addnext(31,'7');
	states[31].addnext(31,'8');
	states[31].addnext(31,'9');
	states[26].addnext(27,'=');
	states[19].addnext(20,'=');
	states[28].addnext(29,'=');
	states[30].addnext(30,'0');
	states[30].addnext(30,'1');
	states[30].addnext(30,'2');
	states[30].addnext(30,'3');
	states[30].addnext(30,'4');
	states[30].addnext(30,'5');
	states[30].addnext(30,'6');
	states[30].addnext(30,'7');
	states[30].addnext(30,'8');
	states[30].addnext(30,'9');
	states[30].addnext(30,'A');
	states[30].addnext(30,'B');
	states[30].addnext(30,'C');
	states[30].addnext(30,'D');
	states[30].addnext(30,'E');
	states[30].addnext(30,'F');
	states[30].addnext(30,'G');
	states[30].addnext(30,'H');
	states[30].addnext(30,'I');
	states[30].addnext(30,'J');
	states[30].addnext(30,'K');
	states[30].addnext(30,'L');
	states[30].addnext(30,'M');
	states[30].addnext(30,'N');
	states[30].addnext(30,'O');
	states[30].addnext(30,'P');
	states[30].addnext(30,'Q');
	states[30].addnext(30,'R');
	states[30].addnext(30,'S');
	states[30].addnext(30,'T');
	states[30].addnext(30,'U');
	states[30].addnext(30,'V');
	states[30].addnext(30,'W');
	states[30].addnext(30,'X');
	states[30].addnext(30,'Y');
	states[30].addnext(30,'Z');
	states[30].addnext(30,'_');
	states[30].addnext(30,'a');
	states[30].addnext(30,'b');
	states[30].addnext(30,'c');
	states[30].addnext(30,'d');
	states[30].addnext(30,'e');
	states[30].addnext(30,'f');
	states[30].addnext(30,'g');
	states[30].addnext(30,'h');
	states[30].addnext(30,'i');
	states[30].addnext(30,'j');
	states[30].addnext(30,'k');
	states[30].addnext(30,'l');
	states[30].addnext(30,'m');
	states[30].addnext(30,'n');
	states[30].addnext(30,'o');
	states[30].addnext(30,'p');
	states[30].addnext(30,'q');
	states[30].addnext(30,'r');
	states[30].addnext(30,'s');
	states[30].addnext(30,'t');
	states[30].addnext(30,'u');
	states[30].addnext(30,'v');
	states[30].addnext(30,'w');
	states[30].addnext(30,'x');
	states[30].addnext(30,'y');
	states[30].addnext(30,'z');
	states[24].addnext(25,'|');
    table["int"] = INT;
    table["void"] = VOID;
    table["if"] = IF;
    table["else"] = ELSE;
    table["const"] = CONST;
    table["while"] = WHILE;
    table["continue"] = CONTINUE;
    table["break"] = BREAK;
    table["return"] = RETURN;
}
bool SCAN::getNewbuf() {
    if (input.eof()) {
        eof = true;
        return false;
    }
    input.read(buf, BUFSIZE);
    bufLen = input.gcount();
    index = 0;
    return true;
}
char SCAN::getNextchar() {
    if (eof) return EOF;
    while (index >= bufLen) {
        if (!getNewbuf()) return EOF;
    }
    return buf[index];
}
char SCAN::popNextchar() {
    char c = getNextchar();
    if (c == '\n') linenubmber++;
    index++;
    return c;
}
void SCAN::linenote() {
	char c=getNextchar();
	while(eof==false) {
		popNextchar();
		if(c=='\n') break;
		c=getNextchar();
	}
}
TOKEN_TYPE SCAN::checkID(std::string s) {
    if (table.find(s) != table.end())
        return table[s];
    else
        return ID;
}
TOKEN SCAN::getToken() {
    int state = 1;
    char c = getNextchar();
    std::string s;
    while (c == '\n' || c == ' ' || c == '\t') {
        popNextchar();
        c = getNextchar();
    }
    if (eof) return TOKEN("", FILEEND);
    while (1) {
        c = getNextchar();
        int nextstate = states[state].go(c);
        if (eof) {
            if (states[state].end) {
                if (states[state].tokentype == ID)
                    return TOKEN(s, checkID(s));
                else
                    return TOKEN(s, states[state].tokentype);
            } else {
                return TOKEN("", FILEEND);
            }
        } 
        if (nextstate != 0) {
            state = nextstate;
            s += c;
            popNextchar();
            continue;
        }
        if (states[state].end) {
            if (states[state].tokentype == ID)
                return TOKEN(s, checkID(s));
            else
                return TOKEN(s, states[state].tokentype);
        } else {
            return TOKEN("", FILEEND);
        }
    }
}
