/*
 * Based on Obdev's V-USB code and under the same license.
 */
#ifndef __hid_custom_rq_h__
#define __hid_custom_rq_h__

#include "Arduino.h"
#include "usbdrv.h"
#include "requests.h"       /* The custom request numbers we use */

class hid_custom_rqDevice {
 public:
  hid_custom_rqDevice () {
    usbInit();
    ledPin = 13;        // pin 13 as default ledPin
  }
    
  void poll() {
    usbPoll();
  }
  
  unsigned int ledPin;  
};

hid_custom_rqDevice hid_custom_rq = hid_custom_rqDevice();

/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

PROGMEM char usbHidReportDescriptor[22] = {    /* USB report descriptor */
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xc0                           // END_COLLECTION
};
/* The descriptor above is a dummy only, it silences the drivers. The report
 * it describes consists of one byte of undefined data.
 * We don't transfer our data through HID reports, we use custom requests
 * instead.
 */


usbMsgLen_t usbFunctionSetup(uchar data[8])
{
    usbRequest_t    *rq = (usbRequest_t *)((void *)data);    

    /* Manually added for testing echo */
    static uchar    dataBuffer[4];  /* buffer must stay valid when usbFunctionSetup returns */  
    if(rq->bRequest == CUSTOM_RQ_ECHO){ /* echo -- used for reliability tests */  
            dataBuffer[0] = rq->wValue.bytes[0];  
            dataBuffer[1] = rq->wValue.bytes[1];  
            dataBuffer[2] = rq->wIndex.bytes[0];  
            dataBuffer[3] = rq->wIndex.bytes[1];  
            usbMsgPtr = dataBuffer;         /* tell the driver which data to return */  
            return 4;  
        }

    if(rq->bRequest == CUSTOM_RQ_BLINK){ /* blink -- used for blink the LED */
	    /* First set the led pin to high  */
	     unsigned char i = 6;
	     while(i >= 1)
	     {
	     digitalWrite(hid_custom_rq.ledPin, HIGH);
	     delay(1000);
	     digitalWrite(hid_custom_rq.ledPin, LOW);
	     delay(1000);
	     i--;
	     }
    }

    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_VENDOR){
        if(rq->bRequest == CUSTOM_RQ_SET_STATUS){
            if(rq->wValue.bytes[0] & 1){    /* set LED */
                digitalWrite(hid_custom_rq.ledPin, HIGH);
            }else if(rq->wValue.bytes[0] == 0){                          /* clear LED */
                digitalWrite(hid_custom_rq.ledPin, LOW);
            }
	    else 
	    {
                digitalWrite(hid_custom_rq.ledPin, HIGH);
	        delay(1000);
                digitalWrite(hid_custom_rq.ledPin, LOW);
	        delay(1000);
                digitalWrite(hid_custom_rq.ledPin, HIGH);
	        delay(1000);
                digitalWrite(hid_custom_rq.ledPin, LOW);
	        delay(1000);

	    }
        }else if(rq->bRequest == CUSTOM_RQ_GET_STATUS){
            static uchar dataBuffer[1];     /* buffer must stay valid when usbFunctionSetup returns */
            dataBuffer[0] = digitalRead(hid_custom_rq.ledPin);
            usbMsgPtr = dataBuffer;         /* tell the driver which data to return */
            return 1;                       /* tell the driver to send 1 byte */
        }
    }else{
        /* calss requests USBRQ_HID_GET_REPORT and USBRQ_HID_SET_REPORT are
         * not implemented since we never call them. The operating system
         * won't call them either because our descriptor defines no meaning.
         */
    }
    return 0;   /* default for not implemented requests: return no data back to host */
}


#endif // __hid_csutom_rq_h__
