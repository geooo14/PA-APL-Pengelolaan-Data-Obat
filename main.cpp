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

void setColor(int color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color);
}

void registerUser(json &users)
{
    string username, password;
    setColor(9);
    cout << "\n===== REGISTER =====\n";
    setColor(7);

    setColor(3);
    cout << "Enter username: ";
    setColor(7);
    cin >> username;

    for (auto &u : users["users"])
    {
        if (u["username"] == username)
        {
            cout << "Username telah digunakan!\n";
            return;
        }
    }

    cout << "Enter password: ";
    cin >> password;

    json u;

    u["username"] = username;
    u["password"] = password;

    // default role register = kasir
    u["role"] = "kasir";

    users["users"].push_back(u);

    cout << "Registrasi berhasil!\n";
}

string loginUser(json users)
{
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (auto &u : users["users"])
    {
        if (u["username"] == username && u["password"] == password)
        {
            return u["role"];
        }
    }
    return "gagal";
}

void tampilkanObat(json obat)
{
    setColor(11);

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                         DATA OBAT APOTEK                                   ║\n";
    cout << "╠════╦══════╦════════════════╦════════════╦══════════╦══════════╦═══════════ ╣\n";

    setColor(14);

    cout << "║ No ║ ID   ║ Nama Obat      ║ Jenis      ║ Harga    ║ Stok     ║ Expired    ║\n";

    setColor(11);

    cout << "╠════╬══════╬════════════════╬════════════╬══════════╬══════════╬═══════════ ╣\n";

    int no = 1;

    for (auto &o : obat["obat"])
    {
        setColor(7);

        cout << "║ "
             << left << setw(3) << no++
             << "║ "
             << setw(5) << o["id"].get<string>()
             << "║ "
             << setw(15) << o["nama"].get<string>()
             << "║ "
             << setw(11) << o["jenis"].get<string>()
             << "║ "
             << setw(9) << o["harga"].get<int>()
             << "║ "
             << setw(9) << o["stok"].get<int>()
             << "║ "
             << setw(10)
             << (o.contains("expired") ? o["expired"].get<string>() : "-")
             << "║\n";
    }

    setColor(11);

    cout << "╚════╩══════╩════════════════╩════════════╩══════════╩══════════╩═══════════ ╝\n";

    setColor(7);
}

int main()
{
    cout << "Hello, World!" << endl;
    return 0;
}