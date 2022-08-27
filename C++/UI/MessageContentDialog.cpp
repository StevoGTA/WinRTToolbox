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
// MARK: MessageContentDialogInternals

//class MessageContentDialogInternals : public TCopyOnWriteReferenceCountable<MessageContentDialogInternals> {
//	public:
//		MessageContentDialogInternals(const TextBlock& messageTextBlock, const ProgressBar& progressBar,
//				const CoreDispatcher& dispatcher) :
//			mMessageTextBlock(messageTextBlock), mProgressBar(progressBar), mDispatcher(dispatcher)
//			{}
//
//		TextBlock		mMessageTextBlock;
//		ProgressBar		mProgressBar;
//		CoreDispatcher	mDispatcher;
//};

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// MARK: - MessageContentDialog

// MARK: Lifecycle methods

//----------------------------------------------------------------------------------------------------------------------
MessageContentDialog::MessageContentDialog(const CString& title, const CString& message, const CString& buttonLabel) :
		ContentDialog()
//----------------------------------------------------------------------------------------------------------------------
{
	// Setup UI
	Title(box_value(sApplyReplacements(title).getOSString()));
	Content(box_value(sApplyReplacements(message).getOSString()));
	PrimaryButtonText(buttonLabel.getOSString());

	// Setup internals
	//mInternals = new MessageContentDialogInternals(messageTextBlock, progressBar, Dispatcher());
}

//----------------------------------------------------------------------------------------------------------------------
MessageContentDialog::~MessageContentDialog()
//----------------------------------------------------------------------------------------------------------------------
{
	//mInternals->removeReference();
}

// MARK: Class methods

//----------------------------------------------------------------------------------------------------------------------
void MessageContentDialog::showAsync(const CString& title, const CString& message, const CString& buttonLabel)
//----------------------------------------------------------------------------------------------------------------------
{
	MessageContentDialog	messageContentDialog(title, message, buttonLabel);
	messageContentDialog.ShowAsync();
}
