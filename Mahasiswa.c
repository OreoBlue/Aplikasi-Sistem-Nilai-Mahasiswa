#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nim[15];
    char password[20];
    char matkul[50];
    float tugas;
    float uts;
    float uas;
    float nilaiAkhir;
    char grade;
} Mahasiswa;

// Fungsi menghitung nilai akhir dan grade
void hitungNilai(Mahasiswa *m) {
    m->nilaiAkhir = (0.2 * m->tugas) + (0.3 * m->uts) + (0.5 * m->uas);
    if (m->nilaiAkhir >= 85) m->grade = 'A';
    else if (m->nilaiAkhir >= 70) m->grade = 'B';
    else if (m->nilaiAkhir >= 55) m->grade = 'C';
    else if (m->nilaiAkhir >= 40) m->grade = 'D';
    else m->grade = 'E';
}

// Fungsi registrasi password untuk mahasiswa baru
void registrasi(const char *filename, Mahasiswa *m) {
    printf("Registrasi Password untuk NIM %s\n", m->nim);
    printf("Masukkan Password Baru: ");
    scanf("%s", m->password);

    // Simpan data ke file
    FILE *file = fopen(filename, "ab"); // Append binary mode
    if (!file) {
        printf("Gagal membuka file!\n");
        return;
    }
    fwrite(m, sizeof(Mahasiswa), 1, file);
    fclose(file);

    printf("Registrasi berhasil! Silakan login kembali.\n");
}

// Fungsi login mahasiswa
void loginMahasiswa(const char *filename) {
    char inputNIM[15], inputPassword[20];
    Mahasiswa m;
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("File tidak ditemukan! Pastikan dosen/admin telah menginput data.\n");
        return;
    }

    printf("Masukkan NIM: ");
    scanf("%s", inputNIM);

    int found = 0, isRegistered = 0;
    while (fread(&m, sizeof(Mahasiswa), 1, file)) {
        if (strcmp(m.nim, inputNIM) == 0) {
            found = 1;
            if (strlen(m.password) > 0) isRegistered = 1; // Cek apakah sudah ada password
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("NIM tidak ditemukan! Pastikan dosen/admin telah menambahkan data.\n");
        return;
    }

    if (!isRegistered) {
        printf("NIM %s belum memiliki password.\n", inputNIM);
        registrasi(filename, &m);
        return;
    }

    // Login dengan password
    printf("Masukkan Password: ");
    scanf("%s", inputPassword);
    if (strcmp(m.password, inputPassword) == 0) {
        printf("\nLogin berhasil! Selamat datang, Mahasiswa dengan NIM %s.\n", m.nim);
        printf("\n=== Daftar Nilai ===\n");
        printf("-------------------------------------------------\n");
        printf("| Mata Kuliah      | Tugas  | UTS   | UAS   | Akhir | Grade |\n");
        printf("-------------------------------------------------\n");
        printf("| %-16s | %-6.2f | %-5.2f | %-5.2f | %-5.2f | %-5c |\n",
               m.matkul, m.tugas, m.uts, m.uas, m.nilaiAkhir, m.grade);
        printf("-------------------------------------------------\n");
    } else {
        printf("Password salah!\n");
    }
}

int main() {
    const char *filename = "DataMahasiswa.dat"; // File database
    int pilihan;

    do {
        printf("\n=== Sistem Mahasiswa ===\n");
        printf("1. Login Mahasiswa\n");
        printf("2. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                loginMahasiswa(filename);
                break;
            case 2:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 2);

    return 0;
}
