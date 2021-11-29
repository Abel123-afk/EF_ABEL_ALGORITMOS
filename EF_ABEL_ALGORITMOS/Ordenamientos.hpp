#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

#define N 10
template<class T>
class ordenamiento {
	void merge(vector<T> iz, vector<T>der, vector<T>& arr, int n)
	{
		int i, j, k;
		i = j = k = 0;
		while (i < n / 2 && j < n - n / 2)
		{
			if (iz[i] < der[j]) {
				arr[k] = iz[i];
				i++;
				k++;
			}
			else {
				arr[k] = der[j];
				j++;
				k++;
			}
		}
		while (i < n / 2)
		{
			arr[k] = iz[i];
			i++;
			k++;
		}
		while (j < n - n / 2)
		{
			arr[k] = der[j];
			j++;
			k++;
		}
	}
	double tiempo;

public:
	ordenamiento() {}
	~ordenamiento() {}
	void MergeSort(vector<int>& arr, int n)
	{
		clock_t inicio = clock();
		vector<int>a1;
		vector<int>a2;
		if (n > 1)
		{
			for (int i = 0; i < n / 2; i++)
			{
				a1.push_back(arr.at(i));
			}
			for (int i = n / 2; i < n; i++)
			{
				a2.push_back(arr.at(i));
			}
			MergeSort(a1, n / 2);
			MergeSort(a2, n - n / 2);
			merge(a1, a2, arr, n);
		}
		clock_t fin = clock();
		tiempo = (fin - inicio) / CLOCKS_PER_SEC;
	}
	void exchangeSort(vector<int>& numeros)
	{
		clock_t inicio = clock();
		bool ordenado = true;
		for (int i = 0; i < numeros.size() - 1; i++)
		{
			if (numeros[i] > numeros[i + 1])
				ordenado = false;
		}
		if (ordenado) return;
		for (int i = 0; i < numeros.size() - 1; i++)
		{
			for (int j = i + 1; j < numeros.size(); j++)
			{
				if (numeros[i] > numeros[j])
				{
					int aux = numeros[i];
					numeros[i] = numeros[j];
					numeros[j] = aux;
				}
			}
		}
		clock_t fin = clock();
		tiempo = (fin - inicio) / CLOCKS_PER_SEC;
	}
	void showTime()
	{
		cout << "\nTiempo: " << tiempo << endl;
	}
};
void show(vector<int> arr)
{
	for (int n : arr)
	{
		cout << n << " ";
	}
}
void pruebaMerge()
{
	cout << "___Prueba con Merge____" << endl;
	ordenamiento<int>* obj = new ordenamiento<int>();
	vector<int>arr;
	for (int i = 0; i < N; i++)
	{
		arr.push_back(rand() % 100);
	}
	clock_t inicio = clock();
	obj->MergeSort(arr, arr.size());
	clock_t fin = clock();
	cout << endl;
	double tiempo = (fin - inicio) / CLOCKS_PER_SEC;
	cout << "\nTiempo: " << tiempo << endl;
}
void pruebaExchangeSort()
{
	cout << "___Prueba con ExchangeSort____" << endl;
	ordenamiento<int>* obj = new ordenamiento<int>();
	vector<int>arr;
	for (int i = 0; i < N; i++)
	{
		arr.push_back(rand() % 100);
	}
	clock_t inicio = clock();
	obj->exchangeSort(arr);
	clock_t fin = clock();
	cout << endl;
	double tiempo = (fin - inicio) / CLOCKS_PER_SEC;
	cout << "\nTiempo: " << tiempo << endl;

}
/*
int main()
{
	pruebaMerge();

	pruebaExchangeSort();
	system("pause>=NULL");
	return 0;
}*/