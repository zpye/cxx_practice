#ifndef CXX_PRACTICE_LAZY_EVALUATION_H
#define CXX_PRACTICE_LAZY_EVALUATION_H

#include <cstdio>

class Vec;

class BinaryAddExp
{
public:
    BinaryAddExp(const Vec& _lvec, const Vec& _rvec) 
        : lvec(_lvec), rvec(_rvec) {}

    const Vec& lvec;
    const Vec& rvec;
};

inline BinaryAddExp operator+(const Vec& lvec, const Vec& rvec)
{
    return BinaryAddExp(lvec, rvec);
}

class Vec
{
public:
    Vec() : dp(nullptr), len(0) {}
    Vec(float* _dp, size_t _len) 
        : dp(_dp), len(_len) {}

    inline Vec& operator=(const BinaryAddExp& exp)
    {
        for(size_t i = 0; i < len; ++i)
        {
            dp[i] = exp.lvec.dp[i] + exp.rvec.dp[i];
        }
        return *this;
    }

public:
    float* dp;
    size_t len;
};

#endif // CXX_PRACTICE_LAZY_EVALUATION_H