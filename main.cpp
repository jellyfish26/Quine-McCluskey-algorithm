#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool debug = true;

struct logical_expression {
    string variable;
    vector<int> number;
    bool completion;
};

int number_of_variables;
vector<logical_expression> logical_number;
vector<logical_expression> answer;
bool answer_complete = false;
int combined_number[26] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072,
                           262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432}; // A ~ Z

string Constructing_logical_expressions(string input) {
    string output;
    int number_temp = 0;
    vector<int> number;
    if (input.size() != number_of_variables) return "DON'T INPUT (The number of variables is different.)";
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '0' || input[i] == '1') {
            output += input[i];
            if (input[i] == '1') number_temp += combined_number[i];
        } else return "DON'T INPUT (Please enter a binary number.)";
    }
    number.push_back(number_temp);

    for (int i = 0; i < logical_number.size(); i++) {
        if (logical_number[i].number[0] == number_temp) return "DON'T INPUT (It has already been entered.)";
    }

    logical_number.push_back({output, number, false});

    return "INPUT COMPLETE";
}

void First_combining(int bind, int value, string variable) {
    vector<int> number;
    variable[bind] = '-';
    number.push_back(value);
    number.push_back(value + combined_number[bind]);
    answer.push_back({variable, number, false});
}

void First_compare_and_combine() {
    unsigned long int size = logical_number.size();
    for (int comparison = 0; comparison < size; comparison++) {
        for (int object = 0; object < size; object++) {
            if (comparison == object) continue;

            for (int variable_to_bind = 0; variable_to_bind < number_of_variables; variable_to_bind++) {
                if (logical_number[comparison].number[0] > logical_number[object].number[0]) continue;
                int check = logical_number[comparison].number[0] xor logical_number[object].number[0];
                if (debug) cout << check << endl;

                if (check == combined_number[variable_to_bind]) {
                    First_combining(variable_to_bind, logical_number[comparison].number[0],
                                    logical_number[comparison].variable);
                    logical_number[comparison].completion = true;
                    logical_number[object].completion = true;
                    break;
                }
            }
        }
    }

    //Not combine
    for (int comparison = 0; comparison < size; comparison++) {
        if (!logical_number[comparison].completion) {
            answer.push_back({logical_number[comparison].variable, logical_number[comparison].number, false});
        }
    }

}

void Multiple_combining(int bind, vector<int> value, string variable) {
    variable[bind] = '-';
    unsigned long int value_size = value.size();
    for (int high = 0; high < value_size; ++high) {
        value.push_back(value[high] + combined_number[bind]);
    }
    answer.push_back({variable, value, false});
}

bool check_overlap(int comparison, int object) {
    for (int i = 0; i < answer[comparison].number.size(); ++i) {
        for (int j = 0; j < answer[object].number.size(); ++j) {

            if (answer[comparison].number[i] > answer[object].number[j]) return true;
        }
    }

    return false;
}

void Multiple_compare_and_combine() {
    int hierarchy = 2; // The first time is over.
    while (true) {
        if (answer_complete) break;
        answer_complete = true; //init
        for (int comparison = 0; comparison < answer.size(); comparison++) {
            if (answer[comparison].number.size() != hierarchy) continue;

            for (int object = 0; object < answer.size(); ++object) {
                if (answer[object].number.size() != hierarchy) continue;
                answer_complete = false; // There is something to compare

                for (int variable_to_bind = 0; variable_to_bind < number_of_variables; variable_to_bind++) {
                    //if (answer[comparison].number[0] > answer[object].number[0]) continue;
                    int check = answer[comparison].number[0] xor answer[object].number[0];
                    if (check == combined_number[variable_to_bind]) {
                        bool combining = true;
                        for (int high = 1; high < hierarchy; high++) {
                            if (check != (answer[comparison].number[high] xor answer[object].number[high])) combining = false;
                        }

                        if (combining) {
                            answer[comparison].completion = true;
                            answer[object].completion = true;
                            if (check_overlap(comparison, object)) continue;
                            Multiple_combining(variable_to_bind, answer[comparison].number, answer[comparison].variable);
                            break;
                        }
                    }
                }
            }
        }
        hierarchy *= 2;
    }
}

// Ask for an answer

vector<int> value;
vector<logical_expression> items;

void Extraction() {
    for (int i = 0; i < answer.size(); ++i) {
        if (!answer[i].completion) {
            items.push_back({answer[i].variable, answer[i].number, false});
        }
    }

    if (debug) {
        for (int i = 0; i < items.size(); ++i) {
            cout << items[i].variable << endl;
            for (int j = 0; j < items[i].number.size(); ++j) {
                cout << items[i].number[j] << " ";
            }
            cout << endl;
        }
    }
}

bool tables[1000][10000] = {false};
bool choice[10000] = {false};

void Make_table() {
    for (int i = 0; i < items.size(); ++i) {
        for (int j = 0; j < items[i].number.size(); ++j) {
            for (int k = 0; k < value.size(); ++k) {
                if (items[i].number[j] == value[k]) tables[i][k] = true;
            }
        }
    }
}

bool Check_mandatory_items(int item) {
    bool onlyone;
    for (int i = 0; i < value.size(); ++i) {
        onlyone = true;
        if (!tables[item][i]) continue;
        for (int j = 0; j < items.size(); ++j) {
            if (item == j) continue;
            if (tables[j][i]) onlyone = false;
        }

        if (onlyone) return true;
    }

    return false;
}

void Require_essential_items() {
    for (int i = 0; i < answer.size(); ++i) {
        for (int j = 0; j < answer[i].number.size(); ++j) {
            value.push_back(answer[i].number[j]);
        }
    }

    sort(value.begin(), value.end());
    value.erase(unique(value.begin(), value.end()), value.end());
    Extraction();
    Make_table();

    for (int i = 0; i < items.size(); ++i) {
        items[i].completion = Check_mandatory_items(i);
        if (debug) cout << i << " " << items[i].completion << endl;
    }

    if (debug) {
        for (int i = 0; i < items.size(); ++i) {
            for (int j = 0; j < value.size(); ++j) {
                cout << tables[i][j] << " ";
            }
            cout << endl;
        }

        for (int i = 0; i < value.size(); ++i) {
            cout << value[i] << " ";
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
            cout << logical_number[i].variable << endl << logical_number[i].number[0] << endl;
        }
    }
    First_compare_and_combine();

    Multiple_compare_and_combine();

    Require_essential_items();

    return EXIT_SUCCESS;
}