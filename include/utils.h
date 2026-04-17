#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define BOLD    "\033[1m"

const int BOX_WIDTH = 86;

int getVisibleLength(const string& s) {
    int len = 0;
    bool inEscape = false;
    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] == '\033') {
            inEscape = true;
        } else if (inEscape) {
            if (s[i] >= '@' && s[i] <= '~') inEscape = false;
        } else {
            unsigned char c = (unsigned char)s[i];
            if (c <= 127) len++;
            else if ((c & 0xE0) == 0xC0) { i += 1; len++; }
            else if ((c & 0xF0) == 0xE0) { i += 2; len++; } // NF Icons in PUA are usually width 1 in Mono fonts
            else if ((c & 0xF8) == 0xF0) { i += 3; len += 2; }
        }
    }
    return len;
}

void printDoubleLine(string color = CYAN) {
    cout << "  " << color;
    for (int i = 0; i < BOX_WIDTH - 4; i++) cout << "═";
    cout << RESET << endl;
}

void printSingleLine(string color = CYAN) {
    cout << "  " << color;
    for (int i = 0; i < BOX_WIDTH - 4; i++) cout << "─";
    cout << RESET << endl;
}

void bigHeader() {
    string art[] = {
        "██╗  ██╗ █████╗ ██████╗ ████████╗███████╗██╗      ███████╗██╗  ██╗ ██████╗ ██████╗ ",
        "██║ ██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔════╝██║      ██╔════╝██║  ██║██╔═══██╗██╔══██╗",
        "█████╔╝ ███████║██████╔╝   ██║   █████╗  ██║█████╗███████╗███████║██║   ██║██████╔╝",
        "██╔═██╗ ██╔══██║██╔══██╗   ██║   ██╔══╝  ██║╚════╝╚════██║██╔══██║██║   ██║██╔═══╝ ",
        "██║  ██╗██║  ██║██║  ██║   ██║   ███████╗███████╗ ███████║██║  ██║╚██████╔╝██║     ",
        "╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚══════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝     "
    };
    cout << "\n";
    for (const string& line : art) {
        int padding = (BOX_WIDTH - (int)line.length()) / 2;
        if (padding < 0) padding = 0;
        cout << string(padding, ' ') << BOLD << CYAN << line << RESET << "\n";
    }
    cout << "\n";
}

void printBoxTop(string color = CYAN) {
    cout << "  " << color << "╔"; 
    for (int i = 0; i < BOX_WIDTH - 6; i++) cout << "═";
    cout << "╗" << RESET << endl;
}

void printBoxBottom(string color = CYAN) {
    cout << "  " << color << "╚"; 
    for (int i = 0; i < BOX_WIDTH - 6; i++) cout << "═";
    cout << "╝" << RESET << endl;
}

void printBoxMiddle(string color = CYAN) {
    cout << "  " << color << "╠"; 
    for (int i = 0; i < BOX_WIDTH - 6; i++) cout << "═";
    cout << "╣" << RESET << endl;
}

void drawLine(string text, string color = CYAN, string textColor = RESET) {
    int visLen = getVisibleLength(text);
    int padding = MAX(0, BOX_WIDTH - 6 - visLen);
    cout << "  " << color << "║ " << RESET << textColor << text << RESET << string(padding - 1, ' ') << color << "║" << RESET << endl;
}

void drawCentered(string text, string color = CYAN, string textColor = YELLOW) {
    int visLen = getVisibleLength(text);
    int totalPadding = MAX(0, BOX_WIDTH - 6 - visLen);
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;
    cout << "  " << color << "║" << RESET << string(leftPadding, ' ') << textColor << BOLD << text << RESET << string(rightPadding, ' ') << color << "║" << RESET << endl;
}

void header(string title) {
    system("cls");
    bigHeader();
    printBoxTop(CYAN);
    drawCentered(title, CYAN, YELLOW);
    printBoxBottom(CYAN);
    cout << "\n";
}

void successBox(string message) {
    cout << "\n";
    printBoxTop(GREEN);
    drawCentered("\uF00C " + message, GREEN, GREEN);
    printBoxBottom(GREEN);
    cout << "\n";
}

void errorBox(string message) {
    cout << "\n";
    printBoxTop(RED);
    drawCentered("\uF00D " + message, RED, RED);
    printBoxBottom(RED);
    cout << "\n";
}

void infoBox(string message) {
    cout << "\n";
    printBoxTop(CYAN);
    drawCentered("\uF129 " + message, CYAN, CYAN);
    printBoxBottom(CYAN);
    cout << "\n";
}

void typing(string text, int delay = 30) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void loading(string label, int durationMs = 1500) {
    int width = 30;
    for (int i = 0; i <= width; i++) {
        float progress = (float)i / width;
        int pos = (int)(width * progress);
        
        cout << "\r  " << CYAN << "\uF110 " << RESET << label << " [";
        for (int j = 0; j < width; j++) {
            if (j < pos) cout << GREEN << "\uF0C8" << RESET;
            else cout << "\u2591";
        }
        cout << "] " << (int)(progress * 100) << "% " << flush;
        if (i < width) this_thread::sleep_for(chrono::milliseconds(durationMs / width));
    }
    cout << endl;
}

void footer() {
    cout << "\n";
    printSingleLine(CYAN);
    string text = "\uF158 KARTEL SHOP \uF158 Made with \uF004";
    int vis = getVisibleLength(text);
    int pad = (BOX_WIDTH - vis) / 2;
    cout << string(MAX(0, pad), ' ') << CYAN << "\uF158 " << RESET << BOLD << MAGENTA << "KARTEL SHOP" << RESET << CYAN << " \uF158 " << RESET << "Made with " << RED << "\uF004" << RESET << "\n";
    printSingleLine(CYAN);
}

void drawTable(vector<string> headers, vector<vector<string>> rows) {
    int colCount = headers.size();
    vector<int> colWidths(colCount);

    for (int i = 0; i < colCount; i++) {
        colWidths[i] = getVisibleLength(headers[i]) + 4;
    }

    for (const auto& row : rows) {
        for (int i = 0; i < colCount; i++) {
            if (i < row.size()) {
                int len = getVisibleLength(row[i]) + 4;
                if (len > colWidths[i]) colWidths[i] = len;
            }
        }
    }

    auto printLine = [&](string left, string mid, string right) {
        cout << "  " << CYAN << left;
        for (int i = 0; i < colCount; i++) {
            for (int j = 0; j < colWidths[i]; j++) cout << "─";
            if (i < colCount - 1) cout << mid;
        }
        cout << right << RESET << endl;
    };

    printLine("┌", "┬", "┐");
    cout << "  " << CYAN << "│" << RESET;
    for (int i = 0; i < colCount; i++) {
        int vis = getVisibleLength(headers[i]);
        int pad = (colWidths[i] - vis) / 2;
        cout << string(pad, ' ') << BOLD << MAGENTA << headers[i] << RESET << string(colWidths[i] - vis - pad, ' ') << CYAN << "│" << RESET;
    }
    cout << endl;
    printLine("├", "┼", "┤");

    if (rows.empty()) {
        int totalWidth = 0;
        for (int w : colWidths) totalWidth += w;
        totalWidth += colCount - 1;
        cout << "  " << CYAN << "│" << RESET << string((totalWidth - 11) / 2, ' ') << YELLOW << "[ Data Kosong ]" << RESET << string(totalWidth - 11 - (totalWidth - 11) / 2, ' ') << CYAN << "│" << RESET << endl;
    } else {
        for (const auto& row : rows) {
            cout << "  " << CYAN << "│" << RESET;
            for (int i = 0; i < colCount; i++) {
                string val = (i < row.size()) ? row[i] : "";
                int vis = getVisibleLength(val);
                cout << " " << val << string(colWidths[i] - vis - 1, ' ') << CYAN << "│" << RESET;
            }
            cout << endl;
        }
    }
    printLine("└", "┴", "┘");
}

void pressEnter() {
    cout << "\n  " << CYAN << ">> " << RESET << "Tekan " << BOLD << YELLOW << "ENTER" << RESET << " untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void clearScreen() {
    system("cls");
}

// Keeping these for compatibility with games.h though modified
void slotAnimation(int loops = 15) {
    string items[] = {"100 DM", "500 DM", "60 UC", "300 UC", "SALDO", "BONUS!"};
    for (int i = 0; i < loops; i++) {
        cout << "\r  " << MAGENTA << "\uF6D2 MENARIK SLOT: " << YELLOW << "[" << items[i % 6] << "]" << RESET << flush;
        this_thread::sleep_for(chrono::milliseconds(60 + (i * 15)));
    }
    cout << endl;
}

void reelAnimation(string s1, string s2, string s3) {
    string syms[] = {"7", "$", "@", "\uF005", "#", "\uF005"};
    int loops = 12;
    int pad = (BOX_WIDTH - 15) / 2;
    string space(pad, ' ');
    
    for (int i = 0; i < loops * 3; i++) {
        cout << "\033[H"; // Cursor to top
        bigHeader();
        drawCentered("\uF6D2 MEMPUTAR SLOT... \uF6D2", CYAN, YELLOW);
        cout << "\n";
        cout << space << CYAN << "╔═══╦═══╦═══╗" << RESET << endl;
        cout << space << CYAN << "║ " << RESET << MAGENTA << (i < loops ? syms[i%6] : s1) << RESET << CYAN << " ║ " << RESET << MAGENTA << (i < loops*2 ? syms[(i+1)%6] : s2) << RESET << CYAN << " ║ " << RESET << MAGENTA << (i < loops*3 ? syms[(i+2)%6] : s3) << RESET << CYAN << " ║" << RESET << endl;
        cout << space << CYAN << "╚═══╩═══╩═══╝" << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void matrixAnimation(int rows = 10) {
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#$%^&*";
    for (int i = 0; i < rows; i++) {
        cout << "  " << GREEN;
        for (int j = 0; j < 40; j++) cout << chars[rand() % chars.length()];
        cout << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(80));
    }
}

#endif
