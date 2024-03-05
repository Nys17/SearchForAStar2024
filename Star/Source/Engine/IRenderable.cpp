#include "IRenderable.h"

const Transform2D& IRenderable::GetTransform() const
{
	return Transform;
}

void IRenderable::SetPosition(float x, float y)
{
	Transform.PositionX = x;
	Transform.PositionY = y;
}

void IRenderable::SetRotation(float r)
{
	Transform.Rotation = r;
}

void IRenderable::SetScale(float sx, float sy)
{
	Transform.ScaleX = sx;
	Transform.ScaleY = sy;
}

float IRenderable::GetScaleX()
{
	return Transform.ScaleX;
}

float IRenderable::GetScaleY()
{
	return Transform.ScaleY;
}

float IRenderable::GetPosX()
{
	return Transform.PositionX;
}

float IRenderable::GetPosY()
{
	return Transform.PositionY;

}

//void IRenderable::DeleteRenderable(IRenderable* render)
//{
//	delete(&render);
//}
