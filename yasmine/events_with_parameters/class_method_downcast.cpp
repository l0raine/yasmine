//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "class_method_downcast.hpp"

#include <iostream>


namespace sxy
{


class_method_downcast::class_method_downcast()
{
	state_machine_uptr state_machine = setup_state_machine( "downcast_event_state_machine" );
	state_machine->start_state_machine();
	state_machine->fire_event( event_1::create( "parameter 1 test" ) );
	state_machine->fire_event( event_2::create( 2, 3.4 ) );
	state_machine->stop_state_machine();
}


class_method_downcast::~class_method_downcast() Y_NOEXCEPT
{
	// Nothing to do...
}


#ifndef Y_CPP03_BOOST
void class_method_downcast::do_something_event_2_parameters( const event_2& _event )
{
	std::cout << "Parameters of event " << _event.get_name() << " are:\n" << _event.get_param_1() << "\n" <<
		_event.get_param_2() << std::endl;
}
#else
void class_method_downcast::do_something_event_2_parameters( const event& _event )
{
	const event_2* specialized_event = dynamic_cast< const event_2* >( &_event );
	if( specialized_event )
	{
		std::cout << "Parameters of event " << specialized_event->get_name() << " are:\n" << specialized_event->get_param_1() << "\n" <<
			specialized_event->get_param_2() << std::endl;
	}
	else
	{
		const completion_event* specialized_event2 = dynamic_cast< const completion_event* >( &_event );
		if( specialized_event2 )
		{
			do_something_event_0_parameters( _event );
		}
		else
		{
			throw sxy::exception( "Invalid event type!" );
		}
	}
}
#endif


#ifndef Y_CPP03_BOOST
void class_method_downcast::do_something_event_1_parameter( const event_1& _event )
{
	std::cout << "Parameter of event " << _event.get_name() << " is: " << _event.get_param() << std::endl;
}
#else
void class_method_downcast::do_something_event_1_parameter( const event& _event )
{
	const event_1* specialized_event = dynamic_cast< const event_1* >( &_event );
	if( specialized_event )
	{
		std::cout << "Parameter of event " << specialized_event->get_name() << " is: " << specialized_event->get_param() << std::endl;
	}
	else
	{
		 throw sxy::exception( "Invalid event type!" );
	}
}
#endif


#ifndef Y_CPP03_BOOST
void class_method_downcast::do_something_event_0_parameters( const completion_event& _event )
{
	std::cout << "Completion event has no parameters." << std::endl;
}
#else
void class_method_downcast::do_something_event_0_parameters( const event& _event )
{
	const completion_event* specialized_event = dynamic_cast< const completion_event* >( &_event );
	if( specialized_event )
	{
		std::cout << "Completion event has no parameters." << std::endl;
	}
	else
	{
		throw sxy::exception( "Invalid event type!" );
	}	
}
#endif


state_machine_uptr class_method_downcast::setup_state_machine( const std::string& _name )
{
	state_machine_uptr state_machine = Y_MAKE_UNIQUE< sxy::state_machine >( _name );
	composite_state& root_state = state_machine->get_root_state();
	region& main_region = root_state.add_region( "main region" );
	initial_pseudostate& initial_pseudostate = main_region.add_initial_pseudostate( "initial" );
#ifndef Y_CPP03_BOOST	
	simple_state& simple_state_1 = main_region.add_simple_state( "1",
			Y_BEHAVIOR_METHOD_EVENT( &class_method_downcast::do_something_event_2_parameters,
				&class_method_downcast::do_something_event_0_parameters ),
			Y_BEHAVIOR_METHOD_EVENT( &class_method_downcast::do_something_event_2_parameters,
				&class_method_downcast::do_something_event_0_parameters),
			Y_BEHAVIOR_METHOD_EVENT( &class_method_downcast::do_something_event_1_parameter ) );

	simple_state& simple_state_2 = main_region.add_simple_state( "2",
		Y_BEHAVIOR_METHOD_EVENT( &class_method_downcast::do_something_event_1_parameter ),
		Y_BEHAVIOR_METHOD_EVENT( &class_method_downcast::do_something_event_1_parameter ),
		Y_BEHAVIOR_METHOD_EVENT( &class_method_downcast::do_something_event_2_parameters ) );

	state_machine->add_transition( COMPLETION_EVENT_ID, initial_pseudostate, simple_state_1,
		Y_BEHAVIOR_METHOD_EVENT( &class_method_downcast::do_something_event_0_parameters ) );
	state_machine->add_transition( EVENT_1, simple_state_1, simple_state_2,
		Y_BEHAVIOR_METHOD_EVENT( &class_method_downcast::do_something_event_1_parameter ) );
	state_machine->add_transition( EVENT_2, simple_state_2, simple_state_1,
		Y_BEHAVIOR_METHOD_EVENT( &class_method_downcast::do_something_event_2_parameters ) );
#else
	simple_state& simple_state_1 = main_region.add_simple_state( "1",
		sxy::behavior_function( sxy::bind( &class_method_downcast::do_something_event_2_parameters, this, sxy::_1 ) ),		
		sxy::behavior_function( sxy::bind( &class_method_downcast::do_something_event_2_parameters, this, sxy::_1 ) ),
		sxy::behavior_function( sxy::bind( &class_method_downcast::do_something_event_1_parameter, this, sxy::_1 ) ) );

	simple_state& simple_state_2 = main_region.add_simple_state( "2",
		sxy::behavior_function( sxy::bind( &class_method_downcast::do_something_event_1_parameter, this, sxy::_1 ) ),
		sxy::behavior_function( sxy::bind( &class_method_downcast::do_something_event_1_parameter, this, sxy::_1 ) ),
		sxy::behavior_function( sxy::bind( &class_method_downcast::do_something_event_2_parameters, this, sxy::_1 ) ) );

	state_machine->add_transition( COMPLETION_EVENT_ID, initial_pseudostate, simple_state_1,
		sxy::behavior_function( sxy::bind( &class_method_downcast::do_something_event_0_parameters, this, sxy::_1 ) ) );
	state_machine->add_transition( EVENT_1, simple_state_1, simple_state_2,
		sxy::behavior_function( sxy::bind( &class_method_downcast::do_something_event_1_parameter, this, sxy::_1 ) ) );
	state_machine->add_transition( EVENT_2, simple_state_2, simple_state_1,
		sxy::behavior_function( sxy::bind( &class_method_downcast::do_something_event_2_parameters, this, sxy::_1 ) ) );
#endif
	

	return( sxy::move( state_machine ) );
}


void use_method_downcast()
{
	class_method_downcast method_downcast;
}


}
