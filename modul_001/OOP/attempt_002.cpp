#include <iostream>
#include <cmath>

#define el '\n'

template <typename... Args>
void out(Args&&... args){
    (std::cout << ... << args);
}

struct Coordinate{
    double x = 0, y = 0;
};

struct Attr{
struct _MAXHP{
    int Cavalry   = 90;
    int Infantry  = 100;
    int Archer    = 90;
};
struct _MovementSpeed{
    double Infantry_Marching    = 2.7;
    double Infantry_Sprinting   = 8;
    
    double Cavalry_Marching     = 3;
    double Cavalry_Sprinting    = 13;

    double Archer_Marching      = 2.7;
    double Archer_Sprinting     = 8;
};
struct _Def{
    double Basic                = 10;
    double Armored              = 40;
    double HeavyArmoured        = 60;
};
struct _attackRange{
    double Infantry             = 1.6;
    double Cavalry              = 1.7;
    double Archer               = 100;
};
struct _ATK{
    int Infantry                = 50;
    int Cavalry                 = 50;
    int Archer                  = 55;
};
_MAXHP MAXHP;
_MovementSpeed MovementSpeed;
_Def Def;
_attackRange attackRange;
_ATK    ATK;
};

inline constexpr Attr stats{};

double dist(Coordinate a, Coordinate b){
    double dx = a.x - b.x,
           dy = a.y - b.y;
    return std::hypot(dx, dy);
}



class Soldier{
    private:
       int MAXHP;
       int HP;
       Coordinate pos;
       double attackRange;
       double movementSpeed;
       int ATK;
       
       double Def;
        
    public:
        Soldier() = default;
        virtual ~Soldier() = default;

        Soldier(int _MAXHP, Coordinate _pos, double _attackRange, double _Def, int _ATK, double spd){
            MAXHP       = _MAXHP;
            HP          = _MAXHP;
            pos         = _pos;
            attackRange = _attackRange;
            Def         = _Def;
            movementSpeed = spd;
            ATK = _ATK;
            
        }

        
        virtual void deathMsg(){
            out("I have fallen", el);
        }
        virtual void attack(Soldier &target){
            if (!target.isAlive()){
                return;
                // do nothing
            }
            double t = 0;
            if (dist(target.getPos(), getPos()) > attackRange){
                t = moveTo(target.getPos());
            }
            target.damage(ATK);
        }
        int getATK(){
            return ATK;
        }
        void heal(int _heal){
            HP = std::min(MAXHP, HP + _heal);
        }
        void directDamage(int _damage){
            if (_damage > HP)
                HP = 0;
            else HP -= _damage;
        }
        void damage(int _enemyATK){
            int dmg = (int)((double)_enemyATK * (100.0 - Def) / 100.0);
            directDamage(dmg);
        }
        bool isAlive(){
            return HP > 0;
        }
        Coordinate getPos(){
            return pos;
        }
        void movePos(double x, double y){
            pos.x += x;
            pos.y += y;
        }
        double getAttackRange(){
            return attackRange;
        }
        // returns time to move
        double moveTo(Coordinate targetPos){   
            auto _tempPos = pos;
            pos = targetPos;
            return dist(_tempPos, targetPos) / movementSpeed;
        }
        
};

class Archer : public Soldier {
    public:
        Archer(Coordinate pos = {0, 0})
            : Soldier(
                stats.MAXHP.Archer,
                pos,
                stats.attackRange.Archer,
                stats.Def.Basic,
                stats.ATK.Archer,
                stats.MovementSpeed.Archer_Marching
            ){}
        ~Archer() = default;

        void attack(Soldier &target){
            double distance = dist(getPos(), target.getPos());
            if (distance > getAttackRange() || !target.isAlive()){
                return; 
            }
            target.damage(getATK());
        }
    private:
};

class Cavalry : public Soldier {

};

class Infantry : public Soldier {

};
