#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class Paint {
private:
	IDirect3D9Ex* object = NULL;
	IDirect3DDevice9Ex* device = NULL;
	D3DPRESENT_PARAMETERS parameters;
	ID3DXFont* font = 0;
	HWND targetHWND;
	int height, width;

	int init(HWND hWND);

	void drawText(char* string, int x, int y, int a, int r, int g, int b);

public:
	Paint();
	Paint(HWND overlayHWND, HWND targetHWND, int width, int height);
	int render();
};