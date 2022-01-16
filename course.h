#pragma once
#include <iostream>
using std::ostream;
#include <set>
using std::set;
#include <vector>
using std::vector;
#include <string>
using std::string;

#include "vehicle.h"

class Vehicle;

class Course {
 private:
  string racetrack_;  // racetrack without vehicles
  string racetrack_with_vehicles_;  // racetrack with vehicle positions
  vector<Vehicle*> vehicles_;  // vector of vehicles on track
  int start_position_;  // position where vehicles start as index of string
  int finish_position_;  // vehicle finish position as index of string
  int GetVehiclePosition(Vehicle* v);
  char GetVehicleIdentity(Vehicle* v);
 public:
  Course() = default;
  Course(string racetrack);
  Course(Course& c);
  friend ostream& operator<<(ostream& out, Course& c);
  void AddVehicleToStart(Vehicle* v);
  Course& operator=(Course& c);
  set<Vehicle> VehiclesAtFinish();
  int ReturnOffTrackVehiclesToStart();
  friend class Vehicle;
};