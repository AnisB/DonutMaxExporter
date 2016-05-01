
// Library includes
#include "MaxExporter.h"
// SDK includes
#include <maxscript\maxscript.h>
#include "maxscript\macros\define_instantiation_functions.h"

// Exporting functions
def_visible_primitive(ExportForDonut, "ExportForDonut");

Value* ExportForDonut_cf(Value** _argArray, int _nbArgs)
{
	// Check the nb of args
	check_arg_count(ExportForDonut, 4, _nbArgs);

	// Fetch the location, project name and level name;
	MSTR outputDir = _argArray[0]->to_mstr();
	MSTR projectName = _argArray[1]->to_mstr();
	MSTR levelName = _argArray[2]->to_mstr();

	// Create and init the exporter
	Donut::TMaxExporter currentExporter;

	// Init the folder hierachy
	currentExporter.Init(outputDir, projectName, levelName);

	// Fetch the geometry array
	Array* geometryArray = static_cast<Array*>(_argArray[3]);
	currentExporter.ExportScene(geometryArray);

	// Ok its done, goodbye my friend
	return &ok;
}


