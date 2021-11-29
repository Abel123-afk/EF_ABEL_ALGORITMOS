#ifndef CHASHTABLE_HPP
#define CHASHTABLE_HPP
template<class Key, class Value>
class HashEntidad {
private:
	Key key;
	Value value;
public:
	HashEntidad(Key key, Value value) {
		this->key = key;
		this->value = value;
	}
	Key getKey() { return key; }
	Value getValue() { return value; }
	void setValue(Value NValue) { this->value = NValue; }
};

template<class Key, class Value>
class HashTabla {
private:
	function<int(Key, int)>function_hash;
	HashEntidad<Key, Value>** table;
	size_t size;
	size_t Tsize;
	size_t Criba(size_t n)//13
	{
		while (true)
		{
			n++;//14
			int m = n / 2;//7 -> 14 * 1
			bool esPrimo = 1;
			for (int i = 2; i <= m; i++)
			{
				if (n % i == 0)
				{
					esPrimo = 0;
					break;
				}
			}
			if (esPrimo == 1)
				return n;
		}
	}
	function<void(Value)>_mostrar;
public:
	HashTabla(size_t Tsize, function<int(Key, size_t)>f) {
		this->Tsize = Criba(Tsize);
		table = new HashEntidad<Key, Value> * [this->Tsize];
		for (size_t i = 0; i < this->Tsize; ++i) {
			table[i] = nullptr;
		}
		size = 0;
		this->function_hash = f;
	}
	void setLamda(function<void(Value)>m) {
		_mostrar = m;
	}
	~HashTabla()
	{
		for (size_t i = 0; i < Tsize; ++i) {
			if (table[i] != nullptr) {
				delete table[i];
			}
		}
		delete[] table;
	}
	void insert(Key key, Value value) {
		int base, step, hash;
		if (size == Tsize)return;
		//Función Hash1
		base = this->function_hash(key, Tsize);
		hash = base;
		//constante para Hash2
		step = 0;
		while (table[hash] != nullptr)
		{
			//Función Hash2
			hash = (base + step) % Tsize;
			step++;
		}
		//almacenarlo en la table
		table[hash] = new HashEntidad<Key, Value>(key, value);
		size++;
	}
	size_t tamannio() {
		return this->Tsize;
	}
	size_t sizeactual() {
		return this->size;
	}
	Value obtener(int index)
	{
		return table[index]->getValue();
	}
	Key getLLave(int index)
	{
		return table[index]->getKey();
	}
	bool buscar(string key)
	{
		int step = 0;
		int i, base;
		i = base = this->function_hash(key, Tsize);
		int aux = i;
		bool bandera = true;
		if (i >= 0 && i <= Tsize)
		{
			while (true)
			{
				if (table[i] == nullptr)
				{
					return false;
					break;
				}
				if (table[i]->getKey() == key) {
					cout << "\nLlave encontrada: " << table[i]->getKey() << endl;
					cout << "\n ______________________________________Coincidencia con  Bloque_________________________________ \n";
					_mostrar(table[i]->getValue());
					return true;
					break;
				}
				else step++;
				i = (base + step) % Tsize;
			}
		}
		return false;
	}
	void modificar(Key k, Value nValue)
	{
		int hash = function_hash(k, Tsize);
		int pos;
		for (int i = 0; i < size; i++)
		{
			if (function_hash(table[i]->getKey(), Tsize) == hash)
			{
				pos = i;
				break;
			}
		}
		table[pos]->setValue(nValue);
	}

	void eliminar(Key k)
	{
		int hash = function_hash(k, Tsize);
		vector<short> coincidencias;
		for (int i = 0; i < Tsize; i++)
		{
			if (table[i] != nullptr)
			{
				if (function_hash(table[i]->getKey(), Tsize) == hash)
				{
					coincidencias.push_back(i);
				}
			}
		}
		if (coincidencias.size() == 0) return;
		if (coincidencias.size() == 1)
		{
			table[coincidencias.at(0)] = nullptr;
			coincidencias.clear();
			size--;
		}
		else
		{
			short opc;
			cout << "\tCoinicidencias de hashes\n";
			cout << "Indice\tKey" << endl;
			for (int i = 0; i < coincidencias.size(); i++)
			{
				cout << coincidencias.at(i) << "\t";
				cout << table[coincidencias.at(i)]->getKey() << endl;
			}
			cout << "Ingrese el indice a eliminar: "; cin >> opc;
			table[opc] = nullptr;
			coincidencias.clear();
			size--;
		}
	}
	void mostrar()
	{
		for (int i = 0; i < Tsize; i++)
		{
			if (table[i] != nullptr)
			{
				cout << "Indice: " << i << "\tKey: " << table[i]->getKey() << "\tValue: " << table[i]->getValue() << endl;
			}
		}
	}
};
#endif