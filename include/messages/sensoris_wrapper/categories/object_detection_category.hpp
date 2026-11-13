#ifndef OBJECT_DETECTION_CATEGORY_HPP
#define OBJECT_DETECTION_CATEGORY_HPP

#include "../types/spatial.hpp"
#include "sensoris/protobuf/categories/object_detection.pb.h"

class TypeAndConfidence {
 private:
  sensoris::protobuf::categories::objectdetection::
      MovableObject_TypeAndConfidence_Type type;
  Confidence confidence;

 public:
  TypeAndConfidence(const sensoris::protobuf::categories::objectdetection::
                        MovableObject_TypeAndConfidence_Type type,
                    const Confidence& confidence);
  sensoris::protobuf::categories::objectdetection::
      MovableObject_TypeAndConfidence*
      generate_proto();
  ~TypeAndConfidence();
};

class MovableObject {
 private:
  EventEnvelope envelope;
  GoogleInt64Value object_id;
  Confidence existence_confidence;
  TypeAndConfidence type_and_confidence;
  RectangularBoxAndAccuracy rect_box_and_acc;
  XyzVectorAndAccuracy speed_and_acc;
  XyzVectorAndAccuracy accel_and_acc;

 public:
  MovableObject(const EventEnvelope& envelope,
                const GoogleInt64Value& object_id,
                const Confidence& existence_confidence,
                const TypeAndConfidence& type_and_confidence,
                const RectangularBoxAndAccuracy& rect_box_and_acc,
                const XyzVectorAndAccuracy& speed_and_acc,
                const XyzVectorAndAccuracy& accel_and_acc);
  sensoris::protobuf::categories::objectdetection::MovableObject*
  generate_proto();
  ~MovableObject();
};

class ObjectDetectionCategory {
 private:
  vector<MovableObject> movable_objects;

 public:
  ObjectDetectionCategory(const vector<MovableObject>& movable_objects);
  sensoris::protobuf::categories::objectdetection::ObjectDetectionCategory*
  generate_proto();
  ~ObjectDetectionCategory();
};

#endif  // OBJECT_DETECTION_CATEGORY_HPP