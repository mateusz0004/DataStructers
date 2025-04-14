#include <iostream>
#include <vector>
using namespace std;
#include <chrono>

using NSEC = chrono::nanoseconds;
typedef chrono::high_resolution_clock HRC;
template<typename T>
class Node {
public:
    T element;
    Node* next;
    Node* previous;

    Node(T pom) {
        element = pom;
        next = nullptr;
        previous = nullptr;
    }
};
template<typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    DoubleLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    void addToTheBeginningOfTheList(T value) { // dodawanie elementu na początek struktury
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
            size++;
        }
    }
    void addToTheEndOfTheList(T value) { // dodawanie elementu na koniec struktury
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
            size++;
        }
    }
    void print() { // wyświetlanie wszystkich elementów
        Node<T>* pom = head;
        while (pom != nullptr) {
            cout << pom->element << endl;
            pom = pom->next;
        }
        cout << endl;
    }
    void printIndexOfElement(T value) { // wyświetlanie indeksu danego elementu
        if (head == nullptr) {
            cout << "Lista jest pusta";
            return;
        }
        Node<T>* current = head;
        int counter = 0;
        while (current->element != value && current->next != nullptr) {
            current = current->next;
            counter++;
        }
        cout << counter;
    }
    void deleteFirstElement() { // usuwanie pierwszego elementu
        Node<T>* pom = head;
        if (pom == nullptr) {
            cout << "Lista jest pusta";
            return;
        }
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = pom->next;
            head->previous = nullptr;
        }
        size--;
        delete pom;
    }
    void deleteLastElement() { // usuwanie ostatniego elementu
        Node<T>* pom = tail;
        if (tail == nullptr) {
            cout << "Lista jest pusta";
            return;
        }
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = pom->previous;
            tail->next = nullptr;
        }
        size--;
        delete pom;
    }
    void deleteElementAtIndex(int index) { // usuwanie elementu na danym indeksie
        Node<T>* current = nullptr;
        if (index < 0 || index>size) {
            cout << "Niepoprawny index";
            return;
        }
        int counter = 0;
        if (size == index) {
            deleteLastElement();
            return;
        }
        if (index == 0) {
            deleteFirstElement();
            return;
        }
        if (size / 2 >= index) {
            counter = 0;
            current = head;
            while (counter < index) {
                current = current->next;
                counter++;
            }
        }
        else if (size / 2 < index) {
            counter = size;
            current = tail;
            while (counter != index) {
                current = current->previous;
                counter--;
            }
        }
        Node<T>* previousElement = current->previous;
        Node<T>* elementAfter = current->next;
        previousElement->next = elementAfter;
        elementAfter->previous = previousElement;
        size--;
        delete current;
    }
    void addElementToIndex(T element, int index) { // dodawanie elementu na dany indeks
        Node<T>* current = nullptr;
        if (index < 0 || index>size + 1) {
            cout << "Niepoprawny index";
            return;
        }
        if (index == 0) {
            addToTheBeginningOfTheList(element);
            return;
        }
        if (index == size + 1) {
            addToTheEndOfTheList(element);
            return;
        }
        int counter = 0;
        if (size / 2 >= index) {
            counter = 0;
            current = head;
            while (counter < index) {
                current = current->next;
                counter++;
            }
        }
        else if (size / 2 < index) {
            counter = size;
            current = tail;
            while (counter != index) {
                current = current->previous;
                counter--;
            }
        }
        Node<T>* newValue = new Node<T>(element);
        newValue->next = current;
        newValue->previous = current->previous;
        if (current->previous) {
            current->previous->next = newValue;
        }
        current->previous = newValue;
        size++;
    }
};
int main()
{
    vector<int> sizes = { 100, 1000, 10000, 100000, 200000, 500000, 1000000, 2000000 };

    for (int size : sizes) {
        DoubleLinkedList<int> doubleLinkedList;

        for (int i = 0; i < size; i++) {
            doubleLinkedList.addToTheBeginningOfTheList(i);
        }

        int indexToDelete = size / 2;

        auto start = HRC::now();
        doubleLinkedList.deleteLastElement();  //tutaj każdą funkcję testujemy oddzielnie w celu zmierzenia czasu jej wykonania dla danej liczby elementów
        auto end = HRC::now();

        auto exec_time = chrono::duration_cast<NSEC>(end - start);
        cout << "Size: " << size
            << ", Deleted index: " << indexToDelete
            << ", Execution time: " << exec_time.count() << " ns" << endl;
    }

    return 0;
}

