#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<math.h>
#include<list>
using namespace std;
#include"TreeAVL.hpp"
#include"HashTable.hpp"
class Alumno
{
private:
	int id;
	string nombre;
	float c1, c2, c3, c4;
	float promedio;

public:
	Alumno(short id=0.0f, string nombre="", short c1=0.0f,short c2=0.0f, short c3=0.0f, short c4=0.0f)
	: id(id),nombre(nombre),c1(c1),c2(c2),c3(c3),c4(c4)
	{
		promedio = (this->c1 + this->c2 + this->c3 + this->c4) / 4;
	}
	~Alumno() {}
	float getPromedio() {
		return promedio;
	}
	friend ostream& operator<<(ostream& os, Alumno a)
	{
		os << a.id << " " << a.nombre << " " << a.c1 << " " << a.c2 << " " << a.c3 << " " << a.c4 << "- Nota Promedio: " << a.promedio << endl;
		return os;
	}
	string getNombre() {
		return nombre;
	}
	float getC1() {
		return c1;
	}
	float getC2()
	{
		return c2;
	}
	float getC3()
	{
		return c3;
	}
	float getC4() {

	}
};
class Controladora {
private:
	TreeAVL<Alumno> *arbol;
public:
	Controladora() 
	{
		arbol = new TreeAVL<Alumno>([](Alumno a) {cout << a; },
			
			[](Alumno a, Alumno b)->int {
				if (a.getPromedio() < b.getPromedio())
					return -1;
				else if (a.getPromedio() >= b.getPromedio())
					return 1;
				else
					return 0; },

			[](Alumno a, Alumno b)->int {
					if (a.getPromedio() < b.getPromedio())
						return -1;
					else if (a.getPromedio() > b.getPromedio())
						return 1;
					else
						return 0;
			});
		readData("datos.txt", true);
	}
	~Controladora() {}
	void readData(string name="",bool header=true) {
		ifstream miarchivo(name);
		string linea, cadena;
		if (header)
			getline(miarchivo,linea);
		string id, nombre, c1, c2, c3, c4;
		while (getline(miarchivo, cadena))
		{
			stringstream archMem(cadena);
			getline(archMem, id,',');
			getline(archMem, nombre, ',');
			getline(archMem, c1, ',');
			getline(archMem, c2, ',');
			getline(archMem, c3, ',');
			getline(archMem, c4, ',');
			Alumno alu(stoi(id), nombre, stof(c1), stof(c2), stof(c3), stof(c4));
			arbol->insert(alu);
			//INDEXAR LAS NOTAS A HASHTABLE
		}
	}
	void printArbol() {
		arbol->inOrder();
	}
	void contarAlumnos(float a, float b)
	{
		int cont = 0;
		arbol->setLambda([&a, &b, &cont](Alumno alu) {
			if (alu.getPromedio() >= a && alu.getPromedio() <= b)
				cont++;
			});
		arbol->contar();
		cout << "Alumnos entre (" << a << " : " << b << "): " << cont << endl;
	}
	void calcularDesvEst() {
		float desvEst = 0;
		float suma = 0;
		float promedio = 0;
		float sumatoria = 0;
		int n = arbol->size();
		//Hallamos el promedio de todos los alumnos;
		arbol->setLambda([&suma](Alumno a) {suma += a.getPromedio(); });
		arbol->contar();
		promedio = suma / n;
		arbol->setLambda([&sumatoria,&n,&promedio](Alumno a) {
			sumatoria += ((a.getPromedio() - promedio)* (a.getPromedio() - promedio));
			});
		arbol->contar();
		desvEst = sqrt(sumatoria/(n-1));
		cout << "Desviacion Estandar: " << desvEst << endl;
	}
	void obtnerMayorNota() {
		cout << "Mayor Nota Promedio: " << arbol->maxim().getPromedio();
	}
	void mostrarHashTable() {
		//cout<<hashTable->obtener("Jaime Diaz");
	}
};


int main() {
	Controladora* obj = new Controladora();
	obj->printArbol();
	obj->contarAlumnos(15, 20);
	obj->calcularDesvEst();
	obj->obtnerMayorNota();
	cout << "-------HashTable--------" << endl;
	obj->mostrarHashTable();
	system("pause>=NULL");
	return 0;
}