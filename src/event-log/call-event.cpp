/*
 * call-event.cpp
 * Copyright (C) 2010-2017 Belledonne Communications SARL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "call-event.h"
#include "event-log-p.h"

// =============================================================================

using namespace std;

LINPHONE_BEGIN_NAMESPACE

class CallEventPrivate : public EventLogPrivate {
public:
	shared_ptr<Call> call;
};

// -----------------------------------------------------------------------------

CallEvent::CallEvent (Type type, time_t time, const shared_ptr<Call> &call) :
	EventLog(*new CallEventPrivate, type, time) {
	L_D();
	L_ASSERT(call);
	L_ASSERT(type == Type::CallStart || type == Type::CallEnd);
	d->call = call;
}

CallEvent::CallEvent (const CallEvent &src) : CallEvent(src.getType(), src.getTime(), src.getCall()) {}

CallEvent &CallEvent::operator= (const CallEvent &src) {
	L_D();
	if (this != &src) {
		EventLog::operator=(src);
		d->call = src.getPrivate()->call;
	}

	return *this;
}

shared_ptr<Call> CallEvent::getCall () const {
	L_D();
	return d->call;
}

LINPHONE_END_NAMESPACE
