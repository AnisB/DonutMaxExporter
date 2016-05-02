// Library includes
#include "sugarexporter.h"
#include "eggExporter.h"
#include "flourexporter.h"
#include "MaxExporter.h"
#include "base/common.h"
#include "Helpers.h"

// External includes
#include <vector>

namespace Donut
{
	TMaxExporter::TMaxExporter()
	{

	}

	TMaxExporter::~TMaxExporter()
	{

	}

	// This should be called first
	void TMaxExporter::Init(const MSTR& _outputFolder, const MSTR& _projectName, const MSTR& _levelName)
	{
		// Copying the output data
		m_outputDir = _outputFolder.ToCStr().data();
		m_projectName = _projectName.ToCStr().data();
		m_levelName = _levelName.ToCStr().data();

		// In this output data create the right file hierachy
		CreateFolderHierachy();
	}

	// Exports the flour, the scene node and everything
	void TMaxExporter::ExportScene(Array* _geometryNodes)
	{
		ASSERT_POINTER_NOT_NULL_NO_RELEASE(_geometryNodes);
		// Fetch the number of nodes
		int nbNodes = _geometryNodes->size;

		std::vector<TEggExporter> eggs;
		eggs.resize(nbNodes);
		std::vector<TSugarExporter> sugars;
		sugars.resize(nbNodes);

		// For each inode
		for (int nodeIndex = 0; nodeIndex < nbNodes; ++nodeIndex)
		{
			// Fetch the current node
			INode* currentINode = _geometryNodes->get(nodeIndex + 1)->to_node();

			GENERAL_INFO("Building egg interface");
			// Create the egg exporter
			TEggExporter& eggexporter = eggs[nodeIndex];
			// Build its interface
			eggexporter.BuildEggInterface(currentINode, m_geometryFolder);

			GENERAL_INFO("Building sugar interface");
			// Create the sugar exporter
			TSugarExporter& sugarExporter = sugars[nodeIndex];

			// Build its interface
			sugarExporter.BuildSugarInterface(currentINode, m_sugarFolder, eggexporter);

			// Apply some modifications on the mesh before the runtime
			eggexporter.PrepareForRunTime();

			// Exporting the sugar
			GENERAL_INFO("Exporting " << sugarExporter.m_nodeName);
			eggexporter.Export();
			sugarExporter.Export();
		}

		// Definif the flour export interface
		TFlourExporter flourExport;
		flourExport.BuildFlourInterface(m_floursFolder, m_levelName, _geometryNodes, sugars);
		// Exporting the level
		flourExport.Export();
	}

	void TMaxExporter::CreateFolderHierachy()
	{
		// Creating the root folder
		m_projectRoot = m_outputDir + "/" + m_projectName;
		CreateDirectory_DNT(m_projectRoot);

		// Creating the asset root directory
		m_assetsRoot = m_projectRoot + "/" + "common";
		CreateDirectory_DNT(m_assetsRoot);

		// Creating the skybox output folder
		m_floursFolder = m_assetsRoot + "/" + "flours";
		CreateDirectory_DNT(m_floursFolder);

		// Creating the sugar output folder
		m_sugarFolder = m_assetsRoot + "/" + "sugars";
		CreateDirectory_DNT(m_sugarFolder);

		// Creating the geometry output folder
		m_geometryFolder = m_assetsRoot + "/" + "geometry";
		CreateDirectory_DNT(m_geometryFolder);

		// Creating the textures output folder
		m_texturesFolder = m_assetsRoot + "/" + "textures";
		CreateDirectory_DNT(m_texturesFolder);

		// Creating the skybox output folder
		m_skyboxFolder = m_assetsRoot + "/" + "skybox";
		CreateDirectory_DNT(m_skyboxFolder);
	}
}