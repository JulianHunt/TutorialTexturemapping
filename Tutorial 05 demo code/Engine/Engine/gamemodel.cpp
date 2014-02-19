#include "gamemodel.h"
#include "modelclass.h"

GameModel::GameModel()
{

	//initialize all matrices to identity matrix
	XMStoreFloat4x4(&m_orientRotateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_orientTranslateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_dimensionScaleMatrix, XMMatrixIdentity());

	XMStoreFloat4x4(&m_worldRotateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_worldTranslateMatrix, XMMatrixIdentity());

}

GameModel::~GameModel(void)
{
	Shutdown();
}





void GameModel::Shutdown()
{

}



bool GameModel::InitializeVertexModels(ID3D11Device* d3dDevice){
	//subclasses who have vertices are expected to overide this method
	return false;

}

bool GameModel::initializeTextures(ID3D11Device* device){
	//subclasses who have textures are expected to overide this method
	return false;
}
ID3D11ShaderResourceView* GameModel::GetTexture(){
	//subclasses that have textures are expected to overide this method
	return 0;
}

ID3D11ShaderResourceView* GameModel::GetTexture(int i){
	//subclasses that have textures are expected to overide this method
	return 0;
}





//ModelClass* GameModel::GetVertexModel() {return m_VertexModel; }

XMFLOAT4X4 GameModel::GetWorldMatrix(){
    
	//Build the world matrix to give to the graphis system
	XMFLOAT4X4 worldMatrix; 
	XMStoreFloat4x4(&worldMatrix, 
		XMLoadFloat4x4(&m_orientRotateMatrix) * 
		XMLoadFloat4x4(&m_orientTranslateMatrix) * 
		XMLoadFloat4x4(&m_worldRotateMatrix) * 
		XMLoadFloat4x4(&m_worldTranslateMatrix)

		);

	return worldMatrix;

}

bool GameModel::Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShaderClass* colorShader, TextureShaderClass* textureShader){
	
	//Render the model on the device context using the colorShader or textureShader as appropriate
	
	return false; //subclasses must implement this method

}


XMFLOAT4X4 GameModel::GetWorldRotateMatrix(){
	return m_worldRotateMatrix;
}

void GameModel::orientRotateX(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_orientRotateMatrix, XMLoadFloat4x4(&m_orientRotateMatrix) * XMMatrixRotationX(radianAngle));

}
void GameModel::orientRotateY(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_orientRotateMatrix, XMLoadFloat4x4(&m_orientRotateMatrix) * XMMatrixRotationY(radianAngle));

}
void GameModel::orientRotateZ(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_orientRotateMatrix, XMLoadFloat4x4(&m_orientRotateMatrix) * XMMatrixRotationZ(radianAngle));

}

void GameModel::orientTranslate(float deltaX, float deltaY, float deltaZ){
		XMStoreFloat4x4(&m_orientTranslateMatrix, XMLoadFloat4x4(&m_orientTranslateMatrix) * XMMatrixTranslation(deltaX, deltaY, deltaZ));

}

void GameModel::worldRotateX(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_worldRotateMatrix, XMLoadFloat4x4(&m_worldRotateMatrix) * XMMatrixRotationX(radianAngle));

}
void GameModel::worldRotateY(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_worldRotateMatrix, XMLoadFloat4x4(&m_worldRotateMatrix) * XMMatrixRotationY(radianAngle));

}
void GameModel::worldRotateZ(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_worldRotateMatrix, XMLoadFloat4x4(&m_worldRotateMatrix) * XMMatrixRotationZ(radianAngle));

}

void GameModel::worldTranslate(float deltaX, float deltaY, float deltaZ){
		XMStoreFloat4x4(&m_worldTranslateMatrix, XMLoadFloat4x4(&m_worldTranslateMatrix) * XMMatrixTranslation(deltaX, deltaY, deltaZ));

}





//User Control Moved Methods

void GameModel::MoveLeft()
{
	worldTranslate(-TRANSLATION_INCREMENT, 0.0f, 0.0f);
}

void GameModel::MoveRight()
{
	worldTranslate(TRANSLATION_INCREMENT, 0, 0);
}

void GameModel::MoveUp()
{
	worldTranslate(0.0f, TRANSLATION_INCREMENT, 0.0f);
}

void GameModel::MoveDown()
{
	worldTranslate(0.0f, -TRANSLATION_INCREMENT, 0.0f);
}

void GameModel::RotateLeft()
{
	orientRotateY(-XM_PIDIV4*ROTATION_SPEED);
}

void GameModel::RotateRight()
{
	orientRotateY(XM_PIDIV4*ROTATION_SPEED);

}