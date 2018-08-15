#include <iostream>
#include <vector>
#include <limits>

using namespace std;
bool debug = true;

struct logical_expression {
    string valiable;
    vector<int> number;
};

int number_of_variables;
vector<logical_expression> logical_number;
vector<logical_expression> answer;
bool answer_complete = false;
int Combined_number[26] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072,
                           262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432}; // A ~ Z

string Constructing_logical_expressions(string input) {
    string output;
    int number_temp = 0;
    vector<int> number;
    if (input.size() != number_of_variables) return "DON'T INPUT (The number of variables is different.)";
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '0' || input[i] == '1') {
            output += input[i];
            if (input[i] == '1') number_temp += Combined_number[i];
        } else return "DON'T INPUT (Please enter a binary number.)";
    }
    number.push_back(number_temp);

    for (int i = 0; i < logical_number.size(); i++) {
        if (logical_number[i].number[0] == number_temp) return "DON'T INPUT (It has already been entered.)";
    }

    logical_number.push_back({output, number});

    return "INPUT COMPLETE";
}

void Combining(int value) {

}

void First_compare_and_combine() {
    answer_complete = true;

    unsigned long int size = logical_number.size();
    for (int comparison = 0; comparison < size; comparison++) {
        for (int object = 0; object < size; object++) {
            if (comparison == object) continue;

            for (int variable_to_bind = 0; variable_to_bind < number_of_variables; variable_to_bind++) {
                int check = logical_number[comparison].number[0] xor logical_number[object].number[0];
                if (debug) cout << check << endl;

                if (check == Combined_number[variable_to_bind]) {

                }
            }
        }
    }
}

int main() {
    cout << "Please enter the number of logical variables." << endl;
    cin >> number_of_variables;
    while (true) {
        cout << "Please enter a logical expression. (A ~ " << (char)('A' + number_of_variables - 1) << ")" << endl;
        string temp;
        cin >> temp;
        cout << Constructing_logical_expressions(temp) << endl;
        cout << "Add logical expression? (y / n)";
        char choice;
        cin >> choice;
        if (choice == 'n') break;
    }

    if (debug) {
        for (int i = 0; i < logical_number.size(); i++) {
            cout << logical_number[i].valiable << endl << logical_number[i].number[0] << endl;
        }
    }

    First_compare_and_combine();

    return 0;
}