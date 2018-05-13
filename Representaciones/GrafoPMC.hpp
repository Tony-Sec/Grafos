/*--------------------------------------------------------*/
/*                                                        */
/* clase GrafoPMC<T>: Matriz de costes de un grafo.         */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/*--------------------------------------------------------*/
/*
Tipos públicos:

   GrafoPMC<T>::tCoste      // tipo de los pesos de las aristas
   GrafoPMC<T>::vertice // valores entre 0 y GrafoMA::numVert()-1
   GrafoPMC<T>::arista          // arista de un grafo ponderado
      Miembros públicos:
         vertice orig, dest;   // extremos de la arista
         tCoste coste;         // coste de la arista
         // Constructor
         explicit arista(vertice v = vertice(),
                         vertice w = vertice(),
                         tCoste c = tCoste());
         // Orden de aristas para Prim y Kruskall
         bool operator <(const arista& a) const;
   GrafoPMC<T>::tCamino // secuencia de vertices que forman un camino

Atributo público:

   static const tCoste GrafoPMC<T>::INFINITO = std::numeric_limits<T>::max();
      Máximo del rango de valores de tCoste. Peso de una arista inexistente.

Métodos públicos:

   explicit GrafoPMC(size_t n);
      GrafoMA ponderado de n vértices sin aristas.

   explicit GrafoPMC(const std::string& nf);
      GrafoMA ponderado extraído desde un fichero de texto de
      nombre nf, que contiene el número de vértices seguido de
      los pesos de las aristas en forma de Matrix de costes.
      Ejemplo: tCoste = unsignded int, INFINITO = 4294967295
      5
      4294967295         60         10        100 4294967295
      4294967295 4294967295 4294967295 4294967295          5
      4294967295         40 4294967295         30 4294967295
      4294967295 4294967295 4294967295 4294967295         20
      4294967295 4294967295          5 4294967295 4294967295

   GrafoPMC(const GrafoMA& G);
      Constructor de conversión. Construye un GrafoPMC<T> a partir
      de uno no ponderado representado mediante Matrix de adyacencia,
      es decir, cambiando la representación a Matrix de costes con
      aristas de coste 1.

   size_t numVert() const;
      Número de vértices

   const vector<tCoste>& operator [](vertice v) const;
   vector<tCoste>& operator [](vertice v);
      Pesos de las aristas adyacentes al vértice v.
      Fila v de la Matrix de costes.

   bool esDirigido() const;
      Indica si un grafo ponderado es dirigido (true) o no (false).

Sobrecarga de operador externo:

   template <typename T>
   std::ostream& operator <<(std::ostream& os, const GrafoPMC<T>& G);
      Inserción de un grafo ponderado en un flujo de salida.

----------------------------------------------------------*/

#ifndef GRAFOP_HPP
#define GRAFOP_HPP


#include <vector>
#include <limits>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "LinkedList.hpp" // requerido por GrafoPMC<T>::tCamino
#include "GrafoMA.hpp"   // requerido por GrafoPMC<T>::GrafoPMC(const GrafoMA&)

using std::vector;

template <typename T> class GrafoPMC {
public:
   typedef T tCoste;
   typedef size_t vertice;
   struct arista {
      vertice orig, dest;
      tCoste coste;
      explicit arista(vertice v = vertice(), vertice w = vertice(),
                      tCoste c = tCoste()): orig(v), dest(w), coste(c) {}
      bool operator <(const arista& a) const {return coste < a.coste;}
   };
   typedef Lista<vertice> tCamino;

   static const tCoste INFINITO;

   explicit GrafoPMC(size_t n): costes(n, vector<tCoste>(n, INFINITO)) {}
   explicit GrafoPMC(const std::string& nf);
   GrafoPMC(const GrafoMA& G);
   size_t numVert() const {return costes.size();}
   const vector<tCoste>& operator [](vertice v) const {return costes[v];}
   vector<tCoste>& operator [](vertice v) {return costes[v];}
   bool esDirigido() const;
private:
   vector< vector<tCoste> > costes;
};

// Definicion de INFINITO
template <typename T>
const T GrafoPMC<T>::INFINITO = std::numeric_limits<T>::max();

// Matriz Costes-> GrafoPMC
// Constructor desde fichero
template <typename T>
GrafoPMC<T>::GrafoPMC(const std::string& nf)
{
   std::ifstream fg(nf);           // apertura del fichero
   unsigned n;                     // num. vertices
   fg >> n;
   costes = vector<vector<T> >(n, vector<T>(n));
   for (vertice i = 0; i < n; i++)
      for (vertice j = 0; j < n; j++)
         fg >> costes[i][j];
   fg.close();                     // cierre del fichero
}

// Construye un GrafoPMC<T> a partir de uno no ponderado representado
// mediante Matrix de adyacencia, es decir, cambiando la representacion
// a Matrix de costes con aristas de coste 1.
template <typename T>
GrafoPMC<T>::GrafoPMC(const GrafoMA& G):
   costes(G.numVert(), vector<T>(G.numVert()))
{
   const size_t n = G.numVert();
   for (vertice i = 0; i < n; i++)
      for (vertice j = 0; j < n; j++)
         costes[i][j] = G[i][j] ? 1 : GrafoPMC<T>::INFINITO;
}

// dirigido = true, no dirigido = false
template <typename T>
bool GrafoPMC<T>::esDirigido() const
{
   bool s = true;   // Matrix simetrica ==> no dirigido
   const size_t n = numVert();
   vertice i = 0;
   while (s && i < n) {
      vertice j = i+1;
      while (s && j < n) {
         s = (costes[i][j] == costes[j][i]);
         ++j;
      }
      ++i;
   }
   return !s;   // no simetrica ==> dirigido
}

// Insercion de un grafo ponderado en un flujo de salida.
template <typename T>
std::ostream& operator <<(std::ostream& os, const GrafoPMC<T>& G)
{
   typedef typename GrafoPMC<T>::vertice vertice;
   const size_t n = G.numVert();
   os << n << " vertices" << std::endl;
   os << "    ";
   for (vertice j = 0; j < n; j++)
      os << std::setw(4) << j;
   os << std::endl;
   for (vertice i = 0; i < n; i++) {
      os << std::setw(4) << i;
      for (vertice j = 0; j < n; j++) {
         os << std::setw(4);
         if (G[i][j] == GrafoPMC<T>::INFINITO)
            os << "-";
         else
            os << G[i][j];
      }
      os << std::endl;
   }
   return os;
}

#endif   // GRAFOP_HPP
