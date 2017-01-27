//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "try_to_build_compound_transition_visitor.hpp"

#include "base.hpp"

#include "join.hpp"
#include "compound_transition_impl.hpp"
#include "compound_transition_builder.hpp"
#include "event.hpp"
#include "composite_state.hpp"
#include "simple_state.hpp"
#include "final_state.hpp"
#include "initial_pseudostate.hpp"
#include "choice.hpp"
#include "junction.hpp"
#include "join.hpp"
#include "fork.hpp"
#include "entry_point.hpp"
#include "exit_point.hpp"
#include "deep_history.hpp"
#include "shallow_history.hpp"
#include "terminate_pseudostate.hpp"


namespace sxy
{


try_to_build_compound_transition_visitor::try_to_build_compound_transition_visitor( transition& _enabled_transition,
	compound_transitions& _enabled_compound_transitions,	bool& _is_built, const event& _event )
	: enabled_transition_( _enabled_transition ),
		enabled_compound_transitions_( _enabled_compound_transitions ),
		is_built_( _is_built ),
		event_( _event )
{
	is_built_ = false;
}


try_to_build_compound_transition_visitor::~try_to_build_compound_transition_visitor() Y_NOEXCEPT
{
	// Nothing to do...
}


void try_to_build_compound_transition_visitor::visit( const composite_state& _composite_state )
{
	Y_UNUSED_PARAMETER( _composite_state );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::visit(	const simple_state& _simple_state )
{
	Y_UNUSED_PARAMETER( _simple_state );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::visit(	const final_state& _final_state )
{
	Y_UNUSED_PARAMETER( _final_state );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::visit(	const initial_pseudostate& _initial_pseudostate )
{
	Y_UNUSED_PARAMETER( _initial_pseudostate );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::visit(	const choice& _choice )
{
	Y_UNUSED_PARAMETER( _choice );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::visit( const junction& _junction )
{
	Y_UNUSED_PARAMETER( _junction );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::visit( const join& _join )
{
	check_if_join_is_active_and_was_not_processed_yet( _join );
}


void try_to_build_compound_transition_visitor::visit(	const fork& _fork )
{
	Y_UNUSED_PARAMETER( _fork );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::visit(	const entry_point& _entry_point )
{
	Y_UNUSED_PARAMETER( _entry_point );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::visit(	const exit_point& _exit_point )
{
	Y_UNUSED_PARAMETER( _exit_point );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::visit(	const deep_history& _deep_history )
{
	Y_UNUSED_PARAMETER( _deep_history );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::visit(	const shallow_history& _shallow_history )
{
	Y_UNUSED_PARAMETER( _shallow_history );
	build_compound_transition_and_insert_in_container();
}
																					

void try_to_build_compound_transition_visitor::visit(	const terminate_pseudostate& _terminate_pseudostate )
{
	Y_UNUSED_PARAMETER( _terminate_pseudostate );
	build_compound_transition_and_insert_in_container();
}


void try_to_build_compound_transition_visitor::build_compound_transition_and_insert_in_container()
{
	compound_transition_uptr compound_transition = sxy::build_compound_transition( enabled_transition_, event_ );
	if( compound_transition )
	{
		enabled_compound_transitions_.push_back( sxy::move( compound_transition ) );
		is_built_ = true;
	}
}


void try_to_build_compound_transition_visitor::check_if_join_is_active_and_was_not_processed_yet( 
	const join& _join )
{
	const bool transition_was_already_used = 
		check_if_transition_was_already_used( enabled_transition_, enabled_compound_transitions_ );

	if( !transition_was_already_used )
	{
		const bool all_incoming_transitions_enabled 
			= _join.check_if_all_source_states_of_incoming_transitions_are_active();
		if( all_incoming_transitions_enabled )
		{
			build_compound_transition_and_insert_in_container( );
		}
	}
	else
	{
		// The compound transition for this join was already built somewhere else. So the transition search has to end in
		// this branch.
		is_built_ = true;
	}
}


bool try_to_build_compound_transition_visitor::check_if_transition_was_already_used(	
	const transition& _transition,	compound_transitions& _compound_transitions )
{
	bool already_used = false;
	Y_FOR( const compound_transition_uptr& compound_transition, _compound_transitions )
	{
		already_used = compound_transition->check_if_starts_with( _transition );
		if( already_used )
		{
			break;
		}
	}

	return( already_used );
}


}