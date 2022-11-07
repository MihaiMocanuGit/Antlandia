#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class GenericObject
{
	private:

		void m_initPtrShape(sf::CircleShape &object);
		void m_initPtrShape();

		void *m_pHomeChunk = nullptr;
	public:
		

		//need to make this private and only get and set what i need
		sf::CircleShape *pShape = nullptr;
		sf::Vector2f velocity;

		//void* getPtrHomeChunk();
		//void setPtrHomeChunk(void * pChunk);
		
		GenericObject();
		GenericObject(sf::CircleShape &aShape, sf::Vector2f aVelocity);

		GenericObject(const GenericObject &object);

		~GenericObject();

		void moveTo(sf::Vector2f position);
		void moveBy(sf::Vector2f offset);

		void setPtrHomeChunk(void *pHomeChunk);


};

#endif
