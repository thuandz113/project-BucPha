#pragma once

#include <iostream>
#include "doiTuong.h"
#include "nguoiDung.h"
#include "nhanVien.h"
#include "QLNVien.h"
using namespace std;


int ShowManageMenu(UserAccount user)
{
    QuanLyChucNang qlcn;
    int choice;

    cout << "==================== Menu Quan Ly ====================" << endl;
    cout << "1. Nhap hang" << endl;
    cout << "2. Xoa hang" << endl;
    cout << "3. Cap nhat danh sach nhan vien" << endl;
    cout << "4. Xoa khach hang" << endl;
    cout << "5. Thoat" << endl;
    cout << "Nhap lua chon cua ban: ";
    cin >> choice;

    switch (choice) {
        case 1:
            qlcn.nhapHang();
            break;
        case 2:
            qlcn.xoaHang();
            break;
        case 3:
            menuEmployeeManagement();
            break;
        // case 4:
        //     qlcn.xoaKhachHang();
        //     break;
        case 5:
            cout << "Thoat khoi chuong trinh." << endl;
            break;
        default:
            cout << "Lua chon khong hop le! Vui long chon lai." << endl;
            break;
    }

    return choice;
}

