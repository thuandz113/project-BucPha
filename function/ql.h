#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "doiTuong.h"

string maskString(const string& str) 
{
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        result += '*';
    }
    return result;
}
class InputStream {
public:
    template <typename T>
    InputStream& operator>>(T& value) {
        while (true) {
            cin >> value;
            if (cin.fail()) 
			{
				cout<<"\nBan vua nhap chu thay vi nhap so, hay nhap lai:";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }
        return *this;
    }
};
InputStream cinInt;

void printInBox(const string& content, int width) {
    int padding = (width - 4 - content.size()) / 2;
    cout << "|" << string(padding, ' ') << content << string(width - 4 - padding - content.size(), ' ') << "  |" << endl;
}

void printBorder(int width) {
    cout << "+" << string(width - 2, '-') << "+" << endl;
}
void inputPass(string &password) {
    char ch;
    password = "";
    cout<<"password: ";
    while (true) {
        ch = _getch();  // Đọc ký tự không hiện trên màn hình
        if (ch == '\r') { // Dừng khi nhấn Enter
            break;
        } else if (ch == '\b') { // Xóa ký tự cuối khi nhấn Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Xóa ký tự * trên màn hình
            }
        } else {
            password += ch; // Thêm ký tự vào chuỗi mật khẩu
            cout << '*'; // In dấu * thay cho ký tự đã nhập
        }
    }
    cout << endl;
}

string replaceSpace(const string& s) {
    string result = s;
    for (char& c : result) {
        if (c == ' ') {
            c = '_';
        }
    }
    return result;
}
string replaceUnderscore(const string& s) {
    string result = s;
    for (char& c : result) {
        if (c == '_') {
            c = ' ';
        }
    }
    return result;
}
bool updateAccount(UserAccount user) {
    ifstream fileIn("database/account.txt");
    if (!fileIn) {
        cout << "Khong the mo file Account.txt!" << endl;
        return false;
    }

    ofstream fileOut("database/temp.txt");
    if (!fileOut) {
        cout << "Khong the tao file tam!" << endl;
        fileIn.close();
        return false;
    }

    string userTemp, passTemp, number, address, line;
    int roles, credits, sex;
    bool found = false;

    fileOut << "Username/Password/Roles/Credits/Sex/Number/Address" << endl;
    
    getline(fileIn, line);
    
    while (fileIn >> userTemp >> passTemp >> roles >> credits >> sex >> number >> address) {
        if (replaceUnderscore(userTemp) == user.getUsername()) {
            fileOut << replaceSpace(userTemp) << " " 
                    << user.getPassword() << " " 
                    << user.getRoles() << " " 
                    << user.getCredits() << " " 
                    << user.getSex() << " " 
                    << user.getNumber() << " " 
                    << user.getAddress() << endl;
            found = true;
        } else {
            fileOut << replaceSpace(userTemp) << " " << passTemp << " " 
                    << roles << " " << credits << " " << sex << " " 
                    << number << " " << address << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    // Kiểm tra và thay thế file cũ
    if (remove("database/account.txt") != 0) {
        cout << "Khong the xoa file Account.txt!" << endl;
        return false;
    }
    if (rename("database/temp.txt", "database/account.txt") != 0) {
        cout << "Khong the doi ten file tam!" << endl;
        return false;
    }

    return found;
}

string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int day = ltm->tm_mday;
    int month = 1 + ltm->tm_mon;
    int year = 1900 + ltm->tm_year;

    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}
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
