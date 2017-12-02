A simple hack to use middle button scrolling emulation under GNOME Wayland (and other Wayland compositors that do not expose `libinput` configuration). This is tested with my GPD Pocket, whose trackpoint does not have a middle button thus cannot scroll by default (after applying this hook, I can use right button + cursor to emulate scrolling)

Simply clone this repo and run

```bash
gcc -shared -ldl -fPIC hook.c -o hook.so
```

which will generate a `hook.so` in the current directory.

Then add this `hook.so` to your LD\_PRELOAD (use `/etc/profile.d` or `/etc/profile` in order to make it usable to GNOME Wayland)

e.g. You could add content like this to `/etc/profile.d/libinput.sh`

```bash
export LD_PRELOAD="$LD_PRELOAD /path/to/your/hook.so"
```

replace `/path/to/your/hook.so` with the __absolute path__ to your `hook.so`.

Reboot and enjoy. (Press right button and move the cursor = scrolling)

How does it work
===

It is very simple. The `libinput` library itself already contains code to emulate scrolling. Under Xorg we can use configuration like this

```
Driver "libinput"
Option "MiddleEmulation" "1"
Option "ScrollButton" "3"
Option "ScrollMethod" "button"
```

To enable this built-in feature. Even if some Wayland compositors do not expose such configuration, the functionality is still available thanks to `libinput`. All we need to do is to find a way to force apply these options to the devices.

Therefore, I tried to find a function that has `libinput_device` as a parameter and will be always called. One of them is `libinput_device_get_name`. This is what `hook.c` does: hook into this function and force set the needed configuration on every possible device. Since the compositors will load `/etc/profile` regardlessly, we will now have working scrolling emulation.

It might be better if something could be done to force expose those configuration options through `LD_PRELOAD`. This is not difficult, but I'm not doing it now because it seems enough for me right now :).
