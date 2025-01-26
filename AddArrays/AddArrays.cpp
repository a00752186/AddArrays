#include <iostream>
#include <omp.h>

// Definimos los valores para los pedazos a utilizar y el número de sumas a mostrar.
#define chunk 500
#define mostrar 50

void imprimeArreglos(float* a, float* b, float* c);

int main()
{
	int arraySize;

	//Preguntamos cuántos números se desean generar para cada arreglo.
	std::cout << "Cuantos numeros quieres generar aleatoriamente?";
	std::cin >> arraySize;

	std::cout << "Sumando Arreglos en Paralelo!\n";
	float* a = new float[arraySize];
	float* b = new float[arraySize];
	float* c = new float[arraySize];
	int i;

	//Esta línea hace que la semilla para la generación de números aleatorios sea el tiempo actual de la máquina.
	std::srand(std::time(0));

	//Se comienza la generación aleatoria de los números, la generación se realizará entre 0 y 1000.
	//El primer arreglo se llenará con números enteros.
	//En el segundo arreglo realizaremos una multiplicación para forzarlo a ser flotante.
	for (i = 0; i < arraySize; i++)
	{
		a[i] = std::rand() % 1000;
		b[i] = (static_cast<float>(std::rand()) / RAND_MAX) * 1000.0f;
	}

	//Se determina el tamaño de los pedazos a procesar en base a la variable global definida.
	int pedazos = chunk;

	//Especificamos el inicio de la ejecución en paralelo, declarando las variables que serán compartidas por los hilos de ejecución, 
	//así como la indicación de que la variable "i" permanecerá privada para cada uno de estos hilos. También indicamos que la ejecución 
	//será de manera estática en pedazos del mismo tamaño.
	#pragma omp parallel for \
	shared(a, b, c, pedazos) private(i) \
	schedule(static, pedazos)

	//Realizamos la operación de suma de arreglos valor por valor.
	for (i = 0; i < arraySize; i++)
		c[i] = a[i] + b[i];

	//Imprimimos los resultados.
	imprimeArreglos(a, b, c);

}

void imprimeArreglos(float* a, float* b, float* c)
{
	//Imprimimos los encabezados.
	std::cout << "Mostrando los primeros " << mostrar << " numeros" << std::endl;
	std::cout << "Arreglo A\t\tArreglo B\t\tSuma" << std::endl;
	std::cout << "--------\t\t--------\t\t--------" << std::endl;
	// Hacemos un ciclo desde el inicio de los arreglos hasta la cantidad de sumas a mostrar
	// y los vamos imprimiendo con el formato de los encabezados.
	for (int x = 0; x < mostrar; x++)
		std::cout << a[x] << "\t\t\t" << b[x] << "\t\t\t" << c[x] << std::endl;
	std::cout << std::endl;
}

