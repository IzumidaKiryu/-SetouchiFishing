#include "k2EngineLowPreCompile.h"
#include "Right.h"

namespace nsK2EngineLow{
Right::~Right()
{
}

void Right::Init()
{
	DirectionLight directionLig;
	SpotLight  spotLig;
	directionLig.d_direction.x = 1.0f;
	directionLig.d_direction.y = -1.0f;
	directionLig.d_direction.z = -1.0f;

	//���K������B
	directionLig.d_direction.Normalize();
	
	//���C�g�̃J���[�̐ݒ�B
	directionLig.d_color.x = 0.5f;
	directionLig.d_color.y = 0.5f;
	directionLig.d_color.z = 0.5f;
}


void Right::Update()
{
}
}