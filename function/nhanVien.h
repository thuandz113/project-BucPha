#pragma once

#include <iostream>
#include "doiTuong.h"

using namespace std;

int ShowStaffMenu(UserAccount user)
{
    int choice;

    cout << "==================== Menu Quan Ly Khach Hang ====================" << endl;
    cout << "1. Xem danh sach khach hang" << endl;
    cout << "2. Cap nhat thong tin khach hang" << endl;
    cout << "3. Xoa khach hang" << endl;
    cout << "4. Tim kiem khach hang" << endl;
    cout << "5. Xem danh sach hoa don" << endl;
    cout << "6. Thoat" << endl;
    cout << "Nhap lua chon cua ban: ";
    cin >> choice;

    return choice;
}
