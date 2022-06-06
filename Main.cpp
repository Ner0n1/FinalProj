//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "FactoryM.h"
#include "sqlite3.h"
#include "ReadThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
const wchar_t* path = L"\\\\.\\C:";
sqlite3* Database;
AbstractFS* FS;
int id;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree1 -> NodeDataSize = sizeof(TreeNodeStruct);
	sqlite3_stmt *pStatement;
	int result = sqlite3_open16(L".\\ClusterDB.sqlite",&Database);
	if (result != SQLITE_OK) {
		Application->MessageBox(L"Table is broken!", MB_OK);
		Button1 -> Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	sqlite3_close(Database);
	Form1-> Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Button4 -> Enabled = true;
	bool DecState = CheckBox1 -> Checked;
	CheckBox1 -> Enabled = false;
	Button3 -> Enabled = false;
	Button5 -> Enabled = false;
	Button6-> Enabled = false;
	Button1 -> Enabled = false;
	Edit1 -> Enabled = false;
	ReadThreadPtr = new ReadThread(false, FS,DecState, Database);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	path = (Edit1->Text).c_str();
	FS = FactoryFS(path);

	Label7->Caption = UnicodeString(FS->GetOEM());
	Label8->Caption = UnicodeString(FS->GetBytesPerSector());
	Label9->Caption = UnicodeString(FS->GetSectorsPerCluster());
	Label10->Caption = UnicodeString(FS->GetBytesPerCluster());
	Label11->Caption = UnicodeString(FS->GetTotalClusters());
    Button3 -> Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTree1AddToSelection(TBaseVirtualTree *Sender,
          PVirtualNode Node)
{
    if (!Node) return;
	Button6 -> Enabled = True;
    TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1 -> GetNodeData(Node);
    id = nodeData -> ClusterNumber;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	sqlite3_stmt *pStatement;
	std::wstring delrow = L"DELETE FROM Clusters WHERE ClusterNumber = " + std::to_wstring(id) + L";";
	const wchar_t* sql = delrow.c_str();
	int result = sqlite3_prepare16_v2(Database, sql, -1, &pStatement, NULL);
	if(result != SQLITE_OK)
	{
		Application->MessageBox(L"Error in DELETE FROM DB WHERE ClusterNumber = !",L"ERROR", MB_OK);
		return;
	}
	result = sqlite3_step(pStatement);

	if(result != SQLITE_DONE)
	{
		Application->MessageBox(L"Error while delete!",L"ERROR", MB_OK);
		return;
	}
	sqlite3_finalize(pStatement);

	VirtualStringTree1 -> Clear();
	VirtualStringTree1 -> BeginUpdate();
	result = sqlite3_prepare16_v2(Database, L"SELECT * FROM Clusters ORDER BY ClusterNumber;", -1, &pStatement, NULL);
	while (true) {
		result = sqlite3_step(pStatement);
		if(result == SQLITE_DONE) break;
		else if (result == SQLITE_ROW) {
			PVirtualNode entryNode = VirtualStringTree1 -> AddChild(VirtualStringTree1 -> RootNode);
			TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1 -> GetNodeData(entryNode);
			nodeData -> ClusterNumber = sqlite3_column_int(pStatement,0);
			nodeData -> Signature = (UnicodeString)(char*)sqlite3_column_text(pStatement,1);
			}
		else {
			Application->MessageBox(L"Error in update table",L"ERROR", MB_OK);
			break;
		}

	}
	sqlite3_finalize(pStatement);
	VirtualStringTree1 -> EndUpdate();


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	VirtualStringTree1->Clear();
    sqlite3_stmt *pStatement;
	int result = sqlite3_prepare16_v2(Database, L"DELETE FROM Clusters;", -1, &pStatement, NULL);
	if (result != SQLITE_OK) {
		Application->MessageBox(L"Error while delete!",L"ERROR", MB_OK);
		return;
	}

	result = sqlite3_step(pStatement);
	if(result != SQLITE_DONE)
	{
		Application->MessageBox(L"Error while trying end delete!",L"ERROR", MB_OK);
		return;
	}
	sqlite3_finalize(pStatement);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	ReadThreadPtr -> Terminate();
	VirtualStringTree1 -> Clear();
	VirtualStringTree1 -> BeginUpdate();
	sqlite3_stmt *pStatement;
	int result = sqlite3_prepare16_v2(Database, L"SELECT * FROM Clusters ORDER BY ClusterNumber", -1, &pStatement, NULL);
	while (true) {
		result = sqlite3_step(pStatement);
		if(result == SQLITE_DONE) break;
		else if (result == SQLITE_ROW) {
			PVirtualNode entryNode = VirtualStringTree1 -> AddChild(VirtualStringTree1 -> RootNode);
			TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1 -> GetNodeData(entryNode);
			nodeData -> ClusterNumber = sqlite3_column_int(pStatement,0);
			nodeData -> Signature = (UnicodeString)(char*)sqlite3_column_text(pStatement,1);
			}
		else {
			Application->MessageBox(L"Error in update table!",L"ERROR", MB_OK);
			break;
		}

	}
	sqlite3_finalize(pStatement);
	VirtualStringTree1 -> EndUpdate();

	Button4 -> Enabled = false;
	CheckBox1 -> Enabled = true;
	Button3 -> Enabled = true;
	Button5 -> Enabled = true;
	Button1 -> Enabled = true;
	Edit1 -> Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if(!Node) return;
    TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1 -> GetNodeData(Node);

		switch (Column) {

			case 0:
			{
				CellText = UnicodeString(nodeData -> ClusterNumber);  break;
			}
			case 1:
			{
				CellText = nodeData -> Signature; break;
			}
        }
}
//---------------------------------------------------------------------------

