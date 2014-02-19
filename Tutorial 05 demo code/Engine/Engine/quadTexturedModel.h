#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "textureclass.h"
#include "modelclass.h"
#include "gamemodel.h"


#include <string>

using namespace DirectX;

class QuadTexturedModel : public GameModel
	//This model represents a quad made up of two trianges.
	//One of lengthX, lengthY, or lengthZ must be 0;
{
public:
	QuadTexturedModel(float lengthX, float lengthY, WCHAR* aTextureFileName);
	virtual ~QuadTexturedModel(void);
	virtual void Shutdown();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
    virtual bool initializeTextures(ID3D11Device* d3dDevice);
	virtual ID3D11ShaderResourceView* GetTexture();
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShaderClass* colorShader, TextureShaderClass* textureShader);

protected:
	virtual void InitializeModel(float lengthX, float lengthY, WCHAR* aTextureFileName);

private:
	WCHAR * m_textureFileName; 
	TextureClass * m_quadTexture;

	TextureVertexType* m_textureVertices;
	unsigned long*	m_indices;

	ModelClass*     m_VertexModel; //vertices to put on graphics pipeline for rendering

};
