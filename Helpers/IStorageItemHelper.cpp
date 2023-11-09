//----------------------------------------------------------------------------------------------------------------------
//	IStorageItemHelper.cpp			©2021 Stevo Brock	All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#include "IStorageItemHelper.h"

using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Storage;

//----------------------------------------------------------------------------------------------------------------------
// MARK: IStorageItemHelper

// MARK: Class methods

//----------------------------------------------------------------------------------------------------------------------
SFoldersFiles IStorageItemHelper::getFoldersFiles(const IVectorView<IStorageItem>& storageItems)
//----------------------------------------------------------------------------------------------------------------------
{
	// Compose folders and files
	TNArray<CFolder>	folders;
	TNArray<CFile>		files;
	for (auto const& storageItem : storageItems) {
		// Check if directory
		if ((uint32_t) storageItem.Attributes() & (uint32_t) FileAttributes::Directory)
			// Folder
			folders += CFolder(CFilesystemPath(CString(storageItem.Path().data())));
		else
			// File
			files += CFile(CFilesystemPath(CString(storageItem.Path().data())));
	}

	return SFoldersFiles(folders, files);
}
