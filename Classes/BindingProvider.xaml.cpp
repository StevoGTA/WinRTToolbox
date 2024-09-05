//----------------------------------------------------------------------------------------------------------------------
//	BindingProvider.xaml.cpp			©2024 Stevo Brock		All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#include "BindingProvider.xaml.h"

#if __has_include("WinRTToolbox.BindingProvider.g.cpp")
	#include "WinRTToolbox.BindingProvider.g.cpp"
#endif

using namespace winrt::WinRTToolbox::implementation;

using hstring = winrt::hstring;

//----------------------------------------------------------------------------------------------------------------------
// MARK: BindingProvider::Internals

class BindingProvider::Internals {
	public:
		Internals(const I<BindingProviderAdapter>& bindingProviderAdapter) :
			mBindingProviderAdapter(bindingProviderAdapter)
			{}

		I<BindingProviderAdapter>			mBindingProviderAdapter;

		event<PropertyChangedEventHandler>	mPropertyChangedEvent;
};

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// MARK: BindingProvider

// MARK: Lifecycle methods

//----------------------------------------------------------------------------------------------------------------------
BindingProvider::BindingProvider(const IInspectable& bindingProviderAdapter)
//----------------------------------------------------------------------------------------------------------------------
{
	mInternals = new Internals(bindingProviderAdapter.as<BindingProviderAdapterCVInspectable>()->GetValue());
}

//----------------------------------------------------------------------------------------------------------------------
BindingProvider::~BindingProvider()
//----------------------------------------------------------------------------------------------------------------------
{
	delete mInternals;
}

// MARK: Instance methods

//----------------------------------------------------------------------------------------------------------------------
bool BindingProvider::Boolean1() const
//----------------------------------------------------------------------------------------------------------------------
{
	return mInternals->mBindingProviderAdapter->getBool1();
}

//----------------------------------------------------------------------------------------------------------------------
void BindingProvider::Boolean1(bool value)
//----------------------------------------------------------------------------------------------------------------------
{
	mInternals->mBindingProviderAdapter->setBool1(value);
}

//----------------------------------------------------------------------------------------------------------------------
hstring BindingProvider::String1() const
//----------------------------------------------------------------------------------------------------------------------
{
	return mInternals->mBindingProviderAdapter->getString1();
}

//----------------------------------------------------------------------------------------------------------------------
void BindingProvider::String1(hstring value)
//----------------------------------------------------------------------------------------------------------------------
{
	mInternals->mBindingProviderAdapter->setString1(value);
}

// MARK: Event methods

//----------------------------------------------------------------------------------------------------------------------
event_token BindingProvider::PropertyChanged(const PropertyChangedEventHandler& handler)
//----------------------------------------------------------------------------------------------------------------------
{
	return mInternals->mPropertyChangedEvent.add(handler);
}

//----------------------------------------------------------------------------------------------------------------------
void BindingProvider::PropertyChanged(const event_token& token) noexcept
//----------------------------------------------------------------------------------------------------------------------
{
	mInternals->mPropertyChangedEvent.remove(token);
}
