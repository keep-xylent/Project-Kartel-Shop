#ifndef GAMES_H
#define GAMES_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "database.h"
#include "utils.h"

using namespace std;

void minigamesMenu();

void captureID(string item) {
    cout << "\n";
    printBoxTop(GREEN);
    drawLine("\uF091 Pemenang Item: " + item, GREEN, GREEN);
    printBoxMiddle(GREEN);
    cout << "  " << GREEN << "║" << RESET << "  Masukkan ID Game [ML/PUBG] : " << RESET;
    string id;
    cin >> id;
    drawLine("\uF093 Item dikirim ke ID [" + id + "]", GREEN, YELLOW);
    printBoxBottom(GREEN);
    cout << "\n  " << CYAN << "\uF017 Item akan diproses..." << RESET << "\n";
    this_thread::sleep_for(chrono::milliseconds(2000));
}

void luckySlot() {
    int mode = 0;
    string syms[] = {"7", "$", "@", "*", "#", "&"};
    
    while (true) {
        if (mode == 0) {
            header("LUCKY SLOT KARTEL");
            printBoxTop(MAGENTA);
            drawCentered("\uF6D2 LUCKY SLOT \uF6D2", MAGENTA, MAGENTA);
            printBoxMiddle(MAGENTA);
            drawLine("\uF155 Biaya Spin : Rp 10.000", MAGENTA, YELLOW);
            drawLine("\uF3A5 Saldo Anda : Rp " + to_string(saldo[tmp]), MAGENTA, CYAN);
            printBoxBottom(MAGENTA);
            cout << "\n";
            
            if (saldo[tmp] < 10000) {
                errorBox("Saldo tidak cukup!");
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            }
            cout << "  " << GREEN << "[1]" << RESET << " \uF6D2 Spin Sekarang\n";
            cout << "  " << RED << "[2]" << RESET << " Kembali\n";
            cout << "\n  Pilih => ";
            int pil;
            if(!(cin >> pil)) { cin.clear(); cin.ignore(1000, '\n'); break; }
            if (pil != 1) break;
        }

        if (saldo[tmp] < 10000) {
            errorBox("Saldo tidak cukup!");
            this_thread::sleep_for(chrono::milliseconds(1500));
            break;
        }

        saldo[tmp] -= 10000;
        srand(time(0) + rand());
        string s1 = syms[rand() % 6];
        string s2 = syms[rand() % 6];
        string s3 = syms[rand() % 6];
        
        clearScreen();
        header("MEMPUTAR SLOT...");
        reelAnimation(s1, s2, s3);
        
        clearScreen();
        header("HASIL SLOT");
        cout << "\n  " << CYAN << "  ┌─────┬─────┬─────┐" << RESET << "\n";
        cout << "  " << CYAN << "  │" << RESET << "  " << YELLOW << s1 << RESET << "  │  " << YELLOW << s2 << RESET << "  │  " << YELLOW << s3 << RESET << "  " << CYAN << "│" << RESET << "\n";
        cout << "  " << CYAN << "  └─────┴─────┴─────┘" << RESET << "\n\n";

        if (s1 == s2 && s2 == s3) {
            int win = 100000;
            string reward;
            if (s1 == "7") {
                reward = "JACKPOT - 1000 Diamonds";
                captureID(reward);
            } else {
                reward = "JACKPOT - Saldo Rp 100.000";
                printBoxTop(GREEN);
                drawCentered("\uF005\uF005\uF005 JACKPOT! \uF005\uF005\uF005", GREEN, GREEN);
                drawLine("\uF155 Anda menang: Rp " + to_string(win), GREEN, YELLOW);
                printBoxBottom(GREEN);
                saldo[tmp] += win;
            }
            recordWin(user[tmp], reward);
        } else if (s1 == s2 || s2 == s3 || s1 == s3) {
            int win = 15000;
            printBoxTop(CYAN);
            drawCentered("\uF11E MENANG TIPIS!", CYAN, CYAN);
            drawLine("\uF155 Bonus: Rp " + to_string(win), CYAN, YELLOW);
            printBoxBottom(CYAN);
            saldo[tmp] += win;
            recordWin(user[tmp], "Minor Slot Win (Rp 15k)");
        } else {
            errorBox("ZONK! Coba lagi lain kali.");
        }
        
        saveData();
        cout << "\n  \uF3A5 Saldo saat ini: " << BOLD << YELLOW << "Rp " << saldo[tmp] << RESET << "\n";
        cout << "\n  " << GREEN << "[1]" << RESET << " Spin Lagi\n";
        cout << "  " << RED << "[2]" << RESET << " Kembali\n";
        cout << "\n  Pilih => ";
        int pil;
        cin >> pil;
        if (pil == 1) mode = 1;
        else break;
    }
}

void luckySpin() {
    int mode = 0;
    while (true) {
        if (mode == 0) {
            header("LUCKY SPIN KARTEL");
            printBoxTop(CYAN);
            drawCentered("\uF01E LUCKY SPIN \uF01E", CYAN, CYAN);
            printBoxMiddle(CYAN);
            drawLine("\uF155 Biaya Spin : Rp 5.000", CYAN, YELLOW);
            drawLine("\uF3A5 Saldo Anda : Rp " + to_string(saldo[tmp]), CYAN, CYAN);
            printBoxBottom(CYAN);
            cout << "\n";
            
            if (saldo[tmp] < 5000) {
                errorBox("Saldo tidak cukup!");
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            }
            cout << "  " << GREEN << "[1]" << RESET << " \uF01E Putar Sekarang\n";
            cout << "  " << RED << "[2]" << RESET << " Kembali\n";
            cout << "\n  Pilih => ";
            int pil;
            if(!(cin >> pil)) { cin.clear(); cin.ignore(1000, '\n'); break; }
            if (pil != 1) break;
        }

        if (saldo[tmp] < 5000) {
            errorBox("Saldo tidak cukup!");
            this_thread::sleep_for(chrono::milliseconds(1500));
            break;
        }

        saldo[tmp] -= 5000;
        slotAnimation(15);
        
        srand(time(0) + rand());
        int rolled = rand() % 100;
        string rewardName;

        clearScreen();
        header("HASIL SPIN");
        if (rolled < 2) {
            rewardName = "1000 Diamonds ML";
            printBoxTop(GREEN);
            drawCentered("\uF005 SUPER JACKPOT! \uF005", GREEN, GREEN);
            drawLine("\uF06B " + rewardName, GREEN, MAGENTA);
            printBoxBottom(GREEN);
            captureID(rewardName);
            recordWin(user[tmp], rewardName);
        } else if (rolled < 10) {
            rewardName = "Saldo Rp 25.000";
            printBoxTop(YELLOW);
            drawCentered("\uF005 SELAMAT MENANG! \uF005", YELLOW, YELLOW);
            drawLine("\uF155 " + rewardName, YELLOW, GREEN);
            printBoxBottom(YELLOW);
            saldo[tmp] += 25000;
            recordWin(user[tmp], rewardName);
        } else if (rolled < 40) {
            rewardName = "Saldo Rp 5.000";
            printBoxTop(CYAN);
            drawCentered("\uF11E MODAL BALIK!", CYAN, CYAN);
            drawLine("\uF155 " + rewardName, CYAN, CYAN);
            printBoxBottom(CYAN);
            saldo[tmp] += 5000;
            recordWin(user[tmp], rewardName);
        } else {
            errorBox("ZONK! Coba lagi ya.");
        }
        saveData();
        cout << "\n  \uF3A5 Saldo saat ini: " << BOLD << YELLOW << "Rp " << saldo[tmp] << RESET << "\n";
        cout << "\n  " << GREEN << "[1]" << RESET << " Putar Lagi\n";
        cout << "  " << RED << "[2]" << RESET << " Kembali\n";
        cout << "\n  Pilih => ";
        int pil;
        cin >> pil;
        if (pil == 1) mode = 1;
        else break;
    }
}

void mysteryBox() {
    int mode = 0;
    while (true) {
        if (mode == 0) {
            header("MYSTERY BOX KARTEL");
            printBoxTop(MAGENTA);
            drawCentered("\uF06B MYSTERY BOX \uF06B", MAGENTA, MAGENTA);
            printBoxMiddle(MAGENTA);
            drawLine("\uF155 Biaya Buka : Rp 25.000", MAGENTA, YELLOW);
            drawLine("\uF3A5 Saldo Anda : Rp " + to_string(saldo[tmp]), MAGENTA, CYAN);
            drawLine("\uF6D2 Chance Menang : 70%", MAGENTA, GREEN);
            printBoxBottom(MAGENTA);
            cout << "\n";
            
            if (saldo[tmp] < 25000) {
                errorBox("Saldo tidak cukup!");
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            }
            cout << "  " << GREEN << "[1]" << RESET << " \uF06B Buka Mystery Box\n";
            cout << "  " << RED << "[2]" << RESET << " Kembali\n";
            cout << "\n  Pilih => ";
            int pil;
            if(!(cin >> pil)) { cin.clear(); cin.ignore(1000, '\n'); break; }
            if (pil != 1) break;
        }

        if (saldo[tmp] < 25000) {
            errorBox("Saldo tidak cukup!");
            this_thread::sleep_for(chrono::milliseconds(1500));
            break;
        }

        saldo[tmp] -= 25000;
        matrixAnimation(10);
        
        srand(time(0) + rand());
        int rolled = rand() % 100;
        string rewardName;

        clearScreen();
        header("HASIL MYSTERY BOX");
        if (rolled < 10) {
            rewardName = "500 Diamonds / 600 UC";
            printBoxTop(GREEN);
            drawCentered("\uF005 HADIAH SPESIAL! \uF005", GREEN, GREEN);
            drawLine("\uF06B " + rewardName, GREEN, MAGENTA);
            printBoxBottom(GREEN);
            captureID(rewardName);
            recordWin(user[tmp], rewardName);
        } else if (rolled < 30) {
            rewardName = "Saldo Rp 75.000";
            printBoxTop(YELLOW);
            drawCentered("\uF005 SUPER WIN! \uF005", YELLOW, YELLOW);
            drawLine("\uF155 " + rewardName, YELLOW, GREEN);
            printBoxBottom(YELLOW);
            saldo[tmp] += 75000;
            recordWin(user[tmp], rewardName);
        } else if (rolled < 70) {
            rewardName = "Saldo Rp 20.000";
            printBoxTop(CYAN);
            drawCentered("\uF11E COMMON WIN!", CYAN, CYAN);
            drawLine("\uF155 " + rewardName, CYAN, CYAN);
            printBoxBottom(CYAN);
            saldo[tmp] += 20000;
            recordWin(user[tmp], rewardName);
        } else {
            errorBox("ZONK! Habis... Coba lagi!");
        }
        saveData();
        cout << "\n  \uF3A5 Saldo saat ini: " << BOLD << YELLOW << "Rp " << saldo[tmp] << RESET << "\n";
        cout << "\n  " << GREEN << "[1]" << RESET << " Buka Lagi\n";
        cout << "  " << RED << "[2]" << RESET << " Kembali\n";
        cout << "\n  Pilih => ";
        int pil;
        cin >> pil;
        if (pil == 1) mode = 1;
        else break;
    }
}

void viewWinHistory() {
    header("RIWAYAT HADIAH");
    vector<string> headers = {"No", "Pemenang", "Hadiah", "Waktu"};
    vector<vector<string>> rows;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", ltm);
    
    int count = 1;
    for (int i = 0; i < winIndex; i++) {
        if (winUser[i] == user[tmp] || isAdmin) {
            rows.push_back({to_string(count++), winUser[i], winItem[i], timeStr});
        }
    }
    drawTable(headers, rows);
    pressEnter();
}

void minigamesMenu() {
    int ulang;
    do {
        header("KARTEL GAME CENTER");
        printBoxTop(CYAN);
        drawLine("\uF3A5 Saldo : Rp " + to_string(saldo[tmp]), CYAN, YELLOW);
        printBoxBottom(CYAN);
        cout << "\n";
        
        printBoxTop(GREEN);
        drawCentered("\uF11B GAME CENTER \uF11B", GREEN, GREEN);
        printBoxMiddle(GREEN);
        drawLine("[1] \uF01E Lucky Spin", GREEN, CYAN);
        drawLine("[2] \uF06B Mystery Box", GREEN, CYAN);
        drawLine("[3] \uF6D2 Lucky Slot", GREEN, CYAN);
        drawLine("[4] \uF0CA Riwayat Kemenangan", GREEN, CYAN);
        drawLine("[5] \uF3E5 Kembali", GREEN, CYAN);
        printBoxBottom(GREEN);
        cout << "\n  Pilih Game => ";
        
        int pilih;
        cin >> pilih;
        clearScreen();

        switch (pilih) {
            case 1: luckySpin(); ulang = 1; break;
            case 2: mysteryBox(); ulang = 1; break;
            case 3: luckySlot(); ulang = 1; break;
            case 4: viewWinHistory(); ulang = 1; break;
            case 5: ulang = 0; break;
            default: ulang = 1; break;
        }
    } while (ulang == 1);
}

void redeemVoucher() {
    printBoxTop(CYAN);
    drawLine("\uF0EB Voucher aktif : " + activeVoucher, CYAN, GREEN);
    drawLine("\uF06B Nilai Reward   : Rp " + to_string(voucherReward), CYAN, YELLOW);
    printBoxMiddle(CYAN);
    cout << "  " << CYAN << "║" << RESET << "  Masukkan Kode Voucher : " << RESET;
    string code;
    cin >> code;
    printBoxBottom(CYAN);
    
    if (code == activeVoucher) {
        if (!hasRedeemed[tmp]) {
            loading("Memvalidasi kode voucher", 800);
            saldo[tmp] += voucherReward;
            hasRedeemed[tmp] = true;
            saveData();
            clearScreen();
            header("VOUCHER BERHASIL");
            printBoxTop(GREEN);
            drawCentered("\uF00C Voucher berhasil diklaim!", GREEN, GREEN);
            printBoxMiddle(GREEN);
            drawLine("\uF06B Reward : Rp " + to_string(voucherReward), GREEN, GREEN);
            drawLine("\uF3A5 Saldo  : Rp " + to_string(saldo[tmp]), GREEN, GREEN);
            printBoxBottom(GREEN);
        } else {
            errorBox("Voucher sudah pernah diklaim!");
        }
    } else {
        errorBox("Kode voucher tidak valid!");
    }
    
    pressEnter();
}

#endif
