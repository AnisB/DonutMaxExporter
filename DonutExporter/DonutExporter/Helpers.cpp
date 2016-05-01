// Library includes
#include "Helpers.h"

// SDK includes
#include <triobj.h>

// External includes
#include <windows.h>

namespace Donut
{
	// Convert to the internal string structure
	STRING_TYPE convertToString(const MSTR& _mstr)
	{
		return STRING_TYPE(_mstr.ToCStr().data());
	}

	// Creates a directory
	void CreateDirectory_DNT(const STRING_TYPE& _folderLocation)
	{
		CreateDirectoryA(_folderLocation.data(), LPSECURITY_ATTRIBUTES());
	}

	// Fetch a mesh from an Inode
	Mesh* GetMeshFromNode(INode* _currentNode)
	{
		TriObject* triObj = static_cast<TriObject*>(_currentNode->GetObjectRef());
		Mesh& currentMesh = triObj->GetMesh();
		return &currentMesh;
	}
}