#include "vehicle.h"
#include <stdexcept>
using std::invalid_argument;

Vehicle::Vehicle(char chr) {
  identity_ = chr;  // constructor assigns character to vehicle
}

ostream& operator<<(ostream& out, Vehicle& v) {
  out << v.identity_;  // inserts vehicle character to ostream
  return out;
}

bool operator==(const Vehicle& v1, const Vehicle& v2) {
  return (v1.identity_ == v2.identity_);  // compares characters
}

bool operator<(const Vehicle& v1, const Vehicle& v2) {
  return v1.identity_ < v2.identity_;  // true if ASCII value of char is less
}

void Vehicle::SetBearing(char chr) {
  if (!((chr == 'N') || (chr == 'S') || (chr == 'E') || (chr == 'W'))) {
    throw invalid_argument("Invalid argument");
  }  // throws invalid argument if not N, S, E, or W
  bearing_ = chr;
}

void Vehicle::MoveForward(int distance) {
  switch (bearing_) {
    case 'N':
      position_ -= distance * (size_ + 1);
      break;  // subtract d * (length of row plus one) (new line char)
    case 'S':
      position_ += distance * (size_ + 1);
      break;  // add d * (length of row plus one) to move down
    case 'E':
      position_ += distance;
      break;  // add distance to position
    case 'W':
      position_ -= distance;
      break;  // subtract distance from position
    default:
      throw invalid_argument("Invalid argument");
      break;  // throw invalid argument if bearing isn't valid
  }
}

void Vehicle::TurnLeft() {
  switch (bearing_) {
    case 'N':
      bearing_ = 'W';
      break;
    case 'S':
      bearing_ = 'E';
      break;
    case 'E':
      bearing_ = 'N';
      break;
    case 'W':
      bearing_ = 'S';
      break;
  }
}

void Vehicle::TurnRight() {
  switch (bearing_) {
    case 'N':
      bearing_ = 'E';
      break;
    case 'S':
      bearing_ = 'W';
      break;
    case 'E':
      bearing_ = 'S';
      break;
    case 'W':
      bearing_ = 'N';
      break;
  }
}