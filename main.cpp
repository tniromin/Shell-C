#include <iostream>

// using declartion for cout, endl and string
using std::cout;
using std::endl;
using std::string;


int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  

  while(true){

    cout << "$ ";
    string input;
    getline(std::cin, input);
    // if(input=="exit 0") return 0;
    // std::cout << input << ": command not found" << std::endl;
    bool valid= 1;

    //cout << "Echo test " << (input.find("echo ")==0) << endl;
    //cout << "$" << input.substr(4)<< endl;
    //cout << "TEST : " << (input.find("type ")==0)<< endl;

    if (input == "exit 0") {
      return 0;
    } 
    // var.find() returns 0 if found the object 
    else if (input.find("echo ") == 0) {
      
      const int ECHO_LEN = 5; // Length of "echo "
      //std::cout << "Echo Found";
      std::string text = input.substr(ECHO_LEN);
      std::cout << text << std::endl;
    } else if ((input.find("type ")) == 0){
        //const int ECHO_LEN = 5;
        
        std::string txt = input.substr(5);
            if(txt=="type" || txt=="exit" || txt=="echo"){
              std::cout << txt << " is a shell builtin\n";
            }
            else{
              std::cout << txt << ": not found\n";
            }

    } else {
      std::cout << input << ": command not found" << std::endl;
    }

  }
  

}
