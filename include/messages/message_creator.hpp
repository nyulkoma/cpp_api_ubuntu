#ifndef MESSAGE_CREATOR_HPP
#define MESSAGE_CREATOR_HPP

#include <map>
#include <string>
#include <vector>

/**
 * We have to undefine some macro (ERROR, ABSOLUTE, RELATIVE) on Windows
 * because wingdi.h has already defined them and there would be conflicts.
 * MessageType enum in Diagnostic message has an ERROR variable.
 * PositionSystem, OrientationSystem and MotionSystem enum classes have an
 * ABSOLUTE and a RELATIVE variable.
 */
#ifdef ERROR
#undef ERROR
#endif

#ifdef ABSOLUTE
#undef ABSOLUTE
#endif

#ifdef RELATIVE
#undef RELATIVE
#endif

#include "../../proto_gen/data_models/control_protocol/control_protocol.pb.h"
#include "../../proto_gen/data_models/diagnostic_protocol/diagnostic_protocol.pb.h"
#include "../../proto_gen/data_models/diagnostic_protocol/diagnostics_event.pb.h"
#include "../../proto_gen/data_models/diagnostic_protocol/heartbeat.pb.h"
#include "../../proto_gen/data_models/feedback_protocol/feedback_protocol.pb.h"
#include "../../proto_gen/data_models/message_header/message_header.pb.h"
#include "../../proto_gen/data_models/pad_protocol/pad.pb.h"
#include "../../proto_gen/data_models/raw_data/raw_data.pb.h"
#include "../../proto_gen/data_models/sensor_data/raw_sensor_data.pb.h"
#include "../../proto_gen/data_models/sensoris_own_model/sensoris.pb.h"
#include "../../proto_gen/data_models/slam_map/slam_map.pb.h"
#include "../../proto_gen/data_models/traffic_light/traffic_light.pb.h"
#include "../../proto_gen/grpc_models/util/util.pb.h"
#include "../include/messages/sensoris_wrapper/messages/data.hpp"

using namespace std;
using automateddrive::datamodels::control_protocol::protobuf::
    GeneralVehicleControl;
using automateddrive::datamodels::control_protocol::protobuf::
    TorqueVectoringControl;
using automateddrive::datamodels::control_protocol::protobuf::
    TrackedVehicleControl;
using automateddrive::datamodels::control_protocol::protobuf::Trajectory;
using automateddrive::datamodels::control_protocol::protobuf::TrajectoryControl;
using automateddrive::datamodels::control_protocol::protobuf::TrajectoryPoint;
using automateddrive::datamodels::control_protocol::protobuf::TriggerControl;
using automateddrive::datamodels::control_protocol::protobuf::
    VehicleSpecificControl;
using automateddrive::datamodels::control_protocol::protobuf::CommandType;
using automateddrive::datamodels::control_protocol::protobuf::ControlMode;
using automateddrive::datamodels::control_protocol::protobuf::FunctionControl;
using automateddrive::datamodels::control_protocol::protobuf::FunctionControlMessage;
using automateddrive::datamodels::message_header::protobuf::Header;

using automateddrive::datamodels::feedback_protocol::protobuf::FeedbackData;
using automateddrive::datamodels::feedback_protocol::protobuf::FeedbackRequest;
using automateddrive::datamodels::feedback_protocol::protobuf::Measurement;
using automateddrive::datamodels::feedback_protocol::protobuf::Tensor;

using automateddrive::datamodels::diagnostic_protocol::protobuf::
    ConnectionState;
using automateddrive::datamodels::diagnostic_protocol::protobuf::Diagnostic;
using automateddrive::datamodels::diagnostic_protocol::protobuf::LeapStatus;
using automateddrive::datamodels::diagnostic_protocol::protobuf::MessageType;
using automateddrive::datamodels::diagnostic_protocol::protobuf::Misc;
using automateddrive::datamodels::diagnostic_protocol::protobuf::
    SynchronizationInfo;
using automateddrive::datamodels::diagnostic_protocol::protobuf::
    SynchronizationProtocol;
using automateddrive::datamodels::diagnostic_protocol::protobuf::SystemInfo;
using automateddrive::datamodels::diagnostic_protocol::protobuf::SystemMessage;
using automateddrive::datamodels::diagnostic_protocol::protobuf::SystemStatus;

using automateddrive::datamodels::system_monitoring::protobuf::DiagnosticEvent;
using automateddrive::datamodels::system_monitoring::protobuf::EventSeverity;
using automateddrive::datamodels::system_monitoring::protobuf::Heartbeat;
using automateddrive::datamodels::system_monitoring::protobuf::HeartbeatStatus;

using automateddrive::datamodels::raw_data::protobuf::RawData;
using automateddrive::datamodels::sensoris::protobuf::Sensoris;
using automateddrive::datamodels::traffic_light::protobuf::TrafficLightControl;
using automateddrive::datamodels::util::protobuf::StreamRequest;

using automateddrive::datamodels::pad_protocol::protobuf::AerialVehicle;
using automateddrive::datamodels::pad_protocol::protobuf::
    AerialVehicle_FlyingMode;
using automateddrive::datamodels::pad_protocol::protobuf::Detection;
using automateddrive::datamodels::pad_protocol::protobuf::PAD;
using automateddrive::datamodels::pad_protocol::protobuf::Platform;
using automateddrive::datamodels::pad_protocol::protobuf::Platform_GnssStatus;
using automateddrive::datamodels::pad_protocol::protobuf::
    Platform_LocalizationStatus;
using automateddrive::datamodels::pad_protocol::protobuf::Platform_Type;
using automateddrive::datamodels::pad_protocol::protobuf::WheeledVehicle;
using automateddrive::datamodels::shared_messages::protobuf::Acceleration;
using automateddrive::datamodels::shared_messages::protobuf::
    AngularAcceleration;
using automateddrive::datamodels::shared_messages::protobuf::AngularVelocity;
using automateddrive::datamodels::shared_messages::protobuf::Localization;
using automateddrive::datamodels::shared_messages::protobuf::MiscAttributes;
using automateddrive::datamodels::shared_messages::protobuf::ObjectType;
using automateddrive::datamodels::shared_messages::protobuf::Orientation;
using automateddrive::datamodels::shared_messages::protobuf::Position;
using automateddrive::datamodels::shared_messages::protobuf::Position_Utm;
using automateddrive::datamodels::shared_messages::protobuf::Position_Wgs84;
using automateddrive::datamodels::shared_messages::protobuf::RotationVector;
using automateddrive::datamodels::shared_messages::protobuf::Size;
using automateddrive::datamodels::shared_messages::protobuf::Velocity;
using automateddrive::datamodels::shared_messages::protobuf::XyzMatrix3x3;
using automateddrive::datamodels::shared_messages::protobuf::XyzVector;

using automateddrive::datamodels::slam_map::protobuf::CameraIntrinsicParameters;
using automateddrive::datamodels::slam_map::protobuf::EnvironmentalContext;
using automateddrive::datamodels::slam_map::protobuf::MapMetrics;
using automateddrive::datamodels::slam_map::protobuf::ORBSLAM3Map;
using automateddrive::datamodels::slam_map::protobuf::SensorType;
using automateddrive::datamodels::slam_map::protobuf::Settings;
using automateddrive::datamodels::slam_map::protobuf::Weather;

using automateddrive::datamodels::raw_sensor_data::protobuf::RawSensorData;
using automateddrive::datamodels::raw_sensor_data::protobuf::SensorData;
using automateddrive::datamodels::raw_sensor_data::protobuf::SensorData_ExtrinsicParameters;
using automateddrive::datamodels::raw_sensor_data::protobuf::SensorData_IntrinsicParameters;
using automateddrive::datamodels::raw_sensor_data::protobuf::SensorData_Image;
using automateddrive::datamodels::raw_sensor_data::protobuf::SensorData_PointCloud;
using automateddrive::datamodels::raw_sensor_data::protobuf::SensorData_PixelFormat;
using automateddrive::datamodels::raw_sensor_data::protobuf::SensorData_ImageCompression;
using automateddrive::datamodels::raw_sensor_data::protobuf::SensorData_PointCloudBitDepth;
using automateddrive::datamodels::raw_sensor_data::protobuf::SensorData_PointCloudEncoding;
using automateddrive::datamodels::raw_sensor_data::protobuf::SensorData_PointCloudFormat;

/**
 * Message creators for Sensoris message.
 */
class SensorisMessageCreator {
 public:
  typedef sensoris::protobuf::types::spatial::PositionAndAccuracy::
      GeographicMetricCase positionSystem;
  typedef sensoris::protobuf::types::spatial::RotationAndAccuracy::
      EulerQuaternionCase orientationSystem;
  typedef sensoris::protobuf::types::spatial::XyzVectorAndAccuracy::GeometryCase
      motionSystem;
  typedef sensoris::protobuf::categories::objectdetection::
      MovableObject_TypeAndConfidence_Type objectType;

  /**
   * Create a LocalizedVehicle object for Sensoris message. It contains
   * position, orientation, speed, acceleration and orientation rate about
   * the vehicle.
   *
   * @param event_id ID of the event when the vehicle was localized.
   * @param event_timestamp Timestamp of the event in millisecond when the
   * vehicle was localized.
   * @param position Reference to the position vector. UTM [x, y, z] (meter) or
   * WGS84 [longitude, latitude, altitude] (degree, degree, meter).
   * @param orientation Reference to the orientation vector. [yaw, pitch, roll]
   * (degree) They will be converted to [0, 360].
   * @param position_system Vehicle's geographic or metric position system.
   * You can give it with the positionSystem type definition. Options:
   * kGeographicWgs84: World Geodetic System 84.
   * kMetricVehicle: Sensoris vehicle coordinate system.
   * kMetricEventGroup: origin related coordinate system.
   * kMetricEcef: Earth-Centered Earth-Fixed system.
   * @param orientation_system Vehicle's euler orientation system.
   * You can give it with the orientationSystem type definition. Options:
   * kEulerVehicle: Sensoris vehicle coordinate system.
   * kEulerEventGroup: origin related coordinate system.
   * @param speed Reference to the velocity vector. [x, y, z] (m/s)
   * @param acceleration Reference to the acceleration vector. [x, y, z] (m/s^2)
   * @param orientation_rate Reference to the orientation rate vector.
   * [yaw rate, pitch rate, roll rate] (degree/sec)
   * @param motion_system Vehicle's metric motion system.
   * You can give it with the motionSystem type definition. Options:
   * kMetricVehicle: Sensoris vehicle coordinate system.
   * kMetricEventGroup: origin related coordinate system.
   * kMetricOrigin: coordinate system specified by the origin.
   * @param pos_std_dev Reference to the position standard deviation vector.
   * UTM [x, y, z] (meter) or WGS84 [longitude, latitude, altitude] (meter).
   * @param ori_std_dev Reference to the orientation standard deviation vector.
   * [yaw, pitch, roll] (degree)
   * @param speed_std_dev Reference to the velocity standard deviation vector.
   * [x, y, z] (m/s)
   * @param accel_std_dev Reference to the acceleration standard deviation
   * vector. [x, y, z] (m/s^2)
   * @param ori_rate_std_dev Reference to the orientation rate standard
   * deviation vector. [yaw rate, pitch rate, roll rate] (degree/sec)
   * @returns The newly created LocalizedVehicle object.
   */
  static LocalizedVehicle createVehicle(
      const int64_t event_id, const double event_timestamp,
      const vector<double>& position, const vector<double>& orientation,
      const positionSystem position_system = positionSystem::kGeographicWgs84,
      const orientationSystem orientation_system =
          orientationSystem::kEulerEventGroup,
      const vector<double>& speed = vector<double>{0, 0, 0},
      const vector<double>& acceleration = vector<double>{0, 0, 0},
      const vector<double>& orientation_rate = vector<double>{0, 0, 0},
      const motionSystem motion_system = motionSystem::kMetricEventGroup,
      const vector<double>& pos_std_dev = vector<double>{0, 0, 0},
      const vector<double>& ori_std_dev = vector<double>{0, 0, 0},
      const vector<double>& speed_std_dev = vector<double>{0, 0, 0},
      const vector<double>& accel_std_dev = vector<double>{0, 0, 0},
      const vector<double>& ori_rate_std_dev = vector<double>{0, 0, 0});

  /**
   * Create a LocalizedVehicle object for Sensoris message with covariance
   * matrix inputs.
   *
   * @param pos_cov_mtx Reference to the position covariance matrix.
   * Elements should be defined in m^2.
   * @param ori_cov_mtx Reference to the orientation covariance matrix.
   * Elements should be defined in degree^2.
   * @param speed_cov_mtx Reference to the velocity covariance matrix.
   * Elements should be defined in (m/s)^2.
   * @param accel_cov_mtx Reference to the acceleration covariance matrix.
   * Elements should be defined in (m/s^2)^2.
   * @param ori_rate_cov_mtx Reference to the orientation rate covariance
   * matrix. Elements should be defined in (degree/sec)^2.
   * @see createVehicle for the other parameters.
   * @returns The newly created LocalizedVehicle object.
   */
  static LocalizedVehicle createVehicleCovMtx(
      const int64_t event_id, const double event_timestamp,
      const vector<double>& position, const vector<double>& orientation,
      const positionSystem position_system = positionSystem::kGeographicWgs84,
      const orientationSystem orientation_system =
          orientationSystem::kEulerEventGroup,
      const vector<double>& speed = vector<double>{0, 0, 0},
      const vector<double>& acceleration = vector<double>{0, 0, 0},
      const vector<double>& orientation_rate = vector<double>{0, 0, 0},
      const motionSystem motion_system = motionSystem::kMetricEventGroup,
      const double (&pos_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      const double (&ori_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      const double (&speed_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      const double (&accel_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      const double (&ori_rate_cov_mtx)[3][3] = {
          {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

  /**
   * Create a MovableObject object for Sensoris message. It contains several
   * information about the detected object including type, confidence, position,
   * orientation etc.
   *
   * @param event_id ID of the event when the object was detected.
   * @param event_timestamp Timestamp of the event in millisecond when the
   * object was detected.
   * @param object_id ID of the detected object.
   * @param object_type Type of the detected object. You can give it with the
   * objectType type definition. Options (always begins with
   * MovableObject_TypeAndConfidence_Type_): UNKNOWN_TYPE, VEHICLE,
   * VEHICLE_PASSENGER_CAR, VEHICLE_TRUCK, VEHICLE_BUS, VEHICLE_TRAM,
   * VEHICLE_TRAILER, TWO_WHEELER, TWO_WHEELER_MOTORCYCLE, TWO_WHEELER_BICYCLE,
   * PERSON and ANIMAL.
   * @param existence_confidence Confidence of the detection itself.
   * Normalized to [0, 1]. Will be converted to percent.
   * @param type_confidence Confidence of the object type. Normalized to [0, 1].
   * Will be converted to percent.
   * @param position Reference to the position vector. UTM [x, y, z] (meter) or
   * WGS84 [longitude, latitude, altitude] (degree, degree, meter).
   * @param orientation Reference to the orientation vector. [yaw, pitch, roll]
   * (degree) They will be converted to [0, 360].
   * @param position_system Detection's geographic or metric position system.
   * You can give it with the positionSystem type definition. Options:
   * kGeographicWgs84: World Geodetic System 84.
   * kMetricVehicle: Sensoris vehicle coordinate system.
   * kMetricEventGroup: origin related coordinate system.
   * kMetricEcef: Earth-Centered Earth-Fixed system.
   * @param orientation_system Detection's euler orientation system.
   * You can give it with the orientationSystem type definition. Options:
   * kEulerVehicle: Sensoris vehicle coordinate system.
   * kEulerEventGroup: origin related coordinate system.
   * @param size Reference to the size vector. [x, y, z] (meter)
   * @param speed Reference to the velocity vector. [x, y, z] (m/s)
   * @param acceleration Reference to the acceleration vector. [x, y, z] (m/s^2)
   * @param motion_system Detection's metric motion system.
   * You can give it with the motionSystem type definition. Options:
   * kMetricVehicle: Sensoris vehicle coordinate system.
   * kMetricEventGroup: origin related coordinate system.
   * kMetricOrigin: coordinate system specified by the origin.
   * @param pos_std_dev Reference to the position standard deviation vector.
   * UTM [x, y, z] (meter) or WGS84 [longitude, latitude, altitude] (meter).
   * @param ori_std_dev Reference to the orientation standard deviation vector.
   * [yaw, pitch, roll] (degree)
   * @param size_std_dev Reference to the size standard deviation vector.
   * [x, y, z] (meter)
   * @param speed_std_dev Reference to the velocity standard deviation vector.
   * [x, y, z] (m/s)
   * @param accel_std_dev Reference to the acceleration standard deviation
   * vector. [x, y, z] (m/s^2)
   * @returns The newly created MovableObject object.
   */
  static MovableObject createDetection(
      const int64_t event_id, const double event_timestamp,
      const int64_t object_id, const objectType object_type,
      const double existence_confidence, const double type_confidence,
      const vector<double>& position, const vector<double>& orientation,
      const vector<double>& size,
      const positionSystem position_system = positionSystem::kMetricEcef,
      const orientationSystem orientation_system =
          orientationSystem::kEulerEventGroup,
      const vector<double>& speed = vector<double>{0, 0, 0},
      const vector<double>& acceleration = vector<double>{0, 0, 0},
      const motionSystem motion_system = motionSystem::kMetricEventGroup,
      const vector<double>& pos_std_dev = vector<double>{0, 0, 0},
      const vector<double>& ori_std_dev = vector<double>{0, 0, 0},
      const vector<double>& size_std_dev = vector<double>{0, 0, 0},
      const vector<double>& speed_std_dev = vector<double>{0, 0, 0},
      const vector<double>& accel_std_dev = vector<double>{0, 0, 0});

  /**
   * Create a MovableObject object for Sensoris message with covariance matrix
   * inputs.
   *
   * @param pos_cov_mtx Reference to the position covariance matrix.
   * Elements should be defined in m^2.
   * @param ori_cov_mtx Reference to the orientation covariance matrix.
   * Elements should be defined in degree^2.
   * @param size_cov_mtx Reference to the size covariance matrix.
   * Elements should be defined in m^2.
   * @param speed_cov_mtx Reference to the velocity covariance matrix.
   * Elements should be defined in (m/s)^2.
   * @param accel_cov_mtx Reference to the acceleration covariance matrix.
   * Elements should be defined in (m/s^2)^2.
   * @see createDetection for the other parameters.
   * @returns The newly created MovableObject object.
   */
  static MovableObject createDetectionCovMtx(
      const int64_t event_id, const double event_timestamp,
      const int64_t object_id, const objectType object_type,
      const double existence_confidence, const double type_confidence,
      const vector<double>& position, const vector<double>& orientation,
      const vector<double>& size,
      const positionSystem position_system = positionSystem::kMetricEcef,
      const orientationSystem orientation_system =
          orientationSystem::kEulerEventGroup,
      const vector<double>& speed = vector<double>{0, 0, 0},
      const vector<double>& acceleration = vector<double>{0, 0, 0},
      const motionSystem motion_system = motionSystem::kMetricEventGroup,
      const double (&pos_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      const double (&ori_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      const double (&size_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      const double (&speed_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      const double (&accel_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

  /**
   * Create an Origin object for Sensoris message. It is the origin of the
   * coordinate system.
   *
   * @param timestamp Temporal origin's timestamp in milliseconds.
   * @param position_longitude_x WGS84 longitude in degree or UTM x in meter.
   * @param position_latitude_y WGS84 latitude in degree or UTM y in meter.
   * @param position_altitude_z WGS84 altitude or UTM z in meter.
   * @param yaw Yaw in degree. Will be converted to [0, 360].
   * @param pitch Pitch in degree. Will be converted to [0, 360].
   * @param roll Roll in degree. Will be converted to [0, 360].
   * @param position_system Origin's geographic or metric position system.
   * You can give it with the positionSystem type definition. Options:
   * kGeographicWgs84: World Geodetic System 84.
   * kMetricVehicle: Sensoris vehicle coordinate system.
   * kMetricEventGroup: origin related coordinate system.
   * kMetricEcef: Earth-Centered Earth-Fixed system.
   * @param orientation_system Origin's euler orientation system.
   * You can give it with the orientationSystem type definition. Options:
   * kEulerVehicle: Sensoris vehicle coordinate system.
   * kEulerEventGroup: origin related coordinate system.
   * @param pos_lon_x_std_dev WGS84 longitude or UTM x standard deviation in
   * meter.
   * @param pos_lat_y_std_dev WGS84 latitude or UTM y standard deviation in
   * meter.
   * @param pos_alt_z_std_dev WGS84 altitude or UTM z standard deviation in
   * meter.
   * @param yaw_std_dev Yaw standard deviation in degree.
   * @param pitch_std_dev Pitch standard deviation in degree.
   * @param roll_std_dev Roll standard deviation in degree.
   * @returns The newly created Origin object.
   */
  static Origin createSystemOrigin(
      const double timestamp, const double position_longitude_x,
      const double position_latitude_y, const double position_altitude_z,
      const double yaw, const double pitch, const double roll,
      const positionSystem position_system = positionSystem::kGeographicWgs84,
      const orientationSystem orientation_system =
          orientationSystem::kEulerEventGroup,
      const double pos_lon_x_std_dev = 0.0,
      const double pos_lat_y_std_dev = 0.0,
      const double pos_alt_z_std_dev = 0.0, const double yaw_std_dev = 0.0,
      const double pitch_std_dev = 0.0, const double roll_std_dev = 0.0);

  /**
   * Create an Origin object for Sensoris message with covariance matrix inputs.
   *
   * @param pos_cov_mtx Reference to the position covariance matrix.
   * Elements should be defined in m^2.
   * @param ori_cov_mtx Reference to the orientation covariance matrix.
   * Elements should be defined in degree^2.
   * @see createSystemOrigin for the other parameters.
   * @returns The newly created Origin object.
   */
  static Origin createSystemOriginCovMtx(
      const double timestamp, const double position_longitude_x,
      const double position_latitude_y, const double position_altitude_z,
      const double yaw, const double pitch, const double roll,
      const positionSystem position_system = positionSystem::kGeographicWgs84,
      const orientationSystem orientation_system =
          orientationSystem::kEulerEventGroup,
      const double (&pos_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      const double (&ori_cov_mtx)[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

  /**
   * Create DataMessage object for Sensoris message. It is the main message in
   * the Sensoris standard. Now we fill it with some id, origin, movable objects
   * and localized vehicles.
   *
   * @param platform_id ID of the sender platform.
   * @param session_id ID of the message group that belongs to the same
   * platform.
   * @param message_id Message sequence number ID.
   * @param origin Reference to the earlier created erigin with the
   * createSystemOrigin method.
   * @param detections Reference to the vector of earlier created detections
   * with the createDetection method.
   * @param vehicles Reference to the vector of earlier created vehicles with
   * the createVehicle method.
   * @returns The newly created DataMessage object.
   */
  static DataMessage createDataMessage(
      const string& platform_id, const string& session_id,
      const int64_t message_id, const Origin& origin,
      const vector<MovableObject>& detections = vector<MovableObject>(),
      const vector<LocalizedVehicle>& vehicles = vector<LocalizedVehicle>());

  /**
   * Create a Sensoris message. We have created a protobuf message called
   * Sensoris. It contains a Header (our definition) and a DataMessage (defined
   * by sensoris specification).
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param data_message Reference to the earlier created DataMessage object
   * with the createDataMessage method.
   * @returns The newly created Sensoris message.
   */
  static Sensoris createSensorisMessage(Header* header,
                                        DataMessage& data_message);

 private:
  /**
   * Create a PositionAndAccuracy object for Sensoris message.
   *
   * @param position_longitude_x WGS84 longitude (degree) or UTM x (meter)
   * value.
   * @param position_latitude_y WGS84 latitude (degree) or UTM y (meter) value.
   * @param position_altitude_z WGS84 altitude or UTM z value in meter.
   * @param covariance_matrix Reference to the covariance matrix.
   * Elements should be defined in m^2.
   * @param system Geographic or metric position system. Options:
   * kGeographicWgs84: World Geodetic System 84.
   * kMetricVehicle: Sensoris vehicle coordinate system.
   * kMetricEventGroup: origin related coordinate system.
   * kMetricEcef: Earth-Centered Earth-Fixed system.
   * @returns The newly created PositionAndAccuracy object.
   */
  static PositionAndAccuracy createPositionAndAccuracy(
      const double position_longitude_x, const double position_latitude_y,
      const double position_altitude_z, const double (&covariance_matrix)[3][3],
      const positionSystem system);

  /**
   * Create a RotationAndAccuracy object for Sensoris message.
   *
   * @param yaw, pitch, roll Rotation angles in degree. They will be converted
   * to [0, 360].
   * @param covariance_matrix Reference to the covariance matrix.
   * Elements should be defined in degree^2.
   * @param system Euler orientation system. Options:
   * kEulerVehicle: Sensoris vehicle coordinate system.
   * kEulerEventGroup: origin related coordinate system.
   * @returns The newly created RotationAndAccuracy object.
   */
  static RotationAndAccuracy createRotationAndAccuracy(
      const double yaw, const double pitch, const double roll,
      const double (&covariance_matrix)[3][3], const orientationSystem system);

  /**
   * Create an XyzVectorAndAccuracy object for Sensoris message.
   *
   * @param x, y, z Coordinates of the vector.
   * @param covariance_matrix Reference to the covariance matrix.
   * Elements should be defined in m^2 (for size), (m/s)^2 (for speed) or
   * (m/s^2)^2 (for acceleration).
   * @param system Metric motion system. Options:
   * kMetricVehicle: Sensoris vehicle coordinate system.
   * kMetricEventGroup: origin related coordinate system.
   * kMetricOrigin: coordinate system specified by the origin.
   * @param unit Measurement unit of the coordinates.
   * @param resolution Resolution of the coordinates.
   * @param std_dev_unit Measurement unit of standard deviations of the
   * coordinates.
   * @param std_dev_resolution Resolution of standard deviations of the
   * coordinates.
   * @param range_min, range_max Minimum and maximum value of the coordinates.
   * @param std_dev_range_min, std_dev_range_max Minimum and maximum value of
   * standard deviations of the coordinates.
   * @returns The newly created XyzVectorAndAccuracy object.
   */
  static XyzVectorAndAccuracy createXyzVectorAndAccuracy(
      const double x, const double y, const double z,
      const double (&covariance_matrix)[3][3], const motionSystem system,
      const string& unit = "", const double resolution = 1.0,
      const string& std_dev_unit = "", const double std_dev_resolution = 1.0,
      const int64_t range_min = numeric_limits<int64_t>::min(),
      const int64_t range_max = numeric_limits<int64_t>::max(),
      const int64_t std_dev_range_min = numeric_limits<int64_t>::min(),
      const int64_t std_dev_range_max = numeric_limits<int64_t>::max());
};

/**
 * Message creators for feedback messages.
 */
class FeedbackMessageCreator {
 private:
  /**
   * Create a measurement tensor for FeedbackData message.
   *
   * @param measured_data Reference to the measured data vector.
   * @returns Pointer to the newly allocated Tensor object.
   */
  static Tensor* createTensor(const vector<double>& measured_data);

  /**
   * Create a Measurement object for FeedbackData message.
   *
   * @param measured_data Reference to the measured data vector.
   * @returns Pointer to the newly allocated Measurement object.
   */
  static Measurement* createMeasurement(const vector<double>& measured_data);

 public:
  /**
   * Create FeedbackData message. Used for collect informations about a vehicle.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param fqdns Reference to the vector of Fully Qualified Domain Names of
   * measured values. Form of this fqdns is
   * "cs.measurements.vehicledynamics.groupId.channelId". For example
   * "cs.measurements.vehicledynamics.motion.latitude" relates to the latitude
   * coordinate of the vehicle.
   * @param measured_data Reference to the vector of measured values.
   * @param measurement_units Reference to the vector of units of measured
   * values. Form of this units is "cs.units.groupId.unitId". For example
   * "cs.units.angle.degree" relates to the degree unit.
   * @param covariance Reference to the vector of covariance values.
   * @param covariance_units Reference to the vector of units of covariance
   * values. Its form is the same as measurement_units'.
   * @returns The newly created FeedbackData object.
   */
  static FeedbackData createFeedbackDataMessage(
      Header* header, const vector<string>& fqdns = vector<string>(),
      const vector<double>& measured_data = vector<double>(),
      const vector<string>& measurement_units = vector<string>(),
      const vector<double>& covariance = vector<double>(),
      const vector<string>& covariance_units = vector<string>());

  /**
   * Create FeedbackRequest message. Used for requesting informations about a
   * vehicle.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param fqdns Reference to the vector of Fully Qualified Domain Names of
   * measured values. Form of this fqdns is
   * "cs.measurements.vehicledynamics.groupId.channelId". For example
   * "cs.measurements.vehicledynamics.motion.latitude" relates to the latitude
   * coordinate of the vehicle.
   * @param measurement_units Reference to the vector of units of measured
   * values. Form of this units is "cs.units.groupId.unitId". For example
   * "cs.units.angle.degree" relates to the degree unit.
   * @param frequency The data sending frequency in Hz.
   * @returns The newly created FeedbackRequest object.
   */
  static FeedbackRequest createFeedbackRequestMessage(
      Header* header, const vector<string>& fqdns = vector<string>(),
      const vector<string>& measurement_units = vector<string>(),
      const double frequency = 1.0);
};

/**
 * Message creators for control messages.
 */
class ControlMessageCreator {
 public:
  /**
   * Create a WGS84 based point for a trajectory.
   *
   * @param longitude Longitude value in degree.
   * @param latitude Latitude value in degree.
   * @param altitude Altitude value in meter.
   * @param timestamp Timestamp when the vehicle has to reach the point.
   * @param yaw Yaw angle in degree.
   * @param pitch Pitch angle in degree.
   * @param roll Roll angle in degree.
   * @returns Pointer to the newly created TrajectoryPoint object.
   */
  static TrajectoryPoint* createWGS84BasedTrajectoryPoint(
      const double longitude, const double latitude, const double altitude,
      const uint64_t timestamp = 0, const double yaw = 0.0,
      const double pitch = 0.0, const double roll = 0.0);

  /**
   * Create an UTM based point for a trajectory.
   *
   * @param zone_no Number of the UTM zone where the point is
   * located.
   * @param zone_letter Letter of the UTM zone where the point is
   * located.
   * @param x X value in meter.
   * @param y Y value in meter.
   * @param z Z value in meter.
   * @param timestamp Timestamp when the vehicle has to reach the point.
   * @param yaw Yaw angle in degree.
   * @param pitch Pitch angle in degree.
   * @param roll Roll angle in degree.
   * @returns Pointer to the newly created TrajectoryPoint object.
   */
  static TrajectoryPoint* createUTMBasedTrajectoryPoint(
      const uint32_t zone_no, const uint32_t zone_letter, const double x,
      const double y, const double z, const uint64_t timestamp = 0,
      const double yaw = 0.0, const double pitch = 0.0,
      const double roll = 0.0);

  /**
   * Create a velocity based point for a trajectory.
   *
   * @param x X component of the velocity vector in m/s.
   * @param y Y component of the velocity vector in m/s.
   * @param z Z component of the velocity vector in m/s.
   * @param timestamp Timestamp when the vehicle has to reach the point.
   * @param yaw Yaw angle in degree.
   * @param pitch Pitch angle in degree.
   * @param roll Roll angle in degree.
   * @returns Pointer to the newly created TrajectoryPoint object.
   */
  static TrajectoryPoint* createVelocityBasedTrajectoryPoint(
      const double x, const double y, const double z,
      const uint64_t timestamp = 0, const double yaw = 0.0,
      const double pitch = 0.0, const double roll = 0.0);

  /**
   * Create an acceleration based point for a trajectory.
   *
   * @param x X component of the acceleration vector in m/s^2.
   * @param y Y component of the acceleration vector in m/s^2.
   * @param z Z component of the acceleration vector in m/s^2.
   * @param timestamp Timestamp when the vehicle has to reach the point.
   * @param yaw Yaw angle in degree.
   * @param pitch Pitch angle in degree.
   * @param roll Roll angle in degree.
   * @returns Pointer to the newly created TrajectoryPoint object.
   */
  static TrajectoryPoint* createAccelerationBasedTrajectoryPoint(
      const double x, const double y, const double z,
      const uint64_t timestamp = 0, const double yaw = 0.0,
      const double pitch = 0.0, const double roll = 0.0);

  /**
   * Create a point for a trajectory.
   *
   * @param timestamp Timestamp when the vehicle has to reach the point.
   * @param position_utm_zone_no Number of the UTM zone where the point is
   * located.
   * @param position_utm_zone_letter Letter of the UTM zone where the point is
   * located.
   * @param position_x_easting_lon UTM x (in meter) or WGS84 longitude (in
   * degree) value.
   * @param position_y_northing_lat UTM y (in meter) or WGS84 latitude (in
   * degree) value.
   * @param position_z_altitude UTM z (in meter) or WGS84 altitude (in meter)
   * value.
   * @param yaw Yaw angle in degree.
   * @param pitch Pitch angle in degree.
   * @param roll Roll angle in degree.
   * @param velocity_x_easting_lon X component of the velocity vector in m/s.
   * @param velocity_y_northing_lat Y component of the velocity vector in m/s.
   * @param velocity_z_altitude Z component of the velocity vector in m/s.
   * @param acceleration_x_easting_lon X component of the acceleration vector in
   * m/s^2.
   * @param acceleration_y_northing_lat Y component of the acceleration vector
   * in m/s^2.
   * @param acceleration_z_altitude Z component of the acceleration vector in
   * m/s^2.
   * @param curvature Curvature of the trajectory to the next point in 1/m.
   * @returns Pointer to the newly created TrajectoryPoint object.
   */
  static TrajectoryPoint* createTrajectoryPoint(
      const uint64_t timestamp = 0, const uint32_t position_utm_zone_no = 0,
      const uint32_t position_utm_zone_letter = 0,
      const double position_x_easting_lon = 0.0,
      const double position_y_northing_lat = 0.0,
      const double position_z_altitude = 0.0, const double yaw = 0.0,
      const double pitch = 0.0, const double roll = 0.0,
      const double velocity_x_easting_lon = 0.0,
      const double velocity_y_northing_lat = 0.0,
      const double velocity_z_altitude = 0.0,
      const double acceleration_x_easting_lon = 0.0,
      const double acceleration_y_northing_lat = 0.0,
      const double acceleration_z_altitude = 0.0, const double curvature = 0.0);

  /**
   * Create a trajectory for TrajectoryControl message.
   *
   * @param number_of_points Number of points of the trajectory.
   * @param descriptor_mask A binary mask which is used for selecting the
   * appropriate descriptor of the trajectory. Only the last four bit counts.
   * 4th is the velocity, 3rd is the orientation, 2nd is the position and
   * 1st is the timestamp. For example 6 (0x6 or 0b0110) means that only the
   * position and the orientation have to be taken account.
   * @param trajectory_points Reference to the vector of trajectory points.
   * @returns Pointer to the newly created Trajectory object.
   */
  static Trajectory* createTrajectory(
      const uint32_t number_of_points, const uint32_t descriptor_mask,
      const vector<TrajectoryPoint*>& trajectory_points);

  /**
   * Create TrajectoryControl message. Used for high level vehicle control.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param normal_trajectory Pointer to the trajectory which will be used at
   * normal conditions.
   * @param emergency_trajectory Pointer to the trajectory which will be used
   * at emergency situations.
   * @returns The newly created TrajectoryControl object.
   */
  static TrajectoryControl createTrajectoryControlMessage(
      Header* header, Trajectory* normal_trajectory,
      Trajectory* emergency_trajectory = nullptr);

  /**
   * Create GeneralVehicleControl message. Can be used to control any type of
   * vehicle.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param curvature Reciprocal of the rotation radius of vehicle in 1/m.
   * Positive for left rotation, negative for right rotation.
   * @param velocity Speed of vehicle in m/s or km/h.
   * @returns The newly created GeneralVehicleControl object.
   */
  static GeneralVehicleControl createGeneralVehicleControlMessage(
      Header* header, const double curvature = 0.0,
      const double velocity = 0.0);

  /**
   * Create VehicleSpecificControl message. Used for controlling a wheeled
   * vehicle.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param vehicle_id ID of the vehicle.
   * @param steering Steering angle in degree.
   * @param brake Position of the break pedal in % or millimeter.
   * @param acceleration Position of the throttle pedal in % or millimeter or
   * the acceleration command in m/s or km/h.
   * @returns The newly created VehicleSpecificControl object.
   */
  static VehicleSpecificControl createVehicleSpecificControlMessage(
      Header* header, const string& vehicle_id = "",
      const double steering = 0.0, const double brake = 0.0,
      const double acceleration = 0.0);

  /**
   * Create TriggerControl message. Used for triggering an event in a vehicle.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param vehicle_id ID of the vehicle.
   * @param trigger_value A mask of the trigger channels. For example 16 (0x10
   * or 0b10000) means that the fifth channel will be triggered.
   * @returns The newly created TriggerControl object.
   */
  static TriggerControl createTriggerControlMessage(
      Header* header, const string& vehicle_id = "",
      const uint32_t trigger_value = 0);

  /**
   * Create TrackedVehicleControl message. Used for controlling a tracked
   * vehicle.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param vehicle_id ID of the vehicle.
   * @param left_track_command Command of the left track in % or Newton.
   * @param right_track_command Command of the right track in % or Newton.
   * @returns The newly created TrackedVehicleControl object.
   */
  static TrackedVehicleControl createTrackedVehicleControlMessage(
      Header* header, const string& vehicle_id = "",
      const double left_track_command = 0.0,
      const double right_track_command = 0.0);

  /**
   * Create TorqueVectoringControl message. Used for torque vectoring control
   * of a vehicle.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param vehicle_id ID of the vehicle.
   * @param front_left_motor_torque Torque of motor front left in Nm.
   * @param front_right_motor_torque Torque of motor front right in Nm.
   * @param rear_left_motor_torque Torque of motor rear left in Nm.
   * @param rear_right_motor_torque Torque of motor rear right in Nm.
   * @param yaw_torque Additional yaw torque by TV in Nm.
   * @param controller_proportional_gain Controller gain of TV controller:
   * proportional part.
   * @param controller_integral_gain Controller gain of TV controller:
   * integral part.
   * @param stable_velocity_x Driving velocity in m/s to remain stable.
   * @param torque_vectoring_settings Setting of TV like value 0 would be
   * baseline, value 1 meaning other TV characteristics and so on.
   * @param road_friction_coefficient Road friciton value between 0 and 1.
   * @param reference_yaw_rate Reference yaw rate in deg/s for TV Controller.
   * @returns The newly created TorqueVectoringControl object.
   */
  static TorqueVectoringControl createTorqueVectoringControlMessage(
      Header* header, const string& vehicle_id = "",
      const double front_left_motor_torque = 0.0,
      const double front_right_motor_torque = 0.0,
      const double rear_left_motor_torque = 0.0,
      const double rear_right_motor_torque = 0.0,
      const double yaw_torque = 0.0,
      const double controller_proportional_gain = 0.0,
      const double controller_integral_gain = 0.0,
      const double stable_velocity_x = 0.0,
      const uint32_t torque_vectoring_settings = 0,
      const double road_friction_coefficient = 0.0,
      const double reference_yaw_rate = 0.0);

  static FunctionControlMessage createFunctionControlMessage(
      Header* header, const CommandType command_type,
      const ControlMode control_mode,
      MiscAttributes* misc = nullptr);
};

/**
 * Message creators for Diagnostic message.
 */
class DiagnosticMessageCreator {
 public:
  /**
   * Create a Misc object for Diagnostic message. It contains informations
   * about arbitrary attributes of the actual system.
   *
   * @param arbitrary_attribute_name Name of the attribute.
   * @param arbitrary_attribute_unit Unit of the attribute.
   * @param arbitrary_attribute_value Value of the attribute.
   * @param arbitrary_attribute_variance_unit Unit of the variance of the
   * attribute.
   * @param arbitrary_attribute_variance_value Value of the variance of the
   * attribute.
   * @returns Pointer to the newly allocated Misc object.
   */
  static Misc* createMisc(
      const string& arbitrary_attribute_name,
      const string& arbitrary_attribute_unit,
      const uint32_t arbitrary_attribute_value,
      const string& arbitrary_attribute_variance_unit = "",
      const uint32_t arbitrary_attribute_variance_value = 0);

  /**
   * Create a SynchronizationInfo object for Diagnostic message. It contains
   * informations about the synchronization of the actual system.
   *
   * @param sync_source IP or DNS address of the synchronization source.
   * @param sync_protocol Synchronization protocol. Can be NTP, SNTP or PTP.
   * @param stratum Synchronization source's distance in a network hierarchy.
   * For example stratum=1 means it is a local source.
   * @param leap_status Status of the handling of leap seconds. Can be NORMAL,
   * INSERT_SECOND, DELETE_SECOND or NOT_SYNCHRONIZED.
   * @param system_clock_precision Precision of the system clock in second.
   * @param polling_interval The rate at which the source is being polled.
   * @param root_delay Time needed for polling in second.
   * @param root_dispersion Deviation of the polling in second.
   * @param system_time_offset Current time offset in second.
   * @param last_sync_timestamp Timestamp of the last successful synchronization
   * in millisecond.
   * @param time_since_last_sync Time since last successful synchronization
   * in second.
   * @returns Pointer to the newly allocated SynchronizationInfo object.
   */
  static SynchronizationInfo* createSynchronizationInfo(
      const string& sync_source, const SynchronizationProtocol sync_protocol,
      const uint32_t stratum, const LeapStatus leap_status,
      const double system_clock_precision, const double polling_interval,
      const double root_delay, const double root_dispersion,
      const double system_time_offset, const uint64_t last_sync_timestamp,
      const double time_since_last_sync);

  /**
   * Create a SystemMessage object for Diagnostic message.
   *
   * @param type Type of the message which can be DEBUG, INFO, WARNING,
   * ERROR and CRITICAL.
   * @param message An important message about the system.
   * @returns Pointer to the newly allocated SystemMessage object.
   */
  static SystemMessage* createSystemMessage(const MessageType type,
                                            const string& message);

  /**
   * Create a ConnectionState object for Diagnostic message.
   *
   * @param alive Status of the connection.
   * @param last_alive_timestamp Timestamp of the last alive state.
   * @param latency Latency of the connection in second.
   * @param bandwidth Bandwidth of the connection in Mbit/s.
   * @returns Pointer to the newly allocated SystemMessage object.
   */

  static ConnectionState createConnectionState(
      const bool alive, const uint64_t last_alive_timestamp,
      const double latency, const double bandwidth);

  /**
   * Create a SystemInfo object for Diagnostic message.
   *
   * @param validity Latest timestamp when the status of the system was RUNNING.
   * @param system_id, system_name, system_type ID, name and type of the system.
   * @param status Actual status of the system. Options:
   * RUNNING, DISCONNECTED, FAULTY, DEGRADED, IDLE, MAINTENANCE and UNKNOWN.
   * @param system_process_data Does the system process any data?
   * @param system_collect_metadata, system_collect_rawdata Does the system
   * collect any metadata / raw data?
   * @param system_comm_metadata, system_comm_rawdata Does the system transmit
   * any metadata / raw data?
   * @param connections Reference to the network connection map of the system.
   * Format of the key is protocol:ip:port, for example tcp:192.168.1.11:5000.
   * @param system_messages Reference to the vector of messages about the
   * system.
   * @param sync_info Ponter to the synchronization information about the
   * system.
   * @param miscs Reference to the vector of miscellaneous attributes of the
   * system.
   * @param subsystems Reference to the vector of subsystems.
   * @returns Pointer to the newly allocated SystemInfo object.
   */
  static SystemInfo* createSystemInfo(
      const uint64_t validity, const string& system_id,
      const string& system_name, const string& system_type,
      const SystemStatus status, const bool system_process_data = false,
      const bool system_collect_metadata = false,
      const bool system_collect_rawdata = false,
      const bool system_comm_metadata = false,
      const bool system_comm_rawdata = false,
      const map<string, ConnectionState>& connections =
          map<string, ConnectionState>(),
      const vector<SystemMessage*>& system_messages = vector<SystemMessage*>(),
      SynchronizationInfo* sync_info = nullptr,
      const vector<Misc*>& miscs = vector<Misc*>(),
      const vector<SystemInfo*>& subsystems = vector<SystemInfo*>());

  /**
   * Create Diagnostic message. Used for monitoring systems.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param system_info Pointer to the earlier created system info with the
   * createSystemInfo method.
   * @returns The newly created Diagnostic message.
   */
  static Diagnostic createDiagnosticMessage(Header* header,
                                            SystemInfo* system_info);

  static DiagnosticEvent createDiagnosticEventMessage(Header* header,
                                                      EventSeverity severity,
                                                      string message);

  static Heartbeat createHeartbeatMessage(Header* header,
                                          HeartbeatStatus status);
};

/**
 * Message creator for RawData message.
 */
class RawDataMessageCreator {
 public:
  /**
   * Create a RawData message. It contains only raw data bytes.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param data Raw data bytes.
   * @returns The newly created RawData message.
   */
  static RawData createRawDataMessage(Header* header, const string& data);
};

/**
 * Message creator for TrafficLightControl message.
 */
class TrafficLightMessageCreator {
 public:
  /**
   * Create a TrafficLightControl message. When the controller_program_cmd is
   * set, bulb_frequency_cmd and bulb_fill_factor_cmd are not relevant. Send a
   * "halt" command before bulb-level controlling. bulb_frequency_cmd = -1 turns
   * off the bulb. bulb_frequency_cmd = 0 turns on the bulb.
   * bulb_fill_factor_cmd has to be normalized to [0, 1] where 0 means 0% and
   * 1 means 100% fill factor.
   *
   * @param header Pointer to the earlier created header with the createHeader
   * method.
   * @param controller_guid ID of the PLC controller.
   * @param signal_group_suid ID of the signal group.
   * @param signal_head_suid ID of the signal head.
   * @param signal_bulb_suid ID of the signal bulb.
   * @param controller_program_cmd Program command to execute by the controller.
   * @param bulb_frequency_cmd Flashing frequency of the selected bulb.
   * @param bulb_fill_factor_cmd Fill factor of the selected bulb.
   * @returns The newly created TrafficLightControl message.
   */
  static TrafficLightControl createTrafficLightControlMessage(
      Header* header, const string& controller_guid = "",
      const string& signal_group_suid = "", const string& signal_head_suid = "",
      const string& signal_bulb_suid = "",
      const string& controller_program_cmd = "",
      const double bulb_frequency_cmd = 0.0,
      const double bulb_fill_factor_cmd = 0.0);
};

/**
 * Message creators for PAD (Platform And Detection) message.
 * Each method is static, so they can be called using the class name itself.
 * For example PADMessageCreator::createPosition(...)
 * Here only descriptions about the usage of methods can be found.
 * Details of the message fields are in proto files.
 */
class PADMessageCreator {
 private:
  /**
   * Check if a value is within a range or not.
   *
   * @param name Name of the variable.
   * @param value The value to be checked.
   * @param minimum Minimum value of the range.
   * @param maximum Maximum value of the range.
   * @returns The value if it is within the range.
   * @throws out_of_range If the value is not within the range.
   */
  static double checkValidity(
      const string& name, const double value,
      const int64_t minimum = numeric_limits<int64_t>::min(),
      const int64_t maximum = numeric_limits<int64_t>::max());

  /**
   * Create a MiscAttributes object. Values of the input map will be
   * added to the right map.
   *
   * @param attributes The map which contains miscellaneous attributes.
   * @returns nullptr if the size of the input map is equal to 0 else
   * the pointer to the newly created MiscAttributes object.
   */
  static MiscAttributes* createMiscAttributes(
      const map<string, const char*>& strings = map<string, const char*>(),
      const map<string, int>& integers = map<string, int>(),
      const map<string, double>& floating_points = map<string, double>(),
      const map<string, bool>& booleans = map<string, bool>());

 public:
  /**
   * Possible position systems. Used to create position object.
   */
  enum class PositionSystem { UTM, WGS84, RELATIVE };

  /**
   * Possible orientation systems. Used to create orientation object.
   */
  enum class OrientationSystem { ABSOLUTE, RELATIVE };

  /**
   * Possible motion systems. Used to create velocity, acceleration,
   * angular velocity and angular acceleration object.
   */
  enum class MotionSystem { ABSOLUTE, LOCAL, RELATIVE };

  /**
   * Create a deviation vector.
   *
   * @param x The x element of the vector.
   * @param y The y element of the vector.
   * @param z The z element of the vector.
   * @returns Pointer to the created deviation vector.
   */
  static XyzVector* createDeviationVector(const float x, const float y,
                                          const float z);

  /**
   * Create a 3x3 covariance matrix.
   *
   * @param xx, xy, xz First row of the matrix.
   * @param yx, yy, yz Second row of the matrix.
   * @param zx, zy, zz Third row of the matrix.
   * @returns Pointer to the created covariance matrix.
   */
  static XyzMatrix3x3* createCovarianceMatrix(const float xx, const float xy,
                                              const float xz, const float yx,
                                              const float yy, const float yz,
                                              const float zx, const float zy,
                                              const float zz);

  /**
   * Create a position object without covariance or deviation.
   * The translation vector is optional.
   *
   * @param position_system The position system in which the coordinates
   * are interpreted. For example: PADMessageCreator::PositionSystem::UTM
   * @param longitude_easting_x WGS84 longitude in degree within [-180, 180]
   * or UTM easting in meter within [166000, 834000] or
   * relative x coordinate in meter.
   * @param latitude_northing_y WGS84 latitude in degree within [-90, 90] or
   * UTM northing in meter within [0, 10000000] or
   * relative y coordinate in meter.
   * @param altitude_z WGS84 altitude value or relative z coordinate in meter.
   * @param utm_zone_number Number of the UTM zone from 1 to 60.
   * Mandatory for UTM, unused in WGS84 and relative coordinate systems.
   * @param utm_zone_letter Letter of the UTM zone from A to Z.
   * Mandatory for UTM, unused in WGS84 and relative coordinate systems.
   * @param translation_x X element of the translation vector.
   * @param translation_y Y element of the translation vector.
   * @param translation_z Z element of the translation vector.
   * @returns Pointer to the created position object.
   * @throws invalid_argument In case of UTM position system when the zone
   * number or letter has not been set or the letter is not an alphabetic
   * character.
   * @throws out_of_range UTM easting, northing, zone number, WGS84 longitude
   * or latitude is outside the range.
   */
  static Position* createPosition(
      const PositionSystem position_system, const double longitude_easting_x,
      const double latitude_northing_y, const double altitude_z,
      const uint32_t utm_zone_number = 0, const string& utm_zone_letter = "",
      const float translation_x = 0.0, const float translation_y = 0.0,
      const float translation_z = 0.0);

  /**
   * Create a position object with covariance matrix.
   * The translation vector is optional.
   *
   * @param covariance 3x3 covariance matrix. Each element is in meter squared.
   * Can be created with the createCovarianceMatrix method.
   * @see createPosition for the other parameters.
   * @returns Pointer to the created position object.
   */
  static Position* createPositionWithCovariance(
      const PositionSystem position_system, const double longitude_easting_x,
      const double latitude_northing_y, const double altitude_z,
      XyzMatrix3x3* covariance, const uint32_t utm_zone_number = 0,
      const string& utm_zone_letter = "", const float translation_x = 0.0,
      const float translation_y = 0.0, const float translation_z = 0.0);

  /**
   * Create a position object with standard deviation vector.
   * Deviation vector will be converted to covariance matrix.
   * For example (x, y, z) -> (x^2, 0, 0,
   *                           0, y^2, 0,
   *                           0, 0, z^2)
   * The translation vector is optional.
   *
   * @param deviation 1x3 standard deviation vector. Each element is in meter.
   * Can be created with the createDeviationVector method.
   * @see createPosition for the other parameters.
   * @returns Pointer to the created position object.
   */
  static Position* createPositionWithDeviation(
      const PositionSystem position_system, const double longitude_easting_x,
      const double latitude_northing_y, const double altitude_z,
      XyzVector* deviation, const uint32_t utm_zone_number = 0,
      const string& utm_zone_letter = "", const float translation_x = 0.0,
      const float translation_y = 0.0, const float translation_z = 0.0);

  /**
   * Create an orientation object without covariance or deviation.
   *
   * @param orientation_system The orientation system in which the coordinates
   * are interpreted. For example: PADMessageCreator::PositionSystem::ABSOLUTE
   * @param yaw Yaw angle in degree within [0, 360].
   * [-360, 0] will be converted to [0, 360].
   * 0 degree points towards to east, 90 to north,
   * 180 to west and 270 to south.
   * @param pitch Pitch angle in degree within [0, 360].
   * [-360, 0] will be converted to [0, 360].
   * @param roll Roll angle in degree within [0, 360].
   * [-360, 0] will be converted to [0, 360].
   * @returns Pointer to the created orientation object.
   * @throws out_of_range Yaw, pitch or roll angle is outside the range.
   */
  static Orientation* createOrientation(
      const OrientationSystem orientation_system, const float yaw,
      const float pitch, const float roll);

  /**
   * Create an orientation object with covariance matrix.
   *
   * @param covariance 3x3 covariance matrix. Each element is in degree squared.
   * Can be created with the createCovarianceMatrix method.
   * @see createOrientation for the other parameters.
   * @returns Pointer to the created orientation object.
   */
  static Orientation* createOrientationWithCovariance(
      const OrientationSystem orientation_system, const float yaw,
      const float pitch, const float roll, XyzMatrix3x3* covariance);

  /**
   * Create an orientation object with standard deviation vector.
   * Deviation vector will be converted to covariance matrix.
   * For example (x, y, z) -> (x^2, 0, 0,
   *                           0, y^2, 0,
   *                           0, 0, z^2)
   *
   * @param deviation 1x3 standard deviation vector. Each element is in degree.
   * Can be created with the createDeviationVector method.
   * @see createOrientation for the other parameters.
   * @returns Pointer to the created orientation object.
   */
  static Orientation* createOrientationWithDeviation(
      const OrientationSystem orientation_system, const float yaw,
      const float pitch, const float roll, XyzVector* deviation);

  /**
   * Create a size object without covariance or deviation.
   *
   * @param length Length of the object (along the x-axis).
   * @param width Width of the object (along the y-axis).
   * @param height Height of the object (along the z-axis).
   * @returns Pointer to the created size object.
   * @throws invalid_argument Length, width and height are also zero.
   * Length, width or height is less than zero.
   */
  static Size* createSize(const float length, const float width,
                          const float height);

  /**
   * Create a size object with covariance matrix.
   *
   * @param covariance 3x3 covariance matrix. Elements are in meter squared.
   * Can be created with the createCovarianceMatrix method.
   * @see createSize for the other parameters.
   * @returns Pointer to the created size object.
   */
  static Size* createSizeWithCovariance(const float length, const float width,
                                        const float height,
                                        XyzMatrix3x3* covariance);

  /**
   * Create a size object with standard deviation vector.
   * Deviation vector will be converted to covariance matrix.
   * For example (x, y, z) -> (x^2, 0, 0,
   *                           0, y^2, 0,
   *                           0, 0, z^2)
   *
   * @param deviation 1x3 standard deviation vector. Elements are in meter.
   * Can be created with the createDeviationVector method.
   * @see createSize for the other parameters.
   * @returns Pointer to the created size object.
   */
  static Size* createSizeWithDeviation(const float length, const float width,
                                       const float height,
                                       XyzVector* deviation);

  /**
   * Create a velocity object without covariance or deviation.
   *
   * @param motion_system The motion system in which the coordinates are
   * interpreted. For example: PADMessageCreator::MotionSystem::LOCAL
   * @param x, y, z Elements of the velocity vector in meter per second.
   * @returns Pointer to the created velocity object.
   */
  static Velocity* createVelocity(const MotionSystem motion_system,
                                  const float x, const float y, const float z);

  /**
   * Create a velocity object with covariance matrix.
   *
   * @param covariance 3x3 covariance matrix.
   * Elements are in meter squared per second squared.
   * Can be created with the createCovarianceMatrix method.
   * @see createVelocity for the other parameters.
   * @returns Pointer to the created velocity object.
   */
  static Velocity* createVelocityWithCovariance(
      const MotionSystem motion_system, const float x, const float y,
      const float z, XyzMatrix3x3* covariance);

  /**
   * Create a velocity object with standard deviation vector.
   * Deviation vector will be converted to covariance matrix.
   * For example (x, y, z) -> (x^2, 0, 0,
   *                           0, y^2, 0,
   *                           0, 0, z^2)
   *
   * @param deviation 1x3 standard deviation vector.
   * Elements are in meter per second.
   * Can be created with the createDeviationVector method.
   * @see createVelocity for the other parameters.
   * @returns Pointer to the created velocity object.
   */
  static Velocity* createVelocityWithDeviation(const MotionSystem motion_system,
                                               const float x, const float y,
                                               const float z,
                                               XyzVector* deviation);

  /**
   * Create an acceleration object without covariance or deviation.
   *
   * @param motion_system The motion system in which the coordinates are
   * interpreted. For example: PADMessageCreator::MotionSystem::LOCAL
   * @param x, y, z Elements of the acceleration vector in meter per second
   * squared.
   * @returns Pointer to the created acceleration object.
   */
  static Acceleration* createAcceleration(const MotionSystem motion_system,
                                          const float x, const float y,
                                          const float z);

  /**
   * Create an acceleration object with covariance matrix.
   *
   * @param covariance 3x3 covariance matrix.
   * Elements are in meter squared per second fourth.
   * Can be created with the createCovarianceMatrix method.
   * @see createAcceleration for the other parameters.
   * @returns Pointer to the created acceleration object.
   */
  static Acceleration* createAccelerationWithCovariance(
      const MotionSystem motion_system, const float x, const float y,
      const float z, XyzMatrix3x3* covariance);

  /**
   * Create an acceleration object with standard deviation vector.
   * Deviation vector will be converted to covariance matrix.
   * For example (x, y, z) -> (x^2, 0, 0,
   *                           0, y^2, 0,
   *                           0, 0, z^2)
   *
   * @param deviation 1x3 standard deviation vector.
   * Elements are in meter per second squared.
   * Can be created with the createDeviationVector method.
   * @see createAcceleration for the other parameters.
   * @returns Pointer to the created acceleration object.
   */
  static Acceleration* createAccelerationWithDeviation(
      const MotionSystem motion_system, const float x, const float y,
      const float z, XyzVector* deviation);

  /**
   * Create an angular velocity object without covariance or deviation.
   *
   * @param motion_system The motion system in which the coordinates are
   * interpreted. For example: PADMessageCreator::MotionSystem::LOCAL
   * @param yaw, pitch, roll Elements of the angular velocity vector
   * in degree per second.
   * @returns Pointer to the created angular velocity object.
   */
  static AngularVelocity* createAngularVelocity(
      const MotionSystem motion_system, const float yaw, const float pitch,
      const float roll);

  /**
   * Create an angular velocity object with covariance matrix.
   *
   * @param covariance 3x3 covariance matrix.
   * Elements are in degree squared per second squared.
   * Can be created with the createCovarianceMatrix method.
   * @see createAngularVelocity for the other parameters.
   * @returns Pointer to the created angular velocity object.
   */
  static AngularVelocity* createAngularVelocityWithCovariance(
      const MotionSystem motion_system, const float yaw, const float pitch,
      const float roll, XyzMatrix3x3* covariance);

  /**
   * Create an angular velocity object with standard deviation vector.
   * Deviation vector will be converted to covariance matrix.
   * For example (x, y, z) -> (x^2, 0, 0,
   *                           0, y^2, 0,
   *                           0, 0, z^2)
   *
   * @param deviation 1x3 standard deviation vector.
   * Elements are in degree per second.
   * Can be created with the createDeviationVector method.
   * @see createAngularVelocity for the other parameters.
   * @returns Pointer to the created angular velocity object.
   */
  static AngularVelocity* createAngularVelocityWithDeviation(
      const MotionSystem motion_system, const float yaw, const float pitch,
      const float roll, XyzVector* deviation);

  /**
   * Create an angular acceleration object without covariance or deviation.
   *
   * @param motion_system The motion system in which the coordinates are
   * interpreted. For example: PADMessageCreator::MotionSystem::LOCAL
   * @param yaw, pitch, roll Elements of the angular acceleration vector
   * in degree per second squared.
   * @returns Pointer to the created angular acceleration object.
   */
  static AngularAcceleration* createAngularAcceleration(
      const MotionSystem motion_system, const float yaw, const float pitch,
      const float roll);

  /**
   * Create an angular acceleration object with covariance matrix.
   *
   * @param covariance 3x3 covariance matrix.
   * Elements are in degree squared per second fourth.
   * Can be created with the createCovarianceMatrix method.
   * @see createAngularAcceleration for the other parameters.
   * @returns Pointer to the created angular acceleration object.
   */
  static AngularAcceleration* createAngularAccelerationWithCovariance(
      const MotionSystem motion_system, const float yaw, const float pitch,
      const float roll, XyzMatrix3x3* covariance);

  /**
   * Create an angular acceleration object with standard deviation vector.
   * Deviation vector will be converted to covariance matrix.
   * For example (x, y, z) -> (x^2, 0, 0,
   *                           0, y^2, 0,
   *                           0, 0, z^2)
   *
   * @param deviation 1x3 standard deviation vector.
   * Elements are in degree per second squared.
   * Can be created with the createDeviationVector method.
   * @see createAngularAcceleration for the other parameters.
   * @returns Pointer to the created angular acceleration object.
   */
  static AngularAcceleration* createAngularAccelerationWithDeviation(
      const MotionSystem motion_system, const float yaw, const float pitch,
      const float roll, XyzVector* deviation);

  /**
   * Create a detection object for PAD message.
   *
   * @param object_id Unique identifier of the detected object.
   * Always start from 1.
   * @param object_type Type of the detected object.
   * For example ObjectType::PERSON
   * @param object_confidence Confidence that the object has been detected
   * in percent.
   * @param type_confidence Confidence of the type in percent.
   * @param tracked Object has been tracked or not by the detector.
   * @param position Position information about the detected object.
   * It can be created by the following methods:
   * createPosition
   * createPositionWithCovariance
   * createPositionWithDeviation
   * @param orientation Orientation information about the detected object.
   * It can be created by the following methods:
   * createOrientation
   * createOrientationWithCovariance
   * createOrientationWithDeviation
   * @param size Size information about the detected object.
   * It can be created by the following methods:
   * createSize
   * createSizeWithCovariance
   * createSizeWithDeviation
   * @param velocity Velocity information about the detected object.
   * It can be created by the following methods:
   * createVelocity
   * createVelocityWithCovariance
   * createVelocityWithDeviation
   * @param acceleration Acceleration information about the detected object.
   * It can be created by the following methods:
   * createAcceleration
   * createAccelerationyWithCovariance
   * createAccelerationWithDeviation
   * @param angular_velocity Angular velocity information about the detected
   * object. It can be created by the following methods:
   * createAngularVelocity
   * createAngularVelocityWithCovariance
   * createAngularVelocityWithDeviation
   * @param angular_acceleration Angular acceleration information about the
   * detected object. It can be created by the following methods:
   * createAngularAcceleration
   * createAngularAccelerationWithCovariance
   * createAngularAccelerationWithDeviation
   * @param misc_attributes Miscellaneous attributes about the detected object.
   * Keys of this dictionary must be string.
   * Values can be int, double, bool or string.
   * Each value goes to the right map.
   * @throws out_of_range When the object id is less than 1 or
   * the confidences are not in percent.
   * @returns Pointer to the created detection object.
   */
  static Detection* createDetection(
      const uint32_t object_id, const ObjectType object_type,
      const float object_confidence, const float type_confidence,
      const bool tracked, Position* position, Orientation* orientation,
      Size* size, Velocity* velocity = nullptr,
      Acceleration* acceleration = nullptr,
      AngularVelocity* angular_velocity = nullptr,
      AngularAcceleration* angular_acceleration = nullptr,
      MiscAttributes* misc_attributes = nullptr);

  /**
   * Create a platform object without specific fields for PAD message.
   *
   * @param platform_id Unique identifier of the platform.
   * @param platform_type Type of the platform.
   * For example Platform_Type::Platform_Type_VEHICLE
   * @param position Position information about the platform.
   * It can be created by the following methods:
   * createPosition
   * createPositionWithCovariance
   * createPositionWithDeviation
   * @param orientation Orientation information about the platform.
   * It can be created by the following methods:
   * createOrientation
   * createOrientationWithCovariance
   * createOrientationWithDeviation
   * @param size Size information about the platform.
   * It can be created by the following methods:
   * createSize
   * createSizeWithCovariance
   * createSizeWithDeviation
   * @param velocity Velocity information about the platform.
   * It can be created by the following methods:
   * createVelocity
   * createVelocityWithCovariance
   * createVelocityWithDeviation
   * @param acceleration Acceleration information about the platform.
   * It can be created by the following methods:
   * createAcceleration
   * createAccelerationyWithCovariance
   * createAccelerationWithDeviation
   * @param angular_velocity Angular velocity information about the platform.
   * It can be created by the following methods:
   * createAngularVelocity
   * createAngularVelocityWithCovariance
   * createAngularVelocityWithDeviation
   * @param angular_acceleration Angular acceleration information about the
   * platform. It can be created by the following methods:
   * createAngularAcceleration
   * createAngularAccelerationWithCovariance
   * createAngularAccelerationWithDeviation
   * @param gnss_status Status of the localization.
   * For example Platform_GnssStatus::Platform_GnssStatus_DGPS
   * @param number_of_satellites Number of the currently visible satellites.
   * @param misc_attributes Miscellaneous attributes about the platform.
   * Keys of this dictionary must be string.
   * Values can be int, double, bool or string.
   * Each value goes to the right map.
   * @returns Pointer to the created platform object.
   */
  static Platform* createSimplePlatform(
      const string& platform_id, const Platform_Type platform_type,
      Position* position, Orientation* orientation, Size* size,
      Velocity* velocity = nullptr, Acceleration* acceleration = nullptr,
      AngularVelocity* angular_velocity = nullptr,
      AngularAcceleration* angular_acceleration = nullptr,
      const Platform_GnssStatus gnss_status = Platform_GnssStatus::
          Platform_GnssStatus_Platform_GnssStatus_INT_MAX_SENTINEL_DO_NOT_USE_,
      const uint32_t number_of_satellites = 0,
      MiscAttributes* misc_attributes = nullptr);

  /**
   * Create a platform object with wheeled vehicle data for PAD message.
   *
   * @param wheel_angle Wheel angle of the vehicle in degree.
   * @param steering_angle Steering angle of the vehicle in degree.
   * @param turning_radius Turning radius of the vehicle in meter.
   * @param throttle_state State of the throttle pedal in percent.
   * @param brake_state State of the brake pedal in percent.
   * @param clutch_state State of the clutch pedal (on/off).
   * @param gear_state State of the gearbox. Options:
   * -1: reverse
   * 0: neutral (or park in automatic gearboxes)
   * 1-8: gears
   * 1/2 gear can be used for drive/sport mode in automatic gearboxes.
   * @param engine_torque Torque of the engine in Newton meter.
   * @param brake_force Force of braking in Newton.
   * @see createSimplePlatform for other parameters.
   * @throws out_of_range When the turning radius is less than zero.
   * When the throttle or brake state is not in percent.
   * When the gear state is not in range.
   * When the engine torque is less than zero.
   * When the brake force is less than zero.
   * @returns Pointer to the created platform object.
   */
  static Platform* createWheeledVehicle(
      const string& platform_id, const Platform_Type platform_type,
      Position* position, Orientation* orientation, Size* size,
      Velocity* velocity = nullptr, Acceleration* acceleration = nullptr,
      AngularVelocity* angular_velocity = nullptr,
      AngularAcceleration* angular_acceleration = nullptr,
      const Platform_GnssStatus gnss_status = Platform_GnssStatus::
          Platform_GnssStatus_Platform_GnssStatus_INT_MAX_SENTINEL_DO_NOT_USE_,
      const uint32_t number_of_satellites = 0, const float wheel_angle = 0.0,
      const float steering_angle = 0.0, const float turning_radius = 0.0,
      const float throttle_state = 0.0, const float brake_state = 0.0,
      const bool clutch_state = false, const int32_t gear_state = 0,
      const float engine_torque = 0.0, const float brake_force = 0.0,
      MiscAttributes* misc_attributes = nullptr);

  /**
   * Create a platform object with aerial vehicle data for PAD message.
   *
   * @param flying_mode Flying mode of the vehicle.
   * For example AerialVehicle_FlyingMode::AerialVehicle_FlyingMode_MISSION
   * @param battery_voltage Voltage of the battery in Volt.
   * @param battery_charge Charge of the battery in percent.
   * @param home_position_longitude Longitude coordinate of the home point.
   * @param home_position_latitude Latitude coordinate of the home point.
   * @param home_position_altitude Altitude coordinate of the home point.
   * @param flying_time Flying time in milliseconds.
   * @param turned_on_time Turned on time in milliseconds.
   * @param controller_signal_strength Signal strength of the controller
   * in decibel.
   * @param control_center_signal_strength Signal strength of the control
   * center in decibel.
   * @param status_codes List of possible status codes of the vehicle.
   * @param error_codes List of possible error codes of the vehicle.
   * @see createSimplePlatform for other parameters.
   * @throws out_of_range When the battery voltage is less than zero.
   * When the battery charge is not in percent.
   * @returns Pointer to the created platform object.
   */
  static Platform* createAerialVehicle(
      const string& platform_id, const Platform_Type platform_type,
      Position* position, Orientation* orientation, Size* size,
      Velocity* velocity = nullptr, Acceleration* acceleration = nullptr,
      AngularVelocity* angular_velocity = nullptr,
      AngularAcceleration* angular_acceleration = nullptr,
      const Platform_GnssStatus gnss_status = Platform_GnssStatus::
          Platform_GnssStatus_Platform_GnssStatus_INT_MAX_SENTINEL_DO_NOT_USE_,
      const uint32_t number_of_satellites = 0,
      const AerialVehicle_FlyingMode flying_mode = AerialVehicle_FlyingMode::
          AerialVehicle_FlyingMode_AerialVehicle_FlyingMode_INT_MAX_SENTINEL_DO_NOT_USE_,
      const float battery_voltage = 0.0, const float battery_charge = 0.0,
      const double home_position_longitude = 0.0,
      const double home_position_latitude = 0.0,
      const double home_position_altitude = 0.0, const uint64_t flying_time = 0,
      const uint64_t turned_on_time = 0,
      const float controller_signal_strength = 0.0,
      const float control_center_signal_strength = 0.0,
      const vector<uint32_t>& status_codes = vector<uint32_t>(),
      const vector<uint32_t>& error_codes = vector<uint32_t>(),
      MiscAttributes* misc_attributes = nullptr);

  /**
   * Create a PAD (Platform And Detection) message.
   * It contains a header, platform and detections (if any).
   * Platform can be created with the following methods:
   * createSimplePlatform: a platform without specific fields.
   * createWheeledVehicle: a platform with wheeled vehicle data.
   * createAerialVehicle: a platform with aerial vehicle data.
   * Detections can be created with createDetection method.
   *
   * @param header Header of the PAD message.
   * @param platform Platform of the PAD message.
   * @param detections Detected objects by the platform.
   * @returns The created PAD message.
   */
  static PAD createPADMessage(
      Header* header, Platform* platform,
      const vector<Detection*>& detections = vector<Detection*>());
};

class SlamMapMessageCreator {
 public:
  /**
   * Create a 3x3 transformation matrix.
   *
   * @param xx, xy, xz First row of the matrix.
   * @param yx, yy, yz Second row of the matrix.
   * @param zx, zy, zz Third row of the matrix.
   * @returns Pointer to the created transformation matrix.
   */
  static XyzMatrix3x3* createTransformationMatrix(
      const float xx, const float xy, const float xz, const float yx,
      const float yy, const float yz, const float zx, const float zy,
      const float zz);

  /**
   * Create an UTM position object.
   *
   * @param x UTM x coordinate in meter.
   * @param y UTM y coordinate in meter.
   * @param z Altitude coordinate in meter.
   * @param zone_number Number of the UTM zone.
   * @param zone_letter Letter of the UTM zone.
   * @returns Pointer to the created position object.
   */
  static Position_Utm* createUtmPosition(const double x, const double y,
                                         const double z,
                                         const uint32_t zone_number,
                                         const string& zone_letter);

  /**
   * Create a trajectory which signs the path where the Map can be used
   * for relocalization.
   *
   * @param x UTM x coordinate in meter.
   * @param y UTM y coordinate in meter.
   * @param z Altitude coordinate in meter.
   * @param qw Rotation quaternion w-component.
   * @param qx Rotation quaternion x-component.
   * @param qy Rotation quaternion y-component.
   * @param qz Rotation quaternion z-component.
   * @returns Pointer to the created trajectory object.
   */
  static automateddrive::datamodels::slam_map::protobuf::Trajectory*
  createTrajectory(const double x, const double y, const double z,
                   const float qw, const float qx, const float qy,
                   const float qz);

  /**
   * Create camera intrinsic parameters which should be in
   * OpenCV Pinhole format.
   *
   * @param fx Focal length in x-axis.
   * @param fy Focal length in y-axis.
   * @param cx Optical center x-coordinate.
   * @param cy Optical center y-coordinate.
   * @param p1 Principal point x-coordinate.
   * @param p2 Principal point y-coordinate.
   * @param k1 Radial distortion coefficient k1.
   * @param k2 Radial distortion coefficient k2.
   * @returns Pointer to the created CameraIntrinsicParameters object.
   */
  static CameraIntrinsicParameters* createCameraIntrinsicParameters(
      const float fx, const float fy, const float cx, const float cy,
      const float p1, const float p2, const float k1, const float k2);

  /**
   * Create settings for SLAM map which were used during map creation.
   *
   * @param number_of_orb_features
   * @param scale_factor
   * @param pyramid_level
   * @returns Pointer to the created Settings object.
   */
  static Settings* createSettings(const uint32_t number_of_orb_features,
                                  const uint32_t scale_factor,
                                  const uint32_t pyramid_level);

  /**
   * Create environmental context which is the details on the mapping
   * environment that affect performances.
   *
   * @param indoor_outdoor Indoor (true) or outdoor (false) environment.
   * @param weather Foggy, rainy, showy or sunny.
   * @param lighting_conditions
   * @returns Pointer to the created EnvironmentalContext object.
   */
  static EnvironmentalContext* createEnvironmentalContext(
      const bool indoor_outdoor, const Weather weather,
      const uint32_t lighting_conditions);

  /**
   * Create metrics of the SLAM map.
   *
   * @param number_of_key_frames
   * @param number_of_map_points
   * @param avg_distance_of_map_points Average distance of map points.
   * @param avg_sim_trans_error Average similarity transformation error.
   * @returns Pointer to the created MapMetrics object.
   */
  static MapMetrics* createMapMetrics(const uint32_t number_of_key_frames,
                                      const uint32_t number_of_map_points,
                                      const float avg_distance_of_map_points,
                                      const float avg_sim_trans_error);

  /**
   * Create ORB-SLAM3 Map message.
   *
   * @param header Header of the message.
   * @param raw_map The SLAM-generated map data that encapsulates the 3D
   * environment.
   * @param sim_trans_matrix Similarity transformation matrix to transform SLAM
   * coordinates to the UTM coordinate frame.
   * @param start_utm_coordinates UTM coordinates where the mapping session was
   * initialized.
   * @param start_utc_timestamp Precise UTC time when the map initialization begun.
   * @param end_utm_coordinates UTM coordinates where the mapping session was
   * concluded.
   * @param end_utc_timestamp Precise UTC time when the map initialization finished.
   * @param trajectories Signs the path where the Map can be used for relocalization.
   * @param vehicle_id Identifier for the vehicle used.
   * @param sensor_type The type of the imaging sensor used for visual map creation.
   * @param camera_intrinsic_parameters Camera intrinsic parameters which should be
   * in OpenCV Pinhole format.
   * @param map_size Size of the map in MB.
   * @param map_version Version of the map.
   * @param settings Settings used during map creation.
   * @param environmental_context Details on the mapping environment.
   * @param map_metrics Metrics of the created map.
   * @param comment Further information attached to the map.
   * @param map_id Identifier of the map.
   * @param map_slice_id Identifier of the map slice.
   * @param number_of_slice Number of slices in the map.
   * @returns The created ORBSLAM3Map message.
   */
  static ORBSLAM3Map createSlamMapMessage(
      Header* header, const string& raw_map,
      XyzMatrix3x3* sim_trans_matrix = nullptr,
      Position_Utm* start_utm_coordinates = nullptr,
      const uint64_t start_utc_timestamp = 0,
      Position_Utm* end_utm_coordinates = nullptr,
      const uint64_t end_utc_timestamp = 0,
      const vector<automateddrive::datamodels::slam_map::protobuf::Trajectory*>&
          trajectories = vector<
              automateddrive::datamodels::slam_map::protobuf::Trajectory*>(),
      const string& vehicle_id = "",
      const SensorType sensor_type =
          SensorType::SensorType_INT_MAX_SENTINEL_DO_NOT_USE_,
      CameraIntrinsicParameters* camera_intrinsic_parameters = nullptr,
      const float map_size = 0.0, const uint32_t map_version = 0,
      Settings* settings = nullptr,
      EnvironmentalContext* environmental_context = nullptr,
      MapMetrics* map_metrics = nullptr, const string& comment = "",
      const uint32_t map_id = 0, const uint32_t map_slice_id = 0,
      const uint32_t number_of_slice = 0);
};

class SensorDataMessageCreator {
public:
    /**
     * Create extrinsic parameters of the sensor.
     *
     * @param x UTM x coordinate in meter.
     * @param y UTM y coordinate in meter.
     * @param z Altitude coordinate in meter.
     * @param qw Rotation quaternion w-component.
     * @param qx Rotation quaternion x-component.
     * @param qy Rotation quaternion y-component.
     * @param qz Rotation quaternion z-component.
     * @returns Pointer to the created SensorData_ExtrinsicParameters object.
     */
    static SensorData_ExtrinsicParameters* createExtrinsicParameters(
        const float x, const float y, const float z,
        const float qw, const float qx, const float qy, const float qz);

    /**
     * Create intrinsic parameters of the sensor.
     *
     * @param fx Focal length in x-axis.
     * @param fy Focal length in y-axis.
     * @param cx Optical center x-coordinate.
     * @param cy Optical center y-coordinate.
     * @param p1 Principal point x-coordinate.
     * @param p2 Principal point y-coordinate.
     * @param k1 Radial distortion coefficient k1.
     * @param k2 Radial distortion coefficient k2.
     * @param k3 Radial distortion coefficient k3.
     * @returns Pointer to the created SensorData_IntrinsicParameters object.
     */
    static SensorData_IntrinsicParameters* createIntrinsicParameters(
        const float fx, const float fy, const float cx, const float cy,
        const float p1, const float p2, const float k1, const float k2,
        const float k3);

    /**
     * Create SensorData object with image data.
     *
     * @param id Identifier of the sensor.
     * @param name Name of the sensor.
     * @param timestamp Timestamp of the sensor data.
     * @param int_param Intrinsic parameters of the sensor.
     * @param ext_param Extrinsic parameters of the sensor.
     * @param width Width of the image.
     * @param height Height of the image.
     * @param pixel_format Pixel format of the image.
     * @param compression Compression type of the image.
     * @param data Raw image data.
     * @returns Pointer to the created SensorData object.
     */
    static SensorData* createImageSensorData(
        const uint32_t id, const string& name, const uint64_t timestamp,
        SensorData_IntrinsicParameters* int_param, SensorData_ExtrinsicParameters* ext_param,
        const uint32_t width, const uint32_t height, SensorData_PixelFormat pixel_format,
        SensorData_ImageCompression compression, const string& data);

    /**
     * Create SensorData object with point cloud data.
     *
     * @param id Identifier of the sensor.
     * @param name Name of the sensor.
     * @param timestamp Timestamp of the sensor data.
     * @param num_points Number of points in the point cloud.
     * @param scale Divisor for quantized coordinates.
     * @param ext_param Extrinsic parameters of the sensor.
     * @param format Format of the point cloud data.
     * @param encoding Type of point cloud encoding.
     * @param bit_depth Bit depth of each coordinate value in data bytes.
     * @param data Raw point cloud data.
     * @returns Pointer to the created SensorData object.
     */
    static SensorData* createPointCloudSensorData(
        const uint32_t id, const string& name, const uint64_t timestamp,
        const uint32_t num_points, const uint32_t scale,
        SensorData_ExtrinsicParameters* ext_param, SensorData_PointCloudFormat format,
        SensorData_PointCloudEncoding encoding, SensorData_PointCloudBitDepth bit_depth,
        const string& data);

    /**
     * Create RawSensorData message.
     *
     * @param header Header of the message.
     * @param sensor_data Vector of SensorData objects.
     * @returns The created RawSensorData message.
     */
    static RawSensorData createRawSensorDataMessage(
        Header* header, const vector<SensorData*>& sensor_data = vector<SensorData*>());
};

/**
 * Can create a header to each message type. Each timestamp has to be sent in
 * milliseconds. Timestamps are generally used during measurements. Header has
 * also a topic timestamp and topic offset field which is added by the
 * central system during download.
 *
 * @param protocol_id ID of the currently used message transition protocol.
 * Can be changed and/or extended in the future.
 * 2 - Sensoris Detection
 * 3 - FeedbackData
 * 5 - PAD (Platform And Detection)
 * 6 - Fusion
 * 7 - ORBSLAM3Map
 * 9 - SensorData
 * 103 - TrajectoryControl
 * 104 - GeneralVehicleControl
 * 105 - VehicleSpecificControl
 * 106 - TriggerControl
 * 107 - TrackedVehicleControl
 * 108 - TorqueVectoringControl
 * 109 - FunctionControl
 * 201 - FeedbackRequest
 * 301 - RawVideoData
 * 302 - RawImageData
 * 303 - RawPointCloudData
 * 400 - Diagnostic
 * 401 - Heartbeat
 * 402 - DiagnosticEvent
 * 500 - TrafficLightControl
 * @param version_no Version number. Different versions can be used for
 * different purposes in the future.
 * @param sender_id ID of the message sender.
 * @param recipient_ids Reference to the vector of recipient system IDs for
 * whom messages will be sent.
 * @param seq_num Message sequence number.
 * @param val_earl_ts Earliest timestamp when message is already valid.
 * @param val_lat_ts Latest timestamp when message is still valid.
 * @param acq_ts When message has been acquired.
 * @param decision_ts When decision about data processing was made.
 * @param source_ts When source device sends the message. It will be updated
 * when creating a message and after that message has to be sent to the
 * server.
 * @param seq_id ID of the actual message sequence.
 * @param pre_msg_no Message count requested before taking this message into
 * account.
 * @param origin_header Reference to the vector of headers of origin messages.
 * @param topic_ts When message arrived to a topic in Central System.
 * Only matters when creating origin headers.
 * @param topic_offset Position of message stored in a topic in Central System.
 * Only matters when creating origin headers.
 * @returns Pointer to the newly allocated Header object.
 */
Header* createHeader(const uint32_t protocol_id, const uint32_t version_no,
                     const string& sender_id,
                     const vector<string>& recipient_ids,
                     const uint64_t seq_num, const uint64_t val_earl_ts = 0,
                     const uint64_t val_lat_ts = 0, const uint64_t acq_ts = 0,
                     const uint64_t decision_ts = 0,
                     const uint64_t source_ts = 0, const string& seq_id = "",
                     const uint64_t pre_msg_no = 0,
                     const vector<Header*>& origin_headers = vector<Header*>(),
                     const uint64_t topic_ts = 0,
                     const uint64_t topic_offset = 0);

/**
 * Create a stream request to sent to the central server to receive messages
 * from a topic.
 *
 * @param topic Topic name from where we want to receive messages.
 * Naming convention: "topic_name".
 * For example: receive feedback data -> topic="feedback_data"
 * @param partition Topic partition number. Default and currently used is 0.
 * @param request_name Sender system name. Receive messages only which
 * recipient id list contains this name. Default value is empty string.
 * In this case every message will be downloaded.
 * @param request_id ID of this request.
 * @param receive_older_messages When it is True then receive older messages
 * from offset or timestamp specified in this request.
 * When it is False then waiting for new messages.
 * @param offset Receive messages from this offset.
 * When it is negative then you will get the last N message where
 * N=abs(offset). It only matters when receive_older_messages is True and
 * receive_from_timestamp=0 (by default).
 * @param paced_replay When it is True then get messages in a rate specified
 * by frame_rate.
 * @param frame_rate Number of messages to get in a second. paced_replay has
 * to be true.
 * @param use_cache Download messages from client module's internal buffer.
 * @param receive_from_senders Receive messages only from senders given in
 * this list. When empty then receive every message.
 * @param receive_from_timestamp Receive messages from this timestamp.
 * It is related to server's time and should be in millisecond.
 * It only matters when receive_older_messages is True.
 * @param message_sequence_ids Receive messages only with the given
 * sequence id. When empty then receive every message.
 * @returns The newly created StreamRequest object.
 */
StreamRequest createStreamRequest(
    const string& topic, const uint32_t partition = 0,
    const string& request_name = "", const int32_t request_id = 0,
    const bool receive_older_messages = false, const int64_t offset = 0,
    const bool paced_replay = false, const int32_t frame_rate = 0,
    const bool use_cache = false,
    const vector<string>& receive_from_senders = vector<string>(),
    const uint64_t receive_from_timestamp = 0,
    const vector<string>& message_sequence_ids = vector<string>());

#endif  // MESSAGE_CREATOR_HPP
