#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

void leerArchivo();
void crearArchivoH(string, vector<string>,vector<string>);
void crearArchivoCPP(string, vector<string>, vector<string>);

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

    int contador = 1;
    vector<string> lista_atributos;
    //while(contador < lista_datos.size()){

        stringstream lineas_datos(lista_datos.at(contador));//Utilizado para iterar por linea y conseguir los datos
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

        string cadena_atributo,tipo_atributo;
        vector<string> nombre_atributos;
        //Conseguir los tipos de los atributos de la clase y los nombres de los atributos
        for (int i = 0; i < lista_atributos.size(); i++){
            if(i != lista_atributos.size()){//Excluye el error de la linea en blanco
                cadena_atributo = lista_atributos.at(i).substr(lista_atributos.at(i).find(":") + 1);
                nombre_atributos.push_back(cadena_atributo.substr(cadena_atributo.find("|") + 1));//Agregar nombre a lista de nombres de atributo
            }
            for (int j = 0; j < cadena_atributo.length(); j++){
                tipo_atributo += cadena_atributo[j];//Conseguir cadena de los tipos de atributo
                if(cadena_atributo[j] == '|')
                    break;
            }
        }

        vector<string> lista_tipos_atributos;
        stringstream separarTipos(tipo_atributo);
        string cadena_temporal;
        while(getline(separarTipos,cadena_temporal,'|'))
            lista_tipos_atributos.push_back(cadena_temporal);

        //Creacion de Archivos
        crearArchivoH(nombre_clase, lista_tipos_atributos, nombre_atributos);
        crearArchivoCPP(nombre_clase, lista_tipos_atributos, nombre_atributos);
        contador++;
    //}  
}

void crearArchivoH(string nombre_clase, vector<string> lista_tipos_atributos, vector<string> lista_nombres_atributos){

    //Crear Archivo .h
    string copia_nombre_clase = nombre_clase;

    ofstream archivoH;
    archivoH.open(nombre_clase + ".h", ios::out);//Creacion de Archivo
    
    if(archivoH.fail())
        cout << "Ocurrio un error y no se pudo crear el archivo .h\n";
    
    transform(nombre_clase.begin(), nombre_clase.end(), nombre_clase.begin(), ::toupper);
    archivoH << "\n"//Ifndef/define
        << "#ifndef " << nombre_clase << "_H\n"
        << "#define " << nombre_clase << "_H\n\n"
        << "#include <string>\n\n" << 
        "using namespace std;\n\n";    

    //Clase
    archivoH << "class " << copia_nombre_clase << "{\n"
        << "    private:\n";
    
    int cantidad_atributos = lista_nombres_atributos.size() - 1;//Numero de atributos

    string salida_atributos;
    for (int i = 0; i < cantidad_atributos; i++)//*Ambas listat tienen el mismo tamaño
        salida_atributos += "       " + lista_tipos_atributos.at(i) + " " + lista_nombres_atributos.at(i) + ";\n";

    //Constructores
    archivoH << salida_atributos
        << "public:\n"
        << "       " << copia_nombre_clase << "();\n";

    string salida_constructor = "(";
    for (int i = 0; i < cantidad_atributos; i++){
        if(i == cantidad_atributos - 1){
            salida_constructor += lista_tipos_atributos.at(i) + ");\n";
        } else {
            salida_constructor += lista_tipos_atributos.at(i) + ",";
        }
    }

    //Escribir constructor lleno en archivo .h
    archivoH << "       " << copia_nombre_clase << salida_constructor;

    //Escribir getters y setters para los atributos
    string salida_getters_setters;

    string salida_setters;
    for (int i = 0; i < cantidad_atributos; i++)
        salida_setters += "       void set_" + lista_nombres_atributos.at(i) + "(" + lista_tipos_atributos.at(i) + ");\n";
    

    string salida_getters;
    for (int i = 0; i < cantidad_atributos; i++)
        salida_getters += "       " + lista_tipos_atributos.at(i) +" get_" + lista_nombres_atributos.at(i) + "();\n";

    salida_getters_setters = salida_setters + salida_getters;

    archivoH << salida_getters_setters;//Escribir getters y setters en el archivo .h
    //Ultima Seccion del Archivo
    archivoH << "       string toString();\n"
             << "       ~" << copia_nombre_clase << "();\n"
             << "};\n\n"
             << "#endif";
    archivoH.close();
}

void crearArchivoCPP(string nombre_clase, vector<string>lista_tipos_atributos, vector<string> lista_nombre_atributos){

    ofstream archivoCPP;
    archivoCPP.open(nombre_clase + ".cpp", ios::out);//Creacion de Archivo

    if(archivoCPP.fail())
        cout << "Ocurrio un error y no se pudo crear el archivo .h\n";
    

    string include_h = '"' + nombre_clase + ".h" + '"';
    archivoCPP << "\n"
               << "#include" << include_h << "\n\n"
               << nombre_clase << "::" << nombre_clase << "(){\n}\n\n";

    string salida_constructor_cargado = "(";
    string salida_metodo_constructor;
    int cantidad_atributos = lista_nombre_atributos.size() - 1;
    //Salida de constructor cargado y //Salida adentro de constructor
    for (int i = 0; i < cantidad_atributos; i++){
        if(i == cantidad_atributos - 1){
            salida_constructor_cargado += lista_tipos_atributos.at(i) + " _" + lista_nombre_atributos.at(i) + "){";
            salida_metodo_constructor += "  " + lista_nombre_atributos.at(i) + " = " + " _" + lista_nombre_atributos.at(i) + ";\n";
        } else {
            salida_constructor_cargado += lista_tipos_atributos.at(i) + " _" + lista_nombre_atributos.at(i) + ", ";
            salida_metodo_constructor += "  " + lista_nombre_atributos.at(i) + " = " + " _" + lista_nombre_atributos.at(i) + ";\n";
        }
    }

   //Escribir constructor cargado
   archivoCPP << nombre_clase << "::" << nombre_clase << salida_constructor_cargado << "\n"
              << salida_metodo_constructor << "}\n\n";

    //Escribir metodos getters y setters
    string salida_getters_setters, salida_getters, salida_setters;
    for (int i = 0; i < cantidad_atributos; i++){
        //Setters
        salida_setters += "void " + nombre_clase + "::" + "set_" + lista_nombre_atributos.at(i) + "(" + lista_tipos_atributos.at(i) 
                       + " _" +  lista_nombre_atributos.at(i)  + "){\n"
                       + "     " + lista_nombre_atributos.at(i) + " = _" + lista_nombre_atributos.at(i) + ";\n}\n\n";

        //Getters
        salida_getters += lista_tipos_atributos.at(i) + " " + nombre_clase + "::" + "get_" + lista_nombre_atributos.at(i) + "(){\n"
                       + "     return " + lista_nombre_atributos.at(i) + ";\n}\n\n";
                       
    }

    salida_getters_setters = salida_setters + salida_getters;

    archivoCPP << salida_getters_setters;//Escribir salida de setters y getters

    //Escribir toString
    transform(nombre_clase.begin(), nombre_clase.end(), nombre_clase.begin(), ::toupper) ;

    archivoCPP << "string " << nombre_clase << "::" << "toString(){\n";
    string salida_toString = "     return " + '"' + nombre_clase + "-> ";

    for (int i = 0; i < cantidad_atributos; i++){
        salida_toString += lista_nombre_atributos.at(i) + ":" +  "+"; 

        if(i == cantidad_atributos){

            if(lista_tipos_atributos.at(i) == "int" || lista_tipos_atributos.at(i) == "double" || lista_tipos_atributos.at(i) == "float" ){
                salida_toString += "to_string" + lista_nombre_atributos.at(i)+ ");\n" ;
            } else if(lista_tipos_atributos.at(i) == "char" || lista_tipos_atributos.at(i) == "string"){
                //Para string o chars
                salida_toString += lista_nombre_atributos.at(i) + ";\n";
            } else if(lista_tipos_atributos.at(i) == "bool"){
                //Para booleans
                salida_toString += lista_nombre_atributos.at(i) + ";\n";
            }
        } else {
            //Para atributos numericos
            if(lista_tipos_atributos.at(i) == "int" || lista_tipos_atributos.at(i) == "double" || lista_tipos_atributos.at(i) == "float" ){
                salida_toString += "to_string" + lista_nombre_atributos.at(i) + ")+" + "|";
            } else if(lista_tipos_atributos.at(i) == "char" || lista_tipos_atributos.at(i) == "string"){
                //Para string o chars
                salida_toString += lista_nombre_atributos.at(i) + "+" + "|";
            } else if(lista_tipos_atributos.at(i) == "bool"){
                //Para booleans
                salida_toString += lista_nombre_atributos.at(i) + "+" + "|";
            }
        }
    }

    salida_toString += "\n}\n\n";
    archivoCPP << salida_toString;
    
    //Escribir Destructor
    archivoCPP << nombre_clase << "::~" << nombre_clase << "(){\n}\n";
}