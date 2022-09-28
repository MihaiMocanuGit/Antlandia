#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GenericObject
{
	private:
		void* m_pHomeChunk;

	public:
		sf::Vector2f position;

		sf::Color color;

		float size;

		void* getPtrHomeChunk();
		void setPtrHomeChunk(void * pChunk);
		
		GenericObject();
		GenericObject(sf::Vector2f aPosition, sf::Color aColor, float aSize);

};

#endif
