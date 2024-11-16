#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <thread>
#include <chrono>
#include <conio.h> // Dùng cho _getch() trên Windows

#include "nguoiDung.h"
#include "nhanVien.h"
#include "quanLy.h"
#include "ham.h"
#include "QLNVien.h"


using namespace std;


int ShowMainMenu(UserAccount user);
void displayMenu(int width);

bool checkPass(const string &password) {
    return password.size() >= 8;
}
bool checkLogin(ifstream& file, const string& userName, string& password, int& roles, int& credits, int& sex, string& number, string& address) {
    string userTemp, passTemp;
    while(file>>userTemp>>passTemp>>roles>>credits>>sex>>number>>address)
    {
        if (userName == replaceUnderscore(userTemp)) 
        {
            inputPass(password);
            if (password == passTemp) {
                cout << "\nDang nhap thanh cong\n";
                return true;
            } else {
                cout << "\nPassword khong chinh xac, vui long nhap lai\n\n";
                return false;
            }
        }
    }
    return false; // Tài khoản không tồn tại
}

void login() {
    system("cls");

    ifstream file("database/account.txt");
    
    string userName, password, number, address;
    int roles, credits, sex;
    if (!file.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }

    bool isLoggedIn = false;
    for (int count = 0; count < 3; ++count) {
        cout << "UserName: ";
        if (count == 0) cin.ignore();
        getline(cin, userName);

        file.clear();
        file.seekg(0);
        string line;
        getline(file, line);

        if (checkLogin(file, userName, password, roles, credits, sex, number, address)) {
            isLoggedIn = true;
            break;
        } else {
            cout << "\nCo loi xay ra, vui long nhap lai\n\n";
        }
    }
    file.close();

    if (isLoggedIn) {
        UserAccount user(userName, password, roles, credits, sex, number, address);
        if (roles == 0) {
            cout << "Chao mung khach hang da quay tro lai <3" << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            ShowMainMenu(user);
        } else if (roles == 1) {
            cout << "Chao mung nhan vien da quay tro lai <3" << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            ShowStaffMenu(user);
        } else if (roles == 2) {
            cout << "Chao mung quan ly da quay tro lai <3" << endl;
            ShowManageMenu(user);
        } else {
            cout << "Role khong hop le!" << endl;
        }
    } else {
        cout << "\n\nDa nhap qua 3 lan. Chuong trinh thoat\n";
        exit(0);
    }
}

void registerAccount() {
    ofstream file("database/account.txt", ios::app);
    if (!file.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }

    string userName, password;

    ifstream fileCheck("database/account.txt");
    if (!fileCheck.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }
    string userTemp, passTemp;
        int sex, credits, roles;
        string number,address;
    bool first = false;
    while(1)
    {
        bool checkAccount = true;
        cout << "Nhap ten tai khoan moi: ";
        if(first == false)
        {
            cin.ignore();
            first = true;
        }
        getline(cin, userName);
        fileCheck.clear();
        fileCheck.seekg(0);
        string line;
        getline(fileCheck, line);
        while (fileCheck >> userTemp >> passTemp >> roles >> credits >> sex >> number >> address)
        {
            if(userName == userTemp)
            {
                checkAccount = false;
            }
        }
        if(checkAccount == true) break;
        else {
            cout<<"Ten tai khoan bi trung, vui long nhap lai."<<endl;
        }
    }
    fileCheck.close();
    while (true) {
        cout << "Nhap mat khau moi (it nhat 8 ky tu): ";
        inputPass(password);

        if (checkPass(password)) 
        {
            int sex;
            string number, address;
            cout<<"Vui long chon gioi tinh: 1-Nam, 2-Nu."<<endl;
            do{
                cout<<"Lua chon cua ban:";
                cinInt>>sex;
            }
            while(sex != 1 && sex != 2);
            cin.ignore();
            cout<<"Vui long nhap so dien thoai cua ban:";
            getline(cin, number);
            cout<<"Vui long them dia chi cua ban:";
            getline(cin, address);
            file << replaceSpace(userName) << " " << password << " "<< 0 <<" "<< 0<<" "<< sex <<" "<< replaceSpace(number) << " "<< replaceSpace(address)<<endl;
            cout << "Dang ky tai khoan thanh cong!" << endl;
            file.close();
            displayMenu(120);
            break;
        } else {
            cout << "Mat khau khong du manh, vui long thu lai." << endl;
        }
    }
}

//output function//
void displayMenu(int width) 
{
    system("cls");
    string title = "CHAO MUNG DEN VOI SIEU THI UTC2";
    string message = "BAN CAN GI";
    
    printBorder(width);
    printInBox(title, width);
    printBorder(width);
    printInBox(message, width);
    printBorder(width);

    string option1 = "1.Dang nhap";
    string option2 = "2.Dang ky";
    string option3 = "3.Thoat chuong trinh";
    
    printInBox(option1, width);
    printInBox(option2, width);
    printInBox(option3, width);
    printBorder(width);
    
    int choice;
    cout << " Vui long nhap trong (1-3): "; 
    cout.flush(); 
    cinInt >> choice;
    while (choice < 1 || choice > 3) 
	{
        cout << " Vui long nhap lai trong (1-3): "; 
        cout.flush(); 
        cinInt >> choice;
    }

    cout << " Ban da chon: " << choice << "" << endl;

    printBorder(width);
    system("cls");
    if (choice == 1) 
    {
        login();
    } else if (choice == 2) {
        registerAccount();
    }
    else{
        cout<<"Cam on ban da su dung chuong trinh !"<<endl;
        cout<<"Hen gap lai ban <3"<<endl;
        return;
    }
}
int ShowMainMenu(UserAccount user) {
    QuanLyChucNang qlcn;
    qlcn.docSanPhamTuFile("database/product.txt"); // Đọc danh sách sản phẩm từ file

    char tiepTuc;
    do {
        qlcn.veSieuThi(user);
        cout << "+---------------------------------------+\n";
        cout << "|    CHAO MUNG DEN HE THONG QUAN LY     |\n";
        cout << "|               SIEU THI                |\n";
        cout << "+---------------------------------------+\n";
        cout << "| 1. Chon quay san pham.                |\n";
        cout << "| 2. Nap tien vao tai khoan.            |\n";
        cout << "| 3. Lich su mua hang.                  |\n";
        cout << "| 4. Doi mat khau.                      |\n";
        cout << "| 5. Dang xuat.                         |\n";
        cout << "+---------------------------------------+\n";
        if(user.getRoles() == 2) cout << "6. Quay lai man hinh quan ly.\n";
        int luaChon;
        cout << "Vui long nhap lua chon !: ";
        cinInt >> luaChon;

        switch (luaChon) {
            case 1:
                system("cls");
                qlcn.chonQuayKhac(user);
                break;
            case 2:
                system("cls");
                int credits;
                do{
                    cout<<"Vui long nhap so tien can nap(lon hon 0 va nho hon 10 trieu): ";
                    cinInt>>credits;
                }
                while(credits <= 0 || credits >= 10000000);
                user.accountDeposit(+credits);
                cout<<"Ban vua nap "<<credits<< "$ vao tai khoan."<<endl;
                break;
            case 3:
            {
                system("cls");
                string fileName = "database/history/" + user.getUsername() + ".txt";
                ifstream file(fileName);

                if (!file.is_open()) {
                    cout << "Khong co thong tin!" << endl;
                    break;
                }

                // Kiểm tra nếu file trống
                file.seekg(0, ios::end); // Di chuyển con trỏ đến cuối file
                if (file.tellg() == 0) 
                {
                    cout << "Trang thong tin!" << endl;
                    file.close();
                    // Xóa file trống
                    if (remove(fileName.c_str()) != 0) {
                        cout << "Xoa that bai!" << endl;
                    }
                    break;
                }
                file.seekg(0, ios::beg);
                cout << "========================================================================\n";
                cout << "| " << left << setw(15) << "Ten mon"
                     << "| " << setw(10) << "Gia"
                     << "| " << setw(10) << "So luong"
                     << "| " << setw(15) << "Tong tien"
                     << "| " << "Ngay mua" << "   |\n";
                cout << "========================================================================\n";

                string line;
                while (getline(file, line)) {
                    istringstream iss(line);
                    string itemName, Date;
                    int price, quantity, total;

                    iss >> itemName >> price >> quantity >> total >> Date;

                    cout << "| " << left << setw(15) << itemName
                         << "| " << setw(10) << price
                         << "| " << setw(10) << quantity
                         << "| " << setw(15) << total
                         << "| " << Date << " |\n";
                }
                cout << "========================================================================\n";
                file.close();
                break;

            }
            case 4://doi mat khau
            {
            	string newPassword;
                cout << "Nhap Password moi: ";
                cin.ignore();
                getline(cin, newPassword);
                user.setPassword(newPassword);
                cout << "Password da duoc cap nhat." << endl;
                updateAccount(user);
                break;
			}
            case 5:
                system("cls");
                updateAccount(user);
                displayMenu(120);
                break;
            case 6:
            	system("cls");
            	ShowManageMenu(user);
            	break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }
        cout << "Ban co muon tiep tuc? (y/n): ";
        cin >> tiepTuc;
        system("cls");

    } while (tiepTuc == 'y' || tiepTuc == 'Y');

    return 0;
}

