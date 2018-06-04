#include<Windows.h>
#include<iostream>
#include<string>
void function1(char *write)
{
	char str[50]="hello from function 1";
	for (int i = 0; i < 50; ++i) {
		write[i] = str[i];
	}
}
using namespace std;
int main()
{
	cout << "// Named pipe server  " << endl;
	//named pipe local variable
	HANDLE hCreateNamedPipe;
	char inputbuffer[1023];
	char outputbuffer[1023];
	DWORD sinputbuffer = sizeof(inputbuffer);
	DWORD soutputbuffer = sizeof(outputbuffer);
	//connnect name pipe to local variable
	bool bconnectnamepipe;
		//write file local variable
	bool bwritefile;
	char writefile[1024] = " hello from server side type:menu";
	DWORD writesize = sizeof(writefile);
	DWORD nobytewrite;

	//flush buffer
	bool bflushbuffer;
	//readfilelocal variable
	bool breadfile;
	char readfile[1024];
	DWORD readsize = sizeof(readfile);
	DWORD nobyteread;

	//create name pipe
	hCreateNamedPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipe"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
		1,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);
	if (hCreateNamedPipe == INVALID_HANDLE_VALUE)
	{
		cout << "Named pipe creation faild" << GetLastError() << endl;
	}
	cout << "Named pipe created"  << endl;
	//connect name pipe
	bconnectnamepipe = ConnectNamedPipe(hCreateNamedPipe, NULL);
	if (bconnectnamepipe == FALSE)
	{
		cout << "connection failed" << GetLastError() << endl;
	}
	cout << "connection success" << endl;
	while (true) {
		//write file operation
		bwritefile = WriteFile(
			hCreateNamedPipe,
			writefile,
			writesize, &nobytewrite,
			NULL
		);
		if (bwritefile == FALSE)
		{
			cout << "write file faield" << GetLastError() << endl;

		}
		cout << "write file succes" << endl;
		//flush file buffer
		bflushbuffer = FlushFileBuffers(
			hCreateNamedPipe
		);
		if (bflushbuffer == FALSE)
		{
			cout << "flush buffer error" << endl;
		}
		cout << "flush buffer success" << endl;
		//readfile step5
		breadfile = ReadFile(
			hCreateNamedPipe,
			readfile,
			readsize, &nobyteread,
			NULL
		);
		if (breadfile == FALSE)
		{
			cout << "read file faield" << GetLastError() << endl;

		}
		cout << "read file succes" << endl;
		cout << "data reading from client ->" << readfile << endl;
		if (strcmp(readfile, "close") == 0)
		{
			break;
		}
		else
		{
			
			if (strcmp(readfile, "function1") == 0) 
			{
				function1(writefile);
			}
			if (strcmp(readfile, "menu") == 0)
			{
				char write[140] = "type:menu|close|function1";
				for (int i = 0; i < 50; ++i) {
					writefile[i] = write[i];
				}
			}
			
		}
	}
	//disconnectnamepipe step6
	DisconnectNamedPipe(hCreateNamedPipe);
	//close handle step 7
	CloseHandle(hCreateNamedPipe);
	system("PAUSE");
	return 0;
}