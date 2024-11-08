#pragma once

#include <iostream>
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
        if (replaceUnderscore(username) == s) 
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
    cout << "+---------------+------------------+-------+---------+------+------------+-----------------------+" << endl;
    cout << "| Username      | Password         | Roles | Credits | Sex  |  Number    | Address               |" << endl;
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

bool searchAccount(const string& usernameToSearch) 
{
    ifstream inputFile("database/account.txt");
    
    if (!inputFile.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return false;
    }

    string line;
    bool accountFound = false;

    while (getline(inputFile, line)) {
        string username;
        istringstream iss(line);
        iss >> username;

        if (replaceUnderscore(username) == usernameToSearch) {
            accountFound = true;
            cout << "Tai khoan tim thay: " << username << endl;
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


int ShowStaffMenu(UserAccount user)
{
    char tiepTuc;
    do
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        int choice;

        cout << "==================== Menu nhan vien ====================" << endl;
        cout << "1. Xem danh sach va chinh sua thong tin khach hang" << endl;
        cout << "2. Xoa tai khoan khach hang" << endl;
        cout << "3. Xem hoa don khach hang" << endl;
        cout << "4. Dang xuat" << endl;
        if(user.getRoles() == 2) cout << "5. Quay lai man hinh quan ly.\n" << endl;
        cout << "Nhap lua chon cua ban: ";
        cinInt >> choice;
        switch(choice)
        {
            case 1:
            {
                showList();
                char luaChon;
                string option;
                cout<<"Ban co muon chinh sua khach hang khong?"<<endl;
                cout<<"Lua chon cua ban(Y/N):";
                cinInt>>luaChon;
                if(luaChon != 'y' && luaChon != 'Y') break;

                cin.ignore();
                UserAccount editUser("Null","Null",0,0,0,"Null","Null");
                do
                {
                    cout<<"Nhap ten tai khoan ban muon chinh sua thong tin:";
                    getline(cin, option);
                }while (searchUsername(option, editUser) == false);
                int editChoice;
                do 
                {
                    cout << "Chinh sua thong tin cho " << option << endl;
                    cout << "0. Thoat" << endl;
                    cout << "1. Sua Gioi tinh" << endl;
                    cout << "2. Sua dia chi" << endl;
                    cout << "3. Sua so dien thoai" << endl;
                    cout << "4. Luu" << endl;
                    cout << "Nhap lua chon cua ban: ";
                    cinInt >> editChoice;
                    bool edit = false;
                    switch (editChoice) 
                    {
                        case 1:
                        {
                            int newSex;
                            cout << "Nhap Gioi tinh (1: Nam, 2: Nu): ";
                            cinInt >> newSex;
                            editUser.setSex(newSex);
                            cout << "Gioi tinh da duoc cap nhat." << endl;
                            break;
                        }
                        case 2:
                        {
                            string newAddress;
                            cout << "Nhap Dia chi moi: ";
                            cin.ignore();
                            getline(cin, newAddress);
                            editUser.setAddress(newAddress);
                            cout << "Dia chi da duoc cap nhat." << endl;
                            break;
                        }
                        case 3:
                        {
                            string newNum;
                            cout << "Nhap so dien thoai moi: ";
                            cin.ignore();
                            getline(cin, newNum);
                            editUser.setNumber(newNum);
                            cout << "So dien thoai da duoc cap nhat." << endl;
                            break;
                        }
                        case 4:
                        {
                            updateAccount(editUser);
                            break;
                        }
                    }
                } 
                while (editChoice != 6 && editChoice != 0);
                break;
            }
            case 2: {
                showList();
                string userDelete;
                cout << "Nhap ten tai khoan khach hang muon xoa(bo trong de huy): ";
                cin.ignore();
                getline(cin, userDelete);
                if(userDelete == "") break;
                if (deleteAccount(userDelete, user.getUsername())) {
                    cout << "Tai khoan da duoc xoa thanh cong." << endl;
                } 
                else 
                {
                    cout << "Khong tim thay tai khoan!" << endl;
                }

                break;
            }
            case 3:
            {
                showList();
                string userName;
                cout << "Nhap ten tai khoan khach hang muon xem hoa don(bo trong de huy): ";
                cin.ignore();
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

                    cout << left << setw(15) << "Ten mon"
                        << setw(10) << "Gia"
                        << setw(10) << "So luong"
                        << setw(15) << "Tong tien"
                        << "Ngay mua" << endl;
                    cout << string(60, '-') << endl;

                    string line;
                    while (getline(file, line)) {
                        istringstream iss(line);
                        string itemName, Date;
                        int price, quantity, total;

                        iss >> itemName >> price >> quantity >> total >> Date;

                        cout << left << setw(15) << itemName
                            << setw(10) << price
                            << setw(10) << quantity
                            << setw(15) << total
                            << Date << endl;
                    }

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
                displayMenu(120);        
            }
            case 5:
        	{
        		system("cls");
        		ShowManageMenu(user);
			}
        }
        cout << "Ban co muon tiep tuc? (y/n): ";
        cin >> tiepTuc;
        system("cls");
    }
    while (tiepTuc == 'y' || tiepTuc == 'Y');
    return 1;
}
