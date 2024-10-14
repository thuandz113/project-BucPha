#pragma once

#include <iostream>
#include "doiTuong.h"

using namespace std;

int ShowStaffMenu(UserAccount user)
{
    int choice;

    cout << "==================== Menu Quan Ly Khach Hang ====================" << endl;
    cout << "1. Them khach hang moi" << endl;
    cout << "2. Xem danh sach khach hang" << endl;
    cout << "3. Cap nhat thong tin khach hang" << endl;
    cout << "4. Xoa khach hang" << endl;
    cout << "5. Tim kiem khach hang" << endl;
    cout << "6. Xem danh sach hoa don" << endl;
    cout << "7. Thoat" << endl;
    cout << "Nhap lua chon cua ban: ";
    cin >> choice;

    return choice;
}
