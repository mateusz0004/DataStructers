#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
using NSEC = chrono::nanoseconds;
typedef chrono::high_resolution_clock HRC;
template<typename T>
class Node {
public:
    T element;
    Node* next;

    Node(T pom) {
        element = pom;
        next = nullptr;
    }
};
template<typename T>
class ListaJednokierunkowa {
private:
    Node<T>* head = nullptr;
    int size;
public:
    ListaJednokierunkowa() {
        head = nullptr;
        size = 0;
    }
    void addToEndOfTheList(T value) { // dodawanie elementu na koniec struktury
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }
    void print() { // wyswietlanie całej struktury
        Node<T>* pom = head;
        while (pom != nullptr) {
            cout << pom->element << endl;
            pom = pom->next;
        }
        cout << endl;
    }
    void addToBeginningOfTheList(T value) { // dodawanie elementu na początek struktury
        Node<T>* beginningNode = new Node<T>(value);
        if (head == nullptr) {
            head = beginningNode;
        }
        else {
            beginningNode->next = head;
            head = beginningNode;
        }
        size++;
    }
    void addToIndex(T value, int index) { // dodawanie elementu na wybrany indeks
        int counter = 1;
        Node<T>* newNode = new Node<T>(value);
        Node<T>* temp = head;
        if (index<0 || index >size) {
            cout << "Niewlasciwy index";
            return;
        }
        if (index == 1) {
            newNode->next = temp;
            head = newNode;
            return;
        }
        while (counter != index - 1 && temp != nullptr) {
            temp = temp->next;
            counter++;
        }

        if (temp == nullptr) { //// jeśli head == null
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }
    void deleteNodeFromEnd() { // usuwanie elementu z końca struktury
        Node<T>* temp = head;
        Node<T>* pom = nullptr;
        if (head == nullptr) {  // Jeśli lista jest pusta, nic nie robimy
            cout << "Tablica pusta";
            return;
        }
        if (temp->next == nullptr) {
            temp = nullptr;
            head = nullptr;
        }
        while (temp->next != nullptr) {
            pom = temp;
            temp = temp->next;
        }
        pom->next = nullptr;
        size--;
        delete temp;
    }
    void deleteNodeFromBegining() { // usuwanie elementu z początku struktury
        Node<T>* temp = head;
        if (head == nullptr) {
            cout << "Tablica pusta";
            return;
        }
        else if (temp->next == nullptr) {
            head = nullptr;
        }
        else {
            head = temp->next;
        }
        size--;
        delete temp;
    }
    void deleteNodeFromIndex(int index) { // usuwanie elementu z wybranego indeksu
        Node<T>* temp = head;
        Node<T>* pom = nullptr;
        if (head == nullptr || index < 1 || index>size) {
            cout << "Niewlasciwy indeks";
            return;
        }
        int counter = 1;
        if (index == 1) {
            head = temp->next;
            delete temp;
            return;
        }
        while (counter != index && temp != nullptr) {
            pom = temp;
            temp = temp->next;
            counter++;
        }
        if (temp == nullptr) return;
        pom->next = temp->next;
        size--;
        delete temp;
    }
    void displayIndexOfElement(T value) { // wyszukiwanie zadanego elementu
        Node<T>* temp = head;
        int counter = 1;
        while (temp->element != value && counter != size) {
            counter++;
            temp = temp->next;
        }
        if (temp->element == value) {
            cout << size - counter;
        }
        else {
            cout << "Nie ma takiego elementu w liscie";
        }
    }
};
int main()
{
    ListaJednokierunkowa<int> list;
    vector<int> sizes = {100, 1000, 10000, 100000, 200000, 500000, 1000000, 2000000};

    for (int size : sizes) {
        for (int i = 0; i < size; i++) {
            list.addToEndOfTheList(i);
        }

        int indexToDelete = size / 2;

        auto start = HRC::now();
        list.displayIndexOfElement(indexToDelete); //tutaj każdą funkcję testujemy oddzielnie w celu zmierzenia czasu jej wykonania dla danej liczby elementów
        auto end = HRC::now();

        auto exec_time = chrono::duration_cast<NSEC>(end - start);
        cout << "Size: " << size
            << ", Deleted index: " << indexToDelete
            << ", Execution time: " << exec_time.count() << " ns" << endl;
    }
    return 0;
}
