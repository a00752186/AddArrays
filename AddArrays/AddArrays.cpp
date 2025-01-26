// AddArrays.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>

#define chunk 100
#define mostrar 50

void imprimeArreglos(float* a, float* b, float* c);

int main()
{
	int arraySize;

	//Preguntamos cuantos numeros se quieren generar para cada arreglo
	std::cout << "Cuantos numeros quieres generar aleatoriamente?";
	std::cin >> arraySize;

	std::cout << "Sumando Arreglos en Paralelo!\n";
	float* a = new float[arraySize];
	float* b = new float[arraySize];
	float* c = new float[arraySize];
	int i;

	//Esta linea hace que la semilla sea el tiempo actual de la maquina
	std::srand(std::time(0));

	//Se comienza la generacion aleatoria de los numeros, la generacion se realizara entre 0 y 1000
	//El primer arreglo se llenara con numeros enteros
	//El segundo arreglo realizaremos una multiplicacion para forzarlo a ser flotante
	for (i = 0; i < arraySize; i++)
	{
		a[i] = std::rand() % 1000;
		b[i] = (static_cast<float>(std::rand()) / RAND_MAX) * 1000.0f;
	}

	//Se determinan el tamaño de los pedazos a procesar
	int pedazos = chunk;

	//Se indica los objetos que entran como parte del paralelismo asi como cuales deben permanecer aislados en la ejecucion
	#pragma omp parallel for \
	shared(a, b, c, pedazos) private(i) \
	schedule(static, pedazos)

	//Realizamos la operacion de suma de arreglos valor por valor
	for (i = 0; i < arraySize; i++)
		c[i] = a[i] + b[i];

	//Imprimimos los resultados
	imprimeArreglos(a, b, c);

}

void imprimeArreglos(float* a, float* b, float* c)
{
	std::cout << "Mostrando los primeros " << mostrar << " numeros" << std::endl;
	std::cout << "Arreglo A\t\tArreglo B\t\tSuma" << std::endl;
	std::cout << "--------\t\t--------\t\t--------" << std::endl;
	for (int x = 0; x < mostrar; x++)
		std::cout << a[x] << "\t\t\t" << b[x] << "\t\t\t" << c[x] << std::endl;
	std::cout << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
