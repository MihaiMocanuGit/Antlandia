#pragma once
#include "../ObjectComponents/Body.h"
#include "../ObjectComponents/WorldKnowledge.h"
#include "GenericObject.h"
#include "Food.h"

class Ant
{
public: enum class Action_e; //forward declaration I think
private:
    GenericObject<Ant> m_genericObject;
    sf::Vector2f m_velocity = {0.0f, 0.0f};
    float m_maxVelocity = 1.0f;

    float m_viewRadius = 10.0f;
    float m_interactRadius = 1.0f;


    Action_e m_action = Action_e::Unknown;

    Food m_grabbedOrFoundFood;
    bool m_hasFood = false;
    bool m_foundFood = false;
    sf::Vector2f m_foundFoodPosition = {-1.0f, -1.0f};
public:
    enum class Action_e {
        Unknown, //does nothing for now
        SearchingFood, //walks randomly in the world to search for food, stops when it founds one in viewable distance
        GrabbingFood, //after such food was found, go towards it and grab it
        BringFood, //goes back home after grabbing some food, it marks the way back with pheromones and also takes food home
        Male, // stays home, near queen, maybe they should leave home pheromones?
        Queen, //stays home, makes eggs, maybe should leave home pheromones?
        Egg, // don't know yet
        COUNT
    };

    Ant() = default;
    explicit Ant(GenericObject<Ant> genericObject, Action_e action = Action_e::Unknown);
    Ant(Body body, WorldKnowledge<Ant> worldKnowledge, Action_e action = Action_e::Unknown);

    Body &body();
    const Body &body() const;

    WorldKnowledge<Ant> &knowledge();
    const WorldKnowledge<Ant> &knowledge() const;

    GenericObject<Ant> &genericObject();
    const GenericObject<Ant> &genericObject() const;

    Action_e &action();
    const Action_e &action() const;

    sf::Vector2f &velocity();
    const sf::Vector2f &velocity() const;

    float &viewRadius();
    const float &viewRadius() const;

    float &interactRadius();
    const float &interactRadius() const;

    float &maxVelocity();
    const float &maxVelocity() const;

    Food &grabbedOrFoundFood();
    const Food &grabbedOrFoundFood() const;

    bool &hasFood();
    const bool &hasFood() const;

    bool &foundFood();
    const bool &foundFood() const;

    sf::Vector2f &foundFoodPosition();
    const sf::Vector2f &foundFoodPosition() const;
};

