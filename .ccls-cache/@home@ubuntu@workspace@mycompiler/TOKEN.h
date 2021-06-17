#ifndef _TOKEN_h__
#define _TOKEN_h__
#include"global.h"
class TOKEN {
public:
    TOKEN_TYPE type;
    std::string val;
    TOKEN() = default;
    TOKEN(std::string _v,TOKEN_TYPE _t):val(_v),type(_t) {}
};
void perror(std::string msg);
#endif
