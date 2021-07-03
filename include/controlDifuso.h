#ifndef DIFUSO_DEF
#define DIFUSO_DEF
#include "adc.h"
#include <Fuzzy.h>

//Clase Difuso
class Difuso{
    public:
        Difuso(bool opti);
        float output(float posicion, float angulo, float set_point);


    private:

        float error_pos[2];
        float error_dev_pos[2];
        float error_ang[2];
        float error_dev_ang[2];

        //se crean dos sistemas difuso para el control de posicion y angulo

        Fuzzy *controlPos = new Fuzzy();
        Fuzzy *controlAngulo = new Fuzzy();

        //Funciones de pertenencia para posicion

        FuzzySet *MDR = new FuzzySet(-0.2, -0.2, -0.15, -0.1, 0, 1, 1);
        FuzzySet *DR = new FuzzySet(-0.15, -0.1, -0.05, -0.03, 0, 1, 1);
        FuzzySet *pdr = new FuzzySet(-0.05, -0.03, -0.01, 0, 0, 1, 1);
        FuzzySet *pdro = new FuzzySet(-0.05, -0.03, -0.01, 0, 0, 1, 2);
        FuzzySet *cp = new FuzzySet(-0.0099, 0, 0, 0.0099, 0, 1, 1);
        FuzzySet *cpo = new FuzzySet(-0.01, 0, 0, 0.01, 0, 1, 1);
        FuzzySet *piz = new FuzzySet(0, 0.01, 0.03, 0.05, 0, 1, 1);
        FuzzySet *pizo = new FuzzySet(0, 0.01, 0.03, 0.05, 0, 1, 2);
        FuzzySet *IZ = new FuzzySet(0.03, 0.05, 0.10, 0.15, 0, 1, 1);
        FuzzySet *MIZ = new FuzzySet(0.1, 0.15, 0.2, 0.2, 0, 1, 1);

        FuzzySet *PRP = new FuzzySet(-0.2, -0.2, -0.12, -0.04, 0, 1, 1);
        FuzzySet *plp = new FuzzySet(-0.08, -0.04, -0.04, 0, 0, 1, 1);
        FuzzySet *plpo = new FuzzySet(-0.08, -0.04124, -0.03876, 0, 0.003906, 1, 1.031);
        FuzzySet *CDP = new FuzzySet(-0.04, 0, 0, 0.04, 0, 1, 1);
        FuzzySet *nlp = new FuzzySet( 0, 0.03876, 0.04124, 0.08, 0.003906, 1, 1.031);
        FuzzySet *nlpo = new FuzzySet( 0, 0.04, 0.04, 0.08, 0, 1, 1);
        FuzzySet *NRP = new FuzzySet( 0.04, 0.12, 0.2, 0.2, 0, 1, 1);

        FuzzySet *MHP = new FuzzySet(-1.125, -0.7875, -0.7875, -0.45, 0, 1, 1);
        FuzzySet *HP = new FuzzySet( -0.7875, -0.45, -0.45, -0.2, 0, 1, 1);
        FuzzySet *PHP = new FuzzySet( -0.4, -0.2, -0.2, 0, 0, 1, 1);
        FuzzySet *CAP = new FuzzySet(-0.2, 0, 0, 0.2, 0, 1, 1);
        FuzzySet *PAP = new FuzzySet( 0, 0.2, 0.2, 0.4, 0, 1, 1);
        FuzzySet *AP = new FuzzySet(0.2, 0.45, 0.45, 0.7875, 0, 1, 1);
        FuzzySet *MAP = new FuzzySet(0.45, 0.7875, 0.7875, 1.125, 0, 1, 1);

        //Funciones de pertenencia para angulo

        FuzzySet *muyAbajo = new FuzzySet(-0.785,-0.785,-0.5236,-0.1745, 0, 1, 1);
        FuzzySet *abajo = new FuzzySet(-0.349, -0.1745, -0.1745, -0.01745, 0, 1, 1);
        FuzzySet *cero_ang = new FuzzySet(-0.08, 0, 0, 0.08, 0, 1, 1);
        FuzzySet *arriba = new FuzzySet(0.01745, 0.1745, 0.1745, 0.349, 0, 1, 1);
        FuzzySet *muyArriba = new FuzzySet(0.1745, 0.5235, 0.785, 0.785, 0, 1, 1);

        FuzzySet *posRapido = new FuzzySet(-3, -3, -1.8, -1.2, 0, 1, 1);
        FuzzySet *posLento = new FuzzySet(-1.8, -0.9, -0.9, 0, 0, 1, 1);
        FuzzySet *cero_dev_ang = new FuzzySet(-0.3, 0, 0, 0.3, 0, 1, 1);
        FuzzySet *negLento = new FuzzySet(0, 0.9, 0.9, 1.8, 0, 1, 1);
        FuzzySet *negRapido = new FuzzySet(1.2, 1.8, 3, 3, 0, 1, 1);

        FuzzySet *horaRapido = new FuzzySet(-6.2, -4.96, -4.96, -3.72, 0, 1, 1);
        FuzzySet *horario = new FuzzySet(-3.707, -2.467, -2.467, -1.227, 0, 1, 1);
        FuzzySet *cero_pwm = new FuzzySet(-0.62, 0, 0, 0.62, 0, 1, 1);
        FuzzySet *antiH = new FuzzySet(1.24, 2.48, 2.48, 3.72, 0, 1, 1);
        FuzzySet *antiHRapido = new FuzzySet(3.72, 4.96, 4.96, 6.2, 0, 1, 1);

        void init_pos(FuzzySet *PDR, FuzzySet *CP, FuzzySet *PIZ, FuzzySet *PLP, FuzzySet *NLP);

        void init_ang();
};

#endif
