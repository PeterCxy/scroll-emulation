A simple hack to use middle button scroll emulation under GNOME Wayland (and other Wayland composers that don't show 'libinput' configuration). This is tested with my GPD Pocket, which has no trackpoint middle button, so it can't scroll by default (after implementing this hook, I can use right button + cursor to emulate scrolling)

- Dependencies (fedora) : ```sudo dnf install libinput-devel systemd-devel```

- Simply clone this repo and enter folder: ```git clone <url> && cd scroll-emulation```

- If you want to use Middle click instead of right click, first run this command (no need for right click):

```bash
sed -i 's/libinput_device_config_scroll_set_button(device, 273);//' ./hook.c
```

- install:

```bash
sudo chmod +x ./install.sh
./install.sh
```
Restart and enjoy. (Press right button and move cursor = scroll)
