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
};

void bacaSaldoDariFile(struct Keuangan *keuangan) {
    FILE *file = fopen("transaksi.txt", "r");
    if (file != NULL) {
        struct Transaksi transaksi;
        while (fscanf(file, "%s %s %[^\n] %lf", transaksi.tanggal, transaksi.jenis, transaksi.keterangan, &transaksi.jumlah) == 4) {
            if (strcmp(transaksi.jenis, "Pendapatan") == 0 || strcmp(transaksi.jenis, "p") == 0) {
                keuangan->saldo += transaksi.jumlah;
            } else if (strcmp(transaksi.jenis, "Pengeluaran") == 0 || strcmp(transaksi.jenis, "k") == 0) {
                keuangan->saldo -= transaksi.jumlah;
            }
        }
        fclose(file);
    } else {
        fprintf(stderr, "Gagal membuka file transaksi.txt\n");
        exit(EXIT_FAILURE);
    }
}

void simpanSaldoKeFile(struct Keuangan *keuangan) {
    FILE *file = fopen("transaksi.txt", "a");
    if (file != NULL) {
        time_t now = time(NULL);
        struct tm *ltm = localtime(&now);
        fprintf(file, "%02d/%02d/%d Saldo %.2lf\n", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year, keuangan->saldo);
        fclose(file);
    } else {
        fprintf(stderr, "Gagal membuka file transaksi.txt\n");
        exit(EXIT_FAILURE);
    }
}

void simpanTransaksi(const char *tanggal, const char *jenis, const char *keterangan, double jumlah) {
    struct Transaksi transaksi;
    strcpy(transaksi.tanggal, tanggal);
    strcpy(transaksi.jenis, jenis);
    strcpy(transaksi.keterangan, keterangan);
    transaksi.jumlah = jumlah;

    FILE *file = fopen("transaksi.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s %s %.2lf\n", transaksi.tanggal, transaksi.jenis, transaksi.keterangan, transaksi.jumlah);
        fclose(file);
    } else {
        fprintf(stderr, "Gagal membuka file transaksi.txt\n");
        exit(EXIT_FAILURE);
    }
}

void tampilkanLaporan(struct Keuangan *keuangan) {
    FILE *file = fopen("transaksi.txt", "r");
    if (file != NULL) {
        printf("=========== LAPORAN KEUANGAN ===========\n");
        printf("Saldo saat ini: %.2lf\n", keuangan->saldo);
        printf("---------------------------------------\n");
        printf("%-15s%-15s%-25s%-15s\n", "Tanggal", "Jenis", "Keterangan", "Jumlah");
        printf("---------------------------------------\n");

        struct Transaksi transaksi;

        while (fscanf(file, "%s %s %[^\n] %lf", transaksi.tanggal, transaksi.jenis, transaksi.keterangan, &transaksi.jumlah) == 4) {
            printf("%-15s%-15s%-25s%.2lf\n", transaksi.tanggal, transaksi.jenis, transaksi.keterangan, transaksi.jumlah);
        }

        printf("=======================================\n");
        fclose(file);
    } else {
        fprintf(stderr, "Gagal membuka file transaksi.txt\n");
        exit(EXIT_FAILURE);
    }
}

char *getCurrentDate() {
    time_t now = time(NULL);
    struct tm *ltm = localtime(&now);

    char *date = (char *)malloc(11 * sizeof(char));
    sprintf(date, "%02d/%02d/%d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);

    return date;
}

void catatPendapatan(struct Keuangan *keuangan) {
    double jumlah;
    keuangan->saldo += jumlah;

    char *tanggal = getCurrentDate();

    char keterangan[100];
    printf("Masukkan keterangan pendapatan: ");
    getchar(); // Consume newline character left in the buffer
    fgets(keterangan, sizeof(keterangan), stdin);
    keterangan[strcspn(keterangan, "\n")] = '\0'; // Remove trailing newline character

    simpanTransaksi(tanggal, "Pendapatan", keterangan, jumlah);
    free(tanggal);
}

void catatPengeluaran(struct Keuangan *keuangan) {
    double jumlah;
    keuangan->saldo -= jumlah;

    char tanggal[11];
    printf("Masukkan tanggal pengeluaran (dd/mm/yyyy): ");
    scanf("%s", tanggal);

    char keterangan[100];
    printf("Masukkan keterangan pengeluaran: ");
    getchar();
    fgets(keterangan, sizeof(keterangan), stdin);
    keterangan[strcspn(keterangan, "\n")] = '\0';

    simpanTransaksi(tanggal, "Pengeluaran", keterangan, jumlah);
}

int main() {
    struct Keuangan keuangan;
    keuangan.saldo = 0.0;

    bacaSaldoDariFile(&keuangan);

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
                catatPendapatan(&keuangan);
                break;

            case 'K':
            case 'k':
                printf("Masukkan jumlah pengeluaran: ");
                scanf("%lf", &jumlah);
                catatPengeluaran(&keuangan);
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

    simpanSaldoKeFile(&keuangan);

    return 0;
}
