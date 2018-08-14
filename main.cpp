#include <iostream>
#include <vector>
using namespace std;

struct logical_expression {
    string valiable;
    int number;
};

int Number_of_variables;
vector<logical_expression> logical_number;
int Combined_number[26] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072,
                           262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432}; // A ~ Z

string Constructing_logical_expressions(string input) {
    string output;
    int number = 0;
    if (input.size() != Number_of_variables) return "DON'T INPUT (The number of variables is different.)";
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '0' || input[i] == '1') {
            output.append(1, input[i]);
            if (input[i] == '1') number += Combined_number[i];
        } else return "DON'T INPUT (Please enter a binary number.)";
    }

    for (int i = 0; i < logical_number.size(); i++) {
        if(logical_number[i].number == number) return "DON'T INPUT (It has already been entered.)";
    }

    logical_number.push_back({output, number});

    return "INPUT COMPLETE";
}

void debug() {
    for(int i = 0; i < logical_number.size(); i++) {
        cout << logical_number[i].valiable << endl << logical_number[i].number << endl;
    }
}

int main() {
    cout << "Please enter the number of logical variables." << endl;
    cin >> Number_of_variables;
    while (true) {
        cout << "Please enter a logical expression. (A ~ " << (char)('A' + Number_of_variables - 1) << ")" << endl;
        string temp;
        cin >> temp;
        cout << Constructing_logical_expressions(temp) << endl;
        cout << "Add logical expression? (y / n)";
        char choice;
        cin >> choice;
        if (choice == 'n') break;
    }

    debug();

    return 0;
}