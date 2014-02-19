#include "gamemodel.h"
#include "modelclass.h"
#include "quadTexturedModel.h"

QuadTexturedModel::QuadTexturedModel(float lengthX, float lengthY, WCHAR* aTextureFileName) : GameModel()
{
	InitializeModel(lengthX, lengthY, aTextureFileName);
}

QuadTexturedModel::~QuadTexturedModel(void)
{
}


void QuadTexturedModel::InitializeModel(float lengthX, float lengthY, WCHAR* aTextureFileName)
{

	/*
	Create a quad consisting of 4 vertices and 2 triangles
	*/
	int vertexCount = 4;
	int indexCount = 6;

	m_textureVertices = new TextureVertexType[vertexCount];

	m_indices = new unsigned long[indexCount];

	//potentially dangerous, we should probably make a copy of the string and
	//release it ourselves later
	m_textureFileName = aTextureFileName;
	


	//Quad Face
	m_textureVertices[0].position = XMFLOAT3(-lengthX/2, -lengthY/2, 0.0f); // Bottom left.
	m_textureVertices[0].texture = XMFLOAT2(0.0f, 1.0f);
	
	m_textureVertices[1].position = XMFLOAT3(-lengthX/2, lengthY/2, 0.0f);  // Top left.
	m_textureVertices[1].texture = XMFLOAT2(0.0f, 0.0f);

	m_textureVertices[2].position = XMFLOAT3(lengthX/2, -lengthY/2, 0.0f);  // Bottom right.
	m_textureVertices[2].texture = XMFLOAT2(1.0f, 1.0f);
	
	m_textureVertices[3].position = XMFLOAT3(lengthX/2, lengthY/2, 0.0f);   // Top right.
	m_textureVertices[3].texture = XMFLOAT2(1.0f, 0.0f);




	// Load the index array with data.
	// Two triangles per face. The directions are consistent
	// With back-face culling in a left-hand co-ordinate system.

	//Quad Face
	m_indices[0] = 0;  // Bottom left.
	m_indices[1] = 1;  // Top left.
	m_indices[2] = 2;  // Bottom right.
	m_indices[3] = 1;  // Top left.
	m_indices[4] = 3;  // Top right.  
	m_indices[5] = 2;  // Bottom right.




	//Create the ModelClass object that will be used to deliver these vertices to the graphics pipeline
	m_VertexModel = new ModelClass(m_textureVertices, vertexCount, m_indices, indexCount, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

bool QuadTexturedModel::InitializeVertexModels(ID3D11Device* d3dDevice){
	
	//initialize vertices and textures for rendering to d3dDevice

	bool result = m_VertexModel->Initialize(d3dDevice);

	if(!result) return false;

	result = initializeTextures(d3dDevice);

	return result;

}

bool QuadTexturedModel::initializeTextures(ID3D11Device* d3dDevice){
	
	bool result;

	// Create quad texture object.
	m_quadTexture = new TextureClass;
	if(!m_quadTexture)
	{
		return false;
	}
	// Initialize the body texture object.
	result = m_quadTexture->Initialize(d3dDevice, m_textureFileName);
	if(!result)
	{
		return false;
	}

	return true;
}

ID3D11ShaderResourceView* QuadTexturedModel::GetTexture(){

	return m_quadTexture->GetTexture();
}



bool QuadTexturedModel::Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShaderClass* colorShader, TextureShaderClass* textureShader){
	
	if(!textureShader) return false; //we were not provided with a shader

	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	 m_VertexModel->Render(deviceContext);

	 //render the game model
	 bool result = textureShader->Render(deviceContext, 
		                                  m_VertexModel->GetIndexCount(), 
								          GetWorldMatrix(), 
								          viewMatrix, 
								          projectionMatrix,
										  GetTexture()); //get the texture to render
	


	return result; 

}


void QuadTexturedModel::Shutdown()
{


	if(m_textureVertices)
	{
		delete[] m_textureVertices;
		m_textureVertices = 0;
	}

	if(m_indices)
	{
		delete[] m_indices;
		m_indices = 0;
	}

	if(m_VertexModel)
	{
		delete m_VertexModel;
		m_VertexModel = 0;
	}

	// Release the texture objects.
	if(m_quadTexture)
	{
		m_quadTexture->Shutdown();
		delete m_quadTexture;
		m_quadTexture = 0;
	}


}
