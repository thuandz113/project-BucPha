#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> // Dùng cho _getch() trên Windows
using namespace std;

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

void login(const string& role, const string& filename) {
    system("cls");
    cout << "=== Moi ban dang nhap voi tu cach " << role << " ===" << endl;
    ifstream file(filename);
    
    string userName, password;
    string userTemp, passTemp;

    if (!file.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }

    file >> userTemp >> passTemp;
    file.close();

    for (int count = 0; count < 3; ++count) {
        cout << "UserName: ";
        if (count == 0) cin.ignore(); // Chỉ ignore ở lần nhập đầu tiên để xóa '\n' còn sót lại
        getline(cin, userName);

        if (userName != userTemp) {
            cout << "\nUserName khong chinh xac, vui long nhap lai\n\n";
            continue;
        }

        inputPass(password);

        if (password != passTemp) {
            cout << "\nPassword khong chinh xac, vui long nhap lai\n\n";
            continue;
        }
        
        cout << "\nDang nhap thanh cong\n";
        return;
    }

    cout << "\n\nDa nhap qua 3 lan. Vui long cho mot chut va thu lai\n";
}

void registerAccount(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }

    string userName, password;
    cout << "Nhap ten tai khoan moi: ";
    cin.ignore(); // Ignore để xóa ký tự '\n' còn sót lại
    getline(cin, userName);

    while (true) {
        cout << "Nhap mat khau moi (it nhat 8 ky tu): ";
        inputPass(password);

        if (checkPass(password)) {
            file << userName << " " << password << endl;
            cout << "Dang ky tai khoan thanh cong!" << endl;
            break;
        } else {
            cout << "Mat khau khong du manh, vui long thu lai." << endl;
        }
    }
    
    file.close();
}

void handlePurchase() {
    cout << "\nChao mung den voi chuc nang mua hang!\n";
    cout << "Ban da co tai khoan khach hang chua? (y/n): ";
    char hasAccount;
    cin >> hasAccount;

    if (hasAccount == 'y' || hasAccount == 'Y') {
        login("khach hang", "customerAccount.txt");
    } else {
        cout << "Ban chua co tai khoan. Vui long dang ky tai khoan.\n";
        registerAccount("customerAccount.txt");
    }
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

    string option1 = "1. Dang nhap voi tu cach la quan li";
    string option2 = "2. Dang nhap voi tu cach la nhan vien";
    string option3 = "3. Mua hang";
    
    printInBox(option1, width);
    printInBox(option2, width);
    printInBox(option3, width);
    printBorder(width);
    
    int choice;
    cout << " Vui long nhap trong (1-3): "; 
    cout.flush(); 
    cin >> choice;

    while (choice < 1 || choice > 3) {
        cout << " Vui long nhap lai trong (1-3): "; 
        cout.flush(); 
        cin >> choice;
    }

    cout << " Ban da chon: " << choice << "" << endl;

    printBorder(width);
    system("cls");
    if (choice == 3) {
        handlePurchase(); // Gọi chức năng mua hàng
    } else if (choice == 1) {
        login("quan li", "managerAccount.txt");
    } else if (choice == 2) {
        login("nhan vien", "employeeAccount.txt");
    }
}

int main() {
    int width = 120;
    displayMenu(width);
    return 0;
}
