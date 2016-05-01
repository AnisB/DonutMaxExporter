// Library includes
#include "eggExporter.h"
#include "Helpers.h"

// External include
#include <fstream>

namespace Donut
{
	TEggExporter::TEggExporter()
	: m_maxMesh(nullptr)
	, m_vertNormalUV(nullptr)
	, m_faces(nullptr)
	{

	}

	TEggExporter::~TEggExporter()
	{
		if (m_vertNormalUV)
		{
			delete[] m_vertNormalUV;
		}

		if (m_faces)
		{
			delete[] m_faces;
		}
	}

	void TEggExporter::BuildEggInterface(INode* _maxNode, STRING_TYPE& _eggsDirectory)
	{
		//Keep geometry and fetch the mesh
		m_maxINode = _maxNode;
		m_maxMesh = GetMeshFromNode(_maxNode);

		// Fetch the node's name
		STRING_TYPE node_name = convertToString(MSTR(m_maxINode->GetName()));
		m_hashID = convertToString(std::hash<std::string>()(node_name));

		// Set the output directory
		m_outputFile = _eggsDirectory + "/" + m_hashID + ".egg";

		// Making sure the normals are computed
		m_maxMesh->checkNormals(true);
		// Geometry data
		m_nbVerts = m_maxMesh->numVerts;
		m_nbFaces = m_maxMesh->numFaces;
		m_practicalnbVerts = m_nbFaces * 3;

		// Allocating the memory space
		m_vertNormalUV = new float[m_practicalnbVerts * 8];
		m_faces = new unsigned int[m_nbFaces * 3];

		// Filling the faces indexes
		for (int faceIndex = 0; faceIndex < m_nbFaces; ++faceIndex)
		{
			m_faces[3 * faceIndex] = 3 * faceIndex;
			m_faces[3 * faceIndex + 1] = 3 * faceIndex + 1;
			m_faces[3 * faceIndex + 2] = 3 * faceIndex +2;
		}

		// Computing the shifted ptrs
		float* vertexPTR = m_vertNormalUV;
		float* normalPTR = m_vertNormalUV + 3 * m_practicalnbVerts;
		float* uvPTR = normalPTR + 3 * m_practicalnbVerts;

		// Filling the vertex data
		for (size_t faceIndex = 0; faceIndex < m_nbFaces; ++faceIndex)
		{
			Face& currentFace = m_maxMesh->faces[faceIndex];
			for (int vert = 0; vert < 3; ++vert)
			{
				vertexPTR[9 * faceIndex + vert * 3] = m_maxMesh->verts[currentFace.v[vert]].x;
				vertexPTR[9 * faceIndex + vert * 3 + 1] = m_maxMesh->verts[currentFace.v[vert]].y;
				vertexPTR[9 * faceIndex + vert * 3 + 2] = m_maxMesh->verts[currentFace.v[vert]].z;
			}
		}

		// Filling the normals
		for (int faceIndex = 0; faceIndex < m_nbFaces; ++faceIndex)
		{
			Point3 faceNormal = m_maxMesh->getFaceNormal(faceIndex);
			for (int vert = 0; vert < 3; ++vert)
			{
				normalPTR[9 * faceIndex + vert * 3] = faceNormal.x;
				normalPTR[9 * faceIndex + vert * 3 + 1] = faceNormal.y;
				normalPTR[9 * faceIndex + vert * 3 + 2] = faceNormal.z;
			}
		}

		// Filling the uv vert
		for (int faceIndex = 0; faceIndex < m_nbFaces; ++faceIndex)
		{
			const TVFace& tvface = m_maxMesh->tvFace[faceIndex];
			for (int vert = 0; vert < 2; ++vert)
			{
				uvPTR[6 * faceIndex + vert * 2] = m_maxMesh->tVerts[tvface.t[vert]].x / 1000.0f;
				uvPTR[6 * faceIndex + vert * 2 + 1] = m_maxMesh->tVerts[tvface.t[vert]].y / 1000.0f;
			}
		}
	}

	void TEggExporter::Export()
	{
		// Creating the file writer
		std::ofstream outputFile;
		outputFile.open(m_outputFile, std::ios::binary);
		// Making sure everything is ok
		ASSERT_MSG(outputFile.is_open(), "Couldn't open egg file "<< m_outputFile);

		// Writing the num of vertices
		outputFile.write((const char*)&m_practicalnbVerts, sizeof(int));
		outputFile.write((const char*)m_vertNormalUV, sizeof(float) * 8 * m_practicalnbVerts);
		outputFile.write((const char*)&m_nbFaces, sizeof(int));
		outputFile.write((const char*)m_faces, sizeof(unsigned int) * 3 * m_nbFaces);

		outputFile.close();
	}
}