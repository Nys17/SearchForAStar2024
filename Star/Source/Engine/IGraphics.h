
#pragma once

#include <map>
#include <list>

class IRenderable;
class IShader;
class ITexture;

class IGraphics
{
public:

	IGraphics();
	virtual ~IGraphics();

	virtual void Update() = 0;
	virtual bool IsValid() = 0;

	virtual ITexture* CreateTexture(const wchar_t* filepath) = 0;
	virtual IShader* CreateShader(const wchar_t* filepath, const char* vsentry, const char* vsshader, const char* psentry, const char* psshader, ITexture* TextureIn) = 0;
	virtual IRenderable* CreateBillboard(IShader* ShaderIn) = 0;
	std::map<IShader*, std::list<IRenderable*> >& RenderablesRef{Renderables}; // ref to renderables
	std::list<ITexture*>& TexturesRef{Textures};// ref to textures

	/// add void for deleting textures
	void DeleteRenderable(IRenderable* render);
	void DeleteTexture(ITexture* texture);
	std::map<IShader*, std::list<IRenderable*> > &GetRendarables();
	void ClearRendarables();
	std::list<ITexture*> &GetTextures();
	void ClearTextures();
	void DeleteNumbers(IShader* key, IRenderable* render);
protected:

	std::map<IShader*, std::list<IRenderable*> > Renderables;
	std::list<ITexture*> Textures;

};

