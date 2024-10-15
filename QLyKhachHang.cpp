#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;
const int maxKhachHang=100;

class KhachHang{
	protected:
		string tenKhachHang;
		string diaChi;
		string soDienThoai;
		string email;
		string matKhau;
	public:
		//Ham tao tk
		void taoTaiKhoan(){
			cout<<"Nhap ten khach hang: ";
			cin.ignore();
			getline(cin,tenKhachHang);
			cout<<"Nhap dia chi: ";
			getline(cin,diaChi);
			cout<<"Nhap so dien thoai: ";
			getline(cin,soDienThoai);
			cout<<"Nhap email: ";
			getline(cin,email);
			cout<<"Nhap mat khau: ";
			getline(cin,matKhau);
		//Luu thong tin vao file
		ofstream outfile("khachhang.txt",ios::app);
		outfile<<tenKhachHang<<endl
		       <<diaChi<<endl
		       <<soDienThoai<<endl
		       <<email<<endl
		       <<matKhau<<endl;
		outfile.close();
		cout<<"\n********** TAI KHOAN DA DUOC TAO THANH CONG **********\n";
		}
		//Ham dang nhap
		bool dangNhap(){
			string tenDangNhap, matKhauNhap;
			cout<<"Nhap ten dang nhap: ";
			cin.ignore();
			getline(cin,tenDangNhap);
			cout<<"Nhap mat khau: ";
			getline(cin,matKhauNhap);
			//Kiem tra thong tin
			ifstream infile("khachhang.txt");
			string line;
			bool found=false;
			while(getline(infile,line)){
				if(line==tenDangNhap){
					found=true;
					getline(infile,line);
					getline(infile,line);
					getline(infile,line);
					getline(infile,line);
					if(line==matKhauNhap){
						cout<<"************ Dang nhap thanh cong! ************"<<endl;
						infile.close();
						return true;
					}else{
						cout<<"Mat khau khong dung!"<<endl;
						infile.close();
						return false;
					}
				}
				for(int i=0;i<4;i++) getline(infile,line);
			}
			cout<<"Khong tim thay khach hang!"<<endl;
			infile.close();
			return false;
		}
		//Ham xem thong tin ca nhan
		void xemThongTinCaNhan(){
			cout<<"\n=========== THONG TIN CA NHAN ===========\n";
			cout<<left<<setw(20)<<"Ten khach hang: "<<tenKhachHang<<endl;
			cout<<left<<setw(20)<<"Dia chi: "<<diaChi<<endl;
			cout<<left<<setw(20)<<"So dien thoai: "<<soDienThoai<<endl;
			cout<<left<<setw(20)<<"Email: "<<email<<endl;
			cout<<"=========================================\n";
		}
		//Ham cap nhat thong tin ca nhan
		void capNhatThongTinCaNhan(){
			cout<<"Nhap thong tin can cap nhat:"<<endl;
			cout<<"Nhap dia chi moi: ";
			cin.ignore();
			getline(cin,diaChi);
			cout<<"Nhap so dien thoai moi: ";
			getline(cin,soDienThoai);
			cout<<"Nhap email moi: ";
			getline(cin,email);
			
			fstream infile("khachhang.txt");
			ofstream tempfile("temp.txt");
			string line;
			bool found=false;
			while(getline(infile,line)){
				if(line==tenKhachHang){
					found=true;
					tempfile<<tenKhachHang<<endl
			               <<diaChi<<endl
			               <<soDienThoai<<endl
			               <<email<<endl
			               <<matKhau<<endl;
			        for(int i=0;i<4;i++) getline(infile,line);
				}else{
					tempfile<<line<<endl;
				} 
			}
			infile.close();
			tempfile.close();
			remove("khachhang.txt");
			rename("temp.txt","khachhang.txt");
			cout<<"CAP NHAT THONG TIN THANH CONG!"<<endl;
		}
};
class KhachHangThanThiet:public KhachHang{
	private:
		int diemTichLuy;
		string uuDai;
		string lichSuMuaHang;
		string maKhachHang;
	public:
		//Ham tich luy diem
		void tichLuyDiem(int diem){
			diemTichLuy+=diem;
			cout<<"\n==> Da cap nhat diem tich luy. Diem hien tai: "<<diemTichLuy<<"diem.\n";
		}
		//Ham cap nhat diem tich luy
		void capNhatDiemTichLuy(int soTienGiaoDich){
			int diem=soTienGiaoDich/100;
			tichLuyDiem(diem);
			cout<<"Ban da nhan "<<diem<<" diem sau giao dich "<<soTienGiaoDich;
			cout<<"Tong diem tich luy hien tai: "<<diemTichLuy<<"diem.\n";
		}
		//Ham xem diem tich luy
		void xemDiem(){
			cout<<"\n********** THONG TIN DIEM TICH LUY **********\n";
			cout<<left<<setw(20)<<"Ten Khach hang"<<tenKhachHang<<endl;
			cout<<left<<setw(20)<<"Diem tich luy: "<<diemTichLuy<<"diem"<<endl;
			cout<<"*********************************************\n";
		}
		//Ham luu lich su mua hang
		void luuLichSuMuaHang(string lichSu){
			lichSuMuaHang+=lichSu+"\n";
			cout<<"LICH SU MUA HANG DA DUOC LUU!"<<endl;
		}
		//Ham xem uu dai thanh vien
		void xemUuDai(){
			cout<<"\n========== UU DAI THANH VIEN ===========\n";
			cout<<left<<setw(20)<<"Ten khach hang: "<<tenKhachHang<<endl;
			cout<<left<<setw(20)<<"Uu dai: "<<uuDai<<endl;
			cout<<"========================================\n";
		}
		//Ham doi diem thuong
		void doiDiemThuong(int diem){
			if(diem<=diemTichLuy){
				diemTichLuy-=diem;
				cout<<"DA DOI"<<diem<<" DIEM THANH CONG!"<<endl;
			}else{
				cout<<"KHONG DU DIEM DE DOI!"<<endl;
			}
		}
};
int main(){
	KhachHang kh;
	KhachHangThanThiet khtt;
	int choice;
	do{
		cout<<"\n--- QUAN LY KHACH HANG ---\n";
        cout<<"1. Tao tai khoan\n";
        cout<<"2. Dang nhap\n";
        cout<<"3. Xem thong tin ca nhan\n";
        cout<<"4. Cap nhat thong tin ca nhan\n";
        cout<<"5. Tich luy diem\n";
        cout<<"6. Xem diem\n";
        cout<<"7. Luu lich su mua hang\n";
        cout<<"8. Xem uu dai\n";
        cout<<"9. Doi diem thuong\n";
        cout<<"10. Cap nhat diem sau giao dich\n";
        cout<<"11. Thoat\n";
        cout<<"Lua chon: ";
        cin>>choice;
        switch(choice){
        	case 1:
        		kh.taoTaiKhoan();
        		break;
        	case 2:
        		kh.dangNhap();
        		break;
        	case 3:
        		kh.xemThongTinCaNhan();
        		break;
        	case 4:
        		kh.capNhatThongTinCaNhan();
        		break;
        	case 5:{
        		int diem;
        		cout<<"Nhap diem tich luy: ";
        		cin>>diem;
        		khtt.tichLuyDiem(diem);
				break;
			case 6:
				khtt.xemDiem();
				break;
			case 7:{
				string lichSu;
				cout<<"Nhap lich su mua hang: ";
				cin.ignore();
				getline(cin,lichSu);
				khtt.luuLichSuMuaHang(lichSu);
				break;
		    }
			case 8:
				khtt.xemUuDai();
				break;
			case 9:{
				int diem;
				cout<<"Nhap so diem muon doi: ";
				cin>>diem;
				khtt.doiDiemThuong(diem);
				break;
			}
			case 10:{
				int soTien;
				cout<<"Nhap so tien giao dich (VND): ";
				cin>>soTien;
				khtt.capNhatDiemTichLuy(soTien);
				break;
			}
			case 11:
				cout<<"Thoat chuong trinh."<<endl;
				break;
			default:
				cout<<"LUA CHON KHONG HOP LE. VUI LONG CHON LAI."<<endl;
			}
		}
	}while(choice!=11);
	return 0;
}
