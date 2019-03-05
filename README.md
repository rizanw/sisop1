# Latihan Seslab sisop

### A. Latihan modul 1
  1. Buatlah sebuah program menggunakan bash script untuk menentukan apakah sebuah string yang Anda diinputkan merupakan palindrom atau bukan. Contoh: malam = palindrom, makan != palindrom.
  2. Buatlah sebuah task scheduling menggunakan `crontab` dan sebuah bash script untuk memindahkan semua file mp3 ke `/home/<user>/Music`, semua file mp4 ke `/home/<user>/Videos`, dan semua file jpg ke `/home/<user>/Pictures` setiap satu menit. Awalnya, semua file mp3, mp4, dan jpg tersebut terletak di `/home/<user>/Documents`.
  3. Buatlah sebuah program `awk` yang bisa menampilkan user yang melakukan proses. Tapi karena kemungkinan besar jumlah barisnya akan sangat banyak, maka tampilkan secara distinct (tidak ada user yang sama muncul lebih dari satu kali). Jika sudah bisa, coba masukkan hasilnya ke dalam file user.log (Hint: menggunakan `pipe` dan `command ps`)

### B. Latihan modul 2
  1. Modifikasi code soal1 agar output nya menjadi huruf abjad urut dari A sampai Z, tanpa menghapus fungsi yang sudah ada.
  2. Buatlah program yang bisa membuat folder "anak" yang berisi salinan file warisan.txt. 
     Hint: gunakan `fork`, `exec`, dan `wait`.
  3. Buatlah sebuah daemon yang dapat melakukan backup isi dari file sampah.txt yang disimpan dalam file log.log lalu menghapus file sampah.txt tersebut. Tidak diperbolehkan menggunakan `exec` dan `system`.
