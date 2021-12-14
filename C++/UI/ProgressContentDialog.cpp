//----------------------------------------------------------------------------------------------------------------------
//	ProgressContentDialog.cpp			©2021 Monkey Tools, LLC		All rights reserved.
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
// MARK: ProgressContentDialog

// MARK: Lifecycle methods

//----------------------------------------------------------------------------------------------------------------------
ProgressContentDialog::ProgressContentDialog() : ContentDialog()
//----------------------------------------------------------------------------------------------------------------------
{
}

// MARK: Instance methods

//----------------------------------------------------------------------------------------------------------------------
void ProgressContentDialog::perform(Proc proc, CancelProc cancelProc, CompletionProc completionProc, void* userData)
//----------------------------------------------------------------------------------------------------------------------
{
	// Setup
	bool	isCancelled = false;

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

	CloseButtonText(L"Cancel");
	CloseButtonClick([=, &isCancelled](const ContentDialog& contentDialog, const ContentDialogButtonClickEventArgs& eventArgs) {
		// Cancelled
		isCancelled = true;

		// Call cancel proc
		cancelProc(userData);
	});

	// Run
	auto	dispatcher = Dispatcher();
	ThreadPool::RunAsync([=, *this](IAsyncAction const& workItem) {
		// Setup
		struct Info {
			TextBlock		mMessageTextBlock;
			ProgressBar		mProgressBar;
			CoreDispatcher	mDispatcher;

			Info(const TextBlock& messageTextBlock, const ProgressBar& progressBar, const CoreDispatcher& dispatcher) :
				mMessageTextBlock(messageTextBlock), mProgressBar(progressBar), mDispatcher(dispatcher)
				{}
		};
		Info	info(messageTextBlock, progressBar, dispatcher);

		CProgress	progress(
							CProgress::UpdateInfo([](const CProgress& progress, void* userData) {
								// Setup
								const	Info&	info = *((Info*) userData);

								// Update UI
								info.mDispatcher.RunAsync(CoreDispatcherPriority::Normal, [=]() {
									// Update UI
									info.mMessageTextBlock.Text(progress.getMessage().getOSString());

									OV<Float32>	value = progress.getValue();
									info.mProgressBar.IsIndeterminate(!value.hasValue());
									info.mProgressBar.Value(value.hasValue() ? *value : 0.0);
								});
							}, &info));

		// Call proc
		void*	result = proc(progress, userData);

		// Switch to UI
		dispatcher.RunAsync(CoreDispatcherPriority::Normal, [=, *this, &isCancelled]() {
			// Hide
			this.Hide();

			// Check cancelled
			if (!isCancelled)
				// Call completion proc
				completionProc(result, userData);
		});
	});

	// Show
	ShowAsync();
}
