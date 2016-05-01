#ifndef MAX_FLOUR_EXPORTER_H
#define MAX_FLOUR_EXPORTER_H

// Library includes
#include "sugarexporter.h"

// SDK includes
#include <maxscript\maxscript.h>

// External includes
#include <vector>

namespace Donut
{
	class TFlourExporter
	{
	public:
		TFlourExporter();
		~TFlourExporter();

		void BuildFlourInterface(const STRING_TYPE& _flourDirectory, const STRING_TYPE& _levelName, Array* _nodes, const std::vector<TSugarExporter>& _sugars);
		void Export();

	public:
		STRING_TYPE m_levelName;
		STRING_TYPE m_outputFile;
		Array* m_nodes;
		const std::vector<TSugarExporter>* m_sugars;
	};
}

#endif //MAX_FLOUR_EXPORTER_H