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

    cout << " ╔══════════════════════════════════════════════════════╗" << endl;
    cout << " ║                    ";
    setColor(11);
    cout<<"★ MENU QUẢN LÝ ★";
    setColor(7);
    cout<<"                  ║" << endl;
    cout << " ╠══════════════════════════════════════════════════════╣" ;
}


// Hàm vẽ khung menu

void quanLyKhoHang() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");  // Xóa màn hình lần đầu tiên khi vào menu
    int choice = 0;
    QuanLyChucNang qlcn;
    do {
        system("cls"); // Xóa màn hình mỗi khi vòng lặp chạy lại

        // Vẽ tiêu đề và khung
        qlcn.drawHeader1();
        cout << endl;  // Thêm khoảng trắng giữa tiêu đề và menu

        // Vẽ các mục trong menu
        qlcn.drawMenuOptions(choice);
        
        setColor(7);  // Đặt lại màu trắng mặc định
        cout << " ╚══════════════════════════════════════════════════════╝" << endl;

        // Xử lý phím nhập vào
        int key = _getch();
        if (key == 224) { // Phím mũi tên
            key = _getch();
            if (key == 72) {
                choice = (choice - 1 + 4) % 4;  // Điều chỉnh khi lên xuống
            } else if (key == 80) {
                choice = (choice + 1) % 4;
            }
        } else if (key == 13) {  // Enter
            // Thực hiện chức năng tương ứng
            system("cls");
            switch (choice) {
                case 0:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang nhap hang" << endl;
                    setColor(7);
                    // Hàm nhập hàng (cập nhật số lượng sản phẩm)
                    qlcn.nhapHang();
                    break;
                case 1:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang xoa hang" << endl;
                    setColor(7);
                    // Hàm xóa hàng
                    qlcn.xoaHang();
                    break;
                case 2:
                    setColor(12);
                    cout << "Ban dang den voi chuc nang cap nhat gia san pham" << endl;
                    setColor(7);
                    // Hàm cập nhật giá sản phẩm
                    qlcn.capNhatGiaHang();
                    break;
                case 3:
                    setColor(12);
                    cout << "Thoat kho hang..." << endl;
                    this_thread::sleep_for(chrono::milliseconds(500));
                    system("cls");
                    
                    setColor(7);
                default:
                    cout << "Lua chon khong hop le! Vui long chon lai." << endl;
                    break;
            }
            this_thread::sleep_for(chrono::milliseconds(1000));
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

// Hàm hiển thị menu
int ShowManageMenu(UserAccount user) {
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");  // Xóa màn hình lần đầu tiên khi vào menu
    QuanLyChucNang qlcn;
    int choice = 0;

    do {
        system("cls"); // Xóa màn hình mỗi khi vòng lặp chạy lại

        // Vẽ tiêu đề và khung
        drawHeader();
        cout << endl;  // Thêm khoảng trắng giữa tiêu đề và menu


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
                    setColor(12);
                    cout << "Ban dang den voi chuc nang quan ly kho hang" << endl;
                    setColor(7);
                    this_thread::sleep_for(chrono::milliseconds(500));
                    qlcn.quanLyKhoHang();
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
            // Sau khi xử lý, quay lại menu
            this_thread::sleep_for(chrono::milliseconds(500));
            system("cls");
        }
    } while (true);

    return choice;
}
