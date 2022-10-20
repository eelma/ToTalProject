#include "KShape.h"

void KShapeBox::CreateVertexData()
{
	m_VertexList.resize(24);//p = position, c = color, t



}

void KShapeBox::CreateIndexData()
{


}

bool KShapeBox::Frame()
{
	return true;
}

bool KShapeBox::Render()
{

	PreRender();
	PostRender();
	
	return true;
}
