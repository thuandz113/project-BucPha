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

//============================Account==========================//
using namespace std;
class SanPham {
protected:
    string ten;         // Tên sản phẩm
    int soLuong;        // Số lượng sản phẩm
    double gia;         // Giá sản phẩm

public:
    virtual string getLoai() const = 0; // Trả về loại sản phẩm
    virtual void nhapThongTin() = 0; // Nhập thông tin sản phẩm
    virtual void luuThongTinVaoFile(ofstream& file) = 0; // Lưu thông tin vào file

    string getTen() const { return ten; } // Lấy tên sản phẩm
    int getSoLuong() const { return soLuong; } // Lấy số lượng
    void setSoLuong(int sl) { soLuong = sl; } // Cập nhật số lượng
    double getGia() const { return gia; } // Lấy giá sản phẩm

    virtual ~SanPham() {} // Destructor ảo
};

class ThucPham : public SanPham {
private:
    string hanSuDung;

public:
    string getLoai() const override { return "ThucPham"; }

    void nhapThongTin() override {
        cout << "Nhap ten thuc pham: ";
        cin >> ten;
        cout << "Nhap gia: ";
        cin >> gia;
        cout << "Nhap so luong: ";
        cin >> soLuong;
        cout << "Nhap han su dung: ";
        cin >> hanSuDung;
    }

    void luuThongTinVaoFile(ofstream& file) override {
        file << "thucpham," << ten << "," << gia << "," << soLuong << "," << hanSuDung << endl;
    }

    void khoiTaoTuFile(const string& ten, double gia, int soLuong, const string& hanSuDung) {
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;
        this->hanSuDung = hanSuDung;
    }
};

class DoUong : public SanPham {
private:
    bool coCon;

public:
    string getLoai() const override { return "DoUong"; }

    void nhapThongTin() override {
        cout << "Nhap ten do uong: ";
        cin >> ten;
        cout << "Nhap gia: ";
        cin >> gia;
        cout << "Nhap so luong: ";
        cin >> soLuong;
        cout << "Co con (1: yes, 0: no): ";
        cin >> coCon;
    }

    void luuThongTinVaoFile(ofstream& file) override {
        file << "douong," << ten << "," << gia << "," << soLuong << "," << coCon << endl;
    }

    void khoiTaoTuFile(const string& ten, double gia, int soLuong, bool coCon) {
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;
        this->coCon = coCon;
    }
};

class ThoiTrang : public SanPham {
private:
    string size;

public:
    string getLoai() const override { return "ThoiTrang"; }

    void nhapThongTin() override {
        cout << "Nhap ten thoi trang: ";
        cin >> ten;
        cout << "Nhap gia: ";
        cin >> gia;
        cout << "Nhap so luong: ";
        cin >> soLuong;
        cout << "Nhap size: ";
        cin >> size;
    }

    void luuThongTinVaoFile(ofstream& file) override {
        file << "thoitrang," << ten << "," << gia << "," << soLuong << "," << size << endl;
    }

    void khoiTaoTuFile(const string& ten, double gia, int soLuong, const string& size) {
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;
        this->size = size;
    }
};

class DoGiaDung : public SanPham {
private:
    string chatLieu;

public:
    string getLoai() const override { return "DoGiaDung"; }

    void nhapThongTin() override {
        cout << "Nhap ten do gia dung: ";
        cin >> ten;
        cout << "Nhap gia: ";
        cin >> gia;
        cout << "Nhap so luong: ";
        cin >> soLuong;
        cout << "Nhap chat lieu: ";
        cin >> chatLieu;
    }

    void luuThongTinVaoFile(ofstream& file) override {
        file << "dogiadung," << ten << "," << gia << "," << soLuong << "," << chatLieu << endl;
    }

    void khoiTaoTuFile(const string& ten, double gia, int soLuong, const string& chatLieu) {
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;
        this->chatLieu = chatLieu;
    }
};

class DoDienTu : public SanPham {
private:
    string hangSX;

public:
    string getLoai() const override { return "DoDienTu"; }

    void nhapThongTin() override {
        cout << "Nhap ten do dien tu: ";
        cin >> ten;
        cout << "Nhap gia: ";
        cin >> gia;
        cout << "Nhap so luong: ";
        cin >> soLuong;
        cout << "Nhap hang san xuat: ";
        cin >> hangSX;
    }

    void luuThongTinVaoFile(ofstream& file) override {
        file << "dodientu," << ten << "," << gia << "," << soLuong << "," << hangSX << endl;
    }

    void khoiTaoTuFile(const string& ten, double gia, int soLuong, const string& hangSX) {
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;
        this->hangSX = hangSX;
    }
};
class QuanLyChucNang {
private:
    vector<SanPham*> danhSachSanPham;
    
public:

    enum LoaiSanPham {
        THUC_PHAM,
        DO_UONG,
        THOI_TRANG,
        DO_GIA_DUNG,
        DO_DIEN_TU
    };

    void chonQuayKhac(UserAccount &user) {
        cout << "Chon loai san pham muon mua:\n";
        cout << "1. Thuc pham\n";
        cout << "2. Do uong\n";
        cout << "3. Thoi trang\n";
        cout << "4. Do gia dung\n";
        cout << "5. Do dien tu\n";
        
        int luaChonLoai;
        cin >> luaChonLoai;

        while (luaChonLoai < 1 || luaChonLoai > 5) {
            cout << "Lua chon khong hop le. Vui long nhap tu 1 den 5: ";
            cin >> luaChonLoai;
        }

        switch (luaChonLoai) {
            case 1: muaSanPham(THUC_PHAM, user); break;
            case 2: muaSanPham(DO_UONG, user); break;
            case 3: muaSanPham(THOI_TRANG, user); break;
            case 4: muaSanPham(DO_GIA_DUNG, user); break;
            case 5: muaSanPham(DO_DIEN_TU, user); break;
        }
    }
//     void thanhToan(vector<int>& luaChonSanPham, vector<int>& soLuongMua) {
//         double tongTien = 0.0;

//         cout << "Danh sach san pham da mua:\n";
//         for (size_t i = 0; i < luaChonSanPham.size(); ++i) {
//             int index = luaChonSanPham[i];
//             cout << "- " << danhSachSanPham[index]->getTen() << ": " << soLuongMua[i] 
//                  << " x " << danhSachSanPham[index]->getGia() << " VND" << endl;
//             tongTien += danhSachSanPham[index]->getGia() * soLuongMua[i];
//         }

//         cout << "Tong so tien can thanh toan: " << tongTien << " VND" << endl;

//         char luaChon;
//         cout << "Ban co muon thanh toan khong? (y/n): ";
//         cin >> luaChon;
        
//         if (luaChon == 'y' || luaChon == 'Y') {
//             cout << "Thanh toan thanh cong! Cam on ban!\n";
//                 luuSanPhamVaoFile("database/product.txt");
//         } else {
//             cout << "Huy thanh toan!\n";
//         }
//     }
    

//     void muaSanPham(LoaiSanPham loai) {
//     cout << "Danh sach san pham hien co:\n";
//     vector<int> luaChonSanPham; // Lưu các chỉ mục sản phẩm đã chọn
//     vector<int> soLuongMua; // Lưu số lượng sản phẩm đã chọn
//     vector<int> danhSachHienThi; // Lưu các chỉ mục của sản phẩm hợp lệ được hiển thị
//     bool found = false;

//     // Hiển thị các sản phẩm thuộc loại được chọn
//     for (size_t i = 0; i < danhSachSanPham.size(); ++i) {
//         if (((loai == THUC_PHAM && dynamic_cast<ThucPham*>(danhSachSanPham[i])) ||
//             (loai == DO_UONG && dynamic_cast<DoUong*>(danhSachSanPham[i])) ||
//             (loai == THOI_TRANG && dynamic_cast<ThoiTrang*>(danhSachSanPham[i])) ||
//             (loai == DO_GIA_DUNG && dynamic_cast<DoGiaDung*>(danhSachSanPham[i])) ||
//             (loai == DO_DIEN_TU && dynamic_cast<DoDienTu*>(danhSachSanPham[i])))&&danhSachSanPham[i]->getSoLuong()!=0) {
            
//             cout << danhSachHienThi.size() + 1 << ". " << danhSachSanPham[i]->getTen() 
//                  << " (So luong: " << danhSachSanPham[i]->getSoLuong() << ") "<<danhSachSanPham[i]->getGia()<<"vnd" << endl;
//             danhSachHienThi.push_back(i); // Lưu chỉ mục của sản phẩm hợp lệ
//             found = true;
//         }
//     }

//     if (!found) {
//         cout << "Khong co san pham nao trong kho.\n";
//         return;
//     }

//     // Lặp để người dùng mua nhiều sản phẩm
//     while (true) {
//         int luaChon;
//         cout << "\nChon san pham muon mua (nhap so tuong ung, hoac 0 de dung mua): ";
//         cin >> luaChon;

//         if (luaChon == 0) break; // Kết thúc nếu người dùng nhập 0

//         if (luaChon > 0 && luaChon <= danhSachHienThi.size()) {
//             int soLuong;
//             cout << "Nhap so luong muon mua: ";
//             cin >> soLuong;

//             // Kiểm tra xem có đủ số lượng trong kho không
//             int indexSanPham = danhSachHienThi[luaChon - 1];
//             if (soLuong <= danhSachSanPham[indexSanPham]->getSoLuong()) {
//                 luaChonSanPham.push_back(indexSanPham);
//                 soLuongMua.push_back(soLuong);
//                 danhSachSanPham[indexSanPham]->setSoLuong(danhSachSanPham[indexSanPham]->getSoLuong() - soLuong);
//                 cout << "Da them " << soLuong << " " << danhSachSanPham[indexSanPham]->getTen() << " vao gio hang.\n";
//             } else {
//                 cout << "Khong du so luong san pham trong kho.\n";
//             }
//         } else {
//             cout << "Lua chon khong hop le.\n";
//         }
//     }

//     // Xác nhận các sản phẩm đã mua
//     if (!luaChonSanPham.empty()) {
//         cout << "\nBan da chon mua cac san pham sau:\n";
//         for (size_t i = 0; i < luaChonSanPham.size(); ++i) {
//             int index = luaChonSanPham[i];
//             cout << "- " << danhSachSanPham[index]->getTen() << ": " << soLuongMua[i]<<" thanh tien: "<< soLuongMua[i]*danhSachSanPham[index]->getGia()<<"vnd" << endl;
//         }

//         int luaChonTiep;
//         cout << "\n1. Toi quay thanh toan\n2. Toi quay khac de tiep tuc mua sam\nLua chon cua ban: ";
//         cin >> luaChonTiep;

//         if (luaChonTiep == 1) {
//             cout << "Dang di toi quay thanh toan...\n";
// 			this_thread::sleep_for(chrono::milliseconds(1000));
//             system("cls");
//             thanhToan(luaChonSanPham, soLuongMua);
//         } else if (luaChonTiep == 2) {
            
//             cout << "Dang di toi quay khac...\n";
//             this_thread::sleep_for(chrono::milliseconds(1000));
//             system("cls");
//             chonQuayKhac();

//         } else {
//             cout << "Lua chon khong hop le.\n";
//         }
//     } else {
//         cout << "Ban chua mua san pham nao.\n";
//     }
// }
    void thanhToan(vector<int>& luaChonSanPham, vector<int>& soLuongMua, UserAccount &user) {
    double tongTien = 0.0;

    // Tiêu đề hóa đơn
    cout << "======================= HOA DON ===========================================\n";
    cout << left << setw(30) << "Ten San Pham" 
         << setw(10) << "So Luong" 
         << setw(15) << "Gia (VND)" 
         << setw(15) << "Thanh Tien (VND)" << endl;
    cout << "===========================================================================\n";

    // Hiển thị danh sách sản phẩm đã mua
    for (size_t i = 0; i < luaChonSanPham.size(); ++i) {
        int index = luaChonSanPham[i];
        double giaSanPham = danhSachSanPham[index]->getGia();
        int soLuong = soLuongMua[i];
        double thanhTien = giaSanPham * soLuong;
        tongTien += thanhTien;

        // In ra từng sản phẩm
        cout << left << setw(30) << danhSachSanPham[index]->getTen() 
             << setw(10) << soLuong 
             << setw(15) << giaSanPham 
             << setw(15) << thanhTien << endl;
    }

    cout << "===========================================================================\n";
    cout << "Tong so tien can thanh toan: " << tongTien << " VND" << endl;

    char luaChon;
    cout << "Ban co muon thanh toan khong? (y/n): ";
    cin >> luaChon;
    
    if (luaChon == 'y' || luaChon == 'Y') 
    {
        if(user.getCredits() >= tongTien)
        {
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
    }
}


// Khai báo giỏ hàng
vector<int> cart; // Giỏ hàng tạm thời lưu các chỉ mục sản phẩm đã chọn
vector<int> quantities; // Số lượng tương ứng với từng sản phẩm trong giỏ hàng

void muaSanPham(LoaiSanPham loai, UserAccount &user) {
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
                 << " (So luong: " << danhSachSanPham[i]->getSoLuong() << ") " << danhSachSanPham[i]->getGia() << " vnd" << endl;
            danhSachHienThi.push_back(i); // Lưu chỉ mục của sản phẩm hợp lệ
            found = true;
        }
    }
	int count=0;
    if (!found) {
        cout << "Khong co san pham nao trong kho.\n";
        count++;
    }

    // Lặp để người dùng mua nhiều sản phẩm
    while (true&&count==0) {
        int luaChon;
        cout << "\nChon san pham muon mua (nhap so tuong ung, hoac 0 de dung mua): ";
        cin >> luaChon;

        if (luaChon == 0) break; // Kết thúc nếu người dùng nhập 0

        if (luaChon > 0 && luaChon <= danhSachHienThi.size()) {
            int soLuong;
            cout << "Nhap so luong muon mua: ";
            cin >> soLuong;

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
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    }

    // Xác nhận các sản phẩm đã mua
    if (!cart.empty()) {
        cout << "\nBan da chon mua cac san pham sau:\n";
        for (size_t i = 0; i < cart.size(); ++i) {
            int index = cart[i];
            cout << "- " << danhSachSanPham[index]->getTen() << ": " << quantities[i] 
                 << " thanh tien: "<< fixed << setprecision(1) << quantities[i] * danhSachSanPham[index]->getGia() << " vnd" << endl;
        }

        int luaChonTiep;
        cout << "\n1. Toi quay thanh toan\n2. Toi quay khac de tiep tuc mua sam\nLua chon cua ban: ";
        cin >> luaChonTiep;

        if (luaChonTiep == 1) {
            cout << "Dang di toi quay thanh toan...\n";
            system("cls");
            thanhToan(cart, quantities, user); // Gọi hàm thanh toán
        } else if (luaChonTiep == 2) {
            cout << "Dang di toi quay khac...\n";
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

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string loai, ten;
            double gia;
            int soLuong;

            if (getline(iss, loai, ',') && getline(iss, ten, ',') &&
                iss >> gia && iss.ignore() && iss >> soLuong) {
                if (loai == "ThucPham") {
                    ThucPham* tp = new ThucPham();
                    tp->khoiTaoTuFile(ten, gia, soLuong, ""); // Bạn cần sửa đổi để đưa thông tin hết hạn vào
                    danhSachSanPham.push_back(tp);
                } else if (loai == "DoUong") {
                    bool coCon;
                    iss.ignore(); // Bỏ qua dấu phẩy
                    iss >> coCon; // Đọc thông tin coCon
                    DoUong* du = new DoUong();
                    du->khoiTaoTuFile(ten, gia, soLuong, coCon);
                    danhSachSanPham.push_back(du);
                } else if (loai == "ThoiTrang") {
                    string size;
                    iss.ignore(); // Bỏ qua dấu phẩy
                    getline(iss, size);
                    ThoiTrang* tt = new ThoiTrang();
                    tt->khoiTaoTuFile(ten, gia, soLuong, size);
                    danhSachSanPham.push_back(tt);
                } else if (loai == "DoGiaDung") {
                    string thuongHieu;
                    iss.ignore(); // Bỏ qua dấu phẩy
                    getline(iss, thuongHieu); 
                    DoGiaDung* dg = new DoGiaDung();
                    dg->khoiTaoTuFile(ten, gia, soLuong, thuongHieu);
                    danhSachSanPham.push_back(dg);
                } else if (loai == "DoDienTu") {
                    string congSuat;
                    iss.ignore(); // Bỏ qua dấu phẩy
                    getline(iss, congSuat);
                    DoDienTu* dt = new DoDienTu();
                    dt->khoiTaoTuFile(ten, gia, soLuong, congSuat);
                    danhSachSanPham.push_back(dt);
                }
            }
        }

        file.close();
        cout << "Da doc danh sach san pham tu file " << tenFile << " thanh cong.\n";
        system("cls");
    }

    ~QuanLyChucNang() {
        for (auto sp : danhSachSanPham) {
            delete sp; // Giải phóng bộ nhớ
        }
    }
    void veSieuThi(UserAccount user) {
    cout << "*   +----------------------+                        *                    Thong tin khach hang:\n";
    cout << "*   |   KHACH HANG         |                        *                    Ten: "<<user.getUsername()<<"\n";
    cout << "*   |   TINH TIEN          |                        *                    So du: "<<user.getCredits()<<"\n";
    cout << "*   +----------------------+                        *\n";
    cout << "*                                                   *\n";
    cout << "*   +----------------------+   +---------------+    *\n";
    cout << "*   |    KHU DO UONG       |   | KHU THOI TRANG|    *\n";
    cout << "*   +----------------------+   +---------------+    *\n";
    cout << "*   |  - Nuoc co ga        |   |  - Quan ao    |    *\n";
    cout << "*   |  - Nuoc ep trai cay  |   |  - Phu kien   |    *\n";
    cout << "*   |  - Sua tuoi          |   |  - Giay dep   |    *\n";
    cout << "*   +----------------------+   +---------------+    *\n";
    cout << "*                                                   *\n";
    cout << "*   +----------------------+   +----------------+   *\n";
    cout << "*   |   KHU THUC PHAM      |   | KHU TONG HOP   |   *\n";
    cout << "*   +----------------------+   +----------------+   *\n";
    cout << "*   |  - Thi tuoi          |   |  - Do gia dung |   *\n";
    cout << "*   |  - Ca dong lanh      |   |  - Do dien tu  |   *\n";
    cout << "*   |  - Rau cu tuoi       |   |                |   *\n";
    cout << "*   +----------------------+   +----------------+   *\n";
    cout << "*                   [CUA RA]                        *\n";
    cout << "*****************************************************\n";
    }   
};
