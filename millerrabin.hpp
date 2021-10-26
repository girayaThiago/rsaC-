#ifndef MR_H
#define MR_H

#include "include.hpp"



class MillerRabin {
public:
    static bool test(int1024 k, int1024 n);
    static void calc_R_D(int1024 n, int1024* r, int1024* d);
    static int1024 power(int1024 a, int1024 d, int1024 n);
};

#endif