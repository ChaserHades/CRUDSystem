#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_ARRAY_SIZE 100

void clearScreen() 
{
    system("cls");
    fflush(stdin);
    fflush(stdout);
}

struct Siswa
{
    char nama[50];
    float nilaiASD;
    float nilaiAutomata;
    float nilaiSetres;
};

void bubbleSort(struct Siswa *mahasiswa, const int jumlah) 
{
    for (int i = 0; i < jumlah - 1; i++) 
    {
        for (int j = 0; j < jumlah - i - 1; j++) 
        {
            if (strcmp(mahasiswa[j].nama, mahasiswa[j + 1].nama) > 0) 
            {
                struct Siswa temp = mahasiswa[j];
                mahasiswa[j] = mahasiswa[j + 1];
                mahasiswa[j + 1] = temp;
            }
        }
    }
}

void inputData(struct Siswa **mahasiswa, int *jumlah)
{
    *mahasiswa = (struct Siswa *)realloc(*mahasiswa, (*jumlah + 1) * sizeof(struct Siswa));

    if (*mahasiswa == NULL)
    {
        printf("Data tidak ada.\n");
        exit(EXIT_FAILURE);
    }

    printf("Masukan Nama: ");
    fgets((*mahasiswa)[*jumlah].nama, sizeof((*mahasiswa)[*jumlah].nama), stdin); 
    strtok((*mahasiswa)[*jumlah].nama, "\n");                                   
    printf("Masukan Nilai ASD: ");
    scanf("%f", &(*mahasiswa)[*jumlah].nilaiASD);
    getchar(); 
    printf("Masukan Nilai Automata: ");
    scanf("%f", &(*mahasiswa)[*jumlah].nilaiAutomata);
    getchar(); 
    printf("Masukan Nilai Setres: ");
    scanf("%f", &(*mahasiswa)[*jumlah].nilaiSetres);
    getchar(); 

    (*jumlah)++;
}

void dataMahasiswa(struct Siswa *mahasiswa, int jumlah)
{
    clearScreen();
    printf("\n=== Data Mahasiswa ===\n\n");

    for (int i = 0; i < jumlah; i++)
    {
        printf("Nama: %s\n", mahasiswa[i].nama);
        printf("Nilai ASD: %.2f\n", mahasiswa[i].nilaiASD);
        printf("Nilai Automata: %.2f\n", mahasiswa[i].nilaiAutomata);
        printf("Nilai Setres: %.2f\n\n", mahasiswa[i].nilaiSetres);
    }
}


void persetujuan(struct Siswa **mahasiswa, int *jumlah)
{
    char choice;

    printf("\nTambah data lagi? (Y/N): ");
    choice = getch();

    if (choice == 'Y' || choice == 'y')
    {
        clearScreen();
        inputData(mahasiswa, jumlah);
        persetujuan(mahasiswa, jumlah); 
    }
    else if (choice == 'N' || choice == 'n')
    {
        clearScreen();
        printf("Kembali ke Menu Utama.\n");
    }
    else
    {
        clearScreen();
        printf("\nInput tidak valid. Silakan masukkan Y atau N.\n");
        persetujuan(mahasiswa, jumlah);
    }
}

void outputMain(struct Siswa **mahasiswa, int *jumlah)
{
    inputData(mahasiswa, jumlah); 
    persetujuan(mahasiswa, jumlah); 
}

void lihatData(struct Siswa *mahasiswa, int jumlah)
{
    dataMahasiswa(mahasiswa, jumlah);
}

void frontMenu(struct Siswa **mahasiswa, int *jumlah)
{
    clearScreen();
    printf("\n=== SILAHKAN PILIH ===\n");
    printf("1. Input Data Mahasiswa\n");
    printf("2. Lihat Data Mahasiswa\n");
    printf("3. Urutkan Data Mahasiswa\n");
    printf("4. Exit\n\n");

    tombol(mahasiswa, jumlah);
    
}

void tombol(struct Siswa **mahasiswa, int *jumlah) 
{
    char pencet;
        
    pencet = getch();
        
    switch (pencet)
    {
        case '1':
            outputMain(mahasiswa, jumlah);
            break;
        case '2':
            clearScreen();
            if (*jumlah == 0)
                printf("Belum ada data mahasiswa yang dimasukkan.\n");
            else
                lihatData(*mahasiswa, *jumlah);
            break;
        case '3':
            if (*jumlah == 0)
            printf("Belum ada data mahasiswa yang dimasukkan.\n");
            else 
            {
            bubbleSort(*mahasiswa, *jumlah);  
            clearScreen();
            printf("Data mahasiswa telah diurutkan berdasarkan nama.\n");
            lihatData(*mahasiswa, *jumlah);
            }
        break;
        case '4':
            clearScreen();
            printf("Terimkasih\n");
            exit(0);
        default:
            printf("Pilihan tidak sesuai.\n");
            break;
    }
    printf("\nEnter...");
    getch();
    frontMenu(mahasiswa, jumlah);
}

int main()
{
    struct Siswa *mahasiswa = NULL; 
    int jumlah = 0;                      
    
    frontMenu(&mahasiswa, &jumlah);
    
    free(mahasiswa);
    return 0;
}