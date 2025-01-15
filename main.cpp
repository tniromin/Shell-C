#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
using namespace std;

string get_path(const string& command) {
    const char* path_env = getenv("PATH");
    if (!path_env) return "";  // Handle case where PATH is not set

    string path_env_str = path_env;
    string delimiter = ":";
    size_t pos = 0;

    while ((pos = path_env_str.find(delimiter)) != string::npos) {
        string path = path_env_str.substr(0, pos);
        path_env_str.erase(0, pos + delimiter.length());
        filesystem::path candidate = filesystem::path(path) / command;
        if (filesystem::exists(candidate) && !filesystem::is_directory(candidate)) {
            return candidate.string();
        }
    }

    return "";
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  

  while(true){

    cout << "$ ";
    string input;
    getline(std::cin, input);
 
    bool valid= 1;

   

    if (input == "exit 0") {
      return 0;
    } 
    // var.find() returns 0 if found the object 
    else if (input.find("echo ") == 0) {
      
      const int ECHO_LEN = 5; // Length of "echo "
      //std::cout << "Echo Found";
      string text = input.substr(ECHO_LEN);
      cout << text << endl;
    } else if ((input.find("type ")) == 0){
        //const int ECHO_LEN = 5;
        
        std::string txt = input.substr(5);
            if(txt=="type" || txt=="exit" || txt=="echo"){
              cout << txt << " is a shell builtin\n";
            }
            else{
              //cout << txt << ": not found\n";
              string path = get_path(txt);
                 if(path.empty()){

                        std::cout<<txt<<" not found\n";

                    }

                    else{

                        cout<<txt<<" is "<<path<<std::endl;

                    }
            }
    } else {
      cout << input << ": command not found" << endl;
    }
  }
}
