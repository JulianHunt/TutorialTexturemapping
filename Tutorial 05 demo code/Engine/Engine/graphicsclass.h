////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_



///////////////////////
// MY CLASS INCLUDES //
///////////////////////


#include "d3dclass.h"
#include "cinecameraclass.h"
#include "modelclass.h"
#include "arraylist.h"
#include "gamemodel.h"
#include "XYZaxis.h"



#include "colorshaderclass.h"
#include "textureshaderclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND, CineCameraClass*, ArrayList<GameModel> * gameModels);
	void Shutdown();
	bool Frame(); 



private:
	bool Render();

private:
	
	HWND m_hwnd;
	D3DClass* m_D3D;
	CineCameraClass* m_Camera;

	ModelClass* m_AxisModel;
	XYZaxis* m_axis;

	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;

	ArrayList<GameModel> * m_GameWorldModels;



};

#endif