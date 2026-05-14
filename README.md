# KARTEL SHOP - TUGAS 1 PETRUK

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Repo Size](https://img.shields.io/github/repo-size/keep-xylent/Project-Kartel-Shop?style=for-the-badge)

Game top-up & entertainment console application berbasis C++

## Fitur

- **Top-up Game** - Mobile Legends (Diamonds) & PUBG Mobile (UC)
- **Mini-Games** - Lucky Spin, Mystery Box, Lucky Slot
- **Sistem Member** - Register, login, saldo
- **Admin Panel** - Kelola harga, voucher, member

## Struktur Project

```
PROJECT_KARTEL/
├── src/              # Source code utama
├── include/          # Header files
├── data/             # Data persistence (.dat files)
├── build/            # Output build
├── kartel_shop.exe   # Executable
├── run.bat           # Script build & run (Windows)
└── run.ps1           # Script build & run (PowerShell)
```

## Instalasi

### 1. Install Compiler (g++)

**Menggunakan MSYS2/MinGW (Recommended):**

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

**Atau menggunakan MinGW-w64:**

1. Download dari <https://www.mingw-w64.org/download/>
2. Install dan tambahkan `bin` ke PATH environment variable

### 2. Verifikasi Instalasi

```bash
g++ --version
```

### 3. Clone/Download Project

```bash
git clone https://github.com/keep-xylent/Project-Kartel-Shop.git
cd Project-Kartel-Shop
```

## Build & Run

### Menggunakan Batch Script

```bash
run.bat
```

### Menggunakan PowerShell

```powershell
.\run.ps1
```

### Manual

```bash
g++ src/main.cpp -o build/main.exe -Iinclude
.\build\main.exe
```

## Default Admin

| Username | Password |
|----------|----------|
| `admin`  | `admin123` |

## Requirements

- Windows OS
- g++ (GCC C++ Compiler) untuk kompilasi
- Console dengan support ANSI color
