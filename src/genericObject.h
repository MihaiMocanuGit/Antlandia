#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GenericObject
{
	private:
		void *m_pHomeChunk;

		sf::CircleShape *m_initPtrShape(sf::CircleShape object);

	public:
		sf::CircleShape *pShape = nullptr;
		sf::Color color;

		float size;

		void* getPtrHomeChunk();
		void setPtrHomeChunk(void * pChunk);
		
		GenericObject();
		GenericObject(sf::CircleShape aShape);

		~GenericObject();

};

#endif
