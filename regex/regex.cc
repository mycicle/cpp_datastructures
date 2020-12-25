#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

int main() {
    ifstream file("hwregex.txt");
    string line;
    string text;

    while(getline(file, line)) {
        text.append(line);
    }
    string pattern = R"([A-Z]+[[a-z]*[^?\s\.\,\[\]\{\}\/\\\<\>\"\:\;][a-z]*]*)";
    regex r(pattern);
    smatch match;
    auto start = chrono::system_clock::now();
        while (regex_search(text, match, r)) {
            for (auto m : match) {
                cout << m << '\n';
            }
            text = match.suffix();
        }
    auto end = chrono::system_clock::now();
    cout << "Time to completion: " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " nanoseconds" << '\n';
}