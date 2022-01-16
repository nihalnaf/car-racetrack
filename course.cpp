#include <string>
using std::string;
#include <iostream>
using std::ostream;
using std::endl;
#include <sstream>
using std::istringstream;
#include <algorithm>
using std::remove;
using std::unique;
#include <cctype>

#include "course.h"

// Course constructor from racetrack string
Course::Course(string racetrack) {
  racetrack_ = racetrack;
  // remove whitespace
  racetrack_.erase(remove(racetrack_.begin(), racetrack_.end(), ' '),
                   racetrack_.end());
  // remove empty lines
  racetrack_.erase(
      unique(racetrack_.begin(), racetrack_.end(), [](char chr1, char chr2) {
        return chr1 == '\n' && chr2 == '\n';
      }), racetrack_.end());
  // remove empty line at beginning
  if (racetrack_[0] == '\n') {
    racetrack_.erase(0, 1);
  }
  // remove empty line at end
  if (racetrack_[static_cast<int>(racetrack_.size()) - 1] == '\n') {
    racetrack_.erase(static_cast<int>(racetrack_.size()) - 1);
  }
  racetrack_with_vehicles_ = racetrack_;
  for (int i = 0; i < static_cast<int>(racetrack_.size()); i++) {
    if (isalpha(racetrack_[i])) {
      if (racetrack_[i] == 'S') {
        start_position_ = i;
      } else {
        finish_position_ = i;
      }
    }
  }
}

int Course::GetVehiclePosition(Vehicle* v) {
  return v->position_;
}

char Course::GetVehicleIdentity(Vehicle* v) {
  return v->identity_;
}

// overloaded insertion operator
ostream &operator<<(ostream &out, Course &c) {
  for (auto v : c.vehicles_) {
    // update racetrack to account for vehicles' positions
    for (auto i = c.racetrack_with_vehicles_.begin();
         i != c.racetrack_with_vehicles_.end(); ++i) {
      if ((*i) == c.GetVehicleIdentity(v)) {
        *i = c.racetrack_[i - c.racetrack_with_vehicles_.begin()];
      }
    }
    c.racetrack_with_vehicles_[c.GetVehiclePosition(v)] = c.GetVehicleIdentity(v);
  }
  int size = 0;
  istringstream iss(c.racetrack_with_vehicles_);
  for (auto i = c.racetrack_with_vehicles_.begin();
       i != c.racetrack_with_vehicles_.end(); ++i) {
    if ((*i) == '\n') {
      break;
    }
    size += 1;  // size of row
  }
  int number_of_lines = 1;
  for (auto i = c.racetrack_with_vehicles_.begin();
       i != c.racetrack_with_vehicles_.end(); ++i) {
    if ((*i) == '\n') {
      number_of_lines += 1;  // record number of lines of track
    }
  }
  // wrap track in '+' characters
  for (int i = 0; i < size + 2; i++) {
    out << "+";
  }
  out << endl;
  for (int i = 0; i < number_of_lines; i++) {
    out << "+";
    string word;
    iss >> word;
    out << word;
    out << "+" << endl;
  }
  for (int i = 0; i < size + 2; i++) {
    out << "+";
  }
  out << endl;
  return out;
}

void Course::AddVehicleToStart(Vehicle *v) {
  v->position_ = start_position_;  // change vehicle position to start
  // change racetrack start to show vehicle
  racetrack_with_vehicles_[start_position_] = v->identity_;
  // add vehicle to the course's vehicle vector
  vehicles_.push_back(v);
  // record the size of the row that the vehicle is on
  // this is useful for the vehicle movement
  for (auto i = racetrack_with_vehicles_.begin();
       i != racetrack_with_vehicles_.end(); ++i) {
    if ((*i) == '\n') {
      break;
    }
    v->size_ += 1;
  }
}

Course::Course(Course &c) {
  racetrack_ = c.racetrack_;
  racetrack_with_vehicles_ = racetrack_;
  start_position_ = c.start_position_;
  finish_position_ = c.finish_position_;
}

Course &Course::operator=(Course &c) {
  racetrack_ = c.racetrack_;
  racetrack_with_vehicles_ = c.racetrack_with_vehicles_;
  vehicles_ = c.vehicles_;
  // reset old course vehicles
  c.racetrack_with_vehicles_ = c.racetrack_;
  c.vehicles_.clear();
  return *this;
}

set<Vehicle> Course::VehiclesAtFinish() {
  set<Vehicle> vehicles_at_finish;
  for (auto v : vehicles_) {
    // compare vehicle position with finish position
    if (v->position_ == finish_position_) {
      vehicles_at_finish.insert(*v);
    }
  }
  return vehicles_at_finish;
}

int Course::ReturnOffTrackVehiclesToStart() {
  int num_of_vehicles_removed = 0;
  for (auto v : vehicles_) {
    if (racetrack_[v->position_] == '.') {  // off track if on grass
      // reset vehicle
      racetrack_with_vehicles_[v->position_] = racetrack_[v->position_];
      racetrack_with_vehicles_[start_position_] = v->identity_;
      v->position_ = start_position_;
      // increment number of vehicles removed by one
      num_of_vehicles_removed++;
    }
  }
  return num_of_vehicles_removed;
}