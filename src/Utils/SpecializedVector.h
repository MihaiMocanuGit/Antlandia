#pragma once
#include <vector>
#include <stdexcept>


/// \tparam T copy-constructable and copy-assignable element
template <typename T>
class SpecializedVectorIterator;

template <typename T>
class SpecializedVector
{
    friend SpecializedVectorIterator<T>;
private:
    std::vector<T> m_data = {};

    /// \brief additional vector where we temporally store the elements that will later be added
    std::vector<T> m_addBuffer = {};

    /// \brief additional vector where we temporally store the indexes of elements that will later be removed
    std::vector<size_t > m_removeBuffer = {};

    InitFunction_t<T> m_init;
    SwapFunction_t<T> m_swap;
    DestructFunction_t<T> m_destruct;


public:

    SpecializedVector(InitFunction_t<T> init, SwapFunction_t<T> swap, DestructFunction_t<T> destruct, size_t reserve = 128);
    ptrdiff_t toBeAdded(T &&element);

    ptrdiff_t toBeAdded(T &element);

    //TODO: Maybe add separate option to just remove or just add
    void finishChanges();


    T& toBeRemoved(std::size_t index);

    /// \brief Gets an element only from the section of already added elements.
    /// \param index
    /// \return Reference to the element at the given index
    /// \note Bounds are not checked.
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    /// \brief Gets an element from the vector. If the given index is negative, then it will access the elements that
    /// were marked for insertion. The indexing for these elements start at -1
    /// \param index The index of the element you want to access, can be negative
    /// \return Reference to the given object
    /// \note Bounds are checked
    /// \throws std::out_of_range if out of bounds
    T& at(ptrdiff_t index);
    const T& at(ptrdiff_t index) const;

    /// \brief Gets the size of the section of already added elements.
    /// \return The no of elements.
    inline size_t size() const;

    /// \brief Gets an element from the temporal buffer used for adding elements
    /// \param index The index of the element in the add buffer, it must be negative and indexing starts at -1
    /// \return Reference to the element
    /// \note All references will be invalidated after a call to addAll();
    /// \note Bounds are checked.
    /// \throws std::out_of_range if out of bounds
    T& atAddBuffer(ptrdiff_t index);

    size_t sizeAddBuffer() const;
    size_t sizeRemoveBuffer() const;

};

template <typename T>
SpecializedVector<T>::SpecializedVector(InitFunction_t<T> init, SwapFunction_t<T> swap, DestructFunction_t<T> destruct, size_t reserve)
        : m_init{init}, m_swap{swap}, m_destruct{destruct}
{
    m_data.reserve(reserve);
    m_addBuffer.reserve(reserve/2);
    m_removeBuffer.reserve(reserve/2);
}

template <typename T>
void SpecializedVector<T>::finishChanges()
{

    size_t i;
    //we fill the spaces marked for deletion with elements that are marked for insertion
    for ( i = 0; i < m_addBuffer.size() and i < m_removeBuffer.size(); ++i)
    {
        int index = m_removeBuffer[i];
        m_destruct(m_data[index], index);
        m_data[index] = m_addBuffer[i];
        m_init(m_data[index], index);
    }

    //TODO: Check if the result is correct (off by one errors)
    int noNewElements = m_addBuffer.size() - i;
    m_data.reserve(m_data.size() + noNewElements);

    //if we have more elements that need to be added than removed, add them to the back of the data vector
    for (; i < m_addBuffer.size(); ++i)
    {
           m_data.push_back(m_addBuffer[i]);
           m_init(m_data.back(), m_data.size() - 1);
    }

    //else, if we need to remove more elements than we have to add, move the remaining elements that must be deleted
    // to the back of the vector and pop them out
    for (; i < m_removeBuffer.size(); ++i)
    {
        int index = m_removeBuffer[i];
        m_swap(m_data[index], index, m_data.back(), m_data.size() - 1);
        m_destruct(m_data.back(), m_data.size() - 1);

        m_data.pop_back();
    }

    //TODO: we could shrink the buffers as we take elements from them in the previous steps, although it would be a bit
    // more tedious to write the conditional branches
    m_addBuffer.clear();
    m_removeBuffer.clear();
}


template <typename T>
const T &SpecializedVector<T>::at(ptrdiff_t index) const
{
    //positive index starting from 0 with correct bound
    if (0 <= index and (size_t)index < m_data.size())
        return m_data[index];
        //negative index starting from 1 with correct bound
    else if (-1 * (ptrdiff_t)m_addBuffer.size() <= index and index < 0)
        return  m_addBuffer[-1 * index - 1];
        // we got an invalid index
    else
        throw std::out_of_range("Invalid index, check bounds!");

}

template <typename T>
T &SpecializedVector<T>::at(ptrdiff_t index)
{
    //positive index starting from 0 with correct bound
    if (0 <= index and (size_t)index < m_data.size())
        return m_data[index];
        //negative index starting from 1 with correct bound
    else if (-1 * (ptrdiff_t)m_addBuffer.size() <= index and index < 0)
        return  m_addBuffer[-1 * index - 1];
        // we got an invalid index
    else
        throw std::out_of_range("Invalid index, check bounds!");
}

template <typename T>
const T &SpecializedVector<T>::operator[](size_t index) const
{
    return m_data[index];
}

template <typename T>
T & SpecializedVector<T>::operator[](size_t index)
{
    return m_data[index];
}


template <typename T>
T &SpecializedVector<T>::atAddBuffer(ptrdiff_t index)
{
    //index is negative, so we need to convert it back to a positive having the origin in 0 instead of 1
    ptrdiff_t positiveIndex = -1 * index - 1;
    if (0 <= positiveIndex and (size_t)positiveIndex < m_addBuffer.size())
        return m_addBuffer[positiveIndex];
    else
        throw std::out_of_range("Invalid index, check bounds!");
}

template <typename T>
size_t SpecializedVector<T>::sizeAddBuffer() const
{
    return m_addBuffer.size();
}
template <typename T>
size_t SpecializedVector<T>::sizeRemoveBuffer() const
{
    return m_removeBuffer.size();
}


template <typename T>
ptrdiff_t SpecializedVector<T>::toBeAdded(T &element)
{
    m_addBuffer.push_back(element);

    ptrdiff_t index = -1 * m_addBuffer.size();
    m_init(m_addBuffer.back(), index);
    return index;
}

template <typename T>
ptrdiff_t SpecializedVector<T>::toBeAdded(T &&element)
{
    return toBeAdded(element);
}

template <typename T>
T &SpecializedVector<T>::toBeRemoved(std::size_t index)
{
    if (index >= m_data.size())
        throw std::out_of_range("Invalid index, check bounds!");

    m_removeBuffer.push_back(index);
    return m_data[index];
}

template <typename T>
size_t SpecializedVector<T>::size() const
{
    return m_data.size();
}


