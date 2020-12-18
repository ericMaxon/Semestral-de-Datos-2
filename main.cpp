#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <windows.h>
#define TAM 47//Se recomienda usar numeros primos para mayor dispersion
using namespace std;


//Funcion gotoxy
void gotoxy (int x, int y ){ //ancho 120 alto 30
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
//funcion para generar el marco
void marco(){
	for(int i=1; i <=118; i++){
	  		gotoxy(i, 1);cout<<"*";	
	  		gotoxy(i, 27);cout<<"*";
		}
	
	for(int j=1; j <=27; j++){
  		gotoxy(1, j);cout<<"*";	
  		gotoxy(118, j);cout<<"*";
	}
}

//Clase a la que se le estara practicando la tecnica de Hash
class Persona{
	private:
		string nombre;
		int edad;

	public:
		void asignar(string _nombre, int _edad){
			nombre = _nombre;
			edad = _edad;
		}
		
		string traerNombre(){
			return nombre;
		}

		int traerEdad(){
			return edad;
		}
		
		string aCadena(){
			ostringstream os;//Para enviar los datos de la clase juntos
			os <<nombre<<' '<<edad<<endl;
			return os.str();
		}
};
//Clase que contiene las funciones de hash
class Hash{

	public:
		static int casillasC;//Para llevar un conteo de la cantidad de datos ingresado
		static Persona Pliegue[];
		
		static bool Insertar(string nombre, int edad);
		static bool Buscar(string busqueda, int busnum);
		static void Recorrer();

		static int H_Pliegue(string llave, int edad);
		static int H_PliegueColision(int llave);
};
//Declaracion estatica de los atributos y metodos
Persona Hash :: Pliegue[TAM];
int Hash :: casillasC = 0;
//Tecnica de hashing
int Hash :: H_Pliegue(string llave, int edad){
		int valor=0, hash;
		//Se esta sumando el valor de cada caracter
		for(int i=0; i<llave.length(); i++)
			valor += llave[i];
			
		valor += edad;
		//Se aplica la operacion
		hash = valor%TAM;
	return hash;
}
//Tecnica para solucionar colisiones
int Hash :: H_PliegueColision(int llave){
	//c se incrementara cuando se detecte una colision
	int c=0;
	//Buscando si el nombre en esa posicion no este vacia
	while(!Pliegue[llave].traerNombre().empty()){
		c++;
		llave += c*c;
	}
	return llave;
}
bool Hash :: Insertar(string nombre, int edad){
	int hash = H_Pliegue(nombre, edad);
	
	/*Si esta ubicacion no tiende informacion se puede insertar, ya que size() es determinado por la longitud de los caracteres de la cadena,siendo, 0 para vacio(false) y >0 para ocupado (true)*/
	if(!Pliegue[hash].traerNombre().size()){
		if(casillasC<TAM){//Se contailiza cuantos datos han sido ingresado.
			casillasC++;
			Pliegue[hash].asignar(nombre, edad);
			return true;//Se retorna cierto cuando se completa la insercion
		}
	}
	else{//Se ha dado una colision
		hash = H_PliegueColision(hash);//Se aplica el doble desplazamiento
		if(casillasC<TAM){
			casillasC++;
			Pliegue[hash].asignar(nombre, edad);
			return true;
		}
	}
	return false;
}
bool Hash :: Buscar(string busqueda, int busnum){
	int llave = H_Pliegue(busqueda, busnum);
	gotoxy(51, 4);cout<<"Busqueda";
	//Si en la posicion buscada hay informacion, imprime
	if(!Pliegue[llave].traerNombre().empty()){
		gotoxy(40, 15);cout<<"Ha sido encontrado: ";
		gotoxy(40, 16);cout<<Pliegue[llave].aCadena();
		return true;
	}
	else//No fue fue encontrado el dato.
		return false;
}
void Hash :: Recorrer(){
	gotoxy(51, 4);cout<<"Base de datos";
	int linea =0;
	
	if(casillasC>=1){
		for(int r=0; r<TAM; r++)
			if(Pliegue[r].traerNombre().size()){//Si no esta vacio la celda entonces imprime el valor
				gotoxy(51, 8+linea);cout<<Pliegue[r].aCadena();
				linea++;
			}
	}
	else{
			gotoxy(51, 8);cout<<"No hay datos";
	}
		
}

//Clase para la Lectura de datos
class Lectura{
	public:
		string DatosCadena(){
			string dato;
			//para leer una linea de cadenas
			getline(cin,dato);
			return dato;
		}
		int DatosEnteros(){
			int dato;
			bool bandera = false;
			do{
				cin>>dato;
				if(dato<=0){
					cout<<"Ingrese un dato valido"<<endl;
					bandera = true;
				}
			}while(bandera);
			return dato;
		}
};


//Funcion menu
void menu(){
	gotoxy(40, 7);cout<<"________________________________________"<<endl;
	gotoxy(51, 8);cout<<"PROYECTO SEMESTRAL";
	gotoxy(40, 9);cout<<"________________________________________"<<endl;
	gotoxy(51, 10);cout<<"1 - Presentacion";
	gotoxy(51, 11);cout<<"2 - Planteamiento";
	gotoxy(51, 12);cout<<"3 - Insercion";
	gotoxy(51, 13);cout<<"4 - Busqueda";
	gotoxy(51, 14);cout<<"5 - Recorrido";
	gotoxy(51, 15);cout<<"6 - Salir";
}

//Funcion principal
int main() {
	string name; int edad;
	Lectura leer;
	int opcion=0;
	while(opcion < 7){
  		marco();
		menu();
  		
	  	gotoxy(40, 16);cout<<"Opcion a elegir: ";cin>>opcion;
	  	cin.ignore();
	  	
		    if (opcion ==1){//Presentacion
		    	system("cls");
		    		marco();
		      	gotoxy(43, 3);cout<<"UNIVERSIDAD TECNOLOGICA DE PANAMA";//33
		      	gotoxy(35, 5);cout<<"FACULTAD DE INGENIERIA DE SISTEMAS COMPUTACIONALES";//50
		     	gotoxy(34, 7);cout<<"DEPARTAMENTO DE COMPUTACION Y SIMULACION DE SISTEMAS";//52
		     	gotoxy(40, 9);cout<<"Proyecto Final de Estructura de Datos II";//40
		      	gotoxy(27, 11);cout<<"Algoritmos de Ordenamientos y de Busquedas y Transformacion de llaves ";//70
		      	gotoxy(54, 13);cout<<"Integrantes: ";
		      	gotoxy(44, 14);cout<<"Rivas, Guillermo    8-956-469";
		      	gotoxy(44, 15);cout<<"Calvo, Ezequiel     8-929-1899";
		      	gotoxy(44, 16);cout<<"Mason, Eric          3-747-343";
		      	gotoxy(44, 17);cout<<"Pablú, Franklin      8-955-2298";
		      	gotoxy(55, 20);cout<<"Profesora: ";
		      	gotoxy(54, 22);cout<<"Cueto, Doris";
		      	gotoxy(57, 24);cout<<"Fecha:";
		      	gotoxy(48, 26);cout<<"18 de diciembre de 2020"<<endl<<endl<<endl;
		      	gotoxy(5, 28);system("pause");
				system("cls");
			}
		    else if (opcion == 2){//Planteamiento
		    	system("cls");
		    		marco();
		      	gotoxy(50, 10);cout<<"Planteamiento:";
		      	gotoxy(15, 11);cout<<"En este programa, aplicamos el metodo de hashing por pliegue. Para la tecnica de colision";
		      	gotoxy(41, 12);cout<<"utilizamos la dispersion cuadratica.";
		      	gotoxy(40, 14);cout<<"Este programa cuenta con:";
		      	gotoxy(52, 15);cout<<"-Insercion";
		      	gotoxy(52, 16);cout<<"-Busqueda ";
		      	gotoxy(52, 17);cout<<"-Recorrido";
		      	gotoxy(25, 19);cout<<"Aplicamos la tecnica de hash a una base de datos de personas";
		      	gotoxy(5, 30);system("pause");
				system("cls");
			}	
		    else if(opcion == 3){//Insercion
			
		    	system("cls");
		    		marco();
		      	//Insercion de datos
		      	
				gotoxy(50, 10);cout << "Inserta tus datos ";
				gotoxy(43, 12);cout << "Ingrese su nombre: ";
				name = leer.DatosCadena();
				gotoxy(43, 13);cout << "Ingrese su edad: ";
				edad = leer.DatosEnteros();
  				cin.ignore();
				if(!Hash::Insertar(name, edad)){
					gotoxy(43, 14);cout<<"Se ha llenado la tabla";
				}
				gotoxy(5, 20);system("pause");
				system("cls");
			}
		    else if(opcion==4){//Busqueda
		    	system("cls");
		    		marco();
		        //Busqueda de datos
		        gotoxy(51, 4);cout<<"Busqueda";
				gotoxy(40, 12);cout << "Ingrese el nombre a buscar: ";
				name = leer.DatosCadena();
				gotoxy(40, 13);cout << "Ingrese la edad del buscado: ";
				edad = leer.DatosEnteros();
		 		 cin.ignore();
		 		 gotoxy(0,0);
				if(!Hash :: Buscar(name, edad)){
					gotoxy(40, 17);cout<<"La persona buscada no esta alamacenada";
				}
				gotoxy(5, 20);system("pause");
				system("cls");
			}
			else if(opcion == 5){//Recorrer
				system("cls");
					marco();
				//Recorrido de datos
				Hash :: Recorrer();					
				gotoxy(5, 20);system("pause");
				system("cls");
			}
		    else if(opcion == 6){//Salida
					system("cls");
					marco();
		      		gotoxy(60,12);cout<<"¡¡¡Gracias!!!";
					gotoxy(5, 21);system("pause");
					system("cls");
		    		opcion+=1;
			}
			else{//Opcion incorrecta
				gotoxy(51, 20);cout<<"OPCION INVALIDA"<<endl;
				gotoxy(5, 21);system("pause");
				system("cls");
			}		
		}
	}
