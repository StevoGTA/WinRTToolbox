//----------------------------------------------------------------------------------------------------------------------
//	CColor+Extensions.h			©2026 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "CColor.h"
#include "TInspectable.h"

#include "winrt\Windows.UI.h"

#include <cmath>

//----------------------------------------------------------------------------------------------------------------------
// MARK: CColorEx

class CColorEx {
	// Methods
	public:
											// Class methods
		static	winrt::Windows::UI::Color	toColor(const CColor& color)
												{
													// Setup
													const	CColor::RGBValues&			rgbValues =
																								color.getRGBValues();
															winrt::Windows::UI::Color	color_{};
													color_.R = (uint8_t) std::lround(rgbValues.getRed() * 255.0f);
													color_.G = (uint8_t) std::lround(rgbValues.getGreen() * 255.0f);
													color_.B = (uint8_t) std::lround(rgbValues.getBlue() * 255.0f);
													color_.A = (uint8_t) std::lround(rgbValues.getAlpha() * 255.0f);

													return color_;
												}
};
