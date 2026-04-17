@echo off
chcp 65001 >nul
title KARTEL SHOP

:: Pastikan folder build ada
if not exist "build" mkdir "build"

:: Hentikan proses main.exe jika sedang berjalan (hindari Permission Denied)
taskkill /F /IM main.exe /T >nul 2>&1

echo [⏳] Sedang mengompilasi KARTEL SHOP...
g++ src/main.cpp -o build/main.exe -Iinclude

if %ERRORLEVEL% EQU 0 (
    echo [✅] Kompilasi berhasil! Membuka aplikasi...
    cls
    build\main.exe
) else (
    echo.
    echo [❌] Kompilasi Gagal!
    echo Periksa kesalahan pada kode C++ Anda.
    echo.
    pause
)
