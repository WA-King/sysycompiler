#include<bits/stdc++.h>
using namespace std;
vector<string> key_word={
    "int",
    "void",
    "const",
    "if",
    "else",
    "\\\\",
    "\\*",
    "while",
    "break",
    "continue",
    ",",
    "[",
    "]",
    "(",
    ")",
    "{",
    "}",
    "+",
    "-",
    "*",
    "/",
    "!",
    "%",
    "==",
    "!=",
    "&&",
    "||",
    "<",
    "<=",
    ">",
    ">=",
};
vector<string> key_TOKEN={
    "INT",
    "VOID",
    "CONST",
    "IF",
    "ELSE",
    "LINE_NOTE"
    "BLOCK_NOTE",
    "WHILE",
    "BREAK",
    "CONTINUE",
    "COMMA",
    "LMBRACKETS",
    "RMBRACKETS",
    "LSBRACKETS",
    "RSBRACKETS",
    "LBBRACKETS",
    "RBBRACKETS",
    "ADD",
    "MINUS",
    "MUL",
    "DIV",
    "NOT",
    "MOD",
    "EQ",
    "NE",
    "AND",
    "OR",
    "LT",
    "LE",
    "GT",
    "GE",
};
struct Tries {
    int nex[100000][300],cnt=0,root;
    bool end[100000];
    string type[100000];
    int newnode() {
        cnt++;
        memset(nex[cnt],0,sizeof(nex[0]));
        return cnt;
    }
    void init() {
        root=newnode();
    }
    void ins(string s,string t) {
        int now=root;
        for(char c:s) {
            if(!nex[now][c]) nex[now][c]=newnode();
            now=nex[now][c];
        }
        end[now]=true;
        type[now]=t;
    }
    void print_node() {
        queue<int> q;
        q.push(root);
        while(!q.empty()) {
            int now=q.front();q.pop();
            if(end[now]) {
                cout<<"states["<<now<<"].end=true;\n";
                cout<<"states["<<now<<"].TOKEN_TYPE="<<type[now]<<";\n";
            }
            for(int i=0;i<300;i++) {
                if(nex[now][i]) q.push(nex[now][i]);
            }
        }
    }
    void print_edge() {
        queue<int> q;
        q.push(root);
        while(!q.empty()) {
            int now=q.front();q.pop();
            for(int i=0;i<300;i++) {
                if(nex[now][i]) {
                    cout<<"states["<<now<<"].addnext(\'"<<char(i)<<"\');\n";
                    q.push(nex[now][i]);
                }
            }
        }
    }
}tree;
int main() {
    freopen("dfa_code.txt","w",stdout):
    tree.init();
    for(int i=0;i<key_word.size();i++) {
        tree.ins(key_word[i],key_TOKEN[i]);
    }
    tree.print_node();
    tree.print_edge();
    return 0;
}
