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
    if (!(p.odd())) p++;
    while (!MillerRabin::test(6,p) || p == proibido){
        p+=2;
    }
    return p;
}

// calcula o lambda dos primos p e q, que é a = p-1 b = q-1 |a*b|/gcd(a,b);
int1024 RSA_Class::get_lambda_d(int1024 p, int1024 q, int1024* lambda_p, int1024* d_p){
    p--;
    q--;
    mpz_t num1, num2, gcd,d1, d2, e, lambda;
	mpz_inits(num1, num2, lambda, gcd, e, d1, d2, NULL);
	mpz_set_str(num1,p.to_string().c_str(), 2);
	mpz_set_str(num2,q.to_string().c_str(), 2);
    mpz_set_ui(e,65537);
    mpz_mul(lambda, num1, num2);
    mpz_gcdext(gcd,d1,d2,num1,num2);
    mpz_div(lambda, lambda, gcd);
    mpz_gcdext(gcd, d1,d2,e,lambda);
    //recupera os valores
    char c[1025];
    char c2[1025];
	mpz_get_str(c,2,lambda);
	int1024 test = std::string(c);
    *lambda_p = test;
    std::cout << "will assign";
    if (mpz_cmp(d1,d2) > 0){
        std::cout << " d1 = ";
        mpz_out_str(stdout, 10,d1);
        std::cout << std::endl;
        mpz_out_str(stdout, 2,d1);
        mpz_get_str(c2,2,d1);  
    } else {
        std::cout << " d2 = ";
        mpz_out_str(stdout, 10,d2);
        std::cout << std::endl;
        mpz_out_str(stdout, 2,d2);
        mpz_get_str(c2,2,d2);    
    }
    std::cout << std::endl;
    int1024 test2 = std::string(c2);
    *d_p = test2;
    // std::cout << "assigned test2 -> to *dp" << std::endl;
	mpz_clears(num1, num2, lambda, gcd, d1, e, d2, NULL);
    // std::cout << "cleared mpz_nums" << std::endl;
    return 0;
}

std::pair<RSA_Private_Key, RSA_Public_Key> RSA_Class::generate_keys(){
    int1024 n, lambda_n, d;
    // std::cout << "entrou em generate keys()" << std::endl;
    int1024 p = get_random_primo();
    // std::cout << p.to_string() << std::endl;
    int1024 q = get_random_primo(p);
    // std::cout << q.to_string() << std::endl;
    n = p*q;

    get_lambda_d(p,q,&lambda_n,&d);
    
    // std::cout << lambda_n.to_string() << std::endl;
    int1024 e = 65537;
    if (e * d % lambda_n == 1) std::cout << "deu bom" << std::endl;
    else std::cout << "deu ruim" << std::endl;
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
    // std::cout << "mensagem pré padding = " << mensagem.size() << std::endl;
    std::string padded = mensagem;
    padded = padded.append(KEY_SIZE-k0-i, '\0');
    // std::cout << "mensagem pós padding = " << padded.size() << std::endl;
    std::vector<uint8_t> padded_uint8;
    padded_uint8.insert(padded_uint8.end(), padded.begin(), padded.end());
    std::cout << padded_uint8.size() << std::endl;
    for (int i : padded_uint8) std::cout << i;
    std::cout << std::endl;
    std::vector<uint8_t> salt = get_salt(k0);
    std::vector<uint8_t> G_salt = hash(salt, KEY_SIZE-SALT_LENGTH); // esse é o m G(r);
    std::vector<uint8_t> xor_G_r = xor_vec(G_salt, padded_uint8);
    print_vec_uint8(xor_G_r);
    std::vector<uint8_t> H_xor = hash(xor_G_r, SALT_LENGTH);
    print_vec_uint8(H_xor);
    // std::ios_base::binary 
    
    return padded;
}

void RSA_Class::print_vec_uint8(const std::vector<uint8_t> &v){
    std::cout << "tamanho do vetor = " <<v.size() << std::endl;
    for (int i = 0; i<v.size(); i++){
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)v[i] << " ";
    } 
    std::cout << std::endl;
}
std::vector<uint8_t> RSA_Class::xor_vec(const std::vector<uint8_t> &a,const  std::vector<uint8_t> &b){
    std::vector<uint8_t> result(a.size());
    for (int i = 0; i < a.size(); i++){
        result[i] = a[i]^b[i];
    }
    return result;
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

std::vector<uint8_t> RSA_Class::get_salt(int k0){
    std::vector<uint8_t> s;
    for (int i = 0 ; i < k0/8; i++){
        int r = rand()%94+33;
        uint8_t c = r;
        s.push_back(c);
    }
    return s;
}

//helper function to print the digest bytes as a hex string
std::string RSA_Class::bytes_to_hex_string(const std::vector<uint8_t>& bytes)
{
    std::ostringstream stream;
    for (uint8_t b : bytes)
    {
        stream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(b);
    }

    return stream.str();
}

std::vector<uint8_t> RSA_Class::sha3_256(const std::vector<uint8_t>& input)
{
    uint32_t digest_length = SHA256_DIGEST_LENGTH;
    const EVP_MD* algorithm = EVP_sha3_256();
    uint8_t* digest = static_cast<uint8_t*>(OPENSSL_malloc(digest_length));
    // std::cout << input << std::endl;
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, algorithm, nullptr);
    EVP_DigestUpdate(context, &input[0], input.size());
    EVP_DigestFinal_ex(context, digest, &digest_length);
    EVP_MD_CTX_destroy(context);

    std::vector<uint8_t> output = std::vector<uint8_t>(digest, digest + digest_length);
    OPENSSL_free(digest);
    return output;
}

std::vector<uint8_t> RSA_Class::hash(const std::vector<uint8_t> &r, int length){
    unsigned int counter = 0;
    
    std::vector<uint8_t> s; 
    while (s.size() < length){
        uint8_t* p = (uint8_t*)&counter;
        std::vector<uint8_t> rc = r;
        for (int i = 0; i < 4; i++) rc.push_back(p[i]);
        

        // std::cout << rc << std::endl;
        std::vector<uint8_t> aux = sha3_256(rc);
        s.insert(s.end(),aux.begin(),aux.end()); 
        counter++;
    }
    return s;
}