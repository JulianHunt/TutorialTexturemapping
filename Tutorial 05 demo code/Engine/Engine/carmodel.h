#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "modelclass.h"
#include "gamemodel.h"
#include "cubemodel.h"
#include "prismmodel.h"
#include "conemodel.h"
#include "arraylist.h"


#include <string>

using namespace DirectX;

const float CAR_FORWARD_SPEED_FACTOR = 0.1f; //adjust this to make forward motion look good

class CarModel
{
public:
	CarModel();
	virtual ~CarModel(void);
	virtual void Shutdown(); //release airplane component memory
	ArrayList<GameModel> GetGameModels(); //provide a list of simple components of the airplane

	//Motion control of plane
	//To be called on a per frame basis to alter motion of plane

	void TurnLeft();
	void TurnRight();
	void MoveForward();
	void MoveBackward();
	void Advance();

protected:
	virtual void InitializeModel(); //construct the airplane from component parts

private:
	
	PrismModel* m_WheelFL; //body of airplane
	PrismModel* m_WheelFR; //body of airplane
	PrismModel* m_WheelBL; //body of airplane
	PrismModel* m_WheelBR; //body of airplane
	CubeModel* m_Body; //wings of airplane
	
	

	XMFLOAT3 m_directionVector; //direction plane is facing when constructed
};

