//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016-2018 Seadex GmbH                                                              //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/Licenses.html.           //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "model_version.hpp"

#include <iostream>

#include "essentials/sxprintf.hpp"

#include "build_number.hpp"


namespace sxy
{


namespace version
{


namespace
{


const sxe::uint16_t VERSION_MAJOR( 0 );
const sxe::uint16_t VERSION_MINOR( 2 );
const sxe::uint16_t VERSION_PATCH( 1 );


}


void log_version()
{
	std::cout << sxe::sxprintf( "yasmine_model library version %.%.%.%.", get_major_version(),
		get_minor_version(), get_patch_version(), get_build_number() ) << std::endl;
}


sxe::uint16_t get_major_version()
{
	return( VERSION_MAJOR );
}


sxe::uint16_t get_minor_version()
{
	return( VERSION_MINOR );
}


sxe::uint16_t get_patch_version()
{
	return( VERSION_PATCH );
}


sxe::uint16_t get_build_number()
{
	return( BUILD_NUMBER );
}


}


}
