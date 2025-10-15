//----------------------------------------------------------------------------------------------------------------------
//	CData+Extensions.h			©2025 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "CData.h"
#include "TInspectable.h"

DEFINE_TCVInspectable(DataCVInspectable, CData);
DEFINE_TCVInspectable(OVDataCVInspectable, OV<CData>);
