//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ReadThread.h"
#include "Signatures.h"
#include "sqlite3.h"
#include <windows.h>
#include <iostream>
#include <string.h>
#include "Iterator.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ReadThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

bool Decorator(BYTE* Content){
	if (Content[0] == 0x00) {
		return false;
	}
	return true;
}

__fastcall ReadThread::ReadThread(bool CreateSuspended, AbstractFS* FS, bool EnableDec, sqlite3* Database)
	: TThread(CreateSuspended), FS(FS), EnableDec(EnableDec), Database(Database)
{
	 FreeOnTerminate = true;
	 Iter = new Iterator(FS);

}
//---------------------------------------------------------------------------
void __fastcall ReadThread::Execute()
{
     for(Iter->first();(!Iter->IsDone());Iter->next())
	 {
		if(Terminated){
            break;
		}
		Content = Iter ->GetClusterContent();
		if(EnableDec){
			bool Dec = Decorator(Content);
			if (!Dec) {
				continue;
			}
		}
		int sign = SignatureSearch(Content);
		if (sign != -1) {
			sqlite3_stmt* pStatement;
            std::wstring delrow = L"INSERT INTO Clusters (ClusterNumber, Signature) VALUES (" + std::to_wstring(Iter->GetClusterNumber());
			switch (sign) {
				case 0:
				delrow += L",\"jpeg\");";
				break;
				case 1:
				delrow += L",\"png\");";
				break;
				case 2:
				delrow += L",\"zip\");";
				break;
				case 3:
				delrow += L",\"rar\");";
				break;
				case 4:
				delrow += L",\"gzip\");";
				break;
				case 5:
                delrow += L",\"zip7\");";
				break;
			}
			const wchar_t* sql = delrow.c_str();
			int result = sqlite3_prepare16_v2(Database, sql, -1, &pStatement, NULL);
			if (result != SQLITE_OK) {
				Application->MessageBox(L"Error on Insert into!",L"Message", MB_OK);
			}else{
				result = sqlite3_step(pStatement);
				if(result != SQLITE_DONE)
				{
					Application->MessageBox(L"Error on update table!",L"Message", MB_OK);
				}
			}
   			sqlite3_finalize(pStatement);
		}

	 }
}
//---------------------------------------------------------------------------
