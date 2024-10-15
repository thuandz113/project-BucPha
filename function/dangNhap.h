#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> // Dùng cho _getch() trên Windows

#include "nguoiDung.h"
#include "nhanVien.h"

using namespace std;
int ShowMainMenu(UserAccount user);
void displayMenu(int width);
void printInBox(const string& content, int width) {
    int padding = (width - 4 - content.size()) / 2;
    cout << "|" << string(padding, ' ') << content << string(width - 4 - padding - content.size(), ' ') << "  |" << endl;
}

void printBorder(int width) {
    cout << "+" << string(width - 2, '-') << "+" << endl;
}
void inputPass(string &password) {
    char ch;
    password = "";
    cout << "Password: ";
    while (true) {
        ch = _getch();  // Đọc ký tự không hiện trên màn hình
        if (ch == '\r') { // Dừng khi nhấn Enter
            break;
        } else if (ch == '\b') { // Xóa ký tự cuối khi nhấn Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Xóa ký tự * trên màn hình
            }
        } else {
            password += ch; // Thêm ký tự vào chuỗi mật khẩu
            cout << '*'; // In dấu * thay cho ký tự đã nhập
        }
    }
    cout << endl;
}

bool checkPass(const string &password) {
    return password.size() >= 8;
}
bool checkLogin(ifstream& file, const string& userName, string& password, int& roles, int& credits) {
    string userTemp, passTemp;
    while (file >> userTemp >> passTemp >> roles >> credits) {
        if (userName == userTemp) 
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
    
    string userName, password;
    int roles, credits;
    if (!file.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }
    bool isLoggedIn = false;
    for (int count = 0; count < 3; ++count) 
    {
        cout << "UserName: ";
        if (count == 0) cin.ignore(); // Chỉ ignore ở lần nhập đầu tiên để xóa '\n' còn sót lại
        getline(cin, userName);

        file.clear();
        file.seekg(0);
        string line;
        getline(file, line);
        if (checkLogin(file, userName, password, roles, credits)) 
            isLoggedIn = true;
        
        if (!isLoggedIn) {
            cout << "\nCo loi xay ra, vui long nhap lai\n\n";
        }
        else 
        {
            file.close();
            UserAccount user(userName, password, roles , credits);
            if (roles == 0) {
                cout << "Chao mung khach hang da quay tro lai <3" << endl;
                ShowMainMenu(user);
            } 
            else if (roles == 1) 
            {
                cout << "Chao mung nhan vien da quay tro lai <3" << endl;
                ShowStaffMenu(user);
            } 
            else if (roles == 2) 
            {
                cout << "Chao mung quan ly da quay tro lai <3" << endl;
                //ShowManageMenu(user);
            } 
            else 
            {
                cout << "Role khong hop le!" << endl;
            }
            break;
        }
    }

    if (!isLoggedIn) {
        cout << "\n\nDa nhap qua 3 lan. Chuong trinh thoat\n";
        file.close();
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
        while (fileCheck >> userTemp >> passTemp)
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

        if (checkPass(password)) {
            file << userName << " " << password << " "<< 0 <<" "<< 0<<endl;
            cout << "Dang ky tai khoan thanh cong!" << endl;
            displayMenu(120);
            break;
        } else {
            cout << "Mat khau khong du manh, vui long thu lai." << endl;
        }
    }
    
    file.close();
}
bool updateAccount(UserAccount user) {
    ifstream fileIn("database/account.txt");
    if (!fileIn) {
        cout << "Khong the mo file Account.txt!" << endl;
        return false;
    }

    ofstream fileOut("database/temp.txt");
    if (!fileOut) {
        cout << "Khong the tao file tam!" << endl;
        return false; 
    }

    string userTemp, passTemp, line;
    int roles, credits;
    bool found = false;
    fileOut<<"Username/Password/Roles/Credits"<<endl;
    getline(fileIn, line);
    
    while (fileIn >> userTemp >> passTemp >> roles >> credits) {
        if (userTemp == user.getUsername()) {
            fileOut << userTemp << " " << passTemp << " " << roles << " " << user.getCredits() << endl;
            found = true;
        } else {
            fileOut << userTemp << " " << passTemp << " " << roles << " " << credits << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    if (remove("database/account.txt") != 0) {
        cout << "Khong the xoa file Account.txt!" << endl;
        return false;
    }
    if (rename("database/temp.txt", "database/account.txt") != 0) {
        cout << "Khong the doi ten file tam!" << endl;
        return false;
    }

    return found;
}

//output function//
void displayMenu(int width) {
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
    
    printInBox(option1, width);
    printInBox(option2, width);
    printBorder(width);
    
    int choice;
    cout << " Vui long nhap trong (1-2): "; 
    cout.flush(); 
    cin >> choice;

    while (choice < 1 || choice > 2) {
        cout << " Vui long nhap lai trong (1-2): "; 
        cout.flush(); 
        cin >> choice;
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
}
int ShowMainMenu(UserAccount user) {
    QuanLyChucNang qlcn;
    qlcn.docSanPhamTuFile("database/product.txt"); // Đọc danh sách sản phẩm từ file

    char tiepTuc;
    do {
        qlcn.veSieuThi(user);
        cout << "Chao mung den he thong quan ly sieu thi.\n";
        cout << "1. Chon quay san pham.\n";
        cout << "2. Nap tien vao tai khoan.\n";
        cout << "3. Dang xuat.\n";
        int luaChon;
        cout << "Vui long nhap lua chon: ";
        cin >> luaChon;

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
                    cin>>credits;
                }
                while(credits <= 0 || credits >= 10000000);
                user.accountDeposit(+credits);
                cout<<"Ban vua nap "<<credits<< "$ vao tai khoan."<<endl;
                break;
            case 3:
                system("cls");
                updateAccount(user);
                displayMenu(120);
                return 0;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }
        cout << "Ban co muon tiep tuc? (y/n): ";
        cin >> tiepTuc;
        system("cls");

    } while (tiepTuc == 'y' || tiepTuc == 'Y');

    return 0;
}

