#include "nwpwin.h"
#include "nwpdlg.h"

class number_dialog : public vsite::nwp::dialog {
public:
	int brojkrugovaD;
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
};

class main_window : public vsite::nwp::window {
public:
	int brojkrugova = 0;
	COLORREF color = RGB(0, 0, 0);
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
};
