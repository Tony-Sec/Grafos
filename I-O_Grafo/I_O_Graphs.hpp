/*--------------------------------------------------------*/
/* I_O_Graphs.hpp                                        */
/*                                                        */
/* Operadores de inserción en flujos de salida para       */
/* visualizar los resultados de los algoritmos de grafos  */
/* implementados en alg_grafoMA.[h|cpp] y alg_grafoPMC.h  */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/*--------------------------------------------------------*/
/*
Sobrecarga de operadores:

   template <typename T>
   ostream& operator <<(ostream& os, const vector<T>& v);
      Inserción de vector<T> en un ostream (para probar Dijkstra).

   template <typename T>
   ostream& operator << (ostream& os, const Matrix<T>& m);
      Inserción de Matrix<T> en un ostream (para probar Floyd).

   template <>
   ostream& operator << <bool>(ostream& os, const Matrix<bool>& m);
      Especialización para Matrix<bool> del operador << para la
      clase genérica Matrix<T> (para probar Warshall).

   template <>
   ostream& operator << <size_t>(ostream& os, const Lista<size_t>& L);
      Inserción de una lista de vértices (size_t) de un grafo en un
      flujo de salida (para probar recorridos y caminos de Dijkstra
      y Floyd).

----------------------------------------------------------*/

#ifndef I_O_GRAPHS_HPP
#define I_O_GRAPHS_HPP


#include "../Representaciones/GrafoPMC.hpp"  // grafo ponderado
#include <vector>
#include "../Representaciones/Matrix.hpp"    // Matrix cuadrada
#include "../Representaciones/LinkedList.hpp" // para mostrar listas de vértices
#include "../Representaciones/GrafoPLA.hpp" // para mostrar listas de vértices
#include <iostream>

using std::ostream;
using namespace std;


// Inserción de Lista<size_t> en un ostream (para probar recorridos
// y caminos de Dijkstra y Floyd))
template <typename T>
ostream& operator << (ostream& os, const Lista<T>& L) {
    typedef typename Lista<T>::posicion posicion;
    for (posicion i = L.primera(); i != L.fin(); i = L.siguiente(i))
        os << L.elemento(i) << ' ';
    return os;
}

// Pre:  M está inicializada.
// Post: Rellena la MATRIZ DE COSTES que corresponde a un GrafoP G con elementos
//       leídos segun la accesibilidad y el coste a un nodo
//       desde la entrada estándar.

template <typename T>
void Mcoste(Matrix<T>& M) {
    int cost, n1, n2;
    char d='S',q='N';
    cout << "El Grafo Es Dirigido?[S|n] : ";
    cin>>d;cin.ignore();
    cout << "A continuación se le preguntara sobre el coste de los nodos \n\n";
    cout << "Ej: 1->0,9 Manera de Introducirlo: 1 0 9 \n";
    do{
        cout << "nodo->nodo,coste : \n" ;
        cin >> n1 >> n2 >> cost;
        if(n1<M.dimension()&& n2<M.dimension()){
            M[n1][n2]=cost;
            if(d=='S') M[n2][n1]=cost;
        }else cout<< "El nodo no está en el Grafo!!!!!"<<endl;
        cout << "Desea seguir[s|N]? ";
        cin>>q;
    }while(q=='s');

}

template <typename T>
void imprimir_M(ostream& os,const Matrix<T>& m){
    const size_t n = m.dimension();
    os << n << endl;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            os << m[i][j]<< "\t";
        }
        os << endl;
    }
}


// Pre:  M está inicializada.
// Post: Rellena la LISTA DE ADYACENCIA que corresponde a un Grafo G con elementos
//       leídos segun la accesibilidad y el coste a un nodo
//       desde la entrada estándar.

template <typename T>
void Lady(vector<Lista<T>>& L) {
    int n1, n2;
    char d='S',q='N';
    string s;
    cout << "El Grafo Es Dirigido?[S|n] :";
    cin >> d;cin.ignore();
    cout << "A continuación se le preguntara sobre los nodos adyacentes: \n\n";
    do{
        cout << "Nodo? : \n";
        cin >> n1;
        if(n1<L.size()){
            cout << "Adyacentes? (Introducir separado de , ): \n";
            cin>>s;
            stringstream ss (s);
            typename Lista<T>::posicion p1= L[n1].primera();
            while(ss >> n2){
                if(n2<L.size()){
                    L[n1].insertar(n2,p1);
                    typename Lista<T>::posicion p2= L[n2].primera();
                    if(d=='S') {
                        L[n2].insertar(n1,p2);
                        p2=L[n2].siguiente(p2);
                    }
                    p1=L[n1].siguiente(p1);
                }else cout<<"El nodo no esta en el Grafo o has introducido demasiados ady.!!! \n";
                if (ss.peek() == ',')ss.ignore();
            }
            cout << "Desea seguir[s|N]? ";
            cin>>q;
        }else cout<< "El nodo no está en el Grafo!!!!!"<<endl;
    }while(q=='s');
}

// Pre:  M está inicializada.
// Post: Rellena la LISTA DE ADYACENCIA que corresponde a un Grafo PONDERADO G  con elementos
//       leídos segun la accesibilidad y el coste a un nodo
//       desde la entrada estándar.

template <typename T>
void LadyP(vector<Lista<T>>& L) {
    int n1, n2 ,c;
    char d='S',q='N';
    string s;
    cout << "El Grafo Es Dirigido?[S|n] :";
    cin >> d;cin.ignore();
    cout << "A continuación se le preguntara sobre los nodos adyacentes: \n\n";
    do{
        cout << "Nodo? : \n";
        cin >> n1;
        if(n1<L.size()){
            cout << "Adyacentes? (Introducir separado de , ): \n";
            cin>>s;
            stringstream ss (s);
            while(ss >> n2 ){
                ss.ignore();
                ss >> c;
                if(n2<L.size()){
                    L[n1].insertar(n2,L[n1].fin());
                    L[n1].insertar(c,L[n1].fin());
                    if(d=='S') {
                        L[n2].insertar(n1,L[n2].fin());
                        L[n2].insertar(c,L[n2].fin());
                    }
                }else cout<<"El nodo no esta en el Grafo o has introducido demasiados ady.!!! \n";
                if (ss.peek() == ',')ss.ignore();
            }
            cout << "Desea seguir[s|N]? ";
            cin>>q;
        }else cout<< "El nodo no está en el Grafo!!!!!"<<endl;
    }while(q=='s');
}

template <typename T>
void imprimir_L(ostream& os,vector<Lista<T>>& V){
    int i=0;
    const size_t n = V.size();
    os << n << endl;
    for (auto& lista : V) {
        os<<i<<": "<<lista;
        i++;
        os << endl;
    }
}
/**********************************************************************************************************************/
//Vector distancia:  0 10 50 30 60
//Vector precedencia:0 0  3  0  2

// Inserción de vector<T> en un ostream (para probar Dijkstra)
template <typename T>
ostream& operator <<(ostream& os, const vector<T>& v)
{
   for (size_t i = 0; i < v.size(); i++) {
      os << std::setw(4);
      if (v[i] != GrafoPMC<T>::INFINITO)
         os << v[i];
      else
         os << "-";
   }
   return os;
}


/**********************************************************************************************************************/
/*Matriz de Costes:
* 0     1    6     3    inf
* inf   0    3    inf     4
* inf   3    0    inf    -3
* -2   inf   3     0    inf
* inf   4    inf   4     0
*/
// Inserta una Matrix<T> en un flujo de salida (para probar Floyd)
template <typename T>
ostream& operator << (ostream& os, const Matrix<T>& m)
{
   const size_t n = m.dimension();
   os << "    ";
   for (size_t j = 0; j < n; ++j)
      os << std::setw(4) << j;
   os << std::endl;
   for (size_t i = 0; i < n; ++i) {
      os << std::setw(4) << i;
      for (size_t j = 0; j < n; ++j) {
         os << std::setw(4);
         if (m[i][j] == GrafoPMC<T>::INFINITO)
            os << "-";
         else
            os << m[i][j];
      }
      os << std::endl;
   }
   return os;
}

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
ostream& operator << <bool>(ostream& os, const Matrix<bool>& m);


#endif   // I_O_GRAPHS_HPP
