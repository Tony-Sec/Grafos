/*--------------------------------------------------------*/
/* grafoPLA.hpp                                             */
/*                                                        */
/* clase GrafoPLA<T>: Listas de adyacencia de un grafo      */
/*                  ponderado.                            */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* �2016 Jos� Fidel Argudo                                */
/*--------------------------------------------------------*/
/*
Tipos p�blicos:

   GrafoPLA<T>::tCoste            // tipo de los pesos de las aristas
   GrafoPLA<T>::vertice       // valores entre 0 y Grafo::numVert()-1
   GrafoPLA<T>::tCamino // secuencia de v�rtices que forman un camino
   GrafoPLA<T>::vertice_coste            // v�rtice adyacente y coste
      Miembros p�blicos:
         vertice v;
         tCoste c;
         // Comparaci�n
         bool operator ==(const vertice_coste& vc) const;

Atributo p�blico:

   static const tCoste GrafoPLA<T>::INFINITO = std::numeric_limits<T>::max();
      Maximo del rango de valores de tCoste. Peso de una arista inexistente.

Metodos publicos:

   explicit GrafoPLA(size_t n);
      Grafo ponderado de n vertices sin aristas.

   explicit GrafoPLA(const std::string& nf);
      Grafo ponderado extraido desde un fichero de texto de nombre
      nf, que contiene el numero de vertices seguido en cada linea
      de un vertice, el caracter ':' y la lista de sus adyacentes
      junto a los costes asociados, separado todo ello por espacios.
      Ejemplo:
      5
      0: 1 60 2 10 3 100
      1: 4 5
      2: 1 40 3 30
      3: 4 20
      4: 2 5

   size_t numVert() const;
      Numero de vertices

   const Lista<vertice_coste>& adyacentes(vertice v) const;
   Lista<vertice_coste>& adyacentes(vertice v);
      Vertices adyacentes a v junto a pesos de las aristas.

Sobrecarga de operador externo:

   template <typename T>
   std::ostream& operator <<(std::ostream& os, const GrafoPLA<T>& G);
      Insercion de un grafo ponderado en un flujo de salida.

----------------------------------------------------------*/

#ifndef GRAFO_PON_LIS_ADY_H
#define GRAFO_PON_LIS_ADY_H
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include <ostream>
#include "LinkedList.hpp"

using std::vector;

template <typename T> class GrafoPLA {
public:
   typedef T tCoste;
   typedef size_t vertice;
   typedef Lista<vertice> tCamino;

   struct vertice_coste {
      vertice v;
      tCoste c;
      // requerido por Lista<vertice_coste>::buscar()
      bool operator ==(const vertice_coste& vc) const {return v == vc.v;}
      vertice_coste():v (vertice{}),c(tCoste{}){}
   };

   static const tCoste INFINITO;

   GrafoPLA(size_t n): ady(n) {}
   GrafoPLA(const std::string& nf);
   size_t numVert() const {return ady.size();}
   const Lista<vertice_coste>& adyacentes(vertice v) const {return ady[v];}
   Lista<vertice_coste>& adyacentes(vertice v) {return ady[v];}
private:
   vector< Lista<vertice_coste> > ady;
};

// Definici�n de INFINITO
template <typename T>
const T GrafoPLA<T>::INFINITO = std::numeric_limits<T>::max();

// Lista ady->GrafoPLA
// Constructor desde fichero
template <typename T>
GrafoPLA<T>::GrafoPLA(const std::string& nf)
{
   char c;
   std::string cad;
   vertice v, w;
   tCoste p;
   vertice_coste vc;
   std::ifstream fg(nf);           // apertura del fichero
   unsigned n;                     // num. vertices

   fg >> n;
   ady = vector< Lista<vertice_coste> >(n);
   while (fg >> v) {
      fg >> c; // extrae ':'
      std::getline(fg, cad);
      std::istringstream ss(cad);
      while (ss >> vc.v && ss >> vc.c)
         ady[v].insertar(vc, ady[v].fin());
   }
   fg.close();                     // cierre del fichero
}

// Inserci�n de un grafo ponderado en un flujo de salida.
template <typename T>
std::ostream& operator <<(std::ostream& os, const GrafoPLA<T>& G)
{
   typedef typename GrafoPLA<T>::vertice vertice;
   typedef typename Lista<typename GrafoPLA<T>::vertice_coste>::posicion posicion;
   const size_t n = G.numVert();
   os << n << " vertices" << std::endl;
   for (vertice i = 0; i < n; i++)
      if (G.adyacentes(i).primera() != G.adyacentes(i).fin()) {
         os << i << ':';
         for (posicion p = G.adyacentes(i).primera();
              p != G.adyacentes(i).fin();
              p = G.adyacentes(i).siguiente(p))
            os << ' ' << G.adyacentes(i).elemento(p).v
               << ' ' << G.adyacentes(i).elemento(p).c;
         os << std::endl;
      }
   return os;
}

#endif   // GRAFO_PON_LIS_ADY_H
