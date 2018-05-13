/*--------------------------------------------------------*/
/* grafoLA.h                                              */
/*                                                        */
/* clase GrafoLA: Listas de adyacencia de un grafo.         */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* �2016 Jos� Fidel Argudo                                */
/*--------------------------------------------------------*/
/*
Tipo p�blico:

   GrafoLA::vertice // un valor entre 0 y GrafoLA::numVert()-1

M�todos p�blicos:

   explicit GrafoLA(size_t n);
      GrafoLA de n v�rtices sin aristas.

   explicit GrafoLA(const std::string& nf);
      GrafoLA extra�do desde un fichero de texto de nombre nf,
      que contiene el n�mero de v�rtices seguido en cada l�nea
      de un v�rtice, el car�cter ':' y la lista de sus adyacentes
      separados por espacios.
      Ejemplo:
      5
      0: 1 2 3
      1: 4
      2: 1 3
      3: 4
      4: 2

   size_t numVert() const;
      N�mero de v�rtices

   const Lista<vertice>& adyacentes(vertice v) const;
   Lista<vertice>& adyacentes(vertice v);
      V�rtices adyacentes a v.

Sobrecarga de operador externo:

   std::ostream& operator <<(std::ostream& os, const GrafoLA& G);
      Inserci�n de un GrafoLA en un flujo de salida.

----------------------------------------------------------*/

#ifndef GRAFO_LIS_ADY_H
#define GRAFO_LIS_ADY_H
#include <vector>
#include <iostream>
#include <string>
#include "LinkedList.hpp"

class GrafoLA {
public:
   typedef size_t vertice;

   explicit GrafoLA(size_t n): ady(n) {}
   explicit GrafoLA(const std::string& nf);
   size_t numVert() const {return ady.size();}
   const Lista<vertice>& adyacentes(vertice v) const {return ady[v];}
   Lista<vertice>& adyacentes(vertice v) {return ady[v];}
private:
   std::vector< Lista<vertice> > ady; // vector de listas de v�rtices
};

// Inserci�n de un grafo en un flujo de salida.
std::ostream& operator <<(std::ostream& os, const GrafoLA& G);

#endif   // GRAFO_LIS_ADY_H
