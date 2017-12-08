/*
 * call-p.h
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

#ifndef _CALL_P_H_
#define _CALL_P_H_

#include "call.h"
#include "conference/conference.h"
#include "conference/session/call-session-listener.h"
#include "object/object-p.h"

// TODO: Remove me later.
#include "private.h"

// =============================================================================

LINPHONE_BEGIN_NAMESPACE

class CallSession;

class CallPrivate :	public ObjectPrivate, public CallSessionListener {
public:
	CallPrivate () = default;
	virtual ~CallPrivate () = default;

	void initiateIncoming ();
	bool initiateOutgoing ();
	void iterate (time_t currentRealTime, bool oneSecondElapsed);
	void startIncomingNotification ();

	int startInvite (const Address *destination);

	virtual std::shared_ptr<CallSession> getActiveSession () const { return nullptr; }
	bool getAudioMuted () const;

	LinphoneProxyConfig *getDestProxy () const;
	IceSession *getIceSession () const;
	unsigned int getMediaStartCount () const;
	MediaStream *getMediaStream (LinphoneStreamType type) const;
	SalCallOp *getOp () const;
	void setAudioMuted (bool value);

	void createPlayer () const;

private:
	void resetFirstVideoFrameDecoded ();
	void startRemoteRing ();
	void terminateBecauseOfLostMedia ();

	/* CallSessionListener */
	void onAckBeingSent (const std::shared_ptr<const CallSession> &session, LinphoneHeaders *headers) override;
	void onAckReceived (const std::shared_ptr<const CallSession> &session, LinphoneHeaders *headers) override;
	void onBackgroundTaskToBeStarted (const std::shared_ptr<const CallSession> &session) override;
	void onBackgroundTaskToBeStopped (const std::shared_ptr<const CallSession> &session) override;
	bool onCallSessionAccepted (const std::shared_ptr<const CallSession> &session) override;
	void onCallSessionSetReleased (const std::shared_ptr<const CallSession> &session) override;
	void onCallSessionSetTerminated (const std::shared_ptr<const CallSession> &session) override;
	void onCallSessionStateChanged (const std::shared_ptr<const CallSession> &session, LinphoneCallState state, const std::string &message) override;
	void onCheckForAcceptation (const std::shared_ptr<const CallSession> &session) override;
	void onDtmfReceived (const std::shared_ptr<const CallSession> &session, char dtmf) override;
	void onIncomingCallSessionNotified (const std::shared_ptr<const CallSession> &session) override;
	void onIncomingCallSessionStarted (const std::shared_ptr<const CallSession> &session) override;
	void onIncomingCallSessionTimeoutCheck (const std::shared_ptr<const CallSession> &session, int elapsed, bool oneSecondElapsed) override;
	void onInfoReceived (const std::shared_ptr<const CallSession> &session, const LinphoneInfoMessage *im) override;
	void onNoMediaTimeoutCheck (const std::shared_ptr<const CallSession> &session, bool oneSecondElapsed) override;
	void onEncryptionChanged (const std::shared_ptr<const CallSession> &session, bool activated, const std::string &authToken) override;
	void onStatsUpdated (const std::shared_ptr<const CallSession> &session, const LinphoneCallStats *stats) override;
	void onResetCurrentSession (const std::shared_ptr<const CallSession> &session) override;
	void onSetCurrentSession (const std::shared_ptr<const CallSession> &session) override;
	void onFirstVideoFrameDecoded (const std::shared_ptr<const CallSession> &session) override;
	void onResetFirstVideoFrameDecoded (const std::shared_ptr<const CallSession> &session) override;
	void onPlayErrorTone (const std::shared_ptr<const CallSession> &session, LinphoneReason reason) override;
	void onRingbackToneRequested (const std::shared_ptr<const CallSession> &session, bool requested) override;
	void onStartRinging (const std::shared_ptr<const CallSession> &session) override;
	void onStopRinging (const std::shared_ptr<const CallSession> &session) override;
	void onStopRingingIfInCall (const std::shared_ptr<const CallSession> &session) override;
	void onStopRingingIfNeeded (const std::shared_ptr<const CallSession> &session) override;
	bool isPlayingRingbackTone (const std::shared_ptr<const CallSession> &session) override;

	mutable LinphonePlayer *player = nullptr;

	CallCallbackObj nextVideoFrameDecoded;

	unsigned long backgroundTaskId = 0;

	bool ringingBeep = false;
	bool playingRingbackTone = false;

	L_DECLARE_PUBLIC(Call);
};

LINPHONE_END_NAMESPACE

#endif // ifndef _CALL_P_H_
