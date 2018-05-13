#include <iostream>
#include "I_O_Graphs.hpp"

using namespace std;

int main() {

/********************************************************Guardar Lista de Adyacencia en graph-Lady.dat***************************************/

    cout << "Introducir Lista --> graph-Lady.dat" << endl;
    vector<Lista<int>> Lady_(3,Lista<int>{});
    Lady(Lady_);                               // Desde std::cin
    ofstream fs("graph-Lady.dat");            // Abrir fichero de salida.
    imprimir_L(fs,Lady_);                     // En fichero.
    int i=0;                                  //Mostrar matriz en salida estandar
    for(auto& elem: Lady_) {
        cout<<i<<" :"<<elem<<endl;
        i++;
    }
    fs.close();

/********************************************************Leer Lista de Adyacencia de graph-Lady.dat***************************************/

    cout << "graph-Lady.dat --> Guardar Lista" << endl;
    GrafoMA<int> g("graph-Lady.dat");         //Constructor desde fichero
    cout << g;                           //Mostrar grafo en salida estandar
    cout << "\n*** Lista de adyacencia en Grafo ***\n";

/********************************************************Guardar Lista de Adyacencia ponderada en graph-LadyP.dat***************************************/

    cout << "Introducir Lista ponderada --> graph-LadyP.dat" << endl;
    vector<Lista<int>> LadyP_(5,Lista<int>{});
    LadyP(LadyP_);                               // Desde std::cin
    ofstream fs("graph-LadyP.dat");             // Abrir fichero de salida.
    imprimir_L(fs,LadyP_);                      // En fichero.
    int i=0;                                  //Mostrar Lista en salida estandar
    for(auto& elem: LadyP_) {
        cout<<i<<": "<<elem <<endl;
        i++;
    }
    fs.close();

/********************************************************Leer Lista de Adyacencia de ponderada graph-LadyP.dat***************************************/

    cout << "graph-LadyP.dat --> Guardar Lista" << endl;
    GrafoPLA<int> gla("graph-LadyP.dat");         //Constructor desde fichero
    cout << gla;                           //Mostrar grafo en salida estandar
    cout << "\n*** Lista de adyacencia pondera en Grafo Ponderado ***\n";

/********************************************************Guardar Matriz de Costes en graph-Mcost.dat***************************************/

    cout << "Introducir Matriz --> graph-Mcost.dat" << endl;
    matriz<int> Mcoste_(2,numeric_limits<int>::max());
    Mcoste(Mcoste_);                    // Desde std::cin
    ofstream fs("graph-Mcost.dat");           // Abrir fichero de salida.
    imprimir_M(fs,Mcoste_);             // En fichero.
    cout<<Mcoste_;                       //Mostrar matriz en salida estandar
    fs.close();

/********************************************************Leer Matriz de Costes de graph-Mcost.dat***************************************/

    cout << "graph-Mcost.dat --> Guardar GrafoP" << endl;
    GrafoPMC<int> gp("graph-Mcost.dat");          //Constructor desde fichero
    cout<<gp;                                   //Mostrar grafo en salida estandar
    cout << "\n*** Matriz de costes en Grafo Ponderado ***\n";

    return 0;
}
