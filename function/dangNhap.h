#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <thread>
#include <chrono>
#include <conio.h> // Dùng cho _getch() trên Windows
#include <windows.h>

#include "nguoiDung.h"
#include "nhanVien.h"
#include "quanLy.h"
#include "ham.h"
#include "QLNVien.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13


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
            displayMenu(50);
            break;
        } else {
            cout << "Mat khau khong du manh, vui long thu lai." << endl;
        }
    }
}
void displayMenu(int width) 
{
    system("cls");

    string title = "CHAO MUNG DEN VOI SIEU THI UTC2";
    vector<string> options = {
        "Dang nhap",
        "Dang ky",
        "Thoat chuong trinh"
    };

    int choice = 0; // Lựa chọn hiện tại (bắt đầu từ 0)
    while (true) 
    {
        system("cls");
        
        // Vẽ tiêu đề
        printBorder(width);
        printInBox(title, width, false, 11); // Tiêu đề màu xanh dương nhạt
        printBorder(width);

        // Vẽ các tùy chọn
        for (int i = 0; i < options.size(); i++) 
        {
            if (i == choice) 
                printInBox(to_string(i + 1) + ". " + options[i], width, true); // Highlight
            else
                printInBox(to_string(i + 1) + ". " + options[i], width);
        }
        printBottomBorder(width);

        // Đọc phím từ người dùng
        char key = getch();
        if (key == 72) // Mũi tên lên
            choice = (choice - 1 + options.size()) % options.size(); // Di chuyển lên
        else if (key == 80) // Mũi tên xuống
            choice = (choice + 1) % options.size(); // Di chuyển xuống
        else if (key == 13) // Phím Enter
            break; // Chọn tùy chọn
    }

    // Thực hiện hành động tùy theo lựa chọn
    system("cls");
    switch (choice) 
    {
        case 0: 
            cout << "Dang nhap duoc chon!" << endl;
            login(); // Hàm đăng nhập
            break;
        case 1: 
            cout << "Dang ky duoc chon!" << endl;
            registerAccount(); // Hàm đăng ký
            break;
        case 2: 
            cout << "Cam on ban da su dung chuong trinh!" << endl;
            cout << "Hen gap lai ban <3" << endl;
            return; // Thoát chương trình
    }
}
//output function//

int navigateMenu(const vector<string>& options, UserAccount user) {
    int choice = 0;
    QuanLyChucNang qlcn;
    while (true) {
        system("cls");
        qlcn.veSieuThi(user);
        setColor(9); // Màu xanh dương tiêu đề
        cout << "+---------------------------------------+\n";
        cout << "|    CHAO MUNG DEN HE THONG QUAN LY     |\n";
        cout << "|               SIEU THI                |\n";
        cout << "+---------------------------------------+\n";
        setColor(7); // Màu trắng
        // Hiển thị các mục trong menu
        for (size_t i = 0; i < options.size(); ++i) {
        if (i == choice) {
            setColor(14); // Màu vàng cho mục được chọn
            cout << " > " << options[i] << " <" << endl;
        } else {
            setColor(7); // Màu trắng cho mục không được chọn
            cout << "   " << options[i] << endl;
        }
        }
        setColor(7); // Đặt lại màu trắng mặc định

        // Xử lý phím nhập vào
        int key = _getch();
        if (key == 224) { // Phím mũi tên
            key = _getch();
            if (key == KEY_UP) {
                choice = (choice - 1 + options.size()) % options.size();
            } else if (key == KEY_DOWN) {
                choice = (choice + 1) % options.size();
            }
        } else if (key == KEY_ENTER) {
            return choice; // Trả về mục được chọn
        }
    }
}

int ShowMainMenu(UserAccount user) {
    QuanLyChucNang qlcn;
    qlcn.docSanPhamTuFile("database/product.txt"); // Đọc danh sách sản phẩm từ file
    
    // Danh sách các lựa chọn trong menu
    vector<string> options = {
        "Chon quay san pham.",
        "Nap tien vao tai khoan.",
        "Lich su mua hang.",
        "Doi mat khau.",
        "Dang xuat."
    };
    if (user.getRoles() == 2) {
        options.push_back("Quay lai man hinh quan ly.");
    }

    while (true) {
        // Hiển thị menu và xử lý lựa chọn
        int selected = navigateMenu(options, user);

        switch (selected) {
            case 0:
                system("cls");
                qlcn.chonQuayKhac(user);
                break;
            case 1: {
                system("cls");
                int credits;
                do {
                    setColor(14); // Màu vàng
                    cout << "Nhap so tien nap (lon hon 0 va nho hon 10 trieu): ";
                    setColor(7); // Màu trắng
                    cin >> credits;
                } while (credits <= 0 || credits >= 10000000);
                user.accountDeposit(credits);
                setColor(10); // Xanh lá
                cout << "Nap thanh cong: " << credits << "$.\n";
                setColor(7); // Trắng
                break;
            }
            
            case 2: {
                system("cls");
                string fileName = "database/history/" + user.getUsername() + ".txt";
                ifstream file(fileName);
                if (!file.is_open()) {
                    setColor(12); // Đỏ
                    cout << "Khong co thong tin!\n";
                    setColor(7); // Trắng
                    break;
                }

                file.seekg(0, ios::end); // Di chuyển con trỏ đến cuối file
                if (file.tellg() == 0) {
                    setColor(14); // Vàng
                    cout << "Trang thong tin!\n";
                    setColor(7); // Trắng
                    file.close();
                    if (remove(fileName.c_str()) != 0) {
                        setColor(12); // Đỏ
                        cout << "Xoa that bai!\n";
                        setColor(7); // Trắng
                    }
                    break;
                }
                file.seekg(0, ios::beg);
                setColor(11); // Xanh dương nhạt
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
                setColor(7); // Trắng
                break;
            }
            case 3: {
                setColor(14); // Vàng
                cout << "Nhap Password moi: ";
                setColor(7); // Trắng
                cin.ignore();
                string newPassword;
                getline(cin, newPassword);
                user.setPassword(newPassword);
                setColor(10); // Xanh lá
                cout << "Password da duoc cap nhat.\n";
                setColor(7); // Trắng
                updateAccount(user);
                break;
            }
            case 4: {
                system("cls");
                updateAccount(user);
                displayMenu(120);
                return 0;
            }
            case 5:{
                system("cls");
                ShowManageMenu(user);
                break;
            }
        }
        setColor(9); // Xanh dương nhạt
        cout << "Nhan phim bat ky de tiep tuc...\n";
        setColor(7); // Trắng
        system("pause");
    }
}



