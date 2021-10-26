#include "rsa.hpp"
#include "millerrabin.hpp"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
// #include <openssl/crypto/rsa>

#define SALT_LENGTH 256
#define PADDING_LENGTH 128
#define KEY_SIZE 1024
// retorna um numero primo aleatório entre 100k e 200k~
int1024 RSA_Class::get_random_primo(int1024 proibido = 0){
    int1024 p = rand()%100000+100000;
    if (!(p&1)) p++;
    while (MillerRabin::test(10,p) || p == proibido){
        p+=2;
    }
    return p;
}

// calcula o lambda dos primos p e q, que é a = p-1 b = q-1 |a*b|/gcd(a,b);
int1024 RSA_Class::get_lambda(int1024 p, int1024 q){
    p--;
    q--;
    return p*q/gcd(p,q);
}

// calcula o valor de d para que d*e mod lambda(n) = 1
int1024 RSA_Class::get_d(int1024 e, int1024 lambda_n){
    int1024 d = 1;
    while ((d*e)%lambda_n != 1) d++;
    return d;
}

// calcula o máximo divisor comum via algoritmo de Eclide
int1024 RSA_Class::gcd(int1024 a, int1024 b){
    while (a != b){
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

std::pair<RSA_Private_Key, RSA_Public_Key> RSA_Class::generate_keys(){
    int1024 n, lambda_n, d;
    int1024 p = get_random_primo();
    int1024 q = get_random_primo(p);
    n = p*q;
    lambda_n = get_lambda(p,q);
    int1024 e = 65537;
    d = get_d(e, lambda_n);
    return std::make_pair(RSA_Private_Key(p,q,d,lambda_n), RSA_Public_Key(n,e));
}

std::string RSA_Class::encrypt(const RSA_Private_Key &p,const RSA_Public_Key &q,const std::string &mensagem){
    std::string padded = padding(mensagem, SALT_LENGTH,PADDING_LENGTH);

    return "";
}
std::string RSA_Class::decrypt(const RSA_Private_Key &p,const RSA_Public_Key &q,const std::string &mensagem){

    return "";
}

std::string RSA_Class::padding(const std::string &mensagem, int k0, int k1){
    int i = mensagem.size();
    std::cout << "mensagem pré padding = " << mensagem.size() << std::endl;
    std::string padded = mensagem;
    padded = padded.append(KEY_SIZE-k0-i, '\0');
    std::string salt = get_salt(k0);
    std::string G_salt = sha3_256(salt); // esse é o m;


    std::cout << "mensagem pós padding = " << padded.size() << std::endl;
    return padded;
}

std::string RSA_Class::expand_salt(const std::string &salt){
    return "";
}

std::string read_text(const std::string &path){
    std::ifstream f;
    f.open(path);
    if (!f.good()) exit(-1);

    f.seekg (0, f.end);
    int length = f.tellg();
    f.seekg (0, f.beg);

    char * buffer = new char [length+1];

    std::cout << "Reading " << length << " characters... ";

    f.read (buffer,length);
    buffer[length] = '\0';
    if (f)
        std::cout << "all characters read successfully.";
    else
        std::cout << "error: only " << f.gcount() << " could be read";
    f.close();

    std::string s(buffer);
    delete[] buffer;
    return s;
}

std::string RSA_Class::get_salt(int k0){
    std::string s = "";
    for (int i = 0 ; i < k0/8; i++){
        int r = rand()%94+33;
        char c = r;
        s.append(1,c);
    }
    return s;
}

//helper function to print the digest bytes as a hex string
std::string RSA_Class::bytes_to_hex_string(const std::vector<uint8_t>& bytes)
{
    std::ostringstream stream;
    std::cout << "size of bytes[] = " << bytes.size() << std::endl;
    for (uint8_t b : bytes)
    {
        stream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(b);
    }

    return stream.str();
}

//perform the SHA3-256 hash
std::string RSA_Class::sha3_256(const std::string& input)
{
    uint32_t digest_length = SHA256_DIGEST_LENGTH;
    const EVP_MD* algorithm = EVP_sha3_256();
    uint8_t* digest = static_cast<uint8_t*>(OPENSSL_malloc(digest_length));
    std::cout << input << std::endl;
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, algorithm, nullptr);
    EVP_DigestUpdate(context, input.c_str(), input.size());
    EVP_DigestFinal_ex(context, digest, &digest_length);
    EVP_MD_CTX_destroy(context);

    std::string output = bytes_to_hex_string(std::vector<uint8_t>(digest, digest + digest_length));
    OPENSSL_free(digest);
    return output;
}


std::string RSA_Class::G(const std::string& r){
    int counter = 0;
    
    std::string concat = "";
    std::stringstream s; 
    while (s.str().size() < KEY_SIZE-SALT_LENGTH){
        char* p = (char*) &counter;
        std::string rc = r + p[0] + p[1] + p[2] + p[3];
        std::cout << rc << std::endl;
        s << sha3_256(rc);
        counter++;
    }
    return s.str().substr(0,KEY_SIZE-SALT_LENGTH);
}

std::string test(const std::string &message){
    int c = 0;
    
    std::string concat = message + std::string();
}