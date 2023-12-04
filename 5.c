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

void getCurrentDate(char *date) {
    time_t now = time(NULL);
    struct tm *ltm = localtime(&now);
    sprintf(date, "%02d/%02d/%d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
}

void tampilkanLaporan(struct Keuangan *keuangan) {
    printf("=========== LAPORAN KEUANGAN ===========\n");
    printf("Saldo saat ini: %.2lf\n", keuangan->saldo);
    printf("---------------------------------------\n");
    printf("%-15s%-15s%-25s%-15s\n", "Tanggal", "Jenis", "Keterangan", "Jumlah");
    printf("---------------------------------------\n");

    for (int i = 0; i < keuangan->jumlahTransaksi; ++i) {
        struct Transaksi transaksi = keuangan->transaksi[i];
        printf("%-15s%-15s%-25s%.2lf\n", transaksi.tanggal, transaksi.jenis, transaksi.keterangan, transaksi.jumlah);
    }

    printf("=======================================\n");
}

void catatPendapatan(struct Keuangan *keuangan, double jumlah) {
    keuangan->saldo += jumlah;

    char keterangan[100];
    printf("Masukkan keterangan pendapatan: ");
    getchar();
    fgets(keterangan, sizeof(keterangan), stdin);
    keterangan[strcspn(keterangan, "\n")] = '\0';

    char tanggal[11];
    printf("Masukkan tanggal (dd/mm/yyyy): ");
    scanf("%s", tanggal);

    struct Transaksi transaksi;
    strcpy(transaksi.tanggal, tanggal);
    strcpy(transaksi.jenis, "Pendapatan");
    strcpy(transaksi.keterangan, keterangan);
    transaksi.jumlah = jumlah;

    keuangan->transaksi[keuangan->jumlahTransaksi++] = transaksi;
}

void catatPengeluaran(struct Keuangan *keuangan, double jumlah) {
    keuangan->saldo -= jumlah;

    char keterangan[100];
    printf("Masukkan keterangan pengeluaran: ");
    getchar();
    fgets(keterangan, sizeof(keterangan), stdin);
    keterangan[strcspn(keterangan, "\n")] = '\0';

    char tanggal[11];
    printf("Masukkan tanggal (dd/mm/yyyy): ");
    scanf("%s", tanggal);

    struct Transaksi transaksi;
    strcpy(transaksi.tanggal, tanggal);
    strcpy(transaksi.jenis, "Pengeluaran");
    strcpy(transaksi.keterangan, keterangan);
    transaksi.jumlah = jumlah;

    keuangan->transaksi[keuangan->jumlahTransaksi++] = transaksi;
}

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
                catatPendapatan(&keuangan, jumlah);
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
