#include "Paint.h"

int Paint::init(HWND hWND) {
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &object))) {
		exit(1);
	}

	ZeroMemory(&parameters, sizeof(parameters));

	parameters.BackBufferWidth = width;
	parameters.BackBufferHeight = height;
	parameters.Windowed = true;
	parameters.hDeviceWindow = hWND;
	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	parameters.EnableAutoDepthStencil = TRUE;
	parameters.AutoDepthStencilFormat = D3DFMT_D16;

	object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWND, D3DCREATE_HARDWARE_VERTEXPROCESSING, &parameters, 0, &device);
	D3DXCreateFont(device,50,0,FW_BOLD,1,false,DEFAULT_CHARSET,OUT_DEVICE_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH,L"Comic Sans",&font);

	return 0;
}

int Paint::render() {
	if (&device == nullptr) {
		return 1;
	}

	device->Clear(0,0,D3DCLEAR_TARGET, 0, 1.0f, 0);
	device->BeginScene();

	if (targetHWND == GetForegroundWindow()) {
		drawText((char*)"Hello from directX", width / 10, height / 10, 255, 171, 0, 182);
	}

	device->EndScene();
	device->PresentEx(0,0,0,0,0);

	return 0;
}

Paint::Paint()
{
}

Paint::Paint(HWND overlayHWND, HWND targetHWND, int width, int height)
{
	this->height = height;
	this->width = width;
	this->targetHWND = targetHWND;

	init(overlayHWND);
}

void Paint::drawText(char* string, int x, int y, int a, int r, int g, int b) {
	RECT rect;
	rect.top = y;
	rect.left = x;

	font->DrawTextA(0, string, strlen(string), &rect, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
}