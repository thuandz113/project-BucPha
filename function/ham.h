#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "doiTuong.h"

string maskString(const string& str) 
{
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        result += '*';
    }
    return result;
}
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
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void printBorder(int width) {
    cout << "\t\t\t\t\t\t\t\t" << u8"┌"; // Góc trên bên trái
    for (int i = 0; i < width - 2; i++) 
        cout << u8"─"; // Đường ngang
    cout << u8"┐" << endl; // Góc trên bên phải
}

// Hàm vẽ đường viền dưới
void printBottomBorder(int width) {
    cout << "\t\t\t\t\t\t\t\t" << u8"└"; // Góc dưới bên trái
    for (int i = 0; i < width - 2; i++) 
        cout << u8"─"; // Đường ngang
    cout << u8"┘" << endl; // Góc dưới bên phải
}

// Hàm in nội dung căn giữa trong khung vừa đủ
void printInBox(string content, int width, bool highlight = false, int color = 7) {
    int contentLength = content.length();
    // Đảm bảo chiều rộng của khung đủ để bao bọc nội dung
    width = max(contentLength + 2, width); // Chiều rộng tối thiểu là đủ cho nội dung
    int padding = (width - contentLength - 2) / 2; // Tính khoảng cách bên trái

    // In đường viền bên trái
    cout << "\t\t\t\t\t\t\t\t" << u8"│"; 

    // Đổi màu khi có highlight
    if (highlight) 
        setColor(14); // Màu vàng
    else 
        setColor(color); // Màu mặc định

    // In khoảng trắng trước nội dung
    for (int i = 0; i < padding; i++) 
        cout << " ";

    // In nội dung
    cout << content;

    // In khoảng trắng sau nội dung
    for (int i = 0; i < width - padding - contentLength - 2; i++) 
        cout << " ";

    // Trả lại màu mặc định
    setColor(7); 

    // In đường viền bên phải
    cout << u8"│" << endl; 
}

void showWelcomeArt() {
    system("cls");
    SetConsoleOutputCP(CP_UTF8); // Thiết lập mã hóa UTF-8
    setColor(14);
    cout<<endl<<endl;
    // ASCII art
    const string art[] = {
        "\t\t\t\t ░██████╗░██╗███████╗██╗░░░██╗     ████████╗██╗░░██╗░██╗     ██╗░░░██╗░████████╗░██████░╔███████╗",
        "\t\t\t\t ██╔════╝░██║██╔════╝██║░░░██║     ╚══██╔══╝██║░░██║░██║     ██║░░░██║░╚══██╔══╝██╔═══  ╚═════██╗",
        "\t\t\t\t ╚█████╗░░██║█████╗░░██║░░░██║     ░░░██║░░░███████║░██║     ██║░░░██║░░░░██║░░░██║░░░░░░██████╔╝",
        "\t\t\t\t ░╚═══██╗░██║██╔══╝░░██║░░░██║     ░░░██║░░░██╔══██║░██║     ██║░░░██║░░░░██║░░░██║░░░░░░██╔═══╝ ",
        "\t\t\t\t ██████╔╝░██║███████╗╚██████╔╝     ░░░██║░░░██║░░██║░██║     ╚██████╔╝░░░░██║░░░╚██████ ╔██║░░░  ",
        "\t\t\t\t ╚═════╝░░╚═╝╚══════╝░╚═════╝      ░░░╚═╝░░░╚═╝░░╚═╝░╚═╝      ╚═════╝░░░░░╚═╝░░░╚═════╝ ╚███████ "
    };
    // Hiển thị từng dòng với hiệu ứng chậm
    for (const string& line : art) {
        for (char c : line) {
            cout << c;
            Sleep(0.8); // Độ trễ giữa các ký tự (ms)
        }
        cout << endl;
        Sleep(30); // Độ trễ giữa các dòng (ms)
    }
    setColor(7);
    // Thông báo
    cout << "\nBam Enter de bat dau...";
    cin.ignore(); // Chờ người dùng nhấn Enter
}
void ResetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}