//----------------------------------------------------------------------------------------------------------------------
//	MessageContentDialog.h			©2022 Stevo Brock		All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "CString.h"

#undef Delete

#include "winrt/Windows.UI.Xaml.Controls.h"

#define Delete(x)	{ delete x; x = nil; }

using namespace winrt::Windows::UI::Xaml::Controls;

//----------------------------------------------------------------------------------------------------------------------
// MARK: MessageContentDialog

class MessageContentDialogInternals;
class MessageContentDialog : public ContentDialog {
	// Types

	// Methods
	public:
						// Lifecycle methods
						MessageContentDialog(const CString& title, const CString& message, const CString& buttonLabel);
						~MessageContentDialog();

						// Class methods
		static	void	showAsync(const CString& title, const CString& message, const CString& buttonLabel);

	// Properties
	public:
		static	const	CString							mApplicationName;

	private:
						MessageContentDialogInternals*	mInternals;
};
