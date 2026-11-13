#include "../../../../proto_gen/sensoris/protobuf/messages/data.pb.h"
#include "../categories/localization_category.hpp"
#include "../categories/object_detection_category.hpp"

class Origin {
 private:
  Timestamp timestamp;
  PositionAndAccuracy paa;
  RotationAndAccuracy raa;

 public:
  Origin(const Timestamp& timestamp, const PositionAndAccuracy& paa,
         const RotationAndAccuracy& raa);
  sensoris::protobuf::messages::data::EventGroup_Envelope_Origin*
  generate_proto();
  ~Origin();
};

class EventGroupEnvelope {
 private:
  Origin origin;

 public:
  EventGroupEnvelope(const Origin& origin);
  sensoris::protobuf::messages::data::EventGroup_Envelope* generate_proto();
  ~EventGroupEnvelope();
};

class EventGroup {
 private:
  EventGroupEnvelope envelope;
  ObjectDetectionCategory odc;
  LocalizationCategory lc;

 public:
  EventGroup(const EventGroupEnvelope& envelope,
             const ObjectDetectionCategory& odc,
             const LocalizationCategory& lc);
  sensoris::protobuf::messages::data::EventGroup* generate_proto();
  ~EventGroup();
};

class Ids {
 private:
  GoogleStringValue session_id;
  GoogleInt64Value message_id;
  GoogleBoolValue last_message;
  GoogleStringValue vehicle_fleet_id;
  GoogleStringValue vehicle_id;
  GoogleStringValue driver_id;

 public:
  Ids(const string& vehicle_id, const string& session_id,
      const int64_t message_id);
  sensoris::protobuf::messages::data::DataMessage_Envelope_Ids*
  generate_proto();
  ~Ids();
};

class DataMessageEnvelope {
 private:
  Ids ids;

 public:
  DataMessageEnvelope(const Ids& ids);
  sensoris::protobuf::messages::data::DataMessage_Envelope* generate_proto();
  ~DataMessageEnvelope();
};

class DataMessage {
 private:
  DataMessageEnvelope envelope;
  vector<EventGroup> event_group;

 public:
  DataMessage(const DataMessageEnvelope& envelope,
              const vector<EventGroup>& event_group);
  sensoris::protobuf::messages::data::DataMessage* generate_proto();
  ~DataMessage();
};
