#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_PESANAN 10000
#define MAX_NAMA_BUYER 50
#define MAX_SIZE_NAMA_PELANGGAN 100

char *g_namaPelanggan;
char *g_namaPelangganUpperCase;

int Menu_Checkout();
int Menu_BuyerName();
int Menu_BuyerData();
int Menu_Receipt();
int Menu_DearAsdos();
int Menu_Exit();
int Menu_Main();

void __utils_printMenuItem(int currentArrowPosition, int menuPosition, const char *menuItemName)
{
    if (currentArrowPosition != menuPosition)
        printf("      ");
    else
        printf("===>> ");
    printf("%s\n", menuItemName);
}

void doWait(int num)
{
    Sleep(num);
}

void prettyPrint(const char *msg)
{
    fflush(stdin);
    fflush(stdout);
    for (int i = 0; i < strlen(msg); i++)
    {
        printf("%c", msg[i]);
        fflush(stdout);
        doWait(1);
    }
    fflush(stdout);
}

void clearScreen()
{
    system("cls");
    fflush(stdin);
    fflush(stdout);
}

void doLogin()
{
    free((void *)g_namaPelanggan);
    free((void *)g_namaPelangganUpperCase);
    g_namaPelanggan = (char *)malloc(sizeof(char) * MAX_SIZE_NAMA_PELANGGAN);
    g_namaPelangganUpperCase = (char *)malloc(sizeof(char) * MAX_SIZE_NAMA_PELANGGAN);

    fflush(stdout);
    prettyPrint("==== Selamat Datang di ... ====\n");
    prettyPrint("Silahkan Input Nama Pelanggan\n");
    prettyPrint("    >> ");
    fflush(stdin);
    fgets(g_namaPelanggan, MAX_SIZE_NAMA_PELANGGAN, stdin);
    fflush(stdin);

    if ((strlen(g_namaPelanggan) > 0) && (g_namaPelanggan[strlen(g_namaPelanggan) - 1] == '\n'))
        g_namaPelanggan[strlen(g_namaPelanggan) - 1] = '\0';

    for (int i = 0; i < strlen(g_namaPelanggan); i++)
    {
        g_namaPelangganUpperCase[i] = (char)toupper(g_namaPelanggan[i]);
    }
}

int DataPesanan[MAX_PESANAN] = {-1}; // array data pesananan -> untuk menyimpan data pesanan (checkout)
int CursorDataPesanan = 0;           // cursor untuk ke array data pesanan

int Menu_Checkout()
{
    int currentArrowPosition = 0;
    while (1)
    {
        system("cls");
        printf("___________________________________________________\n");
        printf("||                                               ||\n");
        printf("||                Restoran HALAL                 ||\n");
        printf("___________________________________________________\n");
        printf("||                                               ||\n");
        __utils_printMenuItem(currentArrowPosition, 0, "  Ayam Bakar.................Rp15.000");
        __utils_printMenuItem(currentArrowPosition, 1, "  Ayam Goreng................Rp15.000");
        __utils_printMenuItem(currentArrowPosition, 2, "  All Varian Indomie Goreng..Rp12.000");
        __utils_printMenuItem(currentArrowPosition, 3, "  All Varian Indomie Kuah....Rp12.000");
        __utils_printMenuItem(currentArrowPosition, 4, "  Nasi Goreng................Rp10.000");
        __utils_printMenuItem(currentArrowPosition, 5, "  Esteh......................Rp5.000 ");
        __utils_printMenuItem(currentArrowPosition, 6, "  Lemon Tea..................Rp7.000 ");
        __utils_printMenuItem(currentArrowPosition, 7, "  Jeruk Peras................Rp6.500 ");
        __utils_printMenuItem(currentArrowPosition, 8, "  Susu Milo..................Rp4.500 ");
        __utils_printMenuItem(currentArrowPosition, 9, "  Air Es.....................Rp1.000 ");
        printf("\n");
        __utils_printMenuItem(currentArrowPosition, 10, "              KEMBALI");
        printf("||                                               ||\n");
        printf("___________________________________________________\n");

        int key = -1;
        key = getch();

        if (key == 80)
            currentArrowPosition++; // bawah
        else if (key == 72)
            currentArrowPosition--; // atas
        else if (key == 13)
        {
            if (currentArrowPosition == 10)
            {
                return 0;
            }

            DataPesanan[CursorDataPesanan] = currentArrowPosition;
            CursorDataPesanan++;
        }

        if (currentArrowPosition < 0)
        {
            currentArrowPosition = 10;
        }
        else if (currentArrowPosition > 10)
        {
            currentArrowPosition = 0;
        }
    }
}

int Menu_BuyerName()
{
    system("cls");
    fflush(stdin);

    for (int i = 0; g_namaPelanggan[i] != '\0'; i++)
    {
        g_namaPelanggan[i] = toupper(g_namaPelanggan[i]);
    }
    printf("Selamat datang, %s!\n", g_namaPelanggan);
    system("pause");

    Menu_Main();

    return 0;
}

int Menu_BuyerData()
{
    clearScreen();
    printf("Nama Kamu : %s\n", g_namaPelangganUpperCase);
    printf("====================\n");
    printf("Menu yang Kamu Pilih :\n");
    printf("====================\n");

    for (int i = 0; i < MAX_PESANAN; i++)
    {
        if (DataPesanan[i] == -1)
        {
            continue;
        }
        switch (DataPesanan[i])
        {
        case 0:
            printf("|| Ayam Bakar\n");
            break;
        case 1:
            printf("|| Ayam Goreng\n");
            break;
        case 2:
            printf("|| All Varian Indomie Goreng\n");
            break;
        case 3:
            printf("|| All Varian Indomie Kuah\n");
            break;
        case 4:
            printf("|| Nasi Goreng\n");
            break;
        case 5:
            printf("|| Esteh\n");
            break;
        case 6:
            printf("|| Lemon Tea\n");
            break;
        case 7:
            printf("|| Jeruk Peras\n");
            break;
        case 8:
            printf("|| Susu Milo\n");
            break;
        case 9:
            printf("|| Air Es\n");
            break;
        }
    }
    printf("\n");
    system("pause");

    return 0;
}

int Menu_Receipt()
{
    int semuaJumlah[MAX_PESANAN];
    int harga[MAX_PESANAN] = {15000, 15000, 12000, 12000, 10000, 5000, 7000, 6500, 4500, 1000};
    int totalHarga = 0;
    for (int i = 0; i < MAX_PESANAN; i++)
    {
        semuaJumlah[i] = 0;
    }

    system("cls");
    printf("___________________________________________________\n");
    printf("||                                               ||\n");
    printf("||                Detail Pesanan                 ||\n");
    printf("___________________________________________________\n");

    for (int i = 0; i < MAX_PESANAN; i++)
    {
        if (DataPesanan[i] == -1)
        {
            continue;
        }
        semuaJumlah[DataPesanan[i]]++;
    }

    for (int i = 0; i < MAX_PESANAN; i++)
    {
        if (semuaJumlah[i] == 0)
        {
            continue;
        }

        switch (i)
        {
        case 0:
            printf("||  Ayam Bakar\n");
            printf("||       Rp15.000 x %d   =>  Rp%d\n", semuaJumlah[i], semuaJumlah[i] * 15000);
            totalHarga += semuaJumlah[i] * harga[i];
            break;
        case 1:
            printf("||  Ayam Goreng\n");
            printf("||       Rp15.000 x %d   =>  Rp%d\n", semuaJumlah[i], semuaJumlah[i] * 15000);
            totalHarga += semuaJumlah[i] * harga[i];
            break;
        case 2:
            printf("||  All Varian Indomie Goreng\n");
            printf("||       Rp12.000 x %d   =>  Rp%d\n", semuaJumlah[i], semuaJumlah[i] * 12000);
            totalHarga += semuaJumlah[i] * harga[i];
            break;
        case 3:
            printf("||  All Varian Indomie Kuah\n");
            printf("||       Rp12.000 x %d   =>  Rp%d\n", semuaJumlah[i], semuaJumlah[i] * 12000);
            totalHarga += semuaJumlah[i] * harga[i];
            break;
        case 4:
            printf("||  Nasi Goreng\n");
            printf("||       Rp10.000 x %d   =>  Rp%d\n", semuaJumlah[i], semuaJumlah[i] * 10000);
            totalHarga += semuaJumlah[i] * harga[i];
            break;
        case 5:
            printf("||  Esteh\n");
            printf("||       Rp5.000  x %d   =>  Rp%d\n", semuaJumlah[i], semuaJumlah[i] * 5000);
            totalHarga += semuaJumlah[i] * harga[i];
            break;
        case 6:
            printf("||  Lemon Tea\n");
            printf("||       Rp7.000  x %d   =>  Rp%d\n", semuaJumlah[i], semuaJumlah[i] * 7000);
            totalHarga += semuaJumlah[i] * harga[i];
            break;
        case 7:
            printf("||  Jeruk Peras\n");
            printf("||       Rp6.500  x %d   =>  Rp%d\n", semuaJumlah[i], semuaJumlah[i] * 6500);
            totalHarga += semuaJumlah[i] * harga[i];
            break;
        case 8:
            printf("||  Susu Milo\n");
            printf("||       Rp4.500  x %d   =>  Rp%d\n", semuaJumlah[i], semuaJumlah[i] * 4500);
            totalHarga += semuaJumlah[i] * harga[i];
            break;
        case 9:
            printf("||  Air Es\n");
            printf("||       Rp1.000  x %d   =>  Rp%d\n", semuaJumlah[i], semuaJumlah[i] * 1000);
            totalHarga += semuaJumlah[i] * harga[i];
            break;
        }
    }
    printf("___________________________________________________\n");
    printf("||                                               ||\n");
    printf("||                Total Harga                    ||\n");
    printf("||                   Rp%d                        ||\n", totalHarga);
    printf("___________________________________________________\n");

    int jumlahUang;
    char buffer[100];

    printf("Masukkan jumlah uang yang akan dibayarkan: Rp");
    scanf("%d", &jumlahUang);

    fgets(buffer, sizeof(buffer), stdin);

    if (jumlahUang < totalHarga)
    {
        printf("Jumlah uang kurang. Transaksi dibatalkan.\n");
    }
    else
    {
        int kembalian = jumlahUang - totalHarga;
        printf("Uang kembalian: Rp%d\n", kembalian);
    }

    system("pause");

    return 0;
}

int Menu_DearAsdos()
{
    clearScreen();
    prettyPrint("Dear Asdos,");
    system("pause");

    return 0;
}

int Menu_Exit()
{
    clearScreen();
    prettyPrint("Terima Kasih\n");
    prettyPrint("Sudah Menggunakan Aplikasi Kami!!\n");

    int key = -1;
    while (1)
    {
        key = getch();
        if (key == 13)
        {
            return 1;
        }
        else if (key == 27)
        {
            free((void *)g_namaPelanggan);
            free((void *)g_namaPelangganUpperCase);
            exit(0);
        }
        else
        {
            return 0;
        }
    }
}

int Menu_Main()
{
    int currentArrowPosition = 0;
    while (1)
    {
        system("cls");
        printf("=================================\n");
        printf("=        SELAMAT DATANG         =\n");
        printf("=              DI               =\n");
        printf("=      TUGAS RANCANG DDP-H      =\n");
        printf("=================================\n");
        __utils_printMenuItem(currentArrowPosition, 0, "CHEKOUT");
        __utils_printMenuItem(currentArrowPosition, 1, "BUYER'S NAME");
        __utils_printMenuItem(currentArrowPosition, 2, "BUYER'S DATA");
        __utils_printMenuItem(currentArrowPosition, 3, "RECIEPT");
        __utils_printMenuItem(currentArrowPosition, 4, "DEAR ASDOS");
        __utils_printMenuItem(currentArrowPosition, 5, "Exit");
        printf(">>>>>>>>>>>>>  %d  <<<<<<<<<<<<<<\n\n", currentArrowPosition + 1);

        int key = -1;
        key = getch();

        if (key == 80)
            currentArrowPosition++; // bawah
        else if (key == 72)
            currentArrowPosition--; // atas
        else if (key == 13)
            return currentArrowPosition; // enter

        if (currentArrowPosition < 0)
        {
            currentArrowPosition = 5;
        }
        else if (currentArrowPosition > 5)
        {
            currentArrowPosition = 0;
        }
    }
}

int main()
{
    for (int i = 0; i < MAX_PESANAN; i++)
    {
        DataPesanan[i] = -1;
    }
    while (1)
    {
        clearScreen();
        doLogin();
        while (1)
        {

            int choosenMenu = Menu_Main();
            switch (choosenMenu)
            {
            case 0:
                Menu_Checkout();
                break;
            case 1:
                Menu_BuyerName();
                break;
            case 2:
                Menu_BuyerData();
                break;
            case 3:
                Menu_Receipt();
                break;
            case 4:
                Menu_DearAsdos();
                break;
            case 5:
                if (Menu_Exit() == 1)
                {
                    doLogin();
                    break;
                }
                break;
            }
        }
    }

    free((void *)g_namaPelanggan);
    free((void *)g_namaPelangganUpperCase);
    free((void *)DataPesanan);
    return 0;
}
