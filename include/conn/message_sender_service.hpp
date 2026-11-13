#ifndef MESSAGE_SENDER_SERVICE_HPP
#define MESSAGE_SENDER_SERVICE_HPP

#include <functional>
#include <iostream>
#include <string>
using namespace std;

template <class MessageType>
class MessageSenderService {
 public:
  // Ctrl + left click to see details in derived class.
  virtual bool createConnection() = 0;

  // Ctrl + left click to see details in derived class.
  virtual bool sendMessage(MessageType message) = 0;

  // Ctrl + left click to see details in derived class.
  virtual bool sendMessageAsync(MessageType message) = 0;

  // Ctrl + left click to see details in derived class.
  virtual bool closeConnection() = 0;

  virtual ~MessageSenderService(){};
};

#endif  // MESSAGE_SENDER_SERVICE_HPP
