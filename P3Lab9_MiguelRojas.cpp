#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
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
        lista_datos.push_back(dato_leido);
    }


    /*for (int i = 0; i < lista_datos.size(); i++){
        cout << "[" << i << "] " << lista_datos.at(i) << endl;
    }*/
    int contador = 1;
    vector<string> lista_atributos;
    //while(contador < lista_datos.size()){

        stringstream lineas_datos(lista_datos.at(contador));

        string linea_nombre_clase;
        int contador_lineas = 1;
        //Conseguir linea de primer nombre
        while(getline(lineas_datos, linea_nombre_clase, '\n')){
            if(contador_lineas == 2){
                 break;
            }
           contador_lineas++;
        }
        string nombre_clase = linea_nombre_clase.substr(linea_nombre_clase.find(":") + 1);//Conseguir el nombre de la clase

        //Conseguir Atributos
        //Poner las lineas de texto que contienen a los atributos en una lista
        string linea_atributos;
        while(getline(lineas_datos,linea_atributos, '\n')){
            if(linea_atributos[0] != ']') {
                lista_atributos.push_back(linea_atributos);
            }
        }
        
        contador++;
    //}  
}