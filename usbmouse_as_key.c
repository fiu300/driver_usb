#include <linux/init.h>
#include <linux/usb.h>
#include <linux/errno.h>
#include <linux/kernel.h>

#define USB_SKEL_VENDOR_ID      0xfff0                                                                                                        
#define USB_SKEL_PRODUCT_ID     0xfff0

static struct usb_device_id skel_table [] = {                                                                                                 
	{ USB_DEVICE(USB_SKEL_VENDOR_ID, USB_SKEL_PRODUCT_ID) },
	{ }                                     /* Terminating entry */
};   


static int usbmouse_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk("usbmouse_probe...\n");

	return 0;
}

static void usbmouse_disconnect(struct usb_interface *interface)
{
	printk("usbmouse_disconnect...\n");	
}

static struct usb_driver usbmouse_as_key_fops = {
	.name = "usbmouse_key",
	.probe = usbmouse_probe,
	.disconnect = usbmouse_disconnect,
	.id_table = usbmouse_table,
	.supports_autosuspend = 1,
};

static int __init usbmouse_as_key_init(void)
{
	int ret=0;

	ret = usb_register(&usbmouse_as_key_fops);
	if(ret)
		err("usb register failed. err number:%d\n", ret);

	return ret;
}

static void __exit usbmouse_as_key_exit(void)
{
	usb_deregister(&usbmouse_as_key_fops);
}

module_init(usbmouse_as_key_init);
module_exit(usbmouse_as_key_exit);

MODULE_LICENSE("GPL");

