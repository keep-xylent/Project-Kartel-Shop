#ifndef MODELPUBG_H
#define MODELPUBG_H

#include <iostream>
#include "utils.h"

using namespace std;

void receiptPUBG(string item, int qty, int price, int total) {
    clearScreen();
    cout << "\n";
    printDoubleLine();
    cout << "  " << CYAN << "         \uF11B STRUK PEMBELIAN \uF11B" << RESET << "\n";
    printDoubleLine();
    cout << "\n";
    printBoxTop(CYAN);
    drawLine("\uF54E Toko    : KARTEL SHOP", CYAN, GREEN);
    drawLine("\uF007 Pembeli : " + user[tmp], CYAN, GREEN);
    drawLine("\uF11B Game    : PUBG Mobile", CYAN, YELLOW);
    printBoxMiddle(CYAN);
    drawLine("\uF466 Item    : " + item, CYAN, MAGENTA);
    drawLine("\uF080 Jumlah  : " + to_string(qty) + "x", CYAN, CYAN);
    drawLine("\uF0D6 Harga   : Rp " + to_string(price), CYAN, GREEN);
    printBoxMiddle(CYAN);
    drawLine("\uF155 TOTAL   : Rp " + to_string(total), CYAN, GREEN);
    drawLine("\uF3A5 Sisa    : Rp " + to_string(saldo[tmp]), CYAN, YELLOW);
    printBoxBottom(CYAN);
    cout << "\n";
    printSingleLine();
    cout << "  " << GREEN << "   \uF00C Terima kasih telah berbelanja! \uF00C" << RESET << "\n";
    printSingleLine();
    cout << "\n";
}

void menupubg(){
    int ulang;
    header("PUBG MOBILE TOP UP");
    printBoxTop(YELLOW);
    drawCentered("PILIH PAKET UC", YELLOW, YELLOW);
    printBoxBottom(YELLOW);
    
    vector<string> headers = {"No", "UC", "Harga (Rp)"};
    vector<vector<string>> rows;
    for(int i=0; i<indexuc; i++){
        rows.push_back({to_string(i+1), to_string(unknowncash[i]) + " UC", to_string(hargauc[i])});
    }
    drawTable(headers, rows);
    
    cout << "\n  Pilih Nomor => ";
    int pilih;
    cin >> pilih;

    if (pilih < 1 || pilih > indexuc) {
        errorBox("Pilihan tidak valid!");
        this_thread::sleep_for(chrono::milliseconds(1000));
        return;
    }

    cout << "  Jumlah Beli => ";
    int jumlah;
    cin >> jumlah;

    cout << "  Masukkan ID Game => ";
    int idpubg;
    cin >> idpubg;

    int total = hargauc[pilih-1] * jumlah;
    clearScreen();
    header("MEMPROSES PEMBAYARAN...");

    if (saldo[tmp] >= total) {
        loading("Memvalidasi ID Character", 800);
        loading("Memproses Transaksi", 1200);
        
        saldo[tmp] -= total;
        saveData();
        
        string itemName = to_string(unknowncash[pilih-1]) + " UC";
        recordTransaction(user[tmp], itemName, jumlah, total);
        
        receiptPUBG(itemName, jumlah, hargauc[pilih-1], total);
    } else {
        clearScreen();
        header("PEMBELIAN GAGAL");
        errorBox("Saldo tidak mencukupi!");
        cout << "  Saldo Anda  : " << BOLD << YELLOW << "Rp " << saldo[tmp] << RESET << "\n";
        cout << "  Total Harga : " << BOLD << RED << "Rp " << total << RESET << "\n";
        cout << "  Kekurangan  : " << BOLD << RED << "Rp " << (total - saldo[tmp]) << RESET << "\n";
    }

    cout << "\n  Tekan 1 untuk kembali: ";
    cin >> ulang;
    clearScreen();
}

#endif
