#pragma once

#include "Player.hpp"
#include "Field.hpp"


class Game {
public:
    Game() = default;
    ~Game() {
        free(field);
        free(player1);
        free(player2);
    }
    
    void init(Field *_field, Player *player_01, Player *player_02){
        field = _field;
        player2 = player_02;
        player1 = player_01;
    }

    void showNoBar(){
        
    }
    void shoWithBar(){
        
    }
private:
    Field *field = nullptr;
    Player *player1 = nullptr;
    Player *player2 = nullptr;
};
