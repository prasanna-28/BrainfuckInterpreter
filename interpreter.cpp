#include <bits/stdc++.h>
using namespace std;

char lexicon[] = {'+', '-', '>', '<', '.', ',', '[', ']'};

bool error_occurred = false;

void error(const string& message) {
    cerr << "\033[91m" << message << "\033[00m" << endl;
    error_occurred = true;
}

class Brainfuck {
private:
    vector<char> bytecells;
    int ptr;
    int pos;
    stack<int> stack;
    string content;

public:
    Brainfuck(const string& filename)
        : bytecells(30000, 0), ptr(0), pos(0) {
        ifstream file(filename);
        if (!file.is_open()) {
            error("Unable to open file");
            exit(1);
        }
        getline(file, content, '\0');
        file.close();
    }

    void output() { cout << bytecells[ptr]; }

    void input() {
        char c;
        cin >> c;
        bytecells[ptr] = c;
    }

    void increment() { bytecells[ptr] = (bytecells[ptr] + 1) % 256; }

    void decrement() { bytecells[ptr] = (bytecells[ptr] - 1) % 256; }

    void up() { ptr = (ptr + 1) % 30000; }

    void down() { ptr = (ptr - 1) % 30000; }

    void parser(char command) {
        if (command == '+') increment();
        else if (command == '-') decrement();
        else if (command == '>') up();
        else if (command == '<') down();
        else if (command == '.') output();
        else if (command == ',') input();
    }

    void execute() {
        while (pos < content.size() && !error_occurred) {
            char command = content[pos];
            if (command == '[') {
                stack.push(pos);
            } else if (command == ']') {
                if (stack.empty()) {
                    error("Closing ']' encountered without previous '['");
                } else if (bytecells[ptr] != 0) {
                    pos = stack.top();
                } else {
                    stack.pop();
                }
            } else {
                parser(command);
            }
            pos++;
        }
    }
};

int main() {
    Brainfuck bf("main.bf");
    bf.execute();
    return 0;
}
