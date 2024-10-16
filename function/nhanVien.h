#pragma once

#include <iostream>
#include "doiTuong.h"

using namespace std;

const int max_account=100;
struct Account{
    string username;
    string password
    int roles;
    int credits;
    int sex; //1:Male, 0:Female
    string number;
    string address;
}
void viewAndEditCustomer() {
    Account accounts[MAX_ACCOUNTS];
    
    if (numAccounts == 0) {
        cout << "Khong co tai khoan nao trong file!" << endl;
        return;
    }

    cout << "Danh sach khach hang:" << endl;
    for (int i = 0; i < numAccounts; ++i) {
        cout << i + 1 << ". " << accounts[i].username << " | Credits: " << accounts[i].credits << endl;
    }

    int choice;
    cout << "Vui long chon khach hang de chinh sua (0 de thoat): ";
    cin >> choice;

    if (choice == 0) return;
    if (choice > 0 && choice <= numAccounts) {
        cout << "Ban muon thay doi thong tin gi cho tai khoan nay?" << endl;
        cout << "Nhap credits moi: ";
        cin >> accounts[choice - 1].credits;
        // Sau khi chỉnh sửa, ghi lại vào file
        ofstream file("database/account.txt");
        file << "username password roles credits sex number address\n";  // Tiêu đề
        for (int i = 0; i < numAccounts; ++i) {
            file << accounts[i].username << " " << accounts[i].password << " " << accounts[i].roles << " "
                 << accounts[i].credits << " " << accounts[i].sex << " " << accounts[i].number << " " << accounts[i].address << endl;
        }
        file.close();
        cout << "Da cap nhat thong tin khach hang!" << endl;
    } else {
        cout << "Lua chon khong hop le!" << endl;
    }
}
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
