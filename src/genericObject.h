#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class GenericObject
{
	private:

		void m_initPtrShape(sf::CircleShape &object);
		void m_initPtrShape();

	protected:

		void *m_pHomeChunk = nullptr;


		sf::CircleShape *m_pShape = nullptr;
		sf::Vector2f m_velocity;

	public:
		



		//void* getPtrHomeChunk();
		//void setPtrHomeChunk(void * pChunk);
		
		GenericObject();
		GenericObject(sf::CircleShape &aShape, sf::Vector2f aVelocity);

		GenericObject(const GenericObject &object);

		~GenericObject();

		void moveTo(sf::Vector2f position);
		void moveBy(sf::Vector2f offset);

		void setPtrHomeChunk(void *pHomeChunk);

		const sf::Vector2f &getPosition() const;
		void setPosition(sf::Vector2f position);
		
		const sf::CircleShape &getShape() const;



};

#endif
