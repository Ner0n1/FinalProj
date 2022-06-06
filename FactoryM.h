//---------------------------------------------------------------------------

#ifndef FactoryMH
#define FactoryMH
//---------------------------------------------------------------------------
// NTFS
  #pragma pack(push,1)
  typedef struct{
	BYTE skip1[3];
	char OEM_Name[8];
	USHORT BytesPerSector;
	BYTE SectorsPerCluster;
	BYTE skip2[10];
	UINT16 SectorsPerTrack;
	UINT16 NumberOfHeads;
	BYTE skip3[12];
	ULONGLONG TotalSectors;
	ULONGLONG MFTClusterNumber;
	ULONGLONG CopyMFTClusterNumber;
	UINT MFTSize;
	UINT BufferSize;
	BYTE skip4[3];
	ULONGLONG VolumeSerialNumber;
    USHORT Checksum;
  } NTFS_BootRecord;

// FAT32
  typedef struct{
	BYTE skip1[3];
	char OEM_Name[8];
	USHORT BytesPerSector;
	BYTE SectorsPerCluster;
	BYTE FATTables;
	USHORT RootEntries;
	USHORT SmallSectors;
	BYTE MediaTyoe;
	USHORT FATTableSectors;
	USHORT SectorsPerTrack;
	USHORT NumberOfHeads;
	BYTE skip2[4];
	ULONG LargeSectors;
	BYTE PhysicalDiskNumber;
	BYTE skip3;
	BYTE Signature;
	BYTE VolumeSerialNumber[4];
	BYTE VolumeLabel[11];
	ULONGLONG SystemID;
  } FAT32_BootRecord;

  typedef struct {
	  BYTE skip[3];
      char OEM[8];
  } Abstract_FS;


class AbstractFS
{
	protected:
        HANDLE DiskHandle;
		unsigned long BytesPerSector;
		unsigned long BytesPerCluster;
		unsigned long SectorsPerCluster;
		unsigned long TotalClusters;
		const wchar_t* OEM;
	public:
		HANDLE GetDiskHandle();
		unsigned long GetBytesPerSector();
		unsigned long GetBytesPerCluster();
		unsigned long GetSectorsPerCluster();
		unsigned long GetTotalClusters();
		const wchar_t* GetOEM();
		AbstractFS(const wchar_t* target);

};

class FAT32: public AbstractFS{
	public:
		FAT32(const wchar_t* target);
};
class NTFS: public AbstractFS{
	public:
		NTFS(const wchar_t* target);
};

AbstractFS*  FactoryFS(const wchar_t* target);
#endif
