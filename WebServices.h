#pragma once

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <iostream>
#include <string>
#include <vector>
#include <defaults.h>

class Service {
public:
  static std::vector<Service *> *instances;
  std::string serviceTreePath = "";
  Service();
  virtual std::string getServiceName() = 0;
  void printLog(std::string log);
  // void buildServiceTreePath();
  virtual void printServiceTree(int depth);
  static void printServiceTree(std::string dummyArg);
};

/***
 * WebServer
 * extend this class to provide additional server routes
 * or services for a specific port
 */

template <int SERVER_PORT=DEFAULT_PORT> class WebService : public Service {
public:
  // server at given port shared by all instances
  static AsyncWebServer server;
  // each instances providing custom routes for the shared server
  // static std::vector<WebService<SERVER_PORT> *> *instances;
  // States @todo: support more states like running, stopped, failed..
  static bool serverState;
  bool state = false; // (child) service state

  WebService();
  static void start();
};

/***
 * WebSocketService
 * each instance of this class will be notified of incoming ws message
 */

template <int SERVER_PORT=DEFAULT_PORT, const char *SOCKET_PATH=defaultWSPath>
class WebSocketService : public WebService<SERVER_PORT> {
public:
  // Web socket object associated
  static AsyncWebSocket aws;
  static int messageCount;

  // private:
  // static WebSocketService<SERVER_PORT, SOCKET_PATH> *instance;// Singleton
  // static std::vector<WebSocketListener *> *wsListeners;
  static std::string rawMessage;

  // protect constructor
  WebSocketService();

public:
  // static WebSocketService<SERVER_PORT, SOCKET_PATH> *getSingleton();

  static void eventHandler(AsyncWebSocket *server, AsyncWebSocketClient *client,
                           AwsEventType type, void *arg, uint8_t *data,
                           size_t len);

  static void forwardDispatch(void *arg, uint8_t *data, size_t len, int clientId);

  // virtual std::string processMsg(std::string rawMsg);

  std::string getServiceName();
};

/***
 * each instance of this class will receive ws message
 * can be notified synchroneously OR can listen asynchroneously for incoming messages
 */

template <int WS_PORT=DEFAULT_PORT, const char *WS_PATH=defaultWSPath> class WebSocketListener {
public:
  static int messageCount;
  static std::vector<WebSocketListener<WS_PORT, WS_PATH> *> *instances;
  WebSocketListener();
  // active async listen to a specific WS service
  static void asyncListenForwardLoop();

  // synchroneous call every time a message is received 
  // => to be overriden in child class
  virtual std::string processMsg(std::string rawMsg); 
};
