////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////

//#include <iostream>
#include <sstream>   // for wostringstream

#include "graphicsclass.h"



GraphicsClass::GraphicsClass()
{

	//Set all member pointers to zero for safety
	m_D3D = 0;
	m_Camera = 0;

	m_axis = 0;
    m_AxisModel = 0;

	m_ColorShader = 0;
	m_TextureShader = 0;

	m_GameWorldModels = 0;




}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}



bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, CineCameraClass* camera, ArrayList<GameModel>* gameModels)
{
	bool result;

	m_hwnd = hwnd; //handle to the windows window

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}


	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}




	// keep a local pointer to the camera object.
	m_Camera = camera;
	if(!m_Camera)
	{
		return false;
	}

	m_axis = new XYZaxis; //create orgin axis object to display co-ord system (mostly for debug)
	if(!m_axis)
	{
		return false;
	}
	m_axis->Initialize();

	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f); 
	



    // Create A model for the axis
	m_AxisModel = new ModelClass(m_axis->GetVertices(), 
										m_axis->GetVertexCount(), 
										m_axis->GetIndices(), 
										m_axis->GetIndexCount(), 
										D3D11_PRIMITIVE_TOPOLOGY_LINELIST);



	m_GameWorldModels = gameModels;

	if(m_GameWorldModels && !m_GameWorldModels->isEmpty()){
		for(int i=0; i< m_GameWorldModels->size(); i++){
			GameModel* gameModel = m_GameWorldModels->elementAt(i);
			//result = gameModel->GetVertexModel()->Initialize(m_D3D->GetDevice());			
			result = gameModel->InitializeVertexModels(m_D3D->GetDevice()); //initialize the models for this graphics device
	        if(!result)
	        {
		       MessageBox(hwnd, L"Could not initialize the game model object.", L"Error", MB_OK);
		       return false;
	        }
			/*
			if(gameModel->isTextureVertexModel()){
				result = gameModel->initializeTextures(m_D3D->GetDevice());
	            if(!result)
	            {
		            MessageBox(hwnd, L"Could not initialize the game model textures.", L"Error", MB_OK);
		            return false;
	            }

			}
			*/


		}
	}



	result = m_AxisModel->Initialize(m_D3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the axis model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the axis object.
	if(m_axis)
	{
		m_axis->Shutdown();
		delete m_axis;
		m_axis = 0;
	}

	if(m_AxisModel){
	    m_AxisModel->Shutdown();
		delete m_AxisModel;
		m_AxisModel = 0;

	}


	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;


	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{
	// Update our time	
	static float t = 0.0f;
	static float previous_t = 0.0f;
	static int sampleCount = 0;
	static float sampleStartTime = 0.0f;
	 //std::wostringstream temp;

    static DWORD dwTimeStart = 0;

    DWORD dwTimeCur = GetTickCount();
    if( dwTimeStart == 0 ) dwTimeStart = dwTimeCur;
	previous_t = t;
	t = ( dwTimeCur - dwTimeStart ) / 1000.0f; //elapsed time in seconds
	if(t -sampleStartTime > 1.0){
		//produce FPS stats every second
		sampleCount++;
		float averageFramePeriod = (t-sampleStartTime)/sampleCount;
		sampleCount = 0;
		sampleStartTime = t;


		//Write Framestats on Window title caption
		std::wostringstream captionStrm;
		captionStrm << L"FPS: " << (int)(1.0f/averageFramePeriod) << L" ";
        SetWindowText( m_hwnd, captionStrm.str().c_str() ); //use FPS stats as title caption to windows window.

	}
	else{
		sampleCount++;
	}



	// Matrices
	XMFLOAT4X4 axisWorld;
	XMFLOAT4X4 viewMatrix, projectionMatrix;

	// Initialize matrices to Identity matrices
	
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f); //R,G,B,A values for background (Opaque Black)

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the view and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_Camera->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetWorldMatrix(axisWorld); //set to identity matrix


	if(m_GameWorldModels && !m_GameWorldModels->isEmpty())

		for(int i=0; i< m_GameWorldModels->size(); i++){
			GameModel* gameModel = m_GameWorldModels->elementAt(i);

		   // Provide the game models with a graphics device context,
		   // view and projection matrices, and
		   // shaders and ask them to render themselves

		  result = gameModel->Render(m_D3D->GetDeviceContext(), 
								          viewMatrix, 
								          projectionMatrix,
										  m_ColorShader,
										  m_TextureShader); 
	
	       if(!result) {return false;}
 

	}
 

	// Set up the model for axis scale

	m_AxisModel->Render(m_D3D->GetDeviceContext());
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_AxisModel->GetIndexCount(), axisWorld, viewMatrix, projectionMatrix);
	
	if(!result)
	{
		return false;
	}


    // Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}

