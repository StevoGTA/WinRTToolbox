//----------------------------------------------------------------------------------------------------------------------
//	TimeAndDate+Extensions.h			©2026 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "TimeAndDate.h"
#include "TInspectable.h"

using DateTime = winrt::Windows::Foundation::DateTime;
using TimeSpan = winrt::Windows::Foundation::TimeSpan;

//----------------------------------------------------------------------------------------------------------------------
// MARK: IInspectables
DEFINE_TCVInspectable(GregorianDateComponentsCVInspectable, SGregorianDate::Components);

//----------------------------------------------------------------------------------------------------------------------
// MARK: Functions
SGregorianDate::Components	toGregorianDateComponents(const DateTime& dateTime, bool includeYear = true,
									bool includeMonth = true, bool includeDay = true, bool includeHour = true,
									bool includeMinute = true, bool includeSecond = true);
SGregorianDate::Components	toGregorianDateComponents(const TimeSpan& timeSpan, bool includeHour = true,
									bool includeMinute = true, bool includeSecond = true);

DateTime					toDateTime(const SGregorianDate::Components& gregorianDateComponents);
TimeSpan					toTimeSpan(const SGregorianDate::Components& gregorianDateComponents);
