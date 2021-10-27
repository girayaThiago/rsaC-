#include "millerrabin.hpp"
#include "rsa.hpp"

// testa o numero k vezes para ver se ele é primo. retorna verdadeiro se ele talvez seja primo, retorna falso se não for.
bool MillerRabin::test(int k, int1024 n) {
    n.to_mpz_string();
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
    int1024 x,r,d;
    calc_R_D(n, &r, &d);
    
    
    // printf("r = %d, d = %d\n", r, d);

    while (k-- > 0){
        int1024 a = rand()+2;
        x = power(a,d,n);
        // std::cout << "k = " << k << std::endl;
        if (!(x == 1 || x == n-1)){
            for (int1024 i = 0; i < r-1; i++){
                x = power(x,2,n);
                if (x == n-1) break;
            }
            if (x != n-1) {
                // std::cout << "entrou no if, true"  << std::endl;
                return false;
            } else {
                // std::cout << "entrou no if, false" << std::endl;
            }
        }
        
    }
    return true;
}

// calcula R e D;
void MillerRabin::calc_R_D(int1024 n, int1024* r, int1024 *d){
    int1024 m = n-1;
    int1024 local_r = 0;
    while(!(m.odd())){
        m >>= 1;
        local_r++;
    }
    *r = local_r;
    *d = m;
}

// exponenciacão rápida modular.
int1024 MillerRabin::power(int1024 a, int1024 d, int1024 n){
    int1024 resultado = 1;
    a = a % n;
    while (d > 0){
        if (d.odd()){
            resultado = (resultado * a) % n;
        }
        d >>= 1;
        a = (a * a)%n;
    }
    return resultado;

}