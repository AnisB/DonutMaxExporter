
// Library includes
#include "Exporters.h"

// SDK includes
#include "maxscript\macros\define_instantiation_functions.h"

// Exporting functions
def_visible_primitive(Donut_ExportINodes, "Donut_ExportINodes");

Value* Donut_ExportINodes_cf(Value** _argArray, int _nbArgs)
{
	// Check the nb of args
	check_arg_count(Donut_ExportINodes, 4, _nbArgs);
	// Parameters are:
		// Geometry array
		// Sugar export folder
		// Geometry export array

	Array* geometryArray = static_cast<Array*>(_argArray[0]);
	Donut::ExportINodes(geometryArray);

	return &ok;
}


