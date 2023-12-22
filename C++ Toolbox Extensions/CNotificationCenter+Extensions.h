//----------------------------------------------------------------------------------------------------------------------
//	CNotificationCenter+Extensions.h			©2021 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "CNotificationCenter.h"
#include "TInspectable.h"

//----------------------------------------------------------------------------------------------------------------------
// MARK: NotificationCenterRInspectable

struct NotificationCenterRInspectable : public TRInspectable<NotificationCenterRInspectable, CNotificationCenter> {
	// Methods
	public:
		NotificationCenterRInspectable(CNotificationCenter& value) :
			TRInspectable<NotificationCenterRInspectable, CNotificationCenter>(value)
			{}
};
