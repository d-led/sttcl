/*
 * IConcurrentStateMachine.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef ICONCURRENTSTATEMACHINE_H_
#define ICONCURRENTSTATEMACHINE_H_

#include "Region.h"
#include "EventArgsClass.h"

namespace Application
{

class ConcurrentStateMachine;

class IConcurrentStateMachine
{
public:
	typedef sttcl::RegionBase<Application::ConcurrentStateMachine, Application::IConcurrentStateMachine, EventArgsClass> RegionContext;

	virtual void handleEvent1(ConcurrentStateMachine* context,RegionContext* regionContext, sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual void handleEvent2(ConcurrentStateMachine* context,RegionContext* regionContext, sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual void handleEvent3(ConcurrentStateMachine* context,RegionContext* regionContext, sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual void handleEvent4(ConcurrentStateMachine* context,RegionContext* regionContext, sttcl::RefCountPtr<EventArgsClass> eventArgs) = 0;
	virtual ~IConcurrentStateMachine() {}
};

}

#endif /* ICONCURRENTSTATEMACHINE_H_ */
