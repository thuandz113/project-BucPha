#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> // Dùng cho _getch() trên Windows
using namespace std;

class UserAccount
{
    private:
        int roles;//0 : khách hàng bth, 1: nhân viên , 2: quản lý
        string password, username;
    public:
        
};


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

void login() {
    system("cls");

    ifstream file("Account.txt");
    
    string userName, password;
    string userTemp, passTemp;
    int roles;
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
        while (getline(file, line)) 
        {
            file >> userTemp >> passTemp >> roles;
            if (userName == userTemp) {
                inputPass(password);
                if (password == passTemp) {
                    cout << "\nDang nhap thanh cong\n";
                    isLoggedIn = true; // Đánh dấu là đã đăng nhập thành công
                    break;
                } else {
                    cout << "\nPassword khong chinh xac, vui long nhap lai\n\n";
                    break; // Thoát vòng lặp nếu password không khớp
                }
            }
        }
        if (!isLoggedIn) {
            cout << "\nUserName khong chinh xac, vui long nhap lai\n\n";
        }

        else 
        {
            switch(roles)
            {
                case 0:// khách hàng
                {
                    cout<<"Chao mung khach hang da quay tro lai <3"<<endl;
                    //thêm menu
                    break;
                }
                case 1:// nhân viên
                {
                    cout<<"Chao mung nhan vien da quay tro lai <3"<<endl;
                    //thêm menu
                    break;                    
                }
                case 2:// quản lý
                {
                    cout<<"Chao mung quan ly da quay tro lai <3"<<endl;
                    //thêm menu
                    break;
                }
            }
            break;
        }
    }

    if (!isLoggedIn) {
        cout << "\n\nDa nhap qua 3 lan. Vui long cho mot chut va thu lai\n";
    }

    file.close(); // Đóng file sau khi đọc xong
}

void registerAccount() {
    ofstream file("Account.txt", ios::app);
    if (!file.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }

    string userName, password;

    ifstream fileCheck("Account.txt");
    if (!fileCheck.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }
    string userTemp, passTemp;
    while(1)
    {
        bool checkAccount = true;
        cout << "Nhap ten tai khoan moi: ";
        cin.ignore();
        getline(cin, userName);
        file.clear();
        file.seekp(0);
        string line;
        while (getline(fileCheck, line))
        {
            fileCheck >> userTemp >> passTemp;
            if(userName == userTemp)
            {
                checkAccount = false;
            }
        }
        if(checkAccount == true) break;
        else cout<<"Ten tai khoan bi trung, vui long nhap lai."<<endl;
    }
    fileCheck.close();
    while (true) {
        cout << "Nhap mat khau moi (it nhat 8 ky tu): ";
        inputPass(password);

        if (checkPass(password)) {
            file << userName << " " << password << " "<<0 << endl;
            cout << "Dang ky tai khoan thanh cong!" << endl;
            break;
        } else {
            cout << "Mat khau khong du manh, vui long thu lai." << endl;
        }
    }
    
    file.close();
}


void displayMenu(int width) {
    system("cls");
    string title = "CHAO MUNG DEN VOI SIEU THI CUA BAO THANH THIEN";
    string message = "BAN CAN GI";
    
    printBorder(width);
    printInBox(title, width);
    printBorder(width);
    printInBox(message, width);
    printBorder(width);

    string option1 = "Dang nhap";
    string option2 = "Dang ky";
    
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

int main() {
    int width = 120;
    displayMenu(width);
    return 0;
}
