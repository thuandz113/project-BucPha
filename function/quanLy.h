#pragma once

#include <iostream>
#include "doiTuong.h"

using namespace std;

int ShowManageMenu(UserAccount user)
{
    int choice;

    cout << "==================== Menu Quan Ly ====================" << endl;
    cout << "1. Nhap hang" << endl;
    cout << "2. Xoa hang" << endl;
    cout << "3. Xoa nhan vien" << endl;
    cout << "4. Xoa khach hang" << endl;
    cout << "5. Phan ca truc online" << endl;
    cout << "6. Thoat" << endl;
    cout << "Nhap lua chon cua ban: ";
    cin >> choice;

    return choice;
}
