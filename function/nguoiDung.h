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
        cin.ignore();
        getline(cin,ten);
        cout << "Nhap gia: ";
        cinInt >> gia;
        cout << "Nhap so luong: ";
        cinInt >> soLuong;
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
        cin.ignore();
        getline(cin,ten);
        cout << "Nhap gia: ";
        cinInt >> gia;
        cout << "Nhap so luong: ";
        cinInt >> soLuong;

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
        cin.ignore();
        getline(cin,ten);
        cout << "Nhap gia: ";
        cinInt >> gia;
        cout << "Nhap so luong: ";
        cinInt >> soLuong;

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
        cin.ignore();
        getline(cin,ten);
        cout << "Nhap gia: ";
        cinInt >> gia;
        cout << "Nhap so luong: ";
        cinInt >> soLuong;

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
        cin.ignore();
        getline(cin,ten);
        cout << "Nhap gia: ";
        cinInt >> gia;
        cout << "Nhap so luong: ";
        cinInt >> soLuong;

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
    // Đọc danh sách sản phẩm từ file trước
    docSanPhamTuFile("database/product.txt");
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");
    while(true){
    setColor(12);
    cout << "Chon loai san pham muon nhap:\n";
    setColor(7);
    setColor(11);
    cout << "-----------------------------\n";
    cout << "| 1. Thuc pham              |\n";
    cout << "| 2. Do uong                |\n";
    cout << "| 3. Thoi trang             |\n";
    cout << "| 4. Do gia dung            |\n";
    cout << "| 5. Do dien tu             |\n";
    cout << "| 6. Thoat                  |\n";
    cout << "-----------------------------\n";
    setColor(7);
    int luaChonLoai;
    cinInt >> luaChonLoai;
     if (luaChonLoai == 6) { // Nếu người dùng chọn thoát
            setColor(12);
            cout << "Da thoat khoi chuc nang nhap hang.\n";
            setColor(7);
            break; // Thoát khỏi vòng lặp
        }
        while (luaChonLoai < 1 || luaChonLoai > 6) {
        cout << "Lua chon khong hop le. Vui long nhap tu 1 den 6: ";
        cinInt >> luaChonLoai;
    }
    switch (luaChonLoai) {
            case 1: {
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("cls");
                nhapSanPham(THUC_PHAM); break;
            }
            case 2: {
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("cls");
            nhapSanPham(DO_UONG); break;
            }
            case 3: {
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("cls");
                nhapSanPham(THOI_TRANG); break;
            }
            case 4: {
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("cls");
                nhapSanPham(DO_GIA_DUNG); break;
            }   
            case 5: {
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("cls");
                nhapSanPham(DO_DIEN_TU); break;
            }
        }
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

    // Hiển thị sản phẩm theo loại
    for (size_t i = 0; i < danhSachSanPham.size(); ++i) {
        if (((loai == THUC_PHAM && dynamic_cast<ThucPham*>(danhSachSanPham[i])) ||
            (loai == DO_UONG && dynamic_cast<DoUong*>(danhSachSanPham[i])) ||
            (loai == THOI_TRANG && dynamic_cast<ThoiTrang*>(danhSachSanPham[i])) ||
            (loai == DO_GIA_DUNG && dynamic_cast<DoGiaDung*>(danhSachSanPham[i])) ||
            (loai == DO_DIEN_TU && dynamic_cast<DoDienTu*>(danhSachSanPham[i])))) {
            
            cout << danhSachHienThi.size() + 1 << ". " << danhSachSanPham[i]->getTen()
                 << " (So luong: " << danhSachSanPham[i]->getSoLuong() << ") "
                 << danhSachSanPham[i]->getGia() << " VND\n";
            danhSachHienThi.push_back(i);
            found = true;
        }
    }

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
        cout << "\nChon san pham muon nhap (nhap so tuong ung, hoac 0 de dung, hoac -1 de nhap san pham moi): ";
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
            cout << "Nhap so luong muon them: ";
            cinInt >> soLuongNhap;
            capNhatSanPham(indexSanPham, soLuongNhap);
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    }
}

void xoaHang(){
    docSanPhamTuFile("database/product.txt");

    while(true){
    setColor(12);
    cout << "Chon loai san pham muon xoa:\n";
    setColor(7);
    setColor(11);
    cout << "-----------------------------\n";
    cout << "| 1. Thuc pham              |\n";
    cout << "| 2. Do uong                |\n";
    cout << "| 3. Thoi trang             |\n";
    cout << "| 4. Do gia dung            |\n";
    cout << "| 5. Do dien tu             |\n";
    cout << "| 6. Thoat                  |\n";
    cout << "-----------------------------\n";
    setColor(7);
    int luaChonLoai;
    cinInt >> luaChonLoai;
     if (luaChonLoai == 6) { // Nếu người dùng chọn thoát
            setColor(12);
            cout << "Da thoat khoi chuc nang xoa hang.\n";
            setColor(7);
            break; // Thoát khỏi vòng lặp
        }
    // Kiểm tra lựa chọn đầu vào
    while (luaChonLoai < 1 || luaChonLoai > 6) {
        cout << "Lua chon khong hop le. Vui long nhap tu 1 den 6: ";
        cinInt >> luaChonLoai;
    }
    switch (luaChonLoai) {
            case 1: {
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("cls");
                xoaSanPham(THUC_PHAM); break;
            }
            case 2: {
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("cls");
                xoaSanPham(DO_UONG); break;
            }
            case 3: {
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("cls");
                xoaSanPham(THOI_TRANG); break;
            }
            case 4: {
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("cls");
                xoaSanPham(DO_GIA_DUNG); break;
            }   
            case 5: {
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("cls");
                xoaSanPham(DO_DIEN_TU); break;
            }
        }
    }
}

void xoaSanPham(LoaiSanPham loai) {
    cout << "Danh sach san pham hien co:\n";
    vector<int> danhSachHienThi; // Lưu các chỉ mục của sản phẩm hợp lệ được hiển thị
    bool found = false;

    // Hiển thị các sản phẩm thuộc loại được chọn
    for (size_t i = 0; i < danhSachSanPham.size(); ++i) {
        if (((loai == THUC_PHAM && dynamic_cast<ThucPham*>(danhSachSanPham[i])) ||
            (loai == DO_UONG && dynamic_cast<DoUong*>(danhSachSanPham[i])) ||
            (loai == THOI_TRANG && dynamic_cast<ThoiTrang*>(danhSachSanPham[i])) ||
            (loai == DO_GIA_DUNG && dynamic_cast<DoGiaDung*>(danhSachSanPham[i])) ||
            (loai == DO_DIEN_TU && dynamic_cast<DoDienTu*>(danhSachSanPham[i]))) && danhSachSanPham[i]->getSoLuong() != 0) {
            
            cout << danhSachHienThi.size() + 1 << ". " << danhSachSanPham[i]->getTen() 
                 << " (So luong: " << danhSachSanPham[i]->getSoLuong() << ") " << danhSachSanPham[i]->getGia() << " VND" << endl;
            danhSachHienThi.push_back(i); // Lưu chỉ mục của sản phẩm hợp lệ
            found = true;
        }
    }

    if (!found) {
        cout << "Khong co san pham nao trong kho.\n";
        return; // Nếu không có sản phẩm nào, thoát hàm
    }

    // Lặp để người dùng chọn sản phẩm cần xóa
    while (true) {
        int luaChon;
        cout << "\nChon san pham muon xoa (nhap so tuong ung, hoac 0 de dung): ";
        cinInt >> luaChon;


        if (luaChon == 0){

            system("cls");
            break; 
        } // Kết thúc nếu người dùng nhập 0

        if (luaChon > 0 && luaChon <= danhSachHienThi.size()) {
            int indexSanPham = danhSachHienThi[luaChon - 1]; // Lấy chỉ mục thực của sản phẩm từ danhSachHienThi

            // Xóa sản phẩm này khỏi danh sách (chuyển số lượng về 0)
            danhSachSanPham[indexSanPham]->setSoLuong(0);
            cout << "San pham " << danhSachSanPham[indexSanPham]->getTen() << " da duoc xoa.\n";
            
            // Loại bỏ sản phẩm khỏi danh sách hiển thị
            danhSachHienThi.erase(danhSachHienThi.begin() + luaChon - 1);

            // Cập nhật lại file sau khi xóa sản phẩm
            luuSanPhamVaoFile("database/product.txt");

            // Nếu không còn sản phẩm nào trong danh sách hiển thị, dừng lại
            if (danhSachHienThi.empty()) {
                cout << "Tat ca san pham da duoc xoa.\n";
                break;
            }
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



    ~QuanLyChucNang() {
        for (auto sp : danhSachSanPham) {
            delete sp; // Giải phóng bộ nhớ
        }
    }
    void veSieuThi(UserAccount user) {
    system("cls");
    // setColor(12);
    // cout << "+-------------------------------------------------------+\n";
    // cout << "|                       SIEU THI                        |\n";
    // cout << "+-------------------------------------------------------+\n";
    // setColor(10);
    // cout << "|                                                       |\n";
    // cout << "|   [QUAY THU NGAN]                                     |\n";
    // cout << "|   +----------------------+                            |                  +-------------------------------------+\n";
    // cout << "|   |   KHACH HANG         |                            |                  | Thong tin khach hang:               |\n";
    // cout << "|   |   TINH TIEN          |                            |                  |-------------------------------------|\n";
    // cout << "|   +----------------------+                            |                  | Ten: "  << setw(31) << left << user.getUsername() << "|\n";
    // cout << "|                                                       |                  | So du: "  << setw(24) << left << fixed << setprecision(2) << user.getCredits() << "vnd  |\n";
    // cout << "|                                                       |                  +-------------------------------------+\n";
    // cout << "|   +----------------------+   +--------------------+   |\n";
    // cout << "|   |    KHU DO UONG       |   | KHU THOI TRANG     |   |\n";
    // cout << "|   +----------------------+   +--------------------+   |\n";
    // cout << "|   |  - Nuoc co ga        |   |  - Quan ao         |   |\n";
    // cout << "|   |  - Nuoc ep trai cay  |   |  - Phu kien        |   |\n";
    // cout << "|   |  - Sua tuoi          |   |  - Giay dep        |   |\n";
    // cout << "|   +----------------------+   +--------------------+   |\n";
    // cout << "|                                                       |\n";
    // cout << "|   +----------------------+   +--------------------+   |\n";
    // cout << "|   |   KHU THUC PHAM      |   | KHU TONG HOP       |   |\n";
    // cout << "|   +----------------------+   +--------------------+   |\n";
    // cout << "|   |  - Thit tuoi         |   |  - Do gia dung     |   |\n";
    // cout << "|   |  - Ca dong lanh      |   |  - Do dien tu      |   |\n";
    // cout << "|   |  - Rau cu tuoi       |   |                    |   |\n";
    // cout << "|   +----------------------+   +--------------------+   |\n";
    // cout << "|                        [CUA RA]                       |\n";
    // cout << "+-------------------------------------------------------+\n";
    // setColor(7);
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
