#include<Windows.h>
#include<iostream>

using namespace std;
int main()
{
	cout << "// Named pipe server  " << endl;
	//named pipe local variable
	HANDLE hCreateFile;
	bool bwritefile;
	char writefile[1024] ;
	DWORD writesize = sizeof(writefile);
	DWORD nobytewrite;


	//readfilelocal variable
	bool breadfile;
	char readfile[1024];
	DWORD readsize = sizeof(readfile);
	DWORD nobyteread;

	//Create file for pipe
	hCreateFile = CreateFile(TEXT("\\\\.\\pipe\\Pipe"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hCreateFile == INVALID_HANDLE_VALUE)
	{
		cout << "File creation faild" << GetLastError() << endl;
	}
	cout << "File created" << endl;
	//read file
	while(true){
	breadfile = ReadFile(
		hCreateFile,
		readfile,
		readsize, &nobyteread,
		NULL
	);
	if (breadfile == FALSE)
	{
		cout << "read file faield" << GetLastError() << endl;

	}
	cout << "read file succes" << endl;
	cout << "data reading from server ->" << readfile << endl;
	//disconnectnamepipe step6
	cout << "type command" << endl;
	cin >> writefile;
	//write file operation
	bwritefile = WriteFile(
		hCreateFile,
		writefile,
		writesize, &nobytewrite,
		NULL
	);
	if (bwritefile == FALSE)
	{
		cout << "write file faield" << GetLastError() << endl;

	}
	cout << "write file succes" << endl;
}
	CloseHandle(hCreateFile);
	system("PAUSE");
	return 0;

}