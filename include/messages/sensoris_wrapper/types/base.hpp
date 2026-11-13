#ifndef BASE_HPP
#define BASE_HPP

#include <google/protobuf/wrappers.pb.h>

#include <iostream>
#include <limits>
#include <cmath>

#include "sensoris/protobuf/types/base.pb.h"

using namespace std;
using google::protobuf::BoolValue;
using google::protobuf::Int64Value;
using google::protobuf::StringValue;

class GoogleInt64Value {
 private:
  string unit;
  double resolution;
  int64_t range_min;
  int64_t range_max;
  int64_t value;

 public:
  GoogleInt64Value(const double value, const string& unit = "",
                   const double resolution = 1.0,
                   const int64_t range_min = numeric_limits<int64_t>::min(),
                   const int64_t range_max = numeric_limits<int64_t>::max());
  Int64Value* generate_proto();
  ~GoogleInt64Value();
};

class GoogleStringValue {
 private:
  string value;

 public:
  GoogleStringValue(const string& value);
  StringValue* generate_proto();
  ~GoogleStringValue();
};

class GoogleBoolValue {
 private:
  bool value;

 public:
  GoogleBoolValue(const bool value);
  BoolValue* generate_proto();
  ~GoogleBoolValue();
};

class SensorisInt64Value {
 private:
  string unit;
  double resolution;
  int64_t range_min;
  int64_t range_max;
  int64_t value;

 public:
  SensorisInt64Value(const double value, const string& unit = "",
                     const double resolution = 1.0,
                     const int64_t range_min = numeric_limits<int64_t>::min(),
                     const int64_t range_max = numeric_limits<int64_t>::max());
  sensoris::protobuf::types::base::Int64Value* generate_proto();
  ~SensorisInt64Value();
};

class Int64Matrix3x3 {
 private:
  GoogleInt64Value matrix[3][3];

 public:
  Int64Matrix3x3(const double (&matrix)[3][3], const string& unit = "",
                 const double resolution = 1.0,
                 const int64_t range_min = numeric_limits<int64_t>::min(),
                 const int64_t range_max = numeric_limits<int64_t>::max());
  sensoris::protobuf::types::base::Int64Matrix3x3* generate_proto();
  ~Int64Matrix3x3();
};

class Timestamp {
 private:
  GoogleInt64Value posix_time;
  GoogleInt64Value fraction;

 public:
  Timestamp(const double timestamp);
  sensoris::protobuf::types::base::Timestamp* generate_proto();
  ~Timestamp();
};

class Confidence {
 private:
  int64_t value;

 public:
  Confidence(const double fraction);
  sensoris::protobuf::types::base::Confidence* generate_proto();
  ~Confidence();
};

class EventEnvelope {
 private:
  GoogleInt64Value id;
  Timestamp timestamp;

 public:
  EventEnvelope(const int64_t id, const double timestamp);
  sensoris::protobuf::types::base::EventEnvelope* generate_proto();
  ~EventEnvelope();
};

#endif  // BASE_HPP
