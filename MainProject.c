#include <stdio.h>  // Library untuk fungsi input-output
#include <stdlib.h> // Library untuk fungsi exit
#include <unistd.h> // Library untuk fungsi sleep
#include <string.h> // Library untuk fungsi strcpy

int main(){
    system("cls");
    int pilihan;

    homePage:
    system("cls");
    printf("\n=== Selamat Datang di EduScore! ===\n");
    printf("\nPilih versi \n");
    printf("1. Admin/Dosen\n");
    printf("2. Mahasiswa\n");
    printf("3. Keluar\n");
    printf("Masukkan pilihan (1-3): ");
    scanf("%d", &pilihan);

    switch (pilihan){
    case 1:
        printf("Membuka Admin...\n");
        system("gcc Admin.c -o Admin");
        system("Admin.exe");
        break;
    case 2:
        printf("Membuka Mahasiswa...\n");
        system("gcc Mahasiswa.c -o Mahasiswa");
        system("Mahasiswa.exe");
        break;
    case 3:
        printf("Terima kasih telah menggunakan aplikasi ini!\n");
        sleep(3); // Delay 3 detik
    default:
        printf("Pilihan tidak valid! Harap masukkan angka 1-3.\n");
        goto homePage;
    }

    return 0;
}