#pragma once
#include "Engine/IApplication.h"

class IGraphics;
class ITexture;
class IShader;
class IRenderable;
#include <vector>

enum NumberForArray {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, NumOfNumbers};
class RenderNumbers : public IApplication
{
public:
	RenderNumbers(IGraphics* Graphics, IInput* Input); /// input is added as it is required by iapplication it won't be used
	~RenderNumbers();
	virtual bool Load();
	void RenderTheNumbers(int FirstNumber, int SecondNumber, float xAxisOffest, float yAxisOffest, IRenderable* LocationBase);/// mayube insead of the floats add irendareble location and use its location as base on where to get numbers-> setpos(renderTarget->GetPosX(), renderTarget->GetPosY())
	void RenderSingleDigitNumber(int Number,float xAxisOffest, float yAxisOffest, IRenderable* LocationBase);
	IRenderable* FirstNumberRender;
	IRenderable* SecondNumberRender;
	IRenderable* SingleDigitNumber;
protected:
	virtual bool IsValid();
	
	virtual void Update();
	virtual void Cleanup();
	ITexture* RenderedNumberTexture[NumOfNumbers];
	IShader* RenderedNumberShader[NumOfNumbers];
};

