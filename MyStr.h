#pragma once
#include <iostream>

class MyStr {
private:
    char* data;
    int length;

    int getLength(const char* str) const {
        int len = 0;
        while (str[len] != '\0') len++;
        return len;
    }

    void copy(char* dest, const char* src) {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    void intToStr(int num, char* buffer) {
        int i = 0;
        if (num == 0) buffer[i++] = '0';
        else {
            while (num > 0) {
                buffer[i++] = (num % 10) + '0';
                num /= 10;
            }
            
            for (int j = 0; j < i / 2; j++) {
                char temp = buffer[j];
                buffer[j] = buffer[i - 1 - j];
                buffer[i - 1 - j] = temp;
            }
        }
        buffer[i] = '\0';
    }

public:
    MyStr() {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }

    MyStr(const char* str) {
        length = getLength(str);
        data = new char[length + 1];
        copy(data, str);
    }

    MyStr(int value) {
        char buffer[20];
        intToStr(value, buffer);
        length = getLength(buffer);
        data = new char[length + 1];
        copy(data, buffer);
    }

    MyStr(const MyStr& other) {
        length = other.length;
        data = new char[length + 1];
        copy(data, other.data);
    }

    ~MyStr() {
        delete[] data;
    }

    MyStr& operator=(const MyStr& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            copy(data, other.data);
        }
        return *this;
    }

    MyStr operator+(const MyStr& other) const {
        int newLength = length + other.length;
        char* newData = new char[newLength + 1];

        for (int i = 0; i < length; i++) newData[i] = data[i];
        for (int j = 0; j < other.length; j++) newData[length + j] = other.data[j];
        newData[newLength] = '\0';

        MyStr result(newData);
        delete[] newData;
        return result;
    }

    const char* c_str() const { return data; }
    int size() const { return length; }

    char& operator[](int index) { return data[index]; }
    const char& operator[](int index) const { return data[index]; }

    friend std::ostream& operator<<(std::ostream& os, const MyStr& str) {
        os << str.data;
        return os;
    }
};