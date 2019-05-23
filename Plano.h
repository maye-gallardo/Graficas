#ifndef PLANO_H
#define PLANO_H
#include "ObjetoGeometrico.h"
#include "ColorRGB.h"
#include "Image.h"
#include <math.h>
class Plano : public ObjetoGeometrico
{
    public:
    Plano(Punto3D, Vector3D);
    bool hayImpacto(const Rayo& rayo, double& t, Vector3D& n, Punto3D& q ) const;
    ColorRGB obtenerColor();
    void establecerColor(double, double, double);

    ColorRGB obtenerColorTextura(double u,double v);
    void establecerTextura(Image& img);
    double calcularU(Vector3D& n);
    double calcularV(Vector3D& n);
    bool tieneTextura();

    Punto3D p;
    Vector3D n;
    ColorRGB color;
    Image img;
    bool textura;

};
#endif