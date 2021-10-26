#include "include.hpp"
#include "millerrabin.hpp"
#include "rsa.hpp"
#include <openssl/sha.h>
#include <openssl/evp.h>

using namespace std;
//retorna um numero primo entre 100k e 200k

//helper function to print the digest bytes as a hex string
std::string bytes_to_hex_string(const std::vector<uint8_t>& bytes)
{
    std::ostringstream stream;
    std::cout << "size of bytes[] = " << bytes.size() << endl;
    for (uint8_t b : bytes)
    {
        stream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(b);
    }
    return stream.str();
}

// //perform the SHA3-256 hash
std::string sha3_256(const std::string& input)
{
    uint32_t digest_length = SHA256_DIGEST_LENGTH;
    const EVP_MD* algorithm = EVP_sha3_256();
    uint8_t* digest = static_cast<uint8_t*>(OPENSSL_malloc(digest_length));
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, algorithm, nullptr);
    EVP_DigestUpdate(context, input.c_str(), input.size());
    EVP_DigestFinal_ex(context, digest, &digest_length);
    EVP_MD_CTX_destroy(context);
    std::string output = bytes_to_hex_string(std::vector<uint8_t>(digest, digest + digest_length));
    OPENSSL_free(digest);
    return output;
}

int main (){

    srand(std::random_device()());
    // string mensagem = "The quick brown fox jumps over the lazy dog (tradução do inglês para A rápida raposa marrom pula por cima do cão preguiçoso) é um pangrama, frase que utiliza todas as letras do alfabeto em língua inglesa.\nAlguns tradutores de programas simplesmente transliteram a citação sem procurar usar um pangrama em português, como \"Um pequeno jabuti xereta viu dez cegonhas felizes\"";
    std::string mensagem = "The quick brown fox jumps over the lazy dog";
    std::cout << sha3_256(mensagem) << std::endl;
    // RSA rsa;
    // std::pair<RSA_Private_Key, RSA_Public_Key> keys = rsa.generate_keys();
    return 0;
}