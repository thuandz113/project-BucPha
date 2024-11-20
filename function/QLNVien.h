#pragma once

#include <iostream>
#include "doiTuong.h"
#include "dangNhap.h"
using namespace std;

const int maxNV = 100;
bool checkPasss(const string &password) {
    return password.size() >= 8;
}

void registerEmployeeAccout(string &tenTaiKhoan){
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
        tenTaiKhoan = userName;
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

        inputPass(password);

        if (checkPasss(password)) 
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
            file << replaceSpace(userName) << " " << password << " "<< 1 <<" "<< 0<<" "<< sex <<" "<< replaceSpace(number) << " "<< replaceSpace(address)<<endl;
            cout << "Dang ky tai khoan thanh cong!" << endl;
            break;
        } else {
            cout << "Mat khau khong du manh, vui long thu lai." << endl;
        }
    }
    
    file.close();
}

class NhanVien {
    private:
        string maNhanVien;
        string tenNhanVien;
        string chucVu;
        string caLamViec;
        string tenTaiKhoan;
        int soGioLamViec;
        int soGioLamThem;
        float luongTheoGio;

    public:
        NhanVien(string maNV = "", string tenNV = "", string cv = "", string caLV = "", float luongGio = 0, int gioLV = 0, int gioLamThem = 0)
        : maNhanVien(maNV), tenNhanVien(tenNV), chucVu(cv), caLamViec(caLV), luongTheoGio(luongGio), soGioLamViec(gioLV), soGioLamThem(gioLamThem) {}
		int timKiemMaNhanVien()
		{
			ifstream infile("database/listEmployees.txt");
			int demMaNV = 0;
			int a[100], count= 0;
			NhanVien nv;
			if(infile.is_open())
			{
			 	while(true)
				{
					if(infile.eof()) break;
					nv.docFile(infile);
					string maNV = nv.getMaNV();
		            if (maNV.size() > 2) {
		                string part = maNV.substr(2); 
		                int partInt = stoi(part);
		                a[count++] = partInt;
		            }
				}
				infile.close();
			}
			if(count == 0) return 1;
			bool found = true;
			while(found == true)
			{
				++demMaNV;
				found = false;
				for(int i = 0; i < count ; i++)
				{
					if(a[i] == demMaNV) found = true;
				}
			}
			return demMaNV;
		}
        void nhap() {
            maNhanVien = "NV" + to_string(timKiemMaNhanVien());
            cout << "Ma nhan vien tu dong: " << maNhanVien << endl;
            cout << "Nhap ten nhan vien: ";
            cin.ignore();
            getline(cin, tenNhanVien);
            cout << "Nhap chuc vu: ";
            getline(cin, chucVu);
            cout << "Nhap ca lam viec: ";
            getline(cin, caLamViec);
            cout << "Nhap so gio lam viec: ";
            cinInt >> soGioLamViec;
            cout << "Nhap so gio lam them (neu co): ";
            cinInt >> soGioLamThem;
            luongTheoGio = getLuongByChucVu(chucVu);
        	char choice;
        	cout<<"ban co muon tao tai khoan cho nhan vien nay(y/n): ";
			cin>>choice;
        	if(choice=='y'||choice=='Y')
			{
        		registerEmployeeAccout(tenTaiKhoan);
			}
			else tenTaiKhoan = "None";
        }

        // Ham lay luong co ban theo chuc vu
        float getLuongByChucVu(string chucVu) {
            if (chucVu == "Quan ly cua hang") return 60000;
            // Các trường hợp khác cho các chức vụ khác nhau
            else return 15000;
        }

        // Ham tinh luong
        float tinhLuongThang() {
            float hesoLamThem = 1.5;
            return (soGioLamViec * luongTheoGio) + (soGioLamThem * luongTheoGio * hesoLamThem);
        }

        // Ham hien thi thong tin nhan vien
        void xuat() {
			setColor(7);
            cout << "| " << left << setw(5) << maNhanVien << " | "
            	 << left << setw(17) << tenTaiKhoan << " | "
                 << left << setw(17) << tenNhanVien << " | "
                 << left << setw(27) << chucVu << " | "
                 << left << setw(11) << caLamViec << " | "
                 << left << setw(5) << soGioLamViec << " | "
                 << left << setw(13) << soGioLamThem << " | "
                 << left << setw(9) << fixed << setprecision(0) << tinhLuongThang() << " |" << endl;
        }

        string getMaNV() {
            return maNhanVien;
        }

        // Ghi nhan vien vao file
        void ghiFile(ofstream &outfile) {
            outfile << maNhanVien << endl;
            outfile << tenTaiKhoan << endl;
            outfile << tenNhanVien << endl;
            outfile << chucVu << endl;
            outfile << caLamViec << endl;
            outfile << soGioLamViec << endl;
            outfile << soGioLamThem << endl;
            outfile << luongTheoGio << endl;
        }

        // Doc nhan vien tu file
        void docFile(ifstream &infile) {
            getline(infile, maNhanVien);
            getline(infile, tenTaiKhoan);
            getline(infile, tenNhanVien);
            getline(infile, chucVu);
            getline(infile, caLamViec);
            infile >> soGioLamViec;
            infile >> soGioLamThem;
            infile >> luongTheoGio;
            infile.ignore();
        }
		void capNhatCa(const string &caMoi) {
        caLamViec = caMoi;
		}

		// Hàm để cập nhật lương
		void capNhatLuong(float luongMoi) {
			luongTheoGio = luongMoi;
		}
};
// Khởi tạo biến static
class QLNV:public NhanVien{
	private:
		NhanVien dsNV[maxNV];
int n; //sl nhan vien
	public:
		QLNV():n(0){}
		//Ham them nv
		void themNV()
		{
			if(n>=maxNV){
				cout<<"Da du so luong nhan vien!"<<endl;
				return;
			}
			NhanVien nv;
			nv.nhap();
			dsNV[n++]=nv; //Them nv vao mang
			
			ofstream outfile("database/listEmployees.txt",ios::app);
			if(outfile.is_open()){
				nv.ghiFile(outfile);
				outfile.close();
				cout<<"Da luu vao file."<<endl;
			}else{
				cout<<"Khong the mo file!"<<endl;
			}
		}
		//Ham xoa nv
		void xoaNV(string maNV){
			xuatds();
			ifstream infile("database/listEmployees.txt");
			ofstream tempfile("database/t.txt");
			NhanVien nv;
			bool found=false;
			if(infile.is_open() && tempfile.is_open())
			{
				while(true){
					nv.docFile(infile);
					if(infile.eof()) break;
					if(nv.getMaNV()!=maNV){
						nv.ghiFile(tempfile);
					}else{
						found=true;
					}
				}
				infile.close();
				tempfile.close();
				if(found){
					if(remove("database/listEmployees.txt")!=0){
						cout<<"Khong the xoa file cu!\n";
					}else if(rename("database/t.txt","database/listEmployees.txt")!=0){
						cout<<"Khong the doi ten file moi!\n";
					}else{
						cout<<"Da xoa nhan vien co ma: "<<maNV<<endl;
					}
				}else{
					cout<<"Khong tim thay nhan vien co ma: "<<maNV<<endl;
					remove("database/t.txt");
				}
		    }else{
		    	cout<<"Khong the mo file!\n";
			}
		}
		// Ham phan ca lam viec
		void phanCalamviec(){
			xuatds();
			string maNV;
			string caMoi;
			cout<<"Nhap ma nhan vien can cap nhat ca: ";
			cin>>maNV;
			cout<<"Nhap ca lam viec moi: ";
			cin.ignore();
			getline(cin,caMoi);
			ifstream infile("database/listEmployees.txt");
			ofstream tempfile("database/t.txt");
			NhanVien nv;
			bool found=false;
			if(infile.is_open() && tempfile.is_open()){
				while(true){
					nv.docFile(infile);
					if(infile.eof()) break;
					if(nv.getMaNV()==maNV){
						nv.capNhatCa(caMoi);
						found=true;
					}
					nv.ghiFile(tempfile);
				}
				infile.close();
				tempfile.close();
				remove("database/listEmployees.txt");
				rename("database/t.txt","database/listEmployees.txt");
				if(found){
					cout<<"Da cap nhat ca lam viec cho nhan vien co ma: "<<maNV<<endl;
				}else{
					cout<<"Khong tim thay nhan vien co ma: "<<maNV<<endl;
				}
			}else{
				cout<<"Khong the mo file!\n";
			}
		}
		// Ham cap nhat luong
		void capnhatLuong(){
			xuatds();
			string maNV;
			float luongMoi;
			cout<<"Nhap ma nhan vien can cap nhat luong: ";
			cin>>maNV;
			cout<<"Nhap luong moi: ";
			cin>>luongMoi;
			ifstream infile("database/listEmployees.txt");
			ofstream tempfile("database/t.txt");
			NhanVien nv;
			bool found=false;
			if(infile.is_open() && tempfile.is_open()){
				while(true){
					nv.docFile(infile);
					if(infile.eof()) break;
					if(nv.getMaNV()==maNV){
						nv.capNhatLuong(luongMoi);
						found=true;
					}
					nv.ghiFile(tempfile);
				}
				infile.close();
				tempfile.close();
				remove("database/listEmployees.txt");
				rename("database/t.txt","database/listEmployees.txt");
				if(found){
					cout<<"Da cap nhat luong cho nhan vien co ma: "<<maNV<<endl;
				}else{
					cout<<"Khong tim thay nhan vien co ma: "<<maNV<<endl;
				}
			}else{
				cout<<"Khong the mo file!\n";
			}
		}
		//Ham tim kiem nhan vien theo ma
		void timKiemNV(string maNV){
		setColor(7);
		ifstream infile("database/listEmployees.txt");
			NhanVien nv;
			bool found=false;
			if(infile.is_open())
			{
				while(true){
					nv.docFile(infile);
					if(infile.eof()) break;
					if(nv.getMaNV()==maNV)
					{
					cout << "+-------+-------------------+-------------------+-----------------------------+-------------+-------+---------------+-----------+" << endl;
					cout << "| ";
					setColor(11); // Tô màu xanh dương nhạt cho chữ "MaNV"
					cout << "MaNV";
					setColor(7); // Trở lại màu mặc định
					cout << "  |     ";
					setColor(11); // Tô màu cho "TenTK"
					cout << "TenTK";
					setColor(7);
					cout << "         |       ";
					setColor(11); // Tô màu cho "TenNV"
					cout << "TenNV";
					setColor(7);
					cout << "       |            ";
					setColor(11); // Tô màu cho "Chuc vu"
					cout << "Chuc vu";
					setColor(7);
					cout << "          | ";
					setColor(11); // Tô màu cho "Ca lam viec"
					cout << "Ca lam viec";
					setColor(7);
					cout << " | ";
					setColor(11); // Tô màu cho "GioLV"
					cout << "GioLV";
					setColor(7);
					cout << " | ";
					setColor(11); // Tô màu cho "Gio lam them"
					cout << "Gio lam them";
					setColor(7);
					cout << "  |   ";
					setColor(11); // Tô màu cho "Luong"
					cout << "Luong";
					setColor(7);
					cout << "   |" << endl;
					cout << "+-------+-------------------+-------------------+-----------------------------+-------------+-------+---------------+-----------+" << endl;
                        nv.xuat();
                        found=true;
                        break;
					}
				}
				if(!found){
					cout<<"Khong tim thay nhan vien co ma: "<<maNV<<endl;
				}
				cout<<"+-------+-------------------+-------------------+-----------------------------+-------------+-------+---------------+-----------+"<<endl;
				infile.close();
			}else{
				cout<<"Khong the mo file!\n";
			}
		}
		// Ham hien thi dsnv
		void xuatds(){
			ifstream infile("database/listEmployees.txt");
			NhanVien nv;
			if(infile.is_open()){
			cout << "+-------+-------------------+-------------------+-----------------------------+-------------+-------+---------------+-----------+" << endl;
			cout << "| ";
			setColor(11); // Tô màu xanh dương nhạt cho chữ "MaNV"
			cout << "MaNV";
			setColor(7); // Trở lại màu mặc định
			cout << "  |     ";
			setColor(11); // Tô màu cho "TenTK"
			cout << "TenTK";
			setColor(7);
			cout << "         |       ";
			setColor(11); // Tô màu cho "TenNV"
			cout << "TenNV";
			setColor(7);
			cout << "       |            ";
			setColor(11); // Tô màu cho "Chuc vu"
			cout << "Chuc vu";
			setColor(7);
			cout << "          | ";
			setColor(11); // Tô màu cho "Ca lam viec"
			cout << "Ca lam viec";
			setColor(7);
			cout << " | ";
			setColor(11); // Tô màu cho "GioLV"
			cout << "GioLV";
			setColor(7);
			cout << " | ";
			setColor(11); // Tô màu cho "Gio lam them"
			cout << "Gio lam them";
			setColor(7);
			cout << "  |   ";
			setColor(11); // Tô màu cho "Luong"
			cout << "Luong";
			setColor(7);
			cout << "   |" << endl;
			cout << "+-------+-------------------+-------------------+-----------------------------+-------------+-------+---------------+-----------+" << endl;
				while(true){
					nv.docFile(infile);
					if(infile.eof()) break;
					nv.xuat();
				}
				cout<<"+-------+-------------------+-------------------+-----------------------------+-------------+-------+---------------+-----------+"<<endl;
				setColor(7);
				infile.close();
		}else{
			cout<<"Khong the mo file!\n";
		}
    }
};


int menuEmployeeManagement(){
	QLNV qlnv;
	int choice;
	do{
		setColor(11);
		cout<<"           QUAN LY NHAN VIEN       \n";
		setColor(7);
		cout<<"===================================\n";
		cout<<"| 1. Them nhan vien               |\n";
		cout<<"| 2. Xoa nhan vien                |\n";
		cout<<"| 3. Phan ca lam viec             |\n";
		cout<<"| 4. Cap nhat luong               |\n";
		cout<<"| 5. Tim kiem nhan vien           |\n";
		cout<<"| 6. Hien thi danh sach nhan vien |\n";
		cout<<"| 7. Thoat                        |\n";
		cout<<"===================================\n";
		setColor(7);
		setColor(12);
		cout<<"Lua chon: ";
		setColor(7);
		cinInt>>choice;
		switch(choice){
			case 1:
				qlnv.themNV();
				this_thread::sleep_for(chrono::milliseconds(1000));
            	system("cls");
				break;
			case 2:{
				string maNV;
				setColor(12);
				cout<<"Nhap ma nhan vien can xoa: ";
				setColor(7);
				cin>>maNV;
				qlnv.xoaNV(maNV);
				this_thread::sleep_for(chrono::milliseconds(2000));
            	system("cls");
				break;
			}
			case 3:
				qlnv.phanCalamviec();
				this_thread::sleep_for(chrono::milliseconds(1000));
            	system("cls");
				break;
			case 4:
				qlnv.capnhatLuong();
				this_thread::sleep_for(chrono::milliseconds(1000));
            	system("cls");
				break;
			case 5:{
				string maNV;
				setColor(12);
				cout<<"Nhap ma nhan vien can tim: ";
				setColor(7);
				cin>>maNV;
				qlnv.timKiemNV(maNV);
				this_thread::sleep_for(chrono::milliseconds(2000));
            	system("cls");
				break;
			}
			case 6:
				this_thread::sleep_for(chrono::milliseconds(1000));
            	system("cls");
				setColor(14);
				cout<<"====================================================== DANH SACH NHAN VIEN =====================================================\n\n";
				setColor(7);
				qlnv.xuatds();
				break;
			case 7:
			    setColor(12);
				cout<<"Thoat chuong trinh."<<endl;
				setColor(7);
				this_thread::sleep_for(chrono::milliseconds(500));
            	system("cls");
				break;
			default:
			    setColor(12);
				cout<<"Lua chon khong hop le. Vui long chon lai."<<endl;
				setColor(7);
		}
	}while(choice!=7);
	return 0;
}