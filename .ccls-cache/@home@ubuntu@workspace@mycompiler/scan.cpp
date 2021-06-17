#include "scan.h"

#include <cstring>
#include <iostream>
#define LZNB(x)                 \
    case (x):                   \
        std::cout << #x << ' '; \
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
    states[18].end = true;
    states[18].tokentype = NOT;
    states[19].end = true;
    states[19].tokentype = MOD;
    states[11].end = true;
    states[11].tokentype = LSBRACKETS;
    states[12].end = true;
    states[12].tokentype = RSBRACKETS;
    states[5].end = true;
    states[5].tokentype = MUL;
    states[15].end = true;
    states[15].tokentype = ADD;
    states[8].end = true;
    states[8].tokentype = COMMA;
    states[16].end = true;
    states[16].tokentype = MINUS;
    states[17].end = true;
    states[17].tokentype = DIV;
    states[32].end = true;
    states[32].tokentype = NUM;
    states[7].end = true;
    states[7].tokentype = SEMICOLON;
    states[27].end = true;
    states[27].tokentype = LT;
    states[20].end = true;
    states[20].tokentype = ASSIGN;
    states[29].end = true;
    states[29].tokentype = GT;
    states[31].end = true;
    states[31].tokentype = ID;
    states[9].end = true;
    states[9].tokentype = LMBRACKETS;
    states[10].end = true;
    states[10].tokentype = RMBRACKETS;
    states[13].end = true;
    states[13].tokentype = LBBRACKETS;
    states[14].end = true;
    states[14].tokentype = RBBRACKETS;
    states[22].end = true;
    states[22].tokentype = NE;
    states[24].end = true;
    states[24].tokentype = AND;
    states[6].end = true;
    states[6].tokentype = RBLOCK_NOTE;
    states[28].end = true;
    states[28].tokentype = LE;
    states[21].end = true;
    states[21].tokentype = EQ;
    states[30].end = true;
    states[30].tokentype = GE;
    states[4].end = true;
    states[4].tokentype = LBLOCK_NOTE;
    states[3].end = true;
    states[3].tokentype = LINE_NOTE;
    states[26].end = true;
    states[26].tokentype = OR;
    states[1].addnext(18, '!');
    states[1].addnext(19, '%');
    states[1].addnext(23, '&');
    states[1].addnext(11, '(');
    states[1].addnext(12, ')');
    states[1].addnext(5, '*');
    states[1].addnext(15, '+');
    states[1].addnext(8, ',');
    states[1].addnext(16, '-');
    states[1].addnext(17, '/');
    states[1].addnext(32, '0');
    states[1].addnext(32, '1');
    states[1].addnext(32, '2');
    states[1].addnext(32, '3');
    states[1].addnext(32, '4');
    states[1].addnext(32, '5');
    states[1].addnext(32, '6');
    states[1].addnext(32, '7');
    states[1].addnext(32, '8');
    states[1].addnext(32, '9');
    states[1].addnext(7, ';');
    states[1].addnext(27, '<');
    states[1].addnext(20, '=');
    states[1].addnext(29, '>');
    states[1].addnext(31, 'A');
    states[1].addnext(31, 'B');
    states[1].addnext(31, 'C');
    states[1].addnext(31, 'D');
    states[1].addnext(31, 'E');
    states[1].addnext(31, 'F');
    states[1].addnext(31, 'G');
    states[1].addnext(31, 'H');
    states[1].addnext(31, 'I');
    states[1].addnext(31, 'J');
    states[1].addnext(31, 'K');
    states[1].addnext(31, 'L');
    states[1].addnext(31, 'M');
    states[1].addnext(31, 'N');
    states[1].addnext(31, 'O');
    states[1].addnext(31, 'P');
    states[1].addnext(31, 'Q');
    states[1].addnext(31, 'R');
    states[1].addnext(31, 'S');
    states[1].addnext(31, 'T');
    states[1].addnext(31, 'U');
    states[1].addnext(31, 'V');
    states[1].addnext(31, 'W');
    states[1].addnext(31, 'X');
    states[1].addnext(31, 'Y');
    states[1].addnext(31, 'Z');
    states[1].addnext(9, '[');
    states[1].addnext(2, '\\');
    states[1].addnext(10, ']');
    states[1].addnext(31, '_');
    states[1].addnext(31, 'a');
    states[1].addnext(31, 'b');
    states[1].addnext(31, 'c');
    states[1].addnext(31, 'd');
    states[1].addnext(31, 'e');
    states[1].addnext(31, 'f');
    states[1].addnext(31, 'g');
    states[1].addnext(31, 'h');
    states[1].addnext(31, 'i');
    states[1].addnext(31, 'j');
    states[1].addnext(31, 'k');
    states[1].addnext(31, 'l');
    states[1].addnext(31, 'm');
    states[1].addnext(31, 'n');
    states[1].addnext(31, 'o');
    states[1].addnext(31, 'p');
    states[1].addnext(31, 'q');
    states[1].addnext(31, 'r');
    states[1].addnext(31, 's');
    states[1].addnext(31, 't');
    states[1].addnext(31, 'u');
    states[1].addnext(31, 'v');
    states[1].addnext(31, 'w');
    states[1].addnext(31, 'x');
    states[1].addnext(31, 'y');
    states[1].addnext(31, 'z');
    states[1].addnext(13, '{');
    states[1].addnext(25, '|');
    states[1].addnext(14, '}');
    states[18].addnext(22, '=');
    states[23].addnext(24, '&');
    states[5].addnext(6, '\\');
    states[32].addnext(32, '0');
    states[32].addnext(32, '1');
    states[32].addnext(32, '2');
    states[32].addnext(32, '3');
    states[32].addnext(32, '4');
    states[32].addnext(32, '5');
    states[32].addnext(32, '6');
    states[32].addnext(32, '7');
    states[32].addnext(32, '8');
    states[32].addnext(32, '9');
    states[27].addnext(28, '=');
    states[20].addnext(21, '=');
    states[29].addnext(30, '=');
    states[31].addnext(31, '0');
    states[31].addnext(31, '1');
    states[31].addnext(31, '2');
    states[31].addnext(31, '3');
    states[31].addnext(31, '4');
    states[31].addnext(31, '5');
    states[31].addnext(31, '6');
    states[31].addnext(31, '7');
    states[31].addnext(31, '8');
    states[31].addnext(31, '9');
    states[31].addnext(31, 'A');
    states[31].addnext(31, 'B');
    states[31].addnext(31, 'C');
    states[31].addnext(31, 'D');
    states[31].addnext(31, 'E');
    states[31].addnext(31, 'F');
    states[31].addnext(31, 'G');
    states[31].addnext(31, 'H');
    states[31].addnext(31, 'I');
    states[31].addnext(31, 'J');
    states[31].addnext(31, 'K');
    states[31].addnext(31, 'L');
    states[31].addnext(31, 'M');
    states[31].addnext(31, 'N');
    states[31].addnext(31, 'O');
    states[31].addnext(31, 'P');
    states[31].addnext(31, 'Q');
    states[31].addnext(31, 'R');
    states[31].addnext(31, 'S');
    states[31].addnext(31, 'T');
    states[31].addnext(31, 'U');
    states[31].addnext(31, 'V');
    states[31].addnext(31, 'W');
    states[31].addnext(31, 'X');
    states[31].addnext(31, 'Y');
    states[31].addnext(31, 'Z');
    states[31].addnext(31, '_');
    states[31].addnext(31, 'a');
    states[31].addnext(31, 'b');
    states[31].addnext(31, 'c');
    states[31].addnext(31, 'd');
    states[31].addnext(31, 'e');
    states[31].addnext(31, 'f');
    states[31].addnext(31, 'g');
    states[31].addnext(31, 'h');
    states[31].addnext(31, 'i');
    states[31].addnext(31, 'j');
    states[31].addnext(31, 'k');
    states[31].addnext(31, 'l');
    states[31].addnext(31, 'm');
    states[31].addnext(31, 'n');
    states[31].addnext(31, 'o');
    states[31].addnext(31, 'p');
    states[31].addnext(31, 'q');
    states[31].addnext(31, 'r');
    states[31].addnext(31, 's');
    states[31].addnext(31, 't');
    states[31].addnext(31, 'u');
    states[31].addnext(31, 'v');
    states[31].addnext(31, 'w');
    states[31].addnext(31, 'x');
    states[31].addnext(31, 'y');
    states[31].addnext(31, 'z');
    states[2].addnext(4, '*');
    states[2].addnext(3, '\\');
    states[25].addnext(26, '|');

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
