#pragma once
#include "libds/adt/table.h"
#include "TerritorialUnit.h"

#include "libds/amt/implicit_sequence.h"

template<typename T>
struct TableData {

    using Sequence = ds::amt::ImplicitSequence<T>;
    T single;
    Sequence* duplicit = nullptr;

    void addDuplicit(T comm) {
        if (duplicit == nullptr) {
            duplicit = new Sequence();
            duplicit->insertLast().data_ = comm;
        }
        duplicit->insertLast().data_ = single;
    }
    bool operator==(const TableData& other) const {
        return this->single == other.single && this->duplicit == other.duplicit;
        
    }
    bool operator!=(const TableData& other) const {
        return this->single != other.single && this->duplicit != other.duplicit;
    }
      

    ~TableData() {
        if (this->duplicit != nullptr)
        {
            delete this->duplicit;
            
        }
        
    }
};

