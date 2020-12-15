#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#define TAM 47//Se recomienda usar numeros primos para mayor dispersion
using namespace std;

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
	private: 
		static int casillasC;//Para llevar un conteo de la cantidad de datos ingresado

	public:
		static Persona Pliegue[];
		
		static bool Insertar(string nombre, int edad);
		static string Buscar(string busqueda);
		static void Recorrer();

		static int H_Pliegue(string llave);
		static int H_PliegueColision(Persona per[], int llave);

};
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
//Declaracion estatica de los atributos y metodos
Persona Hash :: Pliegue[TAM];
int Hash :: casillasC = 0;

bool Hash :: Insertar(string nombre, int edad){
	int hash = H_Pliegue(nombre);
	if(casillasC<=TAM){
		Pliegue[hash].asignar(nombre, edad);
		return true;
	}
	return false;
}
string Hash :: Buscar(string busqueda){
	int llave = H_Pliegue(busqueda);

	if(!Pliegue[llave].traerNombre().empty())
		return Pliegue[llave].aCadena();

	return "No se ha encontrado el dato buscado";
}
void Hash :: Recorrer(){
	cout<<endl;
	for(int r=0; r<TAM; r++)
		if(!Hash::Pliegue[r].traerNombre().empty())//Si no esta vacio la celda entonces imprime el valor
			cout<<Hash::Pliegue[r].aCadena();
}

int Hash :: H_Pliegue(string llave){
	int valor=0, hash;
	//Se esta sumando el valor de cada caracter
	for(int i=0; i<llave.length(); i++){
		valor += llave[i];
	}
	//Se aplica la operacion
	hash = valor%TAM;
	if(Pliegue[hash].traerNombre().empty())	
		return hash;
	else
		return H_PliegueColision(Pliegue, hash);
}
int Hash :: H_PliegueColision(Persona per[], int llave){
	//c se incrementara cuando se detecte una colision
	int c=0;
	//Buscando si el nombre en esa posicion no este vacia
	while(!per[llave].traerNombre().empty()){
		c++;
		llave += c*c;
	}
	return llave;
}

int main() {
	string name; int edad;
	Lectura leer;
	cout << "Ingrese su nombre: ";
	name = leer.DatosCadena();
	cout << "Ingrese su edad: ";
	edad = leer.DatosEnteros();

	if(!Hash::Insertar(name, edad))
		cout<<"Se ha llenado la tabla"<<endl;
	Hash :: Recorrer();
	cout<<endl<<Hash :: Buscar("Ramon")<<endl;
}