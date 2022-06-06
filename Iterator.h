//---------------------------------------------------------------------------
#include "Main.h"
#include "FactoryM.h"
#ifndef IteratorH
#define IteratorH
//---------------------------------------------------------------------------
class Iterator
{
	protected:
	   unsigned long ClusterNumber;
	   BYTE* ClusterContent;
	   unsigned long ClustersTotal;
	   bool Done;
	   AbstractFS* FS;
	public:
        Iterator(AbstractFS* FS);
		unsigned long GetClusterNumber();
		BYTE* GetClusterContent();
		bool IsDone();
        bool ForceDone();
		void first();
		void next();

};
#endif
