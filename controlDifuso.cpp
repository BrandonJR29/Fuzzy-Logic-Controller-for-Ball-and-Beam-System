#include "include/controlDifuso.h"

//Contructor de clase Difuso
Difuso::Difuso(bool opti){

  if(opti){
	  //Se crea el control difuso ajustado
	  ESP_LOGI("FUZZY","Inicio Control Difuso Ajustado");
	  init_pos(this->pdro,this->cpo,this->pizo,this->plpo,this->nlpo);

  }else{

    init_pos(this->pdr,this->cp,this->piz,this->plp,this->nlp);
    ESP_LOGI("FUZZY","Inicio Control Difuso");

  }

  init_ang();


}

//inicia conttrol difuso para la posicion
void Difuso::init_pos(FuzzySet *PDR, FuzzySet *CP, FuzzySet *PIZ, FuzzySet *PLP, FuzzySet *NLP){

  /*****************Control de Posicion****************************/

  FuzzyInput *EP = new FuzzyInput(1);

  EP->addFuzzySet(MIZ);
  EP->addFuzzySet(IZ);
  EP->addFuzzySet(PIZ);
  EP->addFuzzySet(CP);
  EP->addFuzzySet(PDR);
  EP->addFuzzySet(DR);
  EP->addFuzzySet(MDR);
  controlPos->addFuzzyInput(EP);

  FuzzyInput *EDP = new FuzzyInput(2);

  EDP->addFuzzySet(NRP);
  EDP->addFuzzySet(NLP);
  EDP->addFuzzySet(CDP);
  EDP->addFuzzySet(PLP);
  EDP->addFuzzySet(PRP);
  controlPos->addFuzzyInput(EDP);

  FuzzyOutput *ADP = new FuzzyOutput(1);

  ADP->addFuzzySet(MHP);
  ADP->addFuzzySet(HP);
  ADP->addFuzzySet(PHP);
  ADP->addFuzzySet(CAP);
  ADP->addFuzzySet(PAP);
  ADP->addFuzzySet(AP);
  ADP->addFuzzySet(MAP);
  controlPos->addFuzzyOutput(ADP);

  FuzzyRuleAntecedent *ifMuyIzquierdaAndNegRapido = new FuzzyRuleAntecedent();
  ifMuyIzquierdaAndNegRapido->joinWithAND(MIZ, NRP);

  FuzzyRuleAntecedent *ifMuyIzquierdaAndNegLento = new FuzzyRuleAntecedent();
  ifMuyIzquierdaAndNegLento->joinWithAND(MIZ, NLP);

  FuzzyRuleAntecedent *ifMuyIzquierdaAndCero_dev_pos = new FuzzyRuleAntecedent();
  ifMuyIzquierdaAndCero_dev_pos->joinWithAND(MIZ, CDP);

  FuzzyRuleAntecedent *ifMuyIzquierdaAndPosLento = new FuzzyRuleAntecedent();
  ifMuyIzquierdaAndPosLento->joinWithAND(MIZ, PLP);

  FuzzyRuleAntecedent *ifMuyIzquierdaAndPosRapido = new FuzzyRuleAntecedent();
  ifMuyIzquierdaAndPosRapido->joinWithAND(MIZ, PRP);



  FuzzyRuleAntecedent *ifIzquierdaAndNegRapido = new FuzzyRuleAntecedent();
  ifIzquierdaAndNegRapido->joinWithAND(IZ, NRP);

  FuzzyRuleAntecedent *ifIzquierdaAndNegLento = new FuzzyRuleAntecedent();
  ifIzquierdaAndNegLento->joinWithAND(IZ, NLP);

  FuzzyRuleAntecedent *ifIzquierdaAndCero_dev_pos = new FuzzyRuleAntecedent();
  ifIzquierdaAndCero_dev_pos->joinWithAND(IZ, CDP);

  FuzzyRuleAntecedent *ifIzquierdaAndPosLento = new FuzzyRuleAntecedent();
  ifIzquierdaAndPosLento->joinWithAND(IZ, PLP);

  FuzzyRuleAntecedent *ifIzquierdaAndPosRapido = new FuzzyRuleAntecedent();
  ifIzquierdaAndPosRapido->joinWithAND(IZ, PRP);



  FuzzyRuleAntecedent *ifPocoIzquierdaAndNegRapido = new FuzzyRuleAntecedent();
  ifPocoIzquierdaAndNegRapido->joinWithAND(PIZ, NRP);

  FuzzyRuleAntecedent *ifPocoIzquierdaAndNegLento = new FuzzyRuleAntecedent();
  ifPocoIzquierdaAndNegLento->joinWithAND(PIZ, NLP);

  FuzzyRuleAntecedent *ifPocoIzquierdaAndCero_dev_pos = new FuzzyRuleAntecedent();
  ifPocoIzquierdaAndCero_dev_pos->joinWithAND(PIZ, CDP);

  FuzzyRuleAntecedent *ifPocoIzquierdaAndPosLento = new FuzzyRuleAntecedent();
  ifPocoIzquierdaAndPosLento->joinWithAND(PIZ, PLP);

  FuzzyRuleAntecedent *ifPocoIzquierdaAndPosRapido = new FuzzyRuleAntecedent();
  ifPocoIzquierdaAndPosRapido->joinWithAND(PIZ, PRP);




  FuzzyRuleAntecedent *ifCero_posAndNegRapido = new FuzzyRuleAntecedent();
  ifCero_posAndNegRapido->joinWithAND(CP, NRP);

  FuzzyRuleAntecedent *ifCero_posAndNegLento = new FuzzyRuleAntecedent();
  ifCero_posAndNegLento->joinWithAND(CP, NLP);

  FuzzyRuleAntecedent *ifCero_posAndCero_dev_pos = new FuzzyRuleAntecedent();
  ifCero_posAndCero_dev_pos->joinWithAND(CP, CDP);

  FuzzyRuleAntecedent *ifCero_posAndPosLento = new FuzzyRuleAntecedent();
  ifCero_posAndPosLento->joinWithAND(CP, PLP);

  FuzzyRuleAntecedent *ifCero_posAndPosRapido = new FuzzyRuleAntecedent();
  ifCero_posAndPosRapido->joinWithAND(CP, PRP);


  FuzzyRuleAntecedent *ifPocoDerechaAndNegRapido = new FuzzyRuleAntecedent();
  ifPocoDerechaAndNegRapido->joinWithAND(PDR, NRP);

  FuzzyRuleAntecedent *ifPocoDerechaAndNegLento = new FuzzyRuleAntecedent();
  ifPocoDerechaAndNegLento->joinWithAND(PDR, NLP);

  FuzzyRuleAntecedent *ifPocoDerechaAndCero_dev_pos = new FuzzyRuleAntecedent();
  ifPocoDerechaAndCero_dev_pos->joinWithAND(PDR, CDP);

  FuzzyRuleAntecedent *ifPocoDerechaAndPosLento = new FuzzyRuleAntecedent();
  ifPocoDerechaAndPosLento->joinWithAND(PDR, PLP);

  FuzzyRuleAntecedent *ifPocoDerechaAndPosRapido = new FuzzyRuleAntecedent();
  ifPocoDerechaAndPosRapido->joinWithAND(PDR, PRP);



  FuzzyRuleAntecedent *ifDerechaAndNegRapido = new FuzzyRuleAntecedent();
  ifDerechaAndNegRapido->joinWithAND(DR, NRP);

  FuzzyRuleAntecedent *ifDerechaAndNegLento = new FuzzyRuleAntecedent();
  ifDerechaAndNegLento->joinWithAND(DR, NLP);

  FuzzyRuleAntecedent *ifDerechaAndCero_dev_pos = new FuzzyRuleAntecedent();
  ifDerechaAndCero_dev_pos->joinWithAND(DR, CDP);

  FuzzyRuleAntecedent *ifDerechaAndPosLento = new FuzzyRuleAntecedent();
  ifDerechaAndPosLento->joinWithAND(DR, PLP);

  FuzzyRuleAntecedent *ifDerechaAndPosRapido = new FuzzyRuleAntecedent();
  ifDerechaAndPosRapido->joinWithAND(DR, PRP);



  FuzzyRuleAntecedent *ifMuyDerechaAndNegRapido = new FuzzyRuleAntecedent();
  ifMuyDerechaAndNegRapido->joinWithAND(MDR, NRP);

  FuzzyRuleAntecedent *ifMuyDerechaAndNegLento = new FuzzyRuleAntecedent();
  ifMuyDerechaAndNegLento->joinWithAND(MDR, NLP);

  FuzzyRuleAntecedent *ifMuyDerechaAndCero_dev_pos = new FuzzyRuleAntecedent();
  ifMuyDerechaAndCero_dev_pos->joinWithAND(MDR, CDP);

  FuzzyRuleAntecedent *ifMuyDerechaAndPosLento = new FuzzyRuleAntecedent();
  ifMuyDerechaAndPosLento->joinWithAND(MDR, PLP);

  FuzzyRuleAntecedent *ifMuyDerechaAndPosRapido = new FuzzyRuleAntecedent();
  ifMuyDerechaAndPosRapido->joinWithAND(MDR, PRP);




  FuzzyRuleConsequent *thenMaxHora = new FuzzyRuleConsequent();
  thenMaxHora->addOutput(MHP);

  FuzzyRuleConsequent *thenHora = new FuzzyRuleConsequent();
  thenHora->addOutput(HP);

  FuzzyRuleConsequent *thenMinHora = new FuzzyRuleConsequent();
  thenMinHora->addOutput(PHP);

  FuzzyRuleConsequent *thenCero_ang_des = new FuzzyRuleConsequent();
  thenCero_ang_des->addOutput(CAP);

  FuzzyRuleConsequent *thenMinAntiH = new FuzzyRuleConsequent();
  thenMinAntiH->addOutput(PAP);

  FuzzyRuleConsequent *thenAntiHora = new FuzzyRuleConsequent();
  thenAntiHora->addOutput(AP);

  FuzzyRuleConsequent *thenMaxAntiH = new FuzzyRuleConsequent();
  thenMaxAntiH->addOutput(MAP);

  //if muyIzquierda and negRapido_pos then maxHora

  FuzzyRule *fuzzyRule1_pos = new FuzzyRule(1, ifMuyIzquierdaAndNegRapido, thenMaxHora);
  controlPos->addFuzzyRule(fuzzyRule1_pos);

  //if muyIzquierda and negLento_pos then maxHora

  FuzzyRule *fuzzyRule2_pos = new FuzzyRule(2, ifMuyIzquierdaAndNegLento, thenMaxHora);
  controlPos->addFuzzyRule(fuzzyRule2_pos);

  //if muyIzquierda and cero_dev_pos then maxHora

  FuzzyRule *fuzzyRule3_pos = new FuzzyRule(3, ifMuyIzquierdaAndCero_dev_pos, thenMaxHora);
  controlPos->addFuzzyRule(fuzzyRule3_pos);

  //if muyIzquierda and posLento_pos then Hora

  FuzzyRule *fuzzyRule4_pos = new FuzzyRule(4, ifMuyIzquierdaAndPosLento, thenMaxHora);
  controlPos->addFuzzyRule(fuzzyRule4_pos);

  //if muyIzquierda and posRapido_pos then maxHora

  FuzzyRule *fuzzyRule5_pos = new FuzzyRule(5, ifMuyIzquierdaAndPosRapido, thenHora);
  controlPos->addFuzzyRule(fuzzyRule5_pos);

  //if izquierda and negRapido_pos then maxHora

  FuzzyRule *fuzzyRule6_pos = new FuzzyRule(6, ifIzquierdaAndNegRapido, thenMaxHora);
  controlPos->addFuzzyRule(fuzzyRule6_pos);

  //if izquierda and negLento_pos then maxHora

  FuzzyRule *fuzzyRule7_pos = new FuzzyRule(7, ifIzquierdaAndNegLento, thenMaxHora);
  controlPos->addFuzzyRule(fuzzyRule7_pos);

  //if izquierda and cero_dev_pos then maxHora

  FuzzyRule *fuzzyRule8_pos = new FuzzyRule(8, ifIzquierdaAndCero_dev_pos, thenHora);
  controlPos->addFuzzyRule(fuzzyRule8_pos);

  //if izquierda and posLento_pos then cero_ang_des

  FuzzyRule *fuzzyRule9_pos = new FuzzyRule(9, ifIzquierdaAndPosLento, thenCero_ang_des);
  controlPos->addFuzzyRule(fuzzyRule9_pos);

  //if izquierda and posRapido_pos then antiHora

  FuzzyRule *fuzzyRule10_pos = new FuzzyRule(10, ifIzquierdaAndPosRapido, thenAntiHora);
  controlPos->addFuzzyRule(fuzzyRule10_pos);

  //if cero_pos and negRapido_pos then maxHora

  FuzzyRule *fuzzyRule11_pos = new FuzzyRule(11, ifCero_posAndNegRapido, thenHora);
  controlPos->addFuzzyRule(fuzzyRule11_pos);

  //if cero_pos and negLento_pos then hora

  FuzzyRule *fuzzyRule12_pos = new FuzzyRule(12, ifCero_posAndNegLento, thenCero_ang_des);
  controlPos->addFuzzyRule(fuzzyRule12_pos);

  //if cero_pos and cero_dev_pos then cero_ang_des

  FuzzyRule *fuzzyRule13_pos = new FuzzyRule(13, ifCero_posAndCero_dev_pos, thenCero_ang_des);
  controlPos->addFuzzyRule(fuzzyRule13_pos);

  //if cero_pos and posLento_pos then antiHora

  FuzzyRule *fuzzyRule14_pos = new FuzzyRule(14, ifCero_posAndPosLento, thenCero_ang_des);
  controlPos->addFuzzyRule(fuzzyRule14_pos);

  //if cero_pos and posRapido_pos then maxAntiH

  FuzzyRule *fuzzyRule15_pos = new FuzzyRule(15, ifCero_posAndPosRapido, thenAntiHora);
  controlPos->addFuzzyRule(fuzzyRule15_pos);

  //if derecha and negRapido_pos then Hora

  FuzzyRule *fuzzyRule16_pos = new FuzzyRule(16, ifDerechaAndNegRapido, thenHora);
  controlPos->addFuzzyRule(fuzzyRule16_pos);

  //if derecha and negLento_pos then cero_ang_des

  FuzzyRule *fuzzyRule17_pos = new FuzzyRule(17, ifDerechaAndNegLento, thenCero_ang_des);
  controlPos->addFuzzyRule(fuzzyRule17_pos);

  //if derecha and cero_dev_pos then antiHora

  FuzzyRule *fuzzyRule18_pos = new FuzzyRule(18, ifDerechaAndCero_dev_pos, thenAntiHora);
  controlPos->addFuzzyRule(fuzzyRule18_pos);

  //if derecha and posLento_pos then maxAntiHora

  FuzzyRule *fuzzyRule19_pos = new FuzzyRule(19, ifDerechaAndPosLento, thenMaxAntiH);
  controlPos->addFuzzyRule(fuzzyRule19_pos);

  //if derecha and posRapido_pos then maxAntiHora

  FuzzyRule *fuzzyRule20_pos = new FuzzyRule(20, ifDerechaAndPosRapido, thenMaxAntiH);
  controlPos->addFuzzyRule(fuzzyRule20_pos);

  //if muyDerecha and negRapido_pos then antiHora

  FuzzyRule *fuzzyRule21_pos = new FuzzyRule(21, ifMuyDerechaAndNegRapido, thenAntiHora);
  controlPos->addFuzzyRule(fuzzyRule21_pos);

  //if muyDerecha and negLento_pos then maxAntiHora

  FuzzyRule *fuzzyRule22_pos = new FuzzyRule(22, ifMuyDerechaAndNegLento, thenMaxAntiH);
  controlPos->addFuzzyRule(fuzzyRule22_pos);

  //if muyDerecha and cero_dev_pos then maxAntiHora

  FuzzyRule *fuzzyRule23_pos = new FuzzyRule(23, ifMuyDerechaAndCero_dev_pos, thenMaxAntiH);
  controlPos->addFuzzyRule(fuzzyRule23_pos);

  //if muyDerecha and posLento_pos then maxAntiHora

  FuzzyRule *fuzzyRule24_pos = new FuzzyRule(24, ifMuyDerechaAndPosLento, thenMaxAntiH);
  controlPos->addFuzzyRule(fuzzyRule24_pos);

  //if muyDerecha and posRapido_pos then maxAntiHora

  FuzzyRule *fuzzyRule25_pos = new FuzzyRule(25, ifMuyDerechaAndPosRapido, thenMaxAntiH);
  controlPos->addFuzzyRule(fuzzyRule25_pos);

  //if pocoIzquierda and negRapido_pos then maxHora

  FuzzyRule *fuzzyRule26_pos = new FuzzyRule(26, ifPocoIzquierdaAndNegRapido, thenMaxHora);
  controlPos->addFuzzyRule(fuzzyRule26_pos);

  //if pocoIzquierda and negLento_pos then maxHora

  FuzzyRule *fuzzyRule27_pos = new FuzzyRule(27, ifPocoIzquierdaAndNegLento, thenHora);
  controlPos->addFuzzyRule(fuzzyRule27_pos);

  //if pocoIzquierda and cero_dev_pos then horario

  FuzzyRule *fuzzyRule28_pos = new FuzzyRule(28, ifPocoIzquierdaAndCero_dev_pos, thenMinHora);
  controlPos->addFuzzyRule(fuzzyRule28_pos);

  //if pocoIzquierda and posLento_pos then pocoAnti

  FuzzyRule *fuzzyRule29_pos = new FuzzyRule(29, ifPocoIzquierdaAndPosLento, thenMinAntiH);
  controlPos->addFuzzyRule(fuzzyRule29_pos);

  //if pocoIzquierda and posRapido_pos then maxAntiH

  FuzzyRule *fuzzyRule30_pos = new FuzzyRule(30, ifPocoIzquierdaAndPosRapido, thenAntiHora);
  controlPos->addFuzzyRule(fuzzyRule30_pos);



  //if pocoDerecha and negRapido_pos then maxAntiH

  FuzzyRule *fuzzyRule31_pos = new FuzzyRule(31, ifPocoDerechaAndNegRapido, thenHora);
  controlPos->addFuzzyRule(fuzzyRule31_pos);

  //if pocoDerecha and negLento_pos then maxAntiH

  FuzzyRule *fuzzyRule32_pos = new FuzzyRule(32, ifPocoDerechaAndNegLento, thenMinHora);
  controlPos->addFuzzyRule(fuzzyRule32_pos);

  //if pocoDerehca and cero_dev_pos then antihora

  FuzzyRule *fuzzyRule33_pos = new FuzzyRule(33, ifPocoDerechaAndCero_dev_pos, thenMinAntiH);
  controlPos->addFuzzyRule(fuzzyRule33_pos);

  //if pocoDerecha and posLento_pos then pocoHora

  FuzzyRule *fuzzyRule34_pos = new FuzzyRule(34, ifPocoDerechaAndPosLento, thenAntiHora);
  controlPos->addFuzzyRule(fuzzyRule34_pos);

  //if pocoDerecha and posRapido_pos then maxHora

  FuzzyRule *fuzzyRule35_pos = new FuzzyRule(35, ifPocoDerechaAndPosRapido, thenMaxAntiH);
  controlPos->addFuzzyRule(fuzzyRule35_pos);

}

//inicia conttrol difuso para el angulo
void Difuso::init_ang(){

/****************Control de Angulo*************************/

  FuzzyInput *err_angulo = new FuzzyInput(1);

  err_angulo->addFuzzySet(muyArriba);
  err_angulo->addFuzzySet(arriba);
  err_angulo->addFuzzySet(cero_ang);
  err_angulo->addFuzzySet(abajo);
  err_angulo->addFuzzySet(muyAbajo);
  controlAngulo->addFuzzyInput(err_angulo);

  FuzzyInput *err_dev_ang = new FuzzyInput(2);

  err_dev_ang->addFuzzySet(posRapido);
  err_dev_ang->addFuzzySet(posLento);
  err_dev_ang->addFuzzySet(cero_dev_ang);
  err_dev_ang->addFuzzySet(negLento);
  err_dev_ang->addFuzzySet(negRapido);
  controlAngulo->addFuzzyInput(err_dev_ang);

  FuzzyOutput *pwm_fuzzy = new FuzzyOutput(1);

  pwm_fuzzy->addFuzzySet(horaRapido);
  pwm_fuzzy->addFuzzySet(horario);
  pwm_fuzzy->addFuzzySet(cero_pwm);
  pwm_fuzzy->addFuzzySet(antiH);
  pwm_fuzzy->addFuzzySet(antiHRapido);
  controlAngulo->addFuzzyOutput(pwm_fuzzy);

  FuzzyRuleAntecedent *ifMuyArribaAndPosRapido = new FuzzyRuleAntecedent();
  ifMuyArribaAndPosRapido->joinWithAND(muyArriba,posRapido);

  FuzzyRuleAntecedent *ifMuyArribaAndPosLento = new FuzzyRuleAntecedent();
  ifMuyArribaAndPosLento->joinWithAND(muyArriba,posLento);

  FuzzyRuleAntecedent *ifMuyArribaAndCero_dev_ang = new FuzzyRuleAntecedent();
  ifMuyArribaAndCero_dev_ang->joinWithAND(muyArriba,cero_dev_ang);

  FuzzyRuleAntecedent *ifMuyArribaAndNegLento = new FuzzyRuleAntecedent();
  ifMuyArribaAndNegLento->joinWithAND(muyArriba,negLento);

  FuzzyRuleAntecedent *ifMuyArribaAndNegRapido = new FuzzyRuleAntecedent();
  ifMuyArribaAndNegRapido->joinWithAND(muyArriba,negRapido);


  FuzzyRuleAntecedent *ifArribaAndPosRapido = new FuzzyRuleAntecedent();
  ifArribaAndPosRapido->joinWithAND(arriba,posRapido);

  FuzzyRuleAntecedent *ifArribaAndPosLento = new FuzzyRuleAntecedent();
  ifArribaAndPosLento->joinWithAND(arriba,posLento);

  FuzzyRuleAntecedent *ifArribaAndCero_dev_ang = new FuzzyRuleAntecedent();
  ifArribaAndCero_dev_ang->joinWithAND(arriba,cero_dev_ang);

  FuzzyRuleAntecedent *ifArribaAndNegLento = new FuzzyRuleAntecedent();
  ifArribaAndNegLento->joinWithAND(arriba,negLento);

  FuzzyRuleAntecedent *ifArribaAndNegRapido = new FuzzyRuleAntecedent();
  ifArribaAndNegRapido->joinWithAND(arriba,negRapido);



  FuzzyRuleAntecedent *ifCero_angAndPosRapido = new FuzzyRuleAntecedent();
  ifCero_angAndPosRapido->joinWithAND(cero_ang,posRapido);

  FuzzyRuleAntecedent *ifCero_angAndPosLento = new FuzzyRuleAntecedent();
  ifCero_angAndPosLento->joinWithAND(cero_ang,posLento);

  FuzzyRuleAntecedent *ifCero_angAndCero_dev_ang = new FuzzyRuleAntecedent();
  ifCero_angAndCero_dev_ang->joinWithAND(cero_ang,cero_dev_ang);

  FuzzyRuleAntecedent *ifCero_angAndNegLento = new FuzzyRuleAntecedent();
  ifCero_angAndNegLento->joinWithAND(cero_ang,negLento);

  FuzzyRuleAntecedent *ifCero_angAndNegRapido = new FuzzyRuleAntecedent();
  ifCero_angAndNegRapido->joinWithAND(cero_ang,negRapido);



  FuzzyRuleAntecedent *ifAbajoAndPosRapido = new FuzzyRuleAntecedent();
  ifAbajoAndPosRapido->joinWithAND(abajo,posRapido);

  FuzzyRuleAntecedent *ifAbajoAndPosLento = new FuzzyRuleAntecedent();
  ifAbajoAndPosLento->joinWithAND(abajo,posLento);

  FuzzyRuleAntecedent *ifAbajoAndCero_dev_ang = new FuzzyRuleAntecedent();
  ifAbajoAndCero_dev_ang->joinWithAND(abajo,cero_dev_ang);

  FuzzyRuleAntecedent *ifAbajoAndNegLento = new FuzzyRuleAntecedent();
  ifAbajoAndNegLento->joinWithAND(abajo,negLento);

  FuzzyRuleAntecedent *ifAbajoAndNegRapido = new FuzzyRuleAntecedent();
  ifAbajoAndNegRapido->joinWithAND(abajo,negRapido);



  FuzzyRuleAntecedent *ifMuyAbajoAndPosRapido = new FuzzyRuleAntecedent();
  ifMuyAbajoAndPosRapido->joinWithAND(muyAbajo,posRapido);

   FuzzyRuleAntecedent *ifMuyAbajoAndPosLento = new FuzzyRuleAntecedent();
  ifMuyAbajoAndPosLento->joinWithAND(muyAbajo,posLento);

  FuzzyRuleAntecedent *ifMuyAbajoAndCero_dev_ang = new FuzzyRuleAntecedent();
  ifMuyAbajoAndCero_dev_ang->joinWithAND(muyAbajo,cero_dev_ang);

  FuzzyRuleAntecedent *ifMuyAbajoAndNegLento = new FuzzyRuleAntecedent();
  ifMuyAbajoAndNegLento->joinWithAND(muyAbajo,negLento);

  FuzzyRuleAntecedent *ifMuyAbajoAndNegRapido = new FuzzyRuleAntecedent();
  ifMuyAbajoAndNegRapido->joinWithAND(muyAbajo,negRapido);


  FuzzyRuleConsequent *thenHoraRapido = new FuzzyRuleConsequent();
  thenHoraRapido->addOutput(horaRapido);

  FuzzyRuleConsequent *thenHorario = new FuzzyRuleConsequent();
  thenHorario->addOutput(horario);

  FuzzyRuleConsequent *thenCero_pwm = new FuzzyRuleConsequent();
  thenCero_pwm->addOutput(cero_pwm);

  FuzzyRuleConsequent *thenAntiH = new FuzzyRuleConsequent();
  thenAntiH->addOutput(antiH);

  FuzzyRuleConsequent *thenAntiHRapido = new FuzzyRuleConsequent();
  thenAntiHRapido->addOutput(antiHRapido);

//if muyArriba and posRapido then horaRapido

  FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifMuyArribaAndPosRapido, thenHoraRapido);
  controlAngulo->addFuzzyRule(fuzzyRule1);

//if muyArriba and posLento then horaRapido

  FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifMuyArribaAndPosLento, thenHoraRapido);
  controlAngulo->addFuzzyRule(fuzzyRule2);

//if muyArriba and cero_dev_ang then horaRapido

  FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifMuyArribaAndCero_dev_ang, thenHoraRapido);
  controlAngulo->addFuzzyRule(fuzzyRule3);

  //if muyArriba and negLento then horaRapido

  FuzzyRule *fuzzyRule4 = new FuzzyRule(4, ifMuyArribaAndNegLento, thenHoraRapido);
  controlAngulo->addFuzzyRule(fuzzyRule4);

  //if muyArriba and negRapido then horaLento

  FuzzyRule *fuzzyRule5 = new FuzzyRule(5, ifMuyArribaAndNegRapido, thenHoraRapido);
  controlAngulo->addFuzzyRule(fuzzyRule5);




//if arriba and posRapido then horaRapido

  FuzzyRule *fuzzyRule6 = new FuzzyRule(6, ifArribaAndPosRapido, thenHorario);
  controlAngulo->addFuzzyRule(fuzzyRule6);

//if arriba and posLento then horaRapido

  FuzzyRule *fuzzyRule7 = new FuzzyRule(7, ifArribaAndPosLento, thenHorario);
  controlAngulo->addFuzzyRule(fuzzyRule7);

  //if arriba and cero_dev_ang then horario

  FuzzyRule *fuzzyRule8 = new FuzzyRule(8, ifArribaAndCero_dev_ang, thenHorario);
  controlAngulo->addFuzzyRule(fuzzyRule8);

  //if arriba and negLento then horario

  FuzzyRule *fuzzyRule9 = new FuzzyRule(9, ifArribaAndNegLento, thenHorario);
  controlAngulo->addFuzzyRule(fuzzyRule9);

  //if arriba and negRapido then cero_pwm

  FuzzyRule *fuzzyRule10 = new FuzzyRule(10, ifArribaAndNegRapido, thenHoraRapido);
  controlAngulo->addFuzzyRule(fuzzyRule10);



  //if cero_ang and posRapido then horaRapido

  FuzzyRule *fuzzyRule11 = new FuzzyRule(11, ifCero_angAndPosRapido, thenAntiH);
  controlAngulo->addFuzzyRule(fuzzyRule11);

  //if cero_ang and posLento then horario

  FuzzyRule *fuzzyRule12 = new FuzzyRule(12, ifCero_angAndPosLento, thenCero_pwm);
  controlAngulo->addFuzzyRule(fuzzyRule12);

  //if cero_ang and cero_dev_ang then cero_pwm

  FuzzyRule *fuzzyRule13 = new FuzzyRule(13, ifCero_angAndCero_dev_ang, thenCero_pwm);
  controlAngulo->addFuzzyRule(fuzzyRule13);

  //if cero_ang and negLento then antiH

  FuzzyRule *fuzzyRule14 = new FuzzyRule(14, ifCero_angAndNegLento, thenCero_pwm);
  controlAngulo->addFuzzyRule(fuzzyRule14);

  //if cero_ang and negRapido then antiHRapido

  FuzzyRule *fuzzyRule15 = new FuzzyRule(15, ifCero_angAndNegRapido, thenHorario);
  controlAngulo->addFuzzyRule(fuzzyRule15);



  //if abajo and posRapido then cero_pwm

  FuzzyRule *fuzzyRule16 = new FuzzyRule(16, ifAbajoAndPosRapido, thenAntiHRapido);
  controlAngulo->addFuzzyRule(fuzzyRule16);

  //if abajo and posLento then antiH

  FuzzyRule *fuzzyRule17 = new FuzzyRule(17, ifAbajoAndPosLento, thenAntiH);
  controlAngulo->addFuzzyRule(fuzzyRule17);

  //if abajo and cero_dev_ang then antiH

  FuzzyRule *fuzzyRule18 = new FuzzyRule(18, ifAbajoAndCero_dev_ang, thenAntiH);
  controlAngulo->addFuzzyRule(fuzzyRule18);

  //if abajo and negLento then antiHRapido

  FuzzyRule *fuzzyRule19 = new FuzzyRule(19, ifAbajoAndNegLento, thenAntiH);
  controlAngulo->addFuzzyRule(fuzzyRule19);

  //if abajo and negRapido then antiHRapido

  FuzzyRule *fuzzyRule20 = new FuzzyRule(20, ifAbajoAndNegRapido, thenAntiH);
  controlAngulo->addFuzzyRule(fuzzyRule20);




  //if muyAbajo and posRapido then antiH

  FuzzyRule *fuzzyRule21 = new FuzzyRule(21, ifMuyAbajoAndPosRapido, thenAntiHRapido);
  controlAngulo->addFuzzyRule(fuzzyRule21);

  //if muyAbajo and posLento then antiHRapido

  FuzzyRule *fuzzyRule22 = new FuzzyRule(22, ifMuyAbajoAndPosLento, thenAntiHRapido);
  controlAngulo->addFuzzyRule(fuzzyRule22);

  //if muyAbajo and cero_dev_ang then antiHRapido

  FuzzyRule *fuzzyRule23 = new FuzzyRule(23, ifMuyAbajoAndCero_dev_ang, thenAntiHRapido);
  controlAngulo->addFuzzyRule(fuzzyRule23);

  //if muyAbajo and negLento then antiHRapido

  FuzzyRule *fuzzyRule24 = new FuzzyRule(24, ifMuyAbajoAndNegLento, thenAntiHRapido);
  controlAngulo->addFuzzyRule(fuzzyRule24);

  //if muyAbajo and negRapido then antiHRapido

  FuzzyRule *fuzzyRule25 = new FuzzyRule(25, ifMuyAbajoAndNegRapido, thenAntiHRapido);
  controlAngulo->addFuzzyRule(fuzzyRule25);

}

//Funcion de control difuso
float Difuso::output(float posicion, float angulo, float set_point){

  float set_point_ang = 0, salida=0.0;

  this->error_pos[0] = this->error_pos[1];

  posicion = posicion*(0.13468) - 0.2222;

  this->error_pos[1] = -(set_point - posicion);

  if(this->error_pos[1] > 0.2){
    this->error_pos[1] = 0.19;
  }

  if(this->error_pos[1] < -0.2){
    this->error_pos[1] = -0.19;
  }

  if(this->error_pos[1] < 0.003 && this->error_pos[1] > -0.003){
    this->error_pos[1] = 0;
  }

  this->error_dev_pos[0] = this->error_dev_pos[1];

  this->error_dev_pos[1] = (this->error_pos[1] - this->error_pos[0]) * 31.4 + this->error_dev_pos[0] * 0.6861;

  if(this->error_dev_pos[1] > 0.2){
    this->error_dev_pos[1] = 0.19;
  }

  if(this->error_dev_pos[1] < -0.2){
    this->error_dev_pos[1] = -0.19;
  }

  this->controlPos->setInput(1,this->error_pos[1]);
  this->controlPos->setInput(2,this->error_dev_pos[1]);
  this->controlPos->fuzzify();

  set_point_ang = this->controlPos->defuzzify(1);

  if(set_point_ang > 0.785){
    set_point_ang = 0.77;
  }

  if(set_point_ang < -0.785){
    set_point_ang = -0.77;
  }

  this->error_ang[0] = this->error_ang[1];

  angulo = angulo * (0.6058) - 1.0904;

  this->error_ang[1] = set_point_ang - angulo;

  if(this->error_ang[1] > 0.785){
    this->error_ang[1] = 0.77;
  }

  if(this->error_ang[1] < -0.785){
    this->error_ang[1] = -0.77;
  }

  this->error_dev_ang[1] = (this->error_ang[1] - this->error_ang[0]) / 0.012;

  if(this->error_dev_ang[1] < 0.15 && this->error_dev_ang[1] >-0.15){
    this->error_dev_ang[1] = 0;
  }

  if(this->error_dev_ang[1] > 3){
    this->error_dev_ang[1] = 2.9;
  }

  if(this->error_dev_ang[1] < -3){
    this->error_dev_ang[1] = -2.9;
  }

  this->controlAngulo->setInput(1,error_ang[1]);
  this->controlAngulo->setInput(2,error_dev_ang[1]);
  this->controlAngulo->fuzzify();

  salida = this->controlAngulo->defuzzify(1);

  salida= -(salida / 10.0) + 0.5;
  salida = salida*255.0;

  return salida;
}
