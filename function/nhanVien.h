#pragma once

#include <iostream>
#include "doiTuong.h"
#include "ham.h"
using namespace std;
bool searchUsername(ifstream& file, const string& s, UserAccount &user) {
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
    return false;
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
        string username;
        istringstream iss(line);
        iss >> username;

        if (replaceUnderscore(username) == usernameToSearch) {
            accountFound = true;
            cout << "Tai khoan tim thay: " << line << endl;
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
        int choice;

        cout << "==================== Menu nhan vien ====================" << endl;
        cout << "1. Xem danh sach va chinh sua thong tin khach hang" << endl;
        cout << "2. Xoa tai khoan khach hang" << endl;
        cout << "3. Xem hoa don khach hang" << endl;
        cout << "4. Dang xuat" << endl;
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
                string option;
                int count = 0, value;
                while (file >> username >> password >> roles >> credits >> sex >> number >> address) {
                    cout << "Username: " << username 
                        << ", Password: " << password 
                        << ", Roles: " << roles 
                        << ", Credits: " << credits 
                        << ", Sex: " << sex 
                        << ", Number: " << number 
                        << ", Address: " << address 
                        << endl;
                        count++;
                }
                char luaChon;
                cout<<"Ban co muon chinh sua khach hang khong?"<<endl;
                cout<<"Lua chon cua ban(Y/N):";
                cin>>luaChon;
                if(luaChon != 'y' && luaChon != 'Y') break;

                file.clear();
                file.seekg(0);
                cin.ignore();
                UserAccount editUser("Null","Null",0,0,0,"Null","Null");
                do
                {
                    cout<<"Nhap ten tai khoan ban muon chinh sua thong tin:";
                    getline(cin, option);
                }while (searchUsername(file, option, editUser) == false);
                file.close();
                int editChoice;
                do 
                {
                    cout << "Chinh sua thong tin cho " << option << endl;
                    cout << "0. Thoat" << endl;
                    cout << "1. Sua Credits" << endl;
                    cout << "2. Sua Password" << endl;
                    cout << "3. Sua Gioi tinh" << endl;
                    cout << "4. Sua dia chi" << endl;
                    cout << "5. Sua so dien thoai" << endl;
                    cout << "6. Luu" << endl;
                    cout << "Nhap lua chon cua ban: ";
                    cin >> editChoice;
                    bool edit = false;
                    switch (editChoice) 
                    {
                        case 1:
                        {
                            int newCredits;
                            cout << "Nhap so Credits moi: ";
                            cin >> newCredits;
                            editUser.setCredits(newCredits);
                            cout << "Credits da duoc cap nhat." << endl;
                            break;
                        }
                        case 2:
                        {
                            string newPassword;
                            cout << "Nhap Password moi: ";
                            getline(cin, newPassword);
                            editUser.setPassword(newPassword);
                            cout << "Password da duoc cap nhat." << endl;
                            break;
                        }
                        case 3:
                        {
                            int newSex;
                            cout << "Nhap Gioi tinh (1: Nam, 2: Nu): ";
                            cin >> newSex;
                            editUser.setSex(newSex);
                            cout << "Gioi tinh da duoc cap nhat." << endl;
                            break;
                        }
                        case 4:
                        {
                            string newAddress;
                            cout << "Nhap Dia chi moi: ";
                            cin.ignore();
                            getline(cin, newAddress);
                            editUser.setAddress(newAddress);
                            cout << "Dia chi da duoc cap nhat." << endl;
                            break;
                        }
                        case 5:
                        {
                            string newNum;
                            cout << "Nhap so dien thoai moi: ";
                            cin.ignore();
                            getline(cin, newNum);
                            editUser.setNumber(newNum);
                            cout << "So dien thoai da duoc cap nhat." << endl;
                            break;
                        }
                        case 6:
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
                string userDelete;
                cout << "Nhap ten tai khoan khach hang muon xoa: ";
                cin.ignore();
                getline(cin, userDelete);
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
                string userName;
                cout << "Nhap ten tai khoan khach hang muon xem hoa don: ";
                cin.ignore();
                getline(cin, userName);
                if(searchAccount(userName))
                {
                    string fileName = "database/history/"+userName+".txt", line;
                    ifstream file(fileName);
                    if(!file.is_open())
                    {
                        cout<<"Khong co thong tin!";                            
                        break;
                    }
                    while(getline(file,line))
                    {
                        if(line.empty()) cout<<"Trang thong tin!";
                        cout<<line<<endl;
                    }
                    file.close();
                }
                else 
                {
                    cout << "Khong tim thay tai khoan!" << endl;
                }
                break;
            }
        }
        cout << "Ban co muon tiep tuc? (y/n): ";
        cin >> tiepTuc;
        system("cls");
    }
    while (tiepTuc == 'y' || tiepTuc == 'Y');
    return 1;
}
