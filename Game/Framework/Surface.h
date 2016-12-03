#ifndef __SURFACE_H__

#define __SURFACE_H__

#include <exception>
#include <d3dx9.h>
using namespace std;


class Surface
{
public:
	Surface(void);
	Surface(const Surface&);
	~Surface(void);

	void LoadSurfaceFromFile(LPDIRECT3DDEVICE9, D3DCOLOR, LPCWSTR);
	void RenderSurface(LPDIRECT3DDEVICE9, RECT*, RECT*);
	void UnloadSurface();

private:

	LPDIRECT3DSURFACE9 m_lpSurface;
	LPDIRECT3DSURFACE9 m_lpBackBuffer;
};


typedef Surface* pSurface;


#endif // !__SURFACE_H__
