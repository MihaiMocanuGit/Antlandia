#pragma once
#include "ChunkMap.h"
#include "../Utils/Utils.h"
#include "../WorldActions/ObjectMover.h"
#include "../WorldActions/ObjectSpawner.h"
#include "../ObjectTypes/PheromoneTypes.h"
#include "../ObjectTypes/AntTypes.h"



#include <cassert>

/// \brief Represents the structure of the world.
class World
{
private:
    /// \brief the chunks are stored here, meaning this is the "physical" representation
    /// of the world.
    ChunkMap m_map = {};

    /// \brief All Ants that appear in the world exist in here.
    SpecializedVector<Ant> m_ants{INIT_ADD_WORLD, INIT_REMOVE_WORLD, INIT_FINALISE_WORLD, SWAP_WORLD, DESTRUCT_WORLD};
    /// \brief All Pheromones that appear in the world exist in here.
    SpecializedVector<Pheromone> m_pheromones{INIT_ADD_WORLD, INIT_REMOVE_WORLD, INIT_FINALISE_WORLD, SWAP_WORLD, DESTRUCT_WORLD};
    /// \brief All the Food that appears in the world exists in here.
    SpecializedVector<Food> m_food{INIT_ADD_WORLD, INIT_REMOVE_WORLD, INIT_FINALISE_WORLD, SWAP_WORLD, DESTRUCT_WORLD};

    /// \brief Helper class used for spawning entities into the world.
    ObjectSpawner m_spawner;

    /// \brief Helper class used for moving entities inside the world.
    ObjectMover m_mover;

    /// \brief Used for syncing the information between the World and Chunk specialized vector.
    /// \tparam T Object following the structure of TemplateForObject class. Meaning it must be constructable from just
    /// a GenericObject.
    /// \param elem Given element from world vector.
    /// \param newIndex The index it will obtain after this step.
    template <class T>
    static void m_syncHomeChunkVectorInfoWithWorld(T& elem, size_t newIndex);

    /// \brief Used for syncing the information between the World and Chunk specialized vector.
    /// \tparam T Object following the structure of TemplateForObject class. Meaning it must be constructable from just
    /// a GenericObject.
    /// \param elem Given element from world vector.
    /// \param newIndex The index it will obtain after this step.
    template <class T>
    static void m_syncNextChunkVectorInfoWithWorld(T& elem, size_t newIndex);

    /// \brief Used for SpecializedVector.
    /// \tparam T Object following the structure of TemplateForObject class.
    /// \param elem Given element that has just been added into the "add buffer".
    /// \param indexWorld The index it will get after this step.
    template <typename T>
    static void INIT_ADD_WORLD(T &elem, ptrdiff_t indexWorld);

    /// \brief Used for SpecializedVector.
    /// \tparam T Object following the structure of TemplateForObject class.
    /// \param elem Given element that has just been marked for removal.
    /// \param indexWorld The new index it will get after this step.
    template <typename T>
    static void INIT_REMOVE_WORLD(T &elem, ptrdiff_t indexWorld);

    /// \brief Used for SpecializedVector.
    /// \tparam T Object following the structure of TemplateForObject class.
    /// \param elem Given element that has finally been added into the vector.
    /// \param indexWorld The new index it will get after this step.
    template <typename T>
    static void INIT_FINALISE_WORLD(T &elem, ptrdiff_t indexWorld);

    /// \brief Used for SpecializedVector. It is used internally for swapping to elements, therefore it has the
    /// responsibility of swapping the give 2 elements.
    /// \tparam T Object following the structure of TemplateForObject class.
    /// \param elem1 Element from the vector.
    /// \param atIndex1 The index it exists at.
    /// \param elem2 Element from the vector.
    /// \param atIndex2 The index it exists at.
    template <typename T>
    static void SWAP_WORLD(T &elem1, ptrdiff_t atIndex1, T &elem2, ptrdiff_t atIndex2);

    /// \brief Used for SpecializedVector.
    /// \tparam T Object following the structure of TemplateForObject class.
    /// \param elem Given element that is about to be permanently removed.
    /// \param indexWorld The index it had in the vector.
    template <typename T>
    static void DESTRUCT_WORLD(T &elem, ptrdiff_t indexWorld);
public:
    /// \brief Shortcut class used to obtain already created pheromones of a given type
    const PheromoneTypes pheromoneTypes = {this, &m_pheromones, &map().primitiveChunkMaps().pheromoneMap};

    /// \brief Shortcut class used to obtain already created ant of a given type
    const AntTypes antTypes = {this, &m_ants, &map().primitiveChunkMaps().antMap};

    World();

    /// \brief Constructs the world
    /// \param size The size refers to the number of chunks in the world, it does not refer to a pixel size.
    explicit World(sf::Vector2u size);

    /// \brief Constructs the world
    /// \param sizeX The size refers to the width of the world in number of chunks, it does not refer to a pixel size.
    /// \param sizeY The size refers to the height of the world in number of chunks, it does not refer to a pixel size.
    World(unsigned sizeX, unsigned sizeY);



    /// \brief Obtain the ChunkMap
    /// \return
    ChunkMap& map();

    /// \brief Moves an object in the world to the given position.
    /// \tparam T Type of an object existing in the world (e.g. Ant/Pheromone/Food).
    /// \param object A valid object that exists in the world vector.
    /// \param newPosition A valid position inside the world.
    template <class T>
    void moveTo(GenericObject<T> &object, const sf::Vector2f &newPosition);

    /// \brief Moves an object in the world by the given amount.
    /// \tparam T Type of an object existing in the world (e.g. Ant/Pheromone/Food).
    /// \param object A valid object that exists in the world vector.
    /// \param moveByOffset The offset added to the object's position must be inside the world.
    template <class T>
    void moveBy(GenericObject<T> &object, const sf::Vector2f &moveByOffset);


    SpecializedVector<Ant>& ants();
    const SpecializedVector<Ant>& ants() const;

    SpecializedVector<Pheromone>& pheromones();
    const SpecializedVector<Pheromone>& pheromones() const;

    SpecializedVector<Food>& food();
    const SpecializedVector<Food>& food() const;

    /// \brief Obtains the width and height of the world in number of chunks
    /// \return
    [[nodiscard]] sf::Vector2u size() const;

    /// \brief Creates and adds an object to the temporal buffers in the world and chunk.
    /// \param position Valid position in the world.
    /// \param size Size of entity.
    /// \param mass Mass of entity.
    /// \param color Color of Entity.
    /// \return A reference to the Ant from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Ant& prepareAnt(sf::Vector2f position, float size = 2, float mass = 1,
                    const sf::Color &color = {0, 0, 0});

    /// \brief Creates and adds an object to the temporal buffers in the world and chunk.
    /// \param antBody Valid Ant Body.
    /// \return A reference to the Ant from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Ant& prepareAnt(const  Body& antBody);

    /// \brief Creates and adds an object to the temporal buffers in the world and chunk.
    /// \param ant Valid Ant object
    /// \return A reference to the Ant from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Ant& prepareAnt(const Ant& ant);

    /// \brief Creates and adds an object to the temporal buffers in the world and chunk.
    /// \param position Valid position in the world.
    /// \param size Size of entity.
    /// \param mass Mass of entity.
    /// \param color Color of Entity.
    /// \return A reference to the Pheromone from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Pheromone& preparePheromone(sf::Vector2f position, float size = 1, float mass = 1,
                                const sf::Color &color = {0, 255, 0});

    /// \brief Creates and adds an object to the temporal buffers in the world and chunk.
    /// \param pheromoneBody Valid Pheromone Body.
    /// \return A reference to the Pheromone from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Pheromone& preparePheromone(const Body& pheromoneBody);

    /// \brief Creates and adds an object to the temporal buffers in the world and chunk.
    /// \param pheromone Valid Pheromone object
    /// \return A reference to the Pheromone from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Pheromone& preparePheromone(const Pheromone& pheromone);

    /// \brief Creates and adds an object to the temporal buffers in the world and chunk.
    /// \param position Valid position in the world.
    /// \param size Size of entity.
    /// \param mass Mass of entity.
    /// \param color Color of Entity.
    /// \return A reference to the Food from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Food& prepareFood(sf::Vector2f position, float size = 1.5, float mass = 1,
                      const sf::Color &color = {255, 0, 0});

    /// \brief Creates and adds an object to the temporal buffers in the world and chunk.
    /// \param foodBody Valid Food Body.
    /// \return A reference to the Food from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Food& prepareFood(const Body& foodBody);

    /// \brief Creates and adds an object to the temporal buffers in the world and chunk.
    /// \param food Valid Food object
    /// \return A reference to the Food from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Food& prepareFood(const Food& food);

    /// \brief Spawns a new pheromone from an ant existing in the world.
    /// \param ant The ant which will spawn the pheromone.
    /// \param pheromone The body of the new pheromone, the body's position will be changed but the rest of the fiels
    /// will be kept.
    /// \return A reference to the Pheromone from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Pheromone& makeAntSpawnPheromone(const Ant &ant, const Pheromone &pheromone);

    /// \brief Spawns a new pheromone from an ant existing in the world.
    /// \param ant The ant which will spawn the pheromone.
    /// \param pheromone The body of the new pheromone, the body's position will be changed but the rest of the fiels
    /// will be kept.
    /// \return A reference to the Pheromone from the temporal add buffer of the world vector. It will be invalidated after a
    /// call to finalise().
    Pheromone& makeAntSpawnPheromone(const Ant &ant, const Body &pheromoneBody);

};


template <class T>
void World::m_syncHomeChunkVectorInfoWithWorld(T &elem, size_t newIndex)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    sf::Vector2i homeChunkIndexes = r_knowledge.homeChunkIndexes();
    size_t linearHomeChunkIndex = xyToIndex(homeChunkIndexes.x, homeChunkIndexes.y, r_knowledge.world().size().x);

    Chunk<T> &r_home = r_knowledge.primitiveChunkMap().at(linearHomeChunkIndex);
    ptrdiff_t indexInChunk = r_knowledge.indexInHomeChunk();
    auto &r_chunkElement = r_home.objects.at(indexInChunk);
    r_chunkElement.index = newIndex;
}

template <class T>
void World::m_syncNextChunkVectorInfoWithWorld(T &elem, size_t newIndex)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    sf::Vector2i nextChunkIndexes = r_knowledge.nextChunkIndexes();
    size_t linearNextChunkIndex = xyToIndex(nextChunkIndexes.x, nextChunkIndexes.y, r_knowledge.world().size().x);

    Chunk<T> &r_next = r_knowledge.primitiveChunkMap().at(linearNextChunkIndex);
    ptrdiff_t indexInChunk = r_knowledge.indexInNextChunk();
    auto &r_chunkElement = r_next.objects.at(indexInChunk);
    r_chunkElement.index = newIndex;
}

template <typename T>
void World::INIT_ADD_WORLD(T &elem, ptrdiff_t indexWorld)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    r_knowledge.giveIndexInWorld(indexWorld);

    //at this point the element should not exist in a chunk
    assert(not r_knowledge.willAppearInHomeChunk());
    assert(not r_knowledge.willAppearInNewChunk());
}

template <typename T>
void World::INIT_REMOVE_WORLD(T &elem, ptrdiff_t indexWorld)
{

}

template <typename T>
void World::INIT_FINALISE_WORLD(T &elem, ptrdiff_t indexWorld)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    r_knowledge.giveIndexInWorld(indexWorld);

    if (r_knowledge.willAppearInHomeChunk())
        m_syncHomeChunkVectorInfoWithWorld(elem, indexWorld);
    if (r_knowledge.willAppearInNewChunk())
        m_syncNextChunkVectorInfoWithWorld(elem, indexWorld);
}


template <typename T>
void World::SWAP_WORLD(T &elem1, ptrdiff_t atIndex1, T &elem2, ptrdiff_t atIndex2)
{
    std::swap(elem1, elem2);

    //in a chunk we have a vector of indexes pointing to the index of said element
    //in the World vector. As such, if the position of an element in the world vector
    //is changed, we need to update the chunk vector too.
    WorldKnowledge<T> &r_knowledge1 = elem1.knowledge();
    r_knowledge1.giveIndexInWorld(atIndex1);
    if (r_knowledge1.willAppearInHomeChunk())
        m_syncHomeChunkVectorInfoWithWorld(elem1, atIndex1);
    if (r_knowledge1.willAppearInNewChunk())
        m_syncNextChunkVectorInfoWithWorld(elem1, atIndex1);

    WorldKnowledge<T> &r_knowledge2 = elem2.knowledge();
    r_knowledge2.giveIndexInWorld(atIndex2);
    if (r_knowledge2.willAppearInHomeChunk())
        m_syncHomeChunkVectorInfoWithWorld(elem2, atIndex2);
    if (r_knowledge2.willAppearInNewChunk())
        m_syncNextChunkVectorInfoWithWorld(elem2, atIndex2);

}

template <typename T>
void World::DESTRUCT_WORLD(T &elem, ptrdiff_t indexWorld)
{
    WorldKnowledge<T> &r_knowledge = elem.knowledge();
    //TODO: Maybe call remove on chunks too? We would need access to remove from the addBuffer

}



template <class T>
void World::moveBy(GenericObject<T> &object, const sf::Vector2f &moveByOffset)
{
    assert (object.knowledge().willAppearInHomeChunk());
    m_mover.moveBy(object, moveByOffset);
}

template <class T>
void World::moveTo(GenericObject<T> &object, const sf::Vector2f &newPosition)
{
    assert (object.knowledge().willAppearInHomeChunk());
    m_mover.moveTo(object, newPosition);
}

