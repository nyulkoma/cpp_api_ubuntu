#ifndef GRPC_RECEIVER_HPP
#define GRPC_RECEIVER_HPP

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include <thread>

#include "../utils/SimpleIni.h"
#include "../utils/logger.hpp"
#include "authenticator.hpp"
#include "default_config.hpp"
#include "message_receiver_service.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;

/**
 * We have to undefine the TRANSPARENT macro on Windows because
 * road attribution category in Sensoris message creates a TRANSPARENT variable
 * and winuser.h has already defined a macro like this.
 */
#ifdef TRANSPARENT
#undef TRANSPARENT
#endif

#include "../../proto_gen/data_models/fusion_protocol/fusion.pb.h"
#include "../../proto_gen/grpc_models/control_protocol/control_protocol_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/diagnostic_protocol/diagnostic_protocol_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/feedback_protocol/feedback_protocol_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/fusion_protocol/fusion_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/pad_protocol/pad_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/raw_data/raw_data_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/sensor_data/raw_sensor_data_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/sensoris/sensoris_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/slam_map/slam_map_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/traffic_light/traffic_light_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/util/util.pb.h"
#include "../queue/readerwriterqueue.h"

using automateddrive::datamodels::fusion::protobuf::Fusion;
using automateddrive::datamodels::util::protobuf::StreamRequest;
using namespace moodycamel;

template <class MessageType>
class ReceiveReactor : public grpc::ClientReadReactor<MessageType> {
 public:
  ReceiveReactor(StreamRequest request);
  string StartStream(shared_ptr<Channel> channel);
  void OnReadDone(bool ok);
  bool WaitForReadDone();
  void OnDone(const Status& status);
  Status WaitForDone();
  void StopStream();
  bool GetRequestReceiveOlderMessages();
  void UpdateRequest(int64_t offset);
  ~ReceiveReactor();

 private:
  unique_ptr<ClientContext> context;
  StreamRequest request;
  mutex rdm;
  bool read_done = false;
  condition_variable rdcv;
  mutex dm;
  bool done = false;
  condition_variable dcv;
  bool read_ok;
  Status status;
};

template <class MessageType>
class GrpcReceiver : public MessageReceiverService<MessageType> {
 private:
  shared_ptr<Channel> channel;
  ReceiveReactor<MessageType>* reactor;
  Authenticator* authenticator;
  shared_ptr<spdlog::logger> logger;
  CSimpleIniA config;
  string host;
  int port;
  string topic;
  bool stoppedByUser;

  /**
   * Receive messages from the server. It will block until a message arrives and
   * then calls the given callback function. In case of connection error or
   * when the user closes the connection it returns.
   *
   * @tparam MessageType Expected type of messages to be downloaded.
   * @param callbackFunction Callback function pointer.
   */
  void handleAsyncOperation(function<void(MessageType)> callbackFunction);

  /**
   * Same as handleAsyncOperation but its callback function also gets a queue
   * where messages will be stored until something reads them out from it.
   *
   * @tparam MessageType Expected type of messages to be downloaded.
   * @param callbackFunction Callback function pointer.
   * @param queue Pointer to the queue.
   */
  void handleAsyncOperationWithQueue(
      function<void(MessageType, ReaderWriterQueue<MessageType>*)>
          callbackFunction,
      ReaderWriterQueue<MessageType>* queue);

 public:
  /**
   * Create grpc receiver object. When the config file was not found or
   * was not set then takes default values from DefaultConfig struct
   * written in default_config.hpp.
   *
   * @param request A StreamRequest object which will be sent to the
   * gRPC server to initiate a message stream. Can be created with the
   * createStreamRequest function of MessageCreator class.
   * @param configFileName Name of the configuration file. Must be an
   * ini file. File route is relative to the executable.
   */
  GrpcReceiver(StreamRequest request, string configFileName = "");

  /**
   * Block until a successful connection with the central server.
   *
   * @returns True on success, false on fail.
   */
  bool createConnection();

  /**
   * Receive messages from the server. It will block until a message arrives and
   * then returns the message. In case of reading error, it tries to reconnect
   * to the server. In case of connection error or when the user closes the
   * connection, it returns an empty MessageType message.
   *
   * @tparam MessageType Expected type of messages to be downloaded.
   * @returns MessageType message which has been received from the server.
   */
  MessageType receiveMessages();

  /**
   * Receive messages from the server asynchronously. It will create a new
   * thread in which the given callback function will be called when a new
   * message arrives.
   *
   * @tparam MessageType Expected type of messages to be downloaded.
   * @param callbackFunction Callback function pointer.
   */
  void receiveMessagesAsync(function<void(MessageType)> callbackFunction);

  /**
   * Same as receiveMessagesAsync but its callback function also gets a queue
   * where messages will be stored until something reads them out from it.
   *
   * @tparam MessageType Expected type of messages to be downloaded.
   * @param callbackFunction Callback function pointer.
   * @param queue Pointer to the queue.
   */
  void receiveMessagesAsyncWithQueue(
      function<void(MessageType, ReaderWriterQueue<MessageType>*)>
          callbackFunction,
      ReaderWriterQueue<MessageType>* queue);

  /**
   * Close the connection with the central server.
   *
   * @returns True on success, false on fail.
   */
  bool closeConnection();
  ~GrpcReceiver();
};

#endif  // GRPC_RECEIVER_HPP
