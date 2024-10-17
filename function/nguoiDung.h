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
    void setGia(double giaSanPham) {
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
        cin >> gia;
        cout << "Nhap so luong: ";
        cin >> soLuong;
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
        cin >> gia;
        cout << "Nhap so luong: ";
        cin >> soLuong;

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
        cin >> gia;
        cout << "Nhap so luong: ";
        cin >> soLuong;

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
        cin >> gia;
        cout << "Nhap so luong: ";
        cin >> soLuong;

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
        cin >> gia;
        cout << "Nhap so luong: ";
        cin >> soLuong;

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
    string fileName;
    fileName = "database/history/" + user.getUsername() + ".txt";
    ofstream fileHoaDon(fileName);
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
        tongTien += thanhTien;

        // In ra từng sản phẩm
        cout << left << setw(30) << danhSachSanPham[index]->getTen() 
             << setw(10) << soLuong 
             << setw(15) << giaSanPham 
             << setw(15) << thanhTien << endl;
        fileHoaDon<<danhSachSanPham[index]->getTen()<<" "<<giaSanPham<<" "<<soLuong<< " "<<thanhTien<< " "<< getCurrentDate()<<endl;
    }
    fileHoaDon.close();

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


void nhapHang() {
    // Đọc danh sách sản phẩm từ file trước
    docSanPhamTuFile("database/product.txt");

    while(true){
    cout << "Chon loai san pham muon nhap:\n";
    cout << "1. Thuc pham\n";
    cout << "2. Do uong\n";
    cout << "3. Thoi trang\n";
    cout << "4. Do gia dung\n";
    cout << "5. Do dien tu\n";
    cout << "6. thoat\n";
    int luaChonLoai;
    cin >> luaChonLoai;
     if (luaChonLoai == 6) { // Nếu người dùng chọn thoát
            cout << "Da thoat khoi chuc nang nhap hang.\n";
            break; // Thoát khỏi vòng lặp
        }
    // Kiểm tra lựa chọn đầu vào
    while (luaChonLoai < 1 || luaChonLoai > 6) {
        cout << "Lua chon khong hop le. Vui long nhap tu 1 den 6: ";
        cin >> luaChonLoai;
    }

    SanPham* sanPhamMoi = nullptr; // Con trỏ sản phẩm mới

    switch (luaChonLoai) {
        case 1:
            sanPhamMoi = new ThucPham();
            break;
        case 2:
            sanPhamMoi = new DoUong();
            break;
        case 3:
            sanPhamMoi = new ThoiTrang();
            break;
        case 4:
            sanPhamMoi = new DoGiaDung();
            break;
        case 5:
            sanPhamMoi = new DoDienTu();
            break;
        default:
            cout << "Khong the tao san pham moi.\n";
            return; // Không cần tiếp tục nếu lựa chọn không hợp lệ
    }

    // Nhập thông tin cho sản phẩm mới
    if (sanPhamMoi) {
        sanPhamMoi->nhapThongTin(); // Nhập thông tin cho sản phẩm mới

        // Kiểm tra xem sản phẩm đã tồn tại trong danh sách chưa
        bool tonTai = false;
        for (auto& sp : danhSachSanPham) {
            if (sp->getTen() == sanPhamMoi->getTen()) { // So sánh tên sản phẩm
                sp->setSoLuong(sp->getSoLuong() + sanPhamMoi->getSoLuong()); // Cập nhật số lượng
                sp->setGia(sanPhamMoi->getGia()); // Cập nhật lại giá
                tonTai = true;
                cout << "San pham da ton tai, da cap nhat so luong va gia!\n";
                break;
            }
        }

        // Nếu sản phẩm không tồn tại, thêm sản phẩm mới vào danh sách
        if (!tonTai) {
            danhSachSanPham.push_back(sanPhamMoi);
            cout << "Da nhap hang thanh cong!\n";
        } else {
            delete sanPhamMoi; // Giải phóng bộ nhớ nếu sản phẩm đã tồn tại
        }

        // Cập nhật file sản phẩm
        luuSanPhamVaoFile("database/product.txt");
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
    cin >> luaChonLoai;
     if (luaChonLoai == 6) { // Nếu người dùng chọn thoát
            cout << "Da thoat khoi chuc nang xoa hang.\n";
            break; // Thoát khỏi vòng lặp
        }
    // Kiểm tra lựa chọn đầu vào
    while (luaChonLoai < 1 || luaChonLoai > 6) {
        cout << "Lua chon khong hop le. Vui long nhap tu 1 den 6: ";
        cin >> luaChonLoai;
    }
    switch (luaChonLoai) {
            case 1: xoaSanPham(THUC_PHAM); break;
            case 2: xoaSanPham(DO_UONG); break;
            case 3: xoaSanPham(THOI_TRANG); break;
            case 4: xoaSanPham(DO_GIA_DUNG); break;
            case 5: xoaSanPham(DO_DIEN_TU); break;
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
                 << " (So luong: " << danhSachSanPham[i]->getSoLuong() << ") " << danhSachSanPham[i]->getGia() << " vnd" << endl;
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
        cin >> luaChon;

        if (luaChon == 0) break; // Kết thúc nếu người dùng nhập 0

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
    cout << "*****************************************************\n";
    cout << "*                SIEU THI                           *\n";
    cout << "*****************************************************\n";
    cout << "*                                                   *\n";
    cout << "*   [QUAY THU NGAN]                                 *\n";
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
    cout << "*   |  - Thit tuoi         |   |  - Do gia dung |   *\n";
    cout << "*   |  - Ca dong lanh      |   |  - Do dien tu  |   *\n";
    cout << "*   |  - Rau cu tuoi       |   |                |   *\n";
    cout << "*   +----------------------+   +----------------+   *\n";
    cout << "*                   [CUA RA]                        *\n";
    cout << "*****************************************************\n";
    }   
};
