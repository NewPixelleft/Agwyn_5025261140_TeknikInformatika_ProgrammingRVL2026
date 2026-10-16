# TUGAS MODUL 001
Includes 3 assignments:
- OOP implementation in C++
- Forward kinematic solution, written on paper
- Implementation of the paper written forward kinematic solution into a C++ program

## Object Oriented Programming

## Paper-Based Forward Kinematic Solution
We are given 2 Degree of Freedom (DOFs). 
$$
\begin{align*}
L_1 = 10\text{cm}\\L_2 = 5\text{cm} \\
\theta_1 = 30^{\circ} \\ \theta_2 = 10^{\circ}
\end{align*}
$$
The problem states to fnind the final position of the end effector in 2 dimensional cartesian field

## Implementation of Forward Kinematic
The implementation of forward Kinematic is pretty straightforward, but we made it more flexible to supporn $N$ amount of arms. This is achieved by creating an `Arm` class.
the  `Arm` class has several methods. Some of the key methods include:
- `Arm(size_t _dof)` creates the class with `_dof` number of link and joint. 
- `void setLength(size_t index, double _newLength)` sets the length of $i^{\text{th}}$ link to `newLength`.
- `void setAngle(size_t index, double _newAngle)` sets the angle of $i^{\text{th}}$ joint to `newAngle` in degree.
- `void moveJoint(size_t index, double _delta)` moves the $i^{\text{th}}$ joint. When `_delta` is negative, it moves the joint counterclockwise and vice versa.
- `Coordinate getPos(size_t _effector)` gets the current position of the effector $i$ with the corresponding angles.
- `Coordinate getEndEffector()` returns the current position of the End Effector.
Other than that, this implementation also contains the struct `Coordinate` which carries `x` and `y` as double. The implementation of this struct is as follows:
```cpp
struct Coordinate{
        double x = 0, y = 0;
};
```
And also a general output function `printout()`.
```cpp
template <typename... Args>
void printout(Args&&... args){
        (std::cout <<...<< args);
}

```
We can implement the `Arm` class very simply. One example would be:
```cpp
int main(){
    Arm arm(2);
    arm.setLength(0, 10);
    arm.setLength(1, 5);

    arm.setAngle(0, 30);
    arm.setAngle(1, 10);
                            
    Coordinate C = arm.getEndEffector();
    printout(C.x, "  ", C.y);
}

```
