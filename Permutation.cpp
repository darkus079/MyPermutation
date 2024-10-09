#include "Permutation.h"

void Permutation::swap(Permutation& a,Permutation& b)
{
    swap(a._sz, b._sz);

    unsigned int* tmp = a._p;
    a._p = b._p;
    b._p = tmp;
}

void Permutation::swap(unsigned int & a,unsigned int & b)
{
    unsigned int tmp = a;
    a = b;
    b = tmp;
}

unsigned int Permutation::min(unsigned int a,unsigned int b) const
{
    return (a < b ? a : b);
}

BigInteger Permutation::fact(unsigned int n) const
{
    BigInteger res = 1;

    for (unsigned int i = 2; i <= n; ++i) {
        res *= (BigInteger)i;
    }

    return res;
}

Permutation::Permutation(unsigned int sz)
{
    _p = new unsigned int[_sz = sz];

    for (unsigned int i = 0; i < _sz; ++i) {
        _p[i] = i;
    }
}

Permutation::Permutation(unsigned int sz, unsigned int* p)
{
    _p = new unsigned int[_sz = sz];

    for (unsigned int i = 0; i < _sz; ++i) {
        _p[i] = p[i];
    }
}

Permutation::Permutation(unsigned int sz, BigInteger num)
{
    if (fact(sz) < num) {
        num = fact(sz);
    }

    if (num <= 0) {
        num = 1;
    }

    --num;
    _p = new unsigned int[_sz = sz];
    bool* was = new bool[_sz];

    for (unsigned int i = 0; i < _sz; ++i) {
        was[i] = false;
    }

    for (unsigned int i = 0; i < _sz; ++i) {
        BigInteger busy = num / fact(_sz - i - 1);
        num %= fact(_sz - i - 1);
        unsigned int cnt = 0;

        for (unsigned int j = 0; j < _sz; ++j) {
            if (!was[j]) {
                ++cnt;

                if (cnt == busy + 1) {
                    _p[i] = j;
                    was[j] = true;
                }
            }
        }
    }

    delete[] was;
}

Permutation::Permutation(const Permutation& b)
{
    _p = new unsigned int[_sz = b._sz];

    for (unsigned int i = 0; i < _sz; ++i) {
        _p[i] = b._p[i];
    }
}

Permutation::~Permutation()
{
    delete[] _p;
}

Permutation Permutation::next() const
{
    Permutation tmp = (*this);
    ++tmp;
    return tmp;
}

Permutation Permutation::previous() const
{
    Permutation tmp = (*this);
    --tmp;
    return tmp;
}

Permutation Permutation::operator*(const Permutation& b) const
{
    if (_sz != b._sz) {
        throw "Permutations of different lengths";
    }

    Permutation res(_sz);

    for (unsigned int i = 0; i < _sz; ++i) {
        res._p[i] = b._p[_p[i]];
    }

    return res;
}

Permutation& Permutation::operator++()
{
    unsigned int ind = _sz - 1;

    while (ind > 0 && _p[ind] < _p[ind - 1]) {
        --ind;
    }

    if (ind > 0) {
        unsigned int ind2 = _sz - 1;

        while (ind2 >= ind && _p[ind2] < _p[ind - 1]) {
            --ind2;
        }

        swap(_p[ind2], _p[ind - 1]);

        for (unsigned int i = ind; i < (ind + _sz) / 2; ++i) {
            swap(_p[i], _p[_sz - i + ind - 1]);
        }
    }

    return (*this);
}

Permutation Permutation::operator++(int)
{
    Permutation tmp = (*this);
    ++(*this);
    return tmp;
}

Permutation& Permutation::operator--()
{
    unsigned int ind = _sz - 1;

    while (ind > 0 && _p[ind] > _p[ind - 1]) {
        --ind;
    }

    if (ind > 0) {
        unsigned int ind2 = _sz - 1;

        while (ind2 >= ind && _p[ind2] > _p[ind - 1]) {
            --ind2;
        }

        swap(_p[ind2], _p[ind - 1]);

        for (unsigned int i = ind; i < (ind + _sz) / 2; ++i) {
            swap(_p[i], _p[_sz - i + ind - 1]);
        }
    }

    return (*this);
}

Permutation Permutation::operator--(int)
{
    Permutation tmp = (*this);
    --(*this);
    return tmp;
}

bool Permutation::operator<(const Permutation& b) const
{
    unsigned int ind = 0;

    for (; ind < min(_sz, b._sz) && _p[ind] == b._p[ind]; ++ind) { }

    if (ind == b._sz) {
        return false;
    }

    if (ind == _sz) {
        return true;
    }

    return _p[ind] < b._p[ind];
}

bool Permutation::operator<=(const Permutation& b) const
{
    return (*this) < b || (*this) == b;
}

bool Permutation::operator>(const Permutation& b) const
{
    return b < (*this);
}

bool Permutation::operator>=(const Permutation& b) const
{
    return b <= (*this);
}

bool Permutation::operator==(const Permutation& b) const
{
    return !((*this) < b) && !(b < (*this));
}

bool Permutation::operator!=(const Permutation& b) const
{
    return !((*this) == b);
}

BigInteger Permutation::getLexNumber() const
{
    BigInteger res = 1;
    bool* used = new bool[_sz];

    for (unsigned int i = 0; i < _sz; ++i) {
        used[i] = false;
    }

    for (unsigned int i = 0; i < _sz - 1; ++i) {
        unsigned int cnt = 0;

        for (unsigned int j = 0; j < _p[i]; ++j) {
            if (!used[j]) {
                ++cnt;
            }
        }

        res += (BigInteger)cnt * fact(_sz - i - 1);
        used[_p[i]] = true;
    }

    delete[] used;
    return res;
}

void Permutation::operator+=(int count)
{
    (*this) = (*this) + count;
}

void Permutation::operator-=(int count)
{
    (*this) = (*this) - count;
}

Permutation Permutation::operator+(int count)
{
    BigInteger num = this->getLexNumber() + count;

    if (fact(_sz) < num) {
        num = fact(_sz);
    }

    if (num <= 0) {
        num = 1;
    }

    Permutation res(_sz, num);
    return res;
}

Permutation Permutation::operator-(int count)
{
    BigInteger num = this->getLexNumber() - count;

    if (fact(_sz) < num) {
        num = fact(_sz);
    }

    if (num <= 0) {
        num = 1;
    }

    Permutation res(_sz, num);
    return res;
}

Permutation& Permutation::operator=(Permutation b)
{
    swap(*this, b);
    return *this;
}

unsigned int Permutation::getSize()
{
    return this->_sz;
}

unsigned int Permutation::getElem(unsigned int ind)
{
    if (ind >= _sz) {
        throw "Array index out of range";
    }

    return this->_p[ind];
}

void Permutation::setSize(unsigned int sz)
{
    delete[] _p;
    _p = new unsigned int[_sz = sz];
}

void Permutation::setElem(unsigned int ind, unsigned int elem)
{
    if (ind >= _sz) {
        throw "Array index out of range";
    }

    _p[ind] = elem;
}

std::istream& operator>>(std::istream& in, Permutation & p)
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Введите размер перестановки: ";
    unsigned int sz;
    std::cin >> sz;
    p.setSize(sz);

    std::cout << "Введите перестановку из " << sz << " элементов: ";

    for (unsigned int i = 0; i < p.getSize(); ++i) {
        unsigned int elem;
        std::cin >> elem;
        p.setElem(i, elem);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, Permutation p)
{
    for (unsigned int i = 0; i < p.getSize(); ++i) {
        std::cout << p.getElem(i) << ' ';
    }

    std::cout << '\n';

    return out;
}