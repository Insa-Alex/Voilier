#ifndef SERVICE_RF_H
#define SERVICE_RF_H


void TIM_RF_Conf(void);
int lecture_rapportcycle(void);
int calc_sens( int rapport_cycle);
int calc_vitesse(int rapport_cycle, int sens);

#endif
