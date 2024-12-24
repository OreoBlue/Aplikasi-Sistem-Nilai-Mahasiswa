    #include <stdio.h>
    #include <stdlib.h>

    int main() {
        int pilihan = 0;

        do {
            printf("\n=== Selamat Datang di Aplikasi Nilai Mahasiswa! ===\n");
            printf("1. Tambah Data Mahasiswa\n");
            printf("2. Lihat Data Mahasiswa\n");
            printf("3. Cari Data Mahasiswa\n");
            printf("4. Keluar\n");
            printf("Masukkan pilihan Anda (1-4): ");
            
            if (scanf("%d", &pilihan) != 1) { // Validasi input bukan angka
                printf("Input tidak valid! Harap masukkan angka 1-4.\n");
                while (getchar() != '\n'); // Membersihkan buffer input
                pilihan = 0;
                continue;
            }

            if (pilihan == 1){
                    printf("Menjalankan Tambah Data Mahasiswa...\n");
                    system("gcc tulisData.c -o tulisData");
                    system("tulisData.exe");
                    break;
            }
            else if (pilihan == 2)
            {
                    printf("Menjalankan Lihat Data Mahasiswa...\n");
                    system("gcc bacaData.c -o bacaData");
                    system("bacaData.exe");
                    break;
            }
            else if (pilihan == 3)
            {
                    printf("Menjalankan Cari Data Mahasiswa...\n");
                    system("gcc cariData.c -o cariData");
                    system("cariData.exe");
                    break;
            }
            else if (pilihan == 4){
                    printf("Terima kasih telah menggunakan aplikasi ini!\n");
                    break;
            }
            else {
                    printf("Pilihan tidak valid! Harap masukkan angka 1-4.\n");
                    break;
            }
        } while (pilihan != 4);


        return 0;
    }
