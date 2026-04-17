#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "database.h"
#include "utils.h"

using namespace std;

void manageVoucher() {
    header("PENGATURAN VOUCHER");
    printBoxTop(CYAN);
    drawLine("\uF145 Voucher Aktif : " + activeVoucher, CYAN, GREEN);
    drawLine("\uF155 Nilai Reward   : Rp " + to_string(voucherReward), CYAN, YELLOW);
    printBoxBottom(CYAN);
    cout << "\n";
    
    cout << "  " << CYAN << "[1]" << RESET << " Ubah Kode Voucher\n";
    cout << "  " << CYAN << "[2]" << RESET << " Ubah Nilai Reward\n";
    cout << "  " << CYAN << "[3]" << RESET << " Reset Status Klaim Semua User\n";
    cout << "  " << CYAN << "[4]" << RESET << " Kembali\n";
    cout << "\n  Pilih => ";
    int pil;
    cin >> pil;
    
    if (pil == 1) {
        cout << "\n  Masukkan Kode Baru : ";
        cin >> activeVoucher;
        successBox("Kode voucher berhasil diubah!");
    } else if (pil == 2) {
        cout << "\n  Masukkan Reward Baru (Rp) : ";
        cin >> voucherReward;
        successBox("Nilai reward berhasil diubah!");
    } else if (pil == 3) {
        for(int i=0; i<100; i++) hasRedeemed[i] = false;
        successBox("Status klaim semua user di-reset!");
    } else return;

    saveData();
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void managePrices() {
    int ulang;
    do {
        header("MANAJEMEN HARGA");
        printBoxTop(YELLOW);
        drawCentered("\uF013 PENGATURAN HARGA", YELLOW, YELLOW);
        printBoxMiddle(YELLOW);
        drawLine("[1] \uF11B Mobile Legends", YELLOW, CYAN);
        drawLine("[2] \uF11B PUBG Mobile", YELLOW, CYAN);
        drawLine("[3] \uF3E5 Kembali", YELLOW, CYAN);
        printBoxBottom(YELLOW);
        cout << "\n  Pilih => ";
        int pilih;
        cin >> pilih;
        clearScreen();

        if (pilih == 1) {
            header("HARGA MOBILE LEGENDS");
            printBoxTop(GREEN);
            drawCentered("DAFTAR HARGA DIAMOND", GREEN, GREEN);
            printBoxBottom(GREEN);
            
            vector<string> headers = {"ID", "Diamond", "Harga (Rp)"};
            vector<vector<string>> rows;
            for(int i=0; i<indexdm; i++){
                rows.push_back({to_string(i+1), to_string(diamond[i]) + " DM", to_string(hargadm[i])});
            }
            drawTable(headers, rows);
            cout << "\n  Pilih ID untuk diubah => ";
            int id;
            cin >> id;
            if (id > 0 && id <= indexdm) {
                cout << "  Masukkan Harga Baru untuk " << diamond[id-1] << " DM => ";
                cin >> hargadm[id-1];
                saveData();
                successBox("Harga berhasil diperbarui!");
            }
            this_thread::sleep_for(chrono::milliseconds(1000));
        } else if (pilih == 2) {
            header("HARGA PUBG MOBILE");
            printBoxTop(CYAN);
            drawCentered("DAFTAR HARGA UC", CYAN, CYAN);
            printBoxBottom(CYAN);
            
            vector<string> headers = {"ID", "UC", "Harga (Rp)"};
            vector<vector<string>> rows;
            for(int i=0; i<indexuc; i++){
                rows.push_back({to_string(i+1), to_string(unknowncash[i]) + " UC", to_string(hargauc[i])});
            }
            drawTable(headers, rows);
            cout << "\n  Pilih ID untuk diubah => ";
            int id;
            cin >> id;
            if (id > 0 && id <= indexuc) {
                cout << "  Masukkan Harga Baru untuk " << unknowncash[id-1] << " UC => ";
                cin >> hargauc[id-1];
                saveData();
                successBox("Harga berhasil diperbarui!");
            }
            this_thread::sleep_for(chrono::milliseconds(1000));
        } else break;

        cout << "\n  Kembali ke Manajemen Harga?\n";
        cout << "  " << GREEN << "[1]" << RESET << " Ya\n";
        cout << "  " << RED << "[0]" << RESET << " Tidak\n";
        cout << "  Pilih => ";
        cin >> ulang;
        clearScreen();
    } while(ulang == 1);
}

void viewTransactions() {
    header("RIWAYAT TRANSAKSI");
    if (histIndex == 0) {
        printBoxTop(YELLOW);
        drawCentered("Belum ada transaksi tercatat", YELLOW, YELLOW);
        printBoxBottom(YELLOW);
    } else {
        vector<string> headers = {"No", "User", "Item", "Qty", "Total (Rp)"};
        vector<vector<string>> rows;
        for (int i = 0; i < histIndex; i++) {
            rows.push_back({to_string(i+1), histUser[i], histItem[i], to_string(histQty[i]), to_string(histTotal[i])});
        }
        drawTable(headers, rows);
    }
    pressEnter();
}
void manageMembers() {
    int pil;
    do {
        header("MANAJEMEN MEMBER");
        if (userCount == 0) {
            printBoxTop(YELLOW);
            drawCentered("Belum ada member terdaftar", YELLOW, YELLOW);
            printBoxBottom(YELLOW);
        } else {
            vector<string> headers = {"No", "Username", "Saldo", "Join Date", "Status"};
            vector<vector<string>> rows;
            for (int i = 0; i < userCount; i++) {
                string status = userIsBanned[i] ? RED + string("\uF05E BANNED") + RESET : GREEN + string("\uF00C AKTIF") + RESET;
                rows.push_back({to_string(i + 1), user[i], "Rp " + to_string(saldo[i]), userRegDate[i], status});
            }
            drawTable(headers, rows);
        }
        
        cout << "\n  " << CYAN << "[1]" << RESET << " Ban / Unban Member\n";
        cout << "  " << CYAN << "[2]" << RESET << " Hapus Member\n";
        cout << "  " << CYAN << "[3]" << RESET << " Kembali\n";
        cout << "\n  Pilih => ";
        cin >> pil;

        if (pil == 1) {
            cout << "  Pilih Nomor Member => ";
            int num;
            cin >> num;
            if (num > 0 && num <= userCount) {
                userIsBanned[num - 1] = !userIsBanned[num - 1];
                saveData();
                successBox("Status member berhasil diubah!");
            }
        } else if (pil == 2) {
            cout << "  Pilih Nomor Member untuk DIHAPUS => ";
            int num;
            cin >> num;
            if (num > 0 && num <= userCount) {
                for (int j = num - 1; j < userCount - 1; j++) {
                    user[j] = user[j+1];
                    pass[j] = pass[j+1];
                    saldo[j] = saldo[j+1];
                    userRegDate[j] = userRegDate[j+1];
                    userIsBanned[j] = userIsBanned[j+1];
                    hasRedeemed[j] = hasRedeemed[j+1];
                }
                userCount--;
                saveData();
                successBox("Member berhasil dihapus!");
            }
        }
    } while (pil != 3);
}

void adminMenu() {
    int ulang;
    do {
        header("ADMIN CONTROL PANEL");
        printBoxTop(RED);
        drawLine("\uF3ED Status : ADMINISTRATOR", RED, RED);
        printBoxBottom(RED);
        cout << "\n";
        
        printBoxTop(RED);
        drawCentered("\uF013 ADMIN PANEL \uF013", RED, RED);
        printBoxMiddle(RED);
        drawLine("[1] \uF155 Manajemen Harga", RED, CYAN);
        drawLine("[2] \uF145 Pengaturan Voucher", RED, CYAN);
        drawLine("[3] \uF1C0 Lihat Semua Transaksi", RED, CYAN);
        drawLine("[4] \uF007 Manajemen Member", RED, CYAN);
        drawLine("[5] \uF08B Logout Admin", RED, CYAN);
        printBoxBottom(RED);
        cout << "\n  Pilih => ";
        
        int pilih;
        cin >> pilih;
        clearScreen();

        switch (pilih) {
            case 1:
                managePrices();
                ulang = 1;
                break;
            case 2:
                manageVoucher();
                ulang = 1;
                break;
            case 3:
                viewTransactions();
                ulang = 1;
                break;
            case 4:
                manageMembers();
                ulang = 1;
                break;
            case 5:
                loading("Logging out Admin", 800);
                isAdmin = false;
                ulang = 0;
                break;
            default:
                ulang = 1;
                break;
        }
    } while(ulang == 1);
}

#endif
