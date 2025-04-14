#include <iostream>
#include <iostream>
#include <vector>
using namespace std;
#include <chrono>
using NSEC = chrono::nanoseconds;
typedef chrono::high_resolution_clock HRC;

using namespace std;

template<typename T>
class DynamicArray {
private:
    int* wsk;
    int size; // zajęte miejsce w tablicy
    int capacity; // rozmiar całej tablicy

    void resize() {
        T* newWsk = new T[capacity * 2];
        for (int i = 0; i < size; i++) {
            newWsk[i] = wsk[i];
        }
        delete[] wsk;
        wsk = newWsk;
        capacity = capacity * 2;
    }
public:
    DynamicArray(int capacityPom) {
        size = 0;
        capacity = capacityPom;
        wsk = new T[capacity];
    }
    void addToLastPosition(T value) { // dodawanie na koniec struktury
        if (size == capacity) {
            resize();
        }
        wsk[size++] = value;
    }
    void addToFirstPosition(T value) { //dodawanie na początek struktury
        for (int i = size; i>0; i--) {
            if (size == capacity) {
                resize();
            }
            wsk[i] = wsk[i - 1];
        }
        wsk[0] = value;
        size++;
    }
    void addToIndex(T value, int index) { //dodawanie elementu na wybrany indeks
        if (index < 0 || index > size) {
            cout << "Nieprawidlowy indeks";
            return;
        }

        if (size == capacity) {
            resize();
        }
        for (int i = size; i>=index; i--) {
                    if (i == index) {
                    wsk[i] = value;
                }else {
                    wsk[i] = wsk[i - 1];
                }
        }
        size++;
    }
    void printWholeArray() { //wyświetlanie elementów całej struktury
        if (size == 0) {
            cout << "Ta tablica jest pusta";
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << wsk[i] << endl;
        }
    }
    void deleteFirstElement() { //usuwanie elementu z początku struktury
        if (size <= 0) {
            cout << "Ta tablica jest pusta";
            return;
        }
            for (int i = 1; i < size; i++) {
                wsk[i - 1] = wsk[i];
            }
            size--;
    }
    void deleteLastElement() { //usuwanie elementu z końca struktury
        if (size <= 0) {
            cout << "Ta tablica jest pusta";
            return;
        }
            size--;
            cout << "size: " << size;
    }
    void deletAtIndex(int index) { // usuwanie elementu z wybranego indeksu
        bool check = false;
        for (int i = 0; i < size; i++) {
            if (index <= i) {
                wsk[i] = wsk[i+1];
                check = true;
            }
        }
        if (check) {
            size--;
        }else {
            cout << "Nie ma elementu o podanym indeksie";
        }
    }
    void printIndexOfElement(T element) { // wyszukiwanie zadanego elementu
        bool check = false;
        for (int i = 0; i < size; i++) {
            if (wsk[i] == element) {
                cout << i;
                check = true;
                break;
            }
        }
        if (!check) {
            cout << "Nie ma w tablicy takiego elementu";
        }
    }
};


int main()
{
    DynamicArray<int> dynamicArray(2);
    vector<int> sizes = { 100, 1000, 10000, 100000, 200000, 500000, 1000000, 2000000 };

    for (int size : sizes) {
        DynamicArray<int> dynamicArray(2);

        for (int i = 0; i < size; i++) {
            dynamicArray.addToLastPosition(i);
        }

        int indexToDelete = size / 2;

        auto start = HRC::now();
        dynamicArray.printIndexOfElement(indexToDelete); //tutaj każdą funkcję testujemy oddzielnie w celu zmierzenia czasu jej wykonania dla danej liczby elementów
        auto end = HRC::now();

        auto exec_time = chrono::duration_cast<NSEC>(end - start);
        cout << "Size: " << size
            << ", Deleted index: " << indexToDelete
            << ", Execution time: " << exec_time.count() << " ns" << endl;
    }
}
