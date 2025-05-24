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
		int getRandomData() const;
		int getRandomKey();
		int keyToInsert;
	private:

		std::default_random_engine rngData_;
		std::default_random_engine rngIndex_;
		size_t key;
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
	class TableFindAnalyzer : public TableAnalyzer<Table>
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
	TableAnalyzer<Table>::TableAnalyzer(const std::string& name) :
		ComplexityAnalyzer<Table>(name),
		rngData_(144),
		rngIndex_(144),
		key(0),
		data_(0)
	{
		ComplexityAnalyzer<Table>::registerBeforeOperation([this](Table& table)
			{
				std::uniform_int_distribution<size_t> indexDist(0, table.size() - 1);
				key = indexDist(rngIndex_);
				data_ = rngData_();
			});
	}

	template<class Table>
	inline void TableAnalyzer<Table>::growToSize(Table& structure, size_t size)
	{

		std::uniform_int_distribution<size_t> indexDist(structure.size(), size);
		this->keyToInsert = indexDist(rngIndex_);
		const size_t toInsert = structure.size();
		for (size_t i = toInsert; i < size; ++i)
		{
			//if (keyToInsert == i)
			//{
			//	continue;
			//}

			structure.insert(i, i);
		}
	}

	template<class Table>
	inline int TableAnalyzer<Table>::getRandomData() const
	{
		return this->data_;
	}

	template<class Table>
	inline int TableAnalyzer<Table>::getRandomKey()
	{
		return this->key;
	}



	template<class Table>
	inline TableInsertAnalyzer<Table>::TableInsertAnalyzer(const std::string& name) :TableAnalyzer<Table>(name)
	{


	}

	template<class Table>
	inline void TableInsertAnalyzer<Table>::executeOperation(Table& structure)
	{
		int data = this->getRandomData();
		structure.insert(this->keyToInsert, data);


	}

	template<class Table>
	inline TableFindAnalyzer<Table>::TableFindAnalyzer(const std::string& name) :TableAnalyzer<Table>(name)
	{
	}

	template<class Table>
	inline void TableFindAnalyzer<Table>::executeOperation(Table& structure)
	{
		int key = this->getRandomKey();
		structure.find(key);
	}
	inline TablesAnalyzer::TablesAnalyzer() : CompositeAnalyzer("Tables") {
		this->addAnalyzer(std::make_unique<TableInsertAnalyzer<ds::adt::Treap<int, int>>>("table-insert"));
		this->addAnalyzer(std::make_unique<TableFindAnalyzer<ds::adt::Treap<int, int>>>("table-find"));

	}

}
