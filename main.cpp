#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#define TAM 47//Se recomienda usar numeros primos para mayor dispersion
using namespace std;

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
			ostringstream os;
			os <<nombre<<' '<<edad<<endl;
			return os.str();
		}
};

class Hash{
	public:
		static Persona Residuo[];
		static Persona Pliegue[];
		static Persona Cuadratico[];

		static int H_Residuo(int llave);
		static int H_ResiduoColision(Persona per[], int llave);

		static int H_Pliegue(string llave);
		static int H_PliegueColision(Persona per[], int llave);
};

//Declaracion estatica de los atributos y metodos
Persona Hash :: Residuo[TAM];
Persona Hash :: Pliegue[TAM];
Persona Hash :: Cuadratico[TAM];

int Hash :: H_Residuo(int data){
			int hash = (int)data%TAM;
			cout<<hash<<endl;
			if(Residuo[hash].traerEdad()==0)		
				return hash;
			else
				return H_ResiduoColision(Residuo, hash);
		}
int Hash :: H_Pliegue(string llave){
				int valor=0, hash;
				for(int i=0; i<llave.length(); i++){
					valor += llave[i];
				}
				hash = valor%TAM;
				if(Pliegue[hash].traerNombre().empty())	
					return hash;
			else
				return H_PliegueColision(Pliegue, hash);
		}
int Hash :: H_ResiduoColision(Persona per[], int llave){
				//c se incrementara cuando se detecte una colision
			int c=0;
			//Buscando en el arreglo que esa llave no este ocupada
			while(per[llave].traerEdad()!=0){
				c++;
				llave += c*c;
			}
			return llave;
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
	string name; int edad, llave;
	
  // cout << "Ingrese su nombre, seguido de su edad"<<endl;
	// cin>>name>>edad;
	// llave = Hash::H_Residuo(edad);
	// cout<<llave<<endl;
	// Hash::Residuo[llave].asignar(name, edad);
	// for(int r=0; r<TAM; r++)
	// 	if(Hash::Residuo[r].traerEdad()!=0)
	// 		cout<<Hash::Residuo[r].aCadena();

	// cout << "Ingrese su nombre, seguido de su edad"<<endl;
	// cin>>name>>edad;
	// llave = Hash::H_Pliegue(name);
	// cout<<llave<<endl;
	// Hash::Pliegue[llave].asignar(name, edad);
	// for(int r=0; r<TAM; r++)
	// 	if(!Hash::Pliegue[r].traerNombre().empty())
	// 		cout<<Hash::Pliegue[r].aCadena();
}