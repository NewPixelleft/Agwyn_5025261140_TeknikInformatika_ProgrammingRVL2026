#include "Field.hpp"
#include <iostream>
#include "Player.hpp"

#include <conio.h>


void clearField(int n){
    for (int i = 0; i < n; i++) {
        std::cout << "\033[1A";  
        std::cout << "\033[2K";  
    }
}

int main(){
    Field *f = new Field(10, 20);
    Player *p1 = new Fighter(f, {4, 4});
    Player *p2 = new Bomber(f, {7, 7});
    
    char input = '.';

    while (input != 'q'){
        std::cout << "Player1: " << p1->getHP() << std::endl;
        std::cout << "Player2: " << p2->getHP() << std::endl;
        f->printOut();
        input = _getch();
        switch(input){
            case 'w':
                p1->walk(movement::top);
                break;
            case 'a':
                p1->walk(movement::left);
                break;
            case 's':
                p1->walk(movement::down);
                break;
            case 'd':
                p1->walk(movement::right);
                break;
            case 'k':
                p2->walk(movement::down);
                break;
            case 'j':
                p2->walk(movement::left);
                break;
            case 'l':
                p2->walk(movement::right);
                break;
            case 'i':
                p2->walk(movement::top);
                break;

            case 'c':
                p1->skill(p2);
                break;
            case 'n':
                p2->skill(p1);
                break;
            case 'q':
                input = 'q';
                break;
        }
        clearField(14);
    }
}
