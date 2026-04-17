$ErrorActionPreference = "SilentlyContinue"
$baseDir = $PSScriptRoot
$buildDir = "$baseDir\build"

# Pastikan folder build ada
if (!(Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir > $null
}

# Hentikan proses main.exe jika sedang berjalan (hindari Permission Denied)
Stop-Process -Name "main" -Force -ErrorAction SilentlyContinue

Write-Host "`n[⏳] Sedang mengompilasi KARTEL SHOP..." -ForegroundColor Cyan
g++ src/main.cpp -o build/main.exe -Iinclude

if ($LASTEXITCODE -eq 0) {
    Write-Host "[✅] Kompilasi berhasil! Membuka aplikasi...`n" -ForegroundColor Green
    Start-Sleep -Milliseconds 500
    Clear-Host
    & "$buildDir\main.exe"
} else {
    Write-Host "`n[❌] Kompilasi Gagal!" -ForegroundColor Red
    Write-Host "Periksa kesalahan pada kode C++ Anda.`n"
    pause
}
