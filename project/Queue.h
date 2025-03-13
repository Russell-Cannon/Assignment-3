#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

template <typename T>
class Queue {
public:
    Queue() {
        arr = new T[1];
        size = 0;
        maxSize = 1;    
        head = 0;
        tail = 0;
    }
    ~Queue() {
        delete [] arr;
    }

    T operator[] (int i) const { // credit to stack overflow for overwriting operator (https://stackoverflow.com/questions/37043078/c-overloading-array-operator)
        //Returns elements relative to head
        i += head;
        return arr[i%maxSize];
    }

    T& operator[] (int i) {
        //Returns elements relative to head
        i += head;
        return arr[i%maxSize];
    }    

    void Push(T element) {
        if (size + 1 >= maxSize) 
            Double();
        
        (*this)[size] = element;
        tail++;
        size++;
    }

    T Pop() {
        if (IsEmpty())
            return T(); //return nothing

        T dat = (*this)[0];
        size--;
        head++;

        //if the array could hold four times as many elements as it does now
        if (size*4 <= maxSize)
            Half(); //Only half the array, even though we could hold more - prevents thrashing

        return dat;
    }

    T Peek() {
        if (IsEmpty())
            return T();

        // returns the front of the queue
        return (*this)[0];
    }

    void Print() {
        std::cout << '{';
        for (int i = 0; i < size; i++) {
            std::cout << (*this)[i];
            if (i < size - 1)
                std::cout << ", ";
        }
        std::cout << "}\n";
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
            newArr[i] = (*this)[i];
        }
        delete [] arr; //remove old array
        arr = newArr; //move pointer to new array    
        maxSize *= 2; //double the size    
        head = 0;
        tail = size > 0 ? size - 1 : 0;
    }
    void Half() {
        T* newArr = new T[maxSize/2];
        for (int i = 0; i < size; i++) { //copy elements from old arr to new arr
            newArr[i] = (*this)[i];
        }
        delete [] arr; //remove old array
        arr = newArr; //move pointer to new array    
        maxSize /= 2; //half the size    
        head = 0;
        tail = size > 0 ? size - 1 : 0;
    }

    T* arr;
    int size;
    int maxSize;
    int head; //Get from head //The index with the frontmost element
    int tail; //add to tail //The index with the endmost element - mostly one less than the size
};

#endif