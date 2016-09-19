//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef CHOICE_IMPL_E8DE2646_E657_4A8B_96EE_B0699FB5652D
#define CHOICE_IMPL_E8DE2646_E657_4A8B_96EE_B0699FB5652D


#include "choice.h"
#include "region_pseudostate_impl.h"


namespace sxy
{


class choice_impl final:
	public virtual choice, public region_pseudostate_impl
{
public:
	explicit choice_impl( const std::string& _name );
	virtual ~choice_impl() override;
	choice_impl( const choice_impl& ) = delete;
	choice_impl& operator=( const choice_impl& ) = delete;
	virtual bool check( state_machine_defects& _defects ) const override;
	virtual void accept_vertex_visitor( const_vertex_visitor& _visitor ) const override;
	virtual void accept_vertex_visitor( vertex_visitor& _visitor ) override;
	virtual void accept_pseudostate_visitor( pseudostate_visitor& _visitor ) const override;
};


}


#endif