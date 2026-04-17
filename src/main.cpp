#include <iostream>
#include "model.h"
#include "utils.h"
using namespace std;

int main(){
    system("chcp 65001 > nul");
    loadData();
    clearScreen();
    loading("Memulai Kartel Shop", 1000);
    
    string ulang;
    do{
        system("cls");
        bigHeader();
        
        printBoxTop(MAGENTA);
        drawCentered("\uF0C9 MENU UTAMA", MAGENTA, MAGENTA);
        printBoxMiddle(MAGENTA);
        drawLine("[1] \uF023 Login", MAGENTA, CYAN);
        drawLine("[2] \uF040 Register", MAGENTA, CYAN);
        drawLine("[3] \uF0C0 List Member", MAGENTA, CYAN);
        drawLine("[4] \uF08B Exit", MAGENTA, CYAN);
        printBoxBottom(MAGENTA);
        cout << "\n  " << CYAN << "Pilih Menu => " << RESET;

        
        int pilih;
        if (!(cin >> pilih)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        
        clearScreen();
        switch(pilih){
            case 1:
                {
                    int loginGagal = 0;
                    do {
                        cocok = 0; 
                        header("LOGIN AREA");
                        loginmember();
                        if(cocok == 1){
                            if(isAdmin) {
                                loading("Proses Login Admin", 1000);
                                adminMenu();
                            } else {
                                loading("Proses Login", 800);
                                mainmenu();
                            }
                            loginGagal = 0;
                        } else {
                            clearScreen();
                            header("LOGIN GAGAL");
                            errorBox("Username atau Password Salah!");
                            cout << "  " << CYAN << "Coba lagi? " << RESET;
                            cout << "[" << GREEN << "y" << RESET << "/" << RED << "n" << RESET << "]: ";
                            string coba;
                            cin >> coba;
                            if (coba == "y" || coba == "Y") loginGagal = 1;
                            else loginGagal = 0;
                            clearScreen();
                        }
                    } while(loginGagal == 1);
                }
                break;
            case 2:
                header("REGISTER MEMBER");
                addmember();
                loading("Menyimpan Data", 1000);
                successBox("Registrasi Berhasil!");
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            case 3:
                readlistmember();
                break;
            case 4:
                header("EXIT");
                cout << "\n";
                printDoubleLine();
                cout << "  " << GREEN << "        Terima kasih telah berkunjung!" << RESET << "\n";
                cout << "  " << GREEN << "           Semoga harimu menyenangkan!       " << RESET << "\n";
                printDoubleLine();
                cout << "\n";
                this_thread::sleep_for(chrono::milliseconds(1500));
                return 0;
            default:
                header("ERROR");
                errorBox("Pilihan tidak tersedia!");
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }

        clearScreen();
        header("KARTEL SHOP");
        cout << "  " << CYAN << "Kembali ke Menu Utama? " << RESET << "[" << GREEN << "y" << RESET << "/" << RED << "n" << RESET << "]: ";
        cin >> ulang;
    } while(ulang == "y" || ulang == "Y");

    return 0;
}
