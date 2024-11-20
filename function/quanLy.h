#pragma once

#include <iostream>
#include "doiTuong.h"
#include "nguoiDung.h"

#include "nhanVien.h"
#include "QLNVien.h"
#include "dangNhap.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
using namespace std;
int ShowMainMenu(UserAccount user);
void drawHeader() {
    setColor(7);
    cout << " ╔══════════════════════════════════════════════════════╗" << endl;
    cout << " ║                    ";
    setColor(11);
    cout<<"★ MENU QUẢN LÝ ★";
    setColor(7);
    cout<<"                  ║" << endl;
    cout << " ╠══════════════════════════════════════════════════════╣" ;
}


void quanLyKhoHang(UserAccount user) {
    
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");
    int choice = 0;
    QuanLyChucNang qlcn;
    do {
        system("cls");
        qlcn.drawHeader1();
        cout << endl;
        qlcn.drawMenuOptions(choice);

        setColor(7);  // Đặt lại màu trắng mặc định
        cout << " ╚══════════════════════════════════════════════════════╝" << endl;

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) {
                choice = (choice - 1 + 5) % 5;
            } else if (key == 80) {
                choice = (choice + 1) % 5;
            }
        } else if (key == 13) {  // Enter
            system("cls");
            switch (choice) {
                case 0:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang nhap hang" << endl;
                    setColor(7);
                    qlcn.nhapHang();
                    break;
                case 1:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang xoa hang" << endl;
                    setColor(7);
                    qlcn.xoaHang();
                    break;
                case 2:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang cap nhat gia san pham" << endl;
                    setColor(7);
                    qlcn.capNhatGiaHang();
                    break;
                case 3:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang tim kiem san pham" << endl;
                    setColor(7);
                    this_thread::sleep_for(chrono::milliseconds(500));
                    system("cls");
                    qlcn.xulytimkiem(user);
                    break;
                case 4:
                    setColor(12);
                    cout << "Thoat kho hang..." << endl;
                    this_thread::sleep_for(chrono::milliseconds(500));
                    return;  // Thoát khỏi hàm quanLyKhoHang()
            }
            this_thread::sleep_for(chrono::milliseconds(500));
            system("cls");
        }
    } while (true);
}
// Hàm vẽ các mục trong menu
void drawMenuOptions(int choice) {
    setColor(7); // Màu trắng cho tất cả mục
    string options[] = {
        "Quản Lý Kho Hàng",
        "Cap nhat danh sach nhan vien",
        "Giao dien nhan vien",
        "Giao dien nguoi dung",
        "Dang xuat"
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
            case 0: cout << "Quản lý kho hang                                   ";
                    setColor(7);
                    cout << "║";
                    break;
            case 1: cout << "Cap nhat danh sach nhan vien                       ";
                    setColor(7);
                    cout << "║";
                    break;
            case 2: cout << "Giao dien nhan vien                                ";
                    setColor(7);
                    cout << "║";
                    break;
            case 3: cout << "Giao dien nguoi dung                               ";
                    setColor(7);
                    cout << "║";
                    break;
            case 4: cout << "Dang xuat                                          ";
                    setColor(7);
                    cout << "║";
                    break;
        }

        cout << endl;
    }
}


int ShowManageMenu(UserAccount user) {
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");
    QuanLyChucNang qlcn;
    int choice = 0;

    do {
        system("cls");
        drawHeader();
        cout << endl;
        drawMenuOptions(choice);

        setColor(7);
        cout << " ╚══════════════════════════════════════════════════════╝" << endl;

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP) {
                choice = (choice - 1 + 6) % 6;
            } else if (key == KEY_DOWN) {
                choice = (choice + 1) % 6;
            }
        } else if (key == KEY_ENTER) {
            system("cls");
            switch (choice + 1) {
                case 1:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang quan ly kho hang" << endl;
                    setColor(7);
                    this_thread::sleep_for(chrono::milliseconds(500));
                    quanLyKhoHang(user);  // Gọi lại quản lý kho
                    break;
                case 2:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang quan ly nhan vien" << endl;
                    setColor(7);
                    this_thread::sleep_for(chrono::milliseconds(500));
                    menuEmployeeManagement();
                    break;
                case 3:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang giao dien nhan vien" << endl;
                    setColor(7);
                    this_thread::sleep_for(chrono::milliseconds(500));
                    ShowStaffMenu(user);
                    break;
                case 4:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang giao dien nguoi dung" << endl;
                    setColor(7);
                    this_thread::sleep_for(chrono::milliseconds(500));
                    ShowMainMenu(user);
                    break;
                case 5:
                    setColor(12);
                    cout << "Dang xuat..." << endl;
                    setColor(7);
                    this_thread::sleep_for(chrono::milliseconds(500));
                    displayMenu(50);
                    return 6;
                default:
                    cout << "Lua chon khong hop le! Vui long chon lai." << endl;
                    break;
            }
            this_thread::sleep_for(chrono::milliseconds(500));
            system("cls");
        }
    } while (true);

    return choice;
}