#include "rce.h"
#include "uinput.h"
#include <stddef.h>


struct libevdev_uinput *uinput_initialize(const struct input_absinfo* absinfoX, const struct input_absinfo* absinfoY) {
    // Create a evdev first to describe the features
    struct libevdev *evdev = libevdev_new();
    libevdev_set_name(evdev, "Simulated Right Button");
    libevdev_enable_event_type(evdev, EV_KEY);
    libevdev_enable_event_code(evdev, EV_KEY, BTN_RIGHT, NULL);
    if (TOUCH_DEVICE_GRAB)
        libevdev_enable_event_code(evdev, EV_KEY, BTN_LEFT, NULL);

    libevdev_enable_event_type(evdev, EV_ABS);
    libevdev_enable_event_code(evdev, EV_ABS, ABS_X, absinfoX);

    libevdev_enable_event_code(evdev, EV_ABS, ABS_Y, absinfoY);
    // Initialize uinput device from the evdev descriptor
    struct libevdev_uinput *uinput = NULL;
    if (libevdev_uinput_create_from_device(evdev,
            LIBEVDEV_UINPUT_OPEN_MANAGED, &uinput) != 0) {
        uinput = NULL;
    }
    // We don't need the fake evdev anymore.
    libevdev_free(evdev);
    return uinput;
}

void uinput_send_move(struct libevdev_uinput *uinput, int positionX, int positionY) {
    libevdev_uinput_write_event(uinput, EV_ABS, ABS_X, positionX);
    libevdev_uinput_write_event(uinput, EV_ABS, ABS_Y, positionY);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);
}

void uinput_send_click(struct libevdev_uinput *uinput, int positionX, int positionY, int button) {
    libevdev_uinput_write_event(uinput, EV_ABS, ABS_X, positionX);
    libevdev_uinput_write_event(uinput, EV_ABS, ABS_Y, positionY);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);

    libevdev_uinput_write_event(uinput, EV_KEY, button, 1);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);
    libevdev_uinput_write_event(uinput, EV_KEY, button, 0);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);
}