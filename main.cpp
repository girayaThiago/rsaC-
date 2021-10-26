#include "include.hpp"

using namespace std;
//retorna um numero primo entre 100k e 200k

int main (){
    
    srand(std::random_device()());
    
    int1024 n, lambda_n;
    int1024 p = get_random_primo();
    int1024 q = get_random_primo(p);
    n = p*q;
    lambda_n = get_lambda(p,q);
    int1024 e = 65537;
    get_d(e, lambda_n);

    return 0;
}