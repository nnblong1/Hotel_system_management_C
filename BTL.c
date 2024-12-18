#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Struct thông tin Phòng
typedef struct Phong {
    int maPhong;
    char kieuPhong[20];
    int sogiuong;
    char thongTinPhong[50];
    bool tinhtrang; // Trống 0, đã thuê 1
    float giaThue;
    struct Phong *next;
} Phong;

// Struct thông tin Khách hàng
typedef struct KhachHang {
    char ten[50];
    int namSinh;
    char cccd[15];
    char gioiTinh[10];
    char soDienThoai[15];
    char queQuan[50];
    Phong *phongThue;
    char ngayThue[15];
    struct KhachHang *next;
} KhachHang;

// Danh sách liên kết chính
typedef struct DanhSachLienKet {
    KhachHang *DanhSachKhachHang;
    Phong *DanhSachPhong;
} DanhSachLienKet;

// Tạo danh sách rỗng
DanhSachLienKet* taoDanhSach() {
    DanhSachLienKet *danhSach = (DanhSachLienKet *)malloc(sizeof(DanhSachLienKet));
    danhSach->DanhSachKhachHang = NULL;
    danhSach->DanhSachPhong = NULL;
    return danhSach;
}

// Kiểm tra danh sách rỗng
bool isEmptyKhachHang(DanhSachLienKet *danhSach) {
    return danhSach->DanhSachKhachHang == NULL;
}

bool isEmptyPhong(DanhSachLienKet *danhSach) {
    return danhSach->DanhSachPhong == NULL;
}

// Hàm nhập chuỗi
void nhapChuoi(const char *thongDiep, char *ketQua, int kichThuoc) {
    printf("%s", thongDiep);
    fgets(ketQua, kichThuoc, stdin);
    ketQua[strcspn(ketQua, "\n")] = '\0'; // Xóa ký tự xuống dòng
}

// Hàm thêm khách hàng mới
void themKhachHang(DanhSachLienKet *danhSach) {
    char cccd[15];
    printf("Nhap so CCCD cua khach hang: ");
    nhapChuoi("", cccd, sizeof(cccd));

    // Kiểm tra khách hàng đã tồn tại hay chưa
    KhachHang *current = danhSach->DanhSachKhachHang;
    while (current) {
        if (strcmp(current->cccd, cccd) == 0) {
            printf("Khach hang da ton tai trong danh sach!\n");
            return;
        }
        current = current->next;
    }

    // Tạo khách hàng mới
    KhachHang *kh = (KhachHang *)malloc(sizeof(KhachHang));
    if (!kh) {
        printf("Khong the cap phat bo nho!\n");
        return;
    }

    strcpy(kh->cccd, cccd);
    nhapChuoi("Nhap ten khach hang: ", kh->ten, sizeof(kh->ten));
    printf("Nhap nam sinh: ");
    scanf("%d", &kh->namSinh);
    getchar();
    nhapChuoi("Nhap gioi tinh: ", kh->gioiTinh, sizeof(kh->gioiTinh));
    nhapChuoi("Nhap so dien thoai: ", kh->soDienThoai, sizeof(kh->soDienThoai));
    nhapChuoi("Nhap que quan: ", kh->queQuan, sizeof(kh->queQuan));

    kh->phongThue = NULL;
    strcpy(kh->ngayThue, ""); // Ngày thuê trống
    kh->next = NULL;

    // Thêm khách hàng vào danh sách liên kết
    if (danhSach->DanhSachKhachHang == NULL) {
        danhSach->DanhSachKhachHang = kh;
    } else {
        KhachHang *current = danhSach->DanhSachKhachHang;
        while (current->next) {
            current = current->next;
        }
        current->next = kh;
    }
    printf("Them khach hang thanh cong!\n");
}
// hàm thêm phòng
void themPhong(DanhSachLienKet *danhSach, Phong *phong) {
    if (danhSach->DanhSachPhong == NULL) {
        danhSach->DanhSachPhong = phong;
    } else {
        Phong *current = danhSach->DanhSachPhong;
        while (current->next) {
            current = current->next;
        }
        current->next = phong;
    }
}
// hàm thêm 10 phòng mặc định

void them10PhongMacDinh(DanhSachLienKet *danhSach) {
    int maPhong[10] = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
    char *kieuPhong[10] = {"Don", "Doi", "Suite", "Deluxe", "Superior", "Studio", "Executive", "Presidential", "Family", "Classic"};
    int soGiuong[10] = {1, 2, 3, 4, 2, 2, 3, 5, 4, 1};
    char *thongTinPhong[10] = {
        "Giuong don, TV, dieu hoa",
        "Giuong doi, ban lam viec",
        "Phong cao cap, tam thu gian",
        "Phong deluxe, ban cong",
        "Phong superior, ho boi",
        "Phong studio, bep nho",
        "Phong executive, sofa",
        "Phong tong thong, phong tam rieng",
        "Phong gia dinh, phong ngu rieng",
        "Phong co dien, thiet ke dep"
    };
    float giaThue[10] = {500.0, 1000.0, 1500.0, 2000.0, 1200.0, 800.0, 1800.0, 3000.0, 2500.0, 700.0};

    for (int i = 0; i < 10; i++) {
        Phong *newPhong = (Phong *)malloc(sizeof(Phong));
        newPhong->maPhong = maPhong[i];
        strcpy(newPhong->kieuPhong, kieuPhong[i]);
        newPhong->sogiuong = soGiuong[i];
        strcpy(newPhong->thongTinPhong, thongTinPhong[i]);
        newPhong->tinhtrang = false;
        newPhong->giaThue = giaThue[i];
        newPhong->next = NULL;
        themPhong(danhSach, newPhong);  
    }  

    printf("Da them 10 phong mac dinh vao danh sach!\n");
}
// hàm hiển thị 10 phòng mặc định
void hienThi10PhongMacDinh(DanhSachLienKet *danhSach) {
    Phong *current = danhSach->DanhSachPhong;
    int count = 0;
    while (current && count < 10) {
        printf("Ma phong: %d, Kieu phong: %s, So giuong: %d, Thong tin phong: %s, Tinh trang: %s, Gia thue: %.2f VND\n",
               current->maPhong, current->kieuPhong, current->sogiuong, current->thongTinPhong, current->tinhtrang ? "Da thue" : "Trong", current->giaThue);
        current = current->next;
        count++;
    }
}
// Hàm tìm khách hàng theo CCCD
KhachHang* timKhachHangTheoCCCD(DanhSachLienKet *danhSach, const char *cccd) {
    KhachHang *current = danhSach->DanhSachKhachHang;
    while (current) {
        if (strcmp(current->cccd, cccd) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Hàm tìm phòng còn trống
Phong* timPhongConTrong(DanhSachLienKet *danhSach) {
    Phong *current = danhSach->DanhSachPhong;
    while (current) {
        if (!current->tinhtrang) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Hiển thị danh sách khách hàng theo bảng cơ sở dữ liệu
void hienThiDanhSachKhachHang(DanhSachLienKet *danhSach) {
    if (isEmptyKhachHang(danhSach)) {
        printf("Danh sach khach hang rong!\n");
        return;
    }

    KhachHang *current = danhSach->DanhSachKhachHang;
    printf("+---------------------------------------+\n");
    printf("|  Ten  |  CCCD  |  SDT  |  Phong  |  Que quan  |\n");
    printf("+---------------------------------------+\n");
    while (current) {
        printf("| %s | %s | %s | %s | %s |\n",
               current->ten, current->cccd, current->soDienThoai,
               current->phongThue ? current->phongThue->kieuPhong : "Chua thue",
               current->queQuan);
        current = current->next;
    }
    printf("+---------------------------------------+\n");
}

// Xóa khách hàng khỏi danh sách
void xoaKhachHang(DanhSachLienKet *danhSach, const char *cccd) {
    if (isEmptyKhachHang(danhSach)) {
        printf("Danh sach khach hang rong!\n");
        return;
    }

    KhachHang *current = danhSach->DanhSachKhachHang;
    KhachHang *prev = NULL;

    while (current) {
        if (strcmp(current->cccd, cccd) == 0) {
            if (prev == NULL) {
                danhSach->DanhSachKhachHang = current->next;
            } else {
                prev->next = current->next;
            }

            if (current->phongThue) {
                current->phongThue->tinhtrang = false; // Đặt phòng lại thành trống
            }

            free(current);
            printf("Xoa khach hang thanh cong!\n");
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Khong tim thay khach hang voi CCCD: %s\n", cccd);
}

// Thanh toán tiền phòng cho khách hàng
void thanhToanTienPhong(DanhSachLienKet *danhSach, const char *cccd) {
    KhachHang *kh = timKhachHangTheoCCCD(danhSach, cccd);
    if (!kh) {
        printf("Khach hang khong ton tai!\n");
        return;
    }

    if (!kh->phongThue) {
        printf("Khach hang chua thue phong!\n");
        return;
    }

    char ngayTra[15];
    printf("Nhap ngay tra phong (dd/mm/yyyy): ");
    nhapChuoi("", ngayTra, sizeof(ngayTra));

    time_t tThue = mktime(strptime(kh->ngayThue, "%d/%m/%Y", NULL));
    time_t tTra = mktime(strptime(ngayTra, "%d/%m/%Y", NULL));

    if (tTra < tThue) {
        printf("Ngay tra phong khong hop le!\n");
        return;
    }

    double soNgayThue = difftime(tTra, tThue) / (60 * 60 * 24);
    float tienPhong = soNgayThue * kh->phongThue->giaThue;

    printf("So ngay thue: %.0f\n", soNgayThue);
    printf("Tien phong: %.2f\n", tienPhong);

    kh->phongThue->tinhtrang = false;
    kh->phongThue = NULL;

    printf("Thanh toan thanh cong!\n");
}
// Hàm đặt phòng
void datPhong(DanhSachLienKet *danhSach, char cccd[15]) {
    KhachHang *kh = timKhachHangTheoCCCD(danhSach, cccd);
    if (!kh) {
        printf("Khach hang chua ton tai! Vui long nhap thong tin khach hang moi:\n");
        themKhachHang(danhSach);
        kh = timKhachHangTheoCCCD(danhSach, cccd);
    }

    int maPhong;
    printf("Nhap ma phong can dat: ");
    scanf("%d", &maPhong);
    getchar();

    Phong *ph = danhSach->DanhSachPhong;
    while (ph) {
        if (ph->maPhong == maPhong) {
            break;
        }
        ph = ph->next;
    }

    if (!ph) {
        printf("Phong khong ton tai!\n");
        return;
    }

    if (ph->tinhtrang) {
        printf("Phong da duoc thue!\n");
        return;
    }

    char ngayThue[15];
    printf("Nhap ngay thue (dd/mm/yyyy): ");
    nhapChuoi("", ngayThue, sizeof(ngayThue));
    strcpy(kh->ngayThue, ngayThue);

    ph->tinhtrang = true;
    kh->phongThue = ph;
    printf("Dat phong thanh cong!\n");
}
// hàm sửa thông tin của khách hàng
void suaThongTinKhachHang(DanhSachLienKet *danhSach) {
    char cccd[15];
    printf("Nhap CCCD cua khach hang can sua thong tin: ");
    nhapChuoi("", cccd, sizeof(cccd));

    KhachHang *kh = timKhachHangTheoCCCD(danhSach, cccd);
    if (!kh) {
        printf("Khach hang khong ton tai!\n");
        return;
    }
    int choose;
    do {
        printf("\nLua chon:\n");
        printf("1. Sua ten\n");
        printf("2. Sua dia chi\n");
        printf("3. Sua so dien thoai\n");
        printf("4. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choose);
        getchar();
        switch (choose) {
            case 1:
                nhapChuoi("Nhap ten moi: ", kh->ten, sizeof(kh->ten));
                break;
            case 2:
                nhapChuoi("Nhap dia chi moi: ", kh->queQuan, sizeof(kh->queQuan));
                break;
            case 3:
                nhapChuoi("Nhap so dien thoai moi: ", kh->soDienThoai, sizeof(kh->soDienThoai));
                break;
            case 4:
                break;
            default:
                printf("Lua chon khong hop le!\n");
                break;
        }
    } while (choose != 4);
}


// Hàm main
int main() {
    DanhSachLienKet *danhSach = taoDanhSach();
    them10PhongMacDinh(danhSach);
    int luaChon;

    do {
        printf("\nQuan ly khach san:\n");
        printf("1. Them khach hang\n");
        printf("2. Hien thi danh sach khach hang\n");
        printf("3. Hien thi danh sach phong\n");
        printf("4. Dat phong cho khach\n");
        printf("5. Thanh toan tien phong\n");
        printf("6. Sua thong tin khach hang\n");
        printf("7. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        getchar();

        switch (luaChon) {
            case 1:
                themKhachHang(danhSach);
                break;
            case 2:
                hienThiDanhSachKhachHang(danhSach);
                break;
            case 3:
                hienThi10PhongMacDinh(danhSach);
                break;
            case 4: {
                char cccd[15];
                printf("Nhap so CCCD cua khach hang: ");
                nhapChuoi("", cccd, sizeof(cccd));
                datPhong(danhSach, cccd);
                break;
            }
            case 5: {
                char cccd[15];
                printf("Nhap so CCCD cua khach hang: ");
                nhapChuoi("", cccd, sizeof(cccd));
                thanhToanTienPhong(danhSach, cccd);
                break;
            }
            case 6:
                suaThongTinKhachHang(danhSach);
                break;
            case 7:
                printf("Thoat chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 7);

    return 0;
}
