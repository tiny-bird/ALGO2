// ALGObinomialheap.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

#include <cstdlib>
using namespace std;
// cutaway of Deputat
struct Deputat{
	int n;
	int degree;
	string IDnumber;
	string surname;
	Deputat* parent;
	Deputat* lchild;
	Deputat* rsibling;
};
// Class for administrative Heap
class BinomialHeap{
private:
	Deputat *head;
	Deputat *roots;
	int count;
public:
	Deputat* initHeap();
	void binomialLink(Deputat*, Deputat*);
	Deputat* createNode(int);
	Deputat* Union(Deputat*, Deputat*);
	Deputat* insert(Deputat*, Deputat*);
	Deputat* merge(Deputat*, Deputat*);
	Deputat* extractMin(Deputat*);
	void revertList(Deputat*);
	void display(Deputat*);
	Deputat* search(Deputat*, int);
	void decreaseKey(Deputat*, int, int);
	void Delete(Deputat*, int);
	BinomialHeap(){
		head = initHeap();
		roots = initHeap();
	}
};


//Initialize Heap
Deputat* BinomialHeap::initHeap(){
	Deputat* np;
	np = NULL;
	return np;
}

//Link nodes
void BinomialHeap::binomialLink(Deputat* y, Deputat* z){
	y->parent = z;
	y->rsibling = z->lchild;
	z->lchild = y;
	z->degree = z->degree + 1;
}

// Create Nodes

Deputat* BinomialHeap::createNode(int k){
	Deputat* p = new Deputat;
	p->n = k;
	return p;
}

//Insert Nodes
Deputat* BinomialHeap::insert(Deputat* H, Deputat* x){
	Deputat* H1 = initHeap();
	x->parent = NULL;
	x->lchild = NULL;
	x->rsibling = NULL;
	x->degree = 0;
	H1 = x;
	H = Union(H, H1);
	return H;
}


//Union Nodes

Deputat* BinomialHeap::Union(Deputat* H1, Deputat* H2){
	Deputat *H = initHeap();
	H = merge(H1, H2);
	if (H == NULL)
		return H;
	Deputat* prev_x;
	Deputat* next_x;
	Deputat* x;
	prev_x = NULL;
	x = H;
	next_x = x->rsibling;
	while (next_x != NULL){
		if ((x->degree != next_x->degree) || ((next_x->rsibling != NULL)
			&& (next_x->rsibling)->degree == x->degree)){
			prev_x = x;
			x = next_x;
		}
		else{
			if (x->n <= next_x->n)	{
				x->rsibling = next_x->rsibling;
				binomialLink(next_x, x);
			}
			else{
				if (prev_x == NULL)
					H = next_x;
				else
					prev_x->rsibling = next_x;
				binomialLink(x, next_x);
				x = next_x;
			}
		}
		next_x = x->rsibling;
	}
	return H;
}

//Merge Nodes

Deputat* BinomialHeap::merge(Deputat* H1, Deputat* H2){
	Deputat* H = initHeap();
	Deputat* y;
	Deputat* z;
	Deputat* a;
	Deputat* b;
	y = H1;
	z = H2;
	if (y != NULL){
		if (z != NULL){
			if (y->degree <= z->degree)
				H = y;
			else if (y->degree > z->degree)
				H = z;
		}
		else
			H = y;
	}
	else
		H = z;
	while (y != NULL && z != NULL){
		if (y->degree < z->degree){
			y = y->rsibling;
		}
		else if (y->degree == z->degree){
			a = y->rsibling;
			y->rsibling = z;
			y = a;
		}
		else{
			b = z->rsibling;
			z->rsibling = y;
			z = b;
		}
	}
	return H;
}

// Display Binomial Heap
void BinomialHeap::display(Deputat* H){
	if (H == NULL){
		cout << "The Heap is empty" << endl;
		return;
	}
	cout << "The root nodes: " << endl;
	Deputat* p;
	p = H;
	while (p != NULL){
		cout << p->n;
		if (p->rsibling != NULL)
			cout << "-->";
		p = p->rsibling;
	}
	cout << endl;
}

Deputat* BinomialHeap::extractMin(Deputat* H1){
	roots = NULL;
	Deputat* t = NULL;
	Deputat* x = H1;
	if (x == NULL){
		cout << "Nothing to Extract" << endl;
		return x;
	}
	int min = x->n;
	Deputat* p = x;
	while (p->rsibling != NULL){
		if ((p->rsibling)->n < min){
			min = (p->rsibling)->n;
			t = p;
			x = p->rsibling;
		}
		p = p->rsibling;
	}
	if (t == NULL && x->rsibling == NULL)
		H1 = NULL;
	else if (t == NULL)
		H1 = x->rsibling;
	else if (t->rsibling == NULL)
		t = NULL;
	else
		t->rsibling = x->rsibling;
	if (x->lchild != NULL){
		revertList(x->lchild);
		(x->lchild)->rsibling = NULL;
	}
	head = Union(H1, roots);
	return x;
}

void BinomialHeap::revertList(Deputat* y){
	if (y->rsibling != NULL){
		revertList(y->rsibling);
		(y->rsibling)->rsibling = y;
	}
	else{
		roots = y;
	}
}


Deputat* BinomialHeap::search(Deputat* H, int k){
	Deputat* x = H;
	Deputat* p = NULL;
	if (x->n == k){
		p = x;
		return p;
	}
	if (x->lchild != NULL && p == NULL)
		p = search(x->lchild, k);
	if (x->rsibling != NULL && p == NULL)
		p = search(x->rsibling, k);
	return p;
}

void BinomialHeap::decreaseKey(Deputat* H, int i, int k){
	int temp;
	Deputat* p;
	Deputat* y;
	Deputat* z;
	p = search(H, i);
	if (p == NULL){
		cout << "There is no such key" << endl;
		return;
	}
	if (k > p->n){
		cout << "Error!! New key is biger" << endl;
		return;
	}
	p->n = k;
	y = p;
	z = p->parent;
	while (z != NULL && y->n < z->n){
		temp = y->n;
		y->n = z->n;
		z->n = temp;
		y = z;
		z = z->parent;
	}
	cout << "Key reduced" << endl;
}

void BinomialHeap::Delete(Deputat* H, int k){
	Deputat* np;
	if (H == NULL){
		cout << "\nHeap is Empty";
		return;
	}
	decreaseKey(H, k, -1000);
	np = extractMin(H);
	if (np != NULL)
		cout << "Node Deleted" << endl;
}

int main(){
	int m, l;
	BinomialHeap bh;
	Deputat* p;
	Deputat *H;
	H = bh.initHeap();
	while (1){
		cout << "----------------------------" << endl;
		cout << "What do you want?: " << endl;
		cout << "1)Add detutat(insertion)" << endl;
		cout << "2)Extract a boss(minimum)" << endl;
		cout << "3)To promote deputat(decrease key)" << endl;
		cout << "4)Lustrate deputat (delete a node)" << endl;
		cout << "5)Display Heap" << endl;
		cout << "6)Exit" << endl;
		cout << "Enter Your Choice: ";
		cin >> l;
		switch (l){
		case 1:
			cout << "Enter the element you want to insert: ";
			cin >> m;
			p = bh.createNode(m);
			H = bh.insert(H, p);
			break;
		case 2:
			p = bh.extractMin(H);
			if (p != NULL)
				cout << "Minimum key: " << p->n << endl;
			else
				cout << "Heap is empty" << endl;
			break;
		case 3:
			cout << "Enter the key you want to decrease: ";
			cin >> m;
			cout << "Enter new value: ";
			cin >> l;
			bh.decreaseKey(H, m, l);
			break;
		case 4:
			cout << "Enter the key you want to delete: ";
			cin >> m;
			bh.Delete(H, m);
			break;
		case 5:
			cout << "Heap: " << endl;
			bh.display(H);
			break;
		case 6:
			exit(1);
		default:
			cout << "Wrong Choice";
		}
	}
	return 0;
}


/*int main(){
	cout << "Create by H.K" << endl;
	system("pause");
	return 0;
	}
	*/
