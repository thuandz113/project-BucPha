#pragma once

#include <iostream>
#include "doiTuong.h"

using namespace std;

int ShowStaffMenu(UserAccount user)
{
    int choice;

    cout << "==================== Menu nhan vien ====================" << endl;
    cout << "1. Xem danh sach va chinh sua thong tin khach hang" << endl;
        /*hiện ra 1 menu danh sách các tài khoản khách hàng
        có thể thay đổi credits , tên đăng nhập , password
        ví dụ:
        1. Nguyen Van A | Credits: 5000
        2. Nguyen Van B | Credits: 3000
        Vui long chon ten khach hang ban muon thay doi(0 de thoat ra menu):
        */
    cout << "2. Xoa tai khoan khach hang" << endl;
        //Xoá khách hàng trong file, xem hàm updateAccount tựa tựa.
    cout << "3. Tim kiem khach hang" << endl;
        //Tìm tên của 1 khách hàng sau đó show ra thông tin gôm` tên , số credits, giới tính , số điện thoại
    cout << "4. Xem hoa don da mua cua khach hang" << endl;
    cout << "5. Suy nghi" << endl;//suy nghĩ thêm vài cái
    cout << "6. Suy nghi" << endl;
    cout << "7. Suy nghi" << endl;
    cout << "8. Suy nghi" << endl;
    cout << "9. Thoat" << endl;
    cout << "Nhap lua chon cua ban: ";
    cin >> choice;
    switch(choice)
    {
        case 1:
        {
            ifstream file("database/account.txt");
            if (!file.is_open()) {
                cout << "Khong the mo file tai khoan!" << endl;
                return 0;
            }

            int sex, credits, roles;
            string line, username, password, number, address;
            getline(file, line);

            while (file >> username >> password >> roles >> credits >> sex >> number >> address) {
                cout << "Username: " << username 
                    << ", Password: " << password 
                    << ", Roles: " << roles 
                    << ", Credits: " << credits 
                    << ", Sex: " << sex 
                    << ", Number: " << number 
                    << ", Address: " << address 
                    << endl;
            }

            file.close();
            break;
        }
    }
    return choice;
}
