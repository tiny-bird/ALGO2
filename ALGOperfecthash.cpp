// ALGOperfecthash.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>

using namespace std;

typedef long long int long_int;
const int max_int = 1000000001; // value, that could't be in the table. Analog of NULL.

// hash calculation  
 int makehash(long_int a_prime, long_int b_prime, int p_prime, int table_size, int key){
	return (((a_prime * key + b_prime) % p_prime) % table_size);
}

// class for mini-hash table in cells of main hash-table 
class Box{
	vector<int> cells;
	int size; // the size of mini-table should be greater then 4 
	long_int hash_a;
	long_int hash_b;
	int prime;

public:
	Box() {}
	void Initialize(){
		prime = 17;
		hash_a = std::rand() % prime;
		hash_b = 1 + std::rand() % (prime - 1);
	}

	// construct hash table from list of elements
	void Construct(list<int>& input){
		if (input.empty()){
			size = 0;
			return;
		}

		size = input.size() * input.size();
		bool flag = true;

		// while there is no collisions in table 
		while (flag){
			cells.assign(size, max_int);
			Initialize();
			list<int>::iterator elem = input.begin();
			while (elem != input.end() && flag){
				int hashKey = makehash(hash_a, hash_b, prime, size, *elem);
				if (hashKey < 0)
					hashKey = -hashKey;

				// if collision then construct hash table from the begining!
				if (cells[hashKey] != max_int){
					flag = false;
					break;
				}
				cells[hashKey] = *elem;
				++elem;
			}

			if (!flag)
				flag = true;
			else
				flag = false;
		}
	}

	bool Contains(int elem){
		if (size == 0)
			return false;
		int hashKey = makehash(hash_a, hash_b, prime, size, elem);
		if (hashKey < 0)
			hashKey = -hashKey;
		if (cells[hashKey] == elem)
			return true;
		return false;
	}
};

// class for main hash table
class mainTable{
	int tableSize;
	long_int hashFuncA;
	long_int hashFuncB;
	int primeNumber;
	vector<list<int> > elementsInCells;
	vector<Box> boxes;

public:
	mainTable(){
		primeNumber = 100013; // the maximum prime number
		hashFuncA = std::rand() % primeNumber;
		hashFuncB = 1 + std::rand() % (primeNumber - 1);
	}

	void setTableSize(int size){
		tableSize = size;
		boxes.resize(size);
	}

	void Initialize(const vector<int>& numbers){
		tableSize = numbers.size();
		boxes.resize(numbers.size());
		elementsInCells.resize(numbers.size());
		for (int i = 0; i < numbers.size(); ++i){
			int hashKey = makehash(hashFuncA, hashFuncB, primeNumber, tableSize, numbers[i]);
			if (hashKey < 0)
				hashKey = -hashKey;
			elementsInCells[hashKey].push_back(numbers[i]);
		}
		for (int i = 0; i < numbers.size(); ++i){
			boxes[i].Construct(elementsInCells[i]);
		}
	}

	bool Contains(int number){
		int hashKey = makehash(hashFuncA, hashFuncB, primeNumber, tableSize, number);
		if (hashKey < 0)
			hashKey = -hashKey;
		return boxes[hashKey].Contains(number);
	}
};

int main(int argc, char* argv[]){
	int numberOfElements;
	fstream file("File.txt");

	file>>numberOfElements;

	mainTable fs;
	vector<int> inputVector;
	fs.setTableSize(numberOfElements);

	for (int i = 0; i < numberOfElements; ++i){
		int elemValue;
		file>>elemValue;
		inputVector.push_back(elemValue);
		cout << elemValue << endl;
	}

	fs.Initialize(inputVector);
	int numberOfElementsForSearch;
	cout << "Enter  the number of elements for search: \n";
	cin>>numberOfElementsForSearch;
	cout << "Enter elements for search: \n";
	for (int i = 0; i < numberOfElementsForSearch; ++i){
		int elem;
		cin>>elem;
		if (fs.Contains(elem)){
			cout << "Yes" << endl;
		}
		else{
			cout << "No" << endl;
		}
	}
	system("pause");
	return 0;
}
