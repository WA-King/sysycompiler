#include <bits/stdc++.h>
using namespace std;
vector<string> key_word = {
    "\\\\", "\\*", "*\\", ";",  ",", "[",  "]", "(",  ")",
    "{",    "}",   "+",   "-",  "*", "/",  "!", "%",  "=",
    "==",   "!=",  "&&",  "||", "<", "<=", ">", ">=",
};
vector<string> key_TOKEN = {
    "LINE_NOTE",  "LBLOCK_NOTE", "RBLOCK_NOTE", "SEMICOLON",  "COMMA",
    "LMBRACKETS", "RMBRACKETS",  "LSBRACKETS",  "RSBRACKETS", "LBBRACKETS",
    "RBBRACKETS", "ADD",         "MINUS",       "MUL",        "DIV",
    "NOT",        "MOD",         "ASSIGN",      "EQ",         "NE",
    "AND",        "OR",          "LT",          "LE",         "GT",
    "GE",
};
struct Tries {
    int nex[1000][300], cnt = 0, root;
    bool end[1000];
    string type[1000];
    int newnode() {
        cnt++;
        memset(nex[cnt], 0, sizeof(nex[0]));
        return cnt;
    }
    void init() { root = newnode(); }
    void ins(string s, string t) {
        int now = root;
        for (char c : s) {
            if (!nex[now][c]) nex[now][c] = newnode();
            now = nex[now][c];
        }
        end[now] = true;
        type[now] = t;
    }
    void add_num() {
        int num_node = newnode();
        end[num_node] = true;
        type[num_node] = "NUM";
        for (int i = '0'; i <= '9'; i++) {
            nex[1][i] = num_node;
            nex[num_node][i] = num_node;
        }
    }
    void add_id() {
        int id_node = newnode();
        end[id_node] = true;
        type[id_node] = "ID";
        nex[1]['_'] = id_node;
        nex[id_node]['_'] = id_node;
        for (int i = 'a'; i <= 'z'; i++) {
            nex[1][i] = id_node;
            nex[id_node][i] = id_node;
        }
        for (int i = 'A'; i <= 'Z'; i++) {
            nex[1][i] = id_node;
            nex[id_node][i] = id_node;
        }
        for (int i = '0'; i <= '9'; i++) {
            nex[id_node][i] = id_node;
        }
    }
    void print_node() {
        queue<int> q;
        vector<bool> vis(100);
        q.push(root);
        vis[root] = true;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            if (end[now]) {
                cout << "states[" << now << "].end=true;\n";
                cout << "states[" << now << "].tokentype=" << type[now]
                     << ";\n";
                // cout<<type[now]<<",\n";
            }
            for (int i = 0; i < 300; i++) {
                if (nex[now][i] && vis[nex[now][i]] == false) {
                    q.push(nex[now][i]);
                    vis[nex[now][i]] = true;
                }
            }
        }
    }
    void print_edge() {
        vector<bool> vis(100);
        queue<int> q;
        q.push(root);
        vis[root] = true;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int i = 0; i < 300; i++) {
                if (nex[now][i]) {
                    cout << "states[" << now << "].addnext(" << nex[now][i]
                         << ",\'" << char(i) << "\');\n";
                    if (vis[nex[now][i]] == false) {
                        q.push(nex[now][i]);
                        vis[nex[now][i]] = true;
                    }
                }
            }
        }
    }
} tree;
int main() {
    // freopen("TOKEN_TYPE.txt","w",stdout);
    freopen("dfa_code.txt", "w", stdout);
    tree.init();
    for (int i = 0; i < key_word.size(); i++) {
        tree.ins(key_word[i], key_TOKEN[i]);
    }
    tree.add_id();
    tree.add_num();
    tree.print_node();
    tree.print_edge();
    return 0;
}
