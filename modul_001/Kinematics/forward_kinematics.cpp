#include <iostream>
#include <cmath>
#include <vector>


template <typename... Args>
void printout(Args&&... args){
    (std::cout <<...<< args);
}

struct Coordinate{
    double x = 0, y = 0;
};

double toRadian(double degree){
    return degree * M_PI / 180.0;
}

double modulus360(double degree){
    return degree - std::trunc(degree / 360.0) * 360.0;
}

class Arm{
public:
    Arm(size_t _dof) : 
        length(_dof, 0),
        angle(_dof, 0),
        prefix_angle (_dof + 1, 0) {}
    Arm()   = default;
    ~Arm()  = default;
    
    void setLength(size_t index, double _newLength){
        length[index] = _newLength;
    }
    double getLength(size_t index){
        return length[index];
    }
    void setAngle(size_t index, double _newAngle){
        angle[index] = _newAngle;
    }
    double getAngle(size_t index){
        return angle[index];
    }

    void moveJoint(size_t index, double _delta){
        _delta = modulus360(_delta);
        angle[index] += _delta;
        angle[index] = modulus360(angle[index]);

        if (_delta >= 0)
            printout("Moving Joint ", index, ": ", _delta, "degrees Clockwise", '\n');
        else
            printout("Moving Joint ", index, ": ", -_delta, "degrees CounterClockwise", '\n');
    }

    Coordinate getPos(size_t _effector){
        _evaluatePrefix();
        double x = 0,
               y = 0;
        for (size_t i = 0; i < angle.size(); i++){
            double theta = toRadian( modulus360(prefix_angle[i + 1]));
            x += length[i] * std::cos(theta);
            y += length[i] * std::sin(theta);
        }
        return {x, y};
    }

    Coordinate getEndEffector(){
        return getPos(length.size() - 1);
    }
private:
    std::vector <double> length;
    std::vector <double> angle;
    std::vector <double> prefix_angle;

    void _evaluatePrefix(){
        prefix_angle[0] = 0;
        for (size_t i = 1; i <= angle.size(); i++){
            prefix_angle[i] = prefix_angle[i - 1] + angle[i - 1];
        }
    }
};
int main(){
    Arm arm(2);
    arm.setLength(0, 10);
    arm.setLength(1, 5);

    arm.setAngle(0, 30);
    arm.setAngle(1, 10);
    
    Coordinate C = arm.getEndEffector();
    printout(C.x, "  ", C.y);
}
