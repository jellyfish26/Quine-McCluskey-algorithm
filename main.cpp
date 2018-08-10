#include <iostream>
#include <vector>
using namespace std;

struct logical_expression {
    string valiable;
    vector<int> number;
};

int Number_of_variables;
vector<logical_expression> logical_number;
int Combined_number[26] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072,
                           262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432}; // A ~ Z

int main() {
    cin >> Number_of_variables;
}