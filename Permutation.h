#pragma once
#include "BigInteger.h"
#include <iostream>

class Permutation {
private:
    unsigned int _sz;
    unsigned int* _p;
    void swap(Permutation& a, Permutation& b);
    void swap(unsigned int& a, unsigned int& b);
    unsigned int min(unsigned int a, unsigned int b) const;
    BigInteger fact(unsigned int n) const;

public:
    Permutation(unsigned int sz = 1);
    Permutation(unsigned int sz, unsigned int* p);
    Permutation(unsigned int sz, BigInteger num);
    Permutation(const Permutation& b);
    ~Permutation();
    Permutation next() const;
    Permutation previous() const;
    Permutation operator*(const Permutation& b) const;
    Permutation& operator++();
    Permutation operator++(int);
    Permutation& operator--();
    Permutation operator--(int);
    bool operator<(const Permutation& b) const;
    bool operator<=(const Permutation& b) const;
    bool operator>(const Permutation& b) const;
    bool operator>=(const Permutation& b) const;
    bool operator==(const Permutation& b) const;
    bool operator!=(const Permutation& b) const;
    BigInteger getLexNumber() const;
    void operator+=(int count);
    void operator-=(int count);
    Permutation operator+(int count);
    Permutation operator-(int count);
    Permutation& operator=(Permutation b);
    unsigned int getSize();
    unsigned int getElem(unsigned int ind);
    void setSize(unsigned int size);
    void setElem(unsigned int ind, unsigned int elem);
};

std::istream& operator>>(std::istream& in, Permutation& p);
std::ostream& operator<<(std::ostream& out, Permutation p);