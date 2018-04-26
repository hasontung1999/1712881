﻿#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

struct SinhVien
{
	wchar_t MSSV[10];
	wchar_t HoTen[30];
	wchar_t Khoa[30];
	wchar_t NamHoc[5];
	wchar_t NgaySinh[11];
	wchar_t HinhAnh[30];
	wchar_t	MoTa[1000];
	wchar_t SoThich[10][100];
};
//đếm số sở thích
int Countsothich(FILE* inFile)
{
	int n = 0;
	wchar_t c = (wchar_t)malloc(sizeof(wchar_t));
	while (c != '\n')
	{
		c = fgetwc(inFile);
		if (c == ';')
			n++;
	}
	return n + 1 - 7;
}
//đếm số sinh viên
int CountSV(FILE* inFile)
{
	int n = 0;
	wchar_t c;
	while (!feof(inFile))
	{
		c = fgetwc(inFile);
		if (c == '\n')
			n++;
	}
	return n;
}
//đọc dữ liệu
void ReadCSV(FILE* inFile, wchar_t a[], int SoKiTu)
{
	for (int i = 0; i < SoKiTu; i++)
	{
		a[i] = fgetwc(inFile);
		if (a[i] == ';' || a[i] == '\n')
		{
			a[i] = '\0'; break;
		}
	}
}
void ReadCSV(FILE* inFile, SinhVien &sv, int SoSoThich)
{
	ReadCSV(inFile, sv.MSSV, 10);
	ReadCSV(inFile, sv.HoTen, 30);
	ReadCSV(inFile, sv.Khoa, 30);
	ReadCSV(inFile, sv.NamHoc, 5);
	ReadCSV(inFile, sv.NgaySinh, 11);
	ReadCSV(inFile, sv.HinhAnh, 30);
	ReadCSV(inFile, sv.MoTa, 1000);
	if (SoSoThich == 0)
		sv.SoThich[0][0] = '\0';
	else
	{
		for (int i = 0; i < SoSoThich; i++)
		{
			ReadCSV(inFile, sv.SoThich[i], 100);
		}
	}
}
//đưa vào file html
void WriteHTML(FILE* outFile, SinhVien sv, int SoSoThich)
{
	fwprintf(outFile, L"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\r\n<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n<head>\r\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\n<link rel=\"stylesheet\" type=\"text/css\" href=\"personal.css\" />\r\n<title>HCMUS - %s</title>\r\n</head>\r\n<body>\r\n<div class=\"Layout_container\">\r\n<!-- Begin Layout Banner Region -->\r\n<div class=\"Layout_Banner\" >\r\n<div><img id=\"logo\" src=\"Images/logo.jpg\" height=\"105\" /></div>\r\n<div class=\"Header_Title\">TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN </div>\r\n</div>\r\n<!-- End Layout Banner Region -->\r\n<!-- Begin Layout MainContents Region -->\r\n<div class=\"Layout_MainContents\">\r\n<!-- Begin Below Banner Region -->\r\n<div class=\"Personal_Main_Information\">\r\n<!-- Begin Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\r\n<div class=\"Personal_Location\">\r\n<img src=\"Images/LogoFooter.jpg\" width=\"27\" height=\"33\" />\r\n<span class=\"Personal_FullName\">%s - %s</span>\r\n<div class=\"Personal_Department\">%s</div>\r\n<br />\r\n<div class=\"Personal_Phone\">\r\nEmail: %s@student.hcmus.edu.vn\r\n</div>\r\n<br />\r\n<br /> \r\n</div>\r\n<!-- End Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\r\n<div class=\"Personal_HinhcanhanKhung\">\r\n<img src=\"Images/%s\" class=\"Personal_Hinhcanhan\" />\r\n</div>\r\n</div>\r\n<!-- End Below Banner Region -->\r\n<!-- Begin MainContents Region -->\r\n<div class=\"MainContain\">\r\n\r\n<!-- Begin Top Region -->\r\n<div class=\"MainContain_Top\">\r\n\r\n<div class=\"InfoGroup\">Thông tin cá nhân</div>\r\n<div>\r\n<ul class=\"TextInList\">\r\n<li>Họ và tên: %s</li>\r\n<li>MSSV: %s</li>\r\n<li>Sinh viên khoa %s</li>\r\n<li>Ngày sinh: %s</li>\r\n<li>Email: %s@student.hcmus.edu.vn</li>\r\n</ul>\r\n</div>\r\n<div class=\"InfoGroup\">Sở thích</div>\r\n<div>\r\n<ul class=\"TextInList\">", sv.HoTen, sv.HoTen, sv.MSSV, sv.Khoa, sv.MSSV, sv.HinhAnh, sv.HoTen, sv.MSSV, sv.Khoa, sv.NgaySinh, sv.MSSV);
	if (SoSoThich == 0)
		fwprintf(outFile, L"\r\n<li>%s</li>", sv.SoThich[0]);
	else
	{
		for (int i = 0; i < SoSoThich; i++)
		{
			fwprintf(outFile, L"\r\n<li>%s</li>", sv.SoThich[i]);
		}
	}
	fwprintf(outFile, L"\r\n</ul>\r\n</div>\r\n<div class = \"InfoGroup\">Mô tả</div>\r\n<div class=\"Description\">\r\n%s.\r\n</div>\r\n\r\n</div>\r\n</div>\r\n</div>\r\n\r\n<!-- Begin Layout Footer -->\r\n<div class=\"Layout_Footer\">\r\n<div class=\"divCopyright\">\r\n<br />\r\n<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\r\n<br />\r\n@2018</br>\r\nĐồ án giữ kỳ</br>\r\nKỹ thuật lập trình</br>\r\nTH2018/01</br>\r\n1712881 - Hà Sơn Tùng</br>\r\n</div>\r\n</div>\r\n<!-- End Layout Footer -->\r\n</div>\r\n</body>\r\n</html>", sv.MoTa);
}
int wmain(int argc, wchar_t* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input

	wchar_t* html = (L".html");
	FILE* fp = _wfopen(L"danhsach.csv", L"r,ccs=UTF-8");
	if (!fp)
	{
		wprintf(L"Tệp rỗng hoặc không tồn tại!!!");
		exit(0);
	}
	int n;
	n = CountSV(fp);
	rewind(fp);
	int m = Countsothich(fp);
	if (m < 0)
	{
		wprintf(L"File thiếu trường!!!\n");
		exit(0);
	}
	SinhVien* sv;
	sv = (SinhVien*)malloc(n*sizeof(struct SinhVien));
	rewind(fp);
	for (int i = 0; i < n; i++)
	{
		ReadCSV(fp, sv[i], m);
		wchar_t* s = (wchar_t*)malloc(15 * sizeof(wchar_t));
		wcscpy(s, sv[i].MSSV);
		wchar_t* x = wcscat(s, html);
		FILE* outFile = _wfopen(x, L"w,ccs=UTF-8");
		WriteHTML(outFile, sv[i], m);
	}
	fcloseall;
}
