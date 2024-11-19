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
    setColor(12); // Màu đỏ cho tiêu đề
    cout << "  ╔══════════════════════════════════════════════════════╗" << endl;
    cout << " ║                    ★ MENU QUẢN LÝ ★                  ║" << endl;
    cout << "  ╚══════════════════════════════════════════════════════╝" << endl;
}

// Hàm vẽ khung menu
void drawMenuFrame() {
    setColor(9); // Màu xanh cho khung menu
    cout << " ╔══════════════════════════════════════════════════════╗" << endl;
    cout << " ║                                                      ║" << endl;
    cout << " ║                                                      ║" << endl;
    cout << " ║                                                      ║" << endl;
    cout << " ║                                                      ║" << endl;
    cout << " ╚══════════════════════════════════════════════════════╝" << endl;
}

// Hàm vẽ các mục trong menu
void drawMenuOptions(int choice) {
    setColor(7); // Màu trắng cho tất cả mục
    string options[] = {
        "Nhap hang",
        "Xoa hang",
        "Cap nhat danh sach nhan vien",
        "Giao dien nhan vien",
        "Giao dien nguoi dung",
        "Dang xuat"
    };

    for (int i = 0; i < 6; i++) {
        if (i == choice) {
            setColor(14); // Màu vàng cho mục được chọn
            cout << "     > " << options[i] << " <" << endl; // Dấu > < để tạo sự chú ý
        } else {
            setColor(7); // Màu trắng cho các mục không được chọn
            cout << "       " << options[i] << endl;
        }
    }
}

// Hàm hiển thị menu
int ShowManageMenu(UserAccount user) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");  // Xóa màn hình lần đầu tiên khi vào menu
    QuanLyChucNang qlcn;
    int choice = 0;

    do {
        system("cls"); // Xóa màn hình mỗi khi vòng lặp chạy lại

        // Vẽ tiêu đề và khung
        drawHeader();
        cout << endl;  // Thêm khoảng trắng giữa tiêu đề và menu
        drawMenuFrame();
        cout << endl;  // Thêm khoảng trắng giữa khung và các lựa chọn

        // Vẽ các mục trong menu
        drawMenuOptions(choice);
        
        setColor(7);  // Đặt lại màu trắng mặc định
        cout << " ╚══════════════════════════════════════════════════════╝" << endl;

        // Xử lý phím nhập vào
        int key = _getch();
        if (key == 224) { // Phím mũi tên
            key = _getch();
            if (key == KEY_UP) {
                choice = (choice - 1 + 6) % 6;  // Điều chỉnh khi lên xuống
            } else if (key == KEY_DOWN) {
                choice = (choice + 1) % 6;
            }
        } else if (key == KEY_ENTER) {
            // Thực hiện chức năng tương ứng
            system("cls");
            switch (choice + 1) {
                case 1:
                    cout << "Ban dang den voi chuc nang nhap hang" << endl;
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    qlcn.nhapHang();
                    break;
                case 2:
                    cout << "Ban dang den voi chuc nang xoa hang" << endl;
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    qlcn.xoaHang();
                    break;
                case 3:
                    cout << "Ban dang den voi chuc nang quan ly nhan vien" << endl;
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    menuEmployeeManagement();
                    break;
                case 4:
                    cout << "Ban dang den voi chuc nang giao dien nhan vien" << endl;
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    ShowStaffMenu(user);
                    break;
                case 5:
                    cout << "Ban dang den voi chuc nang giao dien nguoi dung" << endl;
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    ShowMainMenu(user);
                    break;
                case 6:
                    cout << "Dang xuat..." << endl;
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    displayMenu(50);
                    return 6;
                default:
                    cout << "Lua chon khong hop le! Vui long chon lai." << endl;
                    break;
            }
            // Sau khi xử lý, quay lại menu
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
        }
    } while (true);

    return choice;
}
