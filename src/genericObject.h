#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GenericObject
{
	private:

		void m_initPtrShape(sf::CircleShape &object);
		void m_initPtrShape();
	public:
		void *m_pHomeChunk = nullptr;

		sf::CircleShape *pShape = nullptr;

		float size;

		//void* getPtrHomeChunk();
		//void setPtrHomeChunk(void * pChunk);
		
		GenericObject();
		GenericObject(sf::CircleShape &aShape);

		GenericObject(const GenericObject &object);

		~GenericObject();

};

#endif
