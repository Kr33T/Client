#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 512

int main()
{
	system("chcp 1251 > nul");
	LPSTR lpszPipeName = "\\\\.\\pipe\\Canal";
	BOOL flag = TRUE;
	DWORD size_buf = SIZE_BUFFER; // размер буффера для записи
	DWORD actual_read_bite; // размер реально записано байт;
	DWORD actual_write_bite; // размер реально записано байт;
	LPSTR buffer;
	BOOL SuccesRead;
	while (TRUE) {

		char message_user[SIZE_BUFFER];
		HANDLE hNamedPipe = CreateFileA(lpszPipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		DWORD dMode = PIPE_READMODE_MESSAGE;
		BOOL isConnected = SetNamedPipeHandleState(hNamedPipe, &dMode, NULL, NULL);
		if (!isConnected) {
			printf("Сервер временно недоступен\n");
			flag = TRUE;
		}
		else 
		{
			if (flag) 
			{
				printf("Соединение с сервером установлено успешно!");
				Sleep(1000);
				system("cls");
				printf("\nВведите число, которое хотите возвести в квадрат ");
				gets(message_user);
				buffer = &message_user;
				WriteFile(hNamedPipe, buffer, size_buf, &actual_write_bite, NULL);
				flag = FALSE;
			}
			buffer = (CHAR*)calloc(size_buf, sizeof(CHAR));
			SuccesRead = ReadFile(hNamedPipe, buffer, SIZE_BUFFER, &actual_read_bite, NULL);
			if (SuccesRead)
			{
				printf("Ответ: ");
				printf(buffer);
				printf("\n");
				flag = TRUE;
			}
		}
		Sleep(1000);
		CloseHandle(hNamedPipe);
	}
}