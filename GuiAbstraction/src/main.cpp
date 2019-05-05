#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "window.h"

bool running;

#if 0
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
#endif;

std::vector<zn::Element>* test_elements;


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
			OutputDebugString("WM_CREATE\n");
		}break;

		case WM_COMMAND:
		{
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

		case WM_PAINT:
		{
			// TODO : handle event with event system and change window_data or use windows's default handling (with paint struct)
			PAINTSTRUCT paint;
			HDC device_context = BeginPaint(handle_window, &paint);

			for (int i = 0; i < test_elements->size(); i++)
			{
				Rectangle(device_context,
					test_elements->at(i).getX(),
					test_elements->at(i).getY(),
					test_elements->at(i).getX() + test_elements->at(i).getWidth(),
					test_elements->at(i).getY() + test_elements->at(i).getHeight());
			}

			EndPaint(handle_window, &paint);
		}break;

		default:
		{
			return DefWindowProcA(handle_window, message, wParam, lParam);
		}break;
	}
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance, LPSTR cmd, int cmd_show)
{
	//zn::Window window_data(250, 250, 250, 250, "Test window Title");
	zn::Window window_data(500, 500, 400, 400, "Test Window");
	zn::Frame test_frame(new zn::SequenceLayout(zn::Y_AXIS, 400, 400, 5, 5));
	window_data.setFrame(&test_frame);

	test_frame.addElement(zn::Element("Button1", 100, 35));
	test_frame.addElement(zn::Element("Button2", 100, 50));
	test_frame.addElement(zn::Element("Button3", 75, 15));
	test_frame.addElement(zn::Element("Button4", 75, 15));
	test_frame.addElement(zn::Element("Button5", 100, 80));
	test_frame.addElement(zn::Element("Button6", 100, 80));
	test_frame.addElement(zn::Element("Button7", 100, 15));
	test_frame.addElement(zn::Element("Button8", 75, 55));
	test_frame.addElement(zn::Element("Button9", 75, 15));
	test_frame.addElement(zn::Element("Button10", 100, 15));

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

	test_elements = test_frame.getElements();

	// 'A' in the end of WNDCLASS means to handle strings in window as ansi code
	WNDCLASSA window_class = {};	// initializes every element of windows class  to 0

	window_class.hbrBackground = (HBRUSH)COLOR_WINDOW;		// Set a default window color
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
}