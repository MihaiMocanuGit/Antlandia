#pragma once
#include <vector>
#include <stdexcept>


/// A specialized vector has the scope of maintaining the validity of indexes while having the
/// benefit of cache-locality and fast removals/additions. The fundamental way it works is the following:
///
/// 1) We use a buffer for add and delete, meaning that you must first mark all elements to be deleted/added and
/// after that send a final command to permanently add/remove the chosen objects.
///
/// 2) It uses the delete by-swap idiom. Meaning that when marking an element for deletion, we first swap it with
/// the last element which is not also marked for deletion. It updates the memorised indexes through a given custom function.
///
/// 3) As such, the buffer used for removal is actually at the end of the original vector. The buffer for
/// additions is a separate vector
/// \note It is built upon std::vector.
//TODO: check swap behavior between data sectors
/// \note The logic should allow swapping elements from the add buffer with the ones in the old data section. I don't
/// recommend doing it yet, as I'm not sure if it works correctly.
/// \brief Optimized vector for frequent additions and random removals. It maintains index validity.
/// \tparam T copy-constructable and copy-assignable element
template <typename T>
class SpecializedVector
{
private:
    std::vector<T> m_data = {};

    /// \brief also represents the size of the section of already added elements
    std::size_t m_eraseStart = 0;

    /// \brief additional vector where we temporally store the elements that will later be added
    std::vector<T> m_addBuffer = {};

    InitFunction_t<T> m_init;
    SwapFunction_t<T> m_swap;


    /// \brief The size of the section of already added elements, ignoring the 2 buffers
    /// \return The number of elements
    [[nodiscard]] inline size_t m_oldDataSize() const;

    /// \brief The size of the section of elements marked for deletion
    /// \return The number of elements
    [[nodiscard]] inline size_t m_eraseSize() const;

    /// \brief Checks if we do not have any elements that need to be deleted
    /// \return bool
    [[nodiscard]] inline bool m_emptyErase() const;

public:


    SpecializedVector(InitFunction_t<T> init, SwapFunction_t<T> swap, size_t reserve = 128);

    /// \brief Marks for deletion elements that were already added
    /// \param index The index is relative only to the section of already added elements. You
    /// cannot remove an element that was marked for insertion/removal
    /// \note Bounds are checked.
    /// \note By marking an element to be deleted, the indexes of elements from the add buffer that were
    /// relative to the start of already added elements will be invalidated
    /// \return A copy to the element that was marked for removal
    T toBeRemoved(std::size_t index);
    void removeAll();

    void toBeAdded(T &&element);
    void toBeAdded(T &element);
    void addAll();

    /// \brief Gets an element only from the section of already added elements.
    /// \param index
    /// \return Reference to the element at the given index
    /// \note Bounds are not checked. As such you might unintentionally access the removal buffer
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    /// \brief Gets an element from the vector. If the given index is greater than the size of
    /// the section of already added elements, then it will access the elements that were marked for
    /// insertion.
    /// \param index The index of the element you want to access
    /// \return Reference to the given object
    /// \note Bounds are checked, you cannot access the removal buffer by mistake.
    /// \throws std::out_of_range if out of bounds
    /// \note The index is given relative to the first element from the section of already added elements in the array
    /// the i'th element that was marked for insertion will be found at the index: size() + i
    T& at(size_t index);
    const T& at(size_t index) const;

    /// \brief Gets the size of the section of already added elements.
    /// \return The no of elements.
    inline size_t size() const;

    /// \brief Gets an element from the temporal buffer used for adding elements
    /// \param index The index of the element in the add buffer.
    /// \return Reference to the element
    /// \note All references will be invalidated after a call to addAll();
    /// \note Bounds are checked.
    /// \throws std::out_of_range if out of bounds
    /// \note The index is given relative to the start of the add buffer
    T& atAddBuffer(size_t index);
    inline size_t sizeAddBuffer() const;

};


template <typename T>
const T &SpecializedVector<T>::at(size_t index) const
{
    if (index < m_oldDataSize())
        return m_data[index];
    //  implies we access the temporal buffer for additions
    else if (index > m_oldDataSize() and index < m_oldDataSize() + m_addBuffer.size())
        return  m_addBuffer[index - m_oldDataSize()];
    // we got an invalid index
    else
        throw std::out_of_range("Invalid index, check bounds!");

}

template <typename T>
T &SpecializedVector<T>::at(size_t index)
{
    if (index < m_oldDataSize())
        return m_data[index];
        //  implies we access the temporal buffer for additions
    else if (index > m_oldDataSize() and index < m_oldDataSize() + m_addBuffer.size())
        return  m_addBuffer[index - m_oldDataSize()];
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
T &SpecializedVector<T>::atAddBuffer(size_t index)
{
    if (index < m_addBuffer.size())
        return m_addBuffer[index];
    else
        throw std::out_of_range("Invalid index, check bounds!");
}

template <typename T>
size_t SpecializedVector<T>::sizeAddBuffer() const
{
    return m_addBuffer.size();
}


template <typename T>
T SpecializedVector<T>::toBeRemoved(std::size_t index)
{
    if (index >= m_oldDataSize())
        throw std::out_of_range("Invalid index, check bounds!");

    m_eraseStart--;

    m_swap(m_data[index], index, m_eraseStart, m_data[m_eraseStart]);

    return *m_data[m_eraseStart];
}


template <typename T>
SpecializedVector<T>::SpecializedVector(InitFunction_t<T> init, SwapFunction_t<T> swap, size_t reserve)
    : m_init{init}, m_swap{swap}
{
    m_data.reserve(reserve);
    m_addBuffer.reserve(reserve);
}


template <typename T>
size_t SpecializedVector<T>::m_oldDataSize() const
{
    return m_eraseStart;
}





template <typename T>
bool SpecializedVector<T>::m_emptyErase() const
{
    return m_eraseStart == m_data.size();
}


template <typename T>
void SpecializedVector<T>::toBeAdded(T &element)
{
    m_addBuffer.push_back(element);
}

template <typename T>
void SpecializedVector<T>::toBeAdded(T &&element)
{
    toBeAdded(element);
}

template <typename T>
void SpecializedVector<T>::removeAll()
{
    for (size_t i = 0; i < m_eraseSize(); ++i)
        m_data.pop_back();
}


template <typename T>
size_t SpecializedVector<T>::m_eraseSize() const
{
    return m_data.size() - m_eraseStart;
}


template <typename T>
void SpecializedVector<T>::addAll()
{

    size_t noNewElements = m_addBuffer.size();
    for (size_t i = 0; i < noNewElements; ++i)
    {
        //pull out the last element and add it to the back of the data vector
        m_data.push_back(m_addBuffer.back());
        m_addBuffer.pop_back();

        //init the world knowledge with the vector indices
        m_init(m_data.back(), m_data.size() - 1);

        //move the newly added element from the back of the whole vector to the back
        //of the active elements region
        //the first element that is supposed to be deleted will be moved to the back o
        //of the whole vector
        size_t last = m_data.size() - 1;
        m_swap(m_data[m_eraseStart], m_eraseStart, m_data[last], last);

        //translate the region of erased element one unit to the right to make the start
        //region valid again
        m_eraseStart++;
    }

}

template <typename T>
size_t SpecializedVector<T>::size() const
{
    return m_oldDataSize();
}


