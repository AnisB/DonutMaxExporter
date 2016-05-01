// Library includes
#include "flourexporter.h"
#include "base/Common.h"

// External includes
#include <fstream>
#include "3rd\rapidxml\rapidxml.hpp"
#include "3rd\rapidxml\rapidxml_print.hpp"

namespace Donut
{
	TFlourExporter::TFlourExporter()
	{

	}

	TFlourExporter::~TFlourExporter()
	{

	}

	void TFlourExporter::BuildFlourInterface(const STRING_TYPE& _flourDirectory, const STRING_TYPE& _levelName, Array* _nodes, const std::vector<TSugarExporter>& _sugars)
	{
		m_levelName = _levelName;
		m_nodes = _nodes;
		m_sugars = &_sugars;
		m_outputFile = _flourDirectory + "/" + m_levelName + ".flour";
	}

	void convertTMToString(Matrix3& _tm, STRING_TYPE& _out)
	{
		_out = "";
		_out += convertToString<float>(_tm.GetRow(0).x);
		_out += " ";
		_out += convertToString<float>(_tm.GetRow(1).x);
		_out += " ";
		_out += convertToString<float>(_tm.GetRow(2).x);
		_out += " ";
		_out += convertToString<float>(_tm.GetRow(3).x);
		_out += " ";

		_out += convertToString<float>(_tm.GetRow(0).y);
		_out += " ";
		_out += convertToString<float>(_tm.GetRow(1).y);
		_out += " ";
		_out += convertToString<float>(_tm.GetRow(2).y);
		_out += " ";
		_out += convertToString<float>(_tm.GetRow(3).y);
		_out += " ";

		_out += convertToString<float>(_tm.GetRow(0).z);
		_out += " ";
		_out += convertToString<float>(_tm.GetRow(1).z);
		_out += " ";
		_out += convertToString<float>(_tm.GetRow(2).z);
		_out += " ";
		_out += convertToString<float>(_tm.GetRow(3).z);
		_out += " ";

		_out += convertToString<float>(0.0);
		_out += " ";
		_out += convertToString<float>(0.0);
		_out += " ";
		_out += convertToString<float>(0.0);
		_out += " ";
		_out += convertToString<float>(1.0);
		_out += " ";
	}
	void TFlourExporter::Export()
	{
		// Creating the file writer
		std::ofstream outputFile;
		outputFile.open(m_outputFile);
		// Making sure everything is ok
		ASSERT(outputFile.is_open());

		// Creating the document
		rapidxml::xml_document<> outputDoc;


		// Creating the floor node
		rapidxml::xml_node<>* floorNode = outputDoc.allocate_node(rapidxml::node_element, "flour");
		outputDoc.append_node(floorNode);

		// Adding the name
		rapidxml::xml_attribute<>* floorName = outputDoc.allocate_attribute("name", m_levelName.c_str());
		floorNode->append_attribute(floorName);


		// Creating the root node
		rapidxml::xml_node<>* rootNode = outputDoc.allocate_node(rapidxml::node_element, "root");
		floorNode->append_node(rootNode);
		
		int nbNodes = m_nodes->size;

		std::vector<STRING_TYPE> tms;
		tms.resize(nbNodes);

		for (int nodeIndex = 0; nodeIndex < nbNodes; ++nodeIndex)
		{
			INode* currentINode = m_nodes->get(nodeIndex + 1)->to_node();
			Matrix3& mTM = currentINode->GetObjectTM(0);
			STRING_TYPE& litteralTM = tms[nodeIndex];
			convertTMToString(mTM, litteralTM);

			rapidxml::xml_node<>* scenenode = outputDoc.allocate_node(rapidxml::node_element, "scenenode");
			rootNode->append_node(scenenode);
			rapidxml::xml_attribute<>* TM = outputDoc.allocate_attribute("TM", litteralTM.c_str());
			scenenode->append_attribute(TM);

			rapidxml::xml_node<>* model = outputDoc.allocate_node(rapidxml::node_element, "model");
			scenenode->append_node(model);
			rapidxml::xml_attribute<>* sugar = outputDoc.allocate_attribute("sugar", (*m_sugars)[nodeIndex].m_hashID.c_str());
			model->append_attribute(sugar);
		}

		// Creating the pipeline node
		rapidxml::xml_node<>* pipeline = outputDoc.allocate_node(rapidxml::node_element, "pipeline");
		rapidxml::xml_attribute<>* pipelinename = outputDoc.allocate_attribute("name", "normal");
		pipeline->append_attribute(pipelinename);
		floorNode->append_node(pipeline);

		// Printing the file name and closing the file
		outputFile << outputDoc;
		outputFile.close();
	}
}