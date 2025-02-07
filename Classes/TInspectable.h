//----------------------------------------------------------------------------------------------------------------------
//	TInspectable.h			©2023 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "winrt\Windows.Foundation.h"

using namespace winrt;

//----------------------------------------------------------------------------------------------------------------------
// MARK: TCVInspectable (const Value Inspectable)

#define DEFINE_TCVInspectable(C, T)																		\
	struct C : public implements<C, Windows::Foundation::IInspectable> {								\
		public:																							\
						C(const T& v) : implements<C, Windows::Foundation::IInspectable>(), mV(v) {}	\
			const	T&	GetValue() const																\
							{ return mV; }																\
		private:																						\
			T	mV;																						\
	};

//----------------------------------------------------------------------------------------------------------------------
// MARK: - TRInspectable (Reference Inspectable)

#define DEFINE_TRInspectable(C, T)														\
	struct C : public implements<C, Windows::Foundation::IInspectable> {				\
		public:																			\
				C(T& r) : implements<C, Windows::Foundation::IInspectable>(), mR(r) {}	\
			T&	GetReference() const													\
					{ return mR; }														\
		private:																		\
			T&	mR;																		\
	};

//----------------------------------------------------------------------------------------------------------------------
// MARK: - TCRInspectable (const Reference Inspectable)

#define DEFINE_TCRInspectable(C, T)																		\
	struct C : public implements<C, Windows::Foundation::IInspectable> {								\
		public:																							\
						C(const T& r) : implements<C, Windows::Foundation::IInspectable>(), mR(r) {}	\
			const	T&	GetReference() const															\
							{ return mR; }																\
		private:																						\
			const	T&	mR;																				\
	};
