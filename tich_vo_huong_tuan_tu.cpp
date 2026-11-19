#include <cmath>
#include <vector>
#include <stdexcept>

double tinhTichVoHuongTuanTu(const std::vector<double>& vectorA, const std::vector<double>& vectorB) {
    if (vectorA.empty() || vectorB.empty()) {
        throw std::invalid_argument("Loi dau vao: Vector rong.");
    }
    if (vectorA.size() != vectorB.size()) {
        throw std::invalid_argument("Loi dau vao: Kich thuoc hai vector khong bang nhau.");
    }

    long long kichThuoc = static_cast<long long>(vectorA.size());
    double tongTich = 0.0;

    for (long long i = 0; i < kichThuoc; ++i) {
        tongTich += vectorA[i] * vectorB[i];
    }

    if (!std::isfinite(tongTich)) {
        throw std::overflow_error("Loi tinh toan: Ket qua tich vo huong bi tran so thuc (Inf hoac NaN).");
    }

    return tongTich;
}