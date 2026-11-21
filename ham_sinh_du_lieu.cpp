#include <stdexcept>
#include <random>
#include <cstddef>

void sinhDuLieuNgauNhien(
    long long kichThuoc,
    double giaTriNhoNhat,
    double giaTriLonNhat,
    unsigned int IDvector,
    std::vector<double>& vectorKetQua
) {
    if (kichThuoc <= 0) {
        throw std::invalid_argument("Loi sinh du lieu: Kich thuoc vector phai lon hon 0.");
    }
    if (giaTriNhoNhat > giaTriLonNhat) {
        throw std::invalid_argument("Loi sinh du lieu: Gia tri nho nhat khong duoc lon hon gia tri lon nhat.");
    }

    vectorKetQua.resize(static_cast<std::size_t>(kichThuoc));

    //Dung IDvector de co dinh vector
    std::mt19937_64 boSinhNgauNhien(IDvector);
    std::uniform_real_distribution<double> phanPhoiDeu(giaTriNhoNhat, giaTriLonNhat);

    for (long long i = 0; i < kichThuoc; ++i) {
        vectorKetQua[i] = phanPhoiDeu(boSinhNgauNhien);
    }
}

//Vi du ham main
/*
int main() {
    long long kichThuoc = 10000000;
    double giaTriNhoNhat = -10.0;
    double giaTriLonNhat = 10.0;
    unsigned int seedA = 1;
    unsigned int seedB = 2;

    std::vector<double> vectorA;
    std::vector<double> vectorB;
    sinhDuLieuNgauNhien(kichThuoc, minVal, maxVal, seedA, vectorA);
    sinhDuLieuNgauNhien(kichThuoc, minVal, maxVal, seedB, vectorB);
}
*/