#pragma once
#include "GenericObject.h"

class Pheromone
{
private:
    GenericObject<Pheromone> m_genericObject;

    /// \brief How many frames it takes for the mass of the pheromone to half
    float m_massHalfLife = 90;
public:
    inline const static Body DEFAULT_PHEROMONE_BODY = {sf::Vector2f{-1.0f, -1.0f}, 1.0f, 1.0f,
                                                       sf::Vector3<unsigned char>{0, 255, 0}};
    Pheromone() = default;
    explicit Pheromone(GenericObject<Pheromone> genericObject);
    Pheromone(Body body, WorldKnowledge<Pheromone> worldKnowledge);

    /// \brief Lowers the mass of the pheromone relative to its half life, taking into account
    /// the number of frames that have passed. A lower pheromone mass implies a weaker potency
    /// \param noFramesPassed The number of frames the function considers it has passed. It's
    /// taken into account for the half-live calculation
    /// \param almostZero If the mass of the object becomes <= than almostZero, we consider it
    /// to be zero. Therefore, the pheromone will vanish at that point;
    /// \return true if said pheromone still exists, or false if it vanished
    bool decreasePotency(unsigned noFramesPassed = 1, float almostZero = 0.0001f);

    Body &body();
    const Body &body() const;

    WorldKnowledge<Pheromone> &knowledge();
    const WorldKnowledge<Pheromone> &knowledge() const;

    GenericObject<Pheromone> &genericObject();
    const GenericObject<Pheromone> &genericObject() const;
};

