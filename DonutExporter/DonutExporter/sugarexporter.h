#ifndef MAX_SUGAR_EXPORTER_H
#define MAX_SUGAR_EXPORTER_H

// Library includes
#include "base/common.h"

// SDK includes
#include <maxscript\maxscript.h>

namespace Donut
{

	// Foward declare
	class TEggExporter;

	// Sugar container
	class TSugarExporter
	{
	public:
		TSugarExporter();
		~TSugarExporter();

		// Build the sugar interface
		void BuildSugarInterface(INode* _maxNode, const STRING_TYPE& _sugarsDirectory, const TEggExporter& _eggExporter);

		// Export 
		void Export();

	public:
		INode* m_maxNode;
		STRING_TYPE m_sugarsDirectory;
		STRING_TYPE m_hashID;
		STRING_TYPE m_nodeName;
		STRING_TYPE m_outputFile;
		const TEggExporter* m_eggExporter;
	};
}

#endif // MAX MAX_SUGAR_EXPORTER_H