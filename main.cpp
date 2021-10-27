#include "include.hpp"
#include "millerrabin.hpp"
#include "rsa.hpp"

using namespace std;
//retorna um numero primo entre 100k e 200k



int main (){

    srand(std::random_device()());
    // string mensagem = "The quick brown fox jumps over the lazy dog (tradução do inglês para A rápida raposa marrom pula por cima do cão preguiçoso) é um pangrama, frase que utiliza todas as letras do alfabeto em língua inglesa.\nAlguns tradutores de programas simplesmente transliteram a citação sem procurar usar um pangrama em português, como \"Um pequeno jabuti xereta viu dez cegonhas felizes\"";
    std::string mensagem = "The quick brown fox jumps over the lazy dog";
    RSA_Class rsa;
    std::pair<RSA_Private_Key, RSA_Public_Key> keys = rsa.generate_keys();
    cout << "gerou chaves" << endl;
    rsa.encrypt(keys.first, keys.second, mensagem);
    cout << "encrypted" << endl;
    return 0;
}