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
	int dupl =0;//Duplicado.
	
	if(Pliegue[llave].traerNombre().size()){
		//Si existe duplicado, imprime todos los duplicados
		/*Usamos llave + 1 
		ya que descubrimos que si incrementamos en 1 duplicado y luego lo sumamos a la llave seria
		llave + 1*1 que nos da llave + 1
		*/
		if(Pliegue[llave+1].traerNombre().size()){
			while(Pliegue[llave].traerNombre().size()){
				cout<<Pliegue[llave].aCadena()<<endl;//Impresion de los duplicados.
				dupl++;
				llave+=dupl*dupl;
			}
			return true;
		}
		//Si no hay duplicados, se muestra el dato existente.
		cout<<Pliegue[llave].aCadena()<<endl;
		return true;
	}
	//No fue fue encontrado el dato.
	return false;
}
void Hash :: Recorrer(){
	cout<<endl;
	for(int r=0; r<TAM; r++)
		if(Pliegue[r].traerNombre().size())//Si no esta vacio la celda entonces imprime el valor
			cout<<Pliegue[r].aCadena()<<endl;
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






//funcion menu


//Funcion principal
int main() {
	string name; int edad;
	Lectura leer;
  /*
    
  switch(opcion){
    case 1: 
      (aqui ira la presentacion)
		break;
    case 2:
      (aqui ira el planteamiento)
		break;
    case 3:
      (aqui ira la insercion )
		break;
    case 4:
      (aqui ira la busqueda)
		break;
    case 5:
      (salir del programa)
		break;
  }
  */
	//Insercion de datos
	cout << "Ingrese su nombre: ";
	name = leer.DatosCadena();
	cout << "Ingrese su edad: ";
	edad = leer.DatosEnteros();
  cin.ignore();
	if(!Hash::Insertar(name, edad))
		cout<<"Se ha llenado la tabla"<<endl;
	
	//Busqueda de datos
	cout << "Ingrese su nombre a buscar: ";
	name = leer.DatosCadena();
	cout << "Ingrese su edad: ";
	edad = leer.DatosEnteros();
  cin.ignore();
	if(!Hash :: Buscar(name, edad))
	cout<<"La persona buscada no esta alamacenada"<<endl;
	//Recorrido de datos
	Hash :: Recorrer();
}