#ifndef RSA_H
#define RSA_H
#include "include.hpp"

class RSA_Private_Key{
    int1024 p;
    int1024 q;
    int1024 d;
    int1024 lambda_n;
public:
    RSA_Private_Key(int1024 p, int1024 q, int1024 d, int1024 lambda_n): p(p), q(q), d(d), lambda_n(lambda_n){}

};

class RSA_Public_Key{
    int1024 n;
    int1024 e;
public:
    RSA_Public_Key(int1024 n, int1024 e): n(n), e(e){}

};

class RSA_Class {
private:
    int1024 get_random_primo(int1024 proibido);
    int1024 get_lambda(int1024 p, int1024 q);
    int1024 get_d(int1024 e, int1024 lambda_n);
    int1024 gcd(int1024 a, int1024 b);
    std::vector<uint8_t>  get_salt(int k0);
    std::string expand_salt(const std::string &salt);
    std::string read_text(const std::string &path);
    void print_vec_uint8(const std::vector<uint8_t> &v);
public:
    std::vector<uint8_t> sha3_256(const std::vector<uint8_t>& input);
    std::pair<RSA_Private_Key, RSA_Public_Key>  generate_keys();
    std::string encrypt(const RSA_Private_Key &p,const RSA_Public_Key &q,const std::string &mensagem);
    std::string decrypt(const RSA_Private_Key &p,const RSA_Public_Key &q,const std::string &mensagem);
    std::string padding(const std::string &mensagem, int k0, int k1);

    std::vector<uint8_t> hash(const std::vector<uint8_t>& r, int length);
    std::string bytes_to_hex_string(const std::vector<uint8_t>& bytes);
    std::vector<uint8_t> xor_vec(const std::vector<uint8_t>&a,const std::vector<uint8_t> &b);
};



#endif