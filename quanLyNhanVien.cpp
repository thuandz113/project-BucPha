#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
const int maxNV=100;
class NhanVien{
	private:
		string maNhanVien;
		string tenNhanVien;
		string chucVu;
		string caLamViec;
		int soGioLamViec;
		int soGioLamThem;
		float luongTheoGio;
	public:
		NhanVien(string maNV="",string tenNV="",string cv="",string caLV="",float luongGio=0,int gioLV=0,int gioLamThem=0):maNhanVien(maNV),tenNhanVien(tenNV),chucVu(cv),caLamViec(caLV),luongTheoGio(luongGio),soGioLamViec(gioLV),soGioLamThem(gioLamThem){}
		//Ham nhap thong tin nhan vi�n
		void nhap(){
			cout<<"Nhap ma nhan vien: ";
			cin>>maNhanVien;
			cout<<"Nhap ten nhan vien: ";
			cin.ignore();
			getline(cin,tenNhanVien);
			cout<<"Nhap chuc vu: ";
			getline(cin,chucVu);
			cout<<"Nhap ca lam viec: ";
			getline(cin,caLamViec);
			cout<<"Nhap so gio lam viec: ";
			cin>>soGioLamViec;
			cout<<"Nhap so gio lam them (neu co): ";
			cin>>soGioLamThem;
			luongTheoGio=getLuongByChucVu(chucVu);
		}
		//Ham lay luong co ban theo chuc vu
		float getLuongByChucVu(string chucVu){
			if(chucVu=="Quan ly cua hang") return 60000;
			else if(chucVu=="Quan ly kho") return 55000;
			else if(chucVu=="Nhan vien ban hang") return 33000;
			else if(chucVu=="Nhan vien thu ngan") return 35000;
			else if(chucVu=="Nhan vien ve sinh") return 28000;
			else if(chucVu=="Nhan vien tiep thi") return 45000;
			else if(chucVu=="Nhan vien ho tro khach hang") return 38000;
			else return 15000;
		}
		//Ham tinh luong
		float tinhLuongThang(){
			float hesoLamThem=1.5;
			return (soGioLamViec*luongTheoGio)+(soGioLamThem*luongTheoGio*hesoLamThem);
		}
		//Ham hien thi thong tin nhan vien
		void xuat(){
		cout<<"| "<<left<<setw(5)<<maNhanVien<<" | "
                 <<left<<setw(13)<<tenNhanVien<<" | "
                 <<left<<setw(27)<<chucVu<<" | "
                 <<left<<setw(11)<<caLamViec<<" | "
                 <<left<<setw(5)<<soGioLamViec<<" | "
                 <<left<<setw(13)<<soGioLamThem<<" | "
                 <<left<<setw(9)<<fixed<<setprecision(0)<<tinhLuongThang()<<" |"<<endl;
		}
		string getMaNV(){
			return maNhanVien;
		}
		//Ghi nhan vien vao file
		void ghiFile(ofstream &outfile){
			outfile<<maNhanVien<<endl;
			outfile<<tenNhanVien<<endl;
			outfile<<chucVu<<endl;
			outfile<<caLamViec<<endl;
			outfile<<soGioLamViec<<endl;
			outfile<<soGioLamThem<<endl;
			outfile<<luongTheoGio<<endl;
		}
		//Doc nhan vien tu file
		void docFile(ifstream &infile){
			getline(infile,maNhanVien);
			getline(infile,tenNhanVien);
			getline(infile,chucVu);
			getline(infile,caLamViec);
			infile>>soGioLamViec;
			infile>>soGioLamThem;
			infile>>luongTheoGio;
			infile.ignore();
		}
		//Cap nhat ca lam viec
		//s�ng(8:00 - 12:00), chieu(13:00-17:00),toi(18:00-22:00)
		void capNhatCa(string caMoi){
			caLamViec=caMoi;
		}
		//Cap nhat luong
		void capNhatLuong(float luongMoi){
			luongTheoGio=luongMoi;
		}	
};
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
			
			ofstream outfile("nv.txt",ios::app);
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
			ifstream infile("nv.txt");
			ofstream tempfile("t.txt");
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
					if(remove("nv.txt")!=0){
						cout<<"Khong the xoa file cu!\n";
					}else if(rename("t.txt","nv.txt")!=0){
						cout<<"Khong the doi ten file moi!\n";
					}else{
						cout<<"Da xoa nhan vien co ma: "<<maNV<<endl;
					}
				}else{
					cout<<"Khong tim thay nhan vien co ma: "<<maNV<<endl;
					remove("t.txt");
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
			ifstream infile("nv.txt");
			ofstream tempfile("t.txt");
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
				remove("nv.txt");
				rename("t.txt","nv.txt");
				if(found){
					cout<<"Da cap nhat ca lam viec cho nhan vien co ma: "<<maNV<<endl;
				}else{
					cout<<"Khong tim thay nhan vien co ma: "<<maNV<<endl;
				}
			}else{
				cout<<"Khong the mo file!\n";
			}
		}
		//Ham cap nhat luong
		void capnhatLuong(){
			string maNV;
			float luongMoi;
			cout<<"Nhap ma nhan vien can cap nhat luong: ";
			cin>>maNV;
			cout<<"Nhap luong moi: ";
			cin>>luongMoi;
			ifstream infile("nv.txt");
			ofstream tempfile("t.txt");
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
				remove("nv.txt");
				rename("t.txt","nhanvien.txt");
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
			ifstream infile("nv.txt");
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
		//Ham hien thi dsnv
		void xuatds(){
			ifstream infile("nv.txt");
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
int main(){
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
