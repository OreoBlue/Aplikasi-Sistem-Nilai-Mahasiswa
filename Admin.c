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


typedef struct {
    char username[50];
    char password[50];
} Admin;

Mahasiswa mhs;
Admin admin;

int currentNIM;

// Fungsi yang digunakan dalam Kelola Data Mahasiswa
void kelolaData(const char *filename);
void editData(const char *filename);
void hapusData(const char *filename);

// Fungsi yang digunakan untuk Pencarian Data Mahasiswa
void pencarianData(const char *filename);

// Fungsi yang digunakan untuk Statistika Data Mahasiswa
void statistikaData(const char *filename);

// Fungsi yang digunakan untuk Login dan Homepage
void loginPage();
void homepage();
void registrasi();

// Fungsi dimulai dari sini
void loginPage() {
    int pilihan = 0;

    loginMenu:
    system("cls");
    printf("\n=== Login Page ===\n");
    printf("1. Login Admin\n");
    printf("2. Registrasi\n");
    printf("3. Keluar\n");
    printf("Masukkan pilihan (1-3): ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        char username[50];
        char password[50];
        FILE *file = fopen("LoginAdmin.dat", "r");
        if (!file) {
            printf("Gagal membuka file!\n");
            goto loginMenu;
        }

        system("cls");
        printf("Masukkan Username: ");
        scanf("%s", username);
        printf("Masukkan Password: ");
        scanf("%s", password);

        int found = 0;
        while (fscanf(file, "%49s %49s", admin.username, admin.password) != EOF) {
            if (strcmp(admin.username, username) == 0 && strcmp(admin.password, password) == 0) {
                found = 1;
                break;
            }
        }
        fclose(file);

        if (found) {
            system("cls");
            printf("Login berhasil!\n");
            sleep(2);
            homepage();
        } else {
            system("cls");
            printf("Username atau Password salah!\n");
            sleep(2);
            goto loginMenu;
        }
    } else if (pilihan == 2) {
        system("cls");
        registrasi();
        goto loginMenu;
    } else if (pilihan == 3) {
        printf("Keluar dari aplikasi...\n");
        sleep(2);
        exit(0);
    } else {
        printf("Pilihan tidak valid! Harap masukkan angka 1-3.\n");
        sleep(2);
        goto loginMenu;
    }
}

void registrasi() {
    FILE *file = fopen("LoginAdmin.dat", "a");
    if (!file) {
        printf("Gagal membuka file!\n");
        return;
    }

    system("cls");
    printf("Masukkan Username: ");
    scanf("%s", admin.username);
    printf("Masukkan Password: ");
    scanf("%s", admin.password);

    fprintf(file, "%s %s\n", admin.username, admin.password);
    fclose(file);
    printf("Registrasi berhasil!\n");
    sleep(2);
    system("cls");
}

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
        pencarianData(filename);
        goto homepageMenu;
    }
    else if (pilihan == 3){
        system("cls");
        statistikaData(filename);
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
    printf("\n=== Kelola Data Mahasiswa ===\n");
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
        printf("Data berhasil ditambahkan!\n");
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

    rewind(file); // Reset file pointer ke awal untuk pencarian data

    Mahasiswa mhs[100]; // Array untuk menyimpan data
    int count = 0;

    // Tampilkan data mahasiswa
    system("cls");
    printf("\n=== Data Nilai Mahasiswa ===\n");
    printf("| %-10s | %-20s | %-20s | %-5s | %-5s | %-5s | %-5s | %-5s |\n",
           "NIM", "Nama", "Matkul", "Tugas", "UTS", "UAS", "NA", "Grade");
    printf("---------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%f,%f,%c\n", &mhs[count].nim, mhs[count].nama, mhs[count].matkul, 
                  &mhs[count].tugas, &mhs[count].uts, &mhs[count].uas, &mhs[count].nilaiAkhir, &mhs[count].grade) != EOF) {
        printf("| %-10d | %-20s | %-20s | %-5.2f | %-5.2f | %-5.2f | %-5.2f | %-5c |\n", 
               mhs[count].nim, mhs[count].nama, mhs[count].matkul, mhs[count].tugas, mhs[count].uts, mhs[count].uas, mhs[count].nilaiAkhir, mhs[count].grade);
        count++;
    }

    int nim, found = 0;
    printf("\nMasukkan NIM mahasiswa yang ingin diedit: ");
    scanf("%d", &nim);

    // Menampilkan data berdasarkan NIM
    system("cls");
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
        system("cls");
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
        system("cls");
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
    system("cls");
    printf("Data berhasil diperbarui!\n");
}

void hapusData(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    // Tampilkan data mahasiswa
    system("cls");
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

    system("cls");
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
        system("cls");
        printf("Hapus Data Berhasil\n");
    } else {
        system("cls");
        printf("Data tidak ditemukan untuk NIM %d dan Mata Kuliah %s.\n", nim, mataKuliah);
    }

    // Tutup file
    fclose(file);
    fclose(tempFile);

    // Hapus file asli dan ganti dengan file sementara
    remove(filename);
    rename("TempDataMahasiswa.dat", filename);
}

void tampilkanDataMahasiswa(const Mahasiswa *mhs, int count) {
    printf("\n=== Data Nilai Mahasiswa ===\n");
    printf("| %-10s | %-20s | %-20s | %-5s | %-5s | %-5s | %-5s | %-5s |\n", "NIM", "Nama", "Mata Kuliah", "Tugas", "UTS", "UAS", "Akhir", "Grade");
    printf("---------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("| %-10d | %-20s | %-20s | %-5.2f | %-5.2f | %-5.2f | %-5.2f | %-5c |\n", mhs[i].nim, mhs[i].nama, mhs[i].matkul, mhs[i].tugas, mhs[i].uts, mhs[i].uas, mhs[i].nilaiAkhir, mhs[i].grade);
    }
}

void pencarianData(const char *filename) {
    int pilihan = 0;
    Mahasiswa mhs[100];
    int count = 0;

    FILE *file = fopen(filename, "r"); //
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%f,%f,%c\n", &mhs[count].nim, mhs[count].nama, mhs[count].matkul, &mhs[count].tugas, &mhs[count].uts, &mhs[count].uas, &mhs[count].nilaiAkhir, &mhs[count].grade) != EOF) {
        count++;
    }
    fclose(file);

    pencarianDataMenu:
    printf("\n=== Pencarian Data Mahasiswa ===\n");
    printf("\n1. Cari Data\n");
    printf("2. Urutkan Data\n");
    printf("3. Keluar\n");
    printf("Masukkan pilihan (1-3): ");
    scanf("%d", &pilihan);

    if (pilihan == 1) { // Searching Data
        int nim; // Cari Data berdasarkan NIM
        printf("Masukkan NIM: ");
        scanf("%d", &nim);
        printf("\n=== Hasil Pencarian ===\n");
        int found = 0;
        for (int i = 0; i < count; i++) {
            if (mhs[i].nim == nim) {
                if (!found) {
                    printf("| %-10s | %-20s | %-20s | %-5s | %-5s | %-5s | %-5s | %-5s |\n", "NIM", "Nama", "Mata Kuliah", "Tugas", "UTS", "UAS", "Akhir", "Grade");
                    printf("---------------------------------------------------------------------------------------------\n");
                    found = 1;
                }
                printf("| %-10d | %-20s | %-20s | %-5.2f | %-5.2f | %-5.2f | %-5.2f | %-5c |\n", mhs[i].nim, mhs[i].nama, mhs[i].matkul, mhs[i].tugas, mhs[i].uts, mhs[i].uas, mhs[i].nilaiAkhir, mhs[i].grade);
            }
        }
        if (!found) {
            printf("Data tidak ditemukan!\n");
        }
        goto pencarianDataMenu;
    } else if (pilihan == 2) { // Sorting Data
        system("cls");
        printf("\n1. Nama (Ascending)(A-Z)\n");
        printf("2. Nama (Descending)(Z-A)\n");
        printf("3. Nilai Akhir (Ascending)(0-100)\n");
        printf("4. Nilai Akhir (Descending)(100-0)\n");
        printf("Masukkan pilihan (1-4): ");
        scanf("%d", &pilihan);

        if (pilihan == 1) { // Ascending Nama
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (strcmp(mhs[i].nama, mhs[j].nama) > 0) {
                        Mahasiswa temp = mhs[i];
                        mhs[i] = mhs[j];
                        mhs[j] = temp;
                    }
                }
            }
        } else if (pilihan == 2) { // Descending Nama
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (strcmp(mhs[i].nama, mhs[j].nama) < 0) {
                        Mahasiswa temp = mhs[i];
                        mhs[i] = mhs[j];
                        mhs[j] = temp;
                    }
                }
            }
        } else if (pilihan == 3) { // Ascending Nilai Akhir
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (mhs[i].nilaiAkhir > mhs[j].nilaiAkhir) {
                        Mahasiswa temp = mhs[i];
                        mhs[i] = mhs[j];
                        mhs[j] = temp;
                    }
                }
            }
        } else if (pilihan == 4) { // Descending Nilai Akhir
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (mhs[i].nilaiAkhir < mhs[j].nilaiAkhir) {
                        Mahasiswa temp = mhs[i];
                        mhs[i] = mhs[j];
                        mhs[j] = temp;
                    }
                }
            }
        } else {
            system("cls");
            printf("Pilihan tidak valid! Harap masukkan angka 1-4.\n");
            goto pencarianDataMenu;
        }

        system("cls");
        tampilkanDataMahasiswa(mhs, count);
        goto pencarianDataMenu;
    } else if (pilihan == 3) {
        system("cls");
        printf("Kembali ke menu utama...\n");
    } else {
        system("cls");
        printf("Pilihan tidak valid! Harap masukkan angka 1-3.\n");
        goto pencarianDataMenu;
    }
}

void statistikaData(const char *filename) {
    int pilihan = 0;
    Mahasiswa mhs[100];
    int count = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f,%f,%f,%c\n", &mhs[count].nim, mhs[count].nama, mhs[count].matkul, &mhs[count].tugas, &mhs[count].uts, &mhs[count].uas, &mhs[count].nilaiAkhir, &mhs[count].grade) != EOF) {
        count++;
    }
    fclose(file);

    statistikaDataMenu:
    printf("\n=== Statistika Data Mahasiswa ===\n");
    printf("1. Nilai Tertinggi dan Terendah\n");
    printf("2. Distribusi Grade\n");
    printf("3. Kembali ke Menu Utama\n");
    printf("Masukkan pilihan (1-3): ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        system("cls");
        if (count == 0) {
            printf("Tidak ada data mahasiswa.\n");
            goto statistikaDataMenu;
        }
        float nilaiTertinggi = mhs[0].nilaiAkhir;
        float nilaiTerendah = mhs[0].nilaiAkhir;
        char namaTertinggi[50], namaTerendah[50];
        strcpy(namaTertinggi, mhs[0].nama);
        strcpy(namaTerendah, mhs[0].nama);

        for (int i = 1; i < count; i++) {
            if (mhs[i].nilaiAkhir > nilaiTertinggi) {
                nilaiTertinggi = mhs[i].nilaiAkhir;
                strcpy(namaTertinggi, mhs[i].nama);
            }
            if (mhs[i].nilaiAkhir < nilaiTerendah) {
                nilaiTerendah = mhs[i].nilaiAkhir;
                strcpy(namaTerendah, mhs[i].nama);
            }
        }
        printf("Nilai Tertinggi: %.2f (Nama: %s)\n", nilaiTertinggi, namaTertinggi);
        printf("Nilai Terendah: %.2f (Nama: %s)\n", nilaiTerendah, namaTerendah);
        goto statistikaDataMenu;
    } else if (pilihan == 2) {
        system("cls");
        int gradeA = 0, gradeB = 0, gradeC = 0, gradeD = 0, gradeE = 0;
        for (int i = 0; i < count; i++) {
            switch (mhs[i].grade) {
                case 'A': gradeA++; break;
                case 'B': gradeB++; break;
                case 'C': gradeC++; break;
                case 'D': gradeD++; break;
                case 'E': gradeE++; break;
            }
        }
        printf("Distribusi Grade:\n");
        printf("A: %d\n", gradeA);
        printf("B: %d\n", gradeB);
        printf("C: %d\n", gradeC);
        printf("D: %d\n", gradeD);
        printf("E: %d\n", gradeE);
        goto statistikaDataMenu;
    
    } else if (pilihan == 3) {
        system("cls");
        printf("Kembali ke menu utama...\n");
    } else {
        system("cls");
        printf("Pilihan tidak valid! Harap masukkan angka 1-3.\n");
        goto statistikaDataMenu;
    }
}

int main() {
    system("cls");
    loginPage();
    return 0;
}
