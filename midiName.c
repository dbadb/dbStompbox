#include "usb_names.h"

#define MIDI_NAME_LEN 10
#define PRODUCT_NAME {'d', 'B', 'S', 't', 'o', 'm', 'p', 'b', 'o', 'x'}

struct usb_string_descriptor_struct usb_string_product_name = 
{
    2 + MIDI_NAME_LEN * 2,
    3, 
   	PRODUCT_NAME
};
