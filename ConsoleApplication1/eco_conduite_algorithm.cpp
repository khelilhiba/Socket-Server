#include "eco_conduite_algorithm.h"
#include <stdio.h>
#include <thread>

CEcoConduiteAlogrithm::CEcoConduiteAlogrithm()
{	
	string lsJson = "{\"h_acceleration\":0,\"h_deceleration\":0,\"rh_cornening\":0,\"lh_cornening\":0,\"excess_speed\":0,\"excess_idle\":0,\"gauge\":0,\"excess_rpm\":1}";
	m_JSonObj.setStr(lsJson);
}

CEcoConduiteAlogrithm::~CEcoConduiteAlogrithm()
{
}

JsonObject CEcoConduiteAlogrithm::GetJson()
{
	return m_JSonObj;
}

void CEcoConduiteAlogrithm::setSpeed(int iIndex, short lValue) {
	if (iIndex < NB_SAMPLE)
	{
		m_speedVector[iIndex] = lValue;
	}
}

void CEcoConduiteAlogrithm::setCorner23(int iIndex, short lValue) {
	if (iIndex < NB_SAMPLE)
	{
		m_CornerVector[iIndex].byte23 = lValue;
	}
}

void CEcoConduiteAlogrithm::setCorner67(int iIndex, short lValue) {
	if (iIndex < NB_SAMPLE)
	{
		m_CornerVector[iIndex].byte67 = lValue;
	}
}

long CEcoConduiteAlogrithm::getSpeed(int iIndex) {
	if (iIndex < NB_SAMPLE)
	{
		return m_speedVector[iIndex];
	}
	else
	{
		return 0;
	}
}

long CEcoConduiteAlogrithm::getCorner23(int iIndex) {
	if (iIndex < NB_SAMPLE)
	{
		return m_CornerVector[iIndex].byte23;
	}
	else
	{
		return 0;
	}
}

long CEcoConduiteAlogrithm::getCorner67(int iIndex) {
	if (iIndex < NB_SAMPLE)
	{
		return m_CornerVector[iIndex].byte67;
	}
	else
	{
		return 0;
	}
}

int a = 1;
int b = 0;
void CEcoConduiteAlogrithm::ecoConduite_Calc_AccelIndicator()
{
   int k=0;
   long VSpeedPrev = 0;
   float Accel, Accel_old=0.0, Medial_Accel;
   float Time_Since_Last_Sample = 10.0;
   float number_of_samples = 0.0;
   float Accel_counter = 0;
   float Acceleration_Parameter = 0.16;
   float Acceleration_Time_Parameter = 0.25/0.01;
   const char *Accel_Led="No";
 
#if 0
   for (k = 0; k < 100; k++)
  { 
   number_of_samples++;
   Accel = m_speedVector[k] - VSpeedPrev;
   Accel = Accel * 10000.0;
   Accel = Accel / Time_Since_Last_Sample;
   Accel = Accel / (float)256;
   Accel = Accel / (float)35;
   Medial_Accel = Accel_old / number_of_samples;
   
   if (Medial_Accel > Acceleration_Parameter)
	   Accel_counter++;
// else Accel_counter = 0; à vérifier page 16 du doc
     Accel_old = Accel;  
     VSpeedPrev = m_speedVector[k];
   }
#endif
  //if (Accel_counter > Acceleration_Time_Parameter)
  if(a==0)
   {
	   m_JSonObj.setJsonAttribute("h_acceleration", 1);
	   cout << " UP accel" << endl;
	   a = 1;
   }
   else
   {
	   m_JSonObj.setJsonAttribute("h_acceleration", 0);
	   cout << " Dowm accel" <<  endl;
	   a = 0;
   }  
}


void CEcoConduiteAlogrithm::ecoConduite_Calc_DesAccelIndicator()
{
	int k = 0;
	long VSpeedPrev = 0;
	float DesAccel, DesAccel_old = 0.0, Medial_DesAccel;
	float Time_Since_Last_Sample = 10.0;
	float number_of_samples = 0.0;
	float DesAccel_counter = 0;
	float DesAcceleration_Parameter = 0.2;
	float DesAcceleration_Time_Parameter = 0.25 / 0.01;
	const char* DesAccel_Led = "Des_No";

	#if 0
	for (k = 0; k < 100; k++)
	{
		number_of_samples++;
		DesAccel = m_speedVector[k] - VSpeedPrev;
		DesAccel = DesAccel * 10000.0;
		DesAccel = DesAccel / Time_Since_Last_Sample;
		DesAccel = DesAccel / (float)256;
		DesAccel = DesAccel / (float)35;
		Medial_DesAccel = DesAccel_old / number_of_samples;

		if ((Medial_DesAccel*(-1)) > DesAcceleration_Parameter)
			DesAccel_counter++;
	// else Accel_counter = 0; à vérifier page 16 du doc
		DesAccel_old = DesAccel;
		VSpeedPrev = m_speedVector[k];
	}
	#endif
	//if (DesAccel_counter > DesAcceleration_Time_Parameter)
		 if(b==0)
	{
		m_JSonObj.setJsonAttribute("h_deceleration", 1);
		cout << " Des_UP accel" << endl;
		b = 1;
	}
	else
	{
		m_JSonObj.setJsonAttribute("h_deceleration", 0);
		cout << " Des_Dowm accel" << endl;
		b = 0;
	}
}


void CEcoConduiteAlogrithm::ecoConduite_Calc_LHCorneringAlgorithm()
{
	float LatAcc, LatAccel, LatAccelOffset;
	float number_of_samples = 0.0;
	float Corning_Parameter = 0.3;
	float Corning_Time_Parameter = 0.25 / 0.01;
	int LH_Corner_Counter = 0; 
	float LatAccel_old = 0;
#if 0
	for (int k = 0; k < 100; k++)
	{
		LatAcc   = m_CornerVector[k].byte67;
		LatAccel = LatAcc - 32126;
		LatAccel = LatAccel / 8;
		LatAccel = LatAccel * 10;
		LatAccel = LatAccel / 98;
		LatAccel = (LatAccel * 100) / 256;

		LatAccelOffset = m_CornerVector[k].byte23;
		LatAccelOffset = LatAccelOffset - 32126;
		LatAccelOffset = LatAccelOffset / 8;
		LatAccelOffset = LatAccelOffset * 10;
		LatAccelOffset = LatAccelOffset / 98;
		LatAccelOffset = (LatAccelOffset * 100) / 256;

		if (LatAccel >= 0) LatAccel += LatAccelOffset;
		if (LatAccel < 0)  LatAccel -= LatAccelOffset;

		LatAccel = LatAccel_old / number_of_samples;
		LatAccel_old = LatAccel;
		if (LatAccel > Corning_Parameter)
			LH_Corner_Counter++;
	}
#endif
		//if (LH_Corner_Counter > Corning_Time_Parameter)
		if(a==0)
		{
			m_JSonObj.setJsonAttribute("lh_cornening", 1);
			cout << " LH Corning : UP " << endl;
			a = 1;
		}
		else
		{
			m_JSonObj.setJsonAttribute("lh_cornening", 0);
			cout << " LH Corning : Down " << endl;
			a = 0;
		}

	
}



void CEcoConduiteAlogrithm::ecoConduite_Calc_RHCorneringAlgorithm()
{
	float LatAcc, LatAccel, LatAccelOffset;
	float number_of_samples = 0.0;
	float Corning_Parameter = 0.3;
	float Corning_Time_Parameter = 0.25 / 0.01;
	int RH_Corner_Counter = 0;
	float LatAccel_old = 0;
#if 0
	for (int k = 0; k < 100; k++)
	{
		LatAcc = m_CornerVector[k].byte67;
		LatAccel = LatAcc - 32126;
		LatAccel = LatAccel / 8;
		LatAccel = LatAccel * 10;
		LatAccel = LatAccel / 98;
		LatAccel = (LatAccel * 100) / 256;

		LatAccelOffset = m_CornerVector[k].byte23;
		LatAccelOffset = LatAccelOffset - 32126;
		LatAccelOffset = LatAccelOffset / 8;
		LatAccelOffset = LatAccelOffset * 10;
		LatAccelOffset = LatAccelOffset / 98;
		LatAccelOffset = (LatAccelOffset * 100) / 256;

		if (LatAccel >= 0) LatAccel += LatAccelOffset;
		if (LatAccel < 0)  LatAccel -= LatAccelOffset;

		LatAccel = LatAccel_old / number_of_samples;
		LatAccel_old = LatAccel;
		if ((LatAccel * (-1)) > Corning_Parameter)
			RH_Corner_Counter++;
	}

#endif
		//if (RH_Corner_Counter > Corning_Time_Parameter)
		if (b == 0)
		{
			m_JSonObj.setJsonAttribute("rh_cornening", 1);
			cout << " RH Corning : UP " << endl;
			b = 1;
		}
		else
		{
			m_JSonObj.setJsonAttribute("rh_cornening", 0);
			cout << " RH Corning : Down " << endl;
			b = 0;
		}

	
}