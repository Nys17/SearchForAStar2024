#include "RenderNumbers.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"

IApplication* RenderNumericals(IGraphics* Graphics, IInput* Input) {
	return new RenderNumbers(Graphics, Input);
}
RenderNumbers::RenderNumbers(IGraphics* GraphicsIn, IInput* InputIn) : IApplication(GraphicsIn, InputIn), FirstNumberRender(nullptr), SecondNumberRender(nullptr), RenderedNumberShader(), RenderedNumberTexture(),SingleDigitNumber(nullptr)
{

}

RenderNumbers::~RenderNumbers()
{
FirstNumberRender = NULL;
SecondNumberRender = NULL;
SingleDigitNumber = NULL;
for (size_t i = 0; i < 10; i++)
{
	RenderedNumberTexture[i] = NULL;
	RenderedNumberShader[i] = NULL;
}
}




bool RenderNumbers::IsValid()
{
	return true;
}

bool RenderNumbers::Load()
{
	RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Zero)] = Graphics->CreateTexture(L"Resource/Textures/Numbers/Zero.dds");
	RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::One)] = Graphics->CreateTexture(L"Resource/Textures/Numbers/One.dds");
	RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Two)] = Graphics->CreateTexture(L"Resource/Textures/Numbers/Two.dds");
	RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Three)] = Graphics->CreateTexture(L"Resource/Textures/Numbers/Three.dds");
	RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Four)] = Graphics->CreateTexture(L"Resource/Textures/Numbers/Four.dds");
	RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Five)] = Graphics->CreateTexture(L"Resource/Textures/Numbers/Five.dds");
	RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Six)] = Graphics->CreateTexture(L"Resource/Textures/Numbers/Six.dds");
	RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Seven)] = Graphics->CreateTexture(L"Resource/Textures/Numbers/Seven.dds");
	RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Eight)] = Graphics->CreateTexture(L"Resource/Textures/Numbers/Eight.dds");
	RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Nine)] = Graphics->CreateTexture(L"Resource/Textures/Numbers/Nine.dds");

	RenderedNumberShader[static_cast<unsigned int>(NumberForArray::Zero)] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Zero)]);
	RenderedNumberShader[static_cast<unsigned int>(NumberForArray::One)] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::One)]);
	RenderedNumberShader[static_cast<unsigned int>(NumberForArray::Two)] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Two)]);
	RenderedNumberShader[static_cast<unsigned int>(NumberForArray::Three)] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Three)]);
	RenderedNumberShader[static_cast<unsigned int>(NumberForArray::Four)] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Four)]);
	RenderedNumberShader[static_cast<unsigned int>(NumberForArray::Five)] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Five)]);
	RenderedNumberShader[static_cast<unsigned int>(NumberForArray::Six)] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Six)]);
	RenderedNumberShader[static_cast<unsigned int>(NumberForArray::Seven)] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Seven)]);
	RenderedNumberShader[static_cast<unsigned int>(NumberForArray::Eight)] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Eight)]);
	RenderedNumberShader[static_cast<unsigned int>(NumberForArray::Nine)] = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RenderedNumberTexture[static_cast<unsigned int>(NumberForArray::Nine)]);
		
		return true;
}

void RenderNumbers::RenderTheNumbers(int FirstNumber, int SecondNumber, float xAxisOffest, float yAxisOffest, IRenderable* LocationBase)
{
	
	FirstNumberRender = Graphics->CreateBillboard(RenderedNumberShader[FirstNumber]);
	FirstNumberRender->SetPosition(LocationBase->GetPosX() + xAxisOffest, LocationBase->GetPosY()+ yAxisOffest);

	SecondNumberRender= Graphics->CreateBillboard(RenderedNumberShader[SecondNumber]);
	SecondNumberRender->SetPosition(FirstNumberRender->GetPosX() + 40, FirstNumberRender->GetPosY() );

	
}

void RenderNumbers::RenderSingleDigitNumber(int Number, float xAxisOffest, float yAxisOffest, IRenderable* LocationBase)
{
	SingleDigitNumber = Graphics->CreateBillboard(RenderedNumberShader[Number]);
	SingleDigitNumber->SetPosition(LocationBase->GetPosX() + xAxisOffest, LocationBase->GetPosY() + yAxisOffest);
}

void RenderNumbers::Update()
{
}

void RenderNumbers::Cleanup()
{
}


