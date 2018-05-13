/*--------------------------------------------------------*/
/* apo.h                                                  */
/*                                                        */
/* clase Apo genérica: Árbol parcialmente ordenado con    */
/*    elementos de tipo T en los nodos, cuyo tamaño       */
/*    (parámetro de entrada del constructor) puede ser    */
/*    distinto para cada objeto de la clase Apo.          */
/*    Los elementos se ordenan con el operador < del tipo */
/*    T, de modo que el de cada nodo es menor que el de   */
/*    todos sus descendientes.                            */
/*--------------------------------------------------------*/

#ifndef APO_H
#define APO_H
#include <cassert>

template <typename T> class Apo {
public:
   explicit Apo(size_t maxNodos);       // constructor
   void insertar(const T& e);
   void suprimir();
   const T& cima() const;
   bool vacio() const;
   Apo(const Apo& A);                   // ctor. de copia
   Apo& operator =(const Apo& A);       // asignación de apo
   ~Apo();                              // destructor
private:
   typedef int nodo; // índice de la matriz
                     // entre 0 y maxNodos-1
   T* nodos;      // vector de nodos
   int maxNodos;  // tamaño del vector
   nodo ultimo;   // último nodo del árbol

   nodo padre(nodo i) const { return (i-1)/2; }
   nodo hIzq(nodo i)  const { return 2*i+1; }
   nodo hDer(nodo i)  const { return 2*i+2; }
   void flotar(nodo i);
   void hundir(nodo i);
};

/*--------------------------------------------------------*/
/* clase Apo genérica: Vector de posiciones relativas.    */
/*    Un Apo de n nodos se almacena en celdas             */
/*    consecutivas del vector, desde 0 hasta n-1 (ultimo).*/
/*    La raíz del APO se almacena en la celda 0 del       */
/*    vector. Al hijo izquierdo del nodo i le corresponde */
/*    la celda 2i+1 y al hijo derecho la celda 2i+2.      */
/*                                                        */
/* Implementación de operaciones                          */
/*--------------------------------------------------------*/

template <typename T>
inline Apo<T>::Apo(size_t maxNodos) :
   nodos(new T[maxNodos]),
   maxNodos(maxNodos),
   ultimo(-1)   // Apo vacío
{}

template <typename T>
inline void Apo<T>::insertar(const T& e)
{
   assert(ultimo < maxNodos-1);   // Apo no lleno
   nodos[++ultimo] = e;
   flotar(ultimo);
}

template <typename T>
inline void Apo<T>::suprimir()
{
   assert(ultimo > -1);   // Apo no vacío
   if (--ultimo > -1) {     // Apo no queda vacío.
      nodos[0] = nodos[ultimo+1];
      if (ultimo > 0)     // Quedan dos o más elementos. Reordenar
         hundir(0);
   }
}

template <typename T>
inline const T& Apo<T>::cima() const
{
   assert(ultimo > -1);   // Apo no vacío
   return nodos[0];
}

template <typename T>
inline bool Apo<T>::vacio() const
{
   return (ultimo == -1);
}

template <typename T>
inline Apo<T>::~Apo()
{
   delete[] nodos;
}

template <typename T>
Apo<T>::Apo(const Apo<T>& A) :
   nodos(new T[A.maxNodos]),
   maxNodos(A.maxNodos),
   ultimo(A.ultimo)
{
   // copiar el vector
   for (nodo n = 0; n <= ultimo; n++)
      nodos[n] = A.nodos[n];
}

template <typename T>
Apo<T>& Apo<T>::operator =(const Apo<T>& A)
{
   if (this != &A) {   // evitar autoasignación
      // Destruir el vector y crear uno nuevo si es necesario
      if (maxNodos != A.maxNodos) {
         delete[] nodos;
         maxNodos = A.maxNodos;
         nodos = new T[maxNodos];
      }
      ultimo = A.ultimo;
      // Copiar el vector
      for (nodo n = 0; n <= ultimo; n++)
         nodos[n] = A.nodos[n];
   }
   return *this;
}

// Métodos privados

template <typename T>
void Apo<T>::flotar(nodo i)
{
   T e = nodos[i];
   while (i > 0 && e < nodos[padre(i)]) {
      nodos[i] = nodos[padre(i)];
      i = padre(i);
   }
   nodos[i] = e;   // colocar e
}

template <typename T>
void Apo<T>::hundir(nodo i)
{
   bool fin = false;
   T e = nodos[i];
   while (hIzq(i) <= ultimo && !fin) {   // hundir e
      nodo hMin;   // hijo menor del nodo i
      if (hIzq(i) < ultimo && nodos[hDer(i)] < nodos[hIzq(i)])
         hMin = hDer(i);
      else
         hMin = hIzq(i);
      if (nodos[hMin] < e) { // subir el hijo menor
         nodos[i] = nodos[hMin];
         i = hMin;
      }
      else   // e <= hMin
         fin = true;
   }
   nodos[i] = e;   // colocar e
}

#endif // APO_H
