/************************************************************************
	filename: 	CEGUIEventSet.h
	created:	21/2/2004
	author:		Paul D Turner
	
	purpose:	Defines class for a named collection of Event objects
*************************************************************************/
/*************************************************************************
    Crazy Eddie's GUI System (http://www.cegui.org.uk)
    Copyright (C)2004 - 2005 Paul D Turner (paul@cegui.org.uk)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*************************************************************************/
#ifndef _CEGUIEventSet_h_
#define _CEGUIEventSet_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIEvent.h"
#include "CEGUIIteratorBase.h"
#include <map>

#if defined (_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


// Start of CEGUI namespace section
namespace CEGUI
{
/*!
\brief
	Class that collects together a set of Event objects.

    The EventSet is a means for code to attach a handler function to some
    named event, and later, for that event to be fired and the subscribed
    handler(s) called.
    \par
    As of 0.5, the EventSet no longer needs to be filled with available events.
    Events are now added to the set as they are first used; that is, the first
    time a handler is subscribed to an event for a given EventSet, an Event
    object is created and added to the EventSet.
    \par
    Instead of throwing an exception when firing an event that does not actually
    exist in the set, we now do nothing (if the Event does not exist, then it
    has no handlers subscribed, and therefore doing nothing is the correct
    course action).
*/
class CEGUIEXPORT EventSet
{
public:
	/*!
	\brief
		Constructor for EventSet objects
	*/
	EventSet();


	/*!
	\brief
		Destructor for EventSet objects
	*/
	virtual ~EventSet(void);


	/*!
	\brief
		Add a new Event to the EventSet with the given name.

	\param name
		String object containing the name to give the new Event.  The name must be unique for the EventSet.

	\return
		Nothing

	\exception AlreadyExistsException	Thrown if an Event already exists named \a name.
	*/
	void	addEvent(const String& name);


	/*!
	\brief
		Removes the Event with the given name.  All connections to the event are disconnected.

	\param name
		String object containing the name of the Event to remove.  If no such Event exists, nothing happens.

	\return
		Nothing.
	*/
	void	removeEvent(const String& name);


	/*!
	\brief
		Remove all Event objects from the EventSet

	\return
		Nothing
	*/
	void	removeAllEvents(void);


	/*!
	\brief
		Checks to see if an Event with the given name is present in the EventSet.

	\return
		true if an Event named \a name was found, or false if the Event was not found
	*/
	bool	isEventPresent(const String& name);


    /*!
    \brief
        Subscribes a handler to the named Event.  If the named Event is not yet
        present in the EventSet, it is created and added.

    \param name
        String object containing the name of the Event to subscribe to.

    \param subscriber
        Function or object that is to be subscribed to the Event.

    \return
        Connection object that can be used to check the status of the Event
        connection and to disconnect (unsubscribe) from the Event.
    */
    virtual Event::Connection subscribeEvent(const String& name, Event::Subscriber subscriber);


    /*!
    \brief
        Subscribes a handler to the specified group of the named Event.  If the
        named Event is not yet present in the EventSet, it is created and added.

    \param name
        String object containing the name of the Event to subscribe to.

    \param group
        Group which is to be subscribed to.  Subscription groups are called in
        ascending order.

    \param subscriber
        Function or object that is to be subscribed to the Event.

    \return
        Connection object that can be used to check the status of the Event
        connection and to disconnect (unsubscribe) from the Event.
    */
    virtual Event::Connection subscribeEvent(const String& name, Event::Group group, Event::Subscriber subscriber);


    /*!
    \brief
        Subscribes the named Event to a scripted funtion

    \param name
        String object containing the name of the Event to subscribe to.

    \param subscriber_name
        String object containing the name of the script funtion that is to be
        subscribed to the Event.

    \return
        Connection object that can be used to check the status of the Event
        connection and to disconnect (unsubscribe) from the Event.
    */
    virtual Event::Connection subscribeScriptedEvent(const String& name, const String& subscriber_name);


    /*!
    \brief
        Subscribes the specified group of the named Event to a scripted funtion.

    \param name
        String object containing the name of the Event to subscribe to.

    \param group
        Group which is to be subscribed to.  Subscription groups are called in
        ascending order.

    \param subscriber_name
        String object containing the name of the script funtion that is to be
        subscribed to the Event.

    \return
        Connection object that can be used to check the status of the Event
        connection and to disconnect (unsubscribe) from the Event.
    */
    virtual Event::Connection subscribeScriptedEvent(const String& name, Event::Group group, const String& subscriber_name);


    /*!
    \brief
        Fires the named event passing the given EventArgs object.

    \param name
        String object holding the name of the Event that is to be fired
        (triggered)

    \param args
        The EventArgs (or derived) object that is to be bassed to each
        subscriber of the Event.  Once all subscribers
        have been called the 'handled' field of the event is updated
        appropriately.

    \param eventNamespace
        String object describing the global event namespace prefix for this
        event.

    \return
        Nothing.
    */
    virtual void fireEvent(const String& name, EventArgs& args, const String& eventNamespace = "");


	/*!
	\brief
		Return whether the EventSet is muted or not.

	\return
		- true if the EventSet is muted.  All requests to fire events will be ignored.
		- false if the EventSet is not muted.  All requests to fire events are processed as normal.
	*/
	bool	isMuted(void) const;


	/*!
	\brief
		Set the mute state for this EventSet.

	\param setting
		- true if the EventSet is to be muted (no further event firing requests will be honoured until EventSet is unmuted).
		- false if the EventSet is not to be muted and all events should fired as requested.

	\return
		Nothing.
	*/
	void	setMutedState(bool setting);


protected:
    /*!
    \brief
        Return a pointer to the Event object with the given name, optionally
        adding such an Event object to the EventSet if it does not already
        exist.

    \param name
        String object holding the name of the Event to return.

    \param autoAdd
        - true if an Event object named \a name should be added to the set
          if such an Event does not currently exist.
        - false if no object should automatically be added to the set.  In this
          case, if the Event does not already exist 0 will be returned.

    \return
        Pointer to the Event object in this EventSet with the specifed name.
        Or 0 if such an Event does not exist and \a autoAdd was false.
    */
    Event* getEventObject(const String& name, bool autoAdd = false);

    /*!
    \brief
        Implementation event firing member
    */
    void fireEvent_impl(const String& name, EventArgs& args);


	// Do not allow copying, assignment, or any other usage than simple creation.
	EventSet(EventSet& e) {}
	EventSet& operator=(EventSet& e) {return *this;}

	typedef std::map<String, Event*, String::FastLessCompare>	EventMap;
	EventMap	d_events;

	bool	d_muted;	//!< true if events for this EventSet have been muted.

public:
	/*************************************************************************
		Iterator stuff
	*************************************************************************/
	typedef	ConstBaseIterator<EventMap>	EventIterator;

	/*!
	\brief
		Return a EventSet::EventIterator object to iterate over the available events.
	*/
	EventIterator	getIterator(void) const;
};

} // End of  CEGUI namespace section


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	// end of guard _CEGUIEventSet_h_
