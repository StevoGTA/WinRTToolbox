//----------------------------------------------------------------------------------------------------------------------
//	ProgressContentDialog.h			©2021 Stevo Brock		All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "CProgress.h"

#undef Delete

#include "winrt/Windows.UI.Xaml.Controls.h"

#define Delete(x)	{ delete x; x = nil; }

using namespace winrt::Windows::UI::Xaml::Controls;

//----------------------------------------------------------------------------------------------------------------------
// MARK: ProgressContentDialog

class ProgressContentDialogInternals;
class ProgressContentDialog : public ContentDialog {
	// Types
// Would be super nice if these were Lambdas...
	typedef	void*	(*Proc)(const I<CProgress>& progress, void* userData);
	typedef	void	(*CancelProc)(void* userData);
	typedef	void	(*CompletionProc)(void* result, void* userData);

	// Methods
	public:
								// Lifecycle methods
								ProgressContentDialog();
								~ProgressContentDialog();

								// Instance methods
		CProgress::UpdateInfo	getProgressUpdateInfo() const;
		void					perform(const I<CProgress>& progress, Proc proc, CancelProc cancelProc,
										CompletionProc completionProc, void* userData);

	// Properties
	private:
		ProgressContentDialogInternals*	mInternals;
};
