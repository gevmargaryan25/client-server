#ifndef SERVER_SERVER_HPP_
#define SERVER_SERVER_HPP_

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class Server {
private:
  std::unordered_map<std::string, std::vector<json::value>> _unread_messages;
  http_listener _listener;

public:
  explicit Server(const std::string& listening_port);
  ~Server();
  void start();

private:
  void handle_get(const http_request& request);
  void handle_post(const http_request& request);
  json::value unread_messages(const std::string& username);
  static void handle_unknown_request(const http_request& request);

  static const std::string user_key;
  static const std::string partner_key;
  static const std::string msg_key;
};

#endif //SERVER_SERVER_HPP_
