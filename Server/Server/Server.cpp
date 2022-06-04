#include "Server.hpp"

const std::string Server::user_key = "username";
const std::string Server::partner_key = "partner_name";
const std::string Server::msg_key = "message";

Server::Server(const std::string& listening_port)
{
  uri_builder uri(U("http://0.0.0.0:") + listening_port);
  const auto uri_address = uri.to_uri().to_string();
  _listener = http_listener(uri_address, http_listener_config());
  _listener.support(methods::GET,
      [this](auto&& arg) { handle_get(std::forward<decltype(arg)>(arg)); });
  _listener.support(methods::POST,
      [this](auto&& arg) { handle_post(std::forward<decltype(arg)>(arg)); });
  _listener.support(methods::PUT, &Server::handle_unknown_request);
  _listener.support(methods::DEL, &Server::handle_unknown_request);
}

Server::~Server()
{
  _listener.close().wait();
}

void Server::start()
{
  _listener.open().wait();
  std::cout << "server is now waiting for requests!" << std::endl;
}

void Server::handle_get(const http_request& request)
{
  try {
    const auto body = request.extract_json(true).get();
    const auto username = body.at(user_key).as_string();
    request.reply(status_codes::OK, unread_messages(username));
    std::cout << "The all messages addressed to " << username << " are sent!" << std::endl;
  }
  catch (const json::json_exception& exc) {
    request.reply(status_codes::BadRequest, json::value::string(exc.what()));
  }
}

void Server::handle_post(const http_request& request)
{
  try {
    const auto body = request.extract_json().get();
    const auto username = body.at(user_key).as_string();
    json::value message{};
    message[partner_key] = body.at(partner_key);
    message[msg_key] = body.at(msg_key);
    _unread_messages[username].emplace_back(message);

    std::cout << "received a message from " << body.at(partner_key).as_string()
              << " for " << username << std::endl;
    request.reply(status_codes::OK);
  }
  catch (const json::json_exception& exc) {
    std::cerr << "server got key error when getting values from post request!" << std::endl;
    request.reply(status_codes::BadRequest, json::value::string(exc.what()));
  }
}

json::value Server::unread_messages(const std::string& username)
{
  json::value result{};
  const auto it = _unread_messages.find(username);
  if (it != _unread_messages.end()) {
    result = json::value::array(it->second);
    _unread_messages.erase(it);
  }
  return result;
}

void Server::handle_unknown_request(const http_request& request)
{
  request.reply(status_codes::MethodNotAllowed);
}
