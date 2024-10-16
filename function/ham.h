#pragma once
#include <iostream>
#include <string>
#include "doiTuong.h"

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

string replaceSpace(const string& s) {
    string result = s;
    for (char& c : result) {
        if (c == ' ') {
            c = '_';
        }
    }
    return result;
}
string replaceUnderscore(const string& s) {
    string result = s;
    for (char& c : result) {
        if (c == '_') {
            c = ' ';
        }
    }
    return result;
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

    string userTemp, passTemp, line, number, address;
    int roles, credits, sex;
    bool found = false;
    fileOut<<"Username/Password/Roles/Credits/Sex/Number/Address"<<endl;
    getline(fileIn, line);
    
    while (fileIn >> userTemp >> passTemp >> roles >> credits>>sex>>number>>address) {
        if (replaceUnderscore(userTemp) == user.getUsername()) 
        {
            fileOut << replaceSpace(userTemp) << " " << passTemp << " " << user.getRoles() << " " << user.getCredits()<<" " <<user.getSex()<<" " << user.getNumber()<<" "<< user.getAddress()<< endl;
            found = true;
        } else {
            fileOut << replaceSpace(userTemp) << " " << passTemp << " " << roles << " " << credits <<" "<<sex<<" " << number<<" "<< address << endl;
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