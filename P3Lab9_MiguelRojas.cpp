#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

void leerArchivo();

int main(){
    leerArchivo();
    return 0;
}

void leerArchivo(){
    ifstream archivo_generator;

    if(archivo_generator.fail()){
        cout << "Ocurrio un error al intentar abrir el archivo puede ser que no exista.\n";
        exit(EXIT_FAILURE);
    }

    cout << "hola";

}