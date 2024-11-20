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


void login() {
    system("cls");

    ifstream file("database/account.txt");
		string userTemp, passTemp, number, address, userName, password;
		int roles, credits, sex;    

    if (!file.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }

    bool isLoggedIn = false;
    int width = 50;
    //vẽ
    printBorder(width);
    printInBox("DANG NHAP", width, false, 11); // Tiêu đề màu xanh dương nhạt
    printBottomBorder(width);
    while(isLoggedIn == false)
	{
		if(isLoggedIn) break;
        userName = cinInBox("Nhap tai khoan: ", width, true, 7);
        file.clear();
        file.seekg(0);
        string line;
        getline(file, line);
	    while(file>>userTemp>>passTemp>>roles>>credits>>sex>>number>>address)
	    {
            if (userName == replaceUnderscore(userTemp)) {
                bool passwordCorrect = false;
				int countWrong = 0;
                while (!passwordCorrect)
				{
					if(countWrong == 3)
					{
						printBorder(width);
						printInBox("Ban da nhap sai 3 lan", width, false , 4);
						printBottomBorder(width);
						break;
					}
                    password = cinInBox1("Nhap mat khau: ", width, true, 9);
                    if (password == passTemp) {
                    		printBorder(width);
                            printInBox("DANG NHAP THANH CONG", width, false ,10);
                            printBottomBorder(width);
                        isLoggedIn = true;
                        passwordCorrect = true;
                    } else {
                    	printBorder(width);
                        printInBox("Password khong dung, nhap lai", width, false , 4);
                        printBottomBorder(width);
                        countWrong++;
                    }
                }
                break;
        	}
	    }
	    if(isLoggedIn == false) {
	    	printBorder(width);
	    	printInBox("Khong the dang nhap vao tai khoan.", width, false , 4);
        	printBottomBorder(width);
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
	int width = 50;
    string userName, password;

    ifstream fileCheck("database/account.txt");
    if (!fileCheck.is_open()) {
        cout << "Khong the mo file tai khoan!" << endl;
        return;
    }
    string userTemp, passTemp, passwordTwo;
        int sex, credits, roles;
        string number,address;
    
    printBorder(width);
    printInBox("DANG KY", width, false, 11); // Tiêu đề màu xanh dương nhạt
    printBottomBorder(width);
    
    while(1)
    {
        bool checkAccount = true;
		userName = cinInBox("Nhap tai khoan moi: ", width, true, 9);
        fileCheck.clear();
        fileCheck.seekg(0);
        string line;
        getline(fileCheck, line);
        while (fileCheck >> userTemp >> passTemp >> roles >> credits >> sex >> number >> address)
        {
            if(replaceSpace(userName) == userTemp)
            {
                checkAccount = false;
            }
        }
        if(checkAccount == true) break;
        else {
        	printBorder(width);
            printInBox("Ten tai khoan bi trung", width, false , 4);
            printBottomBorder(width);
        }
    }
    fileCheck.close();
    while (true) {
        password = cinInBox("Nhap mat khau moi: ", width, true, 9);
        while(checkPasswordStrength(password, width) == false)
        {
        	password = cinInBox("Nhap mat khau moi: ", width, true, 9);
		}
		passwordTwo = cinInBox("Nhap lai mat khau moi: ", width, true, 9);
		while(password != passwordTwo)
		{
        	printBorder(width);
            printInBox("Ban nhap mat khau khong dung vui long tao lai.", width, false , 4);
            printBottomBorder(width);
            
			password = cinInBox("Nhap mat khau moi: ", width, true, 9);
			passwordTwo = cinInBox("Nhap lai mat khau moi: ", width, true, 9);		
		}
		
        int sex;
        string number, address;
		sex = cinIntInBox("Gioi tinh(1: Nam, 2: Nu): ", width, true, 10);
		while(sex != 1 && sex != 2)
		{
        	printBorder(width);
            printInBox("Gioi tinh chu duoc chon 1: Nam, 2: Nu!", width, false , 4);
            printBottomBorder(width);			
			sex = cinIntInBox("Gioi tinh(1: Nam, 2: Nu): ", width, true, 10);
		}
		
		number = cinInBox("Nhap so dien thoai: ", width, true, 9);
		while(checkVietnamesePhoneNumber(number, width) == false)
		{
			number = cinInBox("Nhap so dien thoai: ", width, true, 9);
		}
		
        address = cinInBox("Nhap dia chi: ", width, true, 9);
        file << replaceSpace(userName) << " " << password << " "<< 0 <<" "<< 0<<" "<< sex <<" "<< replaceSpace(number) << " "<< replaceSpace(address)<<endl;

    	printBorder(width);
        printInBox("DANG KY THANH CONG <3", width, false , 10);
        printBottomBorder(width);
		this_thread::sleep_for(chrono::milliseconds(2000));
        file.close();
        displayMenu(50);
        break;
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
            exit(0); // Thoát chương trình
    }
}
//output function//

int navigateMenu(const vector<string>& options, UserAccount user) {
    int choice = 0;
    QuanLyChucNang qlcn;
    while (true) {
        system("cls");
        qlcn.veSieuThi(user);
        cout << "┌───────────────────────────────────────────────────────┐\n";
        cout << "│       ";
        setColor(9); // Màu xanh dương cho chữ
        cout << "      CHAO MUNG DEN HE THONG QUAN LY";
        setColor(7); // Màu trắng
        cout << "            │\n";

        cout << "│                 ";
        setColor(9); // Màu xanh dương cho chữ
        cout << "      SIEU THI";
        setColor(7); // Màu trắng
        cout << "                        │\n";

        cout << "└───────────────────────────────────────────────────────┘\n";
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
int naptien(int &credits) {
    int x = 0, y = 0; // Góc trên bên trái

    // Tạo khung bao
    setColor(11); // Màu xanh dương nhạt
    gotoxy(x, y); cout << "╔════════════════════════════════════════════╗";
    for (int i = 1; i <= 7; ++i) { // Đủ dòng để chứa nội dung
        gotoxy(x, y + i); cout << "║                                            ║";
    }
    gotoxy(x, y + 8); cout << "╚════════════════════════════════════════════╝";
    setColor(7); // Trở lại màu mặc định

    // Hiển thị hướng dẫn và con trỏ nhập liệu
    gotoxy(x + 2, y + 1); cout << "Nhap so tien nap:";
    gotoxy(x + 2, y + 3); cout << "(Lon hon 0 va nho hon 10 trieu)";
    gotoxy(x + 2, y + 5); cout << "So tien: ";

    // Nhập liệu
    do {
        gotoxy(x + 12, y + 5); // Vị trí nhập liệu
        cout << "          "; // Xóa giá trị cũ
        gotoxy(x + 12, y + 5); // Đặt lại con trỏ
        cinInt >> credits;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            setColor(12); // Màu đỏ
            gotoxy(x + 2, y + 6); cout << "Nhap khong hop le! Vui long nhap lai.";
            setColor(7);
            continue;
        }

        if (credits <= 0 || credits >= 10000000) {
            setColor(12);
            gotoxy(x + 2, y + 6); cout << "So tien khong hop le! Vui long nhap lai.";
            setColor(7);
        } else {
            gotoxy(x + 2, y + 6); cout << "                                          ";
        }
    } while (credits <= 0 || credits >= 10000000);

    // Hiển thị thông báo nạp tiền thành công bên trong khung
    gotoxy(x + 2, y + 6); 
    setColor(10); // Màu xanh lá
    cout << "Dang nap tien...";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    gotoxy(x + 2, y + 6); 
    cout << "Nap thanh cong: " << credits << " VND.            ";
    setColor(7);
    return credits;

}

int ShowMainMenu(UserAccount user) {
    QuanLyChucNang qlcn;
    qlcn.docSanPhamTuFile("database/product.txt"); // Đọc danh sách sản phẩm từ file
    
    // Danh sách các lựa chọn trong menu
    vector<string> options = {
        "Chon quay san pham.",
        "Tim kiem san pham",
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
                {
                system("cls");
                qlcn.xulytimkiem(user);
                break;
                }
            }

            case 2: {
                system("cls");

                int credits;
                system("cls");
                naptien(credits);
                
                user.accountDeposit(credits);
                cout<<endl<<endl;
                break;
            }
            
            case 3: {
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
                setColor(7); // Xanh dương nhạt
                cout << "╔══════════════════════════════════════════════════════════════════════╗\n";
                cout << "║ " << left << setw(15) << "Ten mon"
                     << "║ " << setw(10) << "Gia"
                     << "║ " << setw(10) << "So luong"
                     << "║ " << setw(15) << "Tong tien"
                     << "║ " << "Ngay mua" << "   ║\n";
                cout << "╠══════════════════════════════════════════════════════════════════════╣\n";

                string line;
                // while (getline(file, line)) {
                //     istringstream iss(line);
                //     string itemName, Date;
                //     int price, quantity, total;

                //     iss >> itemName >> price >> quantity >> total >> Date;

                //     cout << "| " << left << setw(15) << itemName
                //          << "| " << setw(10) << price
                //          << "| " << setw(10) << quantity
                //          << "| " << setw(15) << total
                //          << "| " << Date << " |\n";
                // }
                // cout << "========================================================================\n";
                while (getline(file, line)) {
                istringstream iss(line);
                string itemName, date, temp;
                int price, quantity, total;

                // Đọc tên sản phẩm trước (có thể chứa nhiều từ)
                getline(iss, itemName, ' ');
                while (iss >> temp) { // Đọc tiếp nếu còn dữ liệu
                    if (isdigit(temp[0])) { // Gặp số thì dừng, xử lý tiếp giá trị số
                        iss.seekg(-(int)temp.length(), ios::cur); // Lùi lại con trỏ
                        break;
                    }
                    itemName += " " + temp; // Ghép phần còn lại vào tên
                }

                // Đọc các giá trị số và ngày tháng
                iss >> price >> quantity >> total >> date;

                // In thông tin ra màn hình
                cout << "║ " << left << setw(15) << itemName
                    << "║ " << setw(10) << price
                    << "║ " << setw(10) << quantity
                    << "║ " << setw(15) << total
                    << "║ " << date << " ║\n";
                }
                cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
                            file.close();
                setColor(7); // Trắng
                break;
            }
            case 4: {
                string newPassword;
                bool validPassword = false;

                while (!validPassword) {
                setColor(14); // Màu vàng
                    cout << "Nhap Password moi: ";
                    setColor(7); // Màu trắng
                    getline(cin, newPassword);

                    // Kiểm tra độ mạnh của mật khẩu
                    validPassword = checkPasswordStrength1(newPassword);
                }

                // Cập nhật mật khẩu khi hợp lệ
                user.setPassword(newPassword);
                setColor(10); // Màu xanh lá
                cout << "Password da duoc cap nhat.\n";
                setColor(7); // Màu trắng

                updateAccount(user); // Gọi hàm cập nhật tài khoản
                break;
            }
            case 5: {
                system("cls");
                updateAccount(user);
                displayMenu(50);
                return 0;
            }
            case 6:{
                system("cls");
                ShowManageMenu(user);
                break;
            }
        }
        setColor(9); // Xanh dương nhạt
        cout << "\nNhan phim bat ky de tiep tuc...\n";
        setColor(7); // Trắng
        system("pause");
    }
}



