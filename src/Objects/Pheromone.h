#pragma once
#include "GenericObject.h"

class Pheromone
{
public: enum class Type_e; //forward declaration
private:
    GenericObject<Pheromone> m_genericObject;
    Type_e m_type = Type_e::Unknown;

    /// \brief How many frames it takes for the mass of the pheromone to half
    float m_massHalfLife = DEFAULT_HALF_LIFE;

    float m_initialMass;
    unsigned char m_initialAlpha;
public:
    static constexpr float DEFAULT_HALF_LIFE = 256 - 64;
    enum class Type_e {
        Unknown,
        Trail,
        Food,
        Home,
        COUNT
    };
    Pheromone() = default;
    explicit Pheromone(GenericObject<Pheromone> genericObject, Type_e type = Type_e::Unknown, float halfLife = DEFAULT_HALF_LIFE);
    Pheromone(Body body, WorldKnowledge<Pheromone> worldKnowledge, Type_e type = Type_e::Unknown, float halfLife = DEFAULT_HALF_LIFE);

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

    const Type_e &type() const;
};

