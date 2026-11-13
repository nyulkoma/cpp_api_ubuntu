#ifndef MESSAGE_RECEIVER_SERVICE_HPP
#define MESSAGE_RECEIVER_SERVICE_HPP

#include <functional>
#include <iostream>
#include <string>
using namespace std;

template <class MessageType>
class MessageReceiverService {
 public:
  // Ctrl + left click to see details in derived class.
  virtual bool createConnection() = 0;

  // Ctrl + left click to see details in derived class.
  virtual MessageType receiveMessages() = 0;

  // Ctrl + left click to see details in derived class.
  virtual void receiveMessagesAsync(
      function<void(MessageType)> callbackFunction) = 0;

  // Ctrl + left click to see details in derived class.
  virtual bool closeConnection() = 0;

  virtual ~MessageReceiverService(){};
};

#endif  // MESSAGE_RECEIVER_SERVICE_HPP
