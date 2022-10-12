#include "KMapObject.h"

bool KMapObject::Frame()
{
    return true;
}

bool KMapObject::Render()
{
    
    PreRender();
    PostRender();

    return true;
}
