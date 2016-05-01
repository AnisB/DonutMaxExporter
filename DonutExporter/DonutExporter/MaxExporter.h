#ifndef DONUT_MAX_EXPORTER_H
#define DONUT_MAX_EXPORTER_H

// Library includes
#include "base/Common.h"

// SDK includes
#include <string.h>
#include "maxscript\macros\define_instantiation_functions.h"

namespace Donut
{
	class TMaxExporter
	{
	public:
		TMaxExporter();
		~TMaxExporter();

		// This should be called first
		void Init(const MSTR& _outputFolder, const MSTR& _projectName, const MSTR& _levelName);

		// Exports the flour, the scene node and everything
		void ExportScene(Array* _geometryNodes);

	private:
		void CreateFolderHierachy();
	protected:

		// Input data
		STRING_TYPE m_outputDir;
		STRING_TYPE m_projectName;
		STRING_TYPE m_levelName;

		// Cached data
		STRING_TYPE m_projectRoot;
		STRING_TYPE m_assetsRoot;
		STRING_TYPE m_floursFolder;
		STRING_TYPE m_sugarFolder;
		STRING_TYPE m_geometryFolder;
		STRING_TYPE m_texturesFolder;
		STRING_TYPE m_skyboxFolder;
	};
}

#endif // DONUT_MAX_EXPORTER_H