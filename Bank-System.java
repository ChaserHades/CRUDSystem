import java.io.Console;
import java.util.Scanner;

// Class BankAccount untuk menyimpan data rekening
class BankAccount 
{
    private double saldo;
    private final String nomorKartu;
    private final String pin;
    private final double interestRate = 0.05; // 5% interest rate per bulan

    public BankAccount(String nomorKartu, String pin) 
    {
        this.saldo = 0; // Saldo awal 0
        this.nomorKartu = nomorKartu;
        this.pin = pin;
    }

    public boolean login(String nomorKartu, String pin) 
    {
        return this.nomorKartu.equals(nomorKartu) && this.pin.equals(pin);
    }

    public double getSaldo() 
    {
        return saldo;
    }

    public void tarikTunai(double jumlah) throws Exception 
    {
        if (jumlah > saldo) 
        {
            throw new Exception("Saldo tidak cukup!!");
        } else 
        {
            saldo -= jumlah;
            System.out.printf("Uang berhasil ditarik. Sisa saldo: %.2f%n", saldo);
        }
    }

    public void setorTunai(double jumlah) throws Exception 
    {
        if (jumlah <= 0) 
        {
            throw new Exception("Jumlah setoran tidak valid!");
        } else 
        {
            saldo += jumlah;
            System.out.printf("Deposit berhasil. Jumlah saldo setelah deposit: %.2f%n", saldo);
        }
    }

    public void tambahBunga() 
    {
        saldo += saldo * interestRate;
        System.out.printf("Saldo setelah penambahan bunga: %.2f%n", saldo);
    }
}

// Class utama untuk mengatur program
public class Tugas3 
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        BankAccount akun = new BankAccount("123456", "1234"); // Rekening contoh

        while (true) 
        {
            // Login Loop
            clearScreen();
            boolean isLoggedIn = loginUser(scanner, akun);

            // Menu Utama
            while (isLoggedIn) 
            {
                clearScreen();
                System.out.println("\n=== Menu ATM ===");
                System.out.println("1. Tarik Tunai");
                System.out.println("2. Setor Tunai");
                System.out.println("3. Cek Saldo");
                System.out.println("4. Exit");
                int pilihanMenu = getIntInput(scanner, "Pilih menu: ");

                switch (pilihanMenu) 
                {
                    case 1:
                        // Menu Tarik Tunai
                        clearScreen();
                        isLoggedIn = handleTarikTunai(scanner, akun);
                        break;

                    case 2:
                        // Menu Setor Tunai
                        clearScreen();
                        isLoggedIn = handleSetorTunai(scanner, akun);
                        break;

                    case 3:
                        // Menu Cek Saldo
                        clearScreen();
                        isLoggedIn = handleCekSaldo(scanner, akun);
                        break;

                    case 4:
                        System.out.println("Terima kasih telah menggunakan layanan ATM.");
                        System.exit(0);

                    default:
                        System.out.println("Pilihan anda Invalid");
                }

                if (isLoggedIn) 
                {
                    // Mengarahkan kembali ke login jika user memilih "Y/y"
                    break;
                }
            }
        }
    }

    public static boolean loginUser(Scanner scanner, BankAccount akun) 
    {
        while (true) 
        {
            System.out.print("Masukkan Nomor Kartu ATM: ");
            String nomorKartu = scanner.nextLine();
            String pin = getHiddenInput("Masukkan PIN ATM: ");

            if (akun.login(nomorKartu, pin)) 
            {
                System.out.println("Login Berhasil");
                return true;
            } else 
            {
                clearScreen();
                System.out.println("Login Gagal, coba lagi.");
            }
        }
    }

    // Untuk input PIN tersembunyi
    public static String getHiddenInput(String prompt) 
    {
        Console console = System.console();
        if (console == null) 
        {
            Scanner scanner = new Scanner(System.in);
            System.out.print(prompt);
            return scanner.nextLine();
        } else 
        {
            return new String(console.readPassword(prompt));
        }
    }

    // Metode untuk menangani transaksi tarik tunai
    public static boolean handleTarikTunai(Scanner scanner, BankAccount akun) 
    {
        double jumlah = getDoubleInput(scanner, "Masukkan jumlah yang ingin ditarik: ");
        try 
        {
            akun.tarikTunai(jumlah);
        } catch (Exception e) 
        {
            System.out.println(e.getMessage());
        }

        return ulangLogin(scanner);
    }

    // Metode untuk menangani transaksi setor tunai
    public static boolean handleSetorTunai(Scanner scanner, BankAccount akun) 
    {
        double jumlah = getDoubleInput(scanner, "Masukkan jumlah yang ingin disetor: ");
        try 
        {
            akun.setorTunai(jumlah);
        } catch (Exception e) 
        {
            System.out.println(e.getMessage());
        }

        return ulangLogin(scanner);
    }

    // Metode untuk menangani cek saldo
    public static boolean handleCekSaldo(Scanner scanner, BankAccount akun) 
    {
        System.out.println("1. Cek Saldo Sekarang");
        System.out.println("2. Cek Saldo dengan Bunga 5%");
        int cekPilihan = getIntInput(scanner, "Pilih: ");

        if (cekPilihan == 1) 
        {
            System.out.printf("Saldo saat ini: %.2f%n", akun.getSaldo());
        } else if (cekPilihan == 2) 
        {
            akun.tambahBunga();
        } else 
        {
            System.out.println("Pilihan tidak valid!");
        }

        return ulangLogin(scanner);
    }

    // Metode untuk menanyakan apakah ingin login ulang
    public static boolean ulangLogin(Scanner scanner) 
    {
        System.out.print("Ingin melanjutkan transaksi? (y/n): ");
        char ulang = scanner.next().charAt(0);
        scanner.nextLine();
        if (ulang == 'n' || ulang == 'N')
        {
            System.exit(0);
        }
        return ulang == 'y' || ulang == 'Y';

    }

    // Metode untuk mendapatkan input integer dengan proteksi
    public static int getIntInput(Scanner scanner, String prompt) 
    {
        int input = 0;
        boolean valid = false;
        while (!valid) 
        {
            System.out.print(prompt);
            try 
            {
                input = Integer.parseInt(scanner.nextLine());
                valid = true;
            } catch (NumberFormatException e) 
            {
                System.out.println("Input tidak valid, masukkan angka!");
            }
        }
        return input;
    }

    // Metode untuk mendapatkan input double dengan proteksi
    public static double getDoubleInput(Scanner scanner, String prompt) 
    {
        double input = 0;
        boolean valid = false;
        while (!valid) 
        {
            System.out.print(prompt);
            try 
            {
                input = Double.parseDouble(scanner.nextLine());
                if (input < 0) 
                {
                    System.out.println("Input tidak valid, masukkan angka positif!");
                } else 
                {
                    valid = true;
                }
            } catch (NumberFormatException e) 
            {
                System.out.println("Input tidak valid, masukkan angka!");
            }
        }
        return input;
    }

    public static void clearScreen() 
    {
        System.out.print("\033[H\033[2J");  
        System.out.flush();
    }
}
