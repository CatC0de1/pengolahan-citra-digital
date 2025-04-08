# Cara Menjalankan Program

Dalam resipoteri ini, terdapat 3 jenis format file yang digunakan. python, jupyter notebook, dan c++. Jika ingin mudah dan cepat, gunakan **python** atau **jupyter notebook**.


## 1. Python
Ikuti tutorial start python di vscode.

Setelah berhasil menjalankan python di vscode, instal library yang diperlukan dalam pengolahan citra digital

```bash
pip install libraries_name
```

### nama paket yang diinstall(tergantung kebutuhan) :
- pillow
- numpy
- matplotlib
- opencv-python

Contoh :

```bash
pip install opencv-python numpy matplotlib
```


## 2. Jupyter Notebook
Setelah sukses mendownload python, lakukan step berikut

1. Download extension `Jupyter`, `Jupyter Notebook`
2. Jalankan dengan intrepeter Python atau yang lain jika ada

Cara memakai jupyter notebook di vscode mirip dengan localhost jupyter di anaconda


## 3. C++

Langkah-langkah untuk mempraktikan pengolahan citral digital dengan c++ cukup panjang dan agak rumit. Jika terjadi kesalahan instalasi dalam mengikuti langkah-langkah berikut, hubungi [aku](https://api.whatsapp.com/send/?phone=6285859817176&text&type=phone_number&app_absent=0) (walau aku tidak menjamin 100%😅).

1. ikuti tutorial di [start c++ di vscode](https://code.visualstudio.com/docs/cpp/config-mingw#_installing-the-mingww64-toolchain)
2. setelah sukses menjalankan c++ di vscode melalui MinGW via MSYS2, maka bisa dilanjutkan ke langkah berikutnya
3. install library OpenCV melalui `MSYS2 MinGW64` dengan :
```bash
pacman -S mingw-w64-x86_64-opencv
```
4. jika ada error akibat versi lama, buka `MSYS2 ucrt64` lalu update versinya (jika versi nya lama) dengan:
```bash
pacman -syu
```
5. di `MSYS2 mingw64` lalu install `pkg-config` dengan :
```bash
pacman -S mingw-w64-x86_64-pkg-config
```
6. lalu cek apakah `pkg-config` sudah terinstall dengan 
```bash
pkg-config --version
```
7. tambahkan path (contoh) `C:\msys64\mingw64\bin` dan `C:\msys64\mingw64\lib\pkgconfig` di edit environment
8. cek instalasi konfigurasi opencv di `MSYS2 mingw64` dengan 
```bash
pkg-config --cflags --libs opencv4
```
9. jika opencv tidak terbaca, ulangi step yang terlewati atau hubungi [aku](https://api.whatsapp.com/send/?phone=6285859817176&text&type=phone_number&app_absent=0)
10. di `MSYS2 minGW64`, cek apakah Qt6 sudah terinstall dengan 
```bash
pacman -Q | grep qt6
```
11. jika Qt6 tidak terinstall, install dengan 
```bash
pacman -S mingw-w64-x86_64-qt6
```
atau kalau mau paket hemat :
```bash
pacman -S mingw-w64-x86_64-qt6-base
```
lalu cek dengan :
```bash
pkg-config --modversion Qt6Core
```
jika masih error, cek apakah `Qt6Core.dll` ada di `C:\msys64\mingw64\bin`. 


#### Jika sampai sini masih lancar, selamat!!
Jika terdapat kendala diluar prediksi, hubungi [aku](https://api.whatsapp.com/send/?phone=6285859817176&text&type=phone_number&app_absent=0). Langkah selanjutnya adalah menjalankan program C++ dengan opencv4

1. Cek contoh program C++ di `/cpp-ex/test1.cpp`
2. Jalankan program dengan memmbuka `MSYSS2 MinGW` dan jalankan perintah berikut(sesuaikan dengan directory masing-masing):
```bash
cd /c/users/arman/vsc/pcd
```
```bash
g++ test1.cpp -o test1.exe $(pkg-config --cflags --libs opencv4)
```
```bash
./test.exe
```

Jika berhasil, **Selamat, kamu keren wkwk**. kalau engga, ya sekali lagi, hubungi [aku](https://api.whatsapp.com/send/?phone=6285859817176&text&type=phone_number&app_absent=0) wkwk

*Perubahan README akan kulakukan jika ada update lebih baik atau kesalahan instruksi