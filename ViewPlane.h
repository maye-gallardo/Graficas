#ifndef VIEWPLANE_H
#define VIEWPLANE_H

class ViewPlane
{
    public:
        ViewPlane();
        ViewPlane(int v_hres, int v_vres, double v_s);
        
    public:
        float s;
        int hres;
        int vres;
};

#endif