#include <iostream>
#include<string>
#inlcude<iomanip>
using namespace std;
class Xe{
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int thoiGianDo;
    double phiDoXe;
    bool dangChiemCho;
public:
   Xe(){
    maXe = 0;
    loaiXe = "";
    gioVao = 0;
    thoiGianDo = 0;
    phiDoXe = 0.0;
    dangChiemCho = false;
   }
   Xe(int ma, const string& loai, int gio, int thoiLuong){
    maXe = ma;
    loaiXe = loai;
    gioVao = gio;
    thoiGianDo = thoiLuong;
    dangChiemCho = true;
    tinhPhi();
   }
   int layMaXe() const{ return maXe; }
   string layLoaiXe() const{ return loaiXe; }
   int layGioVao() const{ return gioVao; }
   int layThoiGianDo() const{ return thoiGianDo; }
   double layPhiDoXe() const{ return phiDoXe; }
   bool layDangChiemCho() const{ return dangChiemCho; }
   void ganMaXe(int ma) { maXe = ma; }
   voide ganLoaiXe(const string& loai) { loaiXe = loai; }
   void ganGioVao(int gio) { gioVao = gio; }
   void ganThoiLuongDo(int thoiLuong) { thoiGianDo = thoiLuong; }
   void ganPhiDoXe(double phi) { phiDoXe = phi; }
   void ganDangChiemCho(bool trangThai) { dangChiemCho = trangThai; }
   static string chuanHoaLoaiXe(const string& loai){
    string s = loai;
    for(int i = 0; i < s.length(); i++){
        s[i] = tolower(s[i]);
    }
    return s;
   }
   static bool laLoaiXeHopLe(const string& loai){
    string s = chuanHoaLoaiXe(loai);
    return (s == "car" || s == "motorcycle" || s == "bicycle");
   }
}

