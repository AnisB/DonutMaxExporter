#ifndef MAX_EXPORT_HELPERS_H
#define MAX_EXPORT_HELPERS_H

// Library includes
#include "base/common.h"

// SDK includes
#include <maxscript\maxscript.h>

namespace Donut
{
	// Convert to the internal string structure
	STRING_TYPE convertToString(const MSTR& _mstr);

	// Create a directory
	void CreateDirectory_DNT(const STRING_TYPE& _folderLocation);

	// Fetch Mesh from Inode
	Mesh* GetMeshFromNode(INode* _currentNode);
}

#endif // MAX_EXPORT_HELPERS_H