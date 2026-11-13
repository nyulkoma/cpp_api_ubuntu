#ifndef LOCALIZATION_CATEGORY_HPP
#define LOCALIZATION_CATEGORY_HPP

#include "../types/spatial.hpp"
#include "sensoris/protobuf/categories/localization.pb.h"

class VehiclePositionAndOrientation {
 private:
  EventEnvelope envelope;
  PositionAndAccuracy position;
  RotationAndAccuracy orientation;

 public:
  VehiclePositionAndOrientation(const EventEnvelope& envelope,
                                const PositionAndAccuracy& position,
                                const RotationAndAccuracy& orientation);
  sensoris::protobuf::categories::localization::VehiclePositionAndOrientation*
  generate_proto();
  ~VehiclePositionAndOrientation();
};

class VehicleSpeed {
 private:
  EventEnvelope envelope;
  XyzVectorAndAccuracy speed;

 public:
  VehicleSpeed(const EventEnvelope& envelope,
               const XyzVectorAndAccuracy& speed);
  sensoris::protobuf::categories::localization::VehicleSpeed* generate_proto();
  ~VehicleSpeed();
};

class VehicleAcceleration {
 private:
  EventEnvelope envelope;
  XyzVectorAndAccuracy acceleration;

 public:
  VehicleAcceleration(const EventEnvelope& envelope,
                      const XyzVectorAndAccuracy& acceleration);
  sensoris::protobuf::categories::localization::VehicleAcceleration*
  generate_proto();
  ~VehicleAcceleration();
};

class VehicleRotationRate {
 private:
  EventEnvelope envelope;
  RotationRateAndAccuracy rotation_rate;

 public:
  VehicleRotationRate(const EventEnvelope& envelope,
                      const RotationRateAndAccuracy& rotation_rate);
  sensoris::protobuf::categories::localization::VehicleRotationRate*
  generate_proto();
  ~VehicleRotationRate();
};

class LocalizedVehicle {
 private:
  VehiclePositionAndOrientation vpao;
  VehicleSpeed vs;
  VehicleAcceleration va;
  VehicleRotationRate vrr;

 public:
  LocalizedVehicle(const VehiclePositionAndOrientation& vpao,
                   const VehicleSpeed& vs, const VehicleAcceleration& va,
                   const VehicleRotationRate& vrr);
  VehiclePositionAndOrientation getPositionAndOrientation() const;
  VehicleSpeed getSpeed() const;
  VehicleAcceleration getAcceleration() const;
  VehicleRotationRate getRotationRate() const;
  ~LocalizedVehicle();
};

class LocalizationCategory {
 private:
  vector<LocalizedVehicle> vehicles;

 public:
  LocalizationCategory(const vector<LocalizedVehicle>& vehicles);
  sensoris::protobuf::categories::localization::LocalizationCategory*
  generate_proto();
  ~LocalizationCategory();
};

#endif  // LOCALIZATION_CATEGORY_HPP