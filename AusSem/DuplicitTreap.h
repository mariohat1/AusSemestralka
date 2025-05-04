#pragma once
#include "libds/adt/table.h"
#include "commune.h"
#include "libds/amt/implicit_sequence.h"


struct CommuneData {
    using Sequence = ds::amt::ImplicitSequence<commune*>;
    commune* single = nullptr;
    Sequence* duplicit = nullptr;

    void addDuplicit(commune* comm) {
        if (duplicit == nullptr) {
            duplicit = new Sequence();
            duplicit->insertLast().data_ = comm;
        }
        duplicit->insertLast().data_ = single;
    }
    bool operator==(const CommuneData& other) const {
        return this->single == other.single && this->duplicit == other.duplicit;
        
    }
      

    ~CommuneData() {
        if (this->duplicit != nullptr)
        {
            delete this->duplicit;
            
        }
        
    }
};

