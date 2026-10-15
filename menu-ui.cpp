#include <stdio.h>
int main() {
	int LuaChon = 0;
	do {
		printf("---------------------------------------");
		printf("\n         QUAN LY SINH VIEN \n");
		printf("---------------------------------------\n");
		printf("1. Them thong tin sinh vien\n");
		printf("2. Hien thi danh sach sinh vien\n");
		printf("3. Tra cuu thong tin sinh vien\n");
		printf("4. Chinh sua thong tin sinh vien\n");
		printf("5. Loc thong tin sinh vien\n");
		printf("6. Thoat\n");
		printf("---------------------------------------\n");
		printf("Chon muc: ");
		scanf("%d", &LuaChon);
		switch (LuaChon) {
			case 1:
				printf("PLHD1");
				break;
			case 2:	
				printf("PLHD2");
				break;
			case 3:
				printf("PLHD3");	
				break;
			case 4:
				printf("PLHD4");
				break;
			case 5:
				printf("PLHD5");
				break;
			case 6:
				return 0;						
		}
	printf("\n");	
 	}
 	while (LuaChon != 0);
}