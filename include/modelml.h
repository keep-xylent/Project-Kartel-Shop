#ifndef MODELML_H
#define MODELML_H

#include <iostream>
#include "utils.h"

using namespace std;

void receiptML(string item, int qty, int price, int total) {
    clearScreen();
    cout << "\n";
    printDoubleLine();
    cout << "  " << GREEN << "         \uF11B STRUK PEMBELIAN \uF11B" << RESET << "\n";
    printDoubleLine();
    cout << "\n";
    printBoxTop(GREEN);
    drawLine("\uF54E Toko    : KARTEL SHOP", GREEN, CYAN);
    drawLine("\uF007 Pembeli : " + user[tmp], GREEN, GREEN);
    drawLine("\uF11B Game    : Mobile Legends", GREEN, MAGENTA);
    printBoxMiddle(GREEN);
    drawLine("\uF466 Item    : " + item, GREEN, YELLOW);
    drawLine("\uF080 Jumlah  : " + to_string(qty) + "x", GREEN, CYAN);
    drawLine("\uF0D6 Harga   : Rp " + to_string(price), GREEN, GREEN);
    printBoxMiddle(GREEN);
    drawLine("\uF155 TOTAL   : Rp " + to_string(total), GREEN, GREEN);
    drawLine("\uF3A5 Sisa    : Rp " + to_string(saldo[tmp]), GREEN, YELLOW);
    printBoxBottom(GREEN);
    cout << "\n";
    printSingleLine();
    cout << "  " << GREEN << "   \uF00C Terima kasih telah berbelanja! \uF00C" << RESET << "\n";
    printSingleLine();
    cout << "\n";
}

void menuml(){
    int ulang;
    header("MOBILE LEGENDS TOP UP");
    printBoxTop(GREEN);
    drawCentered("PILIH PAKET DIAMOND", GREEN, GREEN);
    printBoxBottom(GREEN);
    
    vector<string> headers = {"No", "Diamond", "Harga (Rp)"};
    vector<vector<string>> rows;
    for(int i=0; i<indexdm; i++){
        rows.push_back({to_string(i+1), to_string(diamond[i]) + " DM", to_string(hargadm[i])});
    }
    drawTable(headers, rows);
    
    cout << "\n  Pilih Nomor => ";
    int pilih;
    cin >> pilih;

    if (pilih < 1 || pilih > indexdm) {
        errorBox("Pilihan tidak valid!");
        this_thread::sleep_for(chrono::milliseconds(1000));
        return;
    }

    cout << "  Jumlah Beli => ";
    int jumlah;
    cin >> jumlah;

    cout << "  Masukkan ID Game => ";
    int idml;
    cin >> idml;

    int total = hargadm[pilih-1] * jumlah;
    clearScreen();
    header("MEMPROSES PEMBAYARAN...");

    if (saldo[tmp] >= total) {
        loading("Memvalidasi ID Game", 800);
        loading("Memproses Pembayaran", 1200);
        
        saldo[tmp] -= total;
        saveData();
        
        string itemName = to_string(diamond[pilih-1]) + " Diamonds";
        recordTransaction(user[tmp], itemName, jumlah, total);
        
        receiptML(itemName, jumlah, hargadm[pilih-1], total);
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
