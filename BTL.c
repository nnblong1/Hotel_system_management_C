#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

// Struct thông tin Phòng
 struct Phong {
    int maPhong[10];
    char kieuPhong[20];
    int sogiuong;
    char thongTinPhong[50];
    char tinhtrang[10]; // Trống, đã thuê
    float giaThue;
    DoNoiThat *danhSachDoNoiThat; // Danh sách liên kết đồ nội thất
    struct Phong *next;
} Phong[10];

// Struct thông tin Khách hàng
typedef struct KhachHang {
    char ten[50];
    int namSinh;
    char cccd[20];
    char gioiTinh[10];
    char soDienThoai[15];
    char queQuan[50];
    char maPhong[10];
    char ngayThue[15];
    struct KhachHang *next;
} KhachHang;

// struct thông tin khách hàng đã đặt phòng nào
typedef struct {
    struct Phong *phong;
    struct KhachHang *khachHang;
    struct KhachHangDaDat *next;
} KhachHangDaDat;

// struct thông tin dịch vụ
typedef struct DichVu {
    char tenDichVu[50];
    int soLuong;
    float donGia;
    struct DichVu *next;
} DichVu;

// Cấu trúc đồ nội thất
typedef struct DoNoiThat {
    char tenDo[50];
    char tinhTrang[20]; // "Tốt", "Hỏng", "Cần sửa chữa"
    struct DoNoiThat *next;
} DoNoiThat;

// danh sách liên kết chính
DichVu *danhSachDichVu = NULL;
KhachHangDaDat *danhSachKhachHangDaDat = NULL;
KhachHang *danhSachKhachHang = NULL;

//header
void header(void){
	printf("\n" );
	printf("\n" );


	printf("            ________________________________________________________________________\n");

	printf("            ________________________________________________________________________\n");

	printf("            **********             Hotel Management System             ************\n" );

	printf("            ________________________________________________________________________\n");

	printf("            ________________________________________________________________________\n");


	printf("\n" );
	printf("\n" );

}

// Hàm thêm phòng vào danh sách phòng
void themPhong(Phong **head) {
    Phong *newPhong = (Phong *)malloc(sizeof(Phong));
    printf("Nhap ma phong: ");
    scanf("%s", newPhong->maPhong);
    printf("Nhap kieu phong: ");
    scanf(" %[^\n]", newPhong->kieuPhong);
    printf("Nhap so giuong: ");
    scanf("%d", &newPhong->sogiuong);
    printf("Nhap thong tin phong: ");
    scanf(" %[^\n]", newPhong->thongTinPhong);
    printf("Nhap tinh trang phong (Trong/Da thue): ");
    scanf(" %[^\n]", newPhong->tinhTrang);
    printf("Nhap gia thue: ");
    scanf("%f", &newPhong->giaThue);
    newPhong->next = *head;
    *head = newPhong;
}

// Hàm tìm phòng theo mã phòng
Phong *timPhong(char maPhong[]) {
    KhachSan *ks = danhSachKhachSan;
    while (ks != NULL) {
        Phong *ph = ks->danhSachPhong;
        while (ph != NULL) {
            if (strcmp(ph->maPhong, maPhong) == 0) {
                return ph;
            }
            ph = ph->next;
        }
        ks = ks->next;
    }
    return NULL;
}
// Hàm hiển thị toàn bộ thông tin khách sạn và các phòng
void hienThiThongTinKhachSan() {
    if (danhSachKhachSan == NULL) {
        printf("Chua co khach san nao trong danh sach!\n");
        return;
    }

    int sttKhachSan = 1;
    KhachSan *ks = danhSachKhachSan;
    while (ks != NULL) {
        printf("\nKhach san %d: %s\n", sttKhachSan++, ks->tenKhachSan);
        printf("Dia chi: %s\n", ks->diaChi);
        printf("\nDanh sach phong:\n");
        printf("STT\tMa phong\tKieu phong\tThong tin phong\t\tTinh trang\tGia thue\n");

        Phong *ph = ks->danhSachPhong;
        int sttPhong = 1;
        while (ph != NULL) {
            printf("%d\t%s\t\t%s\t\t%s\t%s\t%.2f\n",
                   sttPhong++, ph->maPhong, ph->kieuPhong, ph->thongTinPhong, ph->tinhTrang, ph->giaThue);
            ph = ph->next;
        }
        ks = ks->next;
    }
}

// Hàm đặt phòng nghỉ
void datPhong() {
    char cccd[20], maPhong[10], ngayThue[15];
    printf("Nhap so CCCD cua khach hang: ");
    scanf("%s", cccd);

    // Kiểm tra khách hàng đã tồn tại
    KhachHang *kh = danhSachKhachHang;
    while (kh != NULL) {
        if (strcmp(kh->cccd, cccd) == 0) {
            printf("Khach hang da ton tai!\n");
            break;
        }
        kh = kh->next;
    }
    if (kh == NULL) {
        // Thêm khách hàng mới
        kh = (KhachHang *)malloc(sizeof(KhachHang));
        printf("Nhap ten khach hang: ");
        scanf(" %[^\n]", kh->ten);
        printf("Nhap nam sinh: ");
        scanf("%d", &kh->namSinh);
        printf("Nhap gioi tinh: ");
        scanf(" %[^\n]", kh->gioiTinh);
        printf("Nhap so dien thoai: ");
        scanf(" %[^\n]", kh->soDienThoai);
        printf("Nhap que quan: ");
        scanf(" %[^\n]", kh->queQuan);
        strcpy(kh->cccd, cccd);
        kh->next = danhSachKhachHang;
        danhSachKhachHang = kh;
    }

    // Nhập mã phòng và ngày thuê
    printf("Nhap ma phong can dat: ");
    scanf("%s", maPhong);
    Phong *ph = timPhong(maPhong);
    if (ph == NULL) {
        printf("Phong khong ton tai!\n");
        return;
    }
    if (ph->tinhTrang == 0) {
        printf("Phong da duoc thue!\n");
        return;
    }
    ph->tinhTrang = 0;
    strcpy(kh->maPhong, maPhong);
    printf("Nhap ngay thue (dd/mm/yyyy): ");
    scanf("%s", ngayThue);
    strcpy(kh->ngayThue, ngayThue);
    printf("Dat phong thanh cong!\n");

    // Thêm vào danh sách khách hàng đã đặt phòng
    KhachHangDaDat *khachHangDaDat = (KhachHangDaDat *)malloc(sizeof(KhachHangDaDat));
    khachHangDaDat->phong = ph;
    khachHangDaDat->khachHang = kh;
    khachHangDaDat->next = danhSachKhachHangDaDat;
    danhSachKhachHangDaDat = khachHangDaDat;
}
// Hàm tìm phòng trống
void timPhongTrong() {
    int found = 0;
    KhachSan *ks = danhSachKhachSan;
    while (ks != NULL) {
        Phong *ph = ks->danhSachPhong;
        while (ph != NULL) {
            if (strcmp(ph->tinhTrang, "Trong") == 0) {
                if (!found) {
                    printf("Danh sach phong trong:\n");
                    printf("Ma phong\tKieu phong\tThong tin phong\t\tGia thue\n");
                    found = 1;
                }
                printf("%s\t\t%s\t\t%s\t%.2f\n", ph->maPhong, ph->kieuPhong, ph->thongTinPhong, ph->giaThue);
            }
            ph = ph->next;
        }
        ks = ks->next;
    }
    if (!found) {
        printf("Khong co phong trong nao!\n");
    }
}
// Hàm hiển thị thông tin khách hàng
void hienThiKhachHang() {
    int luaChon;
    printf("1. Kiem tra thong tin khach hang bang CCCD\n");
    printf("2. Hien thi toan bo danh sach khach hang\n");
    printf("Nhap lua chon: ");
    scanf("%d", &luaChon);

    if (luaChon == 1) {
        char cccd[20];
        printf("Nhap so CCCD: ");
        scanf("%s", cccd);
        KhachHang *kh = danhSachKhachHang;
        while (kh != NULL) {
            if (strcmp(kh->cccd, cccd) == 0) {
                printf("Thong tin khach hang:\n");
                printf("Ten: %s\n", kh->ten);
                printf("Nam sinh: %d\n", kh->namSinh);
                printf("CCCD: %s\n", kh->cccd);
                printf("Gioi tinh: %s\n", kh->gioiTinh);
                printf("So dien thoai: %s\n", kh->soDienThoai);
                printf("Que quan: %s\n", kh->queQuan);
                printf("Phong: %s\n", kh->maPhong);
                printf("Ngay vao: %s\n", kh->ngayThue);
                return;
            }
            kh = kh->next;
        }
        printf("Khong tim thay khach hang voi CCCD nay!\n");
    } else if (luaChon == 2) {
        printf("STT\tTen\tNam sinh\tCCCD\t\tGioi tinh\tSo dien thoai\tQue quan\tPhong\tNgay vao\n");
        int stt = 1;
        KhachHang *kh = danhSachKhachHang;
        while (kh != NULL) {
            printf("%d\t%s\t%d\t\t%s\t%s\t%s\t%s\t%s\t%s\n",
                   stt++, kh->ten, kh->namSinh, kh->cccd, kh->gioiTinh,
                   kh->soDienThoai, kh->queQuan, kh->maPhong, kh->ngayThue);
            kh = kh->next;
        }
    } else {
        printf("Lua chon khong hop le!\n");
    }
}


// Hàm nhập ID khách hàng muốn checkout, trả phòng và thanh toán
void ChonKHcheckout(KhachHangDaDat *KhachHang) {
    if (KhachHang == NULL) {
        printf("Khách hàng không tồn tại!\n");
        return;
    }
    char cccd[20];
    printf("Nhập ID khách hàng cần checkout: ");
    scanf("%s", cccd);
    KhachHang *khachHangCheckout = KhachHang;
    while (khachHangCheckout != NULL) {
        if (strcmp(khachHangCheckout->cccd, cccd) == 0) {
            printf("Khách hàng ID %s đang check out\n", cccd);
            return;
        }
        khachHangCheckout = khachHangCheckout->next;
    }
    printf("Không tìm thấy khách hàng với ID:  %s\n", cccd);

// hàm thanh toán tiền phòng
void checkOut(char *cccd) {
    KhachHangDaDat *prev = NULL, *current = danhSachKhachHangDaDat;

    while (current != NULL) {
        // Tìm khách hàng dựa vào CCCD
        if (strcmp(current->khachHang->cccd, cccd) == 0) {
            Phong *phong = current->phong;
            KhachHang *khachHang = current->khachHang;

            printf("Khách hàng: %s\n", khachHang->ten);
            printf("Phòng: %s\n", phong->maPhong);
            printf("Ngày thuê: %s\n", khachHang->ngayThue);

            // Nhập ngày trả phòng
            char ngayTra[15];
            printf("Nhập ngày trả phòng (dd/mm/yyyy): ");
            scanf("%s", ngayTra);

            // Tính toán số ngày thuê phòng
            struct tm tmThue = {0}, tmTra = {0};
            strptime(khachHang->ngayThue, "%d/%m/%Y", &tmThue);
            strptime(ngayTra, "%d/%m/%Y", &tmTra);

            time_t tThue = mktime(&tmThue);
            time_t tTra = mktime(&tmTra);

            if (tTra < tThue) {
                printf("Lỗi: Ngày trả phòng không hợp lệ.\n");
                return;
            }

            double soNgayThue = difftime(tTra, tThue) / (60 * 60 * 24);
            float tongTien = soNgayThue * phong->giaThue;

            printf("Số ngày ở: %.0f\n", soNgayThue);
            printf("Tổng tiền phải thanh toán: %.2f\n", tongTien);

            // Cập nhật tình trạng phòng
            strcpy(phong->tinhtrang, "Trong");

            // Xóa khách hàng khỏi danh sách đã đặt
            if (prev == NULL) {
                danhSachKhachHangDaDat = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);

            printf("Check-out thành công!\n");
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Khách hàng không tồn tại trong danh sách!\n");
}


// Hàm liệt kê đồ nội thất của phòng
void lietKeDoNoiThat(Phong *phong) {
    if (phong == NULL) {
        printf("Phòng không tồn tại!\n");
        return;
    }

    printf("Danh sách đồ nội thất của phòng mã %d:\n", phong->maPhong[0]);
    DoNoiThat *doNoiThat = phong->danhSachDoNoiThat;
    if (doNoiThat == NULL) {
        printf("Phòng chưa có đồ nội thất.\n");
        return;
    }

    while (doNoiThat != NULL) {
        printf("- %s (Tình trạng: %s)\n", doNoiThat->tenDo, doNoiThat->tinhTrang);
        doNoiThat = doNoiThat->next;
    }
}

// Hàm kiểm tra tình trạng đồ nội thất trong phòng
void kiemTraTinhTrangDoNoiThat(Phong *phong) {
    if (phong == NULL) {
        printf("Phòng không tồn tại!\n");
        return;
    }

    printf("Kiểm tra tình trạng đồ nội thất của phòng mã %d:\n", phong->maPhong[]);
    DoNoiThat *doNoiThat = phong->danhSachDoNoiThat;
    if (doNoiThat == NULL) {
        printf("Phòng chưa có đồ nội thất.\n");
        return;
    }
    
    bool coVanDe = false;
    while (doNoiThat != NULL) {
        if (strcmp(doNoiThat->tinhTrang, "Hỏng") == 0 || strcmp(doNoiThat->tinhTrang, "Cần sửa chữa") == 0) {
            printf("- %s có vấn đề (Tình trạng: %s)\n", doNoiThat->tenDo, doNoiThat->tinhTrang);
            coVanDe = true;
        }
        doNoiThat = doNoiThat->next;
    }

    if (!coVanDe) {
        printf("Tất cả đồ nội thất trong phòng đều ở tình trạng tốt.\n");
    }
}

// hàm thông tin chi tiết về từng phòng
void ChiTietPhong(void) {
    
    Phong[0].soPhong=101;
    Phong[1].soPhong=102;
    Phong[2].soPhong=103;
    Phong[3].soPhong=104;
    Phong[4].soPhong=105;
    Phong[5].soPhong=106;
    Phong[6].soPhong=107;
    Phong[7].soPhong=108;
    Phong[8].soPhong=109;
    Phong[9].soPhong=110;

    strcpy(Phong[0].kieuPhong,"Tieu Chuan   ");
    strcpy(Phong[1].kieuPhong,"Tieu Chuan   ");
    strcpy(Phong[2].kieuPhong,"Tieu Chuan   ");
    strcpy(Phong[3].kieuPhong,"Vip 1  ");
    strcpy(Phong[4].kieuPhong,"Vip 1  ");
    strcpy(Phong[5].kieuPhong,"Vip 1  ");
    strcpy(Phong[6].kieuPhong,"Vip 1  ");
    strcpy(Phong[7].kieuPhong,"vip 2   ");
    strcpy(Phong[8].kieuPhong,"vip 2   ");
    strcpy(Phong[9].kieuPhong,"vip promax   ");
    
    
    

    

   

    RI[0].bed=1;
    RI[1].bed=1;
    RI[2].bed=2;
    RI[3].bed=2;
    RI[4].bed=1;
    RI[5].bed=1;
    RI[6].bed=2;
    RI[7].bed=3;
    RI[8].bed=4;
    RI[9].bed=1;

  



typedef struct Phong {
    int maPhong[10];
    char kieuPhong[20];
    int sogiuong;
    char thongTinPhong[50];
    char tinhtrang[10]; // Trống, đã thuê
    float giaThue;
    DoNoiThat *danhSachDoNoiThat; // Danh sách liên kết đồ nội thất
    struct Phong *next;
} Phong;

