/*
 * PHAN CONG: THIEN KY - DIEM SO, THONG KE VA KIEM THU
 *
 * File nay gom rieng cac ham do Thien Ky phu trach:
 *   - Nhap/cap nhat diem sinh vien
 *   - Tinh diem trung binh va xep loai hoc luc
 *   - Sap xep sinh vien theo diem trung binh giam dan
 *
 * File nay dung chung struct SinhVien, mang dsSV, bien n, va hai ham
 * docChuoi()/xoaBoDem() duoc dinh nghia trong file chuong trinh chinh.
 * Khi tich hop, hay thay cac than ham mau nhapDiem(), thongKeDiem(),
 * sapXepTheoDiem() trong file chinh bang cac khai bao prototype.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SV 100

/* Cau truc phai trung khop voi struct SinhVien trong file chuong trinh chinh. */
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

/* Du lieu va ham duoc cung cap boi file chuong trinh chinh. */
extern SinhVien dsSV[MAX_SV];
extern int n;
void xoaBoDem(void);
void docChuoi(char s[], int kichThuoc);

/* Tim vi tri sinh vien theo ma; tra ve -1 neu khong tim thay. */
static int timViTriSinhVienTheoMa(const char ma[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(dsSV[i].maSV, ma) == 0) {
            return i;
        }
    }
    return -1;
}

/* Doc diem hop le trong khoang 0-10; nhap sai thi yeu cau nhap lai. */
static int docDiemHopLe(const char tenMon[], float *diem) {
    char dong[100];

    while (1) {
        printf("Nhap diem %s (0-10): ", tenMon);

        if (fgets(dong, sizeof(dong), stdin) == NULL) {
            printf("Khong doc duoc du lieu diem. Huy thao tac nhap diem.\n");
            return 0;
        }

        /* Neu dong qua dai, bo phan con lai de tranh troi lenh. */
        if (strchr(dong, '\n') == NULL && !feof(stdin)) {
            xoaBoDem();
        }

        char *cuoi;
        float giaTri = strtof(dong, &cuoi);
        while (isspace((unsigned char)*cuoi)) {
            cuoi++;
        }

        if (cuoi == dong || *cuoi != '\0' ||
            !(giaTri >= 0.0f && giaTri <= 10.0f)) {
            printf("Diem khong hop le. Hay nhap mot so tu 0 den 10.\n");
            continue;
        }

        *diem = giaTri;
        return 1;
    }
}

/*
 * Phan biet sinh vien chua nhap diem voi sinh vien co diem that su bang 0.
 * Sau khi nhap diem, xepLoai duoc dat thanh "Chua tinh" cho den khi thong ke.
 */
static int sinhVienDaNhapDiem(const SinhVien *sv) {
    return sv->xepLoai[0] != '\0' ||
           sv->diemToan != 0.0f ||
           sv->diemLy != 0.0f ||
           sv->diemHoa != 0.0f;
}

/* Tinh diem trung binh va gan xep loai theo nguong tam cua du an. */
static void tinhDiemVaXepLoai(SinhVien *sv) {
    sv->diemTB = (sv->diemToan + sv->diemLy + sv->diemHoa) / 3.0f;

    /* Tai lieu chua quy dinh moc xep loai cu the. */
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

/* CHUC NANG 1: Nhap/cap nhat diem theo ma sinh vien. */
void nhapDiem(void) {
    if (n == 0) {
        printf("Danh sach trong! Hay them sinh vien truoc.\n");
        return;
    }

    char ma[15];
    printf("Nhap ma sinh vien can nhap/cap nhat diem: ");
    docChuoi(ma, (int)sizeof(ma));

    if (strlen(ma) == 0) {
        printf("Ma sinh vien khong duoc de trong!\n");
        return;
    }

    int viTri = timViTriSinhVienTheoMa(ma);
    if (viTri == -1) {
        printf("Khong tim thay sinh vien co ma %s.\n", ma);
        return;
    }

    float toan, ly, hoa;
    printf("Nhap diem cho sinh vien %s - %s\n",
           dsSV[viTri].maSV, dsSV[viTri].hoTen);

    if (!docDiemHopLe("Toan", &toan)) return;
    if (!docDiemHopLe("Ly", &ly)) return;
    if (!docDiemHopLe("Hoa", &hoa)) return;

    /* Chi cap nhat sau khi ca ba diem da duoc nhap hop le. */
    dsSV[viTri].diemToan = toan;
    dsSV[viTri].diemLy = ly;
    dsSV[viTri].diemHoa = hoa;
    dsSV[viTri].diemTB = 0.0f;
    strcpy(dsSV[viTri].xepLoai, "Chua tinh");

    printf("Nhap/cap nhat diem thanh cong! Hay chon muc 7 de tinh diem TB va xep loai.\n");
}

/* CHUC NANG 2: Tinh va hien thi diem trung binh, xep loai tung sinh vien. */
void thongKeDiem(void) {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }

    printf("\n===== DIEM TRUNG BINH VA XEP LOAI =====\n");
    printf("%-12s %-25s %-10s %-8s %-15s\n",
           "Ma SV", "Ho ten", "Lop", "Diem TB", "Xep loai");

    int soSVCoDiem = 0;
    for (int i = 0; i < n; i++) {
        if (!sinhVienDaNhapDiem(&dsSV[i])) {
            printf("%-12s %-25s %-10s %-8s %-15s\n",
                   dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop,
                   "--", "Chua nhap diem");
            continue;
        }

        tinhDiemVaXepLoai(&dsSV[i]);
        soSVCoDiem++;
        printf("%-12s %-25s %-10s %-8.2f %-15s\n",
               dsSV[i].maSV, dsSV[i].hoTen, dsSV[i].lop,
               dsSV[i].diemTB, dsSV[i].xepLoai);
    }

    printf("Da tinh diem TB va xep loai cho %d/%d sinh vien.\n",
           soSVCoDiem, n);
}

/* CHUC NANG 3: Bubble Sort theo diem TB giam dan. */
void sapXepTheoDiem(void) {
    if (n == 0) {
        printf("Danh sach trong!\n");
        return;
    }

    /* Cap nhat diem TB truoc khi sap xep, neu sinh vien da nhap diem. */
    for (int i = 0; i < n; i++) {
        if (sinhVienDaNhapDiem(&dsSV[i])) {
            tinhDiemVaXepLoai(&dsSV[i]);
        } else {
            dsSV[i].diemTB = 0.0f;
            dsSV[i].xepLoai[0] = '\0';
        }
    }

    /* Sinh vien co diem cao o truoc; sinh vien chua nhap diem o cuoi. */
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
