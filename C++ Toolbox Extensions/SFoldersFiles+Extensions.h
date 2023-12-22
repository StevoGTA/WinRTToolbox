//----------------------------------------------------------------------------------------------------------------------
//	SFoldersFiles+Extensions.h			©2021 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "SFoldersFiles.h"
#include "TInspectable.h"

#include "winrt\Windows.Foundation.Collections.h"
#include "winrt\Windows.Storage.h"

using IStorageItem = winrt::Windows::Storage::IStorageItem;
using IStorageItemVectorView = winrt::Windows::Foundation::Collections::IVectorView<IStorageItem>;

//----------------------------------------------------------------------------------------------------------------------
// MARK: SFoldersFilexEx

class SFoldersFilexEx {
	// Methods
	public:
								// Class methods
		static	SFoldersFiles	getFoldersFiles(const IStorageItemVectorView& storageItems);
};

//----------------------------------------------------------------------------------------------------------------------
// MARK: - FoldersFilesVInspectable

struct FoldersFilesVInspectable : public TVInspectable<FoldersFilesVInspectable, SFoldersFiles> {
	// Methods
	public:
		// Lifecycle methods
		FoldersFilesVInspectable(const SFoldersFiles& value) :
			TVInspectable<FoldersFilesVInspectable, SFoldersFiles>(value)
			{}
};
