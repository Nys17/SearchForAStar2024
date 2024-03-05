#include "IGraphics.h"
#include "ITexture.h"
#include "IShader.h"
#include "IRenderable.h"


IGraphics::IGraphics() : Renderables()
{
}

IGraphics::~IGraphics()
{
    for (auto bucket = Renderables.begin(); bucket != Renderables.end(); ++bucket)
    {
        for (auto renderable = bucket->second.begin(); renderable != bucket->second.end(); ++renderable)
        {
            delete (*renderable);
        }
        
        delete bucket->first;
    }

    Renderables.clear();

    for (auto texture = Textures.begin(); texture != Textures.end(); ++texture)
    {
        delete (*texture);
    }

    Textures.clear();
}
void IGraphics::DeleteRenderable(IRenderable* render)
{
    delete(&render);
}

void IGraphics::DeleteTexture(ITexture* texture)
{
    delete(&texture);
}

std::map<IShader*, std::list<IRenderable*> > &IGraphics::GetRendarables()
{
    return Renderables;
}

void IGraphics::ClearRendarables()
{
    Renderables.clear();
}


std::list<ITexture*> &IGraphics::GetTextures()
{
    return Textures;
}

void IGraphics::ClearTextures()
{
    Textures.clear();
}

void IGraphics::DeleteNumbers(IShader* key, IRenderable* render) /// does not work yet
{
    
    delete(&render);
    Renderables.erase(key);
}


