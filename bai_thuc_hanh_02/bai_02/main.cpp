#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

int doc_so(const string& tb, int min_v, int max_v) {
    int x;
    while (true) {
        cout << tb;
        if (cin >> x && x >= min_v && x <= max_v) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        if (cin.eof()) exit(0);
        cout << "Du lieu khong hop le! Nhap lai (" << min_v << " - " << max_v << ").\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

char doc_kich_thuoc() {
    char c;
    while (true) {
        cout << "Kich thuoc (S/M/L): ";
        if (cin >> c) {
            c = toupper(c);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c == 'S' || c == 'M' || c == 'L') return c;
        }
        else if (cin.eof()) exit(0);
        cout << "Chi nhan S, M hoac L!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string doc_loai_xe(const string& tb) {
    string s;
    while (true) {
        cout << tb;
        if (cin >> s) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (s == "Car" || s == "Motorcycle" || s == "Bicycle") return s;
        }
        else if (cin.eof()) exit(0);
        cout << "Chi nhan Car, Motorcycle hoac Bicycle!\n";
        cin.clear();
    }
}

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    int lay_gio_vao() const;
    int lay_tg_do() const;
    double lay_phi() const;

    void dat_ma_xe(int ma);
    void dat_loai_xe(string loai);
    void dat_gio_vao(int gio);
    void dat_tg_do(int tg);

    double tinh_phi();
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0), phi_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg), phi_do(0) {
    tinh_phi();
}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }
int phuong_tien::lay_gio_vao() const { return gio_vao; }
int phuong_tien::lay_tg_do() const { return tg_do; }
double phuong_tien::lay_phi() const { return phi_do; }

void phuong_tien::dat_ma_xe(int ma) { ma_xe = ma; }
void phuong_tien::dat_loai_xe(string loai) { loai_xe = loai; tinh_phi(); }
void phuong_tien::dat_gio_vao(int gio) { gio_vao = gio; tinh_phi(); }
void phuong_tien::dat_tg_do(int tg) { tg_do = tg; tinh_phi(); }

double phuong_tien::tinh_phi() {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    phi_do = 0;
    for (int h = 0; h < tg_do; ++h)
        phi_do += gia * (h < 2 ? (cao_diem ? 1.30 : 0.95) : 0.90);
    return phi_do;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << phi_do << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int MAX_XE = 3;
    phuong_tien ds_xe[MAX_XE];
    int so_xe;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    char lay_kich_thuoc() const;
    int lay_so_xe() const;
    int suc_chua() const;

    bool da_day() const;
    bool them(const phuong_tien& v);
    bool xoa(int ma_xe);
    int tim_xe(int ma_xe) const;
    void hien_thi() const;
    bool hien_thi_theo_loai(const string& loai) const;
    void thong_ke_loai(const string& loai, int& dem, double& tong) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_xe(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_xe(0) {}

int bai_xe::lay_ma() const { return ma_bai; }
char bai_xe::lay_kich_thuoc() const { return kich_thuoc; }
int bai_xe::lay_so_xe() const { return so_xe; }

int bai_xe::suc_chua() const {
    return (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
}

bool bai_xe::da_day() const { return so_xe >= suc_chua(); }

bool bai_xe::them(const phuong_tien& v) {
    if (da_day()) return false;
    ds_xe[so_xe++] = v;
    return true;
}

int bai_xe::tim_xe(int ma_xe) const {
    for (int i = 0; i < so_xe; ++i)
        if (ds_xe[i].lay_ma_xe() == ma_xe) return i;
    return -1;
}

bool bai_xe::xoa(int ma_xe) {
    int vt = tim_xe(ma_xe);
    if (vt == -1) return false;
    for (int i = vt; i < so_xe - 1; ++i)
        ds_xe[i] = ds_xe[i + 1];
    so_xe--;
    return true;
}

void bai_xe::hien_thi() const {
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe << "/" << suc_chua() << " xe\n";
    for (int i = 0; i < so_xe; ++i)
        ds_xe[i].hien_thi();
}

bool bai_xe::hien_thi_theo_loai(const string& loai) const {
    bool co = false;
    for (int i = 0; i < so_xe; ++i) {
        if (ds_xe[i].lay_loai_xe() == loai) {
            if (!co) {
                cout << "Bai " << ma_bai << " [" << kich_thuoc << "]:\n";
                co = true;
            }
            ds_xe[i].hien_thi();
        }
    }
    return co;
}

void bai_xe::thong_ke_loai(const string& loai, int& dem, double& tong) const {
    dem = 0;
    tong = 0;
    for (int i = 0; i < so_xe; ++i) {
        if (ds_xe[i].lay_loai_xe() == loai) {
            dem++;
            tong += ds_xe[i].lay_phi();
        }
    }
}

class SystemInterface {
private:
    static const int MAX_BAI = 10;
    bai_xe ds_bai[MAX_BAI];
    int so_bai;

    int tim_bai(int ma) const;
    void tao_bai();
    void them_xe();
    void xoa_bai();
    void lay_xe_ra();
    void hien_thi_tat_ca() const;
    void hien_thi_xe_theo_bai() const;
    void liet_ke_theo_loai() const;
    void bao_cao_phi() const;

public:
    SystemInterface();
    void runMenu();
    bool trung_ma_bai(int ma) const;
    bool trung_ma_xe(int ma) const;
    int sinh_id_ngau_nhien();
};

SystemInterface::SystemInterface() : so_bai(0) {}

int SystemInterface::sinh_id_ngau_nhien() { return rand() % 9000 + 1000; }

int SystemInterface::tim_bai(int ma) const {
    for (int i = 0; i < so_bai; ++i)
        if (ds_bai[i].lay_ma() == ma) return i;
    return -1;
}

bool SystemInterface::trung_ma_bai(int ma) const { return tim_bai(ma) != -1; }

bool SystemInterface::trung_ma_xe(int ma) const {
    for (int i = 0; i < so_bai; ++i)
        if (ds_bai[i].tim_xe(ma) != -1) return true;
    return false;
}

void SystemInterface::tao_bai() {
    if (so_bai >= MAX_BAI) {
        cout << "Da dat toi da " << MAX_BAI << " bai do!\n";
        return;
    }
    int ma = doc_so("Ma bai: ", 1, 999999);
    char kt = doc_kich_thuoc();
    if (trung_ma_bai(ma)) {
        cout << "Canh bao: Ma bai " << ma << " da ton tai! ";
        do { ma = sinh_id_ngau_nhien(); } while (trung_ma_bai(ma));
        cout << "Tu dong gan ma moi: " << ma << "\n";
    }
    ds_bai[so_bai++] = bai_xe(ma, kt);
    cout << "Da tao bai " << ma << "\n";
}

void SystemInterface::them_xe() {
    if (so_bai == 0) {
        cout << "Chua co bai do nao! Hay tao bai truoc.\n";
        return;
    }
    int ma = doc_so("Ma xe: ", 1, 999999);
    string loai = doc_loai_xe("Loai (Car/Motorcycle/Bicycle): ");
    int gio = doc_so("Gio vao (0-23): ", 0, 23);
    int tg = doc_so("Thoi luong (1-23): ", 1, 23);
    if (trung_ma_xe(ma)) {
        cout << "Canh bao: Ma xe " << ma << " da ton tai! ";
        do { ma = sinh_id_ngau_nhien(); } while (trung_ma_xe(ma));
        cout << "Tu dong gan ma moi: " << ma << "\n";
    }
    phuong_tien v(ma, loai, gio, tg);
    for (int i = 0; i < so_bai; ++i) {
        if (ds_bai[i].them(v)) {
            cout << "Da xep xe " << ma << " vao bai " << ds_bai[i].lay_ma()
                 << " | Phi: $" << fixed << setprecision(2) << v.lay_phi() << "\n";
            return;
        }
    }
    cout << "Canh bao: Tat ca cac bai do deu da day!\n";
}

void SystemInterface::xoa_bai() {
    int ma = doc_so("Ma bai can xoa: ", 1, 999999);
    int vt = tim_bai(ma);
    if (vt == -1) {
        cout << "Khong tim thay bai " << ma << "\n";
        return;
    }
    for (int i = vt; i < so_bai - 1; ++i)
        ds_bai[i] = ds_bai[i + 1];
    so_bai--;
    cout << "Da xoa bai " << ma << "\n";
}

void SystemInterface::lay_xe_ra() {
    int ma = doc_so("Ma xe can lay ra: ", 1, 999999);
    for (int i = 0; i < so_bai; ++i) {
        if (ds_bai[i].xoa(ma)) {
            cout << "Da lay xe " << ma << " ra khoi bai " << ds_bai[i].lay_ma() << "\n";
            return;
        }
    }
    cout << "Khong tim thay xe " << ma << "\n";
}

void SystemInterface::hien_thi_tat_ca() const {
    if (so_bai == 0) {
        cout << "Chua co bai do nao.\n";
        return;
    }
    for (int i = 0; i < so_bai; ++i)
        ds_bai[i].hien_thi();
}

void SystemInterface::hien_thi_xe_theo_bai() const {
    int ma = doc_so("Ma bai: ", 1, 999999);
    int vt = tim_bai(ma);
    if (vt == -1) cout << "Khong tim thay bai " << ma << "\n";
    else ds_bai[vt].hien_thi();
}

void SystemInterface::liet_ke_theo_loai() const {
    string loai = doc_loai_xe("Loai xe: ");
    bool co = false;
    for (int i = 0; i < so_bai; ++i)
        if (ds_bai[i].hien_thi_theo_loai(loai)) co = true;
    if (!co) cout << "Khong co xe loai " << loai << "\n";
}

void SystemInterface::bao_cao_phi() const {
    const string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
    for (int t = 0; t < 3; ++t) {
        int dem = 0;
        double tong = 0;
        cout << "--- " << loai_arr[t] << " ---\n";
        for (int i = 0; i < so_bai; ++i) {
            int d;
            double s;
            ds_bai[i].thong_ke_loai(loai_arr[t], d, s);
            dem += d;
            tong += s;
            cout << "  Bai " << ds_bai[i].lay_ma() << ": ";
            if (d == 0) cout << "khong co xe\n";
            else cout << d << " xe | TB: $" << fixed << setprecision(2) << s / d << "\n";
        }
        cout << "  Toan he thong: ";
        if (dem == 0) cout << "khong co xe\n";
        else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
    }
}

void SystemInterface::runMenu() {
    int chon;
    do {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        chon = doc_so("Chon: ", 1, 9);
        switch (chon) {
            case 1: tao_bai(); break;
            case 2: them_xe(); break;
            case 3: xoa_bai(); break;
            case 4: lay_xe_ra(); break;
            case 5: hien_thi_tat_ca(); break;
            case 6: hien_thi_xe_theo_bai(); break;
            case 7: liet_ke_theo_loai(); break;
            case 8: bao_cao_phi(); break;
            case 9: cout << "Tam biet!\n"; break;
        }
    } while (chon != 9);
}

int main() {
    srand((unsigned)time(0));
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
