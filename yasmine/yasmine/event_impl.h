//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef EVENT_IMPL_447B2A6E_B2CC_4851_A3EB_68ACC838AEA2
#define EVENT_IMPL_447B2A6E_B2CC_4851_A3EB_68ACC838AEA2


#include <string>
#include <map>

#include "event.h"
#include "event_fwd.h"


namespace sxy
{


class event_impl:
	public event
{
public:
	explicit event_impl( const event_id _event_id );
	virtual ~event_impl() override;
	event_impl( const event_impl& ) = delete;
	event_impl& operator=( const event_impl& ) = delete;
	virtual event_id get_id() const override;
	static event_sptr create_event( const event_id _event_id );


private:
	event_id event_id_;
};


}


#endif