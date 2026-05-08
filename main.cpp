#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

json loadJSON(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
        return json::object();
    json data;
    file >> data;
    return data;
}

void saveJSON(string filename, json data)
{
    ofstream file(filename);
    file << data.dump(4) << endl;
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

    saveJSON("users.json", users);

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

void tambahObat(json &obat)
{
    json o;

    string nama, jenis, expired;
    int harga, stok;

    int nomor = obat["obat"].size() + 1;
    o["id"] = "OB" + to_string(nomor);

    cout << "====== TAMBAH DATA OBAT ======\n";

    cout << "Masukkan Nama Obat : ";
    cin >> nama;

    cout << "Masukkan Jenis Obat : ";
    cin >> jenis;

    cout << "Masukkan Tanggal Kedaluwarsa : ";
    cin >> expired;

    cout << "Masukkan Harga Obat : ";
    cin >> harga;

    cout << "Masukkan Stok Obat : ";
    cin >> stok;

    o["nama"] = nama;
    o["jenis"] = jenis;
    o["expired"] = expired;
    o["harga"] = harga;
    o["stok"] = stok;

    obat["obat"].push_back(o);

    saveJSON("obat.json", obat);

    cout << "Data obat berhasil ditambahkan!\n";
}

void updateObat(json &obat)
{
    tampilkanObat(obat);

    int nomor;

    cout << "\nMasukkan Nomor Obat yang ingin diupdate : ";
    cin >> nomor;

    if (nomor < 1 || nomor > obat["obat"].size())
    {
        setColor(12);
        cout << "Nomor tidak valid!\n";
        setColor(7);
        return;
    }

    string nama, jenis, expired;
    int harga, stok;

    cout << "\n===== UPDATE DATA OBAT =====\n";

    cout << "Masukkan Nama Obat Baru : ";
    cin >> nama;

    cout << "Masukkan Jenis Obat Baru : ";
    cin >> jenis;

    cout << "Masukkan Harga Obat Baru : ";
    cin >> harga;

    cout << "Masukkan Stok Obat Baru : ";
    cin >> stok;

    cout << "Masukkan Tanggal Expired Baru : ";
    cin >> expired;

    obat["obat"][nomor - 1]["nama"] = nama;
    obat["obat"][nomor - 1]["jenis"] = jenis;
    obat["obat"][nomor - 1]["harga"] = harga;
    obat["obat"][nomor - 1]["stok"] = stok;
    obat["obat"][nomor - 1]["expired"] = expired;

    saveJSON("obat.json", obat);

    cout << "\nData obat berhasil diupdate!\n";
}

void hapusObat(json &obat)
{
    tampilkanObat(obat);

    int nomor;

    cout << "\nMasukkan Nomor Obat yang ingin dihapus : ";
    cin >> nomor;

    if (nomor < 1 || nomor > obat["obat"].size())
    {
        cout << "Nomor tidak valid!\n";
        return;
    }

    string nama = obat["obat"][nomor - 1]["nama"];

    obat["obat"].erase(obat["obat"].begin() + (nomor - 1));

    saveJSON("obat.json", obat);

    cout << "Data obat " << nama << " berhasil dihapus!\n";
}

int main()
{
    cout << "Hello, World!" << endl;
    return 0;
}