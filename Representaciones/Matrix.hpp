#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <vector>

using std::vector;

// Matriz cuadrada
template <typename T> class Matrix {
public:
   Matrix() {}
   explicit Matrix(size_t n, const T& x = T()): m(n, vector<T>(n, x)) {}
   size_t dimension() const {return m.size();}
   const vector<T>& operator [](size_t i) const {return m[i];}
   vector<T>& operator [](size_t i) {return m[i];}
private:
   vector< vector<T> > m;
};

#endif  // MATRIZ_HPP
