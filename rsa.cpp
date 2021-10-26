#include "rsa.hpp"
#include "millerrabin.hpp"
#include <openssl/sha.h>


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

std::pair<RSA_Private_Key, RSA_Public_Key> RSA::generate_keys(){
    int1024 n, lambda_n, d;
    int1024 p = get_random_primo();
    int1024 q = get_random_primo(p);
    n = p*q;
    lambda_n = get_lambda(p,q);
    int1024 e = 65537;
    d = get_d(e, lambda_n);
    //todo construir o par de chaves
    return std::make_pair(RSA_Private_Key(p,q,d,lambda_n), RSA_Public_Key(n,e));
}

std::string RSA::encrypt(const RSA_Private_Key &p,const RSA_Public_Key &q,const std::string &mensagem){

    return "";
}
std::string RSA::decrypt(const RSA_Private_Key &p,const RSA_Public_Key &q,const std::string &mensagem){

    return "";
}

std::string RSA::padding(const std::string &mensagem){
    std::string padded = "";
    return padded;

}