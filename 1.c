#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 50
#define MAX_TEAM_MEMBERS 10

struct Task {
    char nama[50];
    char tenggat_waktu[20];
    char status[20];
};

struct TeamMember {
    char nama[50];
};

struct Project {
    char nama[50];
    struct Task tasks[MAX_TASKS];
    struct TeamMember team[MAX_TEAM_MEMBERS];
    int jumlah_tugas;
    int jumlah_anggota_tim;
    char status[20];
};

void tambahTugas(struct Project *proyek, const char *nama, const char *tenggat_waktu) {
    if (proyek->jumlah_tugas < MAX_TASKS) {
        struct Task *tugas = &proyek->tasks[proyek->jumlah_tugas];
        strcpy(tugas->nama, nama);
        strcpy(tugas->tenggat_waktu, tenggat_waktu);
        strcpy(tugas->status, "Belum selesai");

        proyek->jumlah_tugas++;
        printf("Tugas '%s' ditambahkan.\n", nama);
    } else {
        printf("Maksimum jumlah tugas telah dicapai.\n");
    }
}

void tambahAnggotaTim(struct Project *proyek, const char *nama) {
    if (proyek->jumlah_anggota_tim < MAX_TEAM_MEMBERS) {
        struct TeamMember *anggota_tim = &proyek->team[proyek->jumlah_anggota_tim];
        strcpy(anggota_tim->nama, nama);

        proyek->jumlah_anggota_tim++;
        printf("Anggota tim '%s' ditambahkan.\n", nama);
    } else {
        printf("Maksimum jumlah anggota tim telah dicapai.\n");
    }
}

void tampilkanProyek(struct Project *proyek) {
    printf("========== PROYEK ==========\n");
    printf("Nama Proyek: %s\n", proyek->nama);
    printf("Status Proyek: %s\n", proyek->status);
    printf("\nTugas:\n");
    for (int i = 0; i < proyek->jumlah_tugas; i++) {
        printf("%d. %s (Tenggat Waktu: %s, Status: %s)\n", i + 1, proyek->tasks[i].nama, proyek->tasks[i].tenggat_waktu, proyek->tasks[i].status);
    }
    printf("\nAnggota Tim:\n");
    for (int i = 0; i < proyek->jumlah_anggota_tim; i++) {
        printf("%d. %s\n", i + 1, proyek->team[i].nama);
    }
    printf("=============================\n");
}

int main() {
    struct Project proyek;
    proyek.jumlah_tugas = 0;
    proyek.jumlah_anggota_tim = 0;
    strcpy(proyek.status, "Belum selesai");

    printf("Masukkan nama proyek: ");
    fgets(proyek.nama, sizeof(proyek.nama), stdin);
    proyek.nama[strcspn(proyek.nama, "\n")] = '\0';  // Menghapus karakter newline dari nama proyek

    char pilihan;
    char nama[50];
    char tenggat_waktu[20];

    do {
        printf("\nPilih tindakan (T/Tambah Tugas, A/Tambah Anggota Tim, L/Lihat Proyek, S/Selesai): ");
        scanf(" %c", &pilihan);

        switch (pilihan) {
            case 'T':
            case 't':
                printf("Masukkan nama tugas: ");
                scanf(" %[^\n]s", nama);
                printf("Masukkan tenggat waktu tugas (format: DD/MM/YYYY): ");
                scanf(" %[^\n]s", tenggat_waktu);
                tambahTugas(&proyek, nama, tenggat_waktu);
                break;

            case 'A':
            case 'a':
                printf("Masukkan nama anggota tim: ");
                scanf(" %[^\n]s", nama);
                tambahAnggotaTim(&proyek, nama);
                break;

            case 'L':
            case 'l':
                tampilkanProyek(&proyek);
                break;

            case 'S':
            case 's':
                printf("Program selesai.\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }

        // Membersihkan buffer input
        while (getchar() != '\n');

    } while (pilihan != 'S' && pilihan != 's');

    return 0;
}
