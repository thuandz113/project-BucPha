#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

class SanPham {
private:
    char maSanPham[20];
    char tenSanPham[30];
    int soLuong;
    double gia;
    char moTaSanPham[50];
    char ngayNhap[20];

public:
    // Hàm kh?i t?o
    SanPham() {}

    // Phuong th?c thêm s?n ph?m
    void themSanPham() {
        cout << "Nhap thong tin san pham moi: " << endl;
        cout << "Ma san pham: "; cin >> maSanPham;
        cout << "Ten san pham: "; cin >> tenSanPham;
        cout << "So luong: "; cin >> soLuong;
        cout << "Gia: "; cin >> gia;
        cout << "Mo ta san pham: "; cin >> moTaSanPham;
        cout << "Ngay nhap: "; cin >> ngayNhap;

        // Luu thông tin vào file
        FILE *file = fopen("sanpham.txt", "a");
        if (file != NULL) {
            fprintf(file, "%s %s %d %.2f %s %s\n", maSanPham, tenSanPham, soLuong, gia, moTaSanPham, ngayNhap);
            fclose(file);
            cout << "Da them san pham thanh cong!" << endl;
        } else {
            cout << "Loi mo file!" << endl;
        }
    }

    // Phuong th?c xóa s?n ph?m
    void xoaSanPham(const char* ma) {
        FILE *fileIn = fopen("sanpham.txt", "r");
        FILE *fileOut = fopen("sanpham_temp.txt", "w");
        if (fileIn == NULL || fileOut == NULL) {
            printf("Khong the mo file!\n");
            return;
        }

        char line[256];
        bool found = false;

        while (fgets(line, sizeof(line), fileIn)) {
            if (strstr(line, ma) == NULL) {
                fputs(line, fileOut);
            } else {
                found = true;
            }
        }

        fclose(fileIn);
        fclose(fileOut);
        remove("sanpham.txt");
        rename("sanpham_temp.txt", "sanpham.txt");

        if (found) {
            cout << "Xoa san pham thanh cong!" << endl;
        } else {
            cout << "Khong tim thay san pham!" << endl;
        }
    }

    // Phuong th?c c?p nh?t kho
    void capNhatKho(const char* ma) {
        FILE *fileIn = fopen("sanpham.txt", "r");
        FILE *fileOut = fopen("sanpham_temp.txt", "w");
        if (fileIn == NULL || fileOut == NULL) {
            printf("Khong the mo file!\n");
            return;
        }

        char line[256];
        bool found = false;

        while (fgets(line, sizeof(line), fileIn)) {
            char maSanPham[20], tenSanPham[30], moTaSanPham[50], ngayNhap[20];
            int soLuong;
            double gia;

            sscanf(line, "%s %s %d %lf %s %s", maSanPham, tenSanPham, &soLuong, &gia, moTaSanPham, ngayNhap);

            if (strcmp(maSanPham, ma) == 0) {
                found = true;
                int soLuongMoi;
                printf("Nhap so luong moi: ");
                scanf("%d", &soLuongMoi);

                fprintf(fileOut, "%s %s %d %.2lf %s %s\n", maSanPham, tenSanPham, soLuongMoi, gia, moTaSanPham, ngayNhap);
            } else {
                fputs(line, fileOut);
            }
        }

        fclose(fileIn);
        fclose(fileOut);
        remove("sanpham.txt");
        rename("sanpham_temp.txt", "sanpham.txt");

        if (found) {
            printf("Cap nhat thanh cong!\n");
        } else {
            printf("Khong tim thay san pham!\n");
        }
    }

    void timSanPhamTheoMa(const char* ma) {
        FILE *file = fopen("sanpham.txt", "r");
        if (file == NULL) {
            printf("Khong the mo file!\n");
            return;
        }

        char line[256];
        bool found = false;

        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, ma) != NULL) {
                printf("%s", line);
                found = true;
                break;
            }
        }

        if (!found) {
            printf("Khong tim thay san pham!\n");
        }

        fclose(file);
    }

    void timSanPhamTheoTen(const char* ten) {
        FILE *file = fopen("sanpham.txt", "r");
        if (file == NULL) {
            printf("Khong the mo file!\n");
            return;
        }

        char line[256];
        bool found = false;

        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, ten) != NULL) {
                printf("%s", line);
                found = true;
            }
        }

        if (!found) {
            printf("Khong tim thay san pham!\n");
        }

        fclose(file);
    }

    void xemTonKho() {
        FILE *file = fopen("sanpham.txt", "r");
        if (file == NULL) {
            printf("Khong the mo file!\n");
            return;
        }

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }

        fclose(file);
    }
};
int main()
{
	
}
