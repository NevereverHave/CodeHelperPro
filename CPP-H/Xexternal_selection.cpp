#include "Xexternal_selection.h"
#include <iostream>
XEx_Selec::XEx_Selec() { XEx_Selec::SelecHwND = NULL; }
BOOL XEx_Selec::InIt(HWND hWnd) {
	SelecHwND = hWnd;
	if (hWnd == NULL) { return false; }
	return true;
};
BOOL XEx_Selec::DeleteClip(int index) {
	if (index == -1) { return false; }
	int outcome = SendMessageA(SelecHwND,ICM_DELETEPROFILE,index,0);
	return outcome != 0;
}
int XEx_Selec::GetNum() {
	return SendMessageA(SelecHwND, TCM_GETITEMCOUNT, 0, 0);
};
int XEx_Selec::insertClip(int where,LPSTR title,int additional,int img) {
	TCITEM structure;
	int outcome, num;
	num = GetNum();
	if (where==NULL||where>num-1||where==-1) {
		where = num;
	}
	structure.mask = TCIF_TEXT + TCIF_IMAGE + TCIF_PARAM;
	structure.dwState = 0;
	structure.dwStateMask = 0;
	structure.pszText = title;
	structure.cchTextMax = 0;
	structure.iImage = img;
	structure.lParam = additional;
	outcome = SendMessageA(SelecHwND, TCM_INSERTITEMA,where, reinterpret_cast<LPARAM>(&structure));
	if (num == 0) {
		UpdateWindow(GetParent(SelecHwND));
	}
	return outcome;
}
string XEx_Selec::GetTitle(int index) {
	if (index == -1) {
		index = GetNum() - 1;
	}
	TCITEM structure;
	structure.mask = TCIF_TEXT;
	structure.dwState = 0;
	structure.dwStateMask = 0;
	structure.pszText = new char[256];
	structure.cchTextMax = 256;
	structure.iImage = -1;
	structure.lParam = 1;
	SendMessageA(SelecHwND, TCM_GETITEMA, index, reinterpret_cast<LPARAM>(&structure));
	return structure.pszText;
}
int XEx_Selec::GetAdditional(int index) {
	if (index == -1) {
		index = GetNum() - 1;
	}
	TCITEM structure;
	structure.mask = TCIF_PARAM;
	SendMessageA(SelecHwND, TCM_GETITEMA, index, reinterpret_cast<LPARAM>(&structure));
	return structure.lParam;
}
bool XEx_Selec::SetTitle(int index,LPSTR Title) {
	if (index == -1) {
		index = GetNum() - 1;
	}
	TCITEM structure;
	structure.mask = TCIF_TEXT;
	structure.dwState = 0;
	structure.dwStateMask = 0;
	structure.pszText = Title;
	structure.cchTextMax = 0;
	structure.iImage = -1;
	structure.lParam = 1;
	auto outcome = SendMessageA(SelecHwND, TCM_GETITEMA, index, reinterpret_cast<LPARAM>(&structure));
	return outcome != 0;
}
bool XEx_Selec::SetAdditional(int index,int v) {
	if (index == -1) {
		index = GetNum() - 1;
	}
	TCITEM structure;
	structure.mask = TCIF_TEXT;
	structure.lParam = v;
	auto outcome = SendMessageA(SelecHwND, TCM_GETITEMA, index, reinterpret_cast<LPARAM>(&structure));
	return outcome != 0;
}
void XEx_Selec::SetCurrentClip(int index) {
	if (index == -1) {
		index = GetNum() - 1;
	}
	SendMessageA(SelecHwND, TCM_SETCURFOCUS, index,0);
}
int XEx_Selec::GetCurrentClip() {
	return SendMessageA(SelecHwND,TCM_GETCURFOCUS,0,0);
}
void XEx_Selec::DeleteAll() {
	SendMessageA(SelecHwND, TCM_DELETEALLITEMS, 0, 0);
}
void XEx_Selec::SetSize(int Width ,int Height) {
	SendMessageA(SelecHwND, TCM_SETITEMSIZE, 0, MAKELPARAM(Width, Height));
}
void XEx_Selec::SetWidth(int Width) {
	SendMessageA(SelecHwND, TCM_SETMINTABWIDTH, 0,Width);
}