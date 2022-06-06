#include "main.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "rc.h"
#include <windows.h>

int number_dialog::idd() const {
	return IDD_NUMBER;
}
bool number_dialog::on_init_dialog() {
	set_int(IDC_EDIT1, this->brojkrugovaD);
	return true;
}
bool number_dialog::on_ok() {
	try {
		this->brojkrugovaD = get_int(IDC_EDIT1);
	}
	catch (std::runtime_error) {
		MessageBox(*this, _T("mora biti broj"), 0, MB_OK);
		return false;
	}
	return true;
}

void main_window::on_paint(HDC hdc) {
	POINT sredina;
	RECT rect;
	GetClientRect(*this, &rect);
	sredina.x = rect.right / 2;
	sredina.y = rect.bottom / 2;
	int r = rect.bottom / 4;
	HBRUSH h = CreateSolidBrush(this->color);
	HGDIOBJ brush = SelectObject(hdc, h);
	SelectObject(hdc, GetStockObject(NULL_PEN));
	SetROP2(hdc, R2_NOTXORPEN);
	for (int i = 0; i < this->brojkrugova; ++i) {
		double a = M_PI * 2 * i / brojkrugova;
		int centerX = sredina.x + r * sin(a);
		int centerY = sredina.y + r * cos(a);
		Ellipse(hdc, centerX - r, centerY - r, centerX + r, centerY + r);
	}
	SelectObject(hdc, brush);
	DeleteObject(h);
}

void main_window::on_command(int id) {

	switch (id) {
	case ID_COLOR: {
		CHOOSECOLOR ColorDialog;
		COLORREF acrCustClr[16] = { 0 };
		ZeroMemory(&ColorDialog, sizeof ColorDialog);
		ColorDialog.lStructSize = sizeof ColorDialog;
		ColorDialog.hwndOwner = *this;
		ColorDialog.lpCustColors = acrCustClr;
		ColorDialog.rgbResult = this->color;
		ColorDialog.Flags = CC_FULLOPEN | CC_RGBINIT;
		if (ChooseColor(&ColorDialog)) {
			this->color = ColorDialog.rgbResult;
		}
		InvalidateRect(*this, NULL, true);
		break;
	}
	case ID_NUMBER: {
		number_dialog nd;
		nd.brojkrugovaD = brojkrugova;
		if (nd.do_modal(0, *this) == IDOK) {
			brojkrugova = nd.brojkrugovaD;
			InvalidateRect(*this, NULL, true);
		}
		break;
	}
	case ID_EXIT:
		DestroyWindow(*this);
		break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}
