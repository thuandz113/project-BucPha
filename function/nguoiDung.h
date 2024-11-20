#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <conio.h>

#include "doiTuong.h"
#include "ham.h"
//============================Account==========================//
using namespace std;
class SanPham {
protected:
    string ten;         // Tên sản phẩm
    int soLuong;        // Số lượng sản phẩm
    int gia;         // Giá sản phẩm

public:
    virtual string getLoai() const = 0; // Trả về loại sản phẩm
    virtual void nhapThongTin() = 0; // Nhập thông tin sản phẩm
    virtual void luuThongTinVaoFile(ofstream& file) = 0; // Lưu thông tin vào file

    string getTen() const { return ten; } // Lấy tên sản phẩm
    int getSoLuong() const { return soLuong; } // Lấy số lượng
    void setSoLuong(int sl) { soLuong = sl; } // Cập nhật số lượng
    int getGia() const { return gia; } // Lấy giá sản phẩm

    virtual ~SanPham() {} // Destructor ảo
    void setGia(int giaSanPham) {
        gia = giaSanPham;
    }
    void setTen(const string& tenSanPham) {
        ten = tenSanPham;
    }
};

class ThucPham : public SanPham {
private:
    string hanSuDung;

public:
    string getLoai() const override { return "ThucPham"; }

    void nhapThongTin() override {
        cout << "Nhap ten thuc pham: ";
        getline(cin,ten);

    do {
        cout << "Nhap gia: ";
        cinInt >> gia;
        if (gia <= 0) {
            setColor(12);  // Đổi màu sang đỏ
            cout << "Gia phai lon hon 0. Vui long nhap lai.\n";
            setColor(7);   // Quay lại màu mặc định
        }
    } while (gia <= 0);  // Lặp lại cho đến khi giá hợp lệ

    // Kiểm tra số lượng nhập vào phải lớn hơn 0
    do {
        cout << "Nhap so luong: ";
        cinInt >> soLuong;
        if (soLuong <= 0) {
            setColor(12);  // Đổi màu sang đỏ
            cout << "So luong phai lon hon 0. Vui long nhap lai.\n";
            setColor(7);   // Quay lại màu mặc định
        }
    } while (soLuong <= 0);  // Lặp lại cho đến khi số lượng hợp lệ
    }

    void luuThongTinVaoFile(ofstream& file) override {
        file << "ThucPham," << ten << "," << gia << "," << soLuong << endl;
    }

    void khoiTaoTuFile(const string& ten, double gia, int soLuong) {
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;
    }
};

class DoUong : public SanPham {
private:
    bool coCon;

public:
    string getLoai() const override { return "DoUong"; }

    void nhapThongTin() override {
        cout << "Nhap ten do uong: ";
        getline(cin,ten);
        do {
        cout << "Nhap gia: ";
        cinInt >> gia;
        if (gia <= 0) {
            setColor(12);  // Đổi màu sang đỏ
            cout << "Gia phai lon hon 0. Vui long nhap lai.\n";
            setColor(7);   // Quay lại màu mặc định
        }
        } while (gia <= 0);  // Lặp lại cho đến khi giá hợp lệ

        // Kiểm tra số lượng nhập vào phải lớn hơn 0
        do {
            cout << "Nhap so luong: ";
            cinInt >> soLuong;
            if (soLuong <= 0) {
                setColor(12);  // Đổi màu sang đỏ
                cout << "So luong phai lon hon 0. Vui long nhap lai.\n";
                setColor(7);   // Quay lại màu mặc định
            }
        } while (soLuong <= 0);  // Lặp lại cho đến khi số lượng hợp lệ

    }

    void luuThongTinVaoFile(ofstream& file) override {
        file << "DoUong," << ten << "," << gia << "," << soLuong << endl;
    }

    void khoiTaoTuFile(const string& ten, double gia, int soLuong) {
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;

    }
};

class ThoiTrang : public SanPham {
private:
    string size;

public:
    string getLoai() const override { return "ThoiTrang"; }

    void nhapThongTin() override {
        cout << "Nhap ten thoi trang: ";
        getline(cin,ten);
        do {
        cout << "Nhap gia: ";
        cinInt >> gia;
        if (gia <= 0) {
            setColor(12);  // Đổi màu sang đỏ
            cout << "Gia phai lon hon 0. Vui long nhap lai.\n";
            setColor(7);   // Quay lại màu mặc định
        }
        } while (gia <= 0);  // Lặp lại cho đến khi giá hợp lệ

        // Kiểm tra số lượng nhập vào phải lớn hơn 0
        do {
            cout << "Nhap so luong: ";
            cinInt >> soLuong;
            if (soLuong <= 0) {
                setColor(12);  // Đổi màu sang đỏ
                cout << "So luong phai lon hon 0. Vui long nhap lai.\n";
                setColor(7);   // Quay lại màu mặc định
            }
        } while (soLuong <= 0);  // Lặp lại cho đến khi số lượng hợp lệ

    }

    void luuThongTinVaoFile(ofstream& file) override {
        file << "ThoiTrang," << ten << "," << gia << "," << soLuong << endl;
    }

    void khoiTaoTuFile(const string& ten, double gia, int soLuong) {
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;

    }
};

class DoGiaDung : public SanPham {
private:
    string chatLieu;

public:
    string getLoai() const override { return "DoGiaDung"; }

    void nhapThongTin() override {
        cout << "Nhap ten do gia dung: ";
        getline(cin,ten);
        do {
        cout << "Nhap gia: ";
        cinInt >> gia;
        if (gia <= 0) {
            setColor(12);  // Đổi màu sang đỏ
            cout << "Gia phai lon hon 0. Vui long nhap lai.\n";
            setColor(7);   // Quay lại màu mặc định
        }
        } while (gia <= 0);  // Lặp lại cho đến khi giá hợp lệ

        // Kiểm tra số lượng nhập vào phải lớn hơn 0
        do {
            cout << "Nhap so luong: ";
            cinInt >> soLuong;
            if (soLuong <= 0) {
                setColor(12);  // Đổi màu sang đỏ
                cout << "So luong phai lon hon 0. Vui long nhap lai.\n";
                setColor(7);   // Quay lại màu mặc định
            }
        } while (soLuong <= 0);  // Lặp lại cho đến khi số lượng hợp lệ

    }

    void luuThongTinVaoFile(ofstream& file) override {
        file << "DoGiaDung," << ten << "," << gia << "," << soLuong << endl;
    }

    void khoiTaoTuFile(const string& ten, double gia, int soLuong) {
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;
    }
};

class DoDienTu : public SanPham {
private:
    string hangSX;

public:
    string getLoai() const override { return "DoDienTu"; }

    void nhapThongTin() override {
        cout << "Nhap ten do dien tu: ";
        
        getline(cin,ten);
        do {
        cout << "Nhap gia: ";
        cinInt >> gia;
        if (gia <= 0) {
            setColor(12);  // Đổi màu sang đỏ
            cout << "Gia phai lon hon 0. Vui long nhap lai.\n";
            setColor(7);   // Quay lại màu mặc định
        }
        } while (gia <= 0);  // Lặp lại cho đến khi giá hợp lệ

        // Kiểm tra số lượng nhập vào phải lớn hơn 0
        do {
            cout << "Nhap so luong: ";
            cinInt >> soLuong;
            if (soLuong <= 0) {
                setColor(12);  // Đổi màu sang đỏ
                cout << "So luong phai lon hon 0. Vui long nhap lai.\n";
                setColor(7);   // Quay lại màu mặc định
            }
        } while (soLuong <= 0);  // Lặp lại cho đến khi số lượng hợp lệ

    }

    void luuThongTinVaoFile(ofstream& file) override {
        file << "DoDienTu," << ten << "," << gia << "," << soLuong << endl;
    }

    void khoiTaoTuFile(const string& ten, double gia, int soLuong) {
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;
    }
};
class QuanLyChucNang {
private:
    vector<SanPham*> danhSachSanPham;
    
public:

    enum LoaiSanPham {
        THUC_PHAM,//thuc pham
        DO_UONG,
        THOI_TRANG,
        DO_GIA_DUNG,
        DO_DIEN_TU
    };

 
    void chonQuayKhac(UserAccount &user) {
    int luaChonLoai = 1;  // Lựa chọn mặc định
    bool keyPress = false;

    while (true) {
        system("cls");

        // Hiển thị menu với màu sắc
        cout << "=============================\n";
        for (int i = 1; i <= 6; ++i) {
            // Nếu đang ở mục chọn hiện tại, đổi màu
            if (i == luaChonLoai) {

                cout << "|";
                setColor(14);
                cout <<" * ";
            } else {
                setColor(7); // Màu trắng cho các lựa chọn khác
                cout << "|   ";
            }

            // In tên lựa chọn
            switch (i) {
                case 1: cout << "Thuc pham               ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 2: cout << "Do uong                 ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 3: cout << "Thoi trang              ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 4: cout << "Do gia dung             ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 5: cout << "Do dien tu              ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 6: cout << "Thoat                   ";
                        setColor(7);
                        cout<<"|";
                        break;
            }

            cout << endl;
        }
        setColor(7);
        cout << "=============================\n";
        cout << "Chon loai san pham muon mua (Sử dụng mũi tên lên/xuống để di chuyển và Enter để chọn):";

        // Đọc phím người dùng
        int key = _getch();

        // Xử lý mũi tên
        if (key == 224) {  // Phím mũi tên
            key = _getch(); // Đọc mã phím mũi tên
            if (key == 72 && luaChonLoai > 1) {  // Mũi tên lên
                luaChonLoai--;
            } else if (key == 80 && luaChonLoai < 6) {  // Mũi tên xuống
                luaChonLoai++;
            }
        } else if (key == 13) {  // Enter
            break;  // Chọn lựa chọn hiện tại
        }
    }

    // Sau khi chọn xong, chuyển đến mục tương ứng
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");

    switch (luaChonLoai) {
        case 1: muaSanPham(THUC_PHAM, user); break;
        case 2: muaSanPham(DO_UONG, user); break;
        case 3: muaSanPham(THOI_TRANG, user); break;
        case 4: muaSanPham(DO_GIA_DUNG, user); break;
        case 5: muaSanPham(DO_DIEN_TU, user); break;
        case 6: break;  // Thoát
    }
    }


void thanhToan(std::vector<int>& luaChonSanPham, std::vector<int>& soLuongMua, UserAccount &user) {
    double tongTien = 0.0;

    // Tiêu đề hóa đơn
        setColor(7); // Màu vàng cho đường viền tiêu đề
    cout << "================================================================================\n";
     // Màu xanh dương nhạt cho tiêu đề
    cout << "|                                   ";
    setColor(11);
    cout<<"HOA DON"                                    ;
    setColor(7);
    cout<<"                                    |\n";
    setColor(7); // Màu vàng cho đường viền tiêu đề
    cout << "================================================================================\n";
    setColor(7); // Màu trắng trở lại cho nội dung bên dưới

    // In thông tin hóa đơn
    setColor(15); // Màu trắng cho phần thông tin sản phẩm
    cout << "| " << left << setw(30) << "Ten San Pham"                                       
        << "| " << setw(10) << "So Luong" 
        << "| " << setw(15) << "Gia (VND)" 
        << "| " << setw(15) << "Thanh Tien (VND)" << "|\n";
    cout << "================================================================================\n";
    setColor(7); // Trở lại màu trắng mặc định

    // Hiển thị danh sách sản phẩm đã mua
    for (size_t i = 0; i < luaChonSanPham.size(); ++i) {
        int index = luaChonSanPham[i];
        double giaSanPham = danhSachSanPham[index]->getGia();
        int soLuong = soLuongMua[i];
        double thanhTien = giaSanPham * soLuong;
        tongTien += thanhTien;

        // In ra từng sản phẩm
        cout << "| " << left << setw(30) << danhSachSanPham[index]->getTen() 
            << "| " << setw(10) << soLuong 
            << "| " << setw(15) << giaSanPham 
            << "| " << setw(15) << thanhTien << " |\n";
    }

    cout << "================================================================================\n";
    setColor(7); // Trở lại màu trắng mặc định

    // In tổng tiền
    setColor(10); // Màu xanh lá cho tổng tiền
    cout << "Tong so tien can thanh toan: " << tongTien << " VND" << endl;
    setColor(7);

    char luaChon;
    cout << "Ban co muon thanh toan khong? (Y(y)/Phim khac): ";
    cin >> luaChon;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (luaChon == 'y' || luaChon == 'Y') {
        if (user.getCredits() >= tongTien) {
            string fileName = "database/history/" + user.getUsername() + ".txt";
            ofstream fileHoaDon(fileName, ios::app);
            if (!fileHoaDon.is_open()) {
                setColor(12); // Màu đỏ cho thông báo lỗi
                cout << "Khong the mo file hoa don!" << endl;
                setColor(7);
                return;
            }
            for (size_t i = 0; i < luaChonSanPham.size(); ++i) {
                int index = luaChonSanPham[i];
                double giaSanPham = danhSachSanPham[index]->getGia();
                int soLuong = soLuongMua[i];
                double thanhTien = giaSanPham * soLuong;
                fileHoaDon << danhSachSanPham[index]->getTen() << " " << giaSanPham << " " << soLuong << " " << thanhTien << " " << getCurrentDate() << endl;
            }
            fileHoaDon.close();

            setColor(10); // Màu xanh lá cho thông báo thành công
            cout << "Thanh toan thanh cong! Cam on ban!" << endl;
            setColor(7);

            user.accountDeposit(-tongTien);
            luuSanPhamVaoFile("database/product.txt"); // Cập nhật file sản phẩm
            cart.clear(); // Xóa giỏ hàng
            quantities.clear(); // Xóa số lượng
        } else {
            double soTienThieu = tongTien - user.getCredits(); // Tính số tiền thiếu
            setColor(12); // Màu đỏ cho thông báo thiếu tiền
            cout << "Ban khong du " << tongTien << "$ de thanh toan, tong tien cua ban: " << user.getCredits() << "$." << endl;
            setColor(7);

            // Hỏi người dùng có muốn nạp tiền đủ để thanh toán không
            char luaChonNap;
            cout << "Ban co muon nap them " << soTienThieu << "$ de thanh toan khong? (Y(y)/Phim khac): ";
            cin >> luaChonNap;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
            if (luaChonNap == 'y' || luaChonNap == 'Y') {
                double credits;
                

                user.accountDeposit(soTienThieu); // Nạp tiền vào tài khoản người dùng
                setColor(10); // Màu xanh lá cho thông báo thành công
                cout << "Nap thanh cong: " << soTienThieu << "$.\n";
                setColor(7);

                // Sau khi nạp tiền, tiếp tục thanh toán lại
                if (user.getCredits() >= tongTien) {
                    // Tiến hành thanh toán lại
                    this_thread::sleep_for(chrono::milliseconds(500));
                    system("cls");
                    thanhToan(luaChonSanPham, soLuongMua, user);
                }
            } else {
                cout << "Khong nap tien. Huy thanh toan!\n";
                cart.clear(); // Xóa giỏ hàng
                quantities.clear(); // Xóa số lượng
            }
        }
    } else {
        setColor(14); // Màu vàng cho thông báo hủy
        cout << "Huy thanh toan!" << endl;
        setColor(7);
        cart.clear(); // Xóa giỏ hàng
        quantities.clear(); // Xóa số lượng
    }
}


void nhapHang() {
    docSanPhamTuFile("database/product.txt");
    // Đọc danh sách sản phẩm từ file trước
    int luaChonLoai = 1;  // Lựa chọn mặc định
    bool keyPress = false;

    while (true) {
        system("cls");

        // Hiển thị menu với màu sắc
        cout << "=============================\n";
        for (int i = 1; i <= 6; ++i) {
            // Nếu đang ở mục chọn hiện tại, đổi màu
            if (i == luaChonLoai) {

                cout << "|";
                setColor(14);
                cout <<" * ";
            } else {
                setColor(7); // Màu trắng cho các lựa chọn khác
                cout << "|   ";
            }

            // In tên lựa chọn
            switch (i) {
                case 1: cout << "Thuc pham               ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 2: cout << "Do uong                 ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 3: cout << "Thoi trang              ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 4: cout << "Do gia dung             ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 5: cout << "Do dien tu              ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 6: cout << "Thoat                   ";
                        setColor(7);
                        cout<<"|";
                        break;
            }

            cout << endl;
        }
        setColor(7);
        cout << "=============================\n";
        cout << "Chon loai san pham muon nhap (Sử dụng mũi tên lên/xuống để di chuyển và Enter để chọn):";

        // Đọc phím người dùng
        int key = _getch();

        // Xử lý mũi tên
        if (key == 224) {  // Phím mũi tên
            key = _getch(); // Đọc mã phím mũi tên
            if (key == 72 && luaChonLoai > 1) {  // Mũi tên lên
                luaChonLoai--;
            } else if (key == 80 && luaChonLoai < 6) {  // Mũi tên xuống
                luaChonLoai++;
            }
        } else if (key == 13) {  // Enter
            break;  // Chọn lựa chọn hiện tại
        }
    }

    // Sau khi chọn xong, chuyển đến mục tương ứng
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");

    switch (luaChonLoai) {
        case 1: nhapSanPham(THUC_PHAM); break;
        case 2: nhapSanPham(DO_UONG); break;
        case 3: nhapSanPham(THOI_TRANG); break;
        case 4: nhapSanPham(DO_GIA_DUNG); break;
        case 5: nhapSanPham(DO_DIEN_TU); break;
        case 6: break;  // Thoát
    }
}


int timSanPham(const string& tenSanPham) {
    for (size_t i = 0; i < danhSachSanPham.size(); ++i) {
        if (danhSachSanPham[i]->getTen() == tenSanPham) {
            return i; // Trả về chỉ mục nếu tìm thấy
        }
    }
    return -1; // Không tìm thấy
}

void capNhatSanPham(int index, int soLuongThem) {
    if (soLuongThem > 0) {
        int soLuongMoi = danhSachSanPham[index]->getSoLuong() + soLuongThem;
        danhSachSanPham[index]->setSoLuong(soLuongMoi);
        cout << "Cap nhat so luong cua " << danhSachSanPham[index]->getTen()
             << " thanh cong. So luong hien tai: " << soLuongMoi << ".\n";
        luuSanPhamVaoFile("database/product.txt");
    } else {
        cout << "So luong them phai lon hon 0.\n";
    }
}

void nhapSanPhamMoi(LoaiSanPham loai) {
    SanPham* sanPhamMoi = nullptr;
    switch (loai) {
        case THUC_PHAM:
            sanPhamMoi = new ThucPham();
            break;
        case DO_UONG:
            sanPhamMoi = new DoUong();
            break;
        case THOI_TRANG:
            sanPhamMoi = new ThoiTrang();
            break;
        case DO_GIA_DUNG:
            sanPhamMoi = new DoGiaDung();
            break;
        case DO_DIEN_TU:
            sanPhamMoi = new DoDienTu();
            break;
    }
    if (sanPhamMoi) {
        sanPhamMoi->nhapThongTin();

        // Kiểm tra trùng lặp
        int index = timSanPham(sanPhamMoi->getTen());
        if (index != -1) {
            capNhatSanPham(index, sanPhamMoi->getSoLuong());
            delete sanPhamMoi; // Xóa sản phẩm mới vì đã cộng vào sản phẩm cũ
        } else {
            danhSachSanPham.push_back(sanPhamMoi);
            cout << "San pham moi da duoc them vao kho.\n";
            luuSanPhamVaoFile("database/product.txt");
        }
    }
}

void nhapSanPham(LoaiSanPham loai) {
    cout << "Danh sach san pham hien co:\n";
    vector<int> danhSachHienThi;
    bool found = false;

    cout << "==================================================================\n";

    // In thông tin tiêu đề, chỉ chữ được tô màu
    cout << "| ";
    setColor(11); // Xanh dương nhạt
    cout << "STT";
    setColor(7); // Trở lại màu mặc định
    cout << " | ";

    setColor(11);
    cout << "Ten san pham";
    setColor(7);
    cout << "                   | ";

    setColor(11);
    cout << "So luong";
    setColor(7);
    cout << " | ";

    setColor(11);
    cout << "Gia (VND)";
    setColor(7);
    cout << "    |\n";
    cout << "==================================================================\n";
    // Hiển thị sản phẩm theo loại
    for (size_t i = 0; i < danhSachSanPham.size(); ++i) {
        if (((loai == THUC_PHAM && dynamic_cast<ThucPham*>(danhSachSanPham[i])) ||
            (loai == DO_UONG && dynamic_cast<DoUong*>(danhSachSanPham[i])) ||
            (loai == THOI_TRANG && dynamic_cast<ThoiTrang*>(danhSachSanPham[i])) ||
            (loai == DO_GIA_DUNG && dynamic_cast<DoGiaDung*>(danhSachSanPham[i])) ||
            (loai == DO_DIEN_TU && dynamic_cast<DoDienTu*>(danhSachSanPham[i]))) ) {
            
            setColor(15); // Màu trắng cho danh sách sản phẩm
            cout << "| " << setw(3) << left << danhSachHienThi.size() + 1 << " | ";
            cout << setw(30) << left << danhSachSanPham[i]->getTen() << " | ";
            cout << setw(8) << left << danhSachSanPham[i]->getSoLuong() << " | ";
            cout << setw(12) << left << danhSachSanPham[i]->getGia() << " |\n";
            setColor(7);
            
            danhSachHienThi.push_back(i);
            found = true;
        }
    }
    cout << "==================================================================\n";


    if (!found) {
        cout << "Khong co san pham nao trong kho. Ban co muon nhap san pham moi khong? (Y(y)/Phim khac): ";
        char nhapMoi;
        cin >> nhapMoi;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (nhapMoi == 'y' || nhapMoi == 'Y') {
            nhapSanPhamMoi(loai);
        }
        return;
    }

    // Nhập sản phẩm
    while (true) {
        int luaChon;
        setColor(14);
        cout << "\nChon san pham muon nhap (nhap so tuong ung, hoac 0 de dung, hoac -1 de nhap san pham moi): ";
        setColor(7);
        cinInt >> luaChon;

        if (luaChon == 0) {
            this_thread::sleep_for(chrono::milliseconds(500));
            system("cls");
            break;
        } 
        if (luaChon == -1) {
            nhapSanPhamMoi(loai);
            continue;
        }

        if (luaChon > 0 && luaChon <= danhSachHienThi.size()) {
            int indexSanPham = danhSachHienThi[luaChon - 1];
            int soLuongNhap;
            setColor(10);
            cout << "Nhap so luong muon them: ";
            setColor(7);
            cinInt >> soLuongNhap;
            capNhatSanPham(indexSanPham, soLuongNhap);
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    }
}

void xoaHang(){
    docSanPhamTuFile("database/product.txt");
    int luaChonLoai = 1;  // Lựa chọn mặc định
    bool keyPress = false;

    while (true) {
        system("cls");

        // Hiển thị menu với màu sắc
        cout << "=============================\n";
        for (int i = 1; i <= 6; ++i) {
            // Nếu đang ở mục chọn hiện tại, đổi màu
            if (i == luaChonLoai) {

                cout << "|";
                setColor(14);
                cout <<" * ";
            } else {
                setColor(7); // Màu trắng cho các lựa chọn khác
                cout << "|   ";
            }

            // In tên lựa chọn
            switch (i) {
                case 1: cout << "Thuc pham               ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 2: cout << "Do uong                 ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 3: cout << "Thoi trang              ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 4: cout << "Do gia dung             ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 5: cout << "Do dien tu              ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 6: cout << "Thoat                   ";
                        setColor(7);
                        cout<<"|";
                        break;
            }

            cout << endl;
        }
        setColor(7);
        cout << "=============================\n";
        cout << "Chon loai san pham muon mua (Sử dụng mũi tên lên/xuống để di chuyển và Enter để chọn):";

        // Đọc phím người dùng
        int key = _getch();

        // Xử lý mũi tên
        if (key == 224) {  // Phím mũi tên
            key = _getch(); // Đọc mã phím mũi tên
            if (key == 72 && luaChonLoai > 1) {  // Mũi tên lên
                luaChonLoai--;
            } else if (key == 80 && luaChonLoai < 6) {  // Mũi tên xuống
                luaChonLoai++;
            }
        } else if (key == 13) {  // Enter
            break;  // Chọn lựa chọn hiện tại
        }
    }

    // Sau khi chọn xong, chuyển đến mục tương ứng
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");

    switch (luaChonLoai) {
        case 1: xoaSanPham(THUC_PHAM); break;
        case 2: xoaSanPham(DO_UONG); break;
        case 3: xoaSanPham(THOI_TRANG); break;
        case 4: xoaSanPham(DO_GIA_DUNG); break;
        case 5: xoaSanPham(DO_DIEN_TU); break;
        case 6: break;  // Thoát
    }
}

void xoaSanPham(LoaiSanPham loai) {
    vector<int> danhSachHienThi; // Lưu các chỉ mục của sản phẩm hợp lệ được hiển thị
    bool found = false;
    cout << "==================================================================\n";

    // In thông tin tiêu đề, chỉ chữ được tô màu
    cout << "| ";
    setColor(11); // Xanh dương nhạt
    cout << "STT";
    setColor(7); // Trở lại màu mặc định
    cout << " | ";

    setColor(11);
    cout << "Ten san pham";
    setColor(7);
    cout << "                   | ";

    setColor(11);
    cout << "So luong";
    setColor(7);
    cout << " | ";

    setColor(11);
    cout << "Gia (VND)";
    setColor(7);
    cout << "    |\n";

    // Đường viền dưới giữ màu mặc định
    cout << "==================================================================\n";
    // Hiển thị các sản phẩm thuộc loại được chọn
    for (size_t i = 0; i < danhSachSanPham.size(); ++i) {
        if (((loai == THUC_PHAM && dynamic_cast<ThucPham*>(danhSachSanPham[i])) ||
            (loai == DO_UONG && dynamic_cast<DoUong*>(danhSachSanPham[i])) ||
            (loai == THOI_TRANG && dynamic_cast<ThoiTrang*>(danhSachSanPham[i])) ||
            (loai == DO_GIA_DUNG && dynamic_cast<DoGiaDung*>(danhSachSanPham[i])) ||
            (loai == DO_DIEN_TU && dynamic_cast<DoDienTu*>(danhSachSanPham[i]))) && danhSachSanPham[i]->getSoLuong() != 0) {
            
            setColor(15); // Màu trắng cho danh sách sản phẩm
            cout << "| " << setw(3) << left << danhSachHienThi.size() + 1 << " | ";
            cout << setw(30) << left << danhSachSanPham[i]->getTen() << " | ";
            cout << setw(8) << left << danhSachSanPham[i]->getSoLuong() << " | ";
            cout << setw(12) << left << danhSachSanPham[i]->getGia() << " |\n";
            setColor(7);
            
            danhSachHienThi.push_back(i);
            found = true;
        }
    }
    cout << "==================================================================\n";
    if (!found) {
        cout << "Khong co san pham nao trong kho.\n";
        return; // Nếu không có sản phẩm nào, thoát hàm
    }

    // Lặp để người dùng chọn sản phẩm cần xóa
    while (true) {
        int luaChon;
        setColor(14);
        cout << "\nChon san pham muon xoa (nhap so tuong ung, hoac 0 de dung): ";
        setColor(7);
        cinInt >> luaChon;

        if (luaChon == 0){
            system("cls");
            break; 
        } // Kết thúc nếu người dùng nhập 0

        if (luaChon > 0 && luaChon <= danhSachHienThi.size()) {
            int indexSanPham = danhSachHienThi[luaChon - 1]; // Lấy chỉ mục thực của sản phẩm từ danhSachHienThi

            // Xóa sản phẩm này khỏi danh sách (chuyển số lượng về 0)
            danhSachSanPham[indexSanPham]->setSoLuong(0);
            setColor(10);
            cout << "San pham " << danhSachSanPham[indexSanPham]->getTen() << " da duoc xoa.\n";
            setColor(7);
            // Loại bỏ sản phẩm khỏi danh sách hiển thị
            danhSachHienThi.erase(danhSachHienThi.begin() + luaChon - 1);

            // Cập nhật lại file sau khi xóa sản phẩm
            luuSanPhamVaoFile("database/product.txt");

            // Nếu không còn sản phẩm nào trong danh sách hiển thị, dừng lại
            if (danhSachHienThi.empty()) {
                setColor(12);
                cout << "Tat ca san pham da duoc xoa.\n";
                setColor(7);
                break;
            }
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    }
}
void capNhatGiaHang() {
    docSanPhamTuFile("database/product.txt");
    int luaChonLoai = 1;  // Lựa chọn mặc định
    bool keyPress = false;

    while (true) {
        system("cls");

        // Hiển thị menu với màu sắc
        cout << "=============================\n";
        for (int i = 1; i <= 6; ++i) {
            // Nếu đang ở mục chọn hiện tại, đổi màu
            if (i == luaChonLoai) {

                cout << "|";
                setColor(14);
                cout <<" * ";
            } else {
                setColor(7); // Màu trắng cho các lựa chọn khác
                cout << "|   ";
            }

            // In tên lựa chọn
            switch (i) {
                case 1: cout << "Thuc pham               ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 2: cout << "Do uong                 ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 3: cout << "Thoi trang              ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 4: cout << "Do gia dung             ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 5: cout << "Do dien tu              ";
                        setColor(7);
                        cout<<"|";
                        break;
                case 6: cout << "Thoat                   ";
                        setColor(7);
                        cout<<"|";
                        break;
            }

            cout << endl;
        }
        setColor(7);
        cout << "=============================\n";
        cout << "Chon loai san pham muon cap nhat gia (Sử dụng mũi tên lên/xuống để di chuyển và Enter để chọn):";

        // Đọc phím người dùng
        int key = _getch();

        // Xử lý mũi tên
        if (key == 224) {  // Phím mũi tên
            key = _getch(); // Đọc mã phím mũi tên
            if (key == 72 && luaChonLoai > 1) {  // Mũi tên lên
                luaChonLoai--;
            } else if (key == 80 && luaChonLoai < 6) {  // Mũi tên xuống
                luaChonLoai++;
            }
        } else if (key == 13) {  // Enter
            break;  // Chọn lựa chọn hiện tại
        }
    }

    // Sau khi chọn xong, chuyển đến mục tương ứng
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");

    switch (luaChonLoai) {
        case 1: capNhatGiaSanPham(THUC_PHAM); break;
        case 2: capNhatGiaSanPham(DO_UONG); break;
        case 3: capNhatGiaSanPham(THOI_TRANG); break;
        case 4: capNhatGiaSanPham(DO_GIA_DUNG); break;
        case 5: capNhatGiaSanPham(DO_DIEN_TU); break;
        case 6: break;  // Thoát
    }
}
void capNhatGiaSanPham(LoaiSanPham loai) {
    vector<int> danhSachHienThi; // Lưu các chỉ mục của sản phẩm hợp lệ được hiển thị
    bool found = false;
    cout << "=======================================================\n";

    // In thông tin tiêu đề, chỉ chữ được tô màu
    cout << "| ";
    setColor(11); // Xanh dương nhạt
    cout << "STT";
    setColor(7); // Trở lại màu mặc định
    cout << " | ";

    setColor(11);
    cout << "Ten san pham";
    setColor(7);
    cout << "                   | ";

    setColor(11);
    cout << "Gia (VND)";
    setColor(7);
    cout << "    |\n";

    // Đường viền dưới giữ màu mặc định
    cout << "=======================================================\n";
    
    // Hiển thị các sản phẩm thuộc loại được chọn
    for (size_t i = 0; i < danhSachSanPham.size(); ++i) {
        if (((loai == THUC_PHAM && dynamic_cast<ThucPham*>(danhSachSanPham[i])) ||
            (loai == DO_UONG && dynamic_cast<DoUong*>(danhSachSanPham[i])) ||
            (loai == THOI_TRANG && dynamic_cast<ThoiTrang*>(danhSachSanPham[i])) ||
            (loai == DO_GIA_DUNG && dynamic_cast<DoGiaDung*>(danhSachSanPham[i])) ||
            (loai == DO_DIEN_TU && dynamic_cast<DoDienTu*>(danhSachSanPham[i]))) && danhSachSanPham[i]->getSoLuong() != 0) {
            
            setColor(15); // Màu trắng cho danh sách sản phẩm
            cout << "| " << setw(3) << left << danhSachHienThi.size() + 1 << " | ";
            cout << setw(30) << left << danhSachSanPham[i]->getTen() << " | ";
            cout << setw(12) << left << danhSachSanPham[i]->getGia() << " |\n";
            setColor(7);
            
            danhSachHienThi.push_back(i);
            found = true;
        }
    }
    cout << "=======================================================\n";
    
    if (!found) {
        cout << "Khong co san pham nao trong kho.\n";
        return; // Nếu không có sản phẩm nào, thoát hàm
    }

    // Lặp để người dùng chọn sản phẩm cần cập nhật giá
    while (true) {
        int luaChon;
        setColor(14);
        cout << "\nChon san pham muon cap nhat gia (nhap so tuong ung, hoac 0 de dung): ";
        setColor(7);
        cinInt >> luaChon;

        if (luaChon == 0){
            system("cls");
            break; 
        } // Kết thúc nếu người dùng nhập 0

        if (luaChon > 0 && luaChon <= danhSachHienThi.size()) {
            int indexSanPham = danhSachHienThi[luaChon - 1]; // Lấy chỉ mục thực của sản phẩm từ danhSachHienThi

            // Nhập giá mới cho sản phẩm
            double giaMoi;
            cout << "Nhap gia moi cho san pham " << danhSachSanPham[indexSanPham]->getTen() << ": ";
            cin >> giaMoi;

            // Cập nhật giá sản phẩm
            danhSachSanPham[indexSanPham]->setGia(giaMoi);
            setColor(10);
            cout << "Gia san pham " << danhSachSanPham[indexSanPham]->getTen() << " da duoc cap nhat.\n";
            setColor(7);

            // Cập nhật lại file sau khi cập nhật giá
            luuSanPhamVaoFile("database/product.txt");

            break;  // Thoát sau khi cập nhật
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    }
}


// Khai báo giỏ hàng
vector<int> cart; // Giỏ hàng tạm thời lưu các chỉ mục sản phẩm đã chọn
vector<int> quantities; // Số lượng tương ứng với từng sản phẩm trong giỏ hàng


void muaSanPham(LoaiSanPham loai, UserAccount &user) {
    vector<int> danhSachHienThi;
    bool found = false;

    // Hiển thị các sản phẩm thuộc loại được chọn
    cout << "==================================================================\n";

    // In thông tin tiêu đề, chỉ chữ được tô màu
    cout << "| ";
    setColor(11); // Xanh dương nhạt
    cout << "STT";
    setColor(7); // Trở lại màu mặc định
    cout << " | ";

    setColor(11);
    cout << "Ten san pham";
    setColor(7);
    cout << "                   | ";

    setColor(11);
    cout << "So luong";
    setColor(7);
    cout << " | ";

    setColor(11);
    cout << "Gia (VND)";
    setColor(7);
    cout << "    |\n";

    // Đường viền dưới giữ màu mặc định
    cout << "==================================================================\n";

    for (size_t i = 0; i < danhSachSanPham.size(); ++i) {
        if (((loai == THUC_PHAM && dynamic_cast<ThucPham*>(danhSachSanPham[i])) ||
            (loai == DO_UONG && dynamic_cast<DoUong*>(danhSachSanPham[i])) ||
            (loai == THOI_TRANG && dynamic_cast<ThoiTrang*>(danhSachSanPham[i])) ||
            (loai == DO_GIA_DUNG && dynamic_cast<DoGiaDung*>(danhSachSanPham[i])) ||
            (loai == DO_DIEN_TU && dynamic_cast<DoDienTu*>(danhSachSanPham[i]))) && danhSachSanPham[i]->getSoLuong() != 0) {
            
            setColor(15); // Màu trắng cho danh sách sản phẩm
            cout << "| " << setw(3) << left << danhSachHienThi.size() + 1 << " | ";
            cout << setw(30) << left << danhSachSanPham[i]->getTen() << " | ";
            cout << setw(8) << left << danhSachSanPham[i]->getSoLuong() << " | ";
            cout << setw(12) << left << danhSachSanPham[i]->getGia() << " |\n";
            setColor(7);
            
            danhSachHienThi.push_back(i);
            found = true;
        }
    }
    cout << "==================================================================\n";

    if (!found) {
        setColor(12); // Màu đỏ cho thông báo không có sản phẩm
        cout << "Khong co san pham nao trong kho.\n";
        setColor(7);
    }

    // Lặp để người dùng mua nhiều sản phẩm
    while (true) {
        int luaChon;
        setColor(14); // Màu vàng cho yêu cầu chọn sản phẩm
        cout << "\nChon san pham muon mua (nhap so tuong ung, hoac 0 de dung mua): ";
        setColor(7);
        cinInt >> luaChon;

        if (luaChon == 0) {
            break;
        }

        if (luaChon > 0 && luaChon <= danhSachHienThi.size()) {
            int soLuong;
            setColor(10); // Màu xanh lá cho yêu cầu nhập số lượng
            cout << "Nhap so luong muon mua: ";
            setColor(7);
            cinInt >> soLuong;

            if (soLuong <= 0) {
                setColor(12); // Màu đỏ cho thông báo sai số lượng
                cout << "So luong phai lon hon 0.\n";
                setColor(7);
            } else {
                int indexSanPham = danhSachHienThi[luaChon - 1];

                // Kiểm tra xem sản phẩm đã có trong giỏ hàng chưa
                auto it = find(cart.begin(), cart.end(), indexSanPham);
                if (it != cart.end()) {
                    // Nếu sản phẩm đã có, cập nhật số lượng
                    int indexInCart = distance(cart.begin(), it);
                    quantities[indexInCart] += soLuong;
                    setColor(10); // Màu xanh lá cho thông báo thêm sản phẩm vào giỏ
                    cout << "Da them " << soLuong << " " << danhSachSanPham[indexSanPham]->getTen() << " vao gio hang.\n";
                    setColor(7);
                } else {
                    // Nếu chưa có, thêm vào giỏ hàng
                    cart.push_back(indexSanPham);
                    quantities.push_back(soLuong);
                    setColor(10); // Màu xanh lá cho thông báo thêm sản phẩm vào giỏ
                    cout << "Da them " << soLuong << " " << danhSachSanPham[indexSanPham]->getTen() << " vao gio hang.\n";
                    setColor(7);
                }

                // Giảm số lượng sản phẩm trong kho
                danhSachSanPham[indexSanPham]->setSoLuong(danhSachSanPham[indexSanPham]->getSoLuong() - soLuong);
            }
        } else {
            setColor(12); // Màu đỏ cho thông báo sai lựa chọn
            cout << "Lua chon khong hop le.\n";
            setColor(7);
        }
    }

    // Xác nhận các sản phẩm đã mua
    if (!cart.empty()) {
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        setColor(11); // Màu xanh sáng cho thông báo sản phẩm đã chọn
        cout << "\nBan da chon mua cac san pham sau:\n";
        setColor(7);
        for (size_t i = 0; i < cart.size(); ++i) {
            int index = cart[i];
            setColor(15); // Màu trắng cho danh sách sản phẩm trong giỏ
            cout << "- " << danhSachSanPham[index]->getTen() << ": " << quantities[i] 
                 << " thanh tien: "<< fixed << setprecision(1) << quantities[i] * danhSachSanPham[index]->getGia() << " VND" << endl;
            setColor(7);
        }
        
        int luaChonTiep;
        setColor(7); // Màu vàng cho lựa chọn tiếp theo
        cout << "\n1. Toi quay thanh toan\n2. Toi quay khac de tiep tuc mua sam\nLua chon cua ban: ";
        setColor(7);
        cin >> luaChonTiep;

        if (luaChonTiep == 1) {
            setColor(10); // Màu xanh lá cho thông báo thanh toán
            cout << "Dang di toi quay thanh toan...\n";
            setColor(7);
            system("cls");

            // Thực hiện thanh toán, và giảm số lượng trong kho
            for (size_t i = 0; i < cart.size(); ++i) {
                int indexSanPham = cart[i];
                int soLuongMua = quantities[i];
                danhSachSanPham[indexSanPham]->setSoLuong(danhSachSanPham[indexSanPham]->getSoLuong() - soLuongMua);
            }

            thanhToan(cart, quantities, user); // Gọi hàm thanh toán
        } else if (luaChonTiep == 2) {
            setColor(15); // Màu trắng cho thông báo quay lại
            cout << "Dang di toi quay khac...\n";
            setColor(7);
            this_thread::sleep_for(chrono::milliseconds(500));
            system("cls");
            chonQuayKhac(user);
        } else {
            setColor(12); // Màu đỏ cho thông báo sai lựa chọn
            cout << "Lua chon khong hop le.\n";
            setColor(7);
        }
    } else {
        setColor(12); // Màu đỏ cho thông báo giỏ hàng trống
        cout << "Ban chua mua san pham nao.\n";
        setColor(7);
    }
}



    void luuSanPhamVaoFile(const string& tenFile) {
        ofstream file(tenFile);
        if (!file.is_open()) {
            cout << "Khong the mo file de ghi.\n";
            return;
        }

        for (const auto& sanPham : danhSachSanPham) {
            file << sanPham->getLoai() << ","
                 << sanPham->getTen() << ","    
                 << sanPham->getGia() << "," 
                 << sanPham->getSoLuong() << endl;   
        }

        file.close();
    }



void docSanPhamTuFile(const string& tenFile) {
    // Xóa danh sách cũ trước khi đọc file
    for (SanPham* sp : danhSachSanPham) {
        delete sp; // Giải phóng bộ nhớ
    }
    danhSachSanPham.clear();

    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong the mo file de doc.\n";
        return;
    }

    string loai, ten;
    double gia;
    int soLuong;

    while (getline(file, loai, ',')) {
        getline(file, ten, ',');
        file >> gia;
        file.ignore(); // Bỏ qua dấu phẩy
        file >> soLuong;
        file.ignore(); // Bỏ qua newline

        SanPham* sanPham = nullptr;
        if (loai == "ThucPham") sanPham = new ThucPham();
        else if (loai == "DoUong") sanPham = new DoUong();
        else if (loai == "ThoiTrang") sanPham = new ThoiTrang();
        else if (loai == "DoGiaDung") sanPham = new DoGiaDung();
        else if (loai == "DoDienTu") sanPham = new DoDienTu();

        if (sanPham) {
            sanPham->setTen(ten);
            sanPham->setGia(gia);
            sanPham->setSoLuong(soLuong);
            danhSachSanPham.push_back(sanPham);
        }
    }

    file.close();
}
void liveSearchByName(const string& query) {
    if (query.empty()) {
        std::cout << "Tu khoa tim kiem khong duoc de trong.\n";
        return;
    }

    std::cout << "\n====== Tim kiem san pham ======\n";
    std::cout << "Tu khoa: \"" << query << "\"\n";
    bool found = false;

    // Tiêu đề với màu vàng (mã ANSI màu vàng: 33)
    std::cout << "[------------------------------------------------------------+\n";
    std::cout << "| " << std::setw(20) << std::left << "Ten san pham"
              << "| " << std::setw(12) << std::left << "Loai"
              << "| " << std::setw(10) << std::left << "Gia"
              << "| " << std::setw(10) << std::left << "So luong" << " |\n";
    std::cout << "+------------------------------------------------------------+\n"; // Reset màu

    // Giả sử danhSachSanPham là danh sách các sản phẩm
    for (SanPham* sp : danhSachSanPham) {
        // So khớp từ khóa với tên sản phẩm (không phân biệt hoa thường)
        if (sp->getTen().find(query) != std::string::npos) {
            std::cout << "| " << std::setw(20) << std::left << sp->getTen()
                      << "| " << std::setw(12) << std::left << sp->getLoai()
                      << "| " << std::setw(10) << std::left << sp->getGia()
                      << "| " << std::setw(10) << std::left << sp->getSoLuong() << " |\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "| Khong tim thay san pham nao.                               |\n";
    }

    // Dòng kết thúc với màu vàng
    std::cout << "+------------------------------------------------------------+\n";
    }
void showSearchUI() {
    cout << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                     Tim kiem san pham                    |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "| Nhap ten san pham can tim (hoac go 'exit' hoac (-1) de   |\n";
    cout << "| mua hang de thoat):                                      |\n";
    cout << "+----------------------------------------------------------+\n";
}
void showSearchUIforManager() {
    cout << "\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                     Tim kiem san pham                    |\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "| Nhap ten san pham can tim (hoac go 'exit' ):             |\n";
    cout << "+----------------------------------------------------------+\n";
}
void moveCursor(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}
void xulytimkiem(UserAccount &user){
    std::string query;
    bool firstSearch = true; // Biến để kiểm tra lần tìm kiếm đầu tiên

    // Đọc danh sách sản phẩm từ file ngay khi bắt đầu tìm kiếm
    docSanPhamTuFile("database/product.txt"); // Đọc danh sách sản phẩm từ file

    while (true) {
        // Nếu không phải lần tìm kiếm đầu tiên, đợi và xóa màn hình
        if (!firstSearch) {
            this_thread::sleep_for(chrono::milliseconds(3500));
            system("cls");  // Xóa màn hình mỗi khi tìm kiếm sau lần đầu tiên
        } else {
            firstSearch = false;  // Sau lần đầu tiên, set flag là false
        }

        // Hiển thị giao diện tìm kiếm tùy theo vai trò của người dùng
        if (user.getRoles() == 0) { // Nếu là khách hàng
            showSearchUI();  // Giao diện tìm kiếm cho khách hàng
            moveCursor(25, 6);  // Di chuyển con trỏ đến vị trí nhập
        } else if (user.getRoles() == 2) { // Nếu là quản lý
            showSearchUIforManager();  // Giao diện tìm kiếm cho quản lý
            moveCursor(48, 5);  // Di chuyển con trỏ đến vị trí nhập
        }

        // Nhập từ khóa tìm kiếm
        getline(cin, query);

        if (query == "exit") break;

        // Nếu người dùng nhập "-1", xử lý tùy theo vai trò
        if (query == "-1") {
            if (user.getRoles() == 0) {
                std::cout << "Ban da chon qua quay san pham.\n";
                chonQuayKhac(user);  
                break;  // Thoát vòng tìm kiếm
            } else if (user.getRoles() == 2) {
                std::cout << "Ban da chon quan ly kho hang.\n";
                break;  // Thoát vòng tìm kiếm, có thể chuyển sang màn hình quản lý kho
            }
        }

        // Tìm kiếm sản phẩm theo tên
        liveSearchByName(query);
        std::cout << "----------------------\n";
    }

    // Dọn dẹp bộ nhớ sau khi tất cả các tìm kiếm đã hoàn tất
    for (SanPham* sp : danhSachSanPham) {
        delete sp;  // Giải phóng bộ nhớ của các đối tượng SanPham
    }
    danhSachSanPham.clear();  // Xóa danh sách sản phẩm
}
               


void drawHeader1(){
        cout << " ╔══════════════════════════════════════════════════════╗" << endl;
    cout << " ║                    ";
    setColor(11);
    cout<<" QUẢN LÝ KHO Hàng";
    setColor(7);
    cout<<"                 ║" << endl;
    cout << " ╠══════════════════════════════════════════════════════╣" ;
}
void drawMenuOptions(int choice) {
    setColor(7); // Màu trắng cho tất cả mục
    string options[] = {
        "Nhap hang",
        "Xoa hang",
        "Cap nhat gia san pham",
        "tim kiem san pham",
        "Thoat"
    };

    for (int i = 0; i < 5; i++) {
        // Nếu đang ở mục chọn hiện tại, đổi màu
        if (i == choice) {
            cout << " ║";
            setColor(14);  // Màu vàng cho mục được chọn
            cout << " * ";  // Dấu * để đánh dấu mục chọn
        } else {
            setColor(7);  // Màu trắng cho các lựa chọn khác
            cout << " ║   ";  // Khoảng trống cho mục không chọn
        }

        // In tên lựa chọn với việc căn chỉnh cho đẹp
        switch (i) {
            case 0: cout << "Nhap hang                                          ";
                    setColor(7);
                    cout << "║";
                    break;
            case 1: cout << "Xoa hang                                           ";
                    setColor(7);
                    cout << "║";
                    break;
            case 2: cout << "Cap nhat gia san pham                              ";
                    setColor(7);
                    cout << "║";
                    break;
            case 3: cout << "Tim kiem san pham                                  ";
                    setColor(7);
                    cout << "║";
                    break;
            case 4: cout << "Thoat                                              ";
                    setColor(7);
                    cout << "║";
                    break;
        }

        cout << endl;
    }
}


    ~QuanLyChucNang() {
        for (auto sp : danhSachSanPham) {
            delete sp; // Giải phóng bộ nhớ
        }
    }
    void veSieuThi(UserAccount user) {
    system("cls");

    setColor(7); // Màu đỏ cho tiêu đề chính
    cout << "┌───────────────────────────────────────────────────────┐\n";
    cout << "│                       ";
    setColor(11); 
    cout << "SIEU THI";
    setColor(7); // Trở lại màu đỏ
    cout << "                        │\n";
    cout << "├───────────────────────────────────────────────────────┤\n";

    setColor(7); // Màu trắng
    cout << "│                                                       │\n";
    cout << "│     [";
    setColor(14);
    cout<<"QUAY THU NGAN";
    setColor(7);
    cout<<"]                                   │\n";
    cout << "│   ┌─────────────────┐                                 │\n";
    cout << "│   │   ";
    setColor(7); // Màu xanh lá cho chữ "KHACH HANG"
    cout << "KHACH HANG";
    setColor(7); // Trắng trở lại
    cout << "    │                                 │\n";
    cout << "│   │   ";
    setColor(7); // Màu xanh lá cho chữ "TINH TIEN"
    cout << "TINH TIEN";
    setColor(7);
    cout << "     │                                 │\n";
    cout << "│   └─────────────────┘                                 │\n";
    cout << "│                                                       │                  ┌─────────────────────────────────────┐\n";
    cout << "│                                                       │                  │ ";
    setColor(11); // Màu xanh dương nhạt
    cout << "Thong tin khach hang:";
    setColor(7); // Màu trắng
    cout << "               │\n";
    cout << "│                                                       │                  ├─────────────────────────────────────┤\n";
    cout << "│                                                       │                  │ Ten: "  
        << setw(31) << left;
    setColor(7); // Màu xanh lá
    cout << user.getUsername();
    setColor(7);
    cout << "│\n";
    cout << "│                                                       │                  │ So du: "  
        << setw(24) << left << fixed << setprecision(2);
    setColor(7);
    cout << user.getCredits() << "vnd";
    setColor(7);
    cout << "  │\n";
    cout << "│                                                       │                  └─────────────────────────────────────┘\n";

    cout << "│   ┌──────────────────────┐   ┌──────────────────────┐ │\n";
    cout << "│   │    ";
    setColor(14);
    cout << "KHU DO UONG";
    setColor(7);
    cout << "       │   │ ";
    setColor(14);
    cout << "KHU THOI TRANG";
    setColor(7);
    cout << "       │ │\n";
                 
    cout << "│   ├──────────────────────┤   ├──────────────────────┤ │\n";
    cout << "│   │  - ";
    setColor(7); // Màu xanh lá
    cout << "Nuoc co ga";
    setColor(7);
    cout << "        │   │  - ";
    setColor(7);
    cout << "Quan ao";
    setColor(7);
    cout << "           │ │\n";
    cout << "│   │  - ";
    setColor(7);
    cout << "Nuoc ep trai cay";
    setColor(7);
    cout << "  │   │  - ";
    setColor(7);
    cout << "Phu kien";
    setColor(7);
    cout << "          │ │\n";
    cout << "│   │  - ";
    setColor(7);
    cout << "Sua tuoi";
    setColor(7);
    cout << "          │   │  - ";
    setColor(7);
    cout << "Giay dep";
    setColor(7);
    cout << "          │ │\n";
    cout << "│   └──────────────────────┘   └──────────────────────┘ │\n";

    cout << "│                                                       │\n";
    cout << "│   ┌──────────────────────┐   ┌──────────────────────┐ │\n";
    cout << "│   │   ";
    setColor(14);
    cout << "KHU THUC PHAM";
    setColor(7);
    cout << "      │   │ ";
    setColor(14);
    cout << "KHU TONG HOP";
    setColor(7);
    cout << "         │ │\n";
    cout << "│   ├──────────────────────┤   ├──────────────────────┤ │\n";
    cout << "│   │  - ";
    setColor(7);
    cout << "Thit tuoi";
    setColor(7);
    cout << "         │   │  - ";
    setColor(7);
    cout << "Do gia dung";
    setColor(7);
    cout << "       │ │\n";
    cout << "│   │  - ";
    setColor(7);
    cout << "Ca dong lanh";
    setColor(7);
    cout << "      │   │  - ";
    setColor(7);
    cout << "Do dien tu";
    setColor(7);
    cout << "        │ │\n";
    cout << "│   │  - ";
    setColor(7);
    cout << "Rau cu tuoi";
    setColor(7);
    cout << "       │   │                      │ │\n";
    cout << "│   └──────────────────────┘   └──────────────────────┘ │\n";
    cout << "│                        [";
    setColor(12); // Đỏ
    cout << "CUA RA";
    setColor(7);
    cout << "]                       │\n";
    cout << "└───────────────────────────────────────────────────────┘\n";

    }   
};
