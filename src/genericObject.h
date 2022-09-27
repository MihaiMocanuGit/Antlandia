#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

class GenericObject
{
	private:
		void* pHomeChunk;
	public:
		float coordX;
	       	float coordY;

		int colorCode;
		float colorIntensity; //alpha channel

		int size;

		void* getPtrHomeChunk();
		void setPtrHomeChunk(void * pChunk);
		
		GenericObject(float aX, float aY, void *pHomeChunk);
		void initGenericObject(int aColorCode, float aColorIntensity, float aSize);
};

#endif
