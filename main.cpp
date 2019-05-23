#include <vector>
#include <iostream>
#include "Triangulo.h"
#include "Vector3D.h"
#include "Plano.h"
#include "Esfera.h"
#include "ViewPlane.h"
#include "LuzPuntual.h"
#include "Utilitarios.h"
#include <algorithm> 
#include <math.h>
#include "Image.h"
using namespace std;

double acotar(double n)
{
    if ( n > 1.0)
    {
        return 1.0;
    }
    else
    {
        return n;
    }
}

ColorRGB obtenerColorPixel(const Rayo& r, vector<ObjetoGeometrico*> objetos, LuzPuntual luz, LuzPuntual luz_ambiente){
    
    ColorRGB color;

    color.r = 0.0;
    color.g = 0.0;
    color.b = 0.0;

    ColorRGB finalColor;
    finalColor.r=1.0;
    finalColor.g=1.0;
    finalColor.b=1.0;
    double u;
    double v;
    int column;
    int row;
    int px;
    double PI = 3.14159265358979323846;

    double t;
    double tmin = 2000000;    
    Vector3D n;
    Punto3D q;

    Vector3D h;
    for(int i = 0; i < objetos.size(); i++) {
        if( objetos[i]->hayImpacto(r, t, n, q) && t < tmin){
            u = objetos[i]->calcularU(n);
            v = objetos[i]->calcularV(n);
            if(objetos[i]->tieneTextura()){
                finalColor=objetos[i]->obtenerColorTextura(u,v); 
            }
            else{
                finalColor=objetos[i]->obtenerColor();
            }
            // color.r = objetos[i]->obtenerColor().r;
            // color.g = objetos[i]->obtenerColor().g;
            // color.b = objetos[i]->obtenerColor().b;

            // color.r = objetos[i]->obtenerColor().r * luz.color.r * std::max(0.0, n * (luz.posicion - q).hat() );
            // color.g = objetos[i]->obtenerColor().g * luz.color.g * std::max(0.0, n * (luz.posicion - q).hat() );
            // color.b = objetos[i]->obtenerColor().b * luz.color.b * std::max(0.0, n * (luz.posicion - q).hat() );


            // color.r = objetos[i]->obtenerColor().r * luz.color.r * std::max(0.0, n * (luz.posicion - q).hat() ) + objetos[i]->obtenerColor().r * luz.color.r * pow(std::max(0.0, n * ((-1)*r.d + (luz.posicion - q).hat()).hat() ),10000);
            // color.g = objetos[i]->obtenerColor().g * luz.color.g * std::max(0.0, n * (luz.posicion - q).hat() ) + objetos[i]->obtenerColor().g * luz.color.g * pow(std::max(0.0, n * ((-1)*r.d + (luz.posicion - q).hat()).hat() ),10000);
            // color.b = objetos[i]->obtenerColor().b * luz.color.b * std::max(0.0, n * (luz.posicion - q).hat() ) + objetos[i]->obtenerColor().b * luz.color.b * pow(std::max(0.0, n * ((-1)*r.d + (luz.posicion - q).hat()).hat() ),10000);
            
            // color.r = objetos[i]->obtenerColor().r * luz_ambiente.color.r;
            // color.g = objetos[i]->obtenerColor().g * luz_ambiente.color.g;
            // color.b = objetos[i]->obtenerColor().b * luz_ambiente.color.b;

            //color.r = objetos[i]->obtenerColor().r * luz_ambiente.color.r;
            //color.g = objetos[i]->obtenerColor().g * luz_ambiente.color.g;
            //color.b = objetos[i]->obtenerColor().b * luz_ambiente.color.b;

            color.r = objetos[i]->obtenerColor().r * luz_ambiente.color.r + objetos[i]->obtenerColor().r * luz.color.r * std::max(0.0, n * (luz.posicion - q).hat() ) + objetos[i]->obtenerColor().r * luz.color.r * pow(std::max(0.0, n * ((-1)*r.d + (luz.posicion - q).hat()).hat() ),10);
            color.g = objetos[i]->obtenerColor().g * luz_ambiente.color.g + objetos[i]->obtenerColor().g * luz.color.g * std::max(0.0, n * (luz.posicion - q).hat() ) + objetos[i]->obtenerColor().g * luz.color.g * pow(std::max(0.0, n * ((-1)*r.d + (luz.posicion - q).hat()).hat() ),10);
            color.b = objetos[i]->obtenerColor().b * luz_ambiente.color.b + objetos[i]->obtenerColor().b * luz.color.b * std::max(0.0, n * (luz.posicion - q).hat() ) + objetos[i]->obtenerColor().b * luz.color.b * pow(std::max(0.0, n * ((-1)*r.d + (luz.posicion - q).hat()).hat() ),10);

            tmin = t;
            /*
            double t_sombra;
            double t_min_sombra = 2000000;
            Vector3D n_sombra;
            Punto3D q_sombra;
            Rayo rayo_sombra(q, (luz.posicion - q).hat()) ;
            for (int j = 0; j < objetos.size(); j++) {
                if (!(objetos[j]->hayImpacto(rayo_sombra, t_sombra, n_sombra, q_sombra) && t_sombra < t_min_sombra) == false ) {
                    color.r = objetos[i]->obtenerColor().r * luz_ambiente.color.r + objetos[i]->obtenerColor().r * luz.color.r * std::max(0.0, n * (luz.posicion - q).hat() ) + objetos[i]->obtenerColor().r * luz.color.r * pow(std::max(0.0, n * ((-1)*r.d + (luz.posicion - q).hat()).hat() ),100);
                    color.g = objetos[i]->obtenerColor().g * luz_ambiente.color.g + objetos[i]->obtenerColor().g * luz.color.g * std::max(0.0, n * (luz.posicion - q).hat() ) + objetos[i]->obtenerColor().g * luz.color.g * pow(std::max(0.0, n * ((-1)*r.d + (luz.posicion - q).hat()).hat() ),100);
                    color.b = objetos[i]->obtenerColor().b * luz_ambiente.color.b + objetos[i]->obtenerColor().b * luz.color.b * std::max(0.0, n * (luz.posicion - q).hat() ) + objetos[i]->obtenerColor().b * luz.color.b * pow(std::max(0.0, n * ((-1)*r.d + (luz.posicion - q).hat()).hat() ),100);
                    t_min_sombra = t_sombra;
                }
            }*/
        }
    }
    return color;
}


int main() {

    // LUZ ----------------------------------------------------------------------------------------------
    //LuzPuntual luz(1.0, 1.0, 1.0, 200, 400, 300);
    LuzPuntual luz(1.0, 1.0, 1.0, 200, 400, 300);
    //LuzPuntual luz(1.0, 1.0, 1.0, 200, 600, 800);
    LuzPuntual luz_ambiente(0.0, 0.0, 0.0, -500.0, 300.0, -200000.0);
    
    //azurill
    //cola
    Punto3D centro1(0.0, -150.0, -200.0);
    double radio1 = 100;
    Esfera esfera1(centro1, radio1);   
    esfera1.establecerColor(0.30, 0.40, 1.0);
    // cuerpo
    Punto3D centro2(0.0, 40.0, -200.0);
    double radio2 = 80;
    Esfera esfera2(centro2, radio2);   
    esfera2.establecerColor(0.30, 0.40, 1.0);

    //orejas
    Punto3D centro3(60.0, 100.0, -200.0);
    double radio3 = 40;
    Esfera esfera3(centro3, radio3);   
    esfera3.establecerColor(0.30, 0.40, 1.0);

    Punto3D centro4(-60.0, 100.0, -200.0);
    double radio4 = 40;
    Esfera esfera4(centro4, radio4);   
    esfera4.establecerColor(0.30, 0.40, 1.0);

    //orejas dentro rosadito
    Punto3D centro5(60.0, 100.0, -170.0);
    double radio5 = 20;
    Esfera esfera5(centro5, radio5);   
    esfera5.establecerColor(1.0, 0.0, 1.0);

    Punto3D centro6(-60.0, 100.0, -170.0);
    double radio6 = 20;
    Esfera esfera6(centro6, radio6);   
    esfera6.establecerColor(1.0, 0.0, 1.0);

    //cachetes blancos 
    Punto3D centro7(55.0, 30.0, -100.0);
    double radio7 = 10;
    Esfera esfera7(centro7, radio7);   
    esfera7.establecerColor(1.0, 1.0, 1.0);

    Punto3D centro8(-55.0, 30.0, -100.0);
    double radio8 = 10;
    Esfera esfera8(centro8, radio8);   
    esfera8.establecerColor(1.0, 1.0, 1.0);

    //ojitos negros
    Punto3D centro9(35.0, 65.0, -100.0);
    double radio9 = 8;
    Esfera esfera9(centro9, radio9);   
    esfera9.establecerColor(0.0, 0.0, 0.0);

    Punto3D centro10(-35.0, 65.0, -100.0);
    double radio10 = 8;
    Esfera esfera10(centro10, radio10);   
    esfera10.establecerColor(0.0, 0.0, 0.0);

    Punto3D centro11(35.0, 70.0, -50.0);
    double radio11 = 3;
    Esfera esfera11(centro11, radio11);   
    esfera11.establecerColor(1.0, 1.0, 1.0);

    Punto3D centro12(-35.0, 70.0, -50.0);
    double radio12 = 3;
    Esfera esfera12(centro12, radio12);   
    esfera12.establecerColor(1.0, 1.0, 1.0);

    //boca 
    Punto3D centro13(0.0, 25.0, -50.0);
    double radio13 = 15;
    Esfera esfera13(centro13, radio13);   
    esfera13.establecerColor(0.0, 0.0, 0.0);
    
    Punto3D centro14(0.0, 20.0, -10.0);
    double radio14 = 10;
    Esfera esfera14(centro14, radio14);   
    esfera14.establecerColor(1.0, 0.0, 1.0);

    //pies
    Punto3D centro15(35.0, -25.0, -100.0);
    double radio15 = 21;
    Esfera esfera15(centro15, radio15);   
    esfera15.establecerColor(0.0, 0.0, 0.0);
        
    Punto3D centro16(-35.0, -25.0, -100.0);
    double radio16 = 21;
    Esfera esfera16(centro16, radio16);   
    esfera16.establecerColor(0.0, 0.0, 0.0);

    Punto3D centro17(35.0, -25.0, -50.0);
    double radio17 = 20;
    Esfera esfera17(centro17, radio17);   
    esfera17.establecerColor(0.30, 0.40, 1.0);

    Punto3D centro18(-35.0, -25.0, -50.0);
    double radio18 = 20;
    Esfera esfera18(centro18, radio18);   
    esfera18.establecerColor(0.30, 0.40, 1.0);

    //colita----
    //primer triangulo
    Punto3D A(100,-150,-400); //puntoizquierda
    Punto3D B(125,-85,350); //punto arriba
    Punto3D C(300, -50, 4000);
    Triangulo t(A, B, C);
    //t.establecerColor(0.40, 0, 0.50);
    t.establecerColor(0.75,0.78,0.75);

    Punto3D A2(90,-150,-300); //puntoizquierda
    Punto3D B2(120,-60,250); //punto arriba
    Punto3D C2(320, -40, 3000);
    Triangulo t2(A2, B2, C2);
    //t.establecerColor(0.40, 0, 0.50);
    t2.establecerColor(0.0, 0.0, 0.0);

    //segundo triangulo
    Punto3D A3(108,-110,-300); //puntoizquierda
    Punto3D B3(120,-40,450); //punto arriba
    Punto3D C3(450, -50, 2500);
    Triangulo t3(A3, B3, C3);
    //t.establecerColor(0.40, 0, 0.50);
    t3.establecerColor(0.75,0.78,0.75);

    Punto3D A31(105,-107,-300); //puntoizquierda
    Punto3D B31(118,-50,430); //punto arriba
    Punto3D C31(440,-45, 3000);
    Triangulo t31(A31, B31, C31);
    //t.establecerColor(0.40, 0, 0.50);
    t31.establecerColor(0.0, 0.0, 0.0);

    //tercer triangulo
    Punto3D A5(115,-77, -215); //puntoizquierda
    Punto3D B5(70,10,450); //punto arriba
    Punto3D C5(300,50, 2000);
    Triangulo t5(A5, B5, C5);
    //t.establecerColor(0.40, 0, 0.50);
    t5.establecerColor(0.75,0.78,0.75);

    Punto3D A41(110,-75,-215); //puntoizquierda
    Punto3D B41(65,6,450); //punto arriba
    Punto3D C41(270, 50, 2000);
    Triangulo t41(A41, B41, C41);
    //t.establecerColor(0.40, 0, 0.50);
    t41.establecerColor(0.0, 0.0, 0.0);

     //cuarto triangulo
    Punto3D A6(95,-40, -210); //puntoizquierda
    Punto3D B6(50,0,450); //punto arriba
    Punto3D C6(300,45, 2000);
    Triangulo t6(A6, B6, C6);
    //t.establecerColor(0.40, 0, 0.50);
    t6.establecerColor(0.75,0.78,0.75);

    Punto3D A7(90,-40, -210); //puntoizquierda
    Punto3D B7(50,-4,450); //punto arriba
    Punto3D C7(300,40, 2000);
    Triangulo t7(A7, B7, C7);
    //t.establecerColor(0.40, 0, 0.50);
    t7.establecerColor(0.0, 0.0, 0.0);

    //quinto triangulo
    Punto3D A8(75,-22, -210); //puntoizquierda
    Punto3D B8(50,10,400); //punto arriba
    Punto3D C8(300,50, 2500);
    Triangulo t8(A8, B8, C8);
    //t.establecerColor(0.40, 0, 0.50);
    t8.establecerColor(0.75,0.78,0.75);

    Punto3D A9(70,-22, -210); //puntoizquierda
    Punto3D B9(45,10,400); //punto arriba
    Punto3D C9(300,50, 2500);
    Triangulo t9(A9, B9, C9);
    //t.establecerColor(0.40, 0, 0.50);
    t9.establecerColor(0.0, 0.0, 0.0);


    Image img;
    

    img.read_ppm_file("tierra2.ppm");
    

    esfera1.establecerTextura(img);

    vector<ObjetoGeometrico*> escena;
    escena.push_back(&esfera1);
    escena.push_back(&esfera2);
    escena.push_back(&esfera3);
    escena.push_back(&esfera4);
    escena.push_back(&esfera5);
    escena.push_back(&esfera6);
    escena.push_back(&esfera7);
    escena.push_back(&esfera8);
    escena.push_back(&esfera9);
    escena.push_back(&esfera10);
    escena.push_back(&esfera11);
    escena.push_back(&esfera12);
    escena.push_back(&esfera13);
    escena.push_back(&esfera14);
    escena.push_back(&esfera15);
    escena.push_back(&esfera16);
    escena.push_back(&esfera17);
    escena.push_back(&esfera18);
    escena.push_back(&t);
    escena.push_back(&t2);
    escena.push_back(&t3);
    escena.push_back(&t31);
    escena.push_back(&t41);
    escena.push_back(&t5);
    escena.push_back(&t6);
    escena.push_back(&t7);
    escena.push_back(&t8);
    escena.push_back(&t9);

    ColorRGB color_pixel;    
    
     // VIEWPLANE
    int hres = 800;
    int vres = 600;
    double s = 1.0;
    ViewPlane vp(hres, vres, s);
    
    
     // UTILITARIO PARA GUARDAR IMAGEN -------------------------------------------------------------------
    int dpi = 72;
    int width = vp.hres;
    int height = vp.vres;
    int n = width * height;
    ColorRGB* pixeles = new ColorRGB[n];
    
    
     // ALGORITMO
    for(int fil = 0; fil < vp.vres; fil++)
    {
        for ( int col = 0; col < vp.hres; col++) 
        {
            // Disparar un rayo
            Vector3D direccion(0.0, 0.0, -1.0);
            double x = vp.s * ( col - vp.hres/2 + 0.5 );
            double y = vp.s * ( fil - vp.vres/2 + 0.5 );
            double z = 100; //valor de z original 0
            Punto3D origen(x, y, z);
            Rayo rayo(origen, direccion);

            color_pixel = obtenerColorPixel(rayo, escena, luz, luz_ambiente);
            pixeles[fil*width+col].r = obtenerColorPixel(rayo, escena, luz, luz_ambiente).r;
            pixeles[fil*width+col].g = obtenerColorPixel(rayo, escena, luz, luz_ambiente).g;
            pixeles[fil*width+col].b = obtenerColorPixel(rayo, escena, luz, luz_ambiente).b;
        }
    }    
    savebmp("img.bmp", width, height, dpi, pixeles);
    return 0;
}