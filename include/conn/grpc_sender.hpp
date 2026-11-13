#ifndef GRPC_SENDER_HPP
#define GRPC_SENDER_HPP

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include <condition_variable>
#include <filesystem>
#include <mutex>
#include <thread>

#include "../utils/SimpleIni.h"
#include "../utils/logger.hpp"
#include "authenticator.hpp"
#include "default_config.hpp"
#include "message_sender_service.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

/**
 * We have to undefine the TRANSPARENT macro on Windows because
 * road attribution category in Sensoris message creates a TRANSPARENT variable
 * and winuser.h has already defined a macro like this.
 */
#ifdef TRANSPARENT
#undef TRANSPARENT
#endif

#include "../../proto_gen/grpc_models/control_protocol/control_protocol_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/diagnostic_protocol/diagnostic_protocol_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/feedback_protocol/feedback_protocol_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/pad_protocol/pad_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/raw_data/raw_data_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/sensor_data/raw_sensor_data_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/sensoris/sensoris_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/slam_map/slam_map_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/traffic_light/traffic_light_grpc.grpc.pb.h"
#include "../../proto_gen/grpc_models/util/util.pb.h"
#include "../queue/readerwriterqueue.h"

using automateddrive::datamodels::util::protobuf::StreamSummary;
using namespace moodycamel;

template <class MessageType>
class SendReactor : public grpc::ClientWriteReactor<MessageType> {
 public:
  SendReactor();
  string StartStream(shared_ptr<Channel> channel, string channelType = "video");
  void OnWriteDone(bool ok);
  bool WaitForWriteDone();
  void OnDone(const Status& status);
  Status WaitForDone(StreamSummary* summary);
  ~SendReactor();

 private:
  unique_ptr<ClientContext> context;
  StreamSummary summary;
  mutex wdm;
  bool write_done = false;
  condition_variable wdcv;
  mutex dm;
  bool done = false;
  condition_variable dcv;
  bool write_ok;
  Status status;
};

template <class MessageType>
class GrpcSender : public MessageSenderService<MessageType> {
 private:
  shared_ptr<Channel> channel;
  SendReactor<MessageType>* reactor;
  Authenticator* authenticator;
  BlockingReaderWriterQueue<MessageType> queue;
  shared_ptr<spdlog::logger> logger;
  CSimpleIniA config;
  mutex mtx;
  condition_variable cv;
  bool ready_to_send;
  string host;
  int port;
  string channelType;
  bool stoppedByUser;

  /**
   * Print the summary of the stream.
   *
   */
  void printSummary(StreamSummary summary);

  /**
   * Read messages out from the queue and send them to the server.
   * In case of sending error it tries to reconnect to the server.
   *
   * @tparam MessageType Expected type of messages to be uploaded.
   * @param queue Message queue from which messages will be dequeued.
   */
  void messageSender(BlockingReaderWriterQueue<MessageType>* queue);

 public:
  /**
   * Create grpc sender object. Create a thread which sends messages
   * to the server.
   *
   * @param configFileName Name of the configuration file. Must be an
   * ini file. File route is relative to the executable.
   * @param channelType Type of channel to create. Only matters when
   * RawData messages will be sent. Options: video, image, pointcloud
   */
  GrpcSender(string configFileName = "", string channelType = "video");

  /**
   * Block until a successful connection with the central server.
   *
   * @returns True on success, false on fail.
   */
  bool createConnection();

  /**
   * Put message to the queue which will be uploaded to the server immediately
   * when there is an active connection to the server. If the queue is full then
   * it waits for at most 10 seconds for free space.
   *
   * @tparam MessageType Expected type of messages to be uploaded.
   * @param message MessageType message to upload.
   * @returns True on success, false on fail.
   */
  bool sendMessage(MessageType message);

  /**
   * Put message to the queue which will be uploaded to the server immediately
   * when there is an active connection to the server. If the queue is full then
   * it waits for at most 'timeout' seconds for free space. After that it
   * replaces the oldest message with this new one.
   *
   * @tparam MessageType Expected type of messages to be uploaded.
   * @param message MessageType message to upload.
   * @param timeout timeout value of free space waiting in second.
   * @returns True on success, false on fail.
   */
  bool sendMessage(MessageType message, int timeout);

  /**
   * Put message to the queue which will be uploaded to the server immediately
   * when there is an active connection to the server. If the queue is full then
   * it replaces the oldest message with this new one and returns false without
   * waiting for a free space.
   *
   * @tparam MessageType Expected type of messages to be uploaded.
   * @param message MessageType message to upload.
   * @returns True on success, false on fail.
   */
  bool sendMessageAsync(MessageType message);

  /**
   * Close the connection with the central server.
   * On success print the summary of the stream.
   *
   * @returns True on success, false on fail.
   */
  bool closeConnection();
  ~GrpcSender();
};

#endif  // GRPC_SENDER_HPP
