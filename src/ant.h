#include "genericObject.h"


class Ant : public  GenericObject
{
	private: 
		int m_statusCode; //to be defined later, ex 0 = standby, 1 = searching etc
	public:
		float health;
		float energy;
		float velDirX, velDirY;
		//vector, need to be normalized to 1
		
		int getStatusCode();
		void setStatusCode(int statusCode);


		Ant(float aX, float aY, void *aPHomeChunk);// : GenericObject(aX, aY, pHomeChunk);
		void initAnt(float aHealth, float aEnergy, float aVelDirX, float aVelDirY);

};


