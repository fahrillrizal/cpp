#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Transaksi {
    char tanggal[11];
    char jenis[20];
    char keterangan[100];
    double jumlah;
};

struct Keuangan {
    double saldo;
    struct Transaksi transaksi[100];
    int jumlahTransaksi;
};

void catatPendapatan(struct Keuangan* keuangan, double jumlah);
void catatPengeluaran(struct Keuangan* keuangan, double jumlah);
void tampilkanLaporan(const struct Keuangan* keuangan);
void getCurrentDate(char* currentDate);

int main() {
    struct Keuangan keuangan;
    keuangan.saldo = 0.0;
    keuangan.jumlahTransaksi = 0;

    char pilihan;
    double jumlah;

    do {
        printf("Pilih tindakan (P/Pendapatan, K/Pengeluaran, L/Laporan, S/Selesai): ");
        scanf(" %c", &pilihan);

        switch (pilihan) {
            case 'P':
            case 'p':
                printf("Masukkan jumlah pendapatan (dalam jutaan): ");
                scanf("%lf", &jumlah);
                catatPendapatan(&keuangan, jumlah * 1000000);
                break;

            case 'K':
            case 'k':
                printf("Masukkan jumlah pengeluaran: ");
                scanf("%lf", &jumlah);
                catatPengeluaran(&keuangan, jumlah);
                break;

            case 'L':
            case 'l':
                tampilkanLaporan(&keuangan);
                break;

            case 'S':
            case 's':
                printf("Program selesai.\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }

    } while (pilihan != 'S' && pilihan != 's');

    return 0;
}

void catatPendapatan(struct Keuangan* keuangan, double jumlah) {
    keuangan->saldo += jumlah;

    char tanggal[11];
    getCurrentDate(tanggal);

    char keterangan[100];
    printf("Masukkan keterangan pendapatan: ");
    scanf(" %[^\n]", keterangan);

    strcpy(keuangan->transaksi[keuangan->jumlahTransaksi].tanggal, tanggal);
    strcpy(keuangan->transaksi[keuangan->jumlahTransaksi].jenis, "Pendapatan");
    strcpy(keuangan->transaksi[keuangan->jumlahTransaksi].keterangan, keterangan);
    keuangan->transaksi[keuangan->jumlahTransaksi].jumlah = jumlah;

    keuangan->jumlahTransaksi++;
}

void catatPengeluaran(struct Keuangan* keuangan, double jumlah) {
    keuangan->saldo -= jumlah;

    char tanggal[11];
    printf("Masukkan tanggal pengeluaran (dd/mm/yyyy): ");
    scanf("%s", tanggal);

    char keterangan[100];
    printf("Masukkan keterangan pengeluaran: ");
    scanf(" %[^\n]", keterangan);

    strcpy(keuangan->transaksi[keuangan->jumlahTransaksi].tanggal, tanggal);
    strcpy(keuangan->transaksi[keuangan->jumlahTransaksi].jenis, "Pengeluaran");
    strcpy(keuangan->transaksi[keuangan->jumlahTransaksi].keterangan, keterangan);
    keuangan->transaksi[keuangan->jumlahTransaksi].jumlah = jumlah;

    keuangan->jumlahTransaksi++;
}

void tampilkanLaporan(const struct Keuangan* keuangan) {
    printf("=========== LAPORAN KEUANGAN ===========\n");
    printf("Saldo saat ini: %.2f\n", keuangan->saldo);
    printf("---------------------------------------\n");
    printf("%-15s%-15s%-25s%-15s\n", "Tanggal", "Jenis", "Keterangan", "Jumlah");
    printf("---------------------------------------\n");

    for (int i = 0; i < keuangan->jumlahTransaksi; i++) {
        printf("%-15s%-15s%-25s%-15.2f\n",
               keuangan->transaksi[i].tanggal,
               keuangan->transaksi[i].jenis,
               keuangan->transaksi[i].keterangan,
               keuangan->transaksi[i].jumlah);
    }

    printf("=======================================\n");
}

void getCurrentDate(char* currentDate) {
    time_t now = time(NULL);
    struct tm* ltm = localtime(&now);
    sprintf(currentDate, "%02d/%02d/%d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
}
