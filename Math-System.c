#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

// Fungsi untuk mengecek apakah sebuah angka adalah bilangan prima
//bool untuk menyimpan nilai T ato F.

//PASSWORD : 096
bool isPrime(int num)
{
    if (num <= 1)
        {
            return false;
        }
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

// Fungsi untuk menghitung faktorial dari sebuah angka
int factorial(int num)
{
    if (num == 0 || num == 1) //Dalam fungsi factorialRecursive, jika n = 0, kita kembali 1 (karena 0! = 1). Jika tidak, kita mengalikan n dengan hasil rekursif dari n - 1.
        {
        return 1;
        }
    return num * factorial(num - 1);
}

// Fungsi untuk menjalankan menu kalkulator
void kalkulatorMenu()
{
    int choice, n; //int untuk kalkulator

    while (true)
        {
        system("cls");
        printf("Menu Kalkulator:\n");
        printf("1. Bilangan Prima\n");
        printf("2. Faktorial\n");
        printf("3. FizzBuzz\n");
        printf("4. Kembali ke Menu Utama\n");
        printf("Pilih operasi (1/2/3/4): ");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);

        if (choice == 4)
            {
            break;
            }

        switch (choice)
        {
            case 1:
                system("cls");
                printf("Masukkan jumlah angka prima yang ingin ditampilkan: ");

                fflush(stdin);
                scanf("%d", &n);
                fflush(stdin);
                printf("Bilangan prima pertama %d adalah: ", n);

                int count = 0, num = 2;
                while (count < n)
                    {
                    if (isPrime(num))
                    {
                        printf("%d, ", num);
                        count++;
                    }
                    num++;
                    }

                printf("\n");
                system("pause");
                system("cls");
                break;

            case 2:
                system("cls");
                printf("Masukkan angka untuk menghitung faktorial: ");
                fflush(stdin);
                scanf(" %d", &n);
                fflush(stdin);
                for(int i = n; i >=1 ;i--){
                    printf(" %d ", i);

                    if( i - 1 > 0){
                        printf("x");
                    }
                }
                printf("= %d\n", factorial(n));
                system("pause");
                system("cls");
                break;

            case 3:
                system("cls");
                printf("masukan bilangan : ");
                scanf("%d", &n);
                for (int i = 1; i <= n; i++)
                {
                    if (i % 3 == 0 && i % 5 == 0)
                    {
                        printf("FizzBuzz");
                    }

                    else if (i % 3 == 0)
                    {
                        printf("Fizz");
                    }

                    else if (i % 5 == 0)
                    {
                        printf("Buzz");
                    }

                    else
                    {
                        printf("%d ", i);
                    }
                printf("\n");
                }

                printf("\n");
                system("pause");
                system("cls");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
        }
}


// Fungsi untuk menjalankan menu bintang
void bintangMenu()
{
    int choice, n;

    while (true)
        {
        system("cls");
        printf("Menu Bintang:\n");
        printf("1. Anak Panah\n");
        printf("2. Outline Belah Ketupat\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("Pilih operasi (1/2/3): ");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);

        if (choice == 3)
            {
            break;
            }

        switch (choice)
        {
            case 1:
                printf("Masukkan tinggi anak panah: ");
                fflush(stdin);
                scanf("%d", &n);
                fflush(stdin);
                for (int baris = 1; baris <= n; baris++)
                {
                    for (int kolom = n; kolom>= baris ; kolom--)
                    {
                        printf(" * ");
                        Sleep(10);
                    }
                    for(int kolom = 1; kolom<=baris ;kolom++ )
                    {
                        printf(" ");
                    }
                    for (int kolom = n; kolom >= baris ; kolom--)
                    {
                        printf(" * ");
                        Sleep(10);
                    }
                    printf("\n");
                }
                for (int baris = 1; baris < n; baris++)
                {
                    for (int kolom = 1; kolom <= baris; kolom++)
                    {
                        printf(" * ");
                        Sleep(10);
                    }
                    for(int kolom = n ; kolom >= baris; kolom--)
                    {
                        printf(" ");
                    }
                    for (int kolom = 1; kolom <= baris ; kolom++)
                    {
                        printf(" * ");
                        Sleep(10);
                    }
                    printf("\n");
                }
                system("pause");
                system("cls");
                break;
            case 2:
                printf("Masukkan tinggi belah ketupat: ");
                fflush(stdin);
                scanf("%d", &n);
                fflush(stdin);
/*
                if (n % 2 == 0)
                {
                system("pause");
                printf("Gak Bisa!! \n");
                continue ;
                }
                */
                for (int i = 1; i <= n; i++)
                    {
                    for (int j = 1; j <= n; j++)
                    {
                    if( n % 2 == 0){
                        if (j == (n / 2 ) - (i - 1) || j == (n / 2 +1 ) + (i - 1) || j == (n / 2) - (n - i) || j == (n / 2 +1) + (n - i))
                            {
                                printf("*");
                                Sleep(100);
                            }
                        else
                            {
                                printf(" ");
                            }
                        }
                    else if(n % 2 == 1){
                         if (j == (n / 2 + 1) - (i - 1) || j == (n / 2 + 1) + (i - 1) || j == (n / 2 + 1) - (n - i) || j == (n / 2 + 1) + (n - i))
                            {
                                printf("*");
                                Sleep(100);
                            }
                        else
                            {
                                printf(" ");
                            }
                        }
                    }
                         printf("\n");
                    }



                system("pause");
                system("cls");
                break;

            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
        }
        }


int main()
{
    system ("cls");
    int number;
    bool validInput = false;
    char password[20];
    char correctPassword[] = "096";
    printf("Masukkan kata sandi: ");
    fflush(stdin);
    scanf("%s", password);
    fflush(stdin);

    if (strcmp(password, correctPassword) != 0)
        {
        printf("Kata sandi salah. Keluar dari program.\n");
        return 0;
        }

    int choice;

    while (true)
        {
        system("cls");
        printf("Menu Utama:\n");
        printf("1. Kalkulator\n");
        printf("2. Bintang\n");
        printf("3. Keluar\n");
        printf("Pilih menu (1/2/3): ");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
            case 1:
                system("cls");
                kalkulatorMenu();
                break;
            case 2:
                system("cls");
                bintangMenu();
                break;
            case 3:
                printf("Terima Kasih!!");
                return ;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                system("pause");
        }
        }

    return 0;
}


 /*while (!validInput)
        {
        printf("Masukkan angka: ");
        if (scanf("%d", &number) == 1)
        {
            validInput = true;
        }
        else
        {
            printf("Input tidak valid. Masukkan angka.\n");
            while (getchar() != '\n');
        }
        }

    printf("Anda memasukkan angka: %d\n", number);*/
