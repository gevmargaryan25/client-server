#include "Client.hpp"

int main()
{
  try {
    constexpr int chat_duration = 40;
    std::cout << "Enter your username: ";
    std::string username{};
    std::cin >> username;
    Client client(uri_builder(U("http://localhost:5445")).to_uri().to_string(), username);
    client.start_chat(chat_duration);
  }
  catch (const web::http::http_exception& exc) {
    std::cerr << exc.what() << std::endl;
  }
  return 0;
}
