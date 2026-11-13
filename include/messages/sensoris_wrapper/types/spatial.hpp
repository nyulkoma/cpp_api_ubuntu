#ifndef SPATIAL_HPP
#define SPATIAL_HPP

#include "base.hpp"
#include <spdlog/spdlog.h>
#include "sensoris/protobuf/types/spatial.pb.h"

class Geographic {
 private:
  SensorisInt64Value longitude;
  SensorisInt64Value latitude;
  SensorisInt64Value altitude;

 public:
  Geographic(const double longitude, const double latitude,
             const double altitude);
  sensoris::protobuf::types::spatial::PositionAndAccuracy_Geographic*
  generate_proto();
  ~Geographic();
};

class Metric {
 private:
  SensorisInt64Value x;
  SensorisInt64Value y;
  SensorisInt64Value z;

 public:
  Metric(const double x, const double y, const double z, const string& unit = "",
         const double resolution = 1.0,
         const int64_t range_min = numeric_limits<int64_t>::min(),
         const int64_t range_max = numeric_limits<int64_t>::max());
  sensoris::protobuf::types::spatial::PositionAndAccuracy_Metric*
  generate_paa_metric();
  sensoris::protobuf::types::spatial::XyzVectorAndAccuracy_Metric*
  generate_xyz_vaa_metric();
  ~Metric();
};

class PositionAndAccuracy {
 private:
  Geographic geographic;
  Metric metric;
  Int64Matrix3x3 covariance;
  sensoris::protobuf::types::spatial::PositionAndAccuracy::GeographicMetricCase
      position_system;

 public:
  PositionAndAccuracy(
      const Geographic& wgs84, const Int64Matrix3x3& covariance,
      const sensoris::protobuf::types::spatial::PositionAndAccuracy::
          GeographicMetricCase position_system);
  PositionAndAccuracy(
      const Metric& metric, const Int64Matrix3x3& covariance,
      const sensoris::protobuf::types::spatial::PositionAndAccuracy::
          GeographicMetricCase position_system);
  sensoris::protobuf::types::spatial::PositionAndAccuracy* generate_proto();
  ~PositionAndAccuracy();
};

class Euler {
 private:
  SensorisInt64Value yaw;
  SensorisInt64Value pitch;
  SensorisInt64Value roll;

 public:
  Euler(const double yaw, const double pitch, const double roll);
  sensoris::protobuf::types::spatial::RotationAndAccuracy_Euler*
  generate_proto();
  ~Euler();
};

class RotationAndAccuracy {
 private:
  Euler euler;
  Int64Matrix3x3 covariance;
  sensoris::protobuf::types::spatial::RotationAndAccuracy::EulerQuaternionCase
      rotation_system;

 public:
  RotationAndAccuracy(
      const Euler& euler, const Int64Matrix3x3& covariance,
      const sensoris::protobuf::types::spatial::RotationAndAccuracy::
          EulerQuaternionCase rotation_system);
  sensoris::protobuf::types::spatial::RotationAndAccuracy* generate_proto();
  ~RotationAndAccuracy();
};

class XyzVectorAndAccuracy {
 private:
  Metric metric;
  Int64Matrix3x3 covariance;
  sensoris::protobuf::types::spatial::XyzVectorAndAccuracy::GeometryCase
      coordinate_system;

 public:
  XyzVectorAndAccuracy(
      const Metric& metric, const Int64Matrix3x3& covariance,
      const sensoris::protobuf::types::spatial::XyzVectorAndAccuracy::
          GeometryCase coordinate_system);
  sensoris::protobuf::types::spatial::XyzVectorAndAccuracy* generate_proto();
  ~XyzVectorAndAccuracy();
};

class CenterOrientationSize {
 private:
  PositionAndAccuracy center;
  RotationAndAccuracy orientation;
  XyzVectorAndAccuracy size;

 public:
  CenterOrientationSize(const PositionAndAccuracy& center,
                        const RotationAndAccuracy& orientation,
                        const XyzVectorAndAccuracy& size);
  sensoris::protobuf::types::spatial::
      RectangularBoxAndAccuracy_CenterOrientationSize*
      generate_proto();
  ~CenterOrientationSize();
};

class RectangularBoxAndAccuracy {
 private:
  CenterOrientationSize cos;

 public:
  RectangularBoxAndAccuracy(const CenterOrientationSize& cos);
  sensoris::protobuf::types::spatial::RectangularBoxAndAccuracy*
  generate_proto();
  ~RectangularBoxAndAccuracy();
};

class RotationRateAndAccuracy {
 private:
  SensorisInt64Value yaw_rate;
  SensorisInt64Value pitch_rate;
  SensorisInt64Value roll_rate;
  Int64Matrix3x3 covariance;

 public:
  RotationRateAndAccuracy(const double yaw_rate, const double pitch_rate,
                          const double roll_rate,
                          const Int64Matrix3x3& covariance);
  sensoris::protobuf::types::spatial::RotationRateAndAccuracy* generate_proto();
  ~RotationRateAndAccuracy();
};

#endif  // SPATIAL_HPP
