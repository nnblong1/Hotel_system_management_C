#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

// Struct thông tin Phòng
 struct Phong {
    int maPhong;
    char kieuPhong[20];
    int sogiuong;
    char thongTinPhong[50];
    char tinhtrang[10]; // Trống, đã thuê
    float giaThue;
    struct DoNoiThat *danhSachDoNoiThat; // Danh sách liên kết đồ nội thất
    struct Phong *next;
} Phong[10];

// Struct thông tin Khách hàng
typedef struct KhachHang {
    char ten[50];
    int namSinh;
    int cccd;
    char gioiTinh[10];
    char soDienThoai[15];
    char queQuan[50];
    
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
    char tinhTrang[20]; // "Tốt", "Hỏng"
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

// // Hàm thêm phòng vào danh sách phòng
// void themPhong(Phong **head) {
//     Phong *newPhong = (Phong *)malloc(sizeof(Phong));
//     printf("Nhap ma phong: ");
//     scanf("%s", newPhong->maPhong);
//     printf("Nhap kieu phong: ");
//     scanf(" %[^\n]", newPhong->kieuPhong);
//     printf("Nhap so giuong: ");
//     scanf("%d", &newPhong->sogiuong);
//     printf("Nhap thong tin phong: ");
//     scanf(" %[^\n]", newPhong->thongTinPhong);
//     printf("Nhap tinh trang phong (Trong/Da thue): ");
//     scanf(" %[^\n]", newPhong->tinhTrang);
//     printf("Nhap gia thue: ");
//     scanf("%f", &newPhong->giaThue);
//     newPhong->next = *head;
//     *head = newPhong;
// }

// // Hàm tìm phòng theo mã phòng
// Phong *timPhong(int maPhong) {
//     KhachSan *ks = danhSachKhachSan;
//     while (ks != NULL) {
//         Phong *ph = ks->danhSachPhong;
//         while (ph != NULL) {
//             if (strcmp(ph->maPhong, maPhong) == 0) {
//                 return ph;
//             }
//             ph = ph->next;
//         }
//         ks = ks->next;
//     }
//     return NULL;
// }
// // Hàm hiển thị toàn bộ thông tin khách sạn và các phòng
// void hienThiThongTinKhachSan() {
//     if (danhSachKhachSan == NULL) {
//         printf("Chua co khach san nao trong danh sach!\n");
//         return;
//     }

//     int sttKhachSan = 1;
//     KhachSan *ks = danhSachKhachSan;
//     while (ks != NULL) {
//         printf("\nKhach san %d: %s\n", sttKhachSan++, ks->tenKhachSan);
//         printf("Dia chi: %s\n", ks->diaChi);
//         printf("\nDanh sach phong:\n");
//         printf("STT\tMa phong\tKieu phong\tThong tin phong\t\tTinh trang\tGia thue\n");

//         Phong *ph = ks->danhSachPhong;
//         int sttPhong = 1;
//         while (ph != NULL) {
//             printf("%d\t%s\t\t%s\t\t%s\t%s\t%.2f\n",
//                    sttPhong++, ph->maPhong, ph->kieuPhong, ph->thongTinPhong, ph->tinhTrang, ph->giaThue);
//             ph = ph->next;
//         }
//         ks = ks->next;
//     }
// }

// Hàm đặt phòng nghỉ
// void datPhong() {
//     char cccd[20], maPhong[10], ngayThue[15];
//     printf("Nhap so CCCD cua khach hang: ");
//     scanf("%s", cccd);

//     // Kiểm tra khách hàng đã tồn tại
//     KhachHang *kh = danhSachKhachHang;
//     while (kh != NULL) {
//         if (kh->cccd==cccd ) {
//             printf("Khach hang da ton tai!\n");
//             break;
//         }
//         kh = kh->next;
//     }
//     if (kh == NULL) {
//         // Thêm khách hàng mới
//         kh = (KhachHang *)malloc(sizeof(KhachHang));
//         printf("Nhap ten khach hang: ");
//         scanf(" %[^\n]", kh->ten);
//         printf("Nhap nam sinh: ");
//         scanf("%d", &kh->namSinh);
//         printf("Nhap gioi tinh: ");
//         scanf(" %[^\n]", kh->gioiTinh);
//         printf("Nhap so dien thoai: ");
//         scanf(" %[^\n]", kh->soDienThoai);
//         printf("Nhap que quan: ");
//         scanf(" %[^\n]", kh->queQuan);
//         printf("Nhap so CCCD: ");
//         scanf("%s", cccd);
//         kh->next = danhSachKhachHang;
//         danhSachKhachHang = kh;
//     }

//     // // Nhập mã phòng và ngày thuê
//     // printf("Nhap ma phong can dat: ");
//     // scanf("%d", maPhong);
//     // Phong *ph = timPhong(maPhong);
//     // if (ph == NULL) {
//     //     printf("Phong khong ton tai!\n");
//     //     return;
//     // }
//     // if (ph->tinhTrang == 0) {
//     //     printf("Phong da duoc thue!\n");
//     //     return;
//     // }
//     // ph->tinhTrang = 0;
//     // strcpy(kh->maPhong, maPhong);
//     // printf("Nhap ngay thue (dd/mm/yyyy): ");
//     // scanf("%s", ngayThue);
//     // strcpy(kh->ngayThue, ngayThue);
//     // printf("Dat phong thanh cong!\n");

//     // Thêm vào danh sách khách hàng đã đặt phòng
//     KhachHangDaDat *khachHangDaDat = (KhachHangDaDat *)malloc(sizeof(KhachHangDaDat));
//     khachHangDaDat->phong = ph;
//     khachHangDaDat->khachHang = kh;
//     khachHangDaDat->next = danhSachKhachHangDaDat;
//     danhSachKhachHangDaDat = khachHangDaDat;
// }
// hàm xóa khách hàng khỏi danh sách khách hàng đã đặt
void xoaKhachHang(KhachHang *kh) {
    KhachHangDaDat *prev = NULL, *current = danhSachKhachHangDaDat;
    while (current != NULL) {
        if (current->khachHang == kh) {
            if (prev == NULL) {
                danhSachKhachHangDaDat = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}
// // Hàm tìm phòng trống
// void timPhongTrong() {
//     int found = 0;
//     KhachSan *ks = danhSachKhachSan;
//     while (ks != NULL) {
//         Phong *ph = ks->danhSachPhong;
//         while (ph != NULL) {
//             if (strcmp(ph->tinhTrang, "Trong") == 0) {
//                 if (!found) {
//                     printf("Danh sach phong trong:\n");
//                     printf("Ma phong\tKieu phong\tThong tin phong\t\tGia thue\n");
//                     found = 1;
//                 }
//                 printf("%s\t\t%s\t\t%s\t%.2f\n", ph->maPhong, ph->kieuPhong, ph->thongTinPhong, ph->giaThue);
//             }
//             ph = ph->next;
//         }
//         ks = ks->next;
//     }
//     if (!found) {
//         printf("Khong co phong trong nao!\n");
//     }
// }
// hàm tìm khách hàng theo CCCD
KhachHang * timKhachHang(int cccd) {
    KhachHang *kh = danhSachKhachHang;
    while (kh != NULL) {
        if (kh->cccd == cccd) {
            return kh;
        }
        kh = kh->next;
    }
    return NULL;
}

// Hàm hiển thị thông tin khách hàng
void hienThiKhachHang(int cccd) {
    KhachHang *kh = danhSachKhachHang;
    kh = timKhachHang(cccd);
    if (kh == NULL) {
        printf("Khong tim thay khach hang!\n");
        return;
    }
    else{
    printf("Thong tin khach hang:\n");
    printf("Ten: %s\n", kh->ten);
    printf("Nam sinh: %d\n", kh->namSinh);
    printf("Gioi tinh: %s\n", kh->gioiTinh);
    printf("So dien thoai: %s\n", kh->soDienThoai);
    printf("Que quan: %s\n", kh->queQuan);
    printf("Ma phong: %s\n", kh->maPhong);
    printf("Ngay thue: %s\n", kh->ngayThue);
}
}
// Hàm nhập ID khách hàng muốn checkout, trả phòng và thanh toán
void ChonKHcheckout(KhachHangDaDat *KhachHang) {  
    if (KhachHang == NULL) {
        printf("Khách hàng không tồn tại!\n");
        return;
    }
    KhachHangDaDat *khachHangCheckout = KhachHang;
    int id;
    printf("Nhập ID khách hàng cần checkout: ");
    scanf("%d", &id);
    khachHangCheckout = timKhachHang(id); 
    if (khachHangCheckout == NULL) {
        printf("Không tìm thấy khách hàng với ID:  %d\n", id);
        return;
    }
// hàm thanh toán tiền phòng
void ThanhToanTienPhong(int cccd) {

    printf("Thanh toán tiền phòng cho KH: ");
    timKhachHang(cccd);
    KhachHangDaDat *kh = timKhachHang(cccd);  
    if (kh == NULL) {
        printf("Không tìm thấy khách hàng với ID:  %d\n", cccd);
        return;
    }
        // Tìm khách hàng dựa vào CCCD
        if (kh->khachHang->cccd == cccd) {

            // Nhập ngày trả phòng
            char ngayTra[15];
            printf("Nhập ngày trả phòng (dd/mm/yyyy): ");
            scanf("%s", ngayTra);

            // Tính toán số ngày thuê phòng
            struct tm tmThue = {0}, tmTra = {0};
            strptime(kh->khachHang->ngayThue, "%d/%m/%Y", &tmThue);
            strptime(ngayTra, "%d/%m/%Y", &tmTra);

            time_t tThue = mktime(&tmThue);
            time_t tTra = mktime(&tmTra);

            if (tTra < tThue) {
                printf("Lỗi: Ngày trả phòng không hợp lệ.\n");
                return;
            }

            double soNgayThue = difftime(tTra, tThue) / (60 * 60 * 24);
            switch (kh->khachHang->maPhong) {
                    case 101:
                        kh->khachHang->tienPhong = stay * 100000;
                        phong->tinhTrang = "Trong";
                        break;
                    case 102:
                        kh->khachHang->tienPhong = stay * 100000;
                        phong->tinhTrang = "Trong";
                        break;
                    case 103:
                        kh->khachHang->tienPhong = stay * 100000;
                        phong->tinhTrang = "Trong";
                        break;
                    case 104:
                        kh->khachHang->tienPhong = stay * 100000;
                        phong->tinhTrang = "Trong";
                        break;
                    case 105:
                        kh->khachHang->tienPhong = stay * 100000;
                        phong->tinhTrang = "Trong";
                        break;
                    case 106:
                        kh->khachHang->tienPhong = stay * 100000;
                        phong->tinhTrang = "Trong";
                        break;
                    case 107:           
                        kh->khachHang->tienPhong = stay * 100000;
                        phong->tinhTrang = "Trong";
                        break;
                    case 108:
                        kh->khachHang->tienPhong = stay * 100000;
                        phong->tinhTrang = "Trong";
                        break;
                    case 109:
                        kh->khachHang->tienPhong = stay * 100000;
                        phong->tinhTrang = "Trong";
                        break;
                    case 110:
                        kh->khachHang->tienPhong = stay * 100000;
                        phong->tinhTrang = "Trong";
                        break;
                    default:
                }
            float tongTien = soNgayThue * current->phong->giaThue;

            printf("Số ngày ở: %.0f\n", soNgayThue);
            printf("Tiền phòng phải thanh toán: %.2f\n", tongTien);
            xoaKhachHang(kh);
            printf("Check-out thành công!\n");
            return;
        }

    printf("Khách hàng không tồn tại trong danh sách!\n");
}


// Hàm liệt kê đồ nội thất của phòng
void lietKeDoNoiThat(Phong *phong) {
    if (phong == NULL) {
        printf("Phòng không tồn tại!\n");
        return;
    }

    printf("Danh sách đồ nội thất của phòng mã %d:\n", phong->maPhong);
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

    printf("Kiểm tra tình trạng đồ nội thất của phòng mã %d:\n", phong->maPhong);
    ChiTietPhong(phong);
    DoNoiThat *doNoiThat = phong->danhSachDoNoiThat;
       
    bool coVanDe = false;
    float Tien = 0;
    while (doNoiThat != NULL) {
        if (strcmp(doNoiThat->tinhTrang, "Hỏng") == 0 ) {
            printf("- %s (Tình trạng: %s)\n", doNoiThat->tenDo, doNoiThat->tinhTrang);
            coVanDe = true;
            Tien += 100000;
        }
            switch (doNoiThat->tinhTrang)
            {
            case "Hỏng":
                if(phong->DanhSachDoNoiThat->loaiDo == "TuLanh"){
                    printf("TuLanh hong");
                    Tien = Tien + 100000;
                }
                if(phong->DanhSachDoNoiThat->loaiDo == "Tivi"){
                    printf("Tivi hong");
                    Tien = Tien + 100000;
                }
                if(phong->DanhSachDoNoiThat->loaiDo == "BanTrangDiem"){
                    printf("BanTrangDiem hong");
                    Tien = Tien + 100000;
                }
                if(phong->DanhSachDoNoiThat->loaiDo == "BonCau"){
                    printf("BonCau hong");
                    Tien = Tien + 100000;
                }
                if(phong->DanhSachDoNoiThat->loaiDo == "Lavabo"){
                    printf("Lavabo hong");
                    Tien = Tien + 100000;
                }
                if(phong->DanhSachDoNoiThat->loaiDo == "GuongNhaTam"){
                    printf("GuongNhaTam hong");
                    Tien = Tien + 100000;
                }
                if(phong->DanhSachDoNoiThat->loaiDo == "Giuong"){
                    printf("Giuong hong");
                    Tien = Tien + 100000;
                }
                if(phong->DanhSachDoNoiThat->loaiDo == "TuQuanAo"){
                    printf("TuQuanAo hong");
                    Tien = Tien + 100000;
                }
                if(phong->DanhSachDoNoiThat->loaiDo == "DepDiTrongNha"){
                    printf("DepDiTrongNha hong");
                    Tien = Tien + 100000;
                }

                break;
                default:
                break;
            }
            }
        doNoiThat = doNoiThat->next;
    }

    if (!coVanDe) {
        printf("Tất cả đồ nội thất trong phòng đều ở tình trạng tốt.\n");
    } else {
        printf("Tổng số tiền bồi thường là: %.2f\n", Tien);
    }
}


// hàm thông tin chi tiết về từng phòng
void ChiTietPhong(void) {
    
    for (int i = 0; i < 10; i++) {
        Phong[i].maPhong = 101 + 1 * i;
    }
    strcpy(Phong[0].kieuPhong,"Tieu Chuan   ");
    strcpy(Phong[1].kieuPhong,"Tieu Chuan   ");
    strcpy(Phong[2].kieuPhong,"Tieu Chuan   ");
    strcpy(Phong[3].kieuPhong,"Vip 1  ");
    strcpy(Phong[4].kieuPhong,"Vip 1  ");    strcpy(Phong[5].kieuPhong,"Vip 1  ");
    strcpy(Phong[6].kieuPhong,"Vip 1  ");
    strcpy(Phong[7].kieuPhong,"vip 2   ");
    strcpy(Phong[8].kieuPhong,"vip 2   ");
    strcpy(Phong[9].kieuPhong,"vip promax   ");
    float giaThue[10] = {1000000, 1000000, 1000000, 2000000, 2000000, 2000000, 2000000, 3000000, 3000000, 3000000};
    for (int i = 0; i < 10; i++) {
        Phong[i].giaThue = giaThue[i];
    }
    for (int i = 0; i < 10; i++) {
        Phong[i].danhSachDoNoiThat = (DoNoiThat *)malloc(sizeof(DoNoiThat));
        strcpy(Phong[i].danhSachDoNoiThat->tenDo, "TuLanh");
        Phong[i].danhSachDoNoiThat->next = (DoNoiThat *)malloc(sizeof(DoNoiThat));
        strcpy(Phong[i].danhSachDoNoiThat->next->tenDo, "Tivi");
        Phong[i].danhSachDoNoiThat->next->next = (DoNoiThat *)malloc(sizeof(DoNoiThat));
        strcpy(Phong[i].danhSachDoNoiThat->next->next->tenDo, "BanTrangDiem");
        Phong[i].danhSachDoNoiThat->next->next->next = (DoNoiThat *)malloc(sizeof(DoNoiThat));
        strcpy(Phong[i].danhSachDoNoiThat->next->next->next->tenDo, "BonCau");
        Phong[i].danhSachDoNoiThat->next->next->next->next = (DoNoiThat *)malloc(sizeof(DoNoiThat));
        strcpy(Phong[i].danhSachDoNoiThat->next->next->next->next->tenDo, "Lavabo");
        Phong[i].danhSachDoNoiThat->next->next->next->next->next = (DoNoiThat *)malloc(sizeof(DoNoiThat));
        strcpy(Phong[i].danhSachDoNoiThat->next->next->next->next->next->tenDo, "GuongNhaTam");
        Phong[i].danhSachDoNoiThat->next->next->next->next->next->next = (DoNoiThat *)malloc(sizeof(DoNoiThat));
        strcpy(Phong[i].danhSachDoNoiThat->next->next->next->next->next->next->tenDo, "Giuong");
        Phong[i].danhSachDoNoiThat->next->next->next->next->next->next->next = (DoNoiThat *)malloc(sizeof(DoNoiThat));
        strcpy(Phong[i].danhSachDoNoiThat->next->next->next->next->next->next->next->tenDo, "TuQuanAo");
        Phong[i].danhSachDoNoiThat->next->next->next->next->next->next->next->next = (DoNoiThat *)malloc(sizeof(DoNoiThat));
        strcpy(Phong[i].danhSachDoNoiThat->next->next->next->next->next->next->next->next->tenDo, "DepDiTrongNha");
    }

 }
