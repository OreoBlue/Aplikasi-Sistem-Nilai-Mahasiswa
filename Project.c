#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Mengompilasi dan menjalankan file_lain.c...\n");

    // Perintah untuk mengompilasi file
    system("gcc homePage.c -o homePage");
    
    // Perintah untuk menjalankan file yang sudah dikompilasi
    //system("./homePage"); // Untuk Linux/MacOS
    system("homePage.exe"); // Untuk Windows

    return 0;
}
