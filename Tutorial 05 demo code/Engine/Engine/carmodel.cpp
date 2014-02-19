#include "gamemodel.h"
#include "modelclass.h"
#include "carmodel.h"
#include "arraylist.h"

/*
This class represents a simple airplane model built out of cube and prism game model components
It can be moved forward in the direction it is facing and turned left or right.

Exercise: it would be cool if it actually banked while turning.
How would you do this?
*/
CarModel::CarModel()
{
	m_WheelFL = 0;
	m_WheelFR = 0;
	m_WheelBL = 0;
	m_WheelBR = 0;
	m_Body = 0;

	//direction plane is facing as constructed in the model co-ordinates
    m_directionVector = XMFLOAT3(1.0f,0.0f,0.0f); //face in positive X direction

	InitializeModel();
}

CarModel::~CarModel(void)
{ 
	Shutdown();
}

ArrayList<GameModel> CarModel::GetGameModels(){

	//Provide an arraylist of simple GameModel components that make up this airplane
	//These will be given to the GraphicsClass object to render using the graphics pipeline

	ArrayList<GameModel> list;
	list.add(m_WheelFL);
	list.add(m_WheelFR);
	list.add(m_WheelBL);
	list.add(m_WheelBR);
	list.add(m_Body);

	return list;
}


void CarModel::InitializeModel()
{

	/*
	Create the airplane out of simple CubeModel and PrismModel parts
	*/

	//Define dimensions of parts of the plane so they can easily be changed in one place

	float bodyLength = 4.0f; //length of body of plane
	float bodyWidth = bodyLength/2; //radius of plane's body
	float bodyThickness = bodyWidth/2;
	float wheelLength = 0.5f;
	float wheelRadius = 0.5f;



	XMFLOAT4 prismColors2[] = {
	    XMFLOAT4(100.0f/255, 100.0f/255, 100.0f/255, 1.0f), //prism faces red1
	    XMFLOAT4(50.0f/255, 50.0f/255, 50.0f/255, 1.0f), //prism ends red2
	};

	m_WheelFL = new PrismModel( wheelLength,  //height
							     wheelRadius,  //radius
							     12,      //number of faces
							     prismColors2 //side and end colours 
							    ); 

    m_WheelFL->orientRotateX(XM_PIDIV2); //orient bomb along X axis
	m_WheelFL->orientTranslate(2*bodyWidth/3, -bodyThickness/2, 1.0f);

	m_WheelFR = new PrismModel( wheelLength,  //height
							     wheelRadius,  //radius
							     12,      //number of faces
							     prismColors2 //side and end colours 
							    ); 

    m_WheelFR->orientRotateX(XM_PIDIV2); //orient bomb along X axis
	m_WheelFR->orientTranslate(2*bodyWidth/3, -bodyThickness/2, -1.0f);

	m_WheelBL = new PrismModel( wheelLength,  //height
							     wheelRadius,  //radius
							     12,      //number of faces
							     prismColors2 //side and end colours 
							    ); 

    m_WheelBL->orientRotateX(XM_PIDIV2); //orient bomb along X axis
	m_WheelBL->orientTranslate(-2*bodyWidth/3, -bodyThickness/2, 1.0f);

	m_WheelBR = new PrismModel( wheelLength,  //height
							     wheelRadius,  //radius
							     12,      //number of faces
							     prismColors2 //side and end colours 
							    ); 

    m_WheelBR->orientRotateX(XM_PIDIV2); //orient bomb along X axis
	m_WheelBR->orientTranslate(-2*bodyWidth/3, -bodyThickness/2, -1.0f);

   // m_directionVector = XMFLOAT3(1.0f,0.0f,0.0f); //plane is facing in positive X directio



	XMFLOAT4 bodyColors[] = {
	    XMFLOAT4(153.0f/255, 76.0f/255, 0.0f, 1.0f), //front face brown1
	    XMFLOAT4(153.0f/255, 76.0f/255, 0.0f, 1.0f), //back face brown1
	    XMFLOAT4(204.0f/255, 102.0f/255, 0.0f, 1.0f), //right side brown2
	    XMFLOAT4(204.0f/255, 102.0f/255, 0.0f, 1.0f), //left side brown2
	    XMFLOAT4(255.0f/255, 128.0f/255, 0.0f, 1.0f), //top face brown3
	    XMFLOAT4(255.0f/255, 128.0f/255, 0.0f, 1.0f), //bottom face brown3
	};

	//Create Wing of airplane
	m_Body= new CubeModel(  bodyLength,  //width of wing
							bodyWidth,  //wing span
							bodyThickness, //thickness of wing
							 bodyColors //XMFLOAT4[6] with face colours
							 );

	m_Body->orientRotateX(XM_PIDIV2);
	m_directionVector = XMFLOAT3(1.0f,0.0f,0.0f); //plane is facing in positive X directio



}

void CarModel::Advance(){
	//Advance moving parts of the plane
	//This method should be called on a per-frame basis
	
	
}

void CarModel::MoveForward(){

	  //Move the airplane in the direction it is facing based on its
	  //direction vector and the speed factor which can be adjusted for smooth motion

	  XMFLOAT3 effectiveDirectionVector;
	  XMFLOAT4X4 fuselageDirectionMatrix = m_Body->GetWorldRotateMatrix();
      XMStoreFloat3( &effectiveDirectionVector,  XMVector3Transform( XMLoadFloat3(&m_directionVector), XMLoadFloat4x4(&fuselageDirectionMatrix) ));

	  float deltaX = effectiveDirectionVector.x*CAR_FORWARD_SPEED_FACTOR;
	  float deltaY = effectiveDirectionVector.y*CAR_FORWARD_SPEED_FACTOR;
	  float deltaZ = effectiveDirectionVector.z*CAR_FORWARD_SPEED_FACTOR;

	  //Move all the  component parts of the airplane relative to the world
	  //co-ordinate system

	  m_Body->worldTranslate(deltaX, deltaY, deltaZ);
	  m_WheelFL->worldTranslate(deltaX, deltaY, deltaZ);
	   m_WheelFR->worldTranslate(deltaX, deltaY, deltaZ);
	    m_WheelBL->worldTranslate(deltaX, deltaY, deltaZ);
		 m_WheelBR->worldTranslate(deltaX, deltaY, deltaZ);
	  //Spin the wheels
	float wheelRadianAngularIncrement = -XM_PIDIV4/5; //sign changes direction of the propeller
	m_WheelFL->orientRotateZ(wheelRadianAngularIncrement);
	m_WheelFR->orientRotateZ(wheelRadianAngularIncrement);
	m_WheelBL->orientRotateZ(wheelRadianAngularIncrement);
	m_WheelBR->orientRotateZ(wheelRadianAngularIncrement);
}

void CarModel::MoveBackward(){

	  //Move the airplane in the direction it is facing based on its
	  //direction vector and the speed factor which can be adjusted for smooth motion

	  XMFLOAT3 effectiveDirectionVector;
	  XMFLOAT4X4 fuselageDirectionMatrix = m_Body->GetWorldRotateMatrix();
      XMStoreFloat3( &effectiveDirectionVector,  XMVector3Transform( XMLoadFloat3(&m_directionVector), XMLoadFloat4x4(&fuselageDirectionMatrix) ));

	  float deltaX = -effectiveDirectionVector.x*CAR_FORWARD_SPEED_FACTOR;
	  float deltaY = -effectiveDirectionVector.y*CAR_FORWARD_SPEED_FACTOR;
	  float deltaZ = -effectiveDirectionVector.z*CAR_FORWARD_SPEED_FACTOR;

	  //Move all the  component parts of the airplane relative to the world
	  //co-ordinate system

	  m_Body->worldTranslate(deltaX, deltaY, deltaZ);
	  m_WheelFL->worldTranslate(deltaX, deltaY, deltaZ);
	   m_WheelFR->worldTranslate(deltaX, deltaY, deltaZ);
	    m_WheelBL->worldTranslate(deltaX, deltaY, deltaZ);
		 m_WheelBR->worldTranslate(deltaX, deltaY, deltaZ);
	  //Spin the wheels
	float wheelRadianAngularIncrement = XM_PIDIV4/5; //sign changes direction of the propeller
	m_WheelFL->orientRotateZ(wheelRadianAngularIncrement);
	m_WheelFR->orientRotateZ(wheelRadianAngularIncrement);
	m_WheelBL->orientRotateZ(wheelRadianAngularIncrement);
	m_WheelBR->orientRotateZ(wheelRadianAngularIncrement);
}
void CarModel::TurnLeft(){
	
	//Rotate, or Yaw, the plane about the Y axis

	float rotationRadianAngle = -XM_PIDIV4/60;
	m_Body->worldRotateY(rotationRadianAngle);
	m_WheelFL->worldRotateY(rotationRadianAngle);
	m_WheelFR->worldRotateY(rotationRadianAngle);
	m_WheelBL->worldRotateY(rotationRadianAngle);
	m_WheelBR->worldRotateY(rotationRadianAngle);
	


}
void CarModel::TurnRight(){

	//Rotate, or Yaw, the plane about the Y axis

	float rotationRadianAngle = XM_PIDIV4/60;
	m_Body->worldRotateY(rotationRadianAngle);
	m_WheelFL->worldRotateY(rotationRadianAngle);
	m_WheelFR->worldRotateY(rotationRadianAngle);
	m_WheelBL->worldRotateY(rotationRadianAngle);
	m_WheelBR->worldRotateY(rotationRadianAngle);
	

}



void CarModel::Shutdown()
{
	//Release the memory of the component parts of the airplane

	if(m_Body)
	{
		delete m_Body;
		m_Body = 0;
	}

	if(m_WheelFL)
	{
		delete m_WheelFL;
		m_WheelFL = 0;
	}

	if(m_WheelFR)
	{
		delete m_WheelFR;
		m_WheelFR = 0;
	}

	if(m_WheelBL)
	{
		delete m_WheelBL;
		m_WheelBL = 0;
	}

	if(m_WheelBR)
	{
		delete m_WheelBR;
		m_WheelBR = 0;
	}
}
