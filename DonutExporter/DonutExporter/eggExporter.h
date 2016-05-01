#ifndef MAX_EGG_EXPORTER_H
#define MAX_EGG_EXPORTER_H

// Library includes
#include "base/common.h"

// SDK includes
#include <maxscript\maxscript.h>

namespace Donut
{
	// Geometry class
	class TEggExporter
	{
	public:
		// Cst and Dst
		TEggExporter();
		~TEggExporter();

		// Build the geometry interface form the Mesh
		void BuildEggInterface(INode* _maxNode, STRING_TYPE& _eggsDirectory);
		void Export();

	public:
		// Max data
		INode* m_maxINode;
		Mesh* m_maxMesh;

		// Export data
		STRING_TYPE m_hashID;
		STRING_TYPE m_outputFile;

		int m_nbVerts;
		int m_nbFaces;
		int m_practicalnbVerts;
		float* m_vertNormalUV;
		unsigned int* m_faces;
	};
}

#endif // MAX_EGG_EXPORTER_H