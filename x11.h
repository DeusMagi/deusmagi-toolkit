/**
 * @file
 * X11 API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_X11_H
#define TOOLKIT_X11_H

#include "toolkit.h"

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(x11);

/**
 * Get the parent window.
 *
 * @param display
 * Display.
 * @param win
 * Window.
 * @return
 * Parent window.
 */
extern x11_window_type
x11_window_get_parent(x11_display_type display,
                      x11_window_type  win);

/**
 * Raises the specified window.
 *
 * @param display
 * Display.
 * @param win
 * Window to raise.
 * @param switch_desktop
 * If 1, will also switch the desktop to that of the window's desktop.
 */
extern void
x11_window_activate(x11_display_type display,
                    x11_window_type  win,
                    uint8_t          switch_desktop);

/**
 * Register clipboard events.
 *
 * @return
 * 1 on success, 0 on failure.
 */
extern int
x11_clipboard_register_events(void);

/**
 * Set the contents of the clipboard.
 *
 * @param display
 * Display.
 * @param win
 * Window.
 * @param str
 * String to set contents of the clipboard to.
 * @return
 * 1 on success, 0 on failure.
 */
extern int
x11_clipboard_set(x11_display_type display,
                  x11_window_type  win,
                  const char      *str);

/**
 * Get the contents of the clipboard.
 *
 * @param display
 * Display.
 * @param window
 * Window.
 * @return
 * Clipboard contents, must be freed. May be NULL in case of
 * failure to acquire the clipboard contents.
 */
char *
x11_clipboard_get(x11_display_type display,
                  x11_window_type  win);

#endif
