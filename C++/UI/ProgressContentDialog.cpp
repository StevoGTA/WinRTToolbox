//----------------------------------------------------------------------------------------------------------------------
//	ProgressContentDialog.cpp			©2021 Stevo Brock		All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#include "ProgressContentDialog.h"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.System.Threading.h>
#include <winrt/Windows.System.Threading.Core.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::System::Threading;
using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// MARK: ProgressContentDialogInternals

class ProgressContentDialogInternals : public TCopyOnWriteReferenceCountable<ProgressContentDialogInternals> {
	public:
		ProgressContentDialogInternals(const TextBlock& messageTextBlock, const ProgressBar& progressBar,
				const CoreDispatcher& dispatcher) :
			mMessageTextBlock(messageTextBlock), mProgressBar(progressBar), mDispatcher(dispatcher)
			{}

		TextBlock		mMessageTextBlock;
		ProgressBar		mProgressBar;
		CoreDispatcher	mDispatcher;
};

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// MARK: - ProgressContentDialog

// MARK: Lifecycle methods

//----------------------------------------------------------------------------------------------------------------------
ProgressContentDialog::ProgressContentDialog() : ContentDialog()
//----------------------------------------------------------------------------------------------------------------------
{
	// Setup UI
	StackPanel	stackPanel;
	stackPanel.Orientation(Orientation::Vertical);

	TextBlock	messageTextBlock;
	messageTextBlock.Text(L"{MESSAGE}");
	messageTextBlock.TextAlignment(TextAlignment::Center);
	messageTextBlock.Margin(ThicknessHelper::FromLengths(10.0, 10.0, 10.0, 20.0));
	stackPanel.Children().Append(messageTextBlock);

	ProgressBar	progressBar;
	progressBar.Minimum(0.0);
	progressBar.Maximum(1.0);
	progressBar.Value(0.5);
	progressBar.IsIndeterminate(true);
	stackPanel.Children().Append(progressBar);

	Content(stackPanel);

	// Setup internals
	mInternals = new ProgressContentDialogInternals(messageTextBlock, progressBar, Dispatcher());
}

//----------------------------------------------------------------------------------------------------------------------
ProgressContentDialog::~ProgressContentDialog()
//----------------------------------------------------------------------------------------------------------------------
{
	mInternals->removeReference();
}

// MARK: Instance methods

//----------------------------------------------------------------------------------------------------------------------
CProgress::UpdateInfo ProgressContentDialog::getProgressUpdateInfo() const
//----------------------------------------------------------------------------------------------------------------------
{
	// Return update info
	return CProgress::UpdateInfo([](const CProgress& progress, void* userData) {
		// Setup
		const	ProgressContentDialogInternals&	internals = *((ProgressContentDialogInternals*) userData);

		// Update UI
		internals.mDispatcher.RunAsync(CoreDispatcherPriority::Normal, [=]() {
			// Update UI
			internals.mMessageTextBlock.Text(progress.getMessage().getOSString());

			const	OV<Float32>&	value = progress.getValue();
			internals.mProgressBar.IsIndeterminate(!value.hasValue());
			internals.mProgressBar.Value(value.hasValue() ? *value : 0.0);
		});
	}, mInternals);
}

//----------------------------------------------------------------------------------------------------------------------
void ProgressContentDialog::perform(const I<CProgress>& progress, Proc proc, CancelProc cancelProc,
		CompletionProc completionProc, void* userData)
//----------------------------------------------------------------------------------------------------------------------
{
	// Setup
	auto			internals = mInternals->addReference();
	bool			isCancelled = false;
	ContentDialog	progressContentDialog(*this);

	// Setup UI
	CloseButtonText(L"Cancel");
	CloseButtonClick([=, &isCancelled](const ContentDialog& contentDialog,
			const ContentDialogButtonClickEventArgs& eventArgs) {
		// Cancelled
		isCancelled = true;

		// Call cancel proc
		cancelProc(userData);
	});

	// Run
	ThreadPool::RunAsync([=, &isCancelled](IAsyncAction const& workItem) {
		// Call proc
		void*	result = proc(progress, userData);

		// Switch to UI
		bool	wasCancelled = isCancelled;
		internals->mDispatcher.RunAsync(CoreDispatcherPriority::Normal, [=, &wasCancelled]() {
			// Hide
			progressContentDialog.Hide();

			// Check cancelled
			if (!wasCancelled)
				// Call completion proc
				completionProc(result, userData);

			// Cleanup
			internals->removeReference();
		});
	});

	// Show
	ShowAsync();
}
