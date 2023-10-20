#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "D:/GitSilkroadTimer/silkroad_taxi_timer/packages/Microsoft.DXSDK.D3DX.9.29.952.8/build/native/release/lib/x64/d3dx9.lib")

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
	int render();

	Paint();
	Paint(HWND overlayHWND, HWND targetHWND, int width, int height);
};