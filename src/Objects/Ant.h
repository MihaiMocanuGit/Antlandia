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

    sf::Vector2f m_home = {-1.0f, -1.0f};
    float m_viewRadius = 96.0f;
    float m_interactRadius = 8.0f;


    Action_e m_action = Action_e::Unknown;

    Food m_grabbedFood;
    sf::Vector2f m_foundFoodPosition = {-1.0f, -1.0f};
    bool m_hasFoundFood = false;
    bool m_hasGrabbedFood = false;

    bool m_followingFoodTrail = false;
public:
    enum class Action_e {
        Unknown, //does nothing for now
        SearchingFood, //walks randomly in the world to search for food, stops when it founds one in viewable distance
        GrabbingFood, //after such food was found, go towards it and grab it
        BringingFood, //searches a trail to go back home after grabbing some food, it marks the way back with pheromones
        SawHomeWhileBringingFood, //saw their home while wandering on a trail towards home. Wander off the trail and go directly home
        Male, // stays home, near queen, maybe they should leave home pheromones?
        Queen, //stays home, makes eggs, maybe should leave home pheromones?
        Egg, // don't know yet
        COUNT
    };

    Ant() = default;
    explicit Ant(GenericObject<Ant> genericObject, Action_e action = Action_e::Unknown, sf::Vector2f home =  {-1.0f, -1.0f} );
    Ant(Body body, WorldKnowledge<Ant> worldKnowledge, Action_e action = Action_e::Unknown, sf::Vector2f home =  {-1.0f, -1.0f} );

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

    sf::Vector2f &home();
    const sf::Vector2f &home() const;

    float &viewRadius();
    const float &viewRadius() const;

    float &interactRadius();
    const float &interactRadius() const;

    float &maxVelocity();
    const float &maxVelocity() const;

    Food &grabbedFood();
    const Food &grabbedFood() const;

    bool &hasFoundFood();
    const bool &hasFoundFood() const;

    bool &hasGrabbedFood();
    const bool &hasGrabbedFood() const;

    sf::Vector2f &foundFoodPosition();
    const sf::Vector2f &foundFoodPosition() const;

    bool &followingFoodTrail();
    const bool &followingFoodTrail() const;
};

