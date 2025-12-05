#include "motor.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "tim.h"
#include "motor.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PPR 1320;
#define RTD 360/1320;


void MotorSetDuty1(int nDuty)
{
	if(nDuty == 0){
		htim3.Instance->CCR1 = 0;
		htim3.Instance->CCR2 = 0;
	}
	else if(nDuty > 0){
		htim3.Instance->CCR2 = nDuty+500;
		htim3.Instance->CCR1 = 0;
	}
	else if(nDuty < 0){
		htim3.Instance->CCR2 = 0;
		htim3.Instance->CCR1 = abs(nDuty-500);
	}

}

void MotorSetDuty2(int nDuty)
{
	if(nDuty == 0){
		htim3.Instance->CCR3 = 0;
		htim3.Instance->CCR4 = 0;
	}
	else if(nDuty>0){
		htim3.Instance->CCR4 = nDuty;
		htim3.Instance->CCR3 = 0;
	}
	else if(nDuty<0){
		htim3.Instance->CCR4 = 0;
		htim3.Instance->CCR3 = abs(nDuty);
	}

}