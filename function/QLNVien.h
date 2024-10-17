#pragma once

#include <iostream>
#include "doiTuong.h"
#include "dangNhap.h"
using namespace std;

const int maxNV = 100;
bool checkPasss(const string &password) {
    return password.size() >= 8;
}
void registerEmployeeAccout(){
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
        cout << "Nhap mat khau moi (it nhat 8 ky tu): ";
        inputPass(password);

        if (checkPasss(password)) 
        {
            int sex;
            string number, address;
            cout<<"Vui long chon gioi tinh: 1-Nam, 2-Nu."<<endl;
            do{
                cout<<"Lua chon cua ban:";
                cin>>sex;
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
        static int demMaNV;  // Biến static để đếm mã nhân viên
        string maNhanVien;
        string tenNhanVien;
        string chucVu;
        string caLamViec;
        int soGioLamViec;
        int soGioLamThem;
        float luongTheoGio;

    public:
        NhanVien(string maNV = "", string tenNV = "", string cv = "", string caLV = "", float luongGio = 0, int gioLV = 0, int gioLamThem = 0)
        : maNhanVien(maNV), tenNhanVien(tenNV), chucVu(cv), caLamViec(caLV), luongTheoGio(luongGio), soGioLamViec(gioLV), soGioLamThem(gioLamThem) {}

        // Ham nhap thong tin nhan vien
        void nhap() {
            maNhanVien = "NV" + to_string(demMaNV++);  // Tự động gán mã nhân viên
            cout << "Ma nhan vien tu dong: " << maNhanVien << endl;
            cout << "Nhap ten nhan vien: ";
            cin.ignore();
            getline(cin, tenNhanVien);
            cout << "Nhap chuc vu: ";
            getline(cin, chucVu);
            cout << "Nhap ca lam viec: ";
            getline(cin, caLamViec);
            cout << "Nhap so gio lam viec: ";
            cin >> soGioLamViec;
            cout << "Nhap so gio lam them (neu co): ";
            cin >> soGioLamThem;
            luongTheoGio = getLuongByChucVu(chucVu);
			cin.ignore();
        	char choice;
        	cout<<"ban co muon tao tai khoan cho nhan vien nay(y/n): ";
			cin>>choice;
        	if(choice=='y'||choice=='Y'){
        		registerEmployeeAccout();
			}
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
            cout << "| " << left << setw(5) << maNhanVien << " | "
                 << left << setw(13) << tenNhanVien << " | "
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
int NhanVien::demMaNV = 1;
class QLNV:public NhanVien{
	private:
		NhanVien dsNV[maxNV];
int n; //sl nhan vien
	public:
		QLNV():n(0){}
		//Ham them nv
		void themNV(){
			if(n>=maxNV){
				cout<<"Da du so luong nhan vien!"<<endl;
				return;
			}
			NhanVien nv;
			nv.nhap();
			dsNV[n++]=nv; //Them nv vao mang
			
			ofstream outfile("database/nv.txt",ios::app);
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
			ifstream infile("database/nv.txt");
			ofstream tempfile("database/t.txt");
			NhanVien nv;
			bool found=false;
			if(infile.is_open() && tempfile.is_open()){
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
					if(remove("database/nv.txt")!=0){
						cout<<"Khong the xoa file cu!\n";
					}else if(rename("database/t.txt","database/nv.txt")!=0){
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
			string maNV;
			string caMoi;
			cout<<"Nhap ma nhan vien can cap nhat ca: ";
			cin>>maNV;
			cout<<"Nhap ca lam viec moi: ";
			cin.ignore();
			getline(cin,caMoi);
			ifstream infile("database/nv.txt");
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
				remove("database/nv.txt");
				rename("database/t.txt","database/nv.txt");
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
			string maNV;
			float luongMoi;
			cout<<"Nhap ma nhan vien can cap nhat luong: ";
			cin>>maNV;
			cout<<"Nhap luong moi: ";
			cin>>luongMoi;
			ifstream infile("database/nv.txt");
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
				remove("database/nv.txt");
				rename("database/t.txt","database/nhanvien.txt");
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
	ifstream infile("database/nv.txt");
			NhanVien nv;
			bool found=false;
			if(infile.is_open()){
				while(true){
					nv.docFile(infile);
					if(infile.eof()) break;
					if(nv.getMaNV()==maNV){
						cout << "+-------+---------------+-----------------------------+-------------+-------+---------------+-----------+" << endl;
                        cout << "| MaNV  |     TenNV     |            Chuc vu          | Ca lam viec | GioLV | Gio lam them  |   Luong   |" << endl;
                        cout << "+-------+---------------+-----------------------------+-------------+-------+---------------+-----------+" << endl;
                        nv.xuat();
                        found=true;
                        break;
					}
				}
				if(!found){
					cout<<"Khon tim thay nhan vien co ma: "<<maNV<<endl;
				}
				cout<<"+-------+---------------+-----------------------------+-------------+-------+---------------+-----------+"<<endl;
				infile.close();
			}else{
				cout<<"Khong the mo file!\n";
			}
		}
		// Ham hien thi dsnv
		void xuatds(){
			ifstream infile("database/nv.txt");
			NhanVien nv;
			if(infile.is_open()){
				cout << "+-------+---------------+-----------------------------+-------------+-------+---------------+-----------+" << endl;
                cout << "| MaNV  |     TenNV     |            Chuc vu          | Ca lam viec | GioLV | Gio lam them  |   Luong   |" << endl;
                cout << "+-------+---------------+-----------------------------+-------------+-------+---------------+-----------+" << endl;
				while(true){
					nv.docFile(infile);
					if(infile.eof()) break;
					nv.xuat();
				}
				cout<<"+-------+---------------+-----------------------------+-------------+-------+---------------+-----------+"<<endl;
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
		cout<<"\n--- QUAN LY NHAN VIEN ---\n";
		cout<<"1. Them nhan vien\n";
		cout<<"2. Xoa nhan vien\n";
		cout<<"3. Phan ca lam viec\n";
		cout<<"4. Cap nhat luong\n";
		cout<<"5. Tim kiem nhan vien\n";
		cout<<"6. Hien thi danh sach nhan vien\n";
		cout<<"7. Thoat\n";
		cout<<"Lua chon: ";
		cin>>choice;
		switch(choice){
			case 1:
				qlnv.themNV();
				break;
			case 2:{
				string maNV;
				cout<<"Nhap ma nhan vien can xoa: ";
				cin>>maNV;
				qlnv.xoaNV(maNV);
				break;
			}
			case 3:
				qlnv.phanCalamviec();
				break;
			case 4:
				qlnv.capnhatLuong();
				break;
			case 5:{
				string maNV;
				cout<<"Nhap ma nhan vien can tim: ";
				cin>>maNV;
				qlnv.timKiemNV(maNV);
				break;
			}
			case 6:
				cout<<"-------------------------------- DANH SACH NHAN VIEN ----------------------------------\n\n";
				qlnv.xuatds();
				break;
			case 7:
				cout<<"Thoat chuong trinh."<<endl;
				break;
			default:
				cout<<"Lua chon khong hop le. Vui long chon lai."<<endl;
		}
	}while(choice!=7);
	return 0;
}