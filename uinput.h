#ifndef UINPUT_H
#define UINPUT_H
#include <libevdev/libevdev-uinput.h>

struct libevdev_uinput *uinput_initialize(const struct input_absinfo* absinfoX, const struct input_absinfo* absinfoY);
void uinput_send_click(struct libevdev_uinput *uinput, int positionX, int positionY, int button);
void uinput_send_move(struct libevdev_uinput *uinput, int positionX, int positionY);
#endif
