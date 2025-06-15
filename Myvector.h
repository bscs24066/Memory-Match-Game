#pragma once

template <typename T>
class MyVector {
private:
    T* data;
    int capacity;
    int count;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    MyVector() {
        capacity = 4;
        count = 0;
        data = new T[capacity];
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (count == capacity) resize(capacity * 2);
        data[count++] = value;
    }

    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const { return data[index]; }

    int size() const { return count; }

    void clear() {
        delete[] data;
        capacity = 4;
        count = 0;
        data = new T[capacity];
    }
};