#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "doiTuong.h"

class InputStream {
public:
    template <typename T>
    InputStream& operator>>(T& value) {
        while (true) {
            cin >> value;
            if (cin.fail()) 
			{
				cout<<"\nBan vua nhap chu thay vi nhap so, hay nhap lai:";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }
        return *this;
    }
};
InputStream cinInt;

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
    cout<<"password: ";
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
        fileIn.close();
        return false;
    }

    string userTemp, passTemp, number, address, line;
    int roles, credits, sex;
    bool found = false;

    fileOut << "Username/Password/Roles/Credits/Sex/Number/Address" << endl;
    
    getline(fileIn, line);
    
    while (fileIn >> userTemp >> passTemp >> roles >> credits >> sex >> number >> address) {
        if (replaceUnderscore(userTemp) == user.getUsername()) {
            fileOut << replaceSpace(userTemp) << " " 
                    << user.getPassword() << " " 
                    << user.getRoles() << " " 
                    << user.getCredits() << " " 
                    << user.getSex() << " " 
                    << user.getNumber() << " " 
                    << user.getAddress() << endl;
            found = true;
        } else {
            fileOut << replaceSpace(userTemp) << " " << passTemp << " " 
                    << roles << " " << credits << " " << sex << " " 
                    << number << " " << address << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    // Kiểm tra và thay thế file cũ
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

string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int day = ltm->tm_mday;
    int month = 1 + ltm->tm_mon;
    int year = 1900 + ltm->tm_year;

    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}