#include <stdio.h>  // Library untuk fungsi input-output
#include <stdlib.h> // Library untuk fungsi exit
#include <unistd.h> // Library untuk fungsi sleep
#include <string.h> // Library untuk fungsi strcpy

int main(){
    int pilihan;

    homePage:
    printf("\n=== Selamat Datang di EduScore! ===\n");
    printf("\nPilih versi \n");
    printf("1. Admin\n");
    printf("2. Dosen\n");
    printf("3. Mahasiswa\n");
    printf("Masukkan pilihan (1-3): ");
    scanf("%d", &pilihan);

    switch (pilihan){
    case 1:
        printf("Membuka Admin...\n");
        system("gcc Admin.c -o Admin");
        system("Admin.exe");
    case 2:
        printf("Membuka Dosen...\n");
        break;
    case 3:
        printf("Membuka Mahasiswa...\n");
        system("gcc Mahasiswa.c -o Mahasiswa");
        system("Mahasiswa.exe");
    default:
        printf("Pilihan tidak valid! Harap masukkan angka 1-3.\n");
        goto homePage;
    }

    return 0;
}