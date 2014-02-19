#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "textureclass.h"
#include "modelclass.h"
#include "gamemodel.h"


#include <string>

using namespace DirectX;

class PrismTexturedModel : public GameModel
{
public:
	PrismTexturedModel(float height, float radius, int nFaces, WCHAR** pTextureFileNames);
	virtual ~PrismTexturedModel(void);
	virtual void Shutdown();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
    virtual bool initializeTextures(ID3D11Device* d3dDevice);
	virtual ID3D11ShaderResourceView* GetTexture(int i);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShaderClass* colorShader, TextureShaderClass* textureShader);

protected:
	virtual void InitializeModel(float height, float radius, int nFaces, WCHAR** pTextureFileNames);

	private:
	static const int NUMBER_OF_TEXTURES = 3;
	
	WCHAR ** m_textureFileNames;  //Array of texture three file names

	TextureVertexType* m_textureVertices;	 //vertices of sides of prism
	TextureVertexType* m_topTextureVertices; //vertices of top end of prism
	TextureVertexType* m_bottomTextureVertices; //vertices of bottom end of prism

	unsigned long*	m_indices; //vertex indices of side triangles of prism
	unsigned long*	m_topIndices; //vertex indices of top triangles of prism
	unsigned long*	m_bottomIndices; //vertix indices of bottom triangles of prism

	TextureClass ** m_faceTextures; //Array of face textures to texture the model
	ModelClass**     m_VertexModelArray; //Array of vertex arrays to put on graphics pipeline for rendering
};

