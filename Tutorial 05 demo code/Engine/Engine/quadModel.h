#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "modelclass.h"
#include "gamemodel.h"


#include <string>

using namespace DirectX;

class QuadModel : public GameModel
	//This model represents a quad made up of two trianges.
	//One of lengthX, lengthY, or lengthZ must be 0;
{
public:
	QuadModel(float lengthX, float lengthY, XMFLOAT4 * pColor = 0);
	virtual ~QuadModel(void);
	virtual void Shutdown();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShaderClass* colorShader, TextureShaderClass* textureShader);

protected:
	virtual void InitializeModel(float lengthX, float lengthY, XMFLOAT4 * pColor);
	
	ColorVertexType* m_colorVertices;
	unsigned long*	m_indices;
	ModelClass*     m_VertexModel; //vertices to put on graphics pipeline for rendering


};

