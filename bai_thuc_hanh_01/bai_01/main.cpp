#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Xe {
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int thoiGianDo;
    double phiDoXe;
    bool dangChiemCho;

public:
    Xe() {
        maXe = 0;
        loaiXe = "";
        gioVao = 0;
        thoiGianDo = 0;
        phiDoXe = 0.0;
        dangChiemCho = false;
    }

    Xe(int ma, string loai, int gio, int thoiLuong) {
        maXe = ma;
        loaiXe = chuanHoaLoaiXe(loai);
        gioVao = gio;
        thoiGianDo = thoiLuong;
        dangChiemCho = true;
        tinhPhiDoXe();
    }

    int layMaXe() { return maXe; }
    string layLoaiXe() { return loaiXe; }
    int layGioVao() { return gioVao; }
    int layThoiGianDo() { return thoiGianDo; }
    double layPhiDoXe() { return phiDoXe; }
    bool layDangChiemCho() { return dangChiemCho; }

    void ganMaXe(int ma) { maXe = ma; }
    void ganLoaiXe(string loai) { 
        loaiXe = chuanHoaLoaiXe(loai); 
        tinhPhiDoXe();
    }
    void ganGioVao(int gio) { 
        gioVao = gio; 
        tinhPhiDoXe();
    }
    void ganThoiLuongDo(int thoiLuong) { 
        thoiGianDo = thoiLuong; 
        tinhPhiDoXe();
    }
    void ganPhiDoXe(double phi) { phiDoXe = phi; }
    void ganDangChiemCho(bool trangThai) { dangChiemCho = trangThai; }

    static string chuanHoaLoaiXe(string loai) {
        string s = loai;
        for (int i = 0; i < s.length(); i++) {
            s[i] = tolower(s[i]);
        }
        if (s == "car") return "Car";
        if (s == "motorcycle") return "Motorcycle";
        if (s == "bicycle") return "Bicycle";
        return "";
    }

    static bool laLoaiXeHopLe(string loai) {
        string s = chuanHoaLoaiXe(loai);
        return (s == "Car" || s == "Motorcycle" || s == "Bicycle");
    }

    void tinhPhiDoXe() {
        if (loaiXe == "") {
            phiDoXe = 0;
            return;
        }

        double donGia = 0;
        if (loaiXe == "Car") donGia = 6.0;
        else if (loaiXe == "Motorcycle") donGia = 4.0;
        else if (loaiXe == "Bicycle") donGia = 2.0;

        bool gioCaoDiem = (gioVao >= 6 && gioVao <= 9) || (gioVao >= 15 && gioVao <= 18);

        double heSo2GioDau = 0.95;
        if (gioCaoDiem) {
            heSo2GioDau = 1.30;
        }

        int gioDau = thoiGianDo;
        int gioSau = 0;
        if (thoiGianDo > 2) {
            gioDau = 2;
            gioSau = thoiGianDo - 2;
        }

        phiDoXe = (gioDau * donGia * heSo2GioDau) + (gioSau * donGia * 0.90);
    }

    void hienThi() {
        if (!dangChiemCho) return;
        cout << "   Ma xe: " << maXe 
             << " | Loai xe: " << loaiXe 
             << " | Gio vao: " << gioVao
             << " | Thoi gian do: " << thoiGianDo
             << " | Phi do: " << fixed << setprecision(2) << phiDoXe << " VNĐ" << endl;
    }
};

class BaiDoXe {
private:
    int maBai;
    char kichThuoc;
    Xe xe1, xe2, xe3;
    bool coXe1, coXe2, coXe3;

public:
    BaiDoXe() {
        maBai = 0;
        kichThuoc = 'S';
        coXe1 = false;
        coXe2 = false;
        coXe3 = false;
    }

    BaiDoXe(int ma, char size) {
        maBai = ma;
        kichThuoc = toupper(size);
        coXe1 = false;
        coXe2 = false;
        coXe3 = false;
    }

    int layMaBai() { return maBai; }
    char layKichThuoc() { return kichThuoc; }

    int laySucChua() {
        if (kichThuoc == 'S') return 1;
        if (kichThuoc == 'M') return 2;
        if (kichThuoc == 'L') return 3;
        return 0;
    }

    int demXe() {
        int dem = 0;
        if (coXe1) dem++;
        if (coXe2) dem++;
        if (coXe3) dem++;
        return dem;
    }

    bool themXe(Xe v) {
        int sucChua = laySucChua();

        if (!coXe1 && sucChua >= 1) {
            xe1 = v;
            xe1.ganDangChiemCho(true);
            coXe1 = true;
            return true;
        }
        if (!coXe2 && sucChua >= 2) {
            xe2 = v;
            xe2.ganDangChiemCho(true);
            coXe2 = true;
            return true;
        }
        if (!coXe3 && sucChua >= 3) {
            xe3 = v;
            xe3.ganDangChiemCho(true);
            coXe3 = true;
            return true;
        }
        return false;
    }

    bool xoaXe(int vID) {
        if (coXe1 && xe1.layMaXe() == vID) {
            coXe1 = false;
            xe1.ganDangChiemCho(false);
            return true;
        }
        if (coXe2 && xe2.layMaXe() == vID) {
            coXe2 = false;
            xe2.ganDangChiemCho(false);
            return true;
        }
        if (coXe3 && xe3.layMaXe() == vID) {
            coXe3 = false;
            xe3.ganDangChiemCho(false);
            return true;
        }
        return false;
    }

    bool coXeVoiMa(int vID) {
        if (coXe1 && xe1.layMaXe() == vID) return true;
        if (coXe2 && xe2.layMaXe() == vID) return true;
        if (coXe3 && xe3.layMaXe() == vID) return true;
        return false;
    }

    void hienThiThongTinBai() {
        cout << "Bai ID: " << maBai 
             << " | Kich thuoc: " << kichThuoc 
             << " | So xe hien tai: " << demXe() << "/" << laySucChua() << endl;
        if (coXe1) xe1.hienThi();
        if (coXe2) xe2.hienThi();
        if (coXe3) xe3.hienThi();
    }

    int hienThiXeTheoLoai(string loai) {
        int dem = 0;
        if (coXe1 && xe1.layLoaiXe() == loai) {
            cout << "Bai " << maBai << ":";
            xe1.hienThi();
            dem++;
        }
        if (coXe2 && xe2.layLoaiXe() == loai) {
            cout << "Bai " << maBai << ":";
            xe2.hienThi();
            dem++;
        }
        if (coXe3 && xe3.layLoaiXe() == loai) {
            cout << "Bai " << maBai << ":";
            xe3.hienThi();
            dem++;
        }
        return dem;
    }

    int demXeTheoLoai(string loai) {
        int dem = 0;
        if (coXe1 && xe1.layLoaiXe() == loai) dem++;
        if (coXe2 && xe2.layLoaiXe() == loai) dem++;
        if (coXe3 && xe3.layLoaiXe() == loai) dem++;
        return dem;
    }

    double tongPhiTheoLoai(string loai) {
        double tong = 0;
        if (coXe1 && xe1.layLoaiXe() == loai) tong += xe1.layPhiDoXe();
        if (coXe2 && xe2.layLoaiXe() == loai) tong += xe2.layPhiDoXe();
        if (coXe3 && xe3.layLoaiXe() == loai) tong += xe3.layPhiDoXe();
        return tong;
    }
};

class GiaoDien {
private:
    BaiDoXe baiDo1, baiDo2, baiDo3;
    bool coBai1, coBai2, coBai3;

    BaiDoXe& layBai(int vt) {
        if (vt == 1) return baiDo1;
        if (vt == 2) return baiDo2;
        return baiDo3;
    }

    bool coBai(int vt) {
        if (vt == 1) return coBai1;
        if (vt == 2) return coBai2;
        return coBai3;
    }

    int timBaiTheoMa(int maBai) {
        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt) && layBai(vt).layMaBai() == maBai) return vt;
        }
        return 0;
    }

    bool xeDaTonTai(int maXe) {
        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt) && layBai(vt).coXeVoiMa(maXe)) return true;
        }
        return false;
    }

    void taoBaiMoi() {
        int vt = 0;
        if (!coBai1) vt = 1;
        else if (!coBai2) vt = 2;
        else if (!coBai3) vt = 3;

        if (vt == 0) {
            cout << "Da co du 3 bai do xe, khong tao them duoc!" << endl;
            return;
        }

        int ma;
        cout << "Nhap parkID: ";
        cin >> ma;

        if (timBaiTheoMa(ma) != 0) {
            cout << "parkID da ton tai!" << endl;
            return;
        }

        char size;
        cout << "Nhap size (S/M/L): ";
        cin >> size;
        size = toupper(size);

        if (size != 'S' && size != 'M' && size != 'L') {
            cout << "Kich thuoc khong hop le!" << endl;
            return;
        }

        layBai(vt) = BaiDoXe(ma, size);
        if (vt == 1) coBai1 = true;
        else if (vt == 2) coBai2 = true;
        else if (vt == 3) coBai3 = true;

        cout << "Tao bai do xe thanh cong!" << endl;
    }

    void themXeVaoBai() {
        int ma;
        cout << "Nhap vehicleID: ";
        cin >> ma;

        if (xeDaTonTai(ma)) {
            cout << "vehicleID da ton tai trong he thong!" << endl;
            return;
        }

        string loai;
        cout << "Nhap vehicleType (Car/Motorcycle/Bicycle): ";
        cin >> loai;

        if (!Xe::laLoaiXeHopLe(loai)) {
            cout << "Loai xe khong hop le!" << endl;
            return;
        }

        int gio;
        cout << "Nhap entryTime (0-23): ";
        cin >> gio;

        if (gio < 0 || gio > 23) {
            cout << "Gio vao khong hop le!" << endl;
            return;
        }

        int thoiLuong;
        cout << "Nhap parkingDuration (1-23): ";
        cin >> thoiLuong;

        if (thoiLuong < 1 || thoiLuong > 23) {
            cout << "Thoi gian do khong hop le!" << endl;
            return;
        }

        Xe xeMoi(ma, loai, gio, thoiLuong);

        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt) && layBai(vt).themXe(xeMoi)) {
                cout << "Da xep xe vao Bai " << layBai(vt).layMaBai() << endl;
                cout << "Phi do xe: " << fixed << setprecision(2) << xeMoi.layPhiDoXe() << " VNĐ" << endl;
                return;
            }
        }
        cout << "Khong con bai do xe nao hop le hoac con vi tri trong!" << endl;
    }

    void xoaBai() {
        int ma;
        cout << "Nhap parkID can xoa: ";
        cin >> ma;

        int vt = timBaiTheoMa(ma);
        if (vt == 0) {
            cout << "Khong tim thay bai do xe!" << endl;
            return;
        }

        if (vt == 1) coBai1 = false;
        else if (vt == 2) coBai2 = false;
        else if (vt == 3) coBai3 = false;

        cout << "Da xoa bai do xe!" << endl;
    }

    void layXeRa() {
        int ma;
        cout << "Nhap vehicleID can lay ra: ";
        cin >> ma;

        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt) && layBai(vt).xoaXe(ma)) {
                cout << "Da lay xe " << ma << " ra khoi bai " << layBai(vt).layMaBai() << endl;
                return;
            }
        }
        cout << "Khong tim thay xe trong he thong!" << endl;
    }

    void hienThiTatCaBai() {
        if (!coBai1 && !coBai2 && !coBai3) {
            cout << "Chua co bai do xe nao!" << endl;
            return;
        }

        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt)) {
                cout << "Bai ID: " << layBai(vt).layMaBai()
                     << " | Kich thuoc: " << layBai(vt).layKichThuoc()
                     << " | So xe: " << layBai(vt).demXe() << "/" << layBai(vt).laySucChua() << endl;
            }
        }
    }

    void hienThiXeTheoBai() {
        int ma;
        cout << "Nhap parkID: ";
        cin >> ma;

        int vt = timBaiTheoMa(ma);
        if (vt == 0) {
            cout << "Khong tim thay bai do xe!" << endl;
            return;
        }

        layBai(vt).hienThiThongTinBai();
    }

    void lietKeTheoLoai() {
        string loai;
        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
        cin >> loai;

        loai = Xe::chuanHoaLoaiXe(loai);
        if (loai == "") {
            cout << "Loai xe khong hop le!" << endl;
            return;
        }

        int tongXe = 0;
        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt)) {
                tongXe += layBai(vt).hienThiXeTheoLoai(loai);
            }
        }

        if (tongXe == 0) {
            cout << "Khong co xe nao thuoc loai nay!" << endl;
        }
    }

    void baoCaoMotLoai(string loai) {
        int tongSoXe = 0;
        double tongPhi = 0;

        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt)) {
                tongSoXe += layBai(vt).demXeTheoLoai(loai);
                tongPhi += layBai(vt).tongPhiTheoLoai(loai);
            }
        }

        cout << loai << ":" << endl;
        if (tongSoXe == 0) {
            cout << "  - Phi trung binh toan he thong: Chua co xe" << endl;
        } else {
            cout << "  - Phi trung binh toan he thong = " << fixed << setprecision(2) << (tongPhi / tongSoXe) << endl;
        }

        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt)) {
                int n = layBai(vt).demXeTheoLoai(loai);
                cout << "    + Bai " << layBai(vt).layMaBai() << ": ";
                if (n == 0) {
                    cout << "Khong co xe" << endl;
                } else {
                    cout << fixed << setprecision(2) << (layBai(vt).tongPhiTheoLoai(loai) / n) << endl;
                }
            }
        }
    }

    void baoCaoPhi() {
        cout << "--- BÁO CÁO PHÍ ĐỖ XE TRUNG BÌNH ---" << endl;
        baoCaoMotLoai("Car");
        baoCaoMotLoai("Motorcycle");
        baoCaoMotLoai("Bicycle");
    }

public:
    GiaoDien() {
        coBai1 = false;
        coBai2 = false;
        coBai3 = false;
    }

    void runMenu() {
        int chon = 0;
        do {
            cout << endl;
            cout << "===== QUAN LY BAI DO XE =====" << endl;
            cout << "1. Tao bai do xe moi" << endl;
            cout << "2. Them xe vao bai do" << endl;
            cout << "3. Xoa mot bai do xe" << endl;
            cout << "4. Lay xe ra khoi bai do" << endl;
            cout << "5. Hien thi danh sach tat ca cac bai do" << endl;
            cout << "6. Hien thi danh sach xe theo bai cu the" << endl;
            cout << "7. Liet ke xe theo loai phuong tien" << endl;
            cout << "8. Bao cao phi do xe trung binh" << endl;
            cout << "9. Thoat program" << endl;
            cout << "Nhap lua chon của ban: ";
            cin >> chon;

            if (chon == 1) taoBaiMoi();
            else if (chon == 2) themXeVaoBai();
            else if (chon == 3) xoaBai();
            else if (chon == 4) layXeRa();
            else if (chon == 5) hienThiTatCaBai();
            else if (chon == 6) hienThiXeTheoBai();
            else if (chon == 7) lietKeTheoLoai();
            else if (chon == 8) baoCaoPhi();
            else if (chon == 9) cout << "Thoat chuong trinh!" << endl;
            else cout << "Lua chon khong hop le!" << endl;

        } while (chon != 9);
    }
};

int main() {
    GiaoDien app;
    app.runMenu();
    return 0;
}
