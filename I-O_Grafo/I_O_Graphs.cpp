/*--------------------------------------------------------*/
/* I_O_Graphs.cpp                                         */
/*                                                        */
/* Implementación de operadores de inserción en flujos de */
/* salida para visualizar los resultados de los           */
/* algoritmos de grafos implementados en                  */
/* Grafo.[hpp|cpp] y GrafoP.hpp                           */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/*--------------------------------------------------------*/

#include "I_O_Graphs.hpp"
#include <iomanip>           // std::setw

/**********************************************************************************************************************/
/*Matriz de adyacencia:              Matriz de acceso:
* 0     1    0     0    1            1     1    1     0    1
* 1     1    0     0    1            0     1    0     0    1
* 0     0    0     0    1            0     1    1     1    1
* 0     0    1     1    1            0     1    1     1    1
* 0     0    0     1    1            0     1    1     1    1
*/
// Inserción de Matrix<bool> en un flujo de salida (para probar Warshall)
template <>
ostream& operator << <bool>(ostream& os, const Matrix<bool>& m)
{
   const size_t n = m.dimension();
   os << "   ";
   for (size_t j = 0; j < n; ++j)
      os << std::setw(3) << j;
   os << std::endl;
   for (size_t i = 0; i < n; ++i) {
      os << std::setw(3) << i;
      for (size_t j = 0; j < n; ++j)
         os << std::setw(3) << m[i][j];
      os << std::endl;
   }
   return os;
}
