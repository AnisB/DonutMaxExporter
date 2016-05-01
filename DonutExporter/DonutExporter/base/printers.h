/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/
#ifndef DONUT_DEBUG_PRINTER
#define DONUT_DEBUG_PRINTER


// SDK includes
#include <maxscript\maxscript.h>

// STL Includes
#include <iostream>
#include <sstream>
#include <cstdio>

namespace Donut
{
	// Print terms
	#define END_PRINT std::endl

	// General print macro
	#define PRINT_GENERAL(FLAG, TYPE, ENONCE)\
	{\
		std::stringstream ss;\
		ss << "[" << FLAG <<"]"<< "["<<TYPE<<"]"<<ENONCE<<END_PRINT;\
		mprintf(CStr(ss.str().c_str()).ToMSTR());\
	}

	// General purpose MACROS
	#if _SILENT
		#define PRINT_DEBUG(TYPE, ENONCE) {}
		#define PRINT_INFO(TYPE, ENONCE) {}
		#define PRINT_WARNING(TYPE, ENONCE) {}
		#define PRINT_ERROR(TYPE, ENONCE) {}
	#else
		#if _DEBUG
		#define PRINT_DEBUG(TYPE, ENONCE) PRINT_GENERAL("DEBUG", TYPE, ENONCE)
		#else
		#define PRINT_DEBUG(TYPE, ENONCE) {}
		#endif
		#define PRINT_INFO(TYPE, ENONCE) PRINT_GENERAL("INFO", TYPE, ENONCE)
		#define PRINT_WARNING(TYPE, ENONCE) PRINT_GENERAL("WARNING", TYPE, ENONCE)
		#define PRINT_ERROR(TYPE, ENONCE) PRINT_GENERAL("ERROR", TYPE, ENONCE)
	#endif

}

#endif