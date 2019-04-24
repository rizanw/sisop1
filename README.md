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
    
### C. Latihan modul 3  
  1. Buatlah sebuah program multithreading yang dapat menyalin isi file baca.txt ke dalam file salin1.txt. Kemudian menyalin isi dari file salin1.txt ke dalam file salin2.txt!  
  2. Buatlah sebuah program multithreading yang dapat menampilkan bilangan prima dari 1-N. program akan dieksekusi menggunakan thread sebanyak T dimana setiap thread akan melakukan pencarian bilangan prima dengan range N/T (range tiap thread berbeda), kemudian tiap thread akan menampilkan hasilnya.  
     misalkan N = 100 dan T=2; jadi thread 1 akan mencari bilangan prima dari 1-50 dan thread 2 akan mencari dari 51-100  
  3. Buatlah sebuah program untuk menampilkan file diurutan ketiga dari sebuah direktori. Dengan ketentuan :  
     - menggunakan pipe.
	 - menggunakan command ls, head, tail.  
	 
### D. Latihan modul 4
1. Buat sebuah file sistem yang kamu buat ke /home/[user]/Downloads, lalu ubah nama file yang ada pada folder tersebut menjadi ```[nama file].[ekstensi].bak```. File .bak tersebut hanya dapat dibaca.
2. Buat sebuah file system yang mengarah ke /home/[user]/Documents. Pada saat membuka file dengan ekstensi .pdf, .doc, .txt pada direktori Documents akan muncul pesan error “Terjadi kesalahan! File berisi konten berbahaya.” dan tidak dapat membaca file tersebut. Setelah memunculkan pesan error, file tersebut diganti namanya menjadi ```<namafile>.<ekstensi>.ditandai```. Setelah memunculkan pesan error dan mengganti nama file tadi, file tersebut otomatis dipindahkan ke direktori ```rahasia```. Jika folder rahasia belum ada, maka secara otomatis akan membuat direktori “rahasia” sebelum dipindahkan dan file tidak bisa di read write execute.
