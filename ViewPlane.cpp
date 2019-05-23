 /*#include "ViewPlane.h"


ViewPlane::ViewPlane()
{
       s = 1.0;
       hres = 600;
       vres = 400;
}
ViewPlane:: ViewPlane(int v_hres, int v_vres, double v_s)
{
    hres=v_hres;
    vres=v_vres;
    s=v_s;
}*/
#include "ViewPlane.h"

ViewPlane::ViewPlane():hres(400), vres(400), s(1.0)
{}
ViewPlane::ViewPlane(int v_hres, int v_vres, double v_s): hres(v_hres), vres(v_vres), s(v_s)
{}
