#include "json_object.h"
#include <string>
using namespace std;
const int  NB_SAMPLE = 100;

struct byteCorner {
	short byte23;
	short byte67;
};
class CEcoConduiteAlogrithm {
private:
	short m_speedVector[NB_SAMPLE];
	byteCorner m_CornerVector[NB_SAMPLE];
	//short m_CornerVector67[NB_SAMPLE];
	JsonObject m_JSonObj;
public:
	CEcoConduiteAlogrithm();
	~CEcoConduiteAlogrithm();
	void ecoConduite_Calc_AccelIndicator();
	void ecoConduite_Calc_DesAccelIndicator();
	void ecoConduite_Calc_LHCorneringAlgorithm();
	void ecoConduite_Calc_RHCorneringAlgorithm();

	void setSpeed(int iIndex, short lValue);
	void setCorner23(int iIndex, short lValue);
	void setCorner67(int iIndex, short lValue);

	long getSpeed(int iIndex);
	long getCorner23(int iIndex);
	long getCorner67(int iIndex);
	JsonObject GetJson();
};
