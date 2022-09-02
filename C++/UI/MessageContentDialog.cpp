//----------------------------------------------------------------------------------------------------------------------
//	MessageContentDialog.cpp			©2022 Stevo Brock		All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#include "MessageContentDialog.h"

#include <winrt/Windows.Foundation.h>
//#include <winrt/Windows.Foundation.Collections.h>
//#include <winrt/Windows.System.Threading.h>
//#include <winrt/Windows.System.Threading.Core.h>
//#include <winrt/Windows.UI.Core.h>
//#include <winrt/Windows.UI.Xaml.h>
//#include <winrt/Windows.UI.Xaml.Controls.h>
//#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>

using namespace winrt;
//using namespace winrt::Windows::Foundation;
//using namespace winrt::Windows::System::Threading;
//using namespace winrt::Windows::UI::Core;
//using namespace winrt::Windows::UI::Xaml;
//using namespace winrt::Windows::UI::Xaml::Controls;

/*
	See https://stackoverflow.com/questions/54209679/c-winrt-xaml-contentdialog-example for example of waiting on ShowAsync();
*/

//----------------------------------------------------------------------------------------------------------------------
// MARK: Local proc definitions

//----------------------------------------------------------------------------------------------------------------------
static CString sApplyReplacements(const CString& string)
//----------------------------------------------------------------------------------------------------------------------
{
	return string.replacingSubStrings(CString(OSSTR("{APPLICATIONNAME}")), MessageContentDialog::mApplicationName);
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// MARK: - MessageContentDialog

// MARK: Lifecycle methods

//----------------------------------------------------------------------------------------------------------------------
MessageContentDialog::MessageContentDialog(const CString& title, const CString& message, const CString& buttonLabel,
		const ButtonProc& buttonProc) : ContentDialog()
//----------------------------------------------------------------------------------------------------------------------
{
	// Setup UI
	Title(box_value(sApplyReplacements(title).getOSString()));
	Content(box_value(sApplyReplacements(message).getOSString()));

	PrimaryButtonText(buttonLabel.getOSString());
	PrimaryButtonClick(
			[buttonProc](const ContentDialog& contentDialog, const ContentDialogButtonClickEventArgs& eventArgs) {
				// Call proc
				buttonProc();
			});
}

//----------------------------------------------------------------------------------------------------------------------
MessageContentDialog::MessageContentDialog(const CString& title, const CString& message,
		const CString& primaryButtonLabel, const ButtonProc& primaryButtonProc, const CString& secondaryButtonLabel,
		const ButtonProc& secondaryButtonProc) : ContentDialog()
//----------------------------------------------------------------------------------------------------------------------
{
	// Setup UI
	Title(box_value(sApplyReplacements(title).getOSString()));
	Content(box_value(sApplyReplacements(message).getOSString()));

	PrimaryButtonText(primaryButtonLabel.getOSString());
	PrimaryButtonClick(
			[primaryButtonProc](const ContentDialog& contentDialog,
					const ContentDialogButtonClickEventArgs& eventArgs) {
				// Call proc
				primaryButtonProc();
			});

	SecondaryButtonText(secondaryButtonLabel.getOSString());
	SecondaryButtonClick(
			[secondaryButtonProc](const ContentDialog& contentDialog,
					const ContentDialogButtonClickEventArgs& eventArgs) {
				// Call proc
				secondaryButtonProc();
			});
}

// MARK: Class methods

//----------------------------------------------------------------------------------------------------------------------
void MessageContentDialog::showAsync(const CString& title, const CString& message,
		const CString& buttonLabel, const ButtonProc& buttonProc)
//----------------------------------------------------------------------------------------------------------------------
{
	MessageContentDialog	messageContentDialog(title, message, buttonLabel, buttonProc);
	messageContentDialog.ShowAsync();
}

//----------------------------------------------------------------------------------------------------------------------
void MessageContentDialog::showAsync(const CString& title, const CString& message,
		const CString& primaryButtonLabel, const ButtonProc& primaryButtonProc, const CString& secondaryButtonLabel,
		const ButtonProc& secondaryButtonProc)
//----------------------------------------------------------------------------------------------------------------------
{
	MessageContentDialog	messageContentDialog(title, message, primaryButtonLabel, primaryButtonProc,
									secondaryButtonLabel, secondaryButtonProc);
	messageContentDialog.ShowAsync();
}
