

class GenericObject
{
	private:
		void* pHomeChunk;
	public:
		int coordX, coordY;

		int colorCode;
		int colorIntensity; //alpha channel

		int size;

		void* getPtrHomeChunk();
		void setPtrHomeChunk(void * pChunk);

};


void testGenObject();
