/*--------------------------------------------------------*/
/* GrafoMA.hpp                                              */
/*                                                        */
/* clase GrafoMA: Matriz de adyacencia de un grafo.         */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/*--------------------------------------------------------*/
/*
Tipo publico:

   GrafoMA::vertice // un valor entre 0 y GrafoMA::numVert()-1

Metodos publicos:

   explicit GrafoMA(size_t n);
      GrafoMA de n vertices sin aristas.

   explicit GrafoMA(const std::string& nf);
      GrafoMA extraido desde un fichero de texto de nombre nf,
      que contiene el numero de vertices seguido en cada linea
      de un vertice, el caracter ':' y la lista de sus adyacentes
      separados por espacios.
      Ejemplo:
      5
      0: 1 2 3
      1: 4
      2: 1 3
      3: 4
      4: 2

   template <typename T> GrafoMA(const GrafoPMC<T>& G);
      Constructor de conversi�n. Construye un GrafoMA a partir
      de uno ponderado representado mediante Matrix de costes,
      es decir, cambiando la representaci�n a Matrix de adyacencia.

   size_t numVert() const;
      Numero de vertices

   const vector<bool>& operator [](vertice v) const;
   vector<bool>& operator [](vertice v);
      Vertices adyacentes a v. Fila v de la Matrix de adyacencia.

   bool esDirigido() const;
      Indica si un grafo es dirigido (true) o no (false).

Sobrecarga de operador externo:

   std::ostream& operator <<(std::ostream& os, const GrafoMA& G);
      Insercion de un GrafoMA en un flujo de salida.

----------------------------------------------------------*/

#ifndef GRAFO_HPP
#define GRAFO_HPP


#include <vector>
#include <ostream>
#include <string>


using std::vector;

template <typename tCoste> class GrafoPMC;

class GrafoMA {
public:
   typedef size_t vertice;

   explicit GrafoMA(size_t n): ady(n, vector<bool>(n, false)) {}
   explicit GrafoMA(const std::string& nf);
   template <typename T> GrafoMA(const GrafoPMC<T>& G);
   size_t numVert() const {return ady.size();}
   const vector<bool>& operator [](vertice v) const {return ady[v];}
   vector<bool>& operator [](vertice v) {return ady[v];}
   bool esDirigido() const;
private:
   vector< vector<bool> > ady;
};

// Construye un GrafoMA a partir de uno ponderado representado
// mediante Matrix de costes, es decir, cambiando la representacion
// a Matrix de adyacencia.
template <typename T> GrafoMA::GrafoMA(const GrafoPMC<T>& G):
   ady(G.numVert(), vector<bool>(G.numVert()))
{
   const size_t n = G.numVert();
   for (vertice i = 0; i < n; i++)
      for (vertice j = 0; j < n; j++)
         ady[i][j] = (G[i][j] != GrafoPMC<T>::INFINITO);
}

// Insercion de un GrafoMA en un flujo de salida.
std::ostream& operator <<(std::ostream& os, const GrafoMA& G);

//#include "GrafoMA.cpp"
#endif   // GRAFO_HPP
