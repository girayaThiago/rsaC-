#ifndef MR_H
#define MR_H

typedef unsigned int int1024;

class MillerRabin {
public:

    bool test(int1024 k, int1024 n);
    void calc_R_D(int1024 n, int1024* r, int1024* d);
    int1024 power(int1024 a, int1024 d, int1024 n);
};

#endif