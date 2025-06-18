#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> // GA USAH DIPELAJARI
#include <unistd.h> //KALO WINDOWS GANTI <windows.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

struct Pengunjung 
{
    char nama[50];
    int NIM;
};

struct User 
{ 
    char username[50]; 
    char password[50]; 
}; 

struct Perpustakaan 
{
    char judul[100];
    char author[50];
    int tahun;
    int status;
    char namaPeminjam[50];
    int NIM;
    char tanggalPinjam[20];
};

struct Pengunjung user;

// BUAT BERSIHIN BUFFER
void clearScreen() 
{
    printf("\033[H\033[J"); // UBAH JADI system("cls"); KALO WINDOWS
    fflush(stdin);
    fflush(stdout);
}

// CUMA BUAT ANIMASI, BIAR TULISANNYA BISA JALAN
void prettyPrint(const char *msg)
{
    fflush(stdin);
    fflush(stdout);
    for (int i = 0; i < strlen(msg); i++)
    {
        printf("%c", msg[i]);
        fflush(stdout);
        usleep(10000);
    }
    fflush(stdout);
}

// ANIMASI BIASA
void loadingAnimation(int duration) 
{
    const char loadingChars[] = {'|', '/', '-', '\\'};
    int numChars = sizeof(loadingChars) / sizeof(loadingChars[0]);
    int timeInterval = 100;

    int iterations = (duration * 1000) / timeInterval;

    for (int i = 0; i < iterations; i++) 
    {
        printf("\rLoading... %c", loadingChars[i % numChars]);
        fflush(stdout);
        usleep(timeInterval * 1000);
    }
    printf("\r                \r"); 
}

// INI AKU AJA (EZER)
void tanggalWaktu(char *buffer, size_t bufferSize)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    strftime(buffer, bufferSize, "%d/%m/%Y %H:%M:%S", local);
}

// BUAT CEK YG DI INPUT ITU HURUF(ALPHABET) ATAU BUKAN
int abjad(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]) && str[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

// SAMA KAYA ATAS, BEDANYA INI CEK ANGKA
int angka(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

// BUAT BIKIN FILE TXT NYA
void loadFromFile(struct Perpustakaan **buku, int *jumlah) 
{
    const char *fileName = "tabelHidup.txt";
    FILE *file = fopen(fileName, "r");
    if (file == NULL) 
    {
        printf("File not found. Starting with an empty database.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) 
    {
        *buku = (struct Perpustakaan *)realloc(*buku, (*jumlah + 1) * sizeof(struct Perpustakaan));
        if (*buku == NULL) 
        {
            printf("Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }

        sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%d,%[^\n]",
               (*buku)[*jumlah].judul, (*buku)[*jumlah].author, &(*buku)[*jumlah].tahun, 
               &(*buku)[*jumlah].status, (*buku)[*jumlah].namaPeminjam, &(*buku)[*jumlah].NIM,
               (*buku)[*jumlah].tanggalPinjam);
        (*jumlah)++;
    }

    fclose(file);
}

// BUAT BACA FILE
void saveToFile(struct Perpustakaan *buku, int jumlah) 
{
    const char *fileName = "tabelHidup.txt";
    FILE *file = fopen(fileName, "w");
    if (file == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < jumlah; i++) 
    {
        fprintf(file, "%s,%s,%d,%d,%s,%d,%s\n", buku[i].judul, buku[i].author, buku[i].tahun, 
                buku[i].status, buku[i].namaPeminjam, buku[i].NIM, buku[i].tanggalPinjam);
    }

    fclose(file);
}

// CUMA DISPLAY, JADI APA YG KITA INPUT BISA KE CETAK DI TABEL INI
void dataBuku(struct Perpustakaan *buku, int jumlah)
{
    clearScreen();
    printf("\n========================== Data Perpustakaan ==========================\n");
    printf("---------------------------------------------------------------------------\n");
    printf("| %-30s | %-20s | %-4s | %-10s | %-15s | %-20s |\n", 
           "Judul", "Author", "Tahun", "Status", "Peminjam", "Tanggal Pinjam");
    printf("---------------------------------------------------------------------------");

    for (int i = 0; i < jumlah; i++)
    {
        printf("\n| %-30s | %-20s | %-5d | %-10s | %-15s | %-20s |", 
               buku[i].judul, buku[i].author, buku[i].tahun, 
               buku[i].status ? "Dipinjam" : "Tersedia", 
               buku[i].status ? buku[i].namaPeminjam : "-", 
               buku[i].status ? buku[i].tanggalPinjam : "-");
    }

    printf("\n-------------------------------------------------------------------------\n");
}

// INPUT BUKU BARU
void inputData(struct Perpustakaan **buku, int *jumlah)
{
    *buku = (struct Perpustakaan *)realloc(*buku, (*jumlah + 1) * sizeof(struct Perpustakaan));

    if (*buku == NULL)
    {
        printf("Data tidak ada.\n");
        exit(EXIT_FAILURE);
    }

    char input[100];
    int isValid = 0;

    while (!isValid)
    {
        printf("Masukan Judul: ");
        fgets(input, sizeof(input), stdin);
        strtok(input, "\n");

        if (!abjad(input))
        {
            printf("Input tidak valid. Judul hanya boleh berisi huruf abjad.\n");
        }
        else
        {
            isValid = 1;
            strcpy((*buku)[*jumlah].judul, input);
        }
    }

    isValid = 0;
    while (!isValid)
    {
        printf("Masukan Author: ");
        fgets(input, sizeof(input), stdin);
        strtok(input, "\n");

        if (!abjad(input))
        {
            printf("Input tidak valid. Author hanya boleh berisi huruf abjad.\n");
        }
        else
        {
            isValid = 1;
            strcpy((*buku)[*jumlah].author, input);
        }
    }

    isValid = 0;
    while (!isValid)
    {
        printf("Masukan Tahun: ");
        fgets(input, sizeof(input), stdin);
        strtok(input, "\n");

        if (!angka(input))
        {
            printf("Input tidak valid. Masukan tahun dalam format angka (misal: 2020).\n");
        }
        else
        {
            isValid = 1;
            (*buku)[*jumlah].tahun = atoi(input);
        }
    }

    (*buku)[*jumlah].status = 0;
    strcpy((*buku)[*jumlah].namaPeminjam, "-");
    (*buku)[*jumlah].NIM = 0;
    strcpy((*buku)[*jumlah].tanggalPinjam, "-");

    (*jumlah)++;
}

// BUAT CEK BUKU YANG DIPINJAM 
void pinjamBuku(struct Perpustakaan *buku, int jumlah)
{
    char judul[100];
    int found = 0;

    printf("Masukan judul buku yang akan dipinjam: ");
    fgets(judul, sizeof(judul), stdin);
    strtok(judul, "\n");

    for (int i = 0; i < jumlah; i++)
    {
        if (strcmp(buku[i].judul, judul) == 0 && buku[i].status == 0)
        {
            found = 1;

            printf("Masukan Nama Peminjam: ");
            fgets(buku[i].namaPeminjam, sizeof(buku[i].namaPeminjam), stdin);
            strtok(buku[i].namaPeminjam, "\n");

            printf("Masukan NIM Peminjam: ");
            char nimInput[20];
            fgets(nimInput, sizeof(nimInput), stdin);
            strtok(nimInput, "\n");
            buku[i].NIM = atoi(nimInput);

            char tanggal[20];
            tanggalWaktu(tanggal, sizeof(tanggal));
            strcpy(buku[i].tanggalPinjam, tanggal);

            buku[i].status = 1; // Set status to 'Dipinjam'
            printf("Buku dengan judul '%s' telah dipinjam oleh %s.\n", buku[i].judul, buku[i].namaPeminjam);
            saveToFile(buku, jumlah);
            break;
        }
        else if (strcmp(buku[i].judul, judul) == 0 && buku[i].status == 1)
        {
            found = 1;
            printf("Buku dengan judul '%s' sedang dipinjam oleh %s.\n", buku[i].judul, buku[i].namaPeminjam);
            break;
        }
    }

        if (!found)
    {
        printf("Buku dengan judul '%s' tidak ditemukan atau sudah dipinjam.\n", judul);
    }
}

// BUAT CEK BUKU YANG UDAH BALIK
void kembalikanBuku(struct Perpustakaan *buku, int jumlah)
{
    char judul[100];
    int found = 0;

    printf("Masukan judul buku yang akan dikembalikan: ");
    fgets(judul, sizeof(judul), stdin);
    strtok(judul, "\n");

    for (int i = 0; i < jumlah; i++)
    {
        if (strcmp(buku[i].judul, judul) == 0 && buku[i].status == 1)
        {
            found = 1;

            // Update data
            buku[i].status = 0;
            strcpy(buku[i].namaPeminjam, "-");
            buku[i].NIM = 0;
            strcpy(buku[i].tanggalPinjam, "-");

            printf("Buku dengan judul '%s' telah dikembalikan.\n", buku[i].judul);
            saveToFile(buku, jumlah);
            break;
        }
        else if (strcmp(buku[i].judul, judul) == 0 && buku[i].status == 0)
        {
            found = 1;
            printf("Buku dengan judul '%s' tidak sedang dipinjam.\n", buku[i].judul);
            break;
        }
    }

    if (!found)
    {
        printf("Buku dengan judul '%s' tidak ditemukan atau tidak sedang dipinjam.\n", judul);
    }
}

// BISA BUAT NGEDIT DATA: JUDUL, AUTHOR, TAHUN BERUBAH.
void editData(struct Perpustakaan *buku, int jumlah)
{
    char judul[100];
    int found = 0;

    printf("Masukan judul buku yang akan diubah: ");
    fgets(judul, sizeof(judul), stdin);
    strtok(judul, "\n");

    for (int i = 0; i < jumlah; i++)
    {
        if (strcmp(buku[i].judul, judul) == 0)
        {
            found = 1;

            printf("Masukan Judul baru: ");
            fgets(buku[i].judul, sizeof(buku[i].judul), stdin);
            strtok(buku[i].judul, "\n");

            printf("Masukan Author baru: ");
            fgets(buku[i].author, sizeof(buku[i].author), stdin);
            strtok(buku[i].author, "\n");

            printf("Masukan Tahun baru: ");
            char tahunInput[20];
            fgets(tahunInput, sizeof(tahunInput), stdin);
            strtok(tahunInput, "\n");
            buku[i].tahun = atoi(tahunInput);

            printf("Data buku dengan judul '%s' telah diubah.\n", judul);
            saveToFile(buku, jumlah);
            break;
        }
    }

    if (!found)
    {
        printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
    }
}

// HAPUS DATA SESUAI JUDUL
void hapusData(struct Perpustakaan **buku, int *jumlah)
{
    char judul[100];
    int found = 0;

    printf("Masukan judul buku yang akan dihapus: ");
    fgets(judul, sizeof(judul), stdin);
    strtok(judul, "\n");

    for (int i = 0; i < *jumlah; i++)
    {
        if (strcmp((*buku)[i].judul, judul) == 0)
        {
            found = 1;

            for (int j = i; j < *jumlah - 1; j++)
            {
                (*buku)[j] = (*buku)[j + 1];
            }
            (*jumlah)--;

            *buku = (struct Perpustakaan *)realloc(*buku, (*jumlah) * sizeof(struct Perpustakaan));
            printf("Buku dengan judul %s telah dihapus.\n", judul);
            saveToFile(*buku, *jumlah);
            break;
        }
    }
    if (!found)
    {
        printf("Buku dengan judul %s tidak ditemukan.\n", judul);
    }
}

// MENU AWAL BIASA
void frontMenu(struct Perpustakaan **buku, int *jumlah)
{
    clearScreen();
    printf("\n=== SELAMAT DATANG DI PERPUSTAKAAN ===\n");
    printf("1. Tambah Data Buku\n");
    printf("2. Lihat Data Buku\n");
    printf("3. Pinjam Buku\n");
    printf("4. Kembalikan Buku\n");
    printf("5. Edit Data Buku\n");
    printf("6. Hapus Data Buku\n");
    printf("7. Cari Buku\n");
    printf("8. Urutkan Data Buku\n");
    printf("9. Exit\n\n");

    mainMenu(buku, jumlah);
}

// BUAT NUNGGU INPUTAN DARI USER
void mainMenu(struct Perpustakaan **buku, int *jumlah)
{
    char pencet;

    pencet = getchar();
    getchar();

    switch (pencet)
    {
        case '1':
            clearScreen();
            inputData(buku, jumlah);
            frontMenu(buku, jumlah);
            break;
        case '2':
            clearScreen();
            if (*jumlah == 0)
                printf("Belum ada data buku yang dimasukkan.\n");
            else
                dataBuku(*buku, *jumlah);
            prettyPrint("\nPress Enter to continue...");
            getchar();
            frontMenu(buku, jumlah);
            break;
        case '3':
            clearScreen();
            if (*jumlah == 0)
                printf("Belum ada data buku yang dimasukkan.\n");
            else
                pinjamBuku(*buku, *jumlah);
            prettyPrint("\nPress Enter to continue...");
            getchar();
            frontMenu(buku, jumlah);
            break;
        case '4':
            clearScreen();
            if (*jumlah == 0)
                printf("Belum ada data buku yang dimasukkan.\n");
            else
                kembalikanBuku(*buku, *jumlah);
            prettyPrint("\nPress Enter to continue...");
            getchar();
            frontMenu(buku, jumlah);
            break;
        case '5':
            clearScreen();
            if (*jumlah == 0)
                printf("Belum ada data buku yang dimasukkan.\n");
            else
                editData(*buku, *jumlah);
            prettyPrint("\nPress Enter to continue...");
            getchar();
            frontMenu(buku, jumlah);
            break;
        case '6':
            clearScreen();
            if (*jumlah == 0)
                printf("Belum ada data buku yang dimasukkan.\n");
            else
                hapusData(buku, jumlah);
            prettyPrint("\nPress Enter to continue...");
            getchar();
            frontMenu(buku, jumlah);
            break;
        case '7':
            clearScreen();
            if (*jumlah == 0)
                printf("Belum ada data buku yang dimasukkan.\n");
            else
                cariBuku(*buku, *jumlah);
            prettyPrint("\nPress Enter to continue...");
            getchar();
            frontMenu(buku, jumlah);
            break;
        case '8':
            clearScreen();
            if (*jumlah == 0)
                printf("Belum ada data buku yang dimasukkan.\n");
            else
                urutkanBuku(*buku, *jumlah);
            prettyPrint("\nPress Enter to continue...");
            getchar();
            frontMenu(buku, jumlah);
            break;
        case '9':
            clearScreen();
            printf("Terimakasih telah menggunakan layanan perpustakaan.\n");
            exit(0);
        default:
            printf("Pilihan tidak valid.\n");
            break;
    }
}

// BUAT NYARI BUKU YANG MAU DICARI
void cariBuku(struct Perpustakaan *buku, int jumlah)
{
    char judul[100];
    int found = 0;

    printf("Masukan judul buku yang akan dicari: ");
    fgets(judul, sizeof(judul), stdin);
    strtok(judul, "\n");

    for (int i = 0; i < jumlah; i++)
    {
        if (strcmp(buku[i].judul, judul) == 0)
        {
            found = 1;

            printf("\nBuku ditemukan:\n");
            printf("Judul: %s\n", buku[i].judul);
            printf("Author: %s\n", buku[i].author);
            printf("Tahun: %d\n", buku[i].tahun);
            printf("Status: %s\n", buku[i].status ? "Dipinjam" : "Tersedia");
            printf("Peminjam: %s\n", buku[i].status ? buku[i].namaPeminjam : "-");
            printf("Tanggal Pinjam: %s\n", buku[i].status ? buku[i].tanggalPinjam : "-");
            break;
        }
    }

    if (!found)
    {
        printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
    }
}

// NGURUTIN BUKU SESUAI DARI JUDUL A-Z
void urutkanBuku(struct Perpustakaan *buku, int jumlah)
{
    // Bubble sort based on judul
    struct Perpustakaan temp;

    for (int i = 0; i < jumlah - 1; i++)
    {
                for (int j = 0; j < jumlah - i - 1; j++)
        {
            if (strcmp(buku[j].judul, buku[j + 1].judul) > 0)
            {
                temp = buku[j];
                buku[j] = buku[j + 1];
                buku[j + 1] = temp;
            }
        }
    }

    printf("Data buku berhasil diurutkan.\n");
    dataBuku(buku, jumlah);
}

void login(struct Perpustakaan **buku, int *jumlah)
{
    clearScreen();
    char correctUsername[MAX_USERNAME_LENGTH] = "admin";
    char correctPassword[MAX_PASSWORD_LENGTH] = "1234";

    char inputUsername[MAX_USERNAME_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(inputUsername, MAX_USERNAME_LENGTH, stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(correctUsername, inputUsername) == 0 && strcmp(correctPassword, inputPassword) == 0) 
    {
        printf("Login successful!\n");
        frontMenu(buku, jumlah);
    } 
    else 
    {
        printf("Incorrect username or password.\n");
    }
}




int main()
{
    struct Perpustakaan *buku = NULL;
    int jumlah = 0;


    loadFromFile(&buku, &jumlah);

    while (1)
    {
        login(&buku, &jumlah);
    }

    return 0;
}


