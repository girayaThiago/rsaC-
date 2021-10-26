#include "include.hpp"
#include "millerrabin.hpp"
#include "rsa.hpp"

using namespace std;
//retorna um numero primo entre 100k e 200k



int main (){

    srand(std::random_device()());
    // string mensagem = "The quick brown fox jumps over the lazy dog (tradução do inglês para A rápida raposa marrom pula por cima do cão preguiçoso) é um pangrama, frase que utiliza todas as letras do alfabeto em língua inglesa.\nAlguns tradutores de programas simplesmente transliteram a citação sem procurar usar um pangrama em português, como \"Um pequeno jabuti xereta viu dez cegonhas felizes\"";
    std::string mensagem = "The quick brown fox jumps over the lazy dog";
    // std::cout << sha3_256(mensagem) << std::endl;
    RSA_Class rsa;
    // unsigned char out[SHA256_DIGEST_LENGTH];

    // rsa.simpleSHA256((void *)mensagem.c_str(), mensagem.length(), out);
    
    // std::string mgf1 = rsa.sha3_256(mensagem);
    std::vector<uint8_t> mgf1 = rsa.G(mensagem);
    cout << mgf1.size() << endl;
    cout << rsa.bytes_to_hex_string(mgf1) << endl;
    printf("\n");
    // std::pair<RSA_Private_Key, RSA_Public_Key> keys = rsa.generate_keys();
    return 0;
}