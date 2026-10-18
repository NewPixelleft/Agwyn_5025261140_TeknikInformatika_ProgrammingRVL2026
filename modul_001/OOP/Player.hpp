#pragma once


#include <array>
#include <cstddef>

#include "Coordinate.hpp"
#include "Field.hpp"

enum class movement : int{
    top = 0,
    down,
    left,
    right,
    COUNT
};

Coordinate
moving[] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

const int FighterDamage = 25;
const int BomberDamage  = 20;
const int BaseHP        = 125;

class Player {
public:
    Player(Field *field, Coordinate initC) : AssignedField(field), pos(initC){
        AssignedField->set(initC, 'X');
    }
    virtual ~Player() = default;

    virtual void skill(Player *other) = 0;

    void walk(movement mov){
        if (!isAlive()) return;

        Coordinate _mov = moving[static_cast<int>( mov)];
        Coordinate _temp = {
            .a = _mov.a + pos.a,
            .b = _mov.b + pos.b
        };

        if (AssignedField->inBound(_temp)){
            AssignedField->remove(pos);
            pos = _temp;
            AssignedField->set(pos, 'X');
        }
    }
    void damage(int dmg){
        hp -= dmg;
        if (!isAlive()){
            hp = 0;
            lockDeath();
        }
    }
    int getHP(){
        return hp;
    }
    bool isAlive(){
        return hp > 0;
    }
    bool canAttack(){
        return attackable;
    }
    bool canMove(){
        return movable;
    }
    void setCoordinate(Coordinate C){
        pos = C;
    }
    Coordinate getCoordinate() const {
        return pos;
    }

    void linkToField(Field *LinkingField){
        AssignedField = LinkingField;
    }
    Field *AssignedField = nullptr;
private:
    int hp = BaseHP;
    Coordinate pos = {1, 1};
    bool movable = true;
    bool attackable = true;

    void lockDeath(){
        movable = false;
        attackable = false;
    }

};

class Fighter : public Player {
public:
    Fighter(Field *field, Coordinate C) : Player(field, C){}

    ~Fighter() override = default;


    void skill(Player *other) override {
        if (!canAttack()) return;

        auto [ea, eb]   = other->getCoordinate();
        auto [a, b]     = getCoordinate();

        int da = std::abs(ea - a);
        int db = std::abs(eb - b);

        if (da <= 1 && db <= 1){
            other->damage(FighterDamage);
        }
    }
};

class Bomber : public Player {
public:
    Bomber(Field *field, Coordinate C) : Player(field, C){}

    ~Bomber() override = default;

    void skill(Player *other) override {
        if (!canAttack()) return;
        auto [ea, eb]   = other->getCoordinate();
        auto [a, b]     = getCoordinate();

        int da = std::abs(ea - a);
        int db = std::abs(eb - b);

        if (da <= 2 && db <= 2){
            other->damage(BomberDamage);
        }
    }
};
