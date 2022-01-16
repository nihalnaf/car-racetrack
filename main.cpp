#include "course.h"
#include "course.cpp"
#include "vehicle.h"
#include "vehicle.cpp"
#include <string>
using std::string;
#include <iostream>
using std::cout; using std::endl;
#include <set>
using std::set;

int main() {
std::string const map_layout_1 = R"(

..****.

..*..*.

..*..F.

..S....

.......

)";

Course c1(map_layout_1);

std::cout << c1;

Vehicle v1('&');

c1.AddVehicleToStart(&v1);

std::cout << c1;

v1.SetBearing('N');

v1.MoveForward(2);

std::cout << c1;

std::ostringstream oss;

oss << c1;

oss.str("");

v1.SetBearing('n');

v1.SetBearing('W');

v1.MoveForward(-1);

std::cout << c1;

oss << c1;

oss.str("");
}