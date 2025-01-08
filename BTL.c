#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Struct thong tin phong
typedef struct Phong {
    int maPhong;
    char kieuPhong[20];
    int sogiuong;
    char thongTinPhong[50];
    bool tinhtrang; 
    float giaThue;
    struct Phong *next;
} Phong;

//struct Dich vu
typedef struct DichVu {
    int soLuong;
    float donGia, sogio;
} DichVu;

// struct KhachHang 
typedef struct KhachHang {
    char ten[50];
    int namSinh;
    char cccd[15];
    char gioiTinh[10];
    char soDienThoai[15];
    char queQuan[50];
    Phong *phongThue;
    char ngayThue[15];
    DichVu doAn;
    DichVu duaDon;
    DichVu giatLa;
    DichVu trongTre;
    struct KhachHang *next;
} KhachHang;

// Danh sach lien ket chinh
typedef struct DanhSachLienKet {
    KhachHang *DanhSachKhachHang;
    Phong *DanhSachPhong;
} DanhSachLienKet;

// Khoi tao danh sach
DanhSachLienKet* taoDanhSach() {
    DanhSachLienKet *danhSach = (DanhSachLienKet *)malloc(sizeof(DanhSachLienKet));
    danhSach->DanhSachKhachHang = NULL;
    danhSach->DanhSachPhong = NULL;
    return danhSach;
}

// Kiem tra danh sach rong
bool isEmptyKhachHang(DanhSachLienKet *danhSach) {
    return danhSach->DanhSachKhachHang == NULL;
}

bool isEmptyPhong(DanhSachLienKet *danhSach) {
    return danhSach->DanhSachPhong == NULL;
}

// Ham nhap chuoi
void nhapChuoi(const char *thongDiep, char *ketQua, int kichThuoc) {
    printf("%s", thongDiep);
    fgets(ketQua, kichThuoc, stdin);
    ketQua[strcspn(ketQua, "\n")] = '\0'; 
}

// Ham them khach hang moi
void themKhachHang(DanhSachLienKet *danhSach) {
    char cccd[15];
    printf("Nhap so CCCD cua khach hang: ");
    nhapChuoi("", cccd, sizeof(cccd));

    // Kiem tra khach hang ton tai hay chua
    KhachHang *current = danhSach->DanhSachKhachHang;
    while (current) {
        if (strcmp(current->cccd, cccd) == 0) {
            printf("Khach hang da ton tai trong danh sach!\n");
            return;
        }
        current = current->next;
    }

    // Tao khach hang moi
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
    strcpy(kh->ngayThue, "");
    kh->next = NULL;

    // Them khach hang vao danh sach lien ket
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
// Them 10 phong mac dinh

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
// Ham hien thi 10 phong mac dinh
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
// Ham tim khach hang theo cccd
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

// ham tim phong con trong
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

// Ham hien thi danh sach khach hang
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

// Xoa khach hang khoi danh sach
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
                current->phongThue->tinhtrang = false; // reset tinh trang phong ve false
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

// ham tinh so ngay giua 2 moc thoi gian
int tinhSoNgay(const char *ngayBatDau, const char *ngayKetThuc) {
    struct tm tmBatDau = {0}, tmKetThuc = {0};

    
    if (sscanf(ngayBatDau, "%d/%d/%d", &tmBatDau.tm_mday, &tmBatDau.tm_mon, &tmBatDau.tm_year) != 3 ||
        sscanf(ngayKetThuc, "%d/%d/%d", &tmKetThuc.tm_mday, &tmKetThuc.tm_mon, &tmKetThuc.tm_year) != 3) {
        return -1; 
    }

    tmBatDau.tm_mon -= 1;  
    tmBatDau.tm_year -= 1900; 
    tmKetThuc.tm_mon -= 1;
    tmKetThuc.tm_year -= 1900;

    time_t timeBatDau = mktime(&tmBatDau);
    time_t timeKetThuc = mktime(&tmKetThuc);

    if (timeBatDau == -1 || timeKetThuc == -1 || timeKetThuc < timeBatDau) {
        return -1; //
    }

    double diffInSeconds = difftime(timeKetThuc, timeBatDau);
    return (int)(diffInSeconds / (60 * 60 * 24)); // tra ve so ngay
}

// Ham dat phong
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
// Ham sua thong tin khach hang
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

// Ham them dich vu
void themDichVu(DanhSachLienKet *danhSach) {
    char cccd[15];
    printf("Nhap CCCD cua khach hang: ");
    nhapChuoi("", cccd, sizeof(cccd));

    KhachHang *kh = timKhachHangTheoCCCD(danhSach, cccd);
    if (!kh) {
        printf("Khach hang khong ton tai!\n");
        return;
    }

    int luaChon;
    printf("Chon dich vu can them:\n");
    printf("1. Do an\n2. Dua don\n3. Giat la\n4. Trong tre\n");
    printf("Nhap lua chon: ");
    scanf("%d", &luaChon);
    getchar();

    int soLuong;
    float donGia, sogio;
    printf("Nhap so luong (don vi la kilogam voi giat la): ");
    scanf("%d", &soLuong);
    printf("Nhap don gia: ");
    scanf("%f", &donGia);
    printf("Nhap so gio: ");
    scanf("%f", &sogio);
    getchar();

    switch (luaChon) {
        case 1:
            kh->doAn.soLuong += soLuong;
            kh->doAn.donGia = donGia;
            break;
        case 2:
            kh->duaDon.sogio += sogio;
            kh->duaDon.donGia = donGia;
            break;
        case 3:
            kh->giatLa.soLuong += soLuong;
            kh->giatLa.donGia = donGia;
            break;
        case 4:
            kh->trongTre.sogio += sogio;
            kh->trongTre.donGia = donGia;
            break;
        default:
            printf("Lua chon khong hop le!\n");
    }

    printf("Them dich vu thanh cong!\n");
}


// Ham xoa dich vu
void xoaDichVu(DanhSachLienKet *danhSach) {
    char cccd[15];
    printf("Nhap CCCD cua khach hang: ");
    nhapChuoi("", cccd, sizeof(cccd));

    KhachHang *kh = timKhachHangTheoCCCD(danhSach, cccd);
    if (!kh) {
        printf("Khach hang khong ton tai!\n");
        return;
    }

    int luaChon;
    printf("Chon dich vu can xoa:\n");
    printf("1. Do an\n2. Dua don\n3. Giat la\n4. Trong tre\n");
    printf("Nhap lua chon: ");
    scanf("%d", &luaChon);
    getchar();

    switch (luaChon) {
        case 1:
            kh->doAn.soLuong = 0;
            kh->doAn.donGia = 0;
            break;
        case 2:
            kh->duaDon.sogio = 0;
            kh->duaDon.donGia = 0;
            break;
        case 3:
            kh->giatLa.soLuong = 0;
            kh->giatLa.donGia = 0;
            break;
        case 4:
            kh->trongTre.sogio = 0;
            kh->trongTre.donGia = 0;
            break;
        default:
            printf("Lua chon khong hop le!\n");
    }

    printf("Xoa dich vu thanh cong!\n");
}

// ham tinh tong chi phi dich vu
float tinhTongChiPhiDichVu(KhachHang *kh) {
    if (!kh) return 0;
    float tongChiPhi = 0;
    tongChiPhi += kh->doAn.soLuong * kh->doAn.donGia;
    tongChiPhi += kh->duaDon.sogio * kh->duaDon.donGia;
    tongChiPhi += kh->giatLa.soLuong * kh->giatLa.donGia;
    tongChiPhi += kh->trongTre.sogio * kh->trongTre.donGia;
    return tongChiPhi;
}

// ham hien thi thong tin hoa don
void hienThiHoaDon(DanhSachLienKet *danhSach, const char *cccd) {
    KhachHang *kh = timKhachHangTheoCCCD(danhSach, cccd);
    if (!kh) {
        printf("Khach hang khong ton tai!\n");
        return;
    }

    if (!kh->phongThue) {
        printf("Khach hang chua thue phong, khong co hoa don.\n");
        return;
    }
    
    // Tinh tong chi phi thue phong
    float chiPhiPhong = 0;
    if (strlen(kh->ngayThue) > 0) {
        char ngayTra[15];
        printf("Nhap ngay tra phong (dd/mm/yyyy): ");
        nhapChuoi("", ngayTra, sizeof(ngayTra));

        int soNgayThue = tinhSoNgay(kh->ngayThue, ngayTra);
        if (soNgayThue > 0) {
            chiPhiPhong = soNgayThue * kh->phongThue->giaThue;
        } else {
            printf("Ngay thue hoac ngay tra khong hop le!\n");
            return;
        }
    }

    printf("================ HOA DON CHI TIET ================\n");
    printf("| Khach hang: %s                             |\n", kh->ten);
    printf("| CCCD: %s                                    |\n", kh->cccd);
    printf("| Phong thue: %s (%d giuong)                 |\n", kh->phongThue->kieuPhong, kh->phongThue->sogiuong);
    printf("| Ngay thue: %s                               |\n", kh->ngayThue);
    printf("| Dich vu da su dung: \n");
    printf("%-20s %-10s %-10s %-15s\n", "Ten dich vu", "So luong", "So gio", "Don gia");
    printf("-------------------------------------------------\n");
    printf("%-20s %-20d %-15.2f\n",
        kh->doAn,
        kh->doAn.soLuong,
        kh->doAn.donGia);
    printf("%-30s %-10.2f %-15.2f\n",
       kh->duaDon,
       kh->duaDon.sogio,
       kh->duaDon.donGia);
    printf("%-20s %-20d %-15.2f\n",
       kh->giatLa,
       kh->giatLa.soLuong,
       kh->giatLa.donGia);
    printf("%-30s %-10.2f %-15.2f\n",
       kh->trongTre,
       kh->trongTre.sogio,
       kh->trongTre.donGia);
    printf("-------------------------------------------------\n");

    // Tinh tong chi phi dich vu
    float chiPhiDichVu = tinhTongChiPhiDichVu(kh);

    // Tong hoa don
    float tongHoaDon = chiPhiPhong + chiPhiDichVu;

    printf("| Chi phi thue phong: %.2f VND               |\n", chiPhiPhong);
    printf("| Chi phi dich vu: %.2f VND                  |\n", chiPhiDichVu);
    printf("| Tong chi phi: %.2f VND                     |\n", chiPhiPhong + chiPhiDichVu);

    // Reset trang thai phong va khach hang sau khi thanh toan
    kh->phongThue->tinhtrang = false;
    kh->phongThue = NULL;
    strcpy(kh->ngayThue, "");
    kh->doAn.soLuong = kh->duaDon.soLuong = kh->giatLa.soLuong = kh->trongTre.soLuong = 0;
    kh->doAn.donGia = kh->duaDon.donGia = kh->giatLa.donGia = kh->trongTre.donGia = 0;

    printf("Thanh toan thanh cong va reset thong tin khach hang!\n");
}

// main
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
        printf("5. Sua thong tin khach hang\n");
        printf("6. Them dich vu\n");
        printf("7. Xoa dich vu\n");
        printf("8. Hoa don va thanh toan\n");
        printf("9. Thoat\n");
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
                hienThi10PhongMacDinh(danhSach);
                datPhong(danhSach, cccd);
                break;
            }
            case 5:
                suaThongTinKhachHang(danhSach);
                break;
            case 6:
                themDichVu(danhSach);
                break;
            case 7:
                xoaDichVu(danhSach);
                break;
            case 8:
                char cccd[15];
                printf("Nhap CCCD cua khach hang: ");
                nhapChuoi("", cccd, sizeof(cccd));
                hienThiHoaDon(danhSach, cccd);
                break;
            case 9:
                printf("Thoat chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 10);

    return 0;
}

