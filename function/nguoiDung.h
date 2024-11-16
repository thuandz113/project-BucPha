#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include <iomanip>

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

        
        cout << "=============================\n";
        cout << "| 1. Thuc pham              |\n";
        cout << "| 2. Do uong                |\n";
        cout << "| 3. Thoi trang             |\n";
        cout << "| 4. Do gia dung            |\n";
        cout << "| 5. Do dien tu             |\n";
        cout << "| 6. Thoat                  |\n";
        cout << "=============================\n";
        cout << " Chon loai san pham muon mua:\n";
        int luaChonLoai;
        cinInt >> luaChonLoai;

        while (luaChonLoai < 1 || luaChonLoai > 6) {
            cout << "Lua chon khong hop le. Vui long nhap tu 1 den 6: ";
            cinInt >> luaChonLoai;
        }

        switch (luaChonLoai) {
            case 1: {
                this_thread::sleep_for(chrono::milliseconds(500));
                system("cls");
                muaSanPham(THUC_PHAM,user);
                break;
            }
            case 2: {
                this_thread::sleep_for(chrono::milliseconds(500));
                system("cls");
                muaSanPham(DO_UONG,user);
                break;
            }
            case 3: {
                this_thread::sleep_for(chrono::milliseconds(500));
                system("cls");
                muaSanPham(THOI_TRANG,user);
                break;
            }
            case 4: {
                this_thread::sleep_for(chrono::milliseconds(500));
                system("cls");
                muaSanPham(DO_GIA_DUNG,user);
                break;
            }   
            case 5: {
                this_thread::sleep_for(chrono::milliseconds(500));
                system("cls");
                muaSanPham(DO_DIEN_TU,user);
                break;
            }
            case 6: break;
        }
    }

    void thanhToan(vector<int>& luaChonSanPham, vector<int>& soLuongMua, UserAccount &user) {
    double tongTien = 0.0;

    // Tiêu đề hóa đơn
    cout << "================================================================================\n";
    cout<<  "|                                   HOA DON                                    |\n";
    cout << "================================================================================\n";
    cout << "| " << left << setw(30) << "Ten San Pham"                                       
         << "| " << setw(10) << "So Luong" 
         << "| " << setw(15) << "Gia (VND)" 
         << "| " << setw(15) << "Thanh Tien (VND)" << "|\n";
    cout << "================================================================================\n";

    // Hiển thị danh sách sản phẩm đã mua
    for (size_t i = 0; i < luaChonSanPham.size(); ++i) 
    {
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
    cout << "Tong so tien can thanh toan: " << tongTien << " VND" << endl;

    char luaChon;
    cout << "Ban co muon thanh toan khong? (y/n): ";
    cin >> luaChon;
    
    if (luaChon == 'y' || luaChon == 'Y') 
    {
        if(user.getCredits() >= tongTien)
        {
            string fileName;
            fileName = "database/history/" + user.getUsername() + ".txt";
            ofstream fileHoaDon(fileName, ios::app);
            if(!fileHoaDon.is_open())
            {
                cout<<"Khong the mo file hoa don!"<<endl;
                return;
            }
            for (size_t i = 0; i < luaChonSanPham.size(); ++i) 
            {
                int index = luaChonSanPham[i];
                double giaSanPham = danhSachSanPham[index]->getGia();
                int soLuong = soLuongMua[i];
                double thanhTien = giaSanPham * soLuong;
                fileHoaDon<<danhSachSanPham[index]->getTen()<<" "<<giaSanPham<<" "<<soLuong<< " "<<thanhTien<< " "<< getCurrentDate()<<endl;
            }
            fileHoaDon.close();

            cout << "Thanh toan thanh cong! Cam on ban!\n";
            user.accountDeposit(-tongTien);
            luuSanPhamVaoFile("database/product.txt"); // Cập nhật file sản phẩm
            cart.clear(); // Xóa giỏ hàng
            quantities.clear(); // Xóa số lượng
        }
        else {
            cout<<"Ban khong du "<<tongTien<<"$ de thanh toan, tong tien cua ban: "<<user.getCredits() <<"$."<< endl;
            cart.clear(); // Xóa giỏ hàng
            quantities.clear(); // Xóa số lượng       
        }
    } else {
        cout << "Huy thanh toan!\n";
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
    cout << "Chon loai san pham muon nhap:\n";
    cout << "1. Thuc pham\n";
    cout << "2. Do uong\n";
    cout << "3. Thoi trang\n";
    cout << "4. Do gia dung\n";
    cout << "5. Do dien tu\n";
    cout << "6. thoat\n";
    int luaChonLoai;
    cinInt >> luaChonLoai;
     if (luaChonLoai == 6) { // Nếu người dùng chọn thoát
            cout << "Da thoat khoi chuc nang nhap hang.\n";
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

void nhapSanPham(LoaiSanPham loai) {
    cout << "Danh sach san pham hien co:\n";
    vector<int> danhSachHienThi; // Lưu các chỉ mục của sản phẩm hợp lệ được hiển thị
    bool found = false;

    // Hiển thị các sản phẩm thuộc loại được chọn
    for (size_t i = 0; i < danhSachSanPham.size(); ++i) {
        if (((loai == THUC_PHAM && dynamic_cast<ThucPham*>(danhSachSanPham[i])) ||
            (loai == DO_UONG && dynamic_cast<DoUong*>(danhSachSanPham[i])) ||
            (loai == THOI_TRANG && dynamic_cast<ThoiTrang*>(danhSachSanPham[i])) ||
            (loai == DO_GIA_DUNG && dynamic_cast<DoGiaDung*>(danhSachSanPham[i])) ||
            (loai == DO_DIEN_TU && dynamic_cast<DoDienTu*>(danhSachSanPham[i])))) {
            
            cout << danhSachHienThi.size() + 1 << ". " << danhSachSanPham[i]->getTen() 
                 << " (So luong: " << danhSachSanPham[i]->getSoLuong() << ") " 
                 << danhSachSanPham[i]->getGia() << " VND" << endl;
            danhSachHienThi.push_back(i); // Lưu chỉ mục của sản phẩm hợp lệ
            found = true;
        }
    }

    if (!found) {
        cout << "Khong co san pham nao trong kho. Ban co muon nhap san pham moi khong? (y/n): ";
        char nhapMoi;
        cin >> nhapMoi;
        if (nhapMoi == 'y' || nhapMoi == 'Y') {
            // Gọi hàm nhập sản phẩm mới theo loại
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
                danhSachSanPham.push_back(sanPhamMoi);
                luuSanPhamVaoFile("database/product.txt");
                cout << "San pham moi da duoc nhap thanh cong!\n";
            }
        }
        return; // Thoát hàm sau khi nhập hàng mới
    }

    // Nếu có sản phẩm, tiếp tục nhập số lượng vào sản phẩm hiện có hoặc thêm mới
    while (true) {
        int luaChon;
        cout << "\nChon san pham muon nhap (nhap so tuong ung, hoac 0 de dung, hoac -1 de nhap san pham moi): ";
        cin >> luaChon;

        if (luaChon == 0){
            this_thread::sleep_for(chrono::milliseconds(5000));
            system("cls");
            break; // Kết thúc nếu người dùng nhập 0
        } 
        if (luaChon == -1) {
            // Nhập thông tin cho sản phẩm mới
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
                danhSachSanPham.push_back(sanPhamMoi);
                luuSanPhamVaoFile("database/product.txt");
                cout << "San pham moi da duoc nhap thanh cong!\n";
            }
            continue; // Tiếp tục vòng lặp
        }

        if (luaChon > 0 && luaChon <= danhSachHienThi.size()) {
            int indexSanPham = danhSachHienThi[luaChon - 1]; // Lấy chỉ mục thực của sản phẩm từ danhSachHienThi
            int soLuongNhap;
            cout << "Nhap so luong muon them: ";
            cin >> soLuongNhap;

            if (soLuongNhap > 0) {
                int soLuongMoi = danhSachSanPham[indexSanPham]->getSoLuong() + soLuongNhap;
                danhSachSanPham[indexSanPham]->setSoLuong(soLuongMoi);
                cout << "Da them " << soLuongNhap << " vao " << danhSachSanPham[indexSanPham]->getTen() 
                     << ". So luong hien tai: " << soLuongMoi << ".\n";
                luuSanPhamVaoFile("database/product.txt");
            } else {
                cout << "So luong phai lon hon 0.\n";
            }
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    }
}
void xoaHang(){
    docSanPhamTuFile("database/product.txt");

    while(true){
    cout << "Chon loai san pham muon xoa:\n";
    cout << "1. Thuc pham\n";
    cout << "2. Do uong\n";
    cout << "3. Thoi trang\n";
    cout << "4. Do gia dung\n";
    cout << "5. Do dien tu\n";
    cout << "6. thoat\n";
    int luaChonLoai;
    cinInt >> luaChonLoai;
     if (luaChonLoai == 6) { // Nếu người dùng chọn thoát
            cout << "Da thoat khoi chuc nang xoa hang.\n";
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
    vector<int> danhSachHienThi; // Lưu các chỉ mục của sản phẩm hợp lệ được hiển thị
    bool found = false;
    
    // Hiển thị các sản phẩm thuộc loại được chọn
    cout << "==================================================================\n";
    cout << "| STT | Ten san pham                   | So luong | Gia (VND)    |\n";
    cout << "==================================================================\n";

    for (size_t i = 0; i < danhSachSanPham.size(); ++i) {
        if (((loai == THUC_PHAM && dynamic_cast<ThucPham*>(danhSachSanPham[i])) ||
            (loai == DO_UONG && dynamic_cast<DoUong*>(danhSachSanPham[i])) ||
            (loai == THOI_TRANG && dynamic_cast<ThoiTrang*>(danhSachSanPham[i])) ||
            (loai == DO_GIA_DUNG && dynamic_cast<DoGiaDung*>(danhSachSanPham[i])) ||
            (loai == DO_DIEN_TU && dynamic_cast<DoDienTu*>(danhSachSanPham[i]))) && danhSachSanPham[i]->getSoLuong() != 0) {

            cout << "| " << setw(3) << left << danhSachHienThi.size() + 1 << " | ";
            cout << setw(30) << left << danhSachSanPham[i]->getTen() << " | ";
            cout << setw(8) << left << danhSachSanPham[i]->getSoLuong() << " | ";
            cout << setw(12) << left << danhSachSanPham[i]->getGia() << " |\n";

            danhSachHienThi.push_back(i); // Lưu chỉ mục của sản phẩm hợp lệ
            found = true;
        }
    }
    
    cout << "==================================================================\n";
	int count=0;
    if (!found) {
        cout << "Khong co san pham nao trong kho.\n";
        count++;
    }

    // Lặp để người dùng mua nhiều sản phẩm
    while (true&&count==0) {
        int luaChon;
        cout << "\nChon san pham muon mua (nhap so tuong ung, hoac 0 de dung mua): ";
        cinInt >> luaChon;

        if (luaChon == 0){
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        break;
        }  

    if (luaChon > 0 && luaChon <= danhSachHienThi.size()) {
    int soLuong;
    cout << "Nhap so luong muon mua: ";
    cinInt >> soLuong;

    // Kiểm tra nếu số lượng là 0
    if (soLuong <= 0) {
        cout << "So luong phai lon hon 0.\n";
    } else {
        // Kiểm tra xem có đủ số lượng trong kho không
        int indexSanPham = danhSachHienThi[luaChon - 1];
        if (soLuong <= danhSachSanPham[indexSanPham]->getSoLuong()) {
            cart.push_back(indexSanPham); // Thêm sản phẩm vào giỏ hàng
            quantities.push_back(soLuong);
            danhSachSanPham[indexSanPham]->setSoLuong(danhSachSanPham[indexSanPham]->getSoLuong() - soLuong);
            cout << "Da them " << soLuong << " " << danhSachSanPham[indexSanPham]->getTen() << " vao gio hang.\n";
        } else {
            cout << "Khong du so luong san pham trong kho.\n";
        }
    }
} else {
    cout << "Lua chon khong hop le.\n";
}
    }

    // Xác nhận các sản phẩm đã mua
    if (!cart.empty()) {
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        cout << "\nBan da chon mua cac san pham sau:\n";
        for (size_t i = 0; i < cart.size(); ++i) {
            int index = cart[i];
            cout << "- " << danhSachSanPham[index]->getTen() << ": " << quantities[i] 
                 << " thanh tien: "<< fixed << setprecision(1) << quantities[i] * danhSachSanPham[index]->getGia() << " VND" << endl;
        }

        int luaChonTiep;
        cout << "\n1. Toi quay thanh toan\n2. Toi quay khac de tiep tuc mua sam\nLua chon cua ban: ";
        cinInt >> luaChonTiep;

        if (luaChonTiep == 1) {
            cout << "Dang di toi quay thanh toan...\n";
            system("cls");
            thanhToan(cart, quantities, user); // Gọi hàm thanh toán
        } else if (luaChonTiep == 2) {
            cout << "Dang di toi quay khac...\n";
            this_thread::sleep_for(chrono::milliseconds(500));
            system("cls");
            chonQuayKhac(user);
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    } else {
        cout << "Ban chua mua san pham nao.\n";
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
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong the mo file de doc.\n";
        return;
    }

    string loai, ten;
    double gia;
    int soLuong;

    while (file.good()) {
        getline(file, loai, ',');
        getline(file, ten, ',');
        file >> gia;
        file.ignore(); // Bỏ qua dấu phẩy
        file >> soLuong;
        file.ignore(); // Bỏ qua ký tự newline

        // Tạo đối tượng sản phẩm tương ứng dựa vào loại
        SanPham* sanPham = nullptr;

        if (loai == "ThucPham") {
            sanPham = new ThucPham();
        } else if (loai == "DoUong") {
            sanPham = new DoUong();
        } else if (loai == "ThoiTrang") {
            sanPham = new ThoiTrang();
        } else if (loai == "DoGiaDung") {
            sanPham = new DoGiaDung();
        } else if (loai == "DoDienTu") {
            sanPham = new DoDienTu();
        }

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
    cout << "*********************************************************\n";
    cout << "*                        SIEU THI                       *\n";
    cout << "*********************************************************\n";
    cout << "*                                                       *\n";
    cout << "*   [QUAY THU NGAN]                                     *\n";
    cout << "*   +----------------------+                            *                  +-------------------------------------+\n";
    cout << "*   |   KHACH HANG         |                            *                  | Thong tin khach hang:               |\n";
    cout << "*   |   TINH TIEN          |                            *                  |-------------------------------------|\n";
    cout << "*   +----------------------+                            *                  | Ten: "  << setw(31) << left << user.getUsername() << "|\n";
    cout << "*                                                       *                  | So du: "  << setw(26) << left << fixed << setprecision(2) << user.getCredits() << "$  |\n";
    cout << "*                                                       *                  +-------------------------------------+\n";
    cout << "*   +----------------------+   +--------------------+   *\n";
    cout << "*   |    KHU DO UONG       |   | KHU THOI TRANG     |   *\n";
    cout << "*   +----------------------+   +--------------------+   *\n";
    cout << "*   |  - Nuoc co ga        |   |  - Quan ao         |   *\n";
    cout << "*   |  - Nuoc ep trai cay  |   |  - Phu kien        |   *\n";
    cout << "*   |  - Sua tuoi          |   |  - Giay dep        |   *\n";
    cout << "*   +----------------------+   +--------------------+   *\n";
    cout << "*                                                       *\n";
    cout << "*   +----------------------+   +--------------------+   *\n";
    cout << "*   |   KHU THUC PHAM      |   | KHU TONG HOP       |   *\n";
    cout << "*   +----------------------+   +--------------------+   *\n";
    cout << "*   |  - Thit tuoi         |   |  - Do gia dung     |   *\n";
    cout << "*   |  - Ca dong lanh      |   |  - Do dien tu      |   *\n";
    cout << "*   |  - Rau cu tuoi       |   |                    |   *\n";
    cout << "*   +----------------------+   +--------------------+   *\n";
    cout << "*                        [CUA RA]                       *\n";
    cout << "*********************************************************\n";

    }   
};
