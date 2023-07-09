#pragma once
#include <vector>
#include "GenericObject.h"




class ChunkContainer
{
private:
    //elements will
    std::vector<GenericObject*> m_data = {};
    std::size_t m_eraseStart = 0;
    std::vector<GenericObject*> m_addBuffer = {};

    [[nodiscard]] inline size_t m_actualDataSize() const;
    [[nodiscard]] inline size_t m_eraseSize() const;
    void m_swapAndUpdate(size_t index1, size_t index2);
    [[nodiscard]] inline bool m_emptyErase() const;

public:
    explicit ChunkContainer(size_t reserve = 16);

    GenericObject toBeRemoved(std::size_t index);
    void removeAll();

    void toBeAdded(GenericObject & element);
    void addAll();

    GenericObject& operator[](size_t index);

    inline size_t size() const;

};

