//----------------------------------------------------------------------------------------------------------------------
//	TimeAndDate+Extensions.cpp			©2026 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#include "TimeAndDate+Extensions.h"

// MARK: Functions

//----------------------------------------------------------------------------------------------------------------------
SGregorianDate::Components toGregorianDateComponents(const DateTime& dateTime, bool includeYear, bool includeMonth,
		bool includeDay, bool includeHour, bool includeMinute, bool includeSecond)
//----------------------------------------------------------------------------------------------------------------------
{
	// Get gregorian date
	SGregorianDate	gregorianDate(((UniversalTime)dateTime.time_since_epoch().count() / 10000000.0) -
							kUniversalTimeInterval1601To2001);

	return SGregorianDate::Components(includeYear ? OV<UInt32>(gregorianDate.getYear()) : OV<UInt32>(),
			includeMonth ? OV<UInt8>(gregorianDate.getMonth()) : OV<UInt8>(),
			includeDay ? OV<UInt8>(gregorianDate.getDay()) : OV<UInt8>(),
			includeHour ? OV<UInt8>(gregorianDate.getHour()) : OV<UInt8>(),
			includeMinute ? OV<UInt8>(gregorianDate.getMinute()) : OV<UInt8>(),
			includeSecond ? OV<Float32>(gregorianDate.getSecond()) : OV<Float32>());
}

//----------------------------------------------------------------------------------------------------------------------
SGregorianDate::Components toGregorianDateComponents(const TimeSpan& timeSpan, bool includeHour, bool includeMinute,
		bool includeSecond)
//----------------------------------------------------------------------------------------------------------------------
{
	return SGregorianDate::Components(OV<UInt32>(), OV<UInt8>(), OV<UInt8>(),
			includeHour ? OV<UInt8>((timeSpan.count() / 36000000000) % 24) : OV<UInt8>(),
			includeMinute ? OV<UInt8>((timeSpan.count() / 600000000) % 60) : OV<UInt8>(),
			includeSecond ? OV<Float32>((timeSpan.count() / 10000000) % 60) : OV<Float32>());
}

//----------------------------------------------------------------------------------------------------------------------
DateTime toDateTime(const SGregorianDate::Components& gregorianDateComponents)
//----------------------------------------------------------------------------------------------------------------------
{
	return DateTime{
			std::chrono::duration<int64_t, std::ratio<1, 10'000'000>>(
					(int64_t) (SGregorianDate(gregorianDateComponents).getUniversalTime() +
									kUniversalTimeInterval1601To2001) *
							10'000'000)};
}

//----------------------------------------------------------------------------------------------------------------------
TimeSpan toTimeSpan(const SGregorianDate::Components& gregorianDateComponents)
//----------------------------------------------------------------------------------------------------------------------
{
		return std::chrono::duration_cast<TimeSpan>(
			std::chrono::hours(gregorianDateComponents.getHour().getValue(0)) +
					std::chrono::minutes(gregorianDateComponents.getMinute().getValue(0)) +
					std::chrono::seconds((int64_t) gregorianDateComponents.getSecond().getValue(0.0)));
}
