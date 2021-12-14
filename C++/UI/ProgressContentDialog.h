//----------------------------------------------------------------------------------------------------------------------
//	ProgressContentDialog.h			©2021 Monkey Tools, LLC		All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "CProgress.h"

#undef Delete
#include "winrt/Windows.UI.Xaml.Controls.h"
#define Delete(x)	{ delete x; x = nil; }

using namespace winrt::Windows::UI::Xaml::Controls;

//----------------------------------------------------------------------------------------------------------------------
// MARK: ProgressContentDialog

class ProgressContentDialog : public ContentDialog {
	// Types
	typedef	void*	(*Proc)(CProgress& progress, void* userData);
	typedef	void	(*CancelProc)(void* userData);
	typedef	void	(*CompletionProc)(void* result, void* userData);

	// Methods
	public:
				// Lifecycle methods
				ProgressContentDialog();

				// Instance methods
		void	perform(Proc proc, CancelProc cancelProc, CompletionProc completionProc, void* userData);
};
