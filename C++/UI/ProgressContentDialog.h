//----------------------------------------------------------------------------------------------------------------------
//	ProgressContentDialog.h			©2021 Stevo Brock		All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "CProgress.h"

#include <functional>	// May only be needed in VS2019

#undef Delete

#include "winrt/Microsoft.UI.Xaml.Controls.h"

#define Delete(x)	{ delete x; x = nil; }

using namespace winrt::Microsoft::UI::Xaml::Controls;

//----------------------------------------------------------------------------------------------------------------------
// MARK: ProgressContentDialog

class ProgressContentDialogInternals;
class ProgressContentDialog : public ContentDialog {
	// Types
	typedef	std::function<void*(const I<CProgress>& progress)>	Proc;
	typedef	std::function<void()>								CancelProc;
	typedef	std::function<void(void* result)>					CompletionProc;

	// Methods
	public:
								// Lifecycle methods
								ProgressContentDialog();
								~ProgressContentDialog();

								// Instance methods
		CProgress::UpdateInfo	getProgressUpdateInfo() const;
		void					perform(const I<CProgress>& progress, Proc proc, CancelProc cancelProc,
										CompletionProc completionProc);

	// Properties
	private:
		ProgressContentDialogInternals*	mInternals;
};
