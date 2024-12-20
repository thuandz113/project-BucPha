#pragma once

#include <iostream>
#include <windows.h>
#include "doiTuong.h"
#include "ham.h"
using namespace std;
void displayMenu(int width);
int ShowManageMenu(UserAccount user);
bool searchUsername(const string& s, UserAccount &user) 
{
    ifstream file("database/account.txt");
    file.clear();
    file.seekg(0);
    int sex, credits, roles;
    string line, username, password, number, address;

    file.clear();
    file.seekg(0);

    getline(file, line);
    while (file >> username >> password >> roles >> credits >> sex >> number >> address) {
        if (replaceUnderscore(username) == s && roles == 0) 
        {
            user.setAttributes(replaceUnderscore(username),password,roles,credits,sex,number,address);
            return true;
        }
    }
    file.close();
    return false;
}
void showList() {
    ifstream file("database/account.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }

    // Bỏ qua dòng đầu tiên (tiêu đề)
    string line;
    getline(file, line);

    int sex, credits, roles;
    string username, password, number, address;

    // In tiêu đề bảng
    setColor(7); // Màu mặc định
    cout << "+---------------+------------------+-------+---------+------+------------+-----------------------+" << endl;

    // Tiêu đề với chỉ chữ cái đổi màu
    string header = "| Username      | Password         | Roles | Credits | Sex  |  Number    | Address               |";
    for (char c : header) {
        if (isalpha(c)) {
            setColor(11); // Màu xanh sáng cho chữ cái
            cout << c;
        } else {
            setColor(7); // Màu mặc định cho các ký tự khác
            cout << c;
        }
    }
    cout << endl;

    // Đường phân cách
    setColor(7);
    cout << "+---------------+------------------+-------+---------+------+------------+-----------------------+" << endl;

    // Đọc dữ liệu từ file và hiển thị trong bảng
    while (file >> username >> password >> roles >> credits >> sex >> number >> address) {
        if(roles==0){
            cout << "| " << setw(13) << left << username
             << " | " << setw(16) << left << maskString(password)
             << " | " << setw(5) << left << roles
             << " | " << setw(7) << left << credits
             << " | " << setw(4) << left << sex
             << " | " << setw(10) << left << number
             << " | " << setw(21) << left << address << " |" << endl;
        }
    }

    // Kết thúc bảng
    cout << "+---------------+------------------+-------+---------+------+------------+-----------------------+" << endl;
    setColor(7);
    file.close();
}
void logDeletion(string line, const string& staffName) 
{
    ofstream logFile("database/deletion_log.txt", ios::app);
    if (!logFile.is_open()) {
        cout << "Khong the mo file log!" << endl;
        return;
    }

    logFile << "Nhan vien: " << staffName << "-Account Del:";
    logFile << line<<endl;
    logFile.close();
}

bool searchAccount(const string& usernameToSearch) {
    ifstream inputFile("database/account.txt");
    
    if (!inputFile.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return false;
    }
    string line;
    bool accountFound = false;

    while (getline(inputFile, line)) {
        string username, password;
        int roles = -1;
        istringstream iss(line);
        iss >> username >> password >> roles;
		
        if (replaceUnderscore(username) == usernameToSearch && roles == 0) {
            accountFound = true;
            cout << "Tai khoan tim thay: " << line << endl;
            cout<<roles;
            break;
        }
    }

    inputFile.close();
    return accountFound;
}
bool deleteAccount(const string& usernameToDelete, const string& staffName) {
    ifstream inputFile("database/account.txt");
    ofstream outputFile("database/temp.txt");
    
    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return false;
    }

    string line;
    bool accountFound = false;

    while (getline(inputFile, line)) {
        string username;
        istringstream iss(line);
        iss >> username;

        if (replaceUnderscore(username) == usernameToDelete) {
            accountFound = true;
            UserAccount user(username, "", 0, 0, 0, "", "");
            user.setAttributes(username, "", 0, 0, 0, "", "");
            logDeletion(line, staffName);
            continue;
        }
        outputFile << line << endl;
    }

    inputFile.close();
    outputFile.close();
    remove("database/account.txt");
    rename("database/temp.txt", "database/account.txt");

    return accountFound;
}
void handleViewAndEditCustomer() {
    showList();
    char luaChon;
    string option;
    setColor(14);
    cout << "Ban co muon chinh sua khach hang khong?" << endl;
    setColor(7);
    cout << "Lua chon cua ban(Y(y)/khac):";
    cin >> luaChon;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (luaChon != 'y' && luaChon != 'Y') return;

    UserAccount editUser("Null", "Null", 0, 0, 0, "Null", "Null");
    do {
        
        setColor(14);
        cout << "Nhap ten tai khoan ban muon chinh sua thong tin:";
        setColor(7);
        getline(cin, option);
    } while (searchUsername(option, editUser) == false);

    int editChoice;
    do {
        setColor(12);
        cout << "Chinh sua thong tin cho " << option << endl;
        setColor(7);
        setColor(11);
        cout << "--------------------------------------\n";
        cout << "| 0. Thoat                           |" << endl;
        cout << "| 1. Sua Gioi tinh                   |" << endl;
        cout << "| 2. Sua dia chi                     |" << endl;
        cout << "| 3. Sua so dien thoai               |" << endl;
        cout << "| 4. Luu                             |" << endl;
        cout << "--------------------------------------\n";
        setColor(7);
        setColor(12);
        cout << "Nhap lua chon cua ban: ";
        setColor(7);
        cinInt >> editChoice;

        switch (editChoice) {
            case 1: {
                int newSex;
                setColor(12);
                cout << "Nhap Gioi tinh (1: Nam, 2: Nu): ";
                setColor(7);

                // Vòng lặp kiểm tra đầu vào
                while (true) {
                    cin >> newSex;

                    if (newSex == 1 || newSex == 2) {
                        break; // Thoát vòng lặp nếu giá trị hợp lệ
                    } else {
                        setColor(12);
                        cout << "Chi duoc nhap 1 hoac 2! Vui long nhap lai: ";
                        setColor(7);
                    }
                }

                editUser.setSex(newSex);
                setColor(12);
                cout << "Gioi tinh da duoc cap nhat!" << endl;
                setColor(7);
            }
            case 2: {
                string newAddress;
                setColor(12);
                cout << "Nhap Dia chi moi: ";
                setColor(7);
                getline(cin, newAddress);
                    while (newAddress.empty()) {
                    setColor(12);
                cout << "Dia chi khong duoc de trong. Vui long nhap lai." << endl;
                cout << "Nhap Dia chi moi: ";
                setColor(7);
                getline(cin, newAddress);
                 }
                editUser.setAddress(newAddress);
                setColor(12);
                cout << "Dia chi da duoc cap nhat!" << endl;
                setColor(7);
                break;
            }
            case 3: {
                string newNum;
                setColor(12);
                cout << "Nhap so dien thoai moi: ";
                setColor(7);
                getline(cin, newNum);
                while (newNum.empty()) {
                    setColor(12);
                    cout << "So dien thoai khong duoc de trong. Vui long nhap lai." << endl;
                                    cout << "Nhap so dien thoai moi: ";
                setColor(7);
                getline(cin, newNum);
                }
                editUser.setNumber(newNum);
                setColor(12);
                cout << "So dien thoai da duoc cap nhat!" << endl;
                setColor(7);
                break;
            }
            case 4: {
                updateAccount(editUser);
                break;
            }
        }
    } while (editChoice != 6 && editChoice != 0);
}



int ShowStaffMenu(UserAccount user)
{
    char tiepTuc;
    do
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        int choice;
        setColor(11);
        cout<<" _   _  _    _            _   _      __      __ _____  ______  _   _ \n";
		cout<<"| \\ | || |  | |    /\\    | \\ | |     \\ \\    / /|_   _||  ____|| \\ | |\n";
		cout<<"|  \\| || |__| |   /  \\   |  \\| |      \\ \\  / /   | |  | |__   |  \\| |\n";
		cout<<"| . ` ||  __  |  / /\\ \\  | . ` |       \\ \\/ /    | |  |  __|  | . ` |\n";
		cout<<"| |\\  || |  | | / ____ \\ | |\\  |        \\  /    _| |_ | |____ | |\\  |\n";
		cout<<"|_| \\_||_|  |_|/_/    \\_\\|_| \\_|         \\/    |_____||______||_| \\_|\n";
        setColor(7);
        cout<<"\n";
        cout << "╔══════════════════════════════════════════════════════╗" << endl;
        cout << "║ 1. Xem danh sach va chinh sua thong tin khach hang   ║" << endl;
        cout << "║ 2. Xoa tai khoan khach hang                          ║" << endl;
        cout << "║ 3. Xem hoa don khach hang                            ║" << endl;
        cout << "║ 4. Dang xuat                                         ║" << endl;
        if(user.getRoles() == 2) cout << "║ 5. Quay lai man hinh quan ly.                        ║" << endl;
        cout << "╚══════════════════════════════════════════════════════╝" << endl;
        setColor(12);
        cout << "Nhap lua chon cua ban!: ";
        setColor(7);
        cinInt >> choice;
        switch(choice)
        {
            case 1:
            {
                 handleViewAndEditCustomer();
                 break;
            }
            case 2: {
                showList();
                string userDelete;
                setColor(12);
                cout << "Nhap ten tai khoan khach hang muon xoa (bo trong de huy): ";
                setColor(7);
                getline(cin, userDelete);
                if(userDelete == "") break;
                if (deleteAccount(userDelete, user.getUsername())) {
                    setColor(12);
                    cout << "Tai khoan da duoc xoa thanh cong." << endl;
                    setColor(7);
                } 
                else 
                {
                    setColor(12);
                    cout << "Khong tim thay tai khoan!" << endl;
                    setColor(7);
                }

                break;
            }
            case 3:
            {
                showList();
                string userName;
                cout << "Nhap ten tai khoan khach hang muon xem hoa don(bo trong de huy): ";
                getline(cin, userName);
                if(userName == "") break;
                if(searchAccount(userName))
                {
                    string fileName = "database/history/" + userName + ".txt";
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
                    setColor(11);
                    cout << "╔══════════════════════════════════════════════════════════════════════╗\n";
                    cout << "║ " << left << setw(15) << "Ten mon"
                         << "║ " << setw(10) << "Gia"
                         << "║ " << setw(10) << "So luong"
                         << "║ " << setw(15) << "Tong tien"
                         << "║ " << "Ngay mua" << "   ║\n";
                    cout << "╠══════════════════════════════════════════════════════════════════════╣\n";

                    string line;
                    while (getline(file, line)) {
                        istringstream iss(line);
                        string itemName, Date;
                        int price, quantity, total;

                        iss >> itemName >> price >> quantity >> total >> Date;

                        cout << "║ " << left << setw(15) << itemName
                             << "║ " << setw(10) << price
                             << "║ " << setw(10) << quantity
                             << "║ " << setw(15) << total
                             << "║ " << Date << " ║\n";
                    }
                    cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
                    setColor(7);
                    file.close();
                }
                else 
                {
                    cout << "Khong tim thay tai khoan!" << endl;
                }
                break;
            }
            case 4:
            {
                system("cls");
                updateAccount(user);
                displayMenu(50);        
            }
            case 5:
        	{
        		system("cls");
        		ShowManageMenu(user);
			}
        }
        setColor(12);
        cout << "Ban co muon tiep tuc? (y/n): ";
        setColor(7);
        cin >> tiepTuc;
        system("cls");
    }
    while (tiepTuc == 'y' || tiepTuc == 'Y');
    return 1;
}
