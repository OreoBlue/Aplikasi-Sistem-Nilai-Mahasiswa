#include <stdio.h>  // Library untuk fungsi input-output
#include <stdlib.h> // Library untuk fungsi exit
#include <unistd.h> // Library untuk fungsi sleep
#include <string.h> // Library untuk fungsi strcpy

#define MAX_MATAKULIAH 6

// Struktur data Mahasiswa
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

// Fungsi yang digunakan dalam Kelola Data Mahasiswa
void kelolaData(const char *filename);
void editData(const char *filename);
void hapusData(const char *filename);



// Fungsi dimulai dari sini
void homepage() {
    char *filename = "DataMahasiswa.dat";
    int pilihan = 0;

    // Menu utama menggunakan label
    homepageMenu:
    printf("             ____\n");
    printf("            /   /\\\n");
    printf("           /   /  \\\n");
    printf("          /___/____\\\n");
    printf("          \\   \\    /\n");
    printf("           \\   \\  /\n");
    printf("            \\___\\/\n");
    printf("\n=== Selamat Datang di EduScore Admin! ===\n");
    printf("1. Kelola Data Mahasiswa\n");
    printf("2. Pencarian Data Mahasiswa\n");
    printf("3. Statistika Nilai\n");
    printf("4. Keluar\n");
    printf("Masukkan pilihan (1-4): ");
    
    if (scanf("%d", &pilihan) != 1){
        printf("Input tidak valid! Harap masukkan angka 1-4.\n");
        while (getchar() != '\n');
        pilihan = 0;
        goto homepageMenu; // Kembali ke menu utama dengan label
    }

    if (pilihan == 1){
        system("cls"); // Hapus layar
        kelolaData(filename); // Panggil fungsi kelola data
    }
    else if (pilihan == 2){
        system("cls");

        goto homepageMenu;
    }
    else if (pilihan == 3){
        printf("Membuka Statistika Data Mahasiswa...\n\n");
        // Panggil fungsi statistika data mahasiswa
        goto homepageMenu;
    }
    else if (pilihan == 4){
        printf("\nTerima kasih telah menggunakan aplikasi ini!\n");
        sleep(3); // Delay 3 detik
    }
    else {
        printf("Pilihan tidak valid! Harap masukkan angka 1-4.\n");
        sleep(3); // Delay 3 detik
        goto homepageMenu;
    }
}

void kelolaData(const char *filename) {
    int pilihan = 0;

    kelolaDataMenu:
    printf("\n=== Kelola Nilai Mahasiswa ===\n");
    printf("1. Tambah Data\n");
    printf("2. Lihat Data\n");
    printf("3. Edit Data\n");
    printf("4. Hapus Data\n");
    printf("5. Kembali ke Homepage\n");
    printf("Masukkan pilihan (1-5): ");

    if (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid! Harap masukkan angka 1-5.\n");
        while (getchar() != '\n');
        pilihan = 0;
        goto kelolaDataMenu;
    }

    if (pilihan == 1) {
        FILE *file = fopen(filename, "a");
        if (file == NULL) {
            printf("Gagal membuka file!\n");
            goto kelolaDataMenu;
        }
        system("cls");
        printf("Masukkan NIM: ");
        scanf("%d", &mhs.nim);
        if(mhs.nim < 1000000 || mhs.nim > 9999999) {
            system("cls");
            printf("Masukkan NIM dengan 7 digit angka!\n");
            fclose(file);
            goto kelolaDataMenu;
        }
        printf("Masukkan Nama: ");
        scanf(" %[^\n]s", mhs.nama); // Membaca string dengan spasi

        system("cls");
        printf("Pilih Mata Kuliah:\n");
        printf("1. Matematika Teknik\n");
        printf("2. Elektronika\n");
        printf("3. Algoritma dan Pemrograman\n");
        printf("4. Rangkaian Listrik\n");
        printf("5. Pendidikan Pancasila\n");
        printf("6. Pendidikan Agama\n");
        int matkulPilihan;
        printf("Masukkan pilihan (1-6): ");
        scanf("%d", &matkulPilihan);

        if (matkulPilihan < 1 || matkulPilihan > MAX_MATAKULIAH) {
            printf("Pilihan tidak valid! Harap masukkan angka 1-6.\n");
            fclose(file);
            goto kelolaDataMenu;
        }

        const char *matkulList[MAX_MATAKULIAH] = {
            "Matematika Teknik",
            "Elektronika",
            "Algoritma dan Pemrograman",
            "Rangkaian Listrik",
            "Pendidikan Pancasila",
            "Pendidikan Agama"
        };

        strcpy(mhs.matkul, matkulList[matkulPilihan - 1]);

        printf("Masukkan Nilai Tugas: ");
        scanf("%f", &mhs.tugas);
        printf("Masukkan Nilai UTS: ");
        scanf("%f", &mhs.uts);
        printf("Masukkan Nilai UAS: ");
        scanf("%f", &mhs.uas);

        mhs.nilaiAkhir = (mhs.tugas + mhs.uts + mhs.uas) / 3;
        if (mhs.nilaiAkhir >= 85) mhs.grade = 'A';
        else if (mhs.nilaiAkhir >= 70) mhs.grade = 'B';
        else if (mhs.nilaiAkhir >= 55) mhs.grade = 'C';
        else if (mhs.nilaiAkhir >= 40) mhs.grade = 'D';
        else mhs.grade = 'E';

        fprintf(file, "%d,%s,%s,%.2f,%.2f,%.2f,%.2f,%c\n", mhs.nim, mhs.nama, mhs.matkul, mhs.tugas, mhs.uts, mhs.uas, mhs.nilaiAkhir, mhs.grade);
        fclose(file);
        system("cls");
    } else if (pilihan == 2) { 
        system("cls");
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Gagal membuka file!\n");
            goto kelolaDataMenu;
        }
        printf("\n=== Data Nilai Mahasiswa ===\n");
        printf("| %-10s | %-20s | %-20s | %-5s | %-5s | %-5s | %-5s | %-5s |\n", "NIM", "Nama", "Mata Kuliah", "Tugas", "UTS", "UAS", "Akhir", "Grade");
        printf("---------------------------------------------------------------------------------------------\n");
        while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%f,%f,%c\n", &mhs.nim, mhs.nama, mhs.matkul, &mhs.tugas, &mhs.uts, &mhs.uas, &mhs.nilaiAkhir, &mhs.grade) != EOF) {
            printf("| %-10d | %-20s | %-20s | %-5.2f | %-5.2f | %-5.2f | %-5.2f | %-5c |\n", mhs.nim, mhs.nama, mhs.matkul, mhs.tugas, mhs.uts, mhs.uas, mhs.nilaiAkhir, mhs.grade);
        }
        fclose(file);
    } else if (pilihan == 3) {
        system("cls");
        editData(filename);
    } else if (pilihan == 4) {
        system("cls");
        hapusData(filename);
    } else if (pilihan == 5) {
        system("cls");
        printf("Kembali ke Homepage...\n");
        homepage(); // Call homepage function
        return;
    } else {
        system("cls");
        printf("Pilihan tidak valid! Harap masukkan angka 1-5.\n");
        goto kelolaDataMenu;
    }

    goto kelolaDataMenu;
}

void editData(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    Mahasiswa mhs[100]; // Array untuk menyimpan data
    int count = 0;

    // Membaca semua data dari file
    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%f,%f,%c\n",
                  &mhs[count].nim, mhs[count].nama, mhs[count].matkul,
                  &mhs[count].tugas, &mhs[count].uts, &mhs[count].uas,
                  &mhs[count].nilaiAkhir, &mhs[count].grade) != EOF) {
        count++;
    }

    int nim, found = 0;
    printf("\nMasukkan NIM mahasiswa yang ingin diedit: ");
    scanf("%d", &nim);

    // Menampilkan data berdasarkan NIM
    printf("\n=== Data Nilai Mahasiswa ===\n");
    printf("| %-10s | %-20s | %-20s | %-5s | %-5s | %-5s | %-5s | %-5s |\n", 
           "NIM", "Nama", "Mata Kuliah", "Tugas", "UTS", "UAS", "Akhir", "Grade");
    printf("---------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (mhs[i].nim == nim) {
            found = 1;
            printf("| %-10d | %-20s | %-20s | %-5.2f | %-5.2f | %-5.2f | %-5.2f | %-5c |\n",
                   mhs[i].nim, mhs[i].nama, mhs[i].matkul, mhs[i].tugas, mhs[i].uts, mhs[i].uas,
                   mhs[i].nilaiAkhir, mhs[i].grade);
        }
    }

    if (!found) {
        printf("Data mahasiswa dengan NIM %d tidak ditemukan!\n", nim);
        fclose(file);
        return;
    }

    // Memilih mata kuliah untuk diedit
    printf("\nPilih Mata Kuliah yang ingin diedit:\n");
    printf("1. Matematika Teknik\n");
    printf("2. Elektronika\n");
    printf("3. Algoritma dan Pemrograman\n");
    printf("4. Rangkaian Listrik\n");
    printf("5. Pendidikan Pancasila\n");
    printf("6. Pendidikan Agama\n");
    int matkulPilihan;
    printf("Masukkan pilihan (1-6): ");
    scanf("%d", &matkulPilihan);

    if (matkulPilihan < 1 || matkulPilihan > MAX_MATAKULIAH) {
        printf("Pilihan tidak valid! Harap masukkan angka 1-6.\n");
        fclose(file);
        return;
    }

    const char *matkulList[MAX_MATAKULIAH] = {
        "Matematika Teknik",
        "Elektronika",
        "Algoritma dan Pemrograman",
        "Rangkaian Listrik",
        "Pendidikan Pancasila",
        "Pendidikan Agama"
    };

    const char *matkulDipilih = matkulList[matkulPilihan - 1];

    found = 0;
    for (int i = 0; i < count; i++) {
        if (mhs[i].nim == nim && strcmp(mhs[i].matkul, matkulDipilih) == 0) {
            found = 1;

            // Memasukkan nilai baru
            printf("Masukkan Nilai Tugas baru: ");
            scanf("%f", &mhs[i].tugas);
            printf("Masukkan Nilai UTS baru: ");
            scanf("%f", &mhs[i].uts);
            printf("Masukkan Nilai UAS baru: ");
            scanf("%f", &mhs[i].uas);

            mhs[i].nilaiAkhir = (mhs[i].tugas + mhs[i].uts + mhs[i].uas) / 3;
            if (mhs[i].nilaiAkhir >= 85) mhs[i].grade = 'A';
            else if (mhs[i].nilaiAkhir >= 70) mhs[i].grade = 'B';
            else if (mhs[i].nilaiAkhir >= 55) mhs[i].grade = 'C';
            else if (mhs[i].nilaiAkhir >= 40) mhs[i].grade = 'D';
            else mhs[i].grade = 'E';

            break;
        }
    }

    if (!found) {
        printf("Mata kuliah %s tidak ditemukan untuk NIM %d!\n", matkulDipilih, nim);
        fclose(file);
        return;
    }

    // Menulis ulang semua data ke file
    freopen(filename, "w", file);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%.2f,%.2f,%.2f,%.2f,%c\n",
                mhs[i].nim, mhs[i].nama, mhs[i].matkul,
                mhs[i].tugas, mhs[i].uts, mhs[i].uas,
                mhs[i].nilaiAkhir, mhs[i].grade);
    }

    fclose(file);
    printf("Data berhasil diperbarui!\n");
}

void hapusData(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    // Tampilkan data mahasiswa
    printf("\n=== Data Nilai Mahasiswa ===\n");
    printf("| %-10s | %-20s | %-20s | %-5s | %-5s | %-5s | %-5s | %-5s |\n", "NIM", "Nama", "Mata Kuliah", "Tugas", "UTS", "UAS", "Akhir", "Grade");
    printf("---------------------------------------------------------------------------------------------\n");
    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%f,%f,%c\n", &mhs.nim, mhs.nama, mhs.matkul, &mhs.tugas, &mhs.uts, &mhs.uas, &mhs.nilaiAkhir, &mhs.grade) != EOF) {
        printf("| %-10d | %-20s | %-20s | %-5.2f | %-5.2f | %-5.2f | %-5.2f | %-5c |\n", mhs.nim, mhs.nama, mhs.matkul, mhs.tugas, mhs.uts, mhs.uas, mhs.nilaiAkhir, mhs.grade);
    }

    rewind(file); // Reset file pointer ke awal untuk pencarian data

    int nim;
    char mataKuliah[50];
    int found = 0;

    // Minta input untuk NIM dan mata kuliah yang ingin dihapus
    printf("\nMasukkan NIM mahasiswa yang ingin dihapus: ");
    scanf("%d", &nim);

    printf("Pilih Mata Kuliah yang diambil:\n");
    printf("1. Matematika Teknik\n");
    printf("2. Elektronika\n");
    printf("3. Algoritma dan Pemrograman\n");
    printf("4. Rangkaian Listrik\n");
    printf("5. Pendidikan Pancasila\n");
    printf("6. Pendidikan Agama\n");
    int matkulPilihan;
    printf("Masukkan pilihan (1-6): ");
    scanf("%d", &matkulPilihan);

    switch (matkulPilihan) {
        case 1:
            strcpy(mataKuliah, "Matematika Teknik");
            break;
        case 2:
            strcpy(mataKuliah, "Elektronika");
            break;
        case 3:
            strcpy(mataKuliah, "Algoritma dan Pemrograman");
            break;
        case 4:
            strcpy(mataKuliah, "Rangkaian Listrik");
            break;
        case 5:
            strcpy(mataKuliah, "Pendidikan Pancasila");
            break;
        case 6:
            strcpy(mataKuliah, "Pendidikan Agama");
            break;
        default:
            printf("Mata kuliah tidak ditemukan! Pilih mata kuliah yang valid.\n");
            fclose(file);
            return;
    }

    // Konfirmasi untuk menghapus data
    int konfirmasi;
    printf("\nApakah Anda yakin ingin menghapus data tersebut?\n");
    printf("1. Ya\n2. Tidak\n");
    printf("Masukkan Input: ");
    scanf("%d", &konfirmasi);

    if (konfirmasi != 1) {
        printf("Penghapusan data dibatalkan.\n");
        fclose(file);
        return;
    }

    // Membuka file sementara untuk menyimpan data yang tidak dihapus
    FILE *tempFile = fopen("TempDataMahasiswa.dat", "w");
    if (tempFile == NULL) {
        printf("Gagal membuka file sementara!\n");
        fclose(file);
        return;
    }

    // Salin semua data yang tidak sesuai dengan NIM dan mata kuliah yang ingin dihapus
    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%f,%f,%c\n", &mhs.nim, mhs.nama, mhs.matkul, &mhs.tugas, &mhs.uts, &mhs.uas, &mhs.nilaiAkhir, &mhs.grade) != EOF) {
        if (mhs.nim == nim && strcmp(mhs.matkul, mataKuliah) == 0) {
            found = 1; // Menandakan bahwa data ditemukan
        } else {
            // Salin data yang tidak dihapus ke file sementara
            fprintf(tempFile, "%d,%s,%s,%.2f,%.2f,%.2f,%.2f,%c\n", mhs.nim, mhs.nama, mhs.matkul, mhs.tugas, mhs.uts, mhs.uas, mhs.nilaiAkhir, mhs.grade);
        }
    }

    if (found) {
        printf("\nMenghapus Data...\n");
        sleep(2); // Delay 2 detik
        printf("Hapus Data Berhasil\n");
    } else {
        printf("Data tidak ditemukan untuk NIM %d dan Mata Kuliah %s.\n", nim, mataKuliah);
    }

    // Tutup file
    fclose(file);
    fclose(tempFile);

    // Hapus file asli dan ganti dengan file sementara
    remove(filename);
    rename("TempDataMahasiswa.dat", filename);
}

int main() {
    system("cls");
    const char *filename = "DataMahasiswa.Dat";
    homepage();
    return 0;
}
