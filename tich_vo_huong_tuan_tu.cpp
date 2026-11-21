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
    double tichVoHuong = 0.0;

    for (long long i = 0; i < kichThuoc; ++i) {
        tichVoHuong += vectorA[i] * vectorB[i];
    }

    if (!std::isfinite(tichVoHuong)) {
        throw std::overflow_error("Loi tinh toan: Inf hoac NaN.");
    }

    return tichVoHuong;
}
