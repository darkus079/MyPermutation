#include "Permutation.h"

using std::cin;
using std::cout;

int main() {
    Permutation a;
    cin >> a;

    Permutation tmp(a);
    cout << tmp.getLexNumber() << ": " << tmp;

    while(tmp.next() != tmp) {
        cout << tmp.getLexNumber() << ": " << ++tmp;
    }

    cout << tmp.getLexNumber() << ": " << tmp;

    while(tmp.previous() != tmp) {
        cout << tmp.getLexNumber() << ": " << --tmp;
    }

    int count = 5;
    cout << "a + " << count << " = " << (a + count).getLexNumber() << ": " << a + count;
    cout << "a - " << count << " = " << (a - count).getLexNumber() << ": " << a - count;

    a += 2 * count;
    cout << "(a += " << 2 * count << ") a = " << a.getLexNumber() << ": " << a;
    a -= count;
    cout << "(a -= " << count << ") a = " << a.getLexNumber() << ": " << a;
    a -= count;
    cout << "next(a) = " << a.next().getLexNumber() << ": " << a.next();
    cout << "previous(a) = " << a.previous().getLexNumber() << ": " << a.previous();

    Permutation b;
    cin >> b;

    cout << "b = " << b.getLexNumber() << ": " << b;
    cout << "a = " << a.getLexNumber() << ": " << a;

    try {
        cout << "a * b = " << (a * b).getLexNumber() << ": " << a * b;
    }
    catch(const char* errorMessage) {
        cout << errorMessage << '\n';
    }

    cout << "a < b: " << (a < b) << '\n';
    cout << "a > b: " << (a > b) << '\n';
    cout << "a <= b: " << (a <= b) << '\n';
    cout << "a >= b: " << (a >= b) << '\n';
    cout << "a == b: " << (a == b) << '\n';
    cout << "a != b: " << (a != b) << '\n';
}