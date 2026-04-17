#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include "database.h"
#include "modelml.h"
#include "modelpubg.h"
#include "admin.h"
#include "games.h"
#include "utils.h"

using namespace std;

void addmember(){
    cout << "\n";
    printBoxTop(YELLOW);
    drawCentered("\uF040 FORM REGISTRASI MEMBER", YELLOW, YELLOW);
    printBoxMiddle(YELLOW);
    cout << "  " << YELLOW << "║" << RESET << "  Username : " << RESET;
    cin >> user[index];
    cout << "  " << YELLOW << "║" << RESET << "  Password : " << RESET;
    cin >> pass[index];
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char dateBuf[12];
    strftime(dateBuf, sizeof(dateBuf), "%d-%m-%Y", ltm);
    userRegDate[index] = string(dateBuf);
    userIsBanned[index] = false;
    index++;
    saveData();
    printBoxBottom(YELLOW);
}

void loginmember(){
    cout << "\n";
    printBoxTop(CYAN);
    drawCentered("\uF023 LOGIN MEMBER", CYAN, YELLOW);
    printBoxMiddle(CYAN);
    cout << "  " << CYAN << "║" << RESET << "  Username : " << RESET;
    cin >> inputuser;
    cout << "  " << CYAN << "║" << RESET << "  Password : " << RESET;
    cin >> inputpass;
    printBoxBottom(CYAN);

    if (inputuser == "admin" && inputpass == "admin123") {
        isAdmin = true;
        cocok = 1;
        return;
    }

    isAdmin = false;
    for (int i=0; i<index; i++){
        if (inputuser == user[i] && inputpass == pass[i]){
            if (userIsBanned[i]) {
                errorBox("AKUN ANDA TELAH DIBANNED!");
                this_thread::sleep_for(chrono::milliseconds(2000));
                return;
            }
            cocok = 1;
            tmp = i;
            break;
        }
    }
}

void readlistmember(){
    header("DAFTAR MEMBER KARTEL");
    if (index == 0) {
        printBoxTop(YELLOW);
        drawCentered("Belum ada member terdaftar", YELLOW, YELLOW);
        printBoxBottom(YELLOW);
    } else {
        vector<string> headers = {"No", "Username", "Status Saldo"};
        vector<vector<string>> rows;
        for(int i=0; i<index; i++){
            rows.push_back({to_string(i+1), user[i], "Rp " + to_string(saldo[i])});
        }
        drawTable(headers, rows);
    }
    pressEnter();
}

void mainmenu(){
    int ulang;
    do{
        header("MEMBER AREA");
        printBoxTop(CYAN);
        drawLine("\uF2BD Selamat Datang, " + user[tmp] + "!", CYAN, GREEN);
        drawLine("\uF155 Saldo : Rp " + to_string(saldo[tmp]), CYAN, YELLOW);
        printBoxBottom(CYAN);
        cout << "\n";
        
        printBoxTop(YELLOW);
        drawCentered("\uF0C9 MENU MEMBER", YELLOW, CYAN);
        printBoxMiddle(YELLOW);
        drawLine("[1] \uF0D6 Top Up Saldo", YELLOW, YELLOW);
        drawLine("[2] \uF11B Top Up Game", YELLOW, YELLOW);
        drawLine("[3] \uF6D2 Mini Games", YELLOW, YELLOW);
        drawLine("[4] \uF145 Klaim Voucher", YELLOW, YELLOW);
        drawLine("[5] \uF08B Logout", YELLOW, YELLOW);
        printBoxBottom(YELLOW);
        cout << "\n  " << CYAN << "Pilih Menu => " << RESET;
        
        int pilih;
        cin >> pilih;
        clearScreen();

        switch (pilih){
            case 1:
                {
                    int inputNominal;
                    do {
                        header("TOP UP SALDO");
                        printBoxTop(CYAN);
                        drawLine("\uF0EB Minimal Top Up: Rp 10.000", CYAN, YELLOW);
                        printBoxMiddle(CYAN);
                        cout << "  " << CYAN << "║" << RESET << "  Masukkan Nominal : Rp " << RESET;
                        cin >> inputNominal;
                        printBoxBottom(CYAN);
                        if(inputNominal < 10000) {
                            errorBox("Nominal minimal Rp 10.000!");
                            this_thread::sleep_for(chrono::milliseconds(500));
                            clearScreen();
                        }
                    } while(inputNominal < 10000);

                    loading("Memproses Top Up", 1200);
                    saldo[tmp] += inputNominal;
                    saveData();
                    clearScreen();
                    header("TOP UP BERHASIL");
                    printBoxTop(GREEN);
                    drawLine("\uF00C Top Up Berhasil!", GREEN, GREEN);
                    printBoxMiddle(GREEN);
                    drawLine("Nominal   : Rp " + to_string(inputNominal), GREEN, GREEN);
                    drawLine("Saldo Baru: Rp " + to_string(saldo[tmp]), GREEN, GREEN);
                    printBoxBottom(GREEN);
                    cout << "\n  Tekan 1 untuk kembali: ";
                    cin >> ulang;
                    clearScreen();
                }
                break;

            case 2:
                {
                    header("PILIH GAME");
                    printBoxTop(MAGENTA);
                    drawCentered("\uF11B PILIH GAME UNTUK TOP UP", MAGENTA, MAGENTA);
                    printBoxMiddle(MAGENTA);
                    drawLine("[1] \uF11B Mobile Legends", MAGENTA, CYAN);
                    drawLine("[2] \uF11B PUBG Mobile", MAGENTA, CYAN);
                    drawLine("[3] \uF3E5 Kembali", MAGENTA, CYAN);
                    printBoxBottom(MAGENTA);
                    cout << "\n  Pilih Game => ";
                    int pilihGame;
                    cin >> pilihGame;
                    if(pilihGame == 1) menuml();
                    else if(pilihGame == 2) menupubg();
                    ulang = 1;
                }
                break;
            
            case 3:
                minigamesMenu();
                ulang = 1;
                break;

            case 4:
                redeemVoucher();
                ulang = 1;
                break;

            case 5:
                loading("Logging out", 800);
                ulang = 0;
                break;
            default:
                ulang = 1;
                break;
        }
    } while(ulang == 1);
}

#endif
