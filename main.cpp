#include <iostream>
#include "millerrabin.hpp"


int main (){
    MillerRabin mr;
    int1024 k = 2, n = 15;
    mr.test(k,n);
    return 0;
}