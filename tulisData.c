#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int nim;
    char nama[50];
    char matkul[50];
    float nilai;
} Mahasiswa;

int main() {
    FILE *file; // Pointer untuk file
    Mahasiswa m; // Variabel struct untuk membaca data

    // Membuka file untuk membaca
    file = fopen("data_mahasiswa.dat", "rb");
    if (file == NULL) {
        printf("File tidak ditemukan atau belum ada data!\n");
        return 1;
    }

    printf("Data Mahasiswa:\n");
    printf("NIM\tNama\t\tMata Kuliah\tNilai\n");
    printf("-------------------------------------------\n");

    // Membaca data dari file hingga selesai
    while (fread(&m, sizeof(Mahasiswa), 1, file)) {
        printf("%d\t%s\t%s\t%.2f\n", m.nim, m.nama, m.matkul, m.nilai);
    }

    fclose(file); // Menutup file
    return 0;
}
