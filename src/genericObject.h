#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define DEBBUG_TYPE double
class GenericObject
{
	private:
		void *m_pHomeChunk;

		void m_initPtrShape(DEBBUG_TYPE &object);
		void m_initPtrShape();
	public:
		DEBBUG_TYPE *pShape = nullptr;

		float size;

		void* getPtrHomeChunk();
		void setPtrHomeChunk(void * pChunk);
		
		GenericObject();
		GenericObject(DEBBUG_TYPE &aShape);

		GenericObject(const GenericObject &object);

		~GenericObject();

};

#endif
