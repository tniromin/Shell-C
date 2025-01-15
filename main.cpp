#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include <sys/wait.h>
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

vector<string> split(const string& input) {
    vector<string> result;
    istringstream iss(input);
    string word;
    while (iss >> word) {
        result.push_back(word);
    }
    return result;
}

int main() {
    cout << std::unitbuf;  // Flush after every std::cout
    cerr << std::unitbuf;

    while (true) {
        cout << "$ ";
        string input;
        getline(cin, input);

        if (input.empty()) continue;

        if (input == "exit 0") {
            return 0;
        }

        vector<string> tokens = split(input);
        string command = tokens[0];

        if (command == "echo") {
            for (size_t i = 1; i < tokens.size(); ++i) {
                if (i > 1) cout << " ";
                cout << tokens[i];
            }
            cout << endl;
        } else if (command == "type") {
            if (tokens.size() != 2) {
                cerr << "Usage: type <command>" << endl;
                continue;
            }
            string cmd_to_check = tokens[1];
            if (cmd_to_check == "type" || cmd_to_check == "exit" || cmd_to_check == "echo") {
                cout << cmd_to_check << " is a shell builtin\n";
            } else {
                string path = get_path(cmd_to_check);
                if (path.empty()) {
                    cout << cmd_to_check << ": not found\n";
                } else {
                    cout << cmd_to_check << " is " << path << endl;
                }
            }
        } else {
            string path = get_path(command);
            if (path.empty()) {
                cerr << command << ": command not found" << endl;
                continue;
            }

            // Prepare arguments for execvp
            vector<char*> args;
            for (const auto& token : tokens) {
                args.push_back(const_cast<char*>(token.c_str()));
            }
            args.push_back(nullptr);  // Null-terminate the arguments array

            pid_t pid = fork();
            if (pid == 0) {
                // In child process
                execvp(path.c_str(), args.data());
                perror("execvp");  // If execvp fails
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                // In parent process
                int status;
                waitpid(pid, &status, 0);  // Wait for child to finish
            } else {
                perror("fork");
            }
        }
    }

    return 0;
}
