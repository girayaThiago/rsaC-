#include "millerrabin.hpp"

// testa o numero k vezes para ver se ele é primo. retorna verdadeiro se ele talvez seja primo, retorna falso se não for.
bool MillerRabin::test(int1024 k, int1024 n) {
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
    int1024 x,r,d;
    calc_R_D(n, &r, &d);
    
    
    // printf("r = %d, d = %d\n", r, d);

    while (k-- > 0){
        std::cout << k.to_string() << std::endl;
        int arand = rand();
        int1024 a = arand;
        a = a % (n-4);
        a += 2;
        x = power(a,d,n);
        if (!(x == 1 || x == n-1)){
            for (int1024 i = 0; i < r-1; i++){
                x = power(x,2,n);
                if (x == n-1) break;
            }
            if (x != n-1) return false;
        }
        
    }
    return true;
}

// calcula R e D;
void MillerRabin::calc_R_D(int1024 n, int1024* r, int1024 *d){
    int1024 m = n-1;
    int1024 local_r = 0;
    printf("entrou em calc_r_d\n");
    while(!(m.odd())){
        m >>= 1;
        local_r++;
    }
    *r = local_r;
    *d = m;
    printf("saiu de calc_r_d\n");
}

// exponenciacão rápida modular.
int1024 MillerRabin::power(int1024 a, int1024 d, int1024 n){
    std::cout << "entrou em power" << std::endl;
    int1024 resultado = 1;
    a = a % n;
    while (d > 0){
        // se d & 1 é verdadeiro expoente é impar (ou o expoente é impar ou terminamos de exponenciar ao numero par e o expoente agora é 1)
        if (d.odd()){
            resultado = (resultado * a) % n;
        }
        d >>= 1;
        a = (a * a)%n;
    }
    return resultado;

}