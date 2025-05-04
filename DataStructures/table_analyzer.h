#pragma once
#include <complexities/complexity_analyzer.h>
#include "libds/adt/table.h"
#include <vector>
#include <random>
namespace ds::utils
{

    template<class Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table>
    {
    protected:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void growToSize(Table& structure, size_t size) override;

    
    private:
        std::default_random_engine rngData_;
        std::default_random_engine rngIndex_;
        size_t index_;
        int data_;
    };

    /**
     * @brief Analyzes complexity of an insertion at the beginning.
     */
    template<class Table>
    class TableInsertAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableInsertAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };

    /**
     * @brief Analyzes complexity of an erasure at the beginning.
     */
    template<class Table>
    class TableFindAnalyzer: public TableAnalyzer<Table>
    {
    public:
        explicit TableFindAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };
    class TablesAnalyzer : public CompositeAnalyzer
    {
    public:
        TablesAnalyzer();
    };


    template<class Table>
    inline TableAnalyzer<Table>::TableAnalyzer(const std::string& name) : ComplexityAnalyzer<Table>(name)
    {
    }

    template<class Table>
    inline void TableAnalyzer<Table>::growToSize(Table& structure, size_t size)
    {
        const size_t toInsert = size - structure.size();
        for (size_t i = 0; i < toInsert; ++i)
        {
            structure.push_back(rngData_());
        }

    }

    template<class Table>
    inline TableInsertAnalyzer<Table>::TableInsertAnalyzer(const std::string& name) :TableAnalyzer(name)
    {

    }

    template<class Table>
    inline void TableInsertAnalyzer<Table>::executeOperation(Table& structure)
    {
    }

    template<class Table>
    inline TableFindAnalyzer<Table>::TableFindAnalyzer(const std::string& name)
    {
    }

    template<class Table>
    inline void TableFindAnalyzer<Table>::executeOperation(Table& structure)
    {
    }
    inline TablesAnalyzer::TablesAnalyzer() : CompositeAnalyzer("Tables") {
        this->addAnalyzer(std::make_unique<TableInsertAnalyzer<ds::adt::Table<int, int>>>("table-insert"));
        this->addAnalyzer(std::make_unique<TableFindAnalyzer<ds::adt::Table<int, int>>>("table-find"));
    
    }

}
