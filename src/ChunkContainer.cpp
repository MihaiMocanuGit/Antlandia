
#include "ChunkContainer.h"

GenericObject ChunkContainer::toBeRemoved(std::size_t index)
{
    m_eraseStart--;

    m_swapAndUpdate(index, m_eraseStart);

    return *m_data[m_eraseStart];
}

ChunkContainer::ChunkContainer(size_t reserve)
{
    m_data.reserve(reserve);
    m_addBuffer.reserve(reserve);
}

size_t ChunkContainer::m_actualDataSize() const
{
    return m_eraseStart;
}

GenericObject & ChunkContainer::operator[](size_t index)
{
    return *m_data[index];
}

void ChunkContainer::m_swapAndUpdate(size_t index1, size_t index2)
{
    std::swap(m_data[index1], m_data[index2]);

    m_data[index1]->knowledge().m_indexChunk = index1;
    m_data[index2]->knowledge().m_indexChunk = index2;
}

bool ChunkContainer::m_emptyErase() const
{
    return m_eraseStart == m_data.size();
}

void ChunkContainer::toBeAdded(GenericObject &element)
{
    m_addBuffer.push_back(&element);
}

void ChunkContainer::removeAll()
{
    for (size_t i = 0; i < m_eraseSize(); ++i)
        m_data.pop_back();
}

size_t ChunkContainer::m_eraseSize() const
{
    return m_data.size() - m_eraseStart;
}

void ChunkContainer::addAll()
{

    size_t noNewElements = m_addBuffer.size();
    for (size_t i = 0; i < noNewElements; ++i)
    {
        //pull out the last element and add it to the back of the data vector
        m_data.push_back(m_addBuffer.back());
        m_addBuffer.pop_back();

        //move the newly added element from the back of the whole vector to the back
        //of the active elements region
        //the first element that is supposed to be deleted will be moved to the back o
        //of the whole vector
        m_swapAndUpdate(m_eraseStart, m_data.size() - 1);

        //translate the region of erased element one unit to the right to make the start
        //region valid again
        m_eraseStart++;
    }

}

size_t ChunkContainer::size() const
{
    return m_actualDataSize();
}

