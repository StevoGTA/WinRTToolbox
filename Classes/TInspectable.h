//----------------------------------------------------------------------------------------------------------------------
//	TInspectable.h			©2023 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "winrt\Windows.Foundation.h"

using namespace winrt;

//----------------------------------------------------------------------------------------------------------------------
// MARK: TVInspectable

template <typename T, typename D> struct TVInspectable : public implements<T, Windows::Foundation::IInspectable> {
	// Methods
	public:
			// Lifecycle methods
			TVInspectable<T, D>(D d) : implements<T, Windows::Foundation::IInspectable>(), mD(d) {}

			// Instance methods
		D	GetValue() const
				{ return mD; }

	// Properties
	private:
		D	mD;
};

//----------------------------------------------------------------------------------------------------------------------
// MARK: - TRInspectable

template <typename T, typename D> struct TRInspectable : public implements<T, Windows::Foundation::IInspectable> {
	// Methods
	public:
			// Lifecycle methods
			TRInspectable<T, D>(D& d) : implements<T, Windows::Foundation::IInspectable>(), mD(d) {}

			// Instance methods
		D&	GetValue() const
				{ return mD; }

	// Properties
	private:
		D&	mD;
};

//----------------------------------------------------------------------------------------------------------------------
// MARK: - TCRInspectable

template <typename T, typename D> struct TCRInspectable : public implements<T, Windows::Foundation::IInspectable> {
	// Methods
	public:
					// Lifecycle methods
					TCRInspectable<T, D>(const D& d) : implements<T, Windows::Foundation::IInspectable>(), mD(d) {}

					// Instance methods
		const	D&	GetValue() const
						{ return mD; }

	// Properties
	private:
		const	D&	mD;
};
