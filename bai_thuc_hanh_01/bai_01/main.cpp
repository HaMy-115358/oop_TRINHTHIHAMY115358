#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    
public:
    phuong_tien();
    
    phuong_tien(int ma, string loai, int gio, int tg);
    
    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};
phuong_tien::phuong_tien(){
	ma_xe = 0;
	loai_xe = "";
	gio_vao = 0;
	tg_do = 0;
}
phuong_tien::phuong_tien(int ma, string loai, int gio, int tg){
	ma_xe = ma;
	loai_xe = loai;
	gio_vao = gio;
	tg_do = tg;
}
int phuong_tien::lay_ma_xe() const{
	return ma_xe;
}
string phuong_tien::lay_loai_xe() const{
	return loai_xe;
}
double phuong_tien::tinh_phi() const{
	double dongia = 0;
	if(loai_xe == "Car"){
		dongia = 6;
	}
	if(loai_xe == "Motocycle"){
		dongia = 4;
	}
	if(loai_xe == "Bicycle"){
		dongia = 2;
	}
	bool giocaodiem = (giovao>=6 && giovao<=9) || (giovao >= 15 && giovao <=18);
	double heso = 0.95;
	if(giocaodiem) heso == 1.3;
	int giodau = thoigiando;
	int giosau = 0;
	if(thoigiando>2){
		giodau = 2;
		giosau = thoigiando - 2;
	}
	phidoxe = giodau*dongia*heso + giosau * dongia * 0.9;
}
void phuong_tien::hien_thi() {
        if (!dangChiemCho) return;
        cout << "   Ma xe: " << ma_xe 
             << " | Loai xe: " << loai_xe 
             << " | Gio vao: " << gio_vao
             << " | Thoi gian do: " << tg_do
             << " | Phi do: " << fixed << setprecision(2) << phidoxe << " VNĐ" << endl;
}

class bai_xe{
	private:
		int ma_bai;
		char kich_thuoc;
		phuong_tien pt1, pt2, pt3;
		bool co1, co2, co3;
	public:
		bai_xe();
		bai_xe(int ma, char kt);
		int lay_ma() const;
		bool them(phuong_tien v);
		bool xoa(int ma_xe);
		bool chua(int ma_xe) const;
		void hien_thi() const;
		bool co_loai(string loai, int& dem, double& tong) const;
};
bai_xe::bai_xe() {
	ma_bai = 0;
	kich_thuoc=0;
}
bai_xe::bai_xe(int ma, char kt){
	ma_bai=ma;
	kich_thuoc=kt;
} 
int bai_xe::lay_ma() const{
	return ma_bai;
}
