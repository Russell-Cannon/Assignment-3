#ifndef RESIZINGARRAY_H
#define RESIZINGARRAY_H
#include <iostream>

//template referenced from geeksforgeeks (https://www.geeksforgeeks.org/templates-cpp/)
template <typename T> class ResizingArray {
public:
    ResizingArray() {
        arr = new T [maxSize];
    }

    ResizingArray(const ResizingArray& other) {
        delete [] arr; //should never have anything in it

        size = other.size;
        maxSize = other.maxSize;

        arr = new T[maxSize];

        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }

    ~ResizingArray() {
        delete [] arr;
    }

    ResizingArray& operator=(const ResizingArray& other) {
        if (this != &other) { //check for self-assign
            delete [] arr;

            size = other.size;
            maxSize = other.maxSize;
    
            arr = new T[maxSize];
    
            for (int i = 0; i < size; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    T operator[] (int i) const { // credit to stack overflow for overwriting operator (https://stackoverflow.com/questions/37043078/c-overloading-array-operator)
        return arr[i];
    }

    T& operator[] (int i) {
        return arr[i];
    }

    T Front() const {
        if (size == 0)
            std::cout << "Tried to access empty array.\n";
        return arr[size - 1];
    }

    T& Front() {
        if (size == 0)
            std::cout << "Tried to access empty array.\n";
        return arr[size - 1];
    }


    void Push(T element) {
        if (size >= maxSize) 
            Double();
        arr[size] = element;
        size++;
    }

    void Push() { //Don't initialize. Useful for arrays of classes
        if (size >= maxSize) 
            Double();
        size++;
    }

    T Pop() {
        //if the array could hold four times as many elements as it does now
        if (size*4 <= maxSize)
            Half();
        //Dont bother cleaning out the data at that array - it will be ineccessable
        size--;
        return arr[size];
    }
    
    void Print() {
        std::cout << '{';
        for (int i = 0; i < size; i++) {
            std::cout << arr[i];
            if (i < size - 1)
                std::cout << ", ";
        }
        std::cout << "} (" << size << '/' << maxSize << ")\n";    
    }
    
    int getSize() {
        return size;
    }
    int getMaxSize() {
        return maxSize;
    }
    bool IsEmpty() {
        return getSize() == 0;
    }

protected:
    void Double() {
        T* newArr = new T[maxSize*2];
        for (int i = 0; i < size; i++) { //copy elements from old arr to new arr
            newArr[i] = arr[i];
        }

        delete [] arr; //remove old array

        arr = newArr; //move pointer to new array
        maxSize *= 2; //double the size    
    }
    void Half() {
        T* newArr = new T[maxSize/2];
        for (int i = 0; i < size; i++) { //copy elements from old arr to new arr
            newArr[i] = arr[i];
        }

        delete [] arr; //remove old array

        arr = newArr; //move pointer to new array    
        maxSize /= 2; //half the size    
    }
    T* arr = nullptr;
    int size = 0;
    int maxSize = 1;
};

#endif