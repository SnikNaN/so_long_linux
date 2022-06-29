


#include	"mlx_int.h"

#include	<unistd.h>
#include <X11/extensions/Xrandr.h>

/* global for independant extension */

RRMode	saved_mode = 0;


int			mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen)
{
  XWindowAttributes	watt;
  int			i;
  int			j;
  XRRScreenResources	*res;
  XRROutputInfo		*o_info;
  XRRCrtcInfo		*crtc;
  RRMode		mode_candidate;
  int			idx_output;
  int			idx_candidate;

  if (!XGetWindowAttributes(xvar->display, win->window, &watt))
    return (0);

  res = XRRGetScreenResources(xvar->display, xvar->root);
  o_info = NULL;
  idx_output = -1;
  i = res->noutput;
  while (i--)
    {
      o_info = XRRGetOutputInfo(xvar->display, res, res->outputs[i]);
      if (o_info->connection == RR_Connected)
	{
	  idx_output = i;
	  i = 0;
	}
      else
	XRRFreeOutputInfo(o_info);
    }
  if (!o_info)
    {
      XRRFreeScreenResources(res);
      return (0);
    }
  
  idx_candidate = -1;
  i = o_info->nmode;
  while (i--)
    {
      j = res->nmode;
      while (j--)
	if (res->modes[j].id == o_info->modes[i])
	  if (res->modes[j].width >= watt.width && res->modes[j].height >= watt.height &&
	      (idx_candidate == -1 || res->modes[idx_candidate].width > res->modes[j].width ||
	       res->modes[idx_candidate].height > res->modes[j].height) )
	    idx_candidate = i;
    }
  if (idx_candidate < 0)
    {
      XRRFreeOutputInfo(o_info);
      XRRFreeScreenResources(res);
      return (0);
    }
  if (!fullscreen && saved_mode == -1)
    idx_candidate = 0; /* if no clue, uses first mode, usually part of npreferred */
  mode_candidate = o_info->modes[idx_candidate];
  if (!fullscreen)
    mode_candidate = saved_mode;

  crtc = XRRGetCrtcInfo(xvar->display, res, o_info->crtc);
  saved_mode = crtc->mode;

  i = XRRSetCrtcConfig(xvar->display, res, o_info->crtc, CurrentTime, 0, 0, mode_candidate,
		       crtc->rotation, &res->outputs[idx_output], 1);
  if (fullscreen)
    printf("found mode : %d x %d\n Status %d\n", res->modes[idx_candidate].width, res->modes[idx_candidate].height, i);
  else
    printf("back previous mode\n");
  
  XMoveWindow(xvar->display, win->window, 0, 0);
  XMapRaised(xvar->display, win->window);

  if (fullscreen)
    {
      //      XGrabPointer(xvar->display, win->window, True, 0, GrabModeAsync, GrabModeAsync, win->window, 0L, CurrentTime);
      XGrabKeyboard(xvar->display, win->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
  else
    {
      XUngrabPointer(xvar->display, CurrentTime);
      XUngrabKeyboard(xvar->display, CurrentTime);
    }

  XSync(xvar->display, False);
  sleep(1);

  XRRFreeCrtcInfo(crtc);
  XRRFreeOutputInfo(o_info);
  XRRFreeScreenResources(res);
}

int force_properties(Display* display, Window win) {
    // Allowed actions
    Atom wm_allowed_actions = XInternAtom(display, "_NET_WM_ALLOWED_ACTIONS", 0);
    Atom wm_action_fullscreen = XInternAtom(display, "_NET_WM_ACTION_FULLSCREEN", 0);
    XChangeProperty(display, win, wm_allowed_actions, XA_ATOM, 32, PropModeAppend,
                    (unsigned char*)&wm_action_fullscreen, 1);

    // Size hints
    XSizeHints* size_hints_ptr = XAllocSizeHints();
    size_hints_ptr->flags = PMinSize;
    size_hints_ptr->min_width = 10;
    size_hints_ptr->min_height = 10;
    XSetWMNormalHints(display, win, size_hints_ptr);
    XFree(size_hints_ptr);
    return 1;
}

int toggle_fullscreen(Display* dpy, Window win) {
    Atom atoms[2] = { XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False), None };
    XChangeProperty(
            dpy,
            win,
            XInternAtom(dpy, "_NET_WM_STATE", False),
            XA_ATOM, 32, PropModeReplace, (unsigned char*)atoms, 1
    );
    return 0;
}

//int toggle_fullscreen(Display* display, Window win) {
//    int xev_action = 1; // 1 for fullscreen, 0 for normal
//
//    Atom wm_state   = XInternAtom(display, "_NET_WM_STATE", 0);
//    Atom wm_fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", 0);
//
//    XEvent xev;
//    memset(&xev, 0, sizeof(xev));
//    xev.type = ClientMessage;
//    xev.xclient.window = win;
//    xev.xclient.message_type = wm_state;
//    xev.xclient.format = 32;
//    xev.xclient.data.l[0] = xev_action;
//    xev.xclient.data.l[1] = wm_fullscreen;
//    xev.xclient.data.l[2] = 0;  // no second property to toggle
//    xev.xclient.data.l[3] = 1;  // source indication: application
//    xev.xclient.data.l[4] = 0;  // unused
//
//    Window root_win = DefaultRootWindow(display);
//
//    long evmask = SubstructureRedirectMask | SubstructureNotifyMask;
//    if (!XSendEvent(display, root_win, 0, evmask, &xev)) {
//        printf("XSendEvent failed");
//        return 0;
//    }
//
//    XWindowAttributes root_win_attr;
//    XGetWindowAttributes(display, root_win, &root_win_attr);
//
//    int display_width = root_win_attr.width;
//    int display_height = root_win_attr.height;
//    XMoveResizeWindow(display, win, 0, 0, display_width, display_height);
//    XMapRaised(display, win);
//    return 1;
//}