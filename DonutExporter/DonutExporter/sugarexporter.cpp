// Library includesd
#include "sugarexporter.h"
#include "eggExporter.h"

// External includes
#include <fstream>
#include "3rd\rapidxml\rapidxml.hpp"
#include "3rd\rapidxml\rapidxml_print.hpp"

namespace Donut
{
	TSugarExporter::TSugarExporter()
	: m_maxNode(nullptr)
	{

	}

	TSugarExporter::~TSugarExporter()
	{

	}

	void TSugarExporter::BuildSugarInterface(INode* _maxNode, const STRING_TYPE& _sugarsDirectory, const TEggExporter& _eggExporter)
	{
		// Keeping track of the max node
		m_maxNode = _maxNode;

		// Sugar location
		m_sugarsDirectory = _sugarsDirectory;

		// The associated sugar exporter
		m_eggExporter = &_eggExporter;

		// Fetch the node's name
		m_nodeName = convertToString(MSTR(m_maxNode->GetName()));
		m_hashID = convertToString(std::hash<std::string>()(m_nodeName));

		// Output file name
		m_outputFile = m_sugarsDirectory + "/" + m_hashID + ".sugar";
	}

	void TSugarExporter::Export()
	{
		// Creating the file writer
		std::ofstream outputFile;
		outputFile.open(m_outputFile);
		// Making sure everything is ok
		ASSERT(outputFile.is_open());
		
		// Creating the document
		rapidxml::xml_document<> outputDoc;

		// Creating the root node
		rapidxml::xml_node<>* sugarRootNode = outputDoc.allocate_node(rapidxml::node_element, "sugar");
		outputDoc.append_node(sugarRootNode);

		// Adding the name
		rapidxml::xml_attribute<>* sugarName = outputDoc.allocate_attribute("name", m_hashID.c_str());
		sugarRootNode->append_attribute(sugarName);

		// Adding the geometry
		rapidxml::xml_node<>* geometry = outputDoc.allocate_node(rapidxml::node_element, "geometry");
		sugarRootNode->append_node(geometry);
		rapidxml::xml_attribute<>* typeAttribute = outputDoc.allocate_attribute("type", "egg");
		const STRING_TYPE& fullLocalPath = ("common/geometry/" + m_eggExporter->m_hashID +".egg");
		rapidxml::xml_attribute<>* locationAttribute = outputDoc.allocate_attribute("location", fullLocalPath.c_str());
		geometry->append_attribute(typeAttribute);
		geometry->append_attribute(locationAttribute);

		// Adding the builtin
		rapidxml::xml_node<>* built_in_data = outputDoc.allocate_node(rapidxml::node_element, "built_in_data");
		sugarRootNode->append_node(built_in_data);

		// Adding the external data
		rapidxml::xml_node<>* extern_data = outputDoc.allocate_node(rapidxml::node_element, "extern_data");
		sugarRootNode->append_node(extern_data);

		// Adding the shaders
		rapidxml::xml_node<>* shaders = outputDoc.allocate_node(rapidxml::node_element, "shader");
		sugarRootNode->append_node(shaders);

		rapidxml::xml_node<>* vertexShader = outputDoc.allocate_node(rapidxml::node_element, "vertex");
		rapidxml::xml_attribute<>* vertexlocation = outputDoc.allocate_attribute("location", "common/shaders/base/vertex.glsl");
		vertexShader->append_attribute(vertexlocation);
		shaders->append_node(vertexShader);

		rapidxml::xml_node<>* geometryShader = outputDoc.allocate_node(rapidxml::node_element, "geometry");
		rapidxml::xml_attribute<>* geometryLocation = outputDoc.allocate_attribute("location", "common/shaders/base/geometry.glsl");
		geometryShader->append_attribute(geometryLocation);
		shaders->append_node(geometryShader);

		rapidxml::xml_node<>* fragmentShader = outputDoc.allocate_node(rapidxml::node_element, "fragment");
		rapidxml::xml_attribute<>* fragmentLocation = outputDoc.allocate_attribute("location", "common/shaders/base/fragment.glsl");
		fragmentShader->append_attribute(fragmentLocation);
		shaders->append_node(fragmentShader);

		// Adding the textures
		rapidxml::xml_node<>* textures = outputDoc.allocate_node(rapidxml::node_element, "textures");
		sugarRootNode->append_node(textures);
		rapidxml::xml_node<>* texture2D = outputDoc.allocate_node(rapidxml::node_element, "texture2D");
		rapidxml::xml_attribute<>* nameLocationTEX = outputDoc.allocate_attribute("name", "textureCmp");
		rapidxml::xml_attribute<>* locationAttributeTEX = outputDoc.allocate_attribute("location", "common/textures/rockwall.bmp");
		texture2D->append_attribute(nameLocationTEX);
		texture2D->append_attribute(locationAttributeTEX);
		textures->append_node(texture2D);

		// Printing the file name and closing the file
		outputFile << outputDoc;
		outputFile.close();
	}
}