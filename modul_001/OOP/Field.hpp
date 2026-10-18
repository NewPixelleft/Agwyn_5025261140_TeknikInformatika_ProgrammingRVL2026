#pragma once
#include <vector>

#include <string>
#include <iostream>

#include "Coordinate.hpp"

constexpr char empty = '.';

class Field {
public:
    Field(const int _height, const int _length):
        height(_height + 2),
        length(_length + 2),
        __field(_height + 2, std::string(_length + 2, empty))
    {
        for (int i = 0; i < height; i++){
            if (i == 0 || i == height - 1){
                __field[i] = std::string(length, '#');
            }
            else {
                __field[i][0] = '#';
                __field[i][length - 1] = '#';
            }
        }
    }

    bool inBound(Coordinate C){
        if((
            (C.a >= height || C.a < 0) ||
            (C.b >= length || C.b < 0)
        )) return false;
        return __field[C.a + 1][C.b + 1] == empty;
    }
    bool inBoundAny(Coordinate C){
        return !((C.a >= height || C.a < 0) ||
            (C.b >= length || C.b < 0));
    }
    
    void remove(Coordinate C){
        if (!inBoundAny(C)) return;
        __field[C.a + 1][C.b + 1] = empty;
    }

    void printOut(){
        for (const std::string &i: __field)
            std::cout << i << std::endl;
    }

    void set(Coordinate C, char ch){
        if (!inBound(C)) return;
        __field[C.a + 1][C.b + 1] = ch;
    }

private:
    std::vector <std::string> __field;
    int height = 0,
        length = 0;
};
