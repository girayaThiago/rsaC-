#include "rsa.hpp"
#include "millerrabin.hpp"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
// #include <openssl/crypto/rsa>

#define SALT_LENGTH 256/8
#define PADDING_LENGTH 128/8
#define KEY_SIZE 1024/8
// retorna um numero primo aleatório entre 100k e 200k~
int1024 RSA_Class::get_random_primo(int1024 proibido = 0){
    // mpz_t num1;
	// mpz_init(num1);
	// std::string s;
    // if (proibido == 0){
    //     s = "31060417014537475679";
    // } else if (proibido == 1){
    //     s = "57321168577908092509";
    // } else if (proibido == 2){
    //     s = "73423288583287125401";
    // } else {
    //     s = "67539680682241914533";
    // }
    // char c[1025];
    // mpz_set_str(num1, s.c_str(),10);
	// mpz_get_str(c,2,num1);
	// int1024 test = std::string(c);
	// mpz_clear(num1);
    // return test;
    
        
    int1024 max;
    max.set();
    int1024 min;
    min.reset();
    // limitando os numeros pq miller rabin n tem o dia inteiro.
    for (int i = 1; i < 128; i++){
        max.reset(max.size()-i);
    }
    min.set(min.size()-176);
    int1024 p;
    p = int1024::random(min,max, randstate);
    if (!(p.odd())) p++;
    while (!MillerRabin::test(3,p)) {
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
    mpz_gcdext(gcd,d1,d2,e,lambda);
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
    int1024 p = get_random_primo(0);
    std::cout << "primeira chave escolhida = "; 
    p.to_mpz_string();
    // yolo existe uma chance de p == q :D
    int1024 q = get_random_primo(1);
    std::cout << "segunda chave escolhida = "; 
    q.to_mpz_string();
    n = p*q;

    get_lambda_d(p,q,&lambda_n,&d);
    
    int1024 e = 65537;
    if (e * d % lambda_n == 1) std::cout << "deu bom" << std::endl;
    else std::cout << "deu ruim" << std::endl;
    return std::make_pair(RSA_Private_Key(p,q,d,lambda_n), RSA_Public_Key(n,e));
}

int1024 RSA_Class::encrypt(const RSA_Private_Key &p,const RSA_Public_Key &q1,const RSA_Public_Key &q2,const std::string &mensagem){
    std::vector<uint8_t> padded = padding(mensagem, SALT_LENGTH,PADDING_LENGTH);
    printf(":D\n");
    // converter padded para int1024 e elevar a 'e';
    int1024 padded_num(padded);
    // padded_num^e; 
    print_vec_uint8(padded);
    std::cout << padded_num.to_hex_string() << std::endl;
    // std::cout << "q.e = " << q.e.to_ullong() << "q.n = " << q.n.to_ullong() << std::endl;
    //alice alice
    int1024 encrypted = MillerRabin::power(padded_num, q2.e,q2.n);
    // signing alice bob
    encrypted = MillerRabin::power(encrypted, p.d,q1.n);
    std::cout << encrypted.to_hex_string() << std::endl;
    return encrypted;
}
std::string RSA_Class::decrypt(const RSA_Private_Key &p,const RSA_Public_Key &q1,const RSA_Public_Key &q2, int1024 mensagem){
    // unsigning
    int1024 unsign = MillerRabin::power(mensagem, q2.e,q2.n);
    unsign = MillerRabin::power(unsign, p.d,q1.n);
    std::vector<uint8_t> P = unsign.to_vec8();
    std::vector<uint8_t> P1;
    std::vector<uint8_t> P2;
    P1.insert(P1.begin(), P.begin(), P.end()-SALT_LENGTH);
    P2.insert(P2.begin(), P.end()-SALT_LENGTH,P.end());
    std::vector<uint8_t> H_p1 = hash(P1, KEY_SIZE-SALT_LENGTH);
    std::vector<uint8_t> r = xor_vec(H_p1, P2);
    std::vector<uint8_t> G_r = hash(r, SALT_LENGTH);
    std::vector<uint8_t> decrypt = xor_vec(G_r, P1);
    std::string decrypted;
    for (auto b : decrypt){
        decrypted.append(1,(char)b);
    }
    return decrypted;
}

// Padding OAEP
std::vector<uint8_t> RSA_Class::padding(const std::string &mensagem, int k0, int k1){
    int i = mensagem.size();
    // std::cout << "mensagem pré padding = " << mensagem.size() << std::endl;
    std::string padded = mensagem;
    padded = padded.append(KEY_SIZE-k0-i, '\0');
    // std::cout << "mensagem pós padding = " << padded << "tamanho = " << padded.size() << " " << std::endl;
    std::vector<uint8_t> padded_uint8;
    padded_uint8.insert(padded_uint8.end(), padded.begin(), padded.end());
    // std::cout << padded_uint8.size() << std::endl;
    for (int i : padded_uint8) std::cout << i;
    std::cout << std::endl;
    std::vector<uint8_t> r = get_salt(k0); // r
    // std::cout << "salt:";
    // print_vec_uint8(r);
    std::vector<uint8_t> G_r = hash(r, KEY_SIZE-SALT_LENGTH ); // esse é o m G(r);
    // std::cout << "G(r):";
    // print_vec_uint8(G_r);
    std::vector<uint8_t> xor_G_r = xor_vec(G_r, padded_uint8); // aplica xor com G(r) e salt
    // std::cout << "xor (G(r), r):";
    // print_vec_uint8(xor_G_r);

    std::vector<uint8_t> H_mensagem = hash(xor_G_r, SALT_LENGTH);
    std::vector<uint8_t> xor_H_r = xor_vec(H_mensagem, r);
    // OAEP feito
    xor_G_r.insert(xor_G_r.end(), xor_H_r.begin(), xor_H_r.end());
    // std::ios_base::binary 
    std::cout << "padding OAEP feito" << std::endl;
    print_vec_uint8(xor_G_r);
    return xor_G_r;
}

void RSA_Class::print_vec_uint8(const std::vector<uint8_t> &v){
    std::cout << "tamanho do vetor = " <<v.size() << std::endl;
    for (int i = 0; i<v.size(); i++){
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)v[i] << " ";
    }
    std::cout << std::endl << std::dec;
}
std::vector<uint8_t> RSA_Class::xor_vec(const std::vector<uint8_t> &a,const  std::vector<uint8_t> &b){
    std::vector<uint8_t> result(a.size());
    for (int i = 0; i < a.size(); i++){
        result[i] = a[i]^b[i];
    }
    return result;
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
    
    for (int i = 0 ; i < k0; i++){
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
    std::cout << "executando has expansivo para tamanho = " << length << std::endl;
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