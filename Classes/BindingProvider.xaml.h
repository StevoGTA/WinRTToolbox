//----------------------------------------------------------------------------------------------------------------------
//	BindingProvider.xaml.h			©2024 Stevo Brock		All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "WinRTToolbox.BindingProvider.g.h"
#include "TInspectable.h"
#include "TWrappers.h"

using PropertyChangedEventHandler = winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler;

//----------------------------------------------------------------------------------------------------------------------
// MARK: winrt::WinRTToolbox

namespace winrt::WinRTToolbox {

	// MARK: BindingProviderAdapter
	class BindingProviderAdapter {
		// Methods
		public:
							// Lifecycle methods
							BindingProviderAdapter() {}
			virtual			~BindingProviderAdapter() {}

							// Instance methods
			virtual	bool	getBool1() const { return false; }
			virtual	void	setBool1(bool value) {}

			virtual	hstring	getString1() const { return L""; }
			virtual	void	setString1(hstring value) {}
	};

	DEFINE_TCVInspectable(BindingProviderAdapterCVInspectable, I<BindingProviderAdapter>);
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// MARK: winrt::WinRTToolbox::implementation

namespace winrt::WinRTToolbox::implementation {

	// MARK: BindingProvider
	struct BindingProvider : BindingProviderT<BindingProvider> {
		// Classes
		private:
			class Internals;

		// Methods
		public:
						// Lifecycle Methods
						BindingProvider(const IInspectable& bindingProviderAdapter);
						~BindingProvider();

						// Instance methods
			bool		Boolean1() const;
			void		Boolean1(bool value);

			hstring		String1() const;
			void		String1(hstring value);

			event_token	PropertyChanged(const PropertyChangedEventHandler& handler);
			void		PropertyChanged(const event_token& token) noexcept;

		// Properties
		private:
			Internals*	mInternals;
	};
}

//----------------------------------------------------------------------------------------------------------------------
// MARK: - winrt::WinRTToolbox::factory_implementation

namespace winrt::WinRTToolbox::factory_implementation {

	// MARK: BindingProvider
	struct BindingProvider : BindingProviderT<BindingProvider, implementation::BindingProvider> {};
}
