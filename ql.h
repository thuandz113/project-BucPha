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

