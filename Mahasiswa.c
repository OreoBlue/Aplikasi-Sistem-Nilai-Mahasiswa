#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_MATAKULIAH 6

typedef struct {
    int nim;
    char nama[50];
    char matkul[50];
    float tugas;
    float uts;
    float uas;
    float nilaiAkhir;
    char grade;
} Mahasiswa;


Mahasiswa mhs;

int currentNIM;

void loginMahasiswa(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        exit(1);
    }

    printf("         ____\n");
    printf("        /   /\\\n");
    printf("       /   /  \\\n");
    printf("      /___/____\\\n");
    printf("      \\   \\    /\n");
    printf("       \\   \\  /\n");
    printf("        \\___\\/\n");
    printf("\n=== Login Mahasiswa ===\n");
    printf("Masukkan NIM Anda: ");
    scanf("%d", &currentNIM);

    int found = 0;
    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%f,%f,%c\n", &mhs.nim, mhs.nama, mhs.matkul, &mhs.tugas, &mhs.uts, &mhs.uas, &mhs.nilaiAkhir, &mhs.grade) != EOF) {
        if (mhs.nim == currentNIM) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("NIM tidak ditemukan!\n");
        exit(1);
    } else {
        printf("\nSelamat datang, %s!\n", mhs.nama);
        sleep(2);
    }
}

void lihatNilaiMahasiswa(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    system("cls");
    printf("\n=== Lihat Nilai Anda ===\n");
    printf("Daftar Mata Kuliah yang Anda Ambil:\n");

    char matkulList[MAX_MATAKULIAH][50];
    int count = 0;

    // Cari mata kuliah yang diambil mahasiswa yang login
    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%f,%f,%c\n", &mhs.nim, mhs.nama, mhs.matkul, &mhs.tugas, &mhs.uts, &mhs.uas, &mhs.nilaiAkhir, &mhs.grade) != EOF) {
        if (mhs.nim == currentNIM) {
            strcpy(matkulList[count], mhs.matkul);
            printf("%d. %s\n", count + 1, mhs.matkul);
            count++;
        }
    }

    fclose(file);

    if (count == 0) {
        printf("Anda tidak memiliki mata kuliah yang terdaftar.\n");
        return;
    }

    printf("\nMasukkan nomor mata kuliah untuk melihat nilai: ");
    int pilihan;
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > count) {
        printf("Pilihan tidak valid!\n");
        return;
    }

    // Tampilkan nilai berdasarkan mata kuliah yang dipilih

    file = fopen(filename, "r");
    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%f,%f,%c\n", &mhs.nim, mhs.nama, mhs.matkul, &mhs.tugas, &mhs.uts, &mhs.uas, &mhs.nilaiAkhir, &mhs.grade) != EOF) {
        if (mhs.nim == currentNIM && strcmp(mhs.matkul, matkulList[pilihan - 1]) == 0) {
            printf("\n=== Nilai Mata Kuliah %s ===\n", mhs.matkul);
            printf("Nilai Tugas   : %.2f\n", mhs.tugas);
            printf("Nilai UTS     : %.2f\n", mhs.uts);
            printf("Nilai UAS     : %.2f\n", mhs.uas);
            printf("Nilai Akhir   : %.2f\n", mhs.nilaiAkhir);
            printf("Grade         : %c\n", mhs.grade);
            break;
        }
    }

    fclose(file);
}

void homepageMahasiswa(const char *filename) {
    int pilihan = 0;

    homepageMenu:
    system("cls");
    printf("\n=== Selamat Datang di EduScore Mahasiswa! ===\n");
    printf("1. Lihat Nilai\n");
    printf("2. Keluar\n");
    printf("Masukkan pilihan (1-2): ");

    if (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid! Harap masukkan angka 1-2.\n");
        while (getchar() != '\n');
        pilihan = 0;
        goto homepageMenu;
    }

    if (pilihan == 1) {
        lihatNilaiMahasiswa(filename);
        printf("\nTekan Enter untuk kembali ke menu utama...");
        getchar();
        getchar(); // Untuk menangkap input enter
        goto homepageMenu;
    } else if (pilihan == 2) {
        printf("\nTerima kasih telah menggunakan aplikasi ini!\n");
        sleep(2);
    } else {
        printf("Pilihan tidak valid! Harap masukkan angka 1-2.\n");
        sleep(2);
        goto homepageMenu;
    }
}

int main() {
    system("cls");
    const char *filename = "DataMahasiswa.dat";
    loginMahasiswa(filename);
    homepageMahasiswa(filename);
    return 0;
}
