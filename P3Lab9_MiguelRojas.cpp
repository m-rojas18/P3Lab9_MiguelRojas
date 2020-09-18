#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

void leerArchivo();

int main(){
    leerArchivo();
    return 0;
}

void leerArchivo(){
    ifstream archivo_generator;

    archivo_generator.open("generator.txt", ios::in);
    if(archivo_generator.fail()){
        cout << "Ocurrio un error al intentar abrir el archivo puede ser que no exista.\n";
        exit(EXIT_FAILURE);
    }

    vector<string> lista_datos;
    string dato_leido;
    while(!archivo_generator.eof()){
        getline(archivo_generator, dato_leido, '[');
        lista_datos.push_back(dato_leido.substr(0,dato_leido.find("]")));
    }


    /*for (int i = 0; i < lista_datos.size(); i++){
        cout << "[" << i << "] " << lista_datos.at(i) << endl;
    }*/
    int contador = 1;
    vector<string> lista_atributos;
    while(contador < lista_datos.size()){
        string linea_nombre_clase = lista_datos.at(contador).substr(lista_datos.at(contador).find("n"), lista_datos.at(contador).find("A") - 3);//Substring de linea donde esta el nombre de la clase
        string nombre_clase = linea_nombre_clase.substr(linea_nombre_clase.find(":") + 1, linea_nombre_clase.find("\n"));//Conseguir el nombre de la clase

        //Conseguir Atributos
        string cadena_atributos = lista_datos.at(contador).substr(lista_datos.at(contador).find("A"),  lista_datos.at(contador).find("]"));
        cout << cadena_atributos;
        //Poner las lineas de atributos en una lista
        for (int i = 0; i < cadena_atributos.length(); i++){
            char temporal = cadena_atributos.at(i);
            if(temporal == '\n' ){
                cout << "hola" << endl;
            }
        }
        
        
        contador++;
    }  
}