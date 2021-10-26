#include <bits/stdc++.h>
#include "millerrabin.hpp"

bool MillerRabin::test(int1024 k, int1024 n) {
    if (n <= 3) return true;
    int1024 x,r,d;
    calc_R_D(n, &r, &d);
    
    
    printf("r = %d, d = %d\n", r, d);
    while (k){
        int1024 a = 2 + rand()%(n-4);
        printf("a = %u\n", a);
        power(a,d,n);
        k--;
    }
    return false;
}
void MillerRabin::calc_R_D(int1024 n, int1024* r, int1024 *d){
    int1024 m = n-1;
    int1024 local_r = 0;

    while(!(m&1)){
        m = m>>1;
        local_r++;
    }
    *r = local_r;
    *d = m;
}

int1024 MillerRabin::power(int1024 a, int1024 d, int1024 n){
    int1024 resultado = 1;
    a = a % n;
    while (d > 0){
        if (d & 1){
            resultado = (resultado * a) % n;
        }
        d = d>>1;
        a = (a * a)%n;
        printf("d = %d a = %d\n", d, a);
    }
    printf("resultado = %d\n", resultado);
    return resultado;

}