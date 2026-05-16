//----------------------------------------------------------------------------------------------------------------------
//	CDictionary+Extensions.h			©2026 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "CDictionary.h"
#include "TInspectable.h"

DEFINE_TCRInspectable(DictionaryCRInspectable, CDictionary);
DEFINE_TCVInspectable(DictionaryCVInspectable, CDictionary);
DEFINE_TCVInspectable(OVDictionaryCVInspectable, OV<CDictionary>);
