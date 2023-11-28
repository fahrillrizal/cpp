#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

struct Transaksi {
    string tanggal;
    string jenis;
    string keterangan;
    double jumlah;
};

class Keuangan {
private:
    double saldo;

public:
    Keuangan() : saldo(0.0) {}

    void catatPendapatan(double jumlah) {
        saldo += jumlah;

        string tanggal = getCurrentDate();

        string keterangan;
        cout << "Masukkan keterangan pendapatan: ";
        cin.ignore();
        getline(cin, keterangan);

        simpanTransaksi(tanggal, "Pendapatan", keterangan, jumlah);
    }

    void catatPengeluaran(double jumlah) {
        saldo -= jumlah;

        string tanggal;
        cout << "Masukkan tanggal pengeluaran (dd/mm/yyyy): ";
        cin >> tanggal;

        string keterangan;
        cout << "Masukkan keterangan pengeluaran: ";
        cin.ignore();
        getline(cin, keterangan);

        simpanTransaksi(tanggal, "Pengeluaran", keterangan, jumlah);
    }

    void simpanTransaksi(const string& tanggal, const string& jenis, const string& keterangan, double jumlah) {
        Transaksi transaksi;
        transaksi.tanggal = tanggal;
        transaksi.jenis = jenis;
        transaksi.keterangan = keterangan;
        transaksi.jumlah = jumlah;

        ofstream file("transaksi.txt", ios::app);
        if (file.is_open()) {
            file << transaksi.tanggal << " " << transaksi.jenis << " " << transaksi.keterangan << " " << fixed << setprecision(2) << transaksi.jumlah << endl;
            file.close();
        } else {
            cerr << "Gagal membuka file transaksi.txt" << endl;
        }
    }

    void tampilkanLaporan() {
        ifstream file("transaksi.txt");
        if (file.is_open()) {
            cout << "=========== LAPORAN KEUANGAN ===========" << endl;
            cout << "Saldo saat ini: " << fixed << setprecision(2) << saldo << endl;
            cout << "---------------------------------------" << endl;
            cout << setw(15) << "Tanggal" << setw(15) << "Jenis" << setw(25) << "Keterangan" << setw(15) << "Jumlah" << endl;
            cout << "---------------------------------------" << endl;

            Transaksi transaksi;

            while (file >> transaksi.tanggal >> transaksi.jenis >> transaksi.keterangan >> transaksi.jumlah) {
                cout << setw(15) << transaksi.tanggal << setw(15) << transaksi.jenis << setw(25) << transaksi.keterangan << setw(15) << fixed << setprecision(2) << transaksi.jumlah << endl;
            }

            cout << "=======================================" << endl;
            file.close();
        } else {
            cerr << "Gagal membuka file transaksi.txt" << endl;
        }
    }

    string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        return to_string(ltm->tm_mday) + '/' + to_string(1 + ltm->tm_mon) + '/' + to_string(1900 + ltm->tm_year);
    }
};

int main() {
    Keuangan keuangan;

    char pilihan;
    double jumlah;

    do {
        cout << "Pilih tindakan (P/Pendapatan, K/Pengeluaran, L/Laporan, S/Selesai): ";
        cin >> pilihan;

        switch (pilihan) {
            case 'P':
            case 'p':
                cout << "Masukkan jumlah pendapatan (dalam jutaan): ";
                cin >> jumlah;
                keuangan.catatPendapatan(jumlah * 1000000);
                break;

            case 'K':
            case 'k':
                cout << "Masukkan jumlah pengeluaran: ";
                cin >> jumlah;
                keuangan.catatPengeluaran(jumlah);
                break;

            case 'L':
            case 'l':
                keuangan.tampilkanLaporan();
                break;

            case 'S':
            case 's':
                cout << "Program selesai." << endl;
                break;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

    } while (pilihan != 'S' && pilihan != 's');

    return 0;
}
