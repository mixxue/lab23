#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

vector<string> names;
vector<int> scores;
vector<char> grades;

char calculateGrade(int score) {
    if (score >= 80) return 'A';
    if (score >= 70) return 'B';
    if (score >= 60) return 'C';
    if (score >= 50) return 'D';
    return 'F';
}

void importDataFromFile(string filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int score1, score2, score3;
        getline(ss, name, ':');
        ss >> score1 >> score2 >> score3;
        
        names.push_back(name);
        int totalScore = score1 + score2 + score3;
        scores.push_back(totalScore);
        grades.push_back(calculateGrade(totalScore));
    }
}

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void searchName(string key) {
    key = toLowerCase(key);
    bool found = false;
    cout << "---------------------------------" << endl;
    for (size_t i = 0; i < names.size(); i++) {
        if (toLowerCase(names[i]) == key) {
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}

void searchGrade(char grade) {
    grade = toupper(grade);
    bool found = false;
    cout << "---------------------------------" << endl;
    for (size_t i = 0; i < grades.size(); i++) {
        if (grades[i] == grade) {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}

void getCommand() {
    string command;
    while (true) {
        cout << "Please input your command:" << endl;
        getline(cin, command);
        stringstream ss(command);
        string action, key;
        ss >> action >> ws;
        getline(ss, key);
        
        action = toLowerCase(action);
        
        if (action == "name") {
            searchName(key);
        } else if (action == "grade" && key.length() == 1) {
            searchGrade(key[0]);
        } else if (action == "exit") {
            break;
        } else {
            cout << "---------------------------------" << endl;
            cout << "Invalid command." << endl;
            cout << "---------------------------------" << endl;
        }
    }
}

int main() {
    importDataFromFile("name_score.txt");
    getCommand();
    return 0;
}
