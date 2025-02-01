//----------------------------------------------------------------------------------------------------------------------
//	TInspectable.h			©2023 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "winrt\Windows.Foundation.h"

using namespace winrt;

//----------------------------------------------------------------------------------------------------------------------
// MARK: TVInspectable (Value Inspectable)

template <typename T, typename V> struct TVInspectable : public implements<T, Windows::Foundation::IInspectable> {
	// Methods
	public:
			// Lifecycle methods
			TVInspectable<T, V>(const V& v) : implements<T, Windows::Foundation::IInspectable>(), mV(v) {}

			// Instance methods
		V	GetValue() const
				{ return mV; }

	// Properties
	private:
		V	mV;
};

//----------------------------------------------------------------------------------------------------------------------
// MARK: TCVInspectable (const Value Inspectable)

template <typename T, typename V> struct TCVInspectable : public implements<T, Windows::Foundation::IInspectable> {
	// Methods
	public:
					// Lifecycle methods
					TCVInspectable<T, V>(const V& v) : implements<T, Windows::Foundation::IInspectable>(), mV(v) {}

					// Instance methods
		const	V	GetValue() const
						{ return mV; }

	// Properties
	private:
		V	mV;
};

//----------------------------------------------------------------------------------------------------------------------
// MARK: - TRInspectable (Reference Inspectable)

template <typename T, typename R> struct TRInspectable : public implements<T, Windows::Foundation::IInspectable> {
	// Methods
	public:
			// Lifecycle methods
			TRInspectable<T, R>(R& r) : implements<T, Windows::Foundation::IInspectable>(), mR(r) {}

			// Instance methods
		R&	GetReference() const
				{ return mR; }

	// Properties
	private:
		R&	mR;
};

//----------------------------------------------------------------------------------------------------------------------
// MARK: - TCRInspectable (const Reference Inspectable)

template <typename T, typename R> struct TCRInspectable : public implements<T, Windows::Foundation::IInspectable> {
	// Methods
	public:
					// Lifecycle methods
					TCRInspectable<T, R>(const R& r) : implements<T, Windows::Foundation::IInspectable>(), mR(r) {}

					// Instance methods
		const	R&	GetReference() const
						{ return mR; }

	// Properties
	private:
		const	R&	mR;
};
