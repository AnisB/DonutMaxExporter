// Library includes
#include "Exporters.h"

// External includes
#include <vector>
#include <triobj.h>

namespace Donut
{
	// Helpers
	Mesh* GetMeshFromNode(INode* _currentNode)
	{
		TriObject* triObj = static_cast<TriObject*>(_currentNode->GetObjectRef());
		Mesh& currentMesh = triObj->GetMesh();
		return &currentMesh;
	}

	// Convert to the internal string structure
	STRING_TYPE convertToString(const MSTR& _mstr)
	{
		return STRING_TYPE(_mstr.ToCStr().data());
	}

	void TSugar::BuildSugarInterface(INode* _maxNode)
	{
		// Keeping track of the max node
		maxNode = _maxNode;

		// Fetch the node's name
		nodeName = convertToString(MSTR(maxNode->GetName()));
	}

	void TGeometry::BuildGeometryInterface(Mesh* _maxMesh)
	{
		maxMesh = _maxMesh;
	}

	void ExportINodes(Array* _inodeArray)
	{
		ASSERT_POINTER_NOT_NULL_NO_RELEASE(_inodeArray);

		// Fetch the array size
		int nbNodes = _inodeArray->size;

		// Creating the containers
		std::vector<TGeometry> geometries(nbNodes);
		std::vector<TSugar> sugars(nbNodes);

		// Process each available INode
		for (int nodeIndex = 0; nodeIndex < nbNodes; ++nodeIndex)
		{
			// Fetch the node
			INode* currentNode = _inodeArray->get(nodeIndex + 1)->to_node();

			// Build the sugar interface
			sugars[nodeIndex].BuildSugarInterface(currentNode);
			
			// Build the geometry interface
			geometries[nodeIndex].BuildGeometryInterface(GetMeshFromNode(currentNode));
		}
	}
}