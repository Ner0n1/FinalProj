//---------------------------------------------------------------------------

#ifndef ReadThreadH
#define ReadThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "Main.h"
#include "FactoryM.h"
#include "sqlite3.h"
#include "Iterator.h"
//---------------------------------------------------------------------------

bool Decorator(BYTE* Content);


class ReadThread : public TThread
{
private:
protected:
	AbstractFS* FS;
	bool EnableDec;
	Iterator* Iter;
	void __fastcall Execute();
	BYTE* Content;
    sqlite3* Database;
public:
	AbstractFS* GetFS();
	bool GetEnableDec();
	__fastcall ReadThread(bool CreateSuspended, AbstractFS* FS, bool EnableDec, sqlite3* Database);
};
//---------------------------------------------------------------------------
#endif
