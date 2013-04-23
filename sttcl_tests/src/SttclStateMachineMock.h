/*
 * SttclStateMachineMock.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef STTCLSTATEMACHINEMOCK_H_
#define STTCLSTATEMACHINEMOCK_H_

#include <iostream>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include <State.h>
#include <SttclMutex.h>
#include <SttclTime.h>
#include "ITestStateInterface.h"
#include "IStateMachineHooks.h"
#include "SttclTestLog.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class SttclStateMachineMock
: public sttcl::StateMachine<SttclStateMachineMock,ITestStateInterface>
, public IStateMachineHooks
{
public:

	typedef sttcl::StateMachine<SttclStateMachineMock,ITestStateInterface> StateMachineBaseClass;

	SttclStateMachineMock(const std::string& stateMachineId = "<anonymous>", IStateMachineHooks::StateBaseClass* initialState = NULL)
	: initialState_(initialState)
	, enableLogs_(false)
	, stateMachineId_(stateMachineId)
	{
		ON_CALL(*this, initializeImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMachineMock::initializeImplCall));
		ON_CALL(*this, finalizeImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMachineMock::finalizeImplCall));
		ON_CALL(*this, subStateMachineCompletedImpl(_))
			.WillByDefault(Invoke(this, &SttclStateMachineMock::subStateMachineCompletedImplCall));
		ON_CALL(*this, getInitialStateImpl())
			.WillByDefault(Invoke((const SttclStateMachineMock*)this, &SttclStateMachineMock::getInitialStateImplCall));
		ON_CALL(*this, isReadyImpl())
			.WillByDefault(Invoke((const SttclStateMachineMock*)this, &SttclStateMachineMock::isReadyImplCall));
	}

	virtual ~SttclStateMachineMock()
	{
//		finalize(true);
	}

	const std::string& id() const { return stateMachineId_; }
	void setInitialState(IStateMachineHooks::StateBaseClass* initialState)
	{
    	sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
		initialState_ = initialState;
	}

	void enableLogs(bool enable)
	{
		enableLogs_ = enable;
	}

	MOCK_METHOD1(initializeImpl, bool (bool force));
	MOCK_METHOD1(finalizeImpl,void (bool finalizeSubStateMachines));
	MOCK_METHOD1(subStateMachineCompletedImpl, void (IStateMachineHooks::StateBaseClass* state));
    MOCK_CONST_METHOD0(getInitialStateImpl, IStateMachineHooks::StateBaseClass* ());
    MOCK_CONST_METHOD0(isReadyImpl, bool ());

protected:
	mutable sttcl::internal::SttclMutex<> internalGuard_;
    IStateMachineHooks::StateBaseClass* initialState_;
    bool enableLogs_;
    std::string stateMachineId_;

private:
	bool isReadyImplCall() const
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclStateMachineMock::StateMachineBaseClass::isReadyImpl() ...");
		}
    	return SttclStateMachineMock::StateMachineBaseClass::isReadyImpl();
    }

    bool initializeImplCall(bool force)
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclStateMachineMock::StateMachineBaseClass::initializeImpl(" << force << ") ...");
		}
    	return SttclStateMachineMock::StateMachineBaseClass::initializeImpl(force);
    }

    void finalizeImplCall(bool finalizeSubStateMachines)
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclStateMachineMock::StateMachineBaseClass::finalizeImpl(" << finalizeSubStateMachines << ") ...");
		}
		SttclStateMachineMock::StateMachineBaseClass::finalizeImpl(finalizeSubStateMachines);
    }

    void subStateMachineCompletedImplCall(IStateMachineHooks::StateBaseClass* state)
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " Calling SttclStateMachineMock::StateMachineBaseClass::subStateMachineCompletedImpl(" << state << ") ...");
		}
    	return SttclStateMachineMock::StateMachineBaseClass::subStateMachineCompletedImpl(state);
    }

    IStateMachineHooks::StateBaseClass* getInitialStateImplCall() const
    {
		if(enableLogs_)
		{
			STTCL_TEST_LOG(id() << " SttclStateMachineMock::getInitialStateImplCall(), initialState: = " << initialState_);
		}
    	sttcl::internal::AutoLocker<sttcl::internal::SttclMutex<> > lock(internalGuard_);
    	return initialState_;
    }

};
#endif /* STTCLSTATEMACHINEMOCK_H_ */