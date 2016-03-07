/* Name: opendevice.c
 * Project: V-USB host-side library
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-10
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: opendevice.c 740 2009-04-13 18:23:31Z cs $
 */

/*
General Description:
The functions in this module can be used to find and open a device based on
libusb or libusb-win32.
*/

#include <stdio.h>
#include "opendevice.h"

/* ------------------------------------------------------------------------- */

usb_dev_handle * usbOpenDevice(int vendorID, int productID)
{
struct usb_bus      *bus;
struct usb_device   *dev;

    usb_init();
    usb_find_busses();
    usb_find_devices();
    for(bus=usb_get_busses(); bus; bus=bus->next){
        for(dev=bus->devices; dev; dev=dev->next){
            if(dev->descriptor.idVendor == vendorID && dev->descriptor.idProduct == productID)
                return usb_open(dev); 
        }
    }    
    
    return NULL;
}

/* ------------------------------------------------------------------------- */
