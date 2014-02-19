#include "gamemodel.h"
#include "modelclass.h"
#include "quadmodel.h"

QuadModel::QuadModel(float lengthX, float lengthY, XMFLOAT4 * pColor) : GameModel()
{
	InitializeModel(lengthX, lengthY, pColor);
}

QuadModel::~QuadModel(void)
{
}


void QuadModel::InitializeModel(float lengthX, float lengthY, XMFLOAT4 * pColor)
{

	/*
	Create a quad consisting of 4 vertices and 2 triangles
	*/
	int vertexCount = 4;
	int indexCount = 6;

	m_colorVertices = new ColorVertexType[vertexCount];
	m_indices = new unsigned long[indexCount];
	

	XMFLOAT4 vertexColor;
	vertexColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f); //red
	if(pColor) vertexColor = *pColor;

	//Quad Face
	m_colorVertices[0].position = XMFLOAT3(-lengthX/2, -lengthY/2, 0.0f); // Bottom left.
	m_colorVertices[0].color = vertexColor;
	
	m_colorVertices[1].position = XMFLOAT3(-lengthX/2, lengthY/2, 0.0f);  // Top left.
	m_colorVertices[1].color = vertexColor;

	m_colorVertices[2].position = XMFLOAT3(lengthX/2, -lengthY/2, 0.0f);  // Bottom right.
	m_colorVertices[2].color = vertexColor;
	
	m_colorVertices[3].position = XMFLOAT3(lengthX/2, lengthY/2, 0.0f);   // Top right.
	m_colorVertices[3].color = vertexColor;




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
	m_VertexModel = new ModelClass(m_colorVertices, vertexCount, m_indices, indexCount, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

bool QuadModel::InitializeVertexModels(ID3D11Device* d3dDevice){
	//subclasses who have vertices are expected to overide this method
	return m_VertexModel->Initialize(d3dDevice);

}

bool QuadModel::Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShaderClass* colorShader, TextureShaderClass* textureShader){
	
	if(!colorShader) return false; //we were not provided with a shader

	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	 m_VertexModel->Render(deviceContext);

	 //render the game model
	 bool result = colorShader->Render(deviceContext, 
		                                  m_VertexModel->GetIndexCount(), 
								          GetWorldMatrix(), 
								          viewMatrix, 
								          projectionMatrix);
	
	return result; 

}


void QuadModel::Shutdown()
{
	if(m_colorVertices)
	{
		delete[] m_colorVertices;
		m_colorVertices = 0;
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


}
