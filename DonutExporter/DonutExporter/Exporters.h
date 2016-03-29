#ifndef EXPORTERS_DONUT_H
#define EXPORTERS_DONUT_H

// Library includes
#include "base/common.h"

// SDK includes
#include <maxscript\maxscript.h>

namespace Donut
{
	// Sugar container
	class TSugar
	{
	public:
		TSugar()
		: maxNode(nullptr)
		{

		}

		void BuildSugarInterface(INode* _maxNode);

	private:
		INode* maxNode;
		STRING_TYPE nodeName;
	};

	// Geometry class
	class TGeometry
	{
	public:
		TGeometry()
		: maxMesh(nullptr)
		{

		}

		void BuildGeometryInterface(Mesh* _maxMesh);

	private:
		Mesh* maxMesh;
	};

	// Export the inodes
	void ExportINodes(Array* _inodeArray);
}

#endif // EXPORTERS_DONUT_H