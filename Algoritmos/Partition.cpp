/*--------------------------------------------------------*/
/* Partition.cpp                                          */
/*                                                        */
/* Implementacion de la clase Particion:                  */
/* Bosque de arboles con union por altura y busqueda con  */
/* compresion de caminos.                                 */
/*--------------------------------------------------------*/

#include "Partition.hpp"

// El arbol con mayor altura se convierte en subarbol del otro.
void Particion::unir(int a, int b)
{
   if (padre[b] < padre[a])
      padre[a] = b;
   else {
      if (padre[a] == padre[b])
         padre[a]--; // El arbol resultante tiene un nivel mas.
      padre[b] = a;
   }
}

int Particion::encontrar(int x) const
{
   int y, raiz = x;

   while (padre[raiz] > -1)
      raiz = padre[raiz];
   // Compresion del camino de x a raiz: Los nodos
   // del camino se hacen hijos de la raiz
   while (padre[x] > -1) {
      y = padre[x];
      padre[x] = raiz;
      x = y;
   }
   return raiz;
}
