#include <Windows.h>
#include "resource.h"
#include <string>
using namespace std;

HINSTANCE hInstance;

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	::hInstance = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hRadioButtons[4];
	static HWND hButtonOk, hButtonCancel,hButtonEqual,hResultStatic,hEdit1,hEdit2;

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		hRadioButtons[0] = GetDlgItem(hwnd, IDC_RADIO1);
		hRadioButtons[1] = GetDlgItem(hwnd, IDC_RADIO2);
		hRadioButtons[2] = GetDlgItem(hwnd, IDC_RADIO3);
		hRadioButtons[3] = GetDlgItem(hwnd, IDC_RADIO4);
		hButtonOk = GetDlgItem(hwnd, IDOK);
		hButtonCancel = GetDlgItem(hwnd, IDCANCEL);
        hResultStatic = GetDlgItem(hwnd, IDC_STATIC24);
		hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
		hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);

		break;
	}

    case WM_COMMAND:
        
        if (LOWORD(wParam) == IDC_BUTTON1 && HIWORD(wParam) == BN_CLICKED) {
            INT result;
            for (size_t i = 0; i < 4; i++) {
                LRESULT isChecked = SendMessage(hRadioButtons[i], BM_GETCHECK, 0, 0);
                if (isChecked == BST_CHECKED) {
                    int num1 = 0, num2 = 0;
                    wchar_t buffer1[256], buffer2[256];
                    GetWindowText(hEdit1, buffer1, 256);
                    GetWindowText(hEdit2, buffer2, 256);

                    num1 = _wtoi(buffer1);
                    num2 = _wtoi(buffer2);

                    if (i == 0) {
                        result = num1 + num2;
                    }
                    else if (i == 1) {
                        result = num1 - num2;
                    }
                    else if (i == 2) {
                        result = num1 * num2;
                    }
                    else if (i == 3) {
                        if (num2 != 0) {
                            result = num1 / num2;
                        }
                        else {
                            result = 0; 
                        }
                    }

                    wstring resultStr = to_wstring(result);
                    SetWindowText(hResultStatic, resultStr.c_str());
                    break; 
                }
            }
        }
        else if (LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == IDOK) {
            EndDialog(hwnd, 0);
        }
        break;


	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;
	}

	return FALSE;
}