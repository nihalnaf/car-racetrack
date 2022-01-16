#pragma once
#include <iostream>
using std::ostream;

#include "course.h"

class Vehicle {
 private:
  char bearing_;  // direction vehicle is facing
  int size_ = 0;  // size of the row that the vehicle is on
  char identity_;  // character assigned to vehicle
  int position_;  // position on track as index of string
 public:
  Vehicle(char chr);
  void SetBearing(char chr);
  void MoveForward(int distance = 1);
  void TurnLeft();
  void TurnRight();
  friend class Course;
  friend ostream& operator<<(ostream& out, Vehicle& v);
  friend bool operator==(const Vehicle& v1, const Vehicle& v2);
  friend bool operator<(const Vehicle& v1, const Vehicle& v2);
};