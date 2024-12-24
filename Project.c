#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Mengompilasi dan menjalankan file_lain.c...\n");

    // Perintah untuk mengompilasi file_lain.c
    system("gcc bacaData.c -o bacaData");
    
    // Perintah untuk menjalankan file_lain yang sudah dikompilasi
    //system("./file_lain"); // Untuk Linux/MacOS
    system("bacaData.exe"); // Untuk Windows

    return 0;
}
