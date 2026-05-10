
# Pengolahan Citra Digital (C++ + OpenCV)

Project ini menggunakan C++17 dan OpenCV yang dijalankan di Windows menggunakan MSYS2 (UCRT64) dan GNU Make.

---

# 📌 Requirements (Windows Setup)

## 1. Install MSYS2
Download dan install MSYS2:
https://www.msys2.org/

Setelah install, buka **MSYS2 UCRT64 terminal** lalu update:

```bash
pacman -Syu
````

Tutup terminal jika diminta, lalu buka lagi UCRT64.

---

## 2. Install compiler & tools

Jalankan di MSYS2 UCRT64:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-make
pacman -S mingw-w64-ucrt-x86_64-pkgconf
```

---

## 3. Install OpenCV

```bash
pacman -S mingw-w64-ucrt-x86_64-opencv
```

---

# ⚙️ Setup PATH (IMPORTANT)

Tambahkan ke Environment Variables Windows:

```
C:\msys64\ucrt64\bin
```

Lalu restart terminal / PowerShell.

---

# 🚀 Cara Build & Run

## Option 1 (Recommended - MSYS2 UCRT64 terminal)

Buka **MSYS2 UCRT64**, lalu:

```bash
cd /PATH/pengolahan-citra-digital-cpp
make
```

Run program:

```bash
./main.exe
```

---

## Option 2 (PowerShell Windows/VScode)

Jika ingin pakai PowerShell, pastikan:

* PATH sudah mengarah ke MSYS2 UCRT64
* Makefile menggunakan path Windows (C:/msys64/...)

Build:

```powershell
make -f Makefile.win
```

Run:

```powershell
.\main.exe
```
feel free to ask ^_____^