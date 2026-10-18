#include <iostream>
#include <conio.h>

int main(){
    char key = '.';
    int cnt = 0;
    while (true){
        key = _getch();
        if (key == 'w'){
            std::cout << "Haha, lol\n";
        }
        std::cout << cnt++ << '\n';
    }
}
