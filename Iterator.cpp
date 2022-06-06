//---------------------------------------------------------------------------
#include <windows.h>
#include <iostream>
#include <string.h>
#pragma hdrstop

#include "Iterator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
Iterator::Iterator(AbstractFS* FS)
	:ClusterNumber(0), ClustersTotal(FS->GetTotalClusters()), Done(false), FS(FS)
{
    ClusterContent = new BYTE[FS->GetBytesPerCluster()];
}
void Iterator::first(){
    	ClusterNumber = 0;
}
void Iterator::next(){
    ClusterNumber++;
}
bool Iterator::IsDone(){
    return Done;
}
bool Iterator::ForceDone(){
	Done = true;
    return Done;
}
unsigned long Iterator::GetClusterNumber(){
	return ClusterNumber;
}

BYTE* Iterator::GetClusterContent(){
	DWORD BytesRead;
	LARGE_INTEGER Offset;
	Offset.QuadPart = ClusterNumber*FS->GetBytesPerCluster();

	unsigned long Pointer = SetFilePointer(FS->GetDiskHandle(), Offset.LowPart, &Offset.HighPart, FILE_BEGIN);
	if (Pointer != Offset.LowPart) {
	   Application->MessageBox(L"[ITERATOR]Error while trying set position!",L"Message", MB_OK);
       return ClusterContent;
	}

	bool ReadCluster = ReadFile(FS->GetDiskHandle(), ClusterContent, FS->GetBytesPerCluster(), &BytesRead, NULL);
	if (ReadCluster == false || BytesRead != FS->GetBytesPerCluster()){
		Application -> MessageBox(L"[ITERATOR]Error while trying to read cluster!", L"Message",MB_OK);
	}
	return ClusterContent;
}