#define _GNU_SOURCE
#include <dlfcn.h>
#include <libinput.h>

typedef const char* (*orig_get_name_t)(struct libinput_device *device);

const char* libinput_device_get_name(struct libinput_device *device) {
  set_scroll_emulation(device); // Inject the code to set scrolling emulation
  orig_get_name_t orig_get_name;
  orig_get_name = (orig_get_name_t) dlsym(RTLD_NEXT, "libinput_device_get_name");
  return orig_get_name(device);
}

void set_scroll_emulation(struct libinput_device *device) {
  libinput_device_config_middle_emulation_set_enabled(device, LIBINPUT_CONFIG_MIDDLE_EMULATION_ENABLED);
  libinput_device_config_scroll_set_method(device, LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN);
  libinput_device_config_scroll_set_button(device, 273);
}
