
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    fstream file;
    vector<string> jokes;
    string line, command;

    // Open the jokes file
    file.open("randomJokes.txt", ios::in);

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    // Read all jokes from the file
    while (getline(file, line)) {
        if (line.find('?') != string::npos) {
            jokes.push_back(line);
        }
    }

    file.close();

    if (jokes.empty()) {
        cout << "No jokes found!" << endl;
        return 1;
    }

    srand(time(0));

    cout << "Welcome to Alexa Joke Generator!" << endl;
    cout << "Type: Alexa, tell me a joke" << endl;
    cout << "Type: quit to exit" << endl;

    while (true) {
        cout << "\nEnter command: ";
        getline(cin, command);

        if (command == "quit") {
            cout << "Goodbye!" << endl;
            break;
        }
        else if (command == "Alexa, tell me a joke") {

            int randomIndex = rand() % jokes.size();
            string joke = jokes[randomIndex];

            int position = joke.find('?');

            string setup = joke.substr(0, position + 1);
            string punchline = joke.substr(position + 1);

            cout << "\n" << setup << endl;

            cout << "Press Enter to see the punchline...";
            string answer;
            getline(cin, answer);

            cout << punchline << endl;
        }
        else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}
