#include "gamemodel.h"
#include "modelclass.h"
#include "airplanemodel.h"
#include "arraylist.h"

/*
This class represents a simple airplane model built out of cube and prism game model components
It can be moved forward in the direction it is facing and turned left or right.

Exercise: it would be cool if it actually banked while turning.
How would you do this?
*/
AirPlaneModel::AirPlaneModel()
{
	m_Fuselage = 0;
	m_PontoonLeft = 0;
	m_PontoonRight = 0;
	m_Wing = 0;
	m_Propeller = 0;
	m_StrutFrontLeft = 0; 
	m_StrutBackLeft = 0; 
	m_StrutFrontRight = 0; 
	m_StrutBackRight =0; 

	//direction plane is facing as constructed in the model co-ordinates
    m_directionVector = XMFLOAT3(1.0f,0.0f,0.0f); //face in positive X direction

	InitializeModel();
}

AirPlaneModel::~AirPlaneModel(void)
{ 
	Shutdown();
}

ArrayList<GameModel> AirPlaneModel::GetGameModels(){

	//Provide an arraylist of simple GameModel components that make up this airplane
	//These will be given to the GraphicsClass object to render using the graphics pipeline

	ArrayList<GameModel> list;

	list.add(m_Fuselage);
	list.add(m_PontoonLeft);
	list.add(m_PontoonRight);
	list.add(m_Wing);
	list.add(m_Propeller);
	list.add(m_StrutFrontLeft);
	list.add(m_StrutBackLeft);
	list.add(m_StrutFrontRight);
	list.add(m_StrutBackRight);


	return list;
}


void AirPlaneModel::InitializeModel()
{

	/*
	Create the airplane out of simple CubeModel and PrismModel parts
	*/

	//Define dimensions of parts of the plane so they can easily be changed in one place

	float fuselageLength = 4.0f; //length of body of plane
	float fuselageRadius = fuselageLength/6.0f; //radius of plane's body
	//float fuselageRadius = 1.0f; //radius of plane's body
	float wingSpan = fuselageLength;
	float wingWidth = fuselageRadius * 2;
	float wingThickness = 0.2f;
	float propellerLength = fuselageRadius * 3.0f;
	float propellerWidth = fuselageRadius * 0.5f;
	float propellerThickness = 0.1f;;

	//fuselage colours
	XMFLOAT4 prismColors[] = {
	    XMFLOAT4(230.0f/255, 0.0f, 0.0f, 1.0f), //prism faces red1
	    XMFLOAT4(204.0f/255, 0.0f, 0.0f, 1.0f), //prism ends red2
	};

    WCHAR * fuselageTextureFiles[] = {
		 L"../Engine/textures/dietCokeCanSide.dds",
		 L"../Engine/textures/cokeCanTop.dds",
		 L"../Engine/textures/cokeCanBottom.dds",
	};


	m_Fuselage = new PrismTexturedModel( fuselageLength,  //height
							     fuselageRadius,  //radius
							     24,      //number of faces
							     fuselageTextureFiles //prism texture files
							    ); 

    m_Fuselage->orientRotateZ(XM_PIDIV2); //orient fuselage along X axis
    m_directionVector = XMFLOAT3(1.0f,0.0f,0.0f); //plane is facing in positive X direction

    WCHAR * pontoonTextureFiles[] = {
		 L"../Engine/textures/toblerone.dds",
		 L"../Engine/textures/tobleroneEnd.dds",
		 L"../Engine/textures/tobleroneEnd.dds",
	};


	m_PontoonLeft = new PrismTexturedModel( fuselageLength*2/3,  //height
							     fuselageRadius*5/8,  //radius
							     3,      //number of faces
							     pontoonTextureFiles //prism texture files
							    ); 

    m_PontoonLeft->orientRotateZ(XM_PIDIV2); //orient fuselage along X axis
	m_PontoonLeft->orientTranslate(fuselageRadius/4, -fuselageRadius*2, fuselageRadius*4/3);

	m_PontoonRight = new PrismTexturedModel( fuselageLength*2/3,  //height
							     fuselageRadius*5/8,  //radius
							     3,      //number of faces
							     pontoonTextureFiles //prism texture files
							    ); 

    m_PontoonRight->orientRotateZ(XM_PIDIV2); //orient fuselage along X axis
	m_PontoonRight->orientTranslate(fuselageRadius/4, -fuselageRadius*2, -fuselageRadius*4/3);

    WCHAR * strutTextureFiles[] = {
		 L"../Engine/textures/penciltexture.dds",
		 L"../Engine/textures/tobleroneEnd.dds",
		 L"../Engine/textures/tobleroneEnd.dds",
	};

	float strutLength = fuselageRadius*2;
	float strutRadius = fuselageRadius/6;

	m_StrutFrontLeft = new PrismTexturedModel( strutLength, strutRadius, 8,  strutTextureFiles ); 
	m_StrutBackLeft = new PrismTexturedModel( strutLength, strutRadius, 8,  strutTextureFiles ); 
	m_StrutFrontRight = new PrismTexturedModel( strutLength, strutRadius, 8,  strutTextureFiles ); 
	m_StrutBackRight = new PrismTexturedModel( strutLength, strutRadius, 8,  strutTextureFiles ); 


    m_StrutFrontLeft->orientRotateX(XM_PIDIV4);
    m_StrutFrontLeft->orientTranslate(fuselageRadius/4 + wingWidth / 3, -fuselageRadius*3/2, -wingWidth * 6 / 16);
    m_StrutBackLeft->orientRotateX(XM_PIDIV4);
    m_StrutBackLeft->orientTranslate(fuselageRadius/4 - wingWidth / 3, -fuselageRadius*3/2, -wingWidth * 6 / 16);
    m_StrutFrontRight->orientRotateX(-XM_PIDIV4);
    m_StrutFrontRight->orientTranslate(fuselageRadius/4 + wingWidth / 3, -fuselageRadius*3/2, wingWidth * 6 / 16);
    m_StrutBackRight->orientRotateX(-XM_PIDIV4);
    m_StrutBackRight->orientTranslate(fuselageRadius/4 - wingWidth / 3, -fuselageRadius*3/2, wingWidth * 6 / 16);



	XMFLOAT4 wingColors[] = {
	    XMFLOAT4(153.0f/255, 76.0f/255, 0.0f, 1.0f), //front face brown1
	    XMFLOAT4(153.0f/255, 76.0f/255, 0.0f, 1.0f), //back face brown1
	    XMFLOAT4(204.0f/255, 102.0f/255, 0.0f, 1.0f), //right side brown2
	    XMFLOAT4(204.0f/255, 102.0f/255, 0.0f, 1.0f), //left side brown2
	    XMFLOAT4(255.0f/255, 128.0f/255, 0.0f, 1.0f), //top face brown3
	    XMFLOAT4(255.0f/255, 128.0f/255, 0.0f, 1.0f), //bottom face brown3
	};

    WCHAR * wingTextureFileNames[] = {
		 L"../Engine/textures/wood_texture.dds", 
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/wood_texture.dds",
		 L"../Engine/textures/end_grain.dds",
		 L"../Engine/textures/end_grain.dds",
	};

	//Create Wing of airplane
	m_Wing = new CubeTexturedModel(  wingWidth,  //width of wing
							 wingSpan,  //wing span
							 wingThickness, //thickness of wing
							 wingTextureFileNames //face texture files
							 );

	//position wing relative to the fuselage
	m_Wing->orientRotateX(XM_PIDIV2);
	m_Wing->orientTranslate(fuselageRadius/4, fuselageRadius, 0.0f);

	//Create propeller of airplane
	m_Propeller = new CubeTexturedModel( propellerThickness,  //length in X direction
							     propellerLength,  //length in Y direction
							     propellerWidth, //length in Z direction
							     wingTextureFileNames //face texture files
							    );

	//position plane relative to fuselage
	m_Propeller->orientTranslate(fuselageLength/2 + 0.2f, 0.0f, 0.0f);


}

void AirPlaneModel::Advance(){
	//Advance moving parts of the plane
	//This method should be called on a per-frame basis
	
	//Spin the propeller
	float propellerRadianAngularIncrement = -XM_PIDIV4/5; //sign changes direction of the propeller
	m_Propeller->orientRotateX(propellerRadianAngularIncrement);
}

void AirPlaneModel::MoveForward(){

	  //Move the airplane in the direction it is facing based on its
	  //direction vector and the speed factor which can be adjusted for smooth motion

	  XMFLOAT3 effectiveDirectionVector;
	  XMFLOAT4X4 fuselageDirectionMatrix = m_Fuselage->GetWorldRotateMatrix();
      XMStoreFloat3( &effectiveDirectionVector,  XMVector3Transform( XMLoadFloat3(&m_directionVector), XMLoadFloat4x4(&fuselageDirectionMatrix) ));

	  float deltaX = effectiveDirectionVector.x*AIRPLANE_FORWARD_SPEED_FACTOR;
	  float deltaY = effectiveDirectionVector.y*AIRPLANE_FORWARD_SPEED_FACTOR;
	  float deltaZ = effectiveDirectionVector.z*AIRPLANE_FORWARD_SPEED_FACTOR;

	  //Move all the  component parts of the airplane relative to the world
	  //co-ordinate system

	  m_Fuselage->worldTranslate(deltaX, deltaY, deltaZ);
	  m_Wing->worldTranslate(deltaX, deltaY, deltaZ);
	  m_Propeller->worldTranslate(deltaX, deltaY, deltaZ);
      m_PontoonLeft->worldTranslate(deltaX, deltaY, deltaZ);
      m_PontoonRight->worldTranslate(deltaX, deltaY, deltaZ);
     
	  m_StrutFrontLeft->worldTranslate(deltaX, deltaY, deltaZ);
      m_StrutFrontRight->worldTranslate(deltaX, deltaY, deltaZ);
      m_StrutBackLeft->worldTranslate(deltaX, deltaY, deltaZ);
      m_StrutBackRight->worldTranslate(deltaX, deltaY, deltaZ);

}


void AirPlaneModel::TurnLeft(){
	
	//Rotate, or Yaw, the plane about the Y axis

	float rotationRadianAngle = -XM_PIDIV4/40;
	m_Fuselage->worldRotateY(rotationRadianAngle);
	m_Wing->worldRotateY(rotationRadianAngle);
	m_Propeller->worldRotateY(rotationRadianAngle);
	m_PontoonLeft->worldRotateY(rotationRadianAngle);
	m_PontoonRight->worldRotateY(rotationRadianAngle);

	m_StrutFrontLeft->worldRotateY(rotationRadianAngle);
    m_StrutFrontRight->worldRotateY(rotationRadianAngle);
    m_StrutBackLeft->worldRotateY(rotationRadianAngle);
    m_StrutBackRight->worldRotateY(rotationRadianAngle);

}
void AirPlaneModel::TurnRight(){

	//Rotate, or Yaw, the plane about the Y axis

	float rotationRadianAngle = XM_PIDIV4/40;
	m_Fuselage->worldRotateY(rotationRadianAngle);
	m_Wing->worldRotateY(rotationRadianAngle);
	m_Propeller->worldRotateY(rotationRadianAngle);
	m_PontoonLeft->worldRotateY(rotationRadianAngle);
	m_PontoonRight->worldRotateY(rotationRadianAngle);

	m_StrutFrontLeft->worldRotateY(rotationRadianAngle);
    m_StrutFrontRight->worldRotateY(rotationRadianAngle);
    m_StrutBackLeft->worldRotateY(rotationRadianAngle);
    m_StrutBackRight->worldRotateY(rotationRadianAngle);

}



void AirPlaneModel::Shutdown()
{
	//Release the memory of the component parts of the airplane

	if(m_Fuselage)
	{
		delete m_Fuselage;
		m_Fuselage = 0;
	}

	if(m_PontoonLeft)
	{
		delete m_PontoonLeft;
		m_PontoonLeft = 0;
	}

	if(m_PontoonRight)
	{
		delete m_PontoonRight;
		m_PontoonRight = 0;
	}

	if(m_StrutFrontLeft)
	{
		delete m_StrutFrontLeft;
		m_StrutFrontLeft = 0;
	}

	if(m_StrutFrontRight)
	{
		delete m_StrutFrontRight;
		m_StrutFrontRight = 0;
	}

	if(m_StrutBackLeft)
	{
		delete m_StrutBackLeft;
		m_StrutBackLeft = 0;
	}

	if(m_StrutBackRight)
	{
		delete m_StrutBackRight;
		m_StrutBackRight = 0;
	}


	if(m_Wing)
	{
		delete m_Wing;
		m_Wing = 0;
	}

	if(m_Propeller)
	{
	  delete m_Propeller;
	  m_Propeller = 0;
	}


}
