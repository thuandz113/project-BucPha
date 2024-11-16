#pragma once

#include <iostream>
#include "doiTuong.h"
#include "nguoiDung.h"

#include "nhanVien.h"
#include "QLNVien.h"
#include "dangNhap.h"

using namespace std;

int ShowMainMenu(UserAccount user);
int ShowManageMenu(UserAccount user)
{

    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    QuanLyChucNang qlcn;
    int choice;

    do{
    cout << "==================== MENU QUAN LY ====================" << endl;
    cout << "| 1. Nhap hang                                       |" << endl;
    cout << "| 2. Xoa hang                                        |" << endl;
    cout << "| 3. Cap nhat danh sach nhan vien                    |" << endl;
    cout << "| 4. Giao dien nhan vien                             |" << endl;
    cout << "| 5. Giao dien nguoi dung                            |" << endl;
    cout << "| 6. Dang xuat                                       |" << endl;
    cout << "======================================================" << endl;
    cout << "Nhap lua chon cua ban!: ";
    cinInt >> choice;

    switch (choice) {
        case 1:
            cout<<"ban dang den voi chuc nang nhap hang"<<endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            qlcn.nhapHang();
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            break;
        case 2:
            cout<<"ban dang den voi chuc nang xoa hang"<<endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            qlcn.xoaHang();
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            break;
        case 3:
            cout<<"ban dang den voi chuc nang quang ly nhan vien"<<endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            menuEmployeeManagement();
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            break;
        case 4:
            cout <<"Ban dang den voi chuc nang giao dien nhan vien"<<endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            ShowStaffMenu(user);
            break;
        case 5:
            cout <<"Ban dang den voi chuc nang giao dien nguoi dung"<<endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            ShowMainMenu(user);
            break;
        case 6:
           
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            displayMenu(120);
            return choice;
            break;
        default:
            cout << "Lua chon khong hop le! Vui long chon lai." << endl;
            break;
        }  
    }while(choice>0||choice<5);

    return choice;
}

