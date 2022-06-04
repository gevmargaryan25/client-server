#ifndef CLIENT_CLIENT_HPP
#define CLIENT_CLIENT_HPP

#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class Client {
private:
  std::string _username;
  http_client _self;
  std::unordered_map<std::string, std::vector<std::string>> _messages;

public:
  Client(const utility::string_t& address, std::string username);
  void start_chat(int duration);

private:
  void send();
  void show_messages();
  void send(const json::value& body);
  void update_messages();
  json::value get_from_server();
  static char get_choice();

  static const std::string user_key;
  static const std::string partner_key;
  static const std::string msg_key;
};

#endif //CLIENT_CLIENT_HPP
