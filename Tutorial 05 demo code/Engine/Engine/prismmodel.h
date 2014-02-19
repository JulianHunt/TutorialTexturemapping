#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "modelclass.h"
#include "gamemodel.h"


#include <string>

using namespace DirectX;

class PrismModel : public GameModel
{
public:
	PrismModel(float height, float radius, int nFaces, XMFLOAT4 * pColors = 0);
	virtual ~PrismModel(void);
	virtual void Shutdown();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShaderClass* colorShader, TextureShaderClass* textureShader);

protected:
	virtual void InitializeModel(float height, float radius, int nFaces, XMFLOAT4 * pColors);

	ColorVertexType* m_colorVertices;
	unsigned long*	m_indices;
	ModelClass*     m_VertexModel; //vertices to put on graphics pipeline for rendering


};

