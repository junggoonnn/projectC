#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SV 100
#define MAX_MON 10
#define MAX_TEN_MON 30
#define FILE_NAME "sinhvien.txt"

// ===== KHAI BÁO CẤU TRÚC DỮ LIỆU =====
typedef struct {
    char maSV[15];
    char hoTen[50];
    char lop[15];

    int soMon;
    char tenMon[MAX_MON][MAX_TEN_MON];
    float diem[MAX_MON];

    float gpa;
    char xepLoai[15];
} SinhVien;

SinhVien dsSV[MAX_SV];
int n = 0;

// ===== HÀM BỔ TRỢ HỆ THỐNG =====
void xoaBoDem(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void docChuoi(char s[], int kichThuoc) {
    if (fgets(s, kichThuoc, stdin) != NULL) {
        s[strcspn(s, "\r\n")] = '\0';
    }
}

int daTonTai(const char ma[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(dsSV[i].maSV, ma) == 0) return 1;
    }
    return 0;
}

static int timViTriSinhVienTheoMa(const char ma[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(dsSV[i].maSV, ma) == 0) return i;
    }
    return -1;
}

static int sinhVienDaNhapDiem(const SinhVien *sv) {
    return sv->soMon > 0;
}


int nhapMaSV(char *maSV, int kieuKiemTraTonTai) {
    char dong[256];
    while (1) {
        printf("Nhap ma sinh vien (nhap 0 de thoat): ");
        if (fgets(dong, sizeof(dong), stdin) == NULL) continue;
        if (strchr(dong, '\n') == NULL && !feof(stdin)) xoaBoDem();
        dong[strcspn(dong, "\r\n")] = '\0';

        if (strcmp(dong, "0") == 0) return 0; 

        if (strlen(dong) == 0) {
            printf("Ma sinh vien khong hop le.\n");
            continue;
        }

        if (strlen(dong) > 8) {
            printf("Vui long khong nhap qua so ky tu quy dinh\n");
            continue;
        }

        int hopLe = 1;
        for (int i = 0; dong[i] != '\0'; i++) {
            if (!isalnum((unsigned char)dong[i])) {
                hopLe = 0;
                break;
            }
        }

        if (!hopLe) {
            printf("Ma sinh vien khong hop le.\n");
            continue;
        }

        if (kieuKiemTraTonTai && daTonTai(dong)) {
            printf("Loi: Ma sinh vien [%s] da ton tai! Vui long nhap ma khac.\n", dong);
            continue;
        }

        strcpy(maSV, dong);
        return 1;
    }
}

int nhapHoTen(char *hoTen) {
    char dong[256];
    while (1) {
        printf("Nhap ho ten (nhap 0 de thoat): ");
        if (fgets(dong, sizeof(dong), stdin) == NULL) continue;
        if (strchr(dong, '\n') == NULL && !feof(stdin)) xoaBoDem();
        dong[strcspn(dong, "\r\n")] = '\0';

        if (strcmp(dong, "0") == 0) return 0; 

        int len = strlen(dong);
        if (len == 0 || dong[0] == ' ' || dong[len - 1] == ' ') {
            printf("Ho ten khong hop le\n");
            continue;
        }

        int hopLe = 1;
        for (int i = 0; i < len; i++) {
            unsigned char c = (unsigned char)dong[i];
            if (isdigit(c) || ispunct(c)) {
                hopLe = 0;
                break;
            }
            if (c == ' ' && dong[i + 1] == ' ') {
                hopLe = 0;
                break;
            }
            if (c < 128 && !isalpha(c) && c != ' ') {
                hopLe = 0;
                break;
            }
        }

        if (!hopLe) {
            printf("Ho ten khong hop le\n");
            continue;
        }

        strcpy(hoTen, dong);
        return 1;
    }
}

int nhapLop(char *lop) {
    char dong[256];
    while (1) {
        printf("Nhap lop (nhap 0 de thoat): ");
        if (fgets(dong, sizeof(dong), stdin) == NULL) continue;
        if (strchr(dong, '\n') == NULL && !feof(stdin)) xoaBoDem();
        dong[strcspn(dong, "\r\n")] = '\0';

        if (strcmp(dong, "0") == 0) return 0; 

        int len = strlen(dong);
        if (len == 0 || len > 10) {
            printf("Khong tim thay lop do khong hop le\n");
            continue;
        }

        int hopLe = 1;
        for (int i = 0; i < len; i++) {
            if (!isalnum((unsigned char)dong[i])) {
                hopLe = 0;
                break;
            }
        }

        if (!hopLe) {
            printf("Khong tim thay lop do khong hop le\n");
            continue;
        }

        strcpy(lop, dong);
        return 1;
    }
}


int nhapTenMonHoc(char *tenMon) {
    char dong[256];
    while (1) {
        printf("Nhap ten mon hoc (nhap 0 de thoat): ");
        if (fgets(dong, sizeof(dong), stdin) == NULL) continue;
        if (strchr(dong, '\n') == NULL && !feof(stdin)) xoaBoDem();
        dong[strcspn(dong, "\r\n")] = '\0';

        if (strcmp(dong, "0") == 0) return 0; 

        if (strlen(dong) == 0) {
            printf("Ten mon hoc khong duoc de trong\n");
            continue;
        }

        int hopLe = 1;
        for (int i = 0; dong[i] != '\0'; i++) {
            if (!isalnum((unsigned char)dong[i])) {
                hopLe = 0;
                break;
            }
        }

        if (!hopLe) {
            printf("Ten mon hoc khong hop le\n");
            continue;
        }

        strcpy(tenMon, dong);
        return 1;
    }
}

static int docDiemHopLe(const char tenMon[], float *diemOut) {
    char dong[128];
    while (1) {
        printf("Nhap diem mon %s (0-10, nhap -1 de thoat): ", tenMon);
        if (fgets(dong, sizeof(dong), stdin) == NULL) continue;
        if (strchr(dong, '\n') == NULL && !feof(stdin)) xoaBoDem();
        dong[strcspn(dong, "\r\n")] = '\0';

        if (strcmp(dong, "-1") == 0) return 0; 
        if (strlen(dong) == 0) {
            printf("Diem khong duoc de trong\n");
            continue;
        }

        int coKhoangTrang = 0;
        int hopLe = 1;
        int dotCount = 0;

        for (int i = 0; dong[i] != '\0'; i++) {
            if (isspace((unsigned char)dong[i])) {
                coKhoangTrang = 1;
                hopLe = 0;
                break;
            }
            if (dong[i] == '.') {
                dotCount++;
                if (dotCount > 1) {
                    hopLe = 0;
                    break;
                }
            } else if (!isdigit((unsigned char)dong[i])) {
                hopLe = 0;
                break;
            }
        }

        if (coKhoangTrang || !hopLe) {
            printf("Diem khong hop le\n");
            continue;
        }

        char *cuoi;
        float val = strtof(dong, &cuoi);
        if (*cuoi != '\0' || val < 0.0f || val > 10.0f) {
            printf("Diem khong hop le\n");
            continue;
        }

        *diemOut = (float)((int)(val * 100.0f + 0.5f)) / 100.0f;
        return 1;
    }
}


static void tinhGPAVaXepLoai(SinhVien *sv) {
    if (sv->soMon <= 0) {
        sv->gpa = 0.0f;
        strcpy(sv->xepLoai, "Chua nhap diem");
        return;
    }

    float tong = 0.0f;
    for (int i = 0; i < sv->soMon; i++) {
        tong += sv->diem[i];
    }
    float diemTB10 = tong / sv->soMon;
    float gpa4 = (diemTB10 / 10.0f) * 4.0f;
    sv->gpa = (float)((int)(gpa4 * 100.0f + 0.5f)) / 100.0f;

    if (sv->gpa >= 3.2f) {
        strcpy(sv->xepLoai, "Gioi");
    } else if (sv->gpa >= 2.5f) {
        strcpy(sv->xepLoai, "Kha");
    } else if (sv->gpa >= 2.0f) {
        strcpy(sv->xepLoai, "Trung binh");
    } else {
        strcpy(sv->xepLoai, "Yeu");
    }
}

// ===== PHẦN 1: QUẢN LÝ DỮ LIỆU BAN ĐẦU =====
int nhapSinhVien(SinhVien *sv) {
    if (!nhapMaSV(sv->maSV, 1)) return 0;
    if (!nhapHoTen(sv->hoTen)) return 0;
    if (!nhapLop(sv->lop)) return 0;

    sv->soMon = 0;
    sv->gpa = 0.0f;
    strcpy(sv->xepLoai, "Chua nhap diem");
    return 1;
}

void themSinhVien() {
    if (n >= MAX_SV) {
        printf("Danh sach da day!\n");
        return;
    }
    SinhVien sv;
    if (nhapSinhVien(&sv)) {
        dsSV[n++] = sv;
        printf("Them sinh vien thanh cong!\n");
    } else {
        printf("Da huy thao tac them sinh vien.\n");
    }
}

void hienThiDanhSach() {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    printf("\n%-12s %-25s %-10s %-8s %-15s\n", "Ma SV", "Ho ten", "Lop", "GPA", "Xep loai");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (!sinhVienDaNhapDiem(&dsSV[i])) {
            printf("%-12s %-25s %-10s %-8s %-15s\n",
                   dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop, "--", dsSV[i].xepLoai);
        } else {
            printf("%-12s %-25s %-10s %-8.2f %-15s\n",
                   dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop,
                   dsSV[i].gpa, dsSV[i].xepLoai);
        }
    }
}

// ===== PHẦN 2: TÌM KIẾM, CẬP NHẬT VÀ XÓA =====
void timKiemSinhVien() {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    char ma[15];
    printf("--- Tim kiem sinh vien ---\n");
    if (!nhapMaSV(ma, 0)) {
        printf("Da huy thao tac tim kiem.\n");
        return;
    }

    int i = timViTriSinhVienTheoMa(ma);
    if (i != -1) {
        printf("\n%-12s %-25s %-10s %-8s %-15s\n", "Ma SV", "Ho ten", "Lop", "GPA", "Xep loai");
        printf("-----------------------------------------------------------------------\n");
        if (!sinhVienDaNhapDiem(&dsSV[i])) {
            printf("%-12s %-25s %-10s %-8s %-15s\n",
                   dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop, "--", dsSV[i].xepLoai);
        } else {
            printf("%-12s %-25s %-10s %-8.2f %-15s\n",
                   dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop,
                   dsSV[i].gpa, dsSV[i].xepLoai);
        }
    } else {
        printf("Khong tim thay sinh vien co ma [%s].\n", ma);
    }
}

void suaSinhVien() {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    char ma[15];
    printf("--- Sua thong tin sinh vien ---\n");
    if (!nhapMaSV(ma, 0)) {
        printf("Da huy thao tac sua.\n");
        return;
    }

    int i = timViTriSinhVienTheoMa(ma);
    if (i == -1) {
        printf("Khong tim thay sinh vien co ma [%s].\n", ma);
        return;
    }

    int luaChon = 0;
    do {
        printf("\n===== CHON PHAN SUA CHO SV [%s] =====\n", dsSV[i].maSV);
        printf("1. Ho ten (Hien tai: %s)\n", dsSV[i].hoTen);
        printf("2. Lop    (Hien tai: %s)\n", dsSV[i].lop);
        printf("3. Ca hai\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        if (scanf("%d", &luaChon) != 1) luaChon = -1;
        xoaBoDem();

        switch (luaChon) {
            case 1:
                if (nhapHoTen(dsSV[i].hoTen)) {
                    printf("Da sua ho ten thanh cong!\n");
                }
                break;
            case 2:
                if (nhapLop(dsSV[i].lop)) {
                    printf("Da sua lop thanh cong!\n");
                }
                break;
            case 3:
                if (nhapHoTen(dsSV[i].hoTen) && nhapLop(dsSV[i].lop)) {
                    printf("Da sua ho ten va lop thanh cong!\n");
                }
                break;
            case 0:
                printf("Da thoat chuc nang sua.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 0);
}

void xoaSinhVien() {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }
    char ma[15];
    printf("--- Xoa sinh vien ---\n");
    if (!nhapMaSV(ma, 0)) {
        printf("Da huy thao tac xoa.\n");
        return;
    }

    int i = timViTriSinhVienTheoMa(ma);
    if (i == -1) {
        printf("Khong tim thay sinh vien co ma [%s].\n", ma);
        return;
    }

    for (int j = i; j < n - 1; j++) {
        dsSV[j] = dsSV[j + 1];
    }
    n--;
    printf("Xoa sinh vien [%s] thanh cong!\n", ma);
}

// ===== PHẦN 3: ĐIỂM SỐ, THỐNG KÊ VÀ SẮP XẾP =====
void nhapDiem() {
    if (n == 0) {
        printf("Danh sach trong! Hay them sinh vien truoc.\n");
        return;
    }

    char ma[15];
    printf("--- Nhap/Cap nhat diem sinh vien ---\n");
    if (!nhapMaSV(ma, 0)) {
        printf("Da huy thao tac nhap diem.\n");
        return;
    }

    int viTri = timViTriSinhVienTheoMa(ma);
    if (viTri == -1) {
        printf("Khong tim thay sinh vien co ma [%s].\n", ma);
        return;
    }

    printf("\n--- Nhap danh sach mon cho sinh vien %s - %s ---\n",
           dsSV[viTri].maSV, dsSV[viTri].hoTen);

    int soMon = 0;
    while (1) {
        printf("Nhap so mon hoc (1-10, nhap 0 de thoat): ");
        char dong[64];
        if (fgets(dong, sizeof(dong), stdin) == NULL) continue;
        if (strchr(dong, '\n') == NULL && !feof(stdin)) xoaBoDem();
        dong[strcspn(dong, "\r\n")] = '\0';

        if (strcmp(dong, "0") == 0) {
            printf("Da huy thao tac nhap diem.\n");
            return;
        }

        char *cuoi;
        long val = strtol(dong, &cuoi, 10);
        if (cuoi == dong || *cuoi != '\0' || val < 1 || val > 10) {
            printf("So mon hoc khong hop le. Vui long nhap so tu 1 den 10.\n");
            continue;
        }
        soMon = (int)val;
        break;
    }

    for (int i = 0; i < soMon; i++) {
        printf("\n-- Mon hoc thu %d --\n", i + 1);
        while (1) {
            char tenMonTam[MAX_TEN_MON];
            if (!nhapTenMonHoc(tenMonTam)) {
                printf("Da huy thao tac nhap diem.\n");
                return;
            }

            int biTrung = 0;
            for (int j = 0; j < i; j++) {
                if (strcmp(dsSV[viTri].tenMon[j], tenMonTam) == 0) {
                    biTrung = 1;
                    break;
                }
            }
            if (biTrung) {
                printf("Mon hoc nay da duoc nhap. Vui long nhap ten khac.\n");
                continue;
            }

            strcpy(dsSV[viTri].tenMon[i], tenMonTam);
            break;
        }

        if (!docDiemHopLe(dsSV[viTri].tenMon[i], &dsSV[viTri].diem[i])) {
            printf("Da huy thao tac nhap diem.\n");
            return;
        }
    }

    dsSV[viTri].soMon = soMon;
    tinhGPAVaXepLoai(&dsSV[viTri]);

    printf("Nhap/cap nhat diem thanh cong! GPA hien tai: %.2f | Xep loai: %s\n",
           dsSV[viTri].gpa, dsSV[viTri].xepLoai);
}

void thongKeDiem() {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }

    printf("\n===== THONG KE GPA VA XEP LOAI =====\n");
    int soSVCoDiem = 0;

    for (int i = 0; i < n; i++) {
        printf("\nSinh vien: %s - %s | Lop: %s\n",
               dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop);

        if (!sinhVienDaNhapDiem(&dsSV[i])) {
            printf("Chua nhap diem.\n");
            continue;
        }

        tinhGPAVaXepLoai(&dsSV[i]);
        printf("%-4s %-30s %-8s\n", "STT", "Ten mon hoc", "Diem");

        for (int j = 0; j < dsSV[i].soMon; j++) {
            printf("%-4d %-30s %-8.2f\n",
                   j + 1, dsSV[i].tenMon[j], dsSV[i].diem[j]);
        }

        printf("GPA (thang 4.0): %.2f\n", dsSV[i].gpa);
        printf("Xep loai: %s\n", dsSV[i].xepLoai);
        soSVCoDiem++;
    }

    printf("\nDa thong ke GPA cho %d/%d sinh vien.\n", soSVCoDiem, n);
}

void sapXepTheoDiem() {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        tinhGPAVaXepLoai(&dsSV[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            int coDiemTruoc = sinhVienDaNhapDiem(&dsSV[j]);
            int coDiemSau = sinhVienDaNhapDiem(&dsSV[j + 1]);
            int canDoiCho = 0;

            if (!coDiemTruoc && coDiemSau) {
                canDoiCho = 1;
            } else if (coDiemTruoc && coDiemSau && dsSV[j].gpa < dsSV[j + 1].gpa) {
                canDoiCho = 1;
            }

            if (canDoiCho) {
                SinhVien tam = dsSV[j];
                dsSV[j] = dsSV[j + 1];
                dsSV[j + 1] = tam;
            }
        }
    }

    printf("\nDa sap xep sinh vien theo GPA giam dan.\n");
    hienThiDanhSach();
}

// ===== PHẦN 4: LƯU VÀ ĐỌC FILE =====
void luuFile() {
    FILE *f = fopen(FILE_NAME, "w");
    if (f == NULL) {
        printf("Loi: Khong the mo file de ghi du lieu!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%s;%s;%s;%d;", dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop, dsSV[i].soMon);
        for (int j = 0; j < dsSV[i].soMon; j++) {
            fprintf(f, "%s:%.2f,", dsSV[i].tenMon[j], dsSV[i].diem[j]);
        }
        fprintf(f, ";%.2f;%s\n", dsSV[i].gpa, dsSV[i].xepLoai);
    }

    fclose(f);
    printf("Luu thanh cong %d sinh vien vao file '%s'!\n", n, FILE_NAME);
}

void docFile() {
    FILE *f = fopen(FILE_NAME, "r");
    if (f == NULL) {
        printf("Khong tim thay file '%s'. Bat dau voi danh sach trong.\n", FILE_NAME);
        return;
    }

    n = 0;
    char line[512];
    while (fgets(line, sizeof(line), f) != NULL && n < MAX_SV) {
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0) continue;

        SinhVien sv;
        memset(&sv, 0, sizeof(SinhVien));
        char monData[256] = "";

        int parsed = sscanf(line, "%[^;];%[^;];%[^;];%d;%[^;];%f;%[^\n]",
                            sv.maSV, sv.hoTen, sv.lop, &sv.soMon,
                            monData, &sv.gpa, sv.xepLoai);

        if (parsed >= 4 && sv.soMon > 0 && strlen(monData) > 0) {
            char *token = strtok(monData, ",");
            int idx = 0;
            while (token != NULL && idx < sv.soMon && idx < MAX_MON) {
                char ten[MAX_TEN_MON] = "";
                float d = 0.0f;
                if (sscanf(token, "%[^:]:%f", ten, &d) == 2) {
                    strcpy(sv.tenMon[idx], ten);
                    sv.diem[idx] = d;
                    idx++;
                }
                token = strtok(NULL, ",");
            }
            sv.soMon = idx;
        }

        dsSV[n++] = sv;
    }

    fclose(f);
    printf("Da tai %d sinh vien tu file '%s'.\n", n, FILE_NAME);
}

// ===== MENU CHÍNH VÀ LUỒNG ĐIỀU KHIỂN =====
void hienThiMenu() {
    printf("\n================ QUAN LY SINH VIEN ================\n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Tim kiem sinh vien theo MSSV\n");
    printf("4. Sua thong tin sinh vien\n");
    printf("5. Xoa sinh vien\n");
    printf("6. Nhap/cap nhat diem\n");
    printf("7. Thong ke GPA va xep loai\n");
    printf("8. Sap xep theo GPA giam dan\n");
    printf("9. Luu danh sach vao file\n");
    printf("10. Doc danh sach tu file\n");
    printf("0. Thoat\n");
    printf("---------------------------------------------------\n");
    printf("Chon chuc nang: ");
}

int main() {
    docFile();

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
            case 9:
                luuFile();
                break;
            case 10:
                docFile();
                break;
            case 0:
                luuFile();
                printf("Cam on ban da su dung chuong trinh. Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (chon != 0);

    return 0;
}