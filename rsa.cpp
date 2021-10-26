#include "rsa.hpp"




int1024 RSA::get_random_primo(int1024 proibido = 0){
    int1024 p = rand()%100000+100000;
    if (!(p&1)) p++;
    while (MillerRabin::test(10,p) || p == proibido){
        p+=2;
    }
    return p;
}
int1024 RSA::get_lambda(int1024 p, int1024 q){
    p--;
    q--;
    return p*q/gcd(p,q);
}

int1024 RSA::get_d(int1024 e, int1024 lambda_n){
    int1024 d = 1;
    while ((d*e)%lambda_n != 1) d++;
    return d;
}

int1024 RSA::gcd(int1024 a, int1024 b){
    while (a != b){
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}