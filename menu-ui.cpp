#include <stdio.h>
#include <string.h>
#define MAX_SV 100

typedef struct {
    char maSV[15];
    char hoTen[50]; 
    char lop[15];    
    float diemToan;
    float diemLy;
    float diemHoa;
    float diemTB; 
    char xepLoai[15]; 
} SinhVien;

SinhVien dsSV[MAX_SV];
int n = 0;

void xoaBoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void docChuoi(char s[], int kichThuoc) {
    fgets(s, kichThuoc, stdin);
    s[strcspn(s, "\n")] = '\0';
}

SinhVien nhapSinhVien() {
    SinhVien sv;
    printf("Nhap ma sinh vien: ");
    docChuoi(sv.maSV, sizeof(sv.maSV));
    printf("Nhap ho ten: ");
    docChuoi(sv.hoTen, sizeof(sv.hoTen));
    printf("Nhap lop: ");
    docChuoi(sv.lop, sizeof(sv.lop));

    sv.diemToan = sv.diemLy = sv.diemHoa = sv.diemTB = 0;
    strcpy(sv.xepLoai, "");
    return sv;
}

int daTonTai(const char ma[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(dsSV[i].maSV, ma) == 0) return 1;
    }
    return 0;
}

void themSinhVien() {
    if (n >= MAX_SV) {
        printf("Danh sach da day!\n");
        return;
    }
    SinhVien sv = nhapSinhVien();
    
        if (strlen(sv.maSV) == 0) {
        printf("Ma sinh vien khong duoc de trong!\n");
        return;
    }
    
    if (daTonTai(sv.maSV)) {
        printf("Ma sinh vien da ton tai!\n");
        return;
    }
    dsSV[n++] = sv;
    printf("Them thanh cong!\n");
}

void hienThiDanhSach() {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    printf("%-10s%-25s%-10s%-8s%s\n", "Ma SV", "Ho ten", "Lop", "DiemTB", "Xep loai");
    for (int i = 0; i < n; i++) {
        printf("%-10s%-25s%-10s%-8.2f%s\n",
               dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop,
               dsSV[i].diemTB, dsSV[i].xepLoai);
    }
}

void hienThiMenu() {
    printf("\n===== QUAN LY SINH VIEN =====\n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Tim kiem sinh vien\n");
    printf("4. Sua thong tin sinh vien\n");
    printf("5. Xoa sinh vien\n");
    printf("6. Nhap/cap nhat diem\n");
    printf("7. Tinh diem TB, xep loai\n");
    printf("8. Sap xep theo diem\n");
    printf("0. Thoat\n");
    printf("Chon chuc nang: ");
}

// ----- Phan 2 huu minh (khai bao prototype) -----
void timKiemSinhVien() {
	char ma[15];
	char ten[20];
	int LuaChon = 0;
	do {
		printf("\n=====TIM KIEM SINH VIEN=====\n");
		printf("\nChon cach tim kiem sinh vien\n");
		printf("1. Tim kiem theo ma so sinh vien\n");
		printf("2. Tim kiem theo ho ten\n");
		printf("0. Thoat\n");
		printf("Nhap lua chon: ");
		scanf("%d", &LuaChon);
		xoaBoDem();
		switch (LuaChon) {
			case 1:	{
				int dem = 0;             
				printf("Nhap MSSV: ");
				docChuoi(ma, sizeof(ma));
				for (int i = 0; i < n; i++) {
					if (strcmp(dsSV[i].maSV, ma) == 0) {
						if (dem == 0) {
						printf("%-10s%-25s%-10s%-8s%s\n", "Ma SV", "Ho ten", "Lop", "DiemTB", "Xep loai");
						printf("%-10s%-25s%-10s%-8s%s\n", dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop, dsSV[i].diemTB, dsSV[i].xepLoai);
						dem++;
					}
				}
			}
			if (dem == 0) {
				printf("\nKhong tim thay sinh vien\n");
			}
				break;
		}
			case 2: {
				int dem = 0;
				printf("Nhap ho ten: ");
				docChuoi(ten, sizeof(ten));
				for (int i = 0; i < n; i++) {
					if (strcmp(dsSV[i].hoTen, ten) == 0) {
						if (dem == 0) {
						printf("%-10s%-25s%-10s%-8s%s\n", "Ma SV", "Ho ten", "Lop", "DiemTB", "Xep loai");
						printf("%-10s%-25s%-10s%-8s%s\n", dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop, dsSV[i].diemTB, dsSV[i].xepLoai);
						dem++;
					}
				}
			}
				if (dem == 0) {
					printf("\nKhong tim thay sinh vien\n");
				}
				break;
		}
			case 0:
				printf("\nDa thoat chuc nang\n");
				break;
				return;
		}
	}	while (LuaChon != 0);     
	return;
}
void suaSinhVien()     {
	char ma[15];
	printf("Nhap MSSV:");
	docChuoi (ma, sizeof(ma));
	for (int i = 0; i < n; i++) {
		if (strcmp(dsSV[i].maSV, ma) == 0) {
			int LuaChon = 0;
			do {
				printf("\n=====CHON PHAN SUA=====\n");
				printf("1. Ho ten\n");
				printf("2. Lop\n");
				printf("3. Ca hai\n");
				printf("0. Thoat\n");
				printf("Chon: ");
				scanf("%d", &LuaChon);
				xoaBoDem();
				switch (LuaChon) {
					case 1:
						printf("\nHo ten cu: %s", dsSV[i].hoTen);
						printf("\nNhap ho ten moi: ");
						docChuoi(dsSV[i].hoTen, sizeof(dsSV[i].hoTen));
						printf("\nDa sua ho ten thanh cong!");
						break;
					case 2:
						printf("\nLop cu: %s", dsSV[i].lop);
						printf("\nNhap lop moi: ");
						docChuoi(dsSV[i].lop, sizeof(dsSV[i].lop));
						printf("\nDa sua lop thanh cong!");
						break;
					case 3:	
						printf("\nHo ten cu: %s", dsSV[i].hoTen);
						printf("\nLop cu: %s", dsSV[i].lop);
						printf("\nNhap ho ten moi: ");
						docChuoi(dsSV[i].hoTen, sizeof(dsSV[i].hoTen));
						printf("\nNhap lop moi: ");
						docChuoi(dsSV[i].lop, sizeof(dsSV[i].lop));
						printf("\nDa sua ho ten va lop thanh cong!");
						break;
					case 0:
						printf("\nDa thoat chuc nang");
						break;	
					}
				} while (LuaChon != 0);
				return;
			}
		printf("\nKhong tim thay sinh vien");	
		}
}
void xoaSinhVien() {
	char ma[15];
	printf("Nhap MSSV:");
	docChuoi (ma, sizeof(ma));
	for (int i = 0; i < n; i++) {
		if (strcmp(dsSV[i].maSV, ma) == 0) {
			for (int j = 0; j < n - 1; j++) {
		 		dsSV[j] = dsSV[j + 1];
			}
		n--;
		printf("Xoa thanh cong");
		return;	 
		}
	}
	printf("\nKhong tim thay sinh vien");
}
// ----- Phan 3 thien ky -----
void nhapDiem()        { printf("(Chua co chuc nang nhap diem)\n"); }
void thongKeDiem()     { printf("(Chua co chuc nang thong ke)\n"); }
void sapXepTheoDiem()  { printf("(Chua co chuc nang sap xep)\n"); }

int main() {
    int chon = 0;
    do {
        hienThiMenu();
        if (scanf("%d", &chon) != 1) chon = -1;
        xoaBoDem();

        switch (chon) {
            case 1: 
				themSinhVien();    
				break;
            case 2: 
				hienThiDanhSach(); 
				break;
            case 3: 
				timKiemSinhVien(); 
				break;
            case 4: 
				suaSinhVien();     
				break;
            case 5: 
				xoaSinhVien();     
				break;
            case 6: 
				nhapDiem();        
				break;
            case 7: 
				thongKeDiem();     
				break;
            case 8: 
				sapXepTheoDiem();  
				break;
            case 0: 
				printf("Tam biet!\n"); 
				break;
            default: 
				printf("Lua chon khong hop le!\n");
        }
    } while (chon != 0);

    return 0;
}