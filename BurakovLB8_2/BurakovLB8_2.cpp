﻿#include <iostream>
#include <string>

struct Data {
	std::string number;
	std::string brand;
	std::string model;
	std::string color;
	std::string owner;
	Data(std::string _number, std::string _brand, std::string _model, std::string _color, std::string _owner) : number(_number), brand(_brand), model(_model), color(_color), owner(_owner) {};
	bool operator==(const Data other) {
		return number == other.number && brand == other.brand && model == other.model && color == other.color && owner == other.owner;
	}
	void print() {
		std::cout << number << "\t" << brand << "\t" << model << "\t" << color << "\t" << owner << "\n";
	}
};

struct Node {
	Data data;
	Node* prev;
	Node* next;
	
	Node(Data _data) : data(_data), prev(nullptr), next(nullptr) {};
	Node(Data _data, Node* _prev, Node* _next) : data(_data), prev(_prev), next(_next) {};

};

class List {
private:
	Node* first;
	Node* last;
public:
	List() : first(nullptr), last(nullptr) {}

	bool empty() {
		return first == nullptr;
	}

	int len() { 
		int index = 0;
		Node* curr = first;
		while (curr != nullptr) {
			++index;
			curr = curr->next;
		}
		return index;
	}

	int middle() {
		int _len = len();
		return ((_len / 2) + 1);
	}

	void push_back(Data _data) {
		Node* p = new Node(_data, last, nullptr);
		if (empty()) {
			first = p;
			last = p;
			return;
		}
		last->next = p;
		last = p;
	}

	void push_front(Data _data) {
		Node* p = new Node(_data, nullptr, first);
		if (empty()) {
			first = p;
			last = p;
			return;
		}
		first->prev = p;
		first = p;
	}

	void push_index(int _index, Data _data) {
		Node* p = new Node(_data);
		if (empty()) {
			first = p;
			last = p;
			return;
		}
		if (_index == 1) {
			push_front(_data);
			return;
		} else if (_index == len() + 1) {
			push_back(_data);
			return;
		}
		Node* curr = first;
		for (int i = 1; i < _index-1; ++i) {
			curr = curr->next;
		}
		p->next = curr->next;
		p->prev = curr;
		curr->next->prev = p;
		curr->next = p;
		
	}

	void pop_back() {
		if (empty()) return;
		else if (last->prev == nullptr) {
			free(last);
			first = nullptr;
			last = nullptr;
			return;
		}
		Node* del_node = last;
		last->prev->next = nullptr;
		last = last->prev;
		delete del_node;
	}

	void pop_front() {
		if (empty()) return;
		else if (first->next == nullptr) {
			free(first);
			first = nullptr;
			last = nullptr;
			return;
		}
		Node* del_node = first;
		first->next->prev = nullptr;
		first = first->next;
		delete del_node;
	}

	void pop_index(int _index) {
		if (empty()) return;
		if (_index == 1) {
			pop_front();
			return;
		} else if (_index == len()) {
			pop_back();
			return;
		}
		Node* curr = first;
		for (int i = 1; i < _index; ++i) {
			curr = curr->next;
		}
		Node* del_node = curr;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		delete del_node;
	}

	void print() {
		if (empty()) {
			std::cout << "Список пуст!";
			return;
		}
		Node* curr = first;
		while (curr != nullptr) {
			curr->data.print();
			curr = curr->next;
		};
	}

	int search(Data _data) {
		Node* curr = first;
		int index = 1;
		while (curr != nullptr) {
			if (curr->data == _data) {
				return index;
			}
			++index;
			curr = curr->next;
		}
		return -1;
	}
};

int main()
{
	setlocale(LC_ALL, "RU");
	List A;
	Data a1("X001AA 161", "BMW", "M5", "black", "Ivanov I.I.");
	Data a2("M678AB 777", "Lada", "Calina", "white", "Sidorenko V.I.");
	Data a3("T325PX 39", "VAZ", "2107", "blue", "Sueta A.V.");
	Data a4("B170CH 102", "Kia", "K5", "white", "Brown F.D.");
	Data a5("E555EE 197", "Rolls-Royce", "Phantom", "black", "Burim A.A.");
	std::cout << "1. Включить новый элемент в конец списка\n";
	A.push_back(a1);
	A.print();
	std::cout << "\n2. Включить новый элемент на заданное пользователем место списка: ";
	int index1;
	std::cin >> index1;
	A.push_index(index1, a2);
	A.print();
	std::cout << "\n3. Включить новый элемент после элемента с заданной информационной частью (X001AA 161 BMW M5 black Ivanov I.I.)\n";
	A.push_index(A.search(a1) + 1, a3);
	A.print();
	std::cout << "\n4. Включить новый элемент перед элементом с заданной информационной частью (M678AB 777 Lada Calina white Sidorenko V.I.)\n";
	A.push_index(A.search(a2), a4);
	A.print();
	std::cout << "\n5. Включить новый элемент в середину списка\n";
	A.push_index(A.middle(), a5);
	A.print();
	std::cout << "\n6. Исключить элемент из середины списка\n";
	A.pop_index(A.middle());
	A.print();
	std::cout << "\n7. Исключить элемент с заданной информационной частью (X001AA 161 BMW M5 black Ivanov I.I.) \n";
	A.pop_index(A.search(a1));
	A.print();
	std::cout << "\n8. Исключить элемент из конца списка\n";
	A.pop_back();
	A.print();
	std::cout << "\n9. Исключить элемент из заданного пользователем места списка: ";
	int index2;
	std::cin >> index2;
	A.pop_index(index2);
	A.print();
	std::cout << "\n10. Исключить элемент из головы списка\n";
	A.pop_front();
	A.print();
}
