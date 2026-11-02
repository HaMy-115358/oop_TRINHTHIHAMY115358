#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

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

    Xe(int ma, const string& loai, int gio, int thoiLuong) {
        maXe = ma;
        loaiXe = chuanHoaLoaiXe(loai);
        gioVao = gio;
        thoiGianDo = thoiLuong;
        dangChiemCho = true;
        tinhPhi();
    }

    int layMaXe() const { return maXe; }
    string layLoaiXe() const { return loaiXe; }
    int layGioVao() const { return gioVao; }
    int layThoiGianDo() const { return thoiGianDo; }
    double layPhiDoXe() const { return phiDoXe; }
    bool layDangChiemCho() const { return dangChiemCho; }

    void ganMaXe(int ma) { maXe = ma; }
    void ganLoaiXe(const string& loai) { 
        loaiXe = chuanHoaLoaiXe(loai); 
        tinhPhi();
    }
    void ganGioVao(int gio) { 
        gioVao = gio; 
        tinhPhi();
    }
    void ganThoiLuongDo(int thoiLuong) { 
        thoiGianDo = thoiLuong; 
        tinhPhi();
    }
    void ganPhiDoXe(double phi) { phiDoXe = phi; }
    void ganDangChiemCho(bool trangThai) { dangChiemCho = trangThai; }

    static string chuanHoaLoaiXe(const string& loai) {
        string s = loai;
        for (size_t i = 0; i < s.length(); i++) {
            s[i] = tolower(s[i]);
        }
        if (s == "car") return "Car";
        if (s == "motorcycle") return "Motorcycle";
        if (s == "bicycle") return "Bicycle";
        return "";
    }

    static bool laLoaiXeHopLe(const string& loai) {
        string s = chuanHoaLoaiXe(loai);
        return (s == "Car" || s == "Motorcycle" || s == "Bicycle");
    }

    void tinhPhi() {
        if (loaiXe == "") {
            phiDoXe = 0.0;
            return;
        }

        double donGiaChuan = 0.0;
        if (loaiXe == "Car") donGiaChuan = 6.0;
        else if (loaiXe == "Motorcycle") donGiaChuan = 4.0;
        else if (loaiXe == "Bicycle") donGiaChuan = 2.0;

        bool laGioCaoDiem = (gioVao >= 6 && gioVao <= 9) || (gioVao >= 15 && gioVao <= 18);

        int gioDau = (thoiGianDo > 2) ? 2 : thoiGianDo;
        int gioSau = (thoiGianDo > 2) ? (thoiGianDo - 2) : 0;

        double heSoGioDau = laGioCaoDiem ? 1.30 : 0.95;
        double phiGioDau = gioDau * donGiaChuan * heSoGioDau;

        double phiGioSau = gioSau * donGiaChuan * 0.90;

        phiDoXe = phiGioDau + phiGioSau;
    }

    void hienThi() const {
        if (!dangChiemCho) return;
        cout << "  [ID Xe: " << maXe 
             << " | Loai: " << loaiXe 
             << " | Gio vao: " << gioVao << "h"
             << " | Thoi gian do: " << thoiGianDo << "h"
             << " | Phi: $" << fixed << setprecision(2) << phiDoXe << "]" << endl;
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
        coXe1 = coXe2 = coXe3 = false;
    }

    BaiDoXe(int ma, char size) {
        maBai = ma;
        kichThuoc = toupper(size);
        coXe1 = coXe2 = coXe3 = false;
    }

    int layMaBai() const { return maBai; }
    char layKichThuoc() const { return kichThuoc; }

    int laySucChua() const {
        if (kichThuoc == 'S') return 1;
        if (kichThuoc == 'M') return 2;
        if (kichThuoc == 'L') return 3;
        return 0;
    }

    int demSoXeHienTai() const {
        int count = 0;
        if (coXe1) count++;
        if (coXe2) count++;
        if (coXe3) count++;
        return count;
    }

    bool themXe(const Xe& v) {
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

    bool coXeVoiMa(int vID) const {
        if (coXe1 && xe1.layMaXe() == vID) return true;
        if (coXe2 && xe2.layMaXe() == vID) return true;
        if (coXe3 && xe3.layMaXe() == vID) return true;
        return false;
    }

    void hienThiThongTinBai() const {
        cout << "Bai ID: " << maBai 
             << " | Kich thuoc: " << kichThuoc 
             << " | So xe hien co: " << demSoXeHienTai() << "/" << laySucChua() << endl;
        if (coXe1) xe1.hienThi();
        if (coXe2) xe2.hienThi();
        if (coXe3) xe3.hienThi();
    }

    int hienThiXeTheoLoai(const string& loai) const {
        int count = 0;
        if (coXe1 && xe1.layLoaiXe() == loai) {
            cout << "Bai ID " << maBai << ":";
            xe1.hienThi();
            count++;
        }
        if (coXe2 && xe2.layLoaiXe() == loai) {
            cout << "Bai ID " << maBai << ":";
            xe2.hienThi();
            count++;
        }
        if (coXe3 && xe3.layLoaiXe() == loai) {
            cout << "Bai ID " << maBai << ":";
            xe3.hienThi();
            count++;
        }
        return count;
    }

    int demXeTheoLoai(const string& loai) const {
        int count = 0;
        if (coXe1 && xe1.layLoaiXe() == loai) count++;
        if (coXe2 && xe2.layLoaiXe() == loai) count++;
        if (coXe3 && xe3.layLoaiXe() == loai) count++;
        return count;
    }

    double tongPhiTheoLoai(const string& loai) const {
        double tong = 0.0;
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

    const BaiDoXe& layBaiConst(int vt) const {
        if (vt == 1) return baiDo1;
        if (vt == 2) return baiDo2;
        return baiDo3;
    }

    bool coBai(int vt) const {
        if (vt == 1) return coBai1;
        if (vt == 2) return coBai2;
        return coBai3;
    }

    int timBaiTheoMa(int maBai) const {
        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt) && layBaiConst(vt).layMaBai() == maBai) return vt;
        }
        return 0;
    }

    bool xeDaTonTai(int maXe) const {
        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt) && layBaiConst(vt).coXeVoiMa(maXe)) return true;
        }
        return false;
    }

    int docSoNguyen(const string& thongBao) {
        int val;
        cout << thongBao;
        while (!(cin >> val)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Du lieu khong hop le. Vui long nhap lai so nguyen: ";
        }
        return val;
    }

    void taoBaiMoi() {
        int vt = 0;
        if (!coBai1) vt = 1;
        else if (!coBai2) vt = 2;
        else if (!coBai3) vt = 3;

        if (vt == 0) {
            cout << "He thong da dat toi da 3 bai do xe!" << endl;
            return;
        }

        int ma = docSoNguyen("Nhap parkID: ");
        if (timBaiTheoMa(ma) != 0) {
            cout << "Loi: parkID da ton tai!" << endl;
            return;
        }

        char size;
        cout << "Nhap size ('S', 'M', 'L'): ";
        cin >> size;
        size = toupper(size);
        if (size != 'S' && size != 'M' && size != 'L') {
            cout << "Loi: Kich thuoc bai do xe khong hop le!" << endl;
            return;
        }

        layBai(vt) = BaiDoXe(ma, size);
        if (vt == 1) coBai1 = true;
        else if (vt == 2) coBai2 = true;
        else if (vt == 3) coBai3 = true;

        cout << "Tao bai do xe thanh cong!" << endl;
    }

    void themXeVaoBai() {
        int ma = docSoNguyen("Nhap vehicleID: ");
        if (xeDaTonTai(ma)) {
            cout << "Loi: vehicleID da ton tai trong he thong!" << endl;
            return;
        }

        string loai;
        cout << "Nhap vehicleType (Car / Motorcycle / Bicycle): ";
        cin >> loai;
        if (!Xe::laLoaiXeHopLe(loai)) {
            cout << "Loi: Loai xe khong hop le!" << endl;
            return;
        }

        int gio = docSoNguyen("Nhap entryTime (0-23): ");
        if (gio < 0 || gio > 23) {
            cout << "Loi: Gio vao phai tu 0 den 23!" << endl;
            return;
        }

        int thoiLuong = docSoNguyen("Nhap parkingDuration (1-23): ");
        if (thoiLuong < 1 || thoiLuong > 23) {
            cout << "Loi: Thoi gian do phai tu 1 den 23 gio!" << endl;
            return;
        }

        Xe xeMoi(ma, loai, gio, thoiLuong);

        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt) && layBai(vt).themXe(xeMoi)) {
                cout << "Da xep xe vao Bai ID " << layBai(vt).layMaBai() << " thanh cong!" << endl;
                cout << "Phi do xe du tinh: $" << fixed << setprecision(2) << xeMoi.layPhiDoXe() << endl;
                return;
            }
        }
        cout << "Loi: Khong con bai do xe nao con vi tri trong!" << endl;
    }

    void xoaBai() {
        int ma = docSoNguyen("Nhap parkID can xoa: ");
        int vt = timBaiTheoMa(ma);
        if (vt == 0) {
            cout << "Loi: Khong tim thay bai do xe voi ID nay!" << endl;
            return;
        }

        if (vt == 1) coBai1 = false;
        else if (vt == 2) coBai2 = false;
        else if (vt == 3) coBai3 = false;

        cout << "Da xoa bai do xe ID " << ma << " ra khoi he thong!" << endl;
    }

    void layXeRa() {
        int ma = docSoNguyen("Nhap vehicleID can lay ra: ");
        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt) && layBai(vt).xoaXe(ma)) {
                cout << "Da lay xe ID " << ma << " ra khoi Bai ID " << layBai(vt).layMaBai() << endl;
                return;
            }
        }
        cout << "Loi: Khong tim thay xe voi vehicleID nay trong he thong!" << endl;
    }

    void hienThiTatCaBai() const {
        if (!coBai1 && !coBai2 && !coBai3) {
            cout << "He thong hien chua co bai do xe nao!" << endl;
            return;
        }
        cout << "\n=== DANH SACH CAC BAI DO XE ===" << endl;
        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt)) {
                const BaiDoXe& bai = layBaiConst(vt);
                cout << "- Bai ID: " << bai.layMaBai()
                     << " | Kich thuoc: " << bai.layKichThuoc()
                     << " | So xe: " << bai.demSoXeHienTai() << "/" << bai.laySucChua() << endl;
            }
        }
    }

    void hienThiXeTheoBai() const {
        int ma = docSoNguyen("Nhap parkID: ");
        int vt = timBaiTheoMa(ma);
        if (vt == 0) {
            cout << "Loi: Khong tim thay bai do xe!" << endl;
            return;
        }
        cout << "\n--- CHITIET ";
        layBaiConst(vt).hienThiThongTinBai();
    }

    void lietKeTheoLoai() const {
        string loai;
        cout << "Nhap loai xe (Car / Motorcycle / Bicycle): ";
        cin >> loai;
        loai = Xe::chuanHoaLoaiXe(loai);
        if (loai == "") {
            cout << "Loi: Loai xe khong hop le!" << endl;
            return;
        }

        cout << "\n=== DANH SACH XE LOAI " << loai << " ===" << endl;
        int tongXe = 0;
        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt)) {
                tongXe += layBaiConst(vt).hienThiXeTheoLoai(loai);
            }
        }
        if (tongXe == 0) {
            cout << "Khong co xe nao thuoc loai nay trong he thong!" << endl;
        }
    }

    void baoCaoMotLoai(const string& loai) const {
        int tongSoXe = 0;
        double tongPhi = 0.0;
        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt)) {
                tongSoXe += layBaiConst(vt).demXeTheoLoai(loai);
                tongPhi += layBaiConst(vt).tongPhiTheoLoai(loai);
            }
        }

        cout << "\n* Loai phuong tien: " << loai << endl;
        if (tongSoXe == 0) {
            cout << "  - Phi trung binh toan he thong: Khong co xe trong he thong" << endl;
            return;
        }
        
        cout << "  - Phi trung binh toan he thong: $" 
             << fixed << setprecision(2) << (tongPhi / tongSoXe) << endl;

        for (int vt = 1; vt <= 3; vt++) {
            if (coBai(vt)) {
                const BaiDoXe& bai = layBaiConst(vt);
                int n = bai.demXeTheoLoai(loai);
                cout << "    + Bai ID " << bai.layMaBai() << ": ";
                if (n == 0) {
                    cout << "Khong co xe" << endl;
                } else {
                    cout << "$" << fixed << setprecision(2) << (bai.tongPhiTheoLoai(loai) / n) << endl;
                }
            }
        }
    }

    void baoCaoPhi() const {
        cout << "\n================ BÁO CÁO PHÍ ĐỖ XE TRUNG BÌNH ================";
        baoCaoMotLoai("Car");
        baoCaoMotLoai("Motorcycle");
        baoCaoMotLoai("Bicycle");
        cout << "==============================================================" << endl;
    }

public:
    GiaoDien() {
        coBai1 = coBai2 = coBai3 = false;
    }

    void runMenu() {
        int luaChon;
        do {
            cout << "\n================ SYSTEM MENU ================" << endl;
            cout << "1. Tao Bai do xe moi" << endl;
            cout << "2. Them xe vao bai do xe" << endl;
            cout << "3. Xoa mot bai do xe" << endl;
            cout << "4. Lay xe ra khoi bai do xe" << endl;
            cout << "5. Hien thi danh sach tat ca cac bai do xe" << endl;
            cout << "6. Hien thi danh sach xe theo bai cu the" << endl;
            cout << "7. Liet ke xe theo loai phuong tien" << endl;
            cout << "8. Xem bao cao tom tat phi do xe trung binh" << endl;
            cout << "9. Thoat" << endl;
            cout << "=============================================" << endl;

            luaChon = docSoNguyen("Nhap lua chon cua ban (1-9): ");

            switch (luaChon) {
                case 1: taoBaiMoi(); break;
                case 2: themXeVaoBai(); break;
                case 3: xoaBai(); break;
                case 4: layXeRa(); break;
                case 5: hienThiTatCaBai(); break;
                case 6: hienThiXeTheoBai(); break;
                case 7: lietKeTheoLoai(); break;
                case 8: baoCaoPhi(); break;
                case 9: cout << "Cam on ban da su dung chuong trinh!" << endl; break;
                default: cout << "Lua chon khong hop le. Vui long chon tu 1 den 9!" << endl;
            }
        } while (luaChon != 9);
    }
};

int main() {
    GiaoDien app;
    app.runMenu();
    return 0;
}
