#ifndef RSA_H
#define RSA_H
#include "include.hpp"

class RSA {
    
int1024 get_random_primo(int1024 proibido = 0);
int1024 get_lambda(int1024 p, int1024 q);
int1024 get_d(int1024 e, int1024 lambda_n);
int1024 gcd(int1024 a, int1024 b);

};


class RSA_Private_Key{
    int1024 d;
    int1024 p;
    int1024 q;
    int1024 lambda_n;
};

class RSA_Public_Key{
    int1024 e;
    int1024 n;
};

#endif