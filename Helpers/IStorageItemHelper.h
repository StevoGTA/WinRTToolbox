//----------------------------------------------------------------------------------------------------------------------
//	IStorageItemHelper.h			©2021 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "SFoldersFiles.h"

#include "winrt\Windows.Foundation.Collections.h"
#include "winrt\Windows.Storage.h"

using namespace winrt;

//----------------------------------------------------------------------------------------------------------------------
// MARK: IStorageItemHelper

class IStorageItemHelper {
	// Methods
	public:
		// Class methods
		static	SFoldersFiles	getFoldersFiles(
										const Windows::Foundation::Collections::IVectorView<
												Windows::Storage::IStorageItem>& storageItems);
};
