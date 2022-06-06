//---------------------------------------------------------------------------

#pragma hdrstop

#include "FactoryM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

AbstractFS::AbstractFS(const wchar_t* target){
	DiskHandle = CreateFileW(target, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0,NULL);
}

NTFS::NTFS(const wchar_t* target) :AbstractFS(target){
	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = 0;

	unsigned long SectorBegin = SetFilePointer(DiskHandle, offset.LowPart, &offset.HighPart, FILE_BEGIN);
	if (SectorBegin != offset.LowPart) {
	   Application->MessageBox(L"[FAT32]Error while trying set position in file!",L"Message", MB_OK);
	   CloseHandle(DiskHandle);
	}

	bool ReadSector = ReadFile(DiskHandle, Block, bytes, &bytesRead, NULL);
	if (ReadSector == false || bytesRead != bytes){
		Application -> MessageBox(L"[FAT32]Error while trying to read block!", L"Message",MB_OK);
		CloseHandle(DiskHandle);
	}
	NTFS_BootRecord *ptrNTFS_BootRecord = (NTFS_BootRecord*)Block;
	BytesPerSector = ptrNTFS_BootRecord -> BytesPerSector;
	SectorsPerCluster = ptrNTFS_BootRecord -> SectorsPerCluster;
	BytesPerCluster =  BytesPerSector*SectorsPerCluster;
	OEM = L"NTFS";
	TotalClusters = (ptrNTFS_BootRecord -> TotalSectors)/SectorsPerCluster;
}

FAT32::FAT32(const wchar_t* target) : AbstractFS(target){

	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = 0;

	unsigned long SectorBegin = SetFilePointer(DiskHandle, offset.LowPart, &offset.HighPart, FILE_BEGIN);
	if (SectorBegin != offset.LowPart) {
	   Application->MessageBox(L"[FAT32]Error while trying set position!",L"Message", MB_OK);
	   CloseHandle(DiskHandle);
	}

	bool ReadSector = ReadFile(DiskHandle, Block, bytes, &bytesRead, NULL);
	if (ReadSector == false || bytesRead != bytes){
		Application -> MessageBox(L"[FAT32]Error while trying to read block!", L"Message",MB_OK);
		CloseHandle(DiskHandle);
	}

	FAT32_BootRecord *ptrFAT32_BootRecord = (FAT32_BootRecord*)Block;
	BytesPerSector = ptrFAT32_BootRecord -> BytesPerSector;
	SectorsPerCluster = ptrFAT32_BootRecord -> SectorsPerCluster;
	BytesPerCluster =  BytesPerSector*SectorsPerCluster;
	OEM = L"FAT32";
	if (ptrFAT32_BootRecord->LargeSectors != 0) {
		 TotalClusters = (ptrFAT32_BootRecord->LargeSectors)/SectorsPerCluster;
	}else{
		 TotalClusters = (ptrFAT32_BootRecord->SmallSectors)/SectorsPerCluster;
	}
}



HANDLE AbstractFS::GetDiskHandle(){
	return DiskHandle;
}
unsigned long AbstractFS::GetBytesPerSector(){
	return BytesPerSector;
}
unsigned long AbstractFS::GetBytesPerCluster(){
	return BytesPerCluster;
}
unsigned long AbstractFS::GetSectorsPerCluster(){
	return SectorsPerCluster;
}
unsigned long AbstractFS::GetTotalClusters(){
	return TotalClusters;
}
const wchar_t* AbstractFS::GetOEM(){
	return OEM;
}

AbstractFS* FactoryFS(const wchar_t* target){
	DWORD bytesRead;
	DWORD bytes = 512;
	BYTE Block[512];
	LARGE_INTEGER offset;
	offset.QuadPart = 0;
    AbstractFS* FS;

	HANDLE DiskHandle = CreateFileW(target, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0,NULL);

	if (DiskHandle == INVALID_HANDLE_VALUE) {
	   CloseHandle(DiskHandle);
	   Application->MessageBox(L"Can't open disk! Please, enter disk name, like \"\\\\.\\E:\"",L"Message", MB_OK);
	}

	unsigned long SectorBegin = SetFilePointer(DiskHandle, offset.LowPart, &offset.HighPart, FILE_BEGIN);
	if (SectorBegin != offset.LowPart) {
	   Application->MessageBox(L"Error while trying set position in file!",L"Message", MB_OK);
	   CloseHandle(DiskHandle);
	}

	bool ReadSector = ReadFile(DiskHandle, Block, bytes, &bytesRead, NULL);
	if (ReadSector == false || bytesRead != bytes){
		Application -> MessageBox(L"Error while trying to read block!", L"Message",MB_OK);
		CloseHandle(DiskHandle);
	}
	Abstract_FS *ptrAbstract_FS = (Abstract_FS*)Block;
	CloseHandle(DiskHandle);

	if (strstr(ptrAbstract_FS ->OEM,"NTFS")) {
	   FS = new NTFS(target);
	}else if (strstr(ptrAbstract_FS -> OEM,"MSDOS5.0")) {
       FS = new FAT32(target);
	}else {
       Application -> MessageBox(L"Unknown FS Type!", L"Message",MB_OK);
	}
    return FS;

}


