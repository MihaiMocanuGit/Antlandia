#pragma once
#include <vector>
#include "GenericObject.h"





template <typename T>
class ChunkContainer
{
private:
    //elements will
    std::vector<T> m_data = {};
    std::size_t m_eraseStart = 0;
    std::vector<T> m_addBuffer = {};

    SwapFunction_t<T> m_swap;
    [[nodiscard]] inline size_t m_actualDataSize() const;
    [[nodiscard]] inline size_t m_eraseSize() const;
    void m_swapAndUpdate(size_t index1, size_t index2);
    [[nodiscard]] inline bool m_emptyErase() const;

public:
    explicit ChunkContainer(SwapFunction_t<T> swap, size_t reserve = 16);

    GenericObject toBeRemoved(std::size_t index);
    void removeAll();

    void toBeAdded(GenericObject & element);
    void addAll();

    GenericObject& operator[](size_t index);

    inline size_t size() const;

};


template <typename T>
GenericObject ChunkContainer<T>::toBeRemoved(std::size_t index)
{
    m_eraseStart--;

    m_swapAndUpdate(index, m_eraseStart);

    return *m_data[m_eraseStart];
}


template <typename T>
ChunkContainer<T>::ChunkContainer(SwapFunction_t<T> swap, size_t reserve)
    : m_swap{swap}
{
    m_data.reserve(reserve);
    m_addBuffer.reserve(reserve);
}


template <typename T>
size_t ChunkContainer<T>::m_actualDataSize() const
{
    return m_eraseStart;
}


template <typename T>
GenericObject & ChunkContainer<T>::operator[](size_t index)
{
    return *m_data[index];
}


template <typename T>
void ChunkContainer<T>::m_swapAndUpdate(size_t index1, size_t index2)
{
    std::swap(m_data[index1], m_data[index2]);

    m_data[index1]->knowledge().m_indexChunk = index1;
    m_data[index2]->knowledge().m_indexChunk = index2;
}

template <typename T>
bool ChunkContainer<T>::m_emptyErase() const
{
    return m_eraseStart == m_data.size();
}


template <typename T>
void ChunkContainer<T>::toBeAdded(GenericObject &element)
{
    m_addBuffer.push_back(&element);
}


template <typename T>
void ChunkContainer<T>::removeAll()
{
    for (size_t i = 0; i < m_eraseSize(); ++i)
        m_data.pop_back();
}


template <typename T>
size_t ChunkContainer<T>::m_eraseSize() const
{
    return m_data.size() - m_eraseStart;
}


template <typename T>
void ChunkContainer<T>::addAll()
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

template <typename T>
size_t ChunkContainer<T>::size() const
{
    return m_actualDataSize();
}


