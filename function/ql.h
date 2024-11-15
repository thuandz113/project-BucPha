#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

// Cấu trúc để lưu thông tin sản phẩm
struct SanPham {
    string ten;
    int soLuong;
    double gia;
    
    double thanhTien() const {
        return soLuong * gia;
    }
};

// Hàm để in tiêu đề hóa đơn với ngăn cách
void inTieuDeHoaDon() {
    cout << "================================================================================\n";
    cout << "|                              HOA DON BAN HANG                                 |\n";
    cout << "================================================================================\n";
    cout << "| " << left << setw(30) << "Ten San Pham" 
         << "| " << right << setw(10) << "So Luong" 
         << " | " << right << setw(15) << "Gia (VND)" 
         << " | " << right << setw(20) << "Thanh Tien (VND)" << " |\n";
    cout << "--------------------------------------------------------------------------------\n";
}



int main() {
    // Danh sách sản phẩm (có thể được nhập từ người dùng hoặc từ nguồn dữ liệu khác)
    vector<SanPham> danhSach = {
        {"Nuoc co ga", 2, 15000},
        {"Nuoc ep trai cay", 3, 20000},
        {"Sua tuoi", 1, 25000},
        {"Quan ao", 5, 50000},
        {"Phu kien", 4, 30000},
        {"Giay dep", 2, 75000}
    };
    
    double tongTien = 0.0;
    
    // In tiêu đề hóa đơn
    inTieuDeHoaDon();
    
    // In từng sản phẩm
    for(const auto& sp : danhSach) {
        inSanPham(sp);
        tongTien += sp.thanhTien();
    }
    
    // In tổng tiền
    inTongTien(tongTien);
    
    return 0;
}
