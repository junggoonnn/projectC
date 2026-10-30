/*
 * QUAN LY DIEM, THONG KE VA SAP XEP SINH VIEN
 *
 * PHIEN BAN MOI:
 * - Moi sinh vien co danh sach mon hoc rieng.
 * - So mon, ten mon va diem duoc luu truc tiep trong struct SinhVien.
 * - File chuong trinh chinh se can dong bo struct SinhVien theo cau truc
 *   duoc khai bao ben duoi khi tich hop.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SV 100
#define MAX_MON 20
#define MAX_TEN_MON 30

/*
 * STRUCT MOI: moi sinh vien co the co so mon va ten mon khac nhau.
 * Khi tich hop, file chinh can dung cung struct nay.
 */
typedef struct {
    char maSV[15];
    char hoTen[50];
    char lop[15];

    int soMon;
    char tenMon[MAX_MON][MAX_TEN_MON];
    float diem[MAX_MON];

    float diemTB;
    char xepLoai[15];
} SinhVien;

/* Mang sinh vien va so luong sinh vien se do file chinh dinh nghia. */
extern SinhVien dsSV[MAX_SV];
extern int n;

/* Hai ham nhap chuoi/lam sach bo dem duoc file chinh cung cap. */
void xoaBoDem(void);
void docChuoi(char s[], int kichThuoc);

/* Tim sinh vien theo ma. */
static int timViTriSinhVienTheoMa(const char ma[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(dsSV[i].maSV, ma) == 0) return i;
    }
    return -1;
}

/* Doc so nguyen trong khoang cho phep. */
static int docSoNguyenTrongKhoang(const char thongBao[], int min,
                                  int max, int *ketQua) {
    char dong[128];

    while (1) {
        printf("%s", thongBao);
        if (fgets(dong, sizeof(dong), stdin) == NULL) return 0;

        if (strchr(dong, '\n') == NULL && !feof(stdin)) xoaBoDem();

        char *cuoi;
        long giaTri = strtol(dong, &cuoi, 10);
        while (isspace((unsigned char)*cuoi)) cuoi++;

        if (cuoi == dong || *cuoi != '\0' ||
            giaTri < min || giaTri > max) {
            printf("Gia tri khong hop le. Hay nhap so tu %d den %d.\n",
                   min, max);
            continue;
        }

        *ketQua = (int)giaTri;
        return 1;
    }
}

/* Doc ten mon, khong chap nhan ten rong hoac qua dai. */
static int docTenMon(char tenMon[], int kichThuoc) {
    char dong[256];

    if (fgets(dong, sizeof(dong), stdin) == NULL) return 0;

    if (strchr(dong, '\n') == NULL && !feof(stdin)) {
        xoaBoDem();
        printf("Ten mon qua dai. Toi da %d ky tu.\n", kichThuoc - 1);
        return -1;
    }

    dong[strcspn(dong, "\n")] = '\0';

    if ((int)strlen(dong) >= kichThuoc) {
        printf("Ten mon qua dai. Toi da %d ky tu.\n", kichThuoc - 1);
        return -1;
    }

    strcpy(tenMon, dong);
    return 1;
}

/* Doc diem hop le tu 0 den 10. */
static int docDiemHopLe(const char tenMon[], float *diem) {
    char dong[128];

    while (1) {
        printf("Nhap diem mon %s (0-10): ", tenMon);
        if (fgets(dong, sizeof(dong), stdin) == NULL) return 0;

        if (strchr(dong, '\n') == NULL && !feof(stdin)) xoaBoDem();

        char *cuoi;
        float giaTri = strtof(dong, &cuoi);
        while (isspace((unsigned char)*cuoi)) cuoi++;

        if (cuoi == dong || *cuoi != '\0' ||
            !(giaTri >= 0.0f && giaTri <= 10.0f)) {
            printf("Diem khong hop le. Hay nhap mot so tu 0 den 10.\n");
            continue;
        }

        *diem = giaTri;
        return 1;
    }
}

static int sinhVienDaNhapDiem(const SinhVien *sv) {
    return sv->soMon > 0;
}

/* Tinh diem trung binh va xep loai tu danh sach mon cua sinh vien. */
static void tinhDiemVaXepLoai(SinhVien *sv) {
    if (sv->soMon <= 0) {
        sv->diemTB = 0.0f;
        sv->xepLoai[0] = '\0';
        return;
    }

    float tong = 0.0f;
    for (int i = 0; i < sv->soMon; i++) {
        tong += sv->diem[i];
    }
    sv->diemTB = tong / sv->soMon;

    if (sv->diemTB >= 8.0f) {
        strcpy(sv->xepLoai, "Gioi");
    } else if (sv->diemTB >= 6.5f) {
        strcpy(sv->xepLoai, "Kha");
    } else if (sv->diemTB >= 5.0f) {
        strcpy(sv->xepLoai, "Trung binh");
    } else {
        strcpy(sv->xepLoai, "Yeu");
    }
}

/* CHUC NANG 1: Nhap/cap nhat danh sach mon hoc va diem cua mot sinh vien. */
void nhapDiem(void) {
    if (n == 0) {
        printf("Danh sach trong! Hay them sinh vien truoc.\n");
        return;
    }

    char ma[15];
    printf("Nhap ma sinh vien can nhap/cap nhat diem: ");
    docChuoi(ma, (int)sizeof(ma));

    if (ma[0] == '\0') {
        printf("Ma sinh vien khong duoc de trong!\n");
        return;
    }

    int viTri = timViTriSinhVienTheoMa(ma);
    if (viTri == -1) {
        printf("Khong tim thay sinh vien co ma %s.\n", ma);
        return;
    }

    printf("Nhap danh sach mon cho sinh vien %s - %s\n",
           dsSV[viTri].maSV, dsSV[viTri].hoTen);

    int soMon;
    if (!docSoNguyenTrongKhoang("Nhap so mon hoc (1-20): ",
                                1, MAX_MON, &soMon)) return;

    /* Dung mang tam de khong lam mat diem cu neu nhap chua hoan tat. */
    char tenMonTam[MAX_MON][MAX_TEN_MON] = {{0}};
    float diemTam[MAX_MON] = {0};

    for (int i = 0; i < soMon; i++) {
        while (1) {
            printf("Nhap ten mon hoc thu %d: ", i + 1);
            int ketQuaDoc = docTenMon(tenMonTam[i], MAX_TEN_MON);

            if (ketQuaDoc == 0) return;
            if (ketQuaDoc < 0) continue;

            if (tenMonTam[i][0] == '\0') {
                printf("Ten mon hoc khong duoc de trong.\n");
                continue;
            }

            int biTrung = 0;
            for (int j = 0; j < i; j++) {
                if (strcmp(tenMonTam[i], tenMonTam[j]) == 0) {
                    biTrung = 1;
                    break;
                }
            }

            if (biTrung) {
                printf("Mon hoc nay da duoc nhap. Hay nhap ten khac.\n");
                continue;
            }
            break;
        }

        if (!docDiemHopLe(tenMonTam[i], &diemTam[i])) return;
    }

    dsSV[viTri].soMon = soMon;
    for (int i = 0; i < soMon; i++) {
        strcpy(dsSV[viTri].tenMon[i], tenMonTam[i]);
        dsSV[viTri].diem[i] = diemTam[i];
    }

    /* Xoa phan du cua lan nhap truoc neu so mon moi it hon. */
    for (int i = soMon; i < MAX_MON; i++) {
        dsSV[viTri].tenMon[i][0] = '\0';
        dsSV[viTri].diem[i] = 0.0f;
    }

    dsSV[viTri].diemTB = 0.0f;
    strcpy(dsSV[viTri].xepLoai, "Chua tinh");

    printf("Nhap/cap nhat diem thanh cong! Hay chon muc thong ke de tinh diem TB va xep loai.\n");
}

/* CHUC NANG 2: Thong ke diem tung mon, diem TB va xep loai. */
void thongKeDiem(void) {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }

    printf("\n===== THONG KE DIEM VA XEP LOAI =====\n");
    int soSVCoDiem = 0;

    for (int i = 0; i < n; i++) {
        printf("\nSinh vien: %s - %s | Lop: %s\n",
               dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop);

        if (!sinhVienDaNhapDiem(&dsSV[i])) {
            dsSV[i].diemTB = 0.0f;
            dsSV[i].xepLoai[0] = '\0';
            printf("Chua nhap diem.\n");
            continue;
        }

        tinhDiemVaXepLoai(&dsSV[i]);
        printf("%-4s %-30s %-8s\n", "STT", "Ten mon hoc", "Diem");

        for (int j = 0; j < dsSV[i].soMon; j++) {
            printf("%-4d %-30s %-8.2f\n",
                   j + 1, dsSV[i].tenMon[j], dsSV[i].diem[j]);
        }

        printf("Diem trung binh: %.2f\n", dsSV[i].diemTB);
        printf("Xep loai: %s\n", dsSV[i].xepLoai);
        soSVCoDiem++;
    }

    printf("\nDa thong ke diem cho %d/%d sinh vien.\n", soSVCoDiem, n);
}

/* CHUC NANG 3: Sap xep diem TB giam dan; chua co diem nam o cuoi. */
void sapXepTheoDiem(void) {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        tinhDiemVaXepLoai(&dsSV[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            int coDiemTruoc = sinhVienDaNhapDiem(&dsSV[j]);
            int coDiemSau = sinhVienDaNhapDiem(&dsSV[j + 1]);
            int canDoiCho = 0;

            if (!coDiemTruoc && coDiemSau) {
                canDoiCho = 1;
            } else if (coDiemTruoc && coDiemSau &&
                       dsSV[j].diemTB < dsSV[j + 1].diemTB) {
                canDoiCho = 1;
            }

            if (canDoiCho) {
                SinhVien tam = dsSV[j];
                dsSV[j] = dsSV[j + 1];
                dsSV[j + 1] = tam;
            }
        }
    }

    printf("\nDa sap xep sinh vien theo diem TB giam dan.\n");
    printf("%-12s %-25s %-10s %-8s %-15s\n",
           "Ma SV", "Ho ten", "Lop", "Diem TB", "Xep loai");

    for (int i = 0; i < n; i++) {
        if (!sinhVienDaNhapDiem(&dsSV[i])) {
            printf("%-12s %-25s %-10s %-8s %-15s\n",
                   dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop,
                   "--", "Chua nhap diem");
        } else {
            printf("%-12s %-25s %-10s %-8.2f %-15s\n",
                   dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop,
                   dsSV[i].diemTB, dsSV[i].xepLoai);
        }
    }
}
