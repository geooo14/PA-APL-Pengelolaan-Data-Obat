#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

json LoadJSON(string filename)
{
    ifstream i(filename);
    json j;
    i >> j;
    return j;
}

void SaveJSON(string filename, json j)
{
    ofstream o(filename);
    o << j.dump(4) << endl;
}

int main()
{
    cout << "Hello, World!" << endl;
    return 0;
}