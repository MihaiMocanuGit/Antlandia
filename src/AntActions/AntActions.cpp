#include <random>
#include "AntActions.h"

namespace AntActions
{
float m_getRandomUniformly(float min, float max)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> distrib(min, max);

    return distrib(gen);
}

float m_norm(const sf::Vector2f &vector)
{
    return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

/// \brief
/// \param r_vector Non-zero vector
/// \param clampNorm
void m_clampVectorByNorm(sf::Vector2f &r_vector, float clampNorm)
{
    r_vector = clampNorm / m_norm(r_vector) * r_vector;
}

void m_changeVelocity(Ant &r_ant)
{
    //add to the current velocity a random change
    sf::Vector2f oldVelocity = r_ant.velocity();

    const sf::Vector2f boundsOfChange = {0.15f, 0.15f};
    sf::Vector2f newVelocity = {m_getRandomUniformly(oldVelocity.x - boundsOfChange.x, oldVelocity.x + boundsOfChange.x),
                                m_getRandomUniformly(oldVelocity.y - boundsOfChange.y, oldVelocity.y + boundsOfChange.y)};

    if (m_norm(newVelocity) > r_ant.maxVelocity())
        m_clampVectorByNorm(newVelocity, r_ant.maxVelocity());

    r_ant.velocity() = newVelocity;
}

void m_findClosestFood(Ant &r_ant, World &r_world)
{
    assert(not r_world.map().isPositionOutsideBounds(r_ant.body().getPosition()));

    //we need to check the chunks that intersect with the ant's interact radius,
    //so we compute the bounds of the zone of interaction
    const sf::Vector2f center = r_ant.body().getPosition();
    const float MAX_VALUE_X = (float)r_world.size().x * Chunk<int>::CHUNK_SIZE_X;
    const float MAX_VALUE_Y = (float)r_world.size().y * Chunk<int>::CHUNK_SIZE_Y;

    //we clamp the bounds inside the world bound
    float left = std::clamp(center.x - r_ant.viewRadius(), 0.0f, MAX_VALUE_X);
    float right = std::clamp(center.x + r_ant.viewRadius(), 0.0f, MAX_VALUE_X);

    float up = std::clamp(center.y - r_ant.viewRadius(), 0.0f, MAX_VALUE_Y);
    float down = std::clamp(center.y + r_ant.viewRadius(), 0.0f, MAX_VALUE_Y);

    //as we computed the bounds of the coordinates, we see their respective chunks
    const sf::Vector2i centerChunk = r_world.map().computeChunkIndex(center);
    const sf::Vector2i leftChunk = r_world.map().computeChunkIndex({left, center.y});
    const sf::Vector2i rightChunk = r_world.map().computeChunkIndex({right, center.y});
    const sf::Vector2i upChunk = r_world.map().computeChunkIndex({center.x, up});
    const sf::Vector2i downChunk = r_world.map().computeChunkIndex({center.x, down});


    // we iterate through all chunk zone that would be contained inside the interact radius
    // we go through a rectangular zone, if needed, this could be sped up by going through
    // a circular zone
    //TODO: Change the traversal order, start from center and go in a Breadth first traversal instead

    //We check the distance between all food particles in the interact region, and choose the closest one
    float closestFoodDistance = MAXFLOAT;
    sf::Vector2i closestFoodChunk = {-1, -1};
    size_t closestFoodIndexInWorld = -1;
    for (int y = upChunk.y; y <= downChunk.y; ++y)
    {
        for (int x = leftChunk.x; x <= rightChunk.x ; ++x)
        {
            auto &chunkFood = r_world.map().at(x,y).ref_foodChunk.objects;

            for (size_t i = 0; i < chunkFood.size(); ++i)
            {
                const Food &food = r_world.food()[chunkFood[i].index];
                const sf::Vector2f distanceVector = food.body().getPosition() - center;
                const float distanceToFood = m_norm(distanceVector);
                if (distanceToFood < r_ant.viewRadius())
                {
                    if (distanceToFood < closestFoodDistance and not food.isLocked())
                    {
                        closestFoodChunk = {x, y};
                        closestFoodIndexInWorld = i;

                        r_ant.action() = Ant::Action_e::GrabbingFood;
                    }
                }
            }
        }
    }

    //if we did find a valid food particle, init r_ant.foundFoodPosition() with its position
    //this way we will go toward that location in the next Action, i.e Ant::Action_e::GrabbingFood
    //We also copy the food into the ant's "inventory" but we will keep this hidden until we actually
    //get to the food (by hidden, I mean that we will not render it to the screen)
    //when we do get to the food position, TODO: search for it again in the chunk and remove it???
    if (r_ant.action() == Ant::Action_e::GrabbingFood)
    {
        //lock into the found food
        Food &r_food = r_world.food()[closestFoodIndexInWorld];
        r_food.isLocked() = true;
        r_ant.foundFood() = true;
        r_ant.foundFoodPosition() = r_food.body().getPosition();
        r_ant.grabbedOrFoundFood() = r_food;

        //go full speed towards that food
        sf::Vector2f newVelocity = r_ant.body().getPosition() - r_ant.foundFoodPosition();
        m_clampVectorByNorm(newVelocity, r_ant.maxVelocity());
        r_ant.velocity() = newVelocity;
    }



}

void searchFood(Ant &r_ant, World &r_world, unsigned currentFrame)
{
    m_changeVelocity(r_ant);
    m_findClosestFood(r_ant, r_world);
}
void foundFood(Ant &r_ant, World &r_world, unsigned currentFrame)
{

}

} //end AntActions namespace