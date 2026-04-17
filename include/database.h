#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <direct.h>
#include <ctime>

using namespace std;

// User Data
extern string user[100];
extern string pass[100];
extern int saldo[100];
extern string userRegDate[100];
extern bool userIsBanned[100];
extern int userCount;

// Global State
extern string inputuser;
extern string inputpass;
extern int cocok;
extern int tmp;
extern int inputsaldo;
extern bool isAdmin;

// Game Data - ML
extern int diamond[100];
extern int hargadm[100];
extern int indexdm;

// Game Data - PUBG
extern int unknowncash[100];
extern int hargauc[100];
extern int indexuc;

// Transaction History (Store Purchases)
extern string histUser[500];
extern string histItem[500];
extern int histQty[500];
extern int histTotal[500];
extern int histIndex;

// Voucher System
extern string activeVoucher;
extern int voucherReward;
extern bool hasRedeemed[100];

// Gacha Win History (Store Lucky Wins)
extern string winUser[500];
extern string winItem[500];
extern int winIndex;

// Definitions
#ifndef DB_DEFINED
#define DB_DEFINED
string user[100];
string pass[100];
int saldo[100];
string userRegDate[100];
bool userIsBanned[100] = {false};
int userCount = 0;

string inputuser;
string inputpass;
int cocok = 0;
int tmp = 0;
int inputsaldo = 0;
bool isAdmin = false;

int diamond[100] = {100, 200, 300, 400};
int hargadm[100] = {10000, 20000, 30000, 40000};
int indexdm = 4;

int unknowncash[100] = {60, 325, 660, 1800};
int hargauc[100] = {15000, 75000, 150000, 350000};
int indexuc = 4;

string histUser[500];
string histItem[500];
int histQty[500];
int histTotal[500];
int histIndex = 0;

string activeVoucher = "KARTEL_GAS";
int voucherReward = 5000;
bool hasRedeemed[100] = {false};

string winUser[500];
string winItem[500];
int winIndex = 0;
#endif

// Alias for backward compatibility
#define index userCount

// Persistence Functions
inline void saveData() {
    _mkdir("data");
    string basePath = "data/";
    // Save Users
    ofstream userFile(basePath + "users.dat");
    if (userFile.is_open()) {
        userFile << userCount << endl;
        for (int i = 0; i < userCount; i++) {
            userFile << user[i] << " " << pass[i] << " " << saldo[i] << " " << (hasRedeemed[i] ? 1 : 0) << " " << userRegDate[i] << " " << (userIsBanned[i] ? 1 : 0) << endl;
        }
        userFile.close();
    }

    // Save Settings (Prices & Voucher)
    ofstream settingsFile(basePath + "settings.dat");
    if (settingsFile.is_open()) {
        for (int i = 0; i < indexdm; i++) settingsFile << hargadm[i] << " ";
        settingsFile << endl;
        for (int i = 0; i < indexuc; i++) settingsFile << hargauc[i] << " ";
        settingsFile << endl;
        settingsFile << activeVoucher << " " << voucherReward << endl;
        settingsFile.close();
    }

    // Save Win History (Gacha)
    ofstream winFile(basePath + "wins.dat");
    if (winFile.is_open()) {
        winFile << winIndex << endl;
        for (int i = 0; i < winIndex; i++) {
            string itemName = winItem[i];
            replace(itemName.begin(), itemName.end(), ' ', '_'); 
            winFile << winUser[i] << " " << itemName << endl;
        }
        winFile.close();
    }

    // Save Purchase History (Transaction)
    ofstream purchaseFile(basePath + "purchases.dat");
    if (purchaseFile.is_open()) {
        purchaseFile << histIndex << endl;
        for (int i = 0; i < histIndex; i++) {
            string itemName = histItem[i];
            replace(itemName.begin(), itemName.end(), ' ', '_');
            purchaseFile << histUser[i] << " " << itemName << " " << histQty[i] << " " << histTotal[i] << endl;
        }
        purchaseFile.close();
    }
}

inline void loadData() {
    string basePath = "data/";
    // Load Users
    ifstream userFile(basePath + "users.dat");
    if (userFile.is_open()) {
        userFile >> userCount;
        for (int i = 0; i < userCount; i++) {
            int redeemedInt, bannedInt;
            userFile >> user[i] >> pass[i] >> saldo[i] >> redeemedInt >> userRegDate[i] >> bannedInt;
            hasRedeemed[i] = (redeemedInt == 1);
            userIsBanned[i] = (bannedInt == 1);
        }
        userFile.close();
    }

    // Load Settings (Prices & Voucher)
    ifstream settingsFile(basePath + "settings.dat");
    if (settingsFile.is_open()) {
        for (int i = 0; i < indexdm; i++) settingsFile >> hargadm[i];
        for (int i = 0; i < indexuc; i++) settingsFile >> hargauc[i];
        settingsFile >> activeVoucher >> voucherReward;
        settingsFile.close();
    }

    // Load Win History
    ifstream winFile(basePath + "wins.dat");
    if (winFile.is_open()) {
        if (winFile >> winIndex) {
            for (int i = 0; i < winIndex; i++) {
                winFile >> winUser[i] >> winItem[i];
                replace(winItem[i].begin(), winItem[i].end(), '_', ' ');
            }
        }
        winFile.close();
    }

    // Load Purchase History
    ifstream purchaseFile(basePath + "purchases.dat");
    if (purchaseFile.is_open()) {
        if (purchaseFile >> histIndex) {
            for (int i = 0; i < histIndex; i++) {
                purchaseFile >> histUser[i] >> histItem[i] >> histQty[i] >> histTotal[i];
                replace(histItem[i].begin(), histItem[i].end(), '_', ' ');
            }
        }
        purchaseFile.close();
    }
}

// Helper to record purchase history
inline void recordTransaction(string u, string item, int qty, int total) {
    if (histIndex < 500) {
        histUser[histIndex] = u;
        histItem[histIndex] = item;
        histQty[histIndex] = qty;
        histTotal[histIndex] = total;
        histIndex++;
        saveData();
    }
}

// Helper to record win history
inline void recordWin(string u, string reward) {
    if (winIndex < 500) {
        winUser[winIndex] = u;
        winItem[winIndex] = reward;
        winIndex++;
        saveData();
    }
}

#endif
