#include <iostream>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while(true){

    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);
    // if(input=="exit 0") return 0;
    // std::cout << input << ": command not found" << std::endl;
   if (input == "exit 0") {
      return 0;
    } else if (input.find("echo ") == 0) {
      const int ECHO_LEN = 5; // Length of "echo "
      std::string text = input.substr(ECHO_LEN);
      std::cout << text << std::endl;
    } else {
      std::cout << input << ": command not found" << std::endl;
    }
    
  }

}
