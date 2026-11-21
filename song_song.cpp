#include <iostream>
#include <vector>
#include <omp.h>
#include <iomanip>
using namespace std;
const int maxLuong = omp_get_max_threads();

// Hàm tính tích vô hướng song song bằng OpenMP
double tinhTichVoHuongSongSong(const vector<double>& A, const vector<double>& B, int soLuong) {
    long long m = A.size(), n = B.size(), i;

    if (m != n) 
        throw invalid_argument("Kich thuoc cua hai vector khong bang nhau.");
    if (m == 0 || n == 0) 
        throw invalid_argument("Vector rong.");
    if (soLuong <= 0) 
        throw invalid_argument("So luong luong phai lon hon 0.");
    if (soLuong > maxLuong) 
        throw invalid_argument("So luong luong (" + to_string(soLuong) + ") vuot qua so luong toi da cua he thong (" + to_string(maxLuong) + ").");

    double tongTich = 0.0;
    omp_set_num_threads(soLuong);

    // Chia các luồng và cộng reduction tránh race conditition
    #pragma omp parallel for reduction(+:tongTich)
    for (i = 0; i < n; ++i)
        tongTich += A[i] * B[i];

    return tongTich;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    try {
        if (!freopen("input.txt", "r", stdin))
            throw runtime_error("Khong mo duoc file input.txt!");
        if (!freopen("output.txt", "w", stdout))
            throw runtime_error("Khong tao duoc file output.txt!");

        long long m = 0, n = 0;
        if (!(cin >> m >> n) || m <= 0 || n <= 0)
            throw invalid_argument("Kich thuoc vecto khong hop le!");

        vector<double> A(m), B(n);
        for (long long i = 0; i < m; ++i)
            if (!(cin >> A[i]))
                throw invalid_argument("Khong doc duoc phan tu thu " + to_string(i + 1) + " cua vector A!");

        for (long long i = 0; i < n; ++i)
            if (!(cin >> B[i]))
                throw invalid_argument("Khong doc duoc phan tu thu " + to_string(i + 1) + " cua vector B!");

        cout << fixed << setprecision(4);

        for (int soLuong : {0, 1, 2, 4, 8, 15}) {
            try {
                double batDau = omp_get_wtime();
                double ketQua = tinhTichVoHuongSongSong(A, B, soLuong);
                double thoiGianTinh = (omp_get_wtime() - batDau) * 1000.0;

                cout << "So luong: " << soLuong
                     << " | Ket qua: " << ketQua
                     << " | Thoi gian: " << thoiGianTinh << " ms\n";
            } catch (const exception& e) {
                cout << "So luong: " << soLuong << " | Loi: " << e.what() << "\n";
            }
        }
    } catch (const exception& e) {
        cout << "Loi du lieu/he thong: " << e.what() << "\n";
        return 1;
    }

    return 0;
}