#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <iostream>

Display* display;
Window window;

int main()
{
    // Open a connection to the X server
    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        std::cerr << "Error: could not open display" << std::endl;
        return 1;
    }

    // Create a window to receive keyboard events
    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, 1, 1, 0, 0, WhitePixel(display, screen));
    XSelectInput(display, window, KeyPressMask);
    XMapWindow(display, window);

    // Main event loop
    while (true) {
        XEvent event;
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            KeySym key = XLookupKeysym(&event.xkey, 0);
            std::cout << "Key pressed: " << XKeysymToString(key) << std::endl;
        }
    }

    // Clean up
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}
