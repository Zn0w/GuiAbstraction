#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "window.h"

bool running;

//HMENU menu;		// A window's main menu (on the top of a screen)

int main()
{
	zn::Window test_window(500, 500, 400, 400, "Test Window");
	zn::Frame test_frame(new zn::SequenceLayout(zn::X_AXIS, 400, 400, 5, 5));
	test_window.setFrame(&test_frame);
	
	test_frame.addElement(zn::Element("Button1", 20, 15));
	test_frame.addElement(zn::Element("Button2", 20, 15));
	test_frame.addElement(zn::Element("Button3", 20, 15));
	test_frame.addElement(zn::Element("Button4", 20, 15));
	test_frame.addElement(zn::Element("Button5", 20, 15));

	for (int i = 0; i < test_frame.getElements()->size(); i++)
	{
		printf(
			"Element %s (%d, %d, %d, %d)\n",
			test_frame.getElement(i)->getContents(),
			test_frame.getElement(i)->getX(),
			test_frame.getElement(i)->getY(),
			test_frame.getElement(i)->getWidth(),
			test_frame.getElement(i)->getHeight()
		);
	}
	
	test_frame.allignElements();

	for (int i = 0; i < test_frame.getElements()->size(); i++)
	{
		printf(
			"Element %s (%d, %d, %d, %d)\n",
			test_frame.getElement(i)->getContents(),
			test_frame.getElement(i)->getX(),
			test_frame.getElement(i)->getY(),
			test_frame.getElement(i)->getWidth(),
			test_frame.getElement(i)->getHeight()
		);
	}

	system("pause");
}
#if 0
enum MenuItem
{
	MENU_FILE = 1,	// New, Open, Close, Save, Save As
	MENU_EDIT,		// Cut, Copy, Paste, Delete, Undo
	MENU_VIEW,		// Selection of menus
	MENU_DATABASE,	// Close, New, Open, Exit
	MENU_SETTINGS,	// Opens the settings window
	MENU_TOOLS,		// Opens tools window, or shows the selection of tools
	MENU_SCRIPTING,	// New Script, Openg Script, Run Script File
	MENU_HELP		// Opens a help window
};


void initWindow(HWND handle_window)
{
	HMENU menu = CreateMenu();
	AppendMenu(menu, MF_STRING, MENU_FILE, "File");
	AppendMenu(menu, MF_STRING, MENU_EDIT, "Edit");
	AppendMenu(menu, MF_STRING, MENU_VIEW, "View");
	AppendMenu(menu, MF_STRING, MENU_DATABASE, "Database");
	AppendMenu(menu, MF_STRING, MENU_SETTINGS, "Settings");
	AppendMenu(menu, MF_STRING, MENU_TOOLS, "Tools");
	AppendMenu(menu, MF_STRING, MENU_SCRIPTING, "Scripting");
	AppendMenu(menu, MF_STRING, MENU_HELP, "Help");
	SetMenu(handle_window, menu);
}


LRESULT CALLBACK WindowProc(
	HWND   handle_window,
	UINT   message,
	WPARAM wParam,
	LPARAM lParam
)
{	
	switch (message)
	{
		case WM_CREATE :
		{
			initWindow(handle_window);
			OutputDebugString("WM_CREATE\n");
		}break;

		case WM_COMMAND:
		{
			switch (wParam)
			{
				case (WPARAM) MENU_FILE :
				{
					MessageBeep(MB_OK);
				}break;

				case MENU_EDIT:
				{

				}break;

				case MENU_VIEW:
				{

				}break;

				case MENU_DATABASE:
				{

				}break;

				case MENU_SETTINGS:
				{

				}break;

				case MENU_TOOLS:
				{

				}break;

				case MENU_SCRIPTING:
				{

				}break;

				case MENU_HELP:
				{

				}break;
			}
			OutputDebugString("WM_COMMAND\n");
		}break;
		
		case WM_DESTROY :
		{
			running = false;
			OutputDebugString("WM_DESTROY\n");
			PostQuitMessage(0);
		}break;

		case WM_CLOSE :
		{
			running = false;
			OutputDebugString("WM_CLOSE\n");
		}break;

		case WM_ACTIVATEAPP :
		{
			OutputDebugString("WM_ACTIVATEAPP\n");
		}break;

		default:
		{
			return DefWindowProcA(handle_window, message, wParam, lParam);
		}break;
	}
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance, LPSTR cmd, int cmd_show)
{
	zn::Window window_data(250, 250, 250, 250, "Test window Title");

	// 'A' in the end of WNDCLASS means to handle strings in window as ansi code
	WNDCLASSA window_class = {};	// initializes every element of windows class  to 0

	window_class.hbrBackground = (HBRUSH) COLOR_WINDOW;		// Set a default window color
	window_class.hCursor = LoadCursor(NULL, IDC_ARROW);	// Enable a cursor in window
	window_class.lpfnWndProc = WindowProc;
	window_class.hInstance = instance;
	window_class.lpszClassName = "Zn0wDBWindowClass";

	if (RegisterClassA(&window_class))
	{
		HWND window_handle = CreateWindowA(
			"Zn0wDBWindowClass",
			window_data.getTitle(),
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			window_data.getX(),
			window_data.getY(),
			window_data.getWidth(),
			window_data.getHeight(),
			NULL,
			NULL,
			instance,
			NULL
			);

		if (window_handle)
		{
			running = true;

			while (running)
			{
				MSG message;
				if (GetMessageA(&message, NULL, NULL, NULL))
				{
					TranslateMessage(&message);
					DispatchMessageA(&message);		// Send message to the WindowProc
				}
				else
				{
					break;
				}
			}
		}
	}

	
	return 0;
#endif