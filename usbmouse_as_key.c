#include <linux/init.h>
#include <linux/usb.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/hid.h>

static struct usb_device_id usbmouse_table [] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_MOUSE) },
	{ }	/* Terminating entry */
};

static int usbmouse_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_device* usb_dev;
	struct usb_host_interface* interface;
	struct usb_endpoint_descriptor *endpoint;
	struct input_dev* input_dev;

	usb_dev = interface_to_usbdev(interface);
	interface = interface->cur_altsetting;
	
	printk("usbmouse_probe...\n");
	
	printk("vendor:%d\n", usb_dev->descriptor.idVendor);
	printk("product:%d\n", usb_dev->descriptor.idProduct);
	printk("manufacture:%d\n", usb_dev->descriptor.iManufacturer);
	
	input_dev = input_allocate_device();
	if (!input_dev)
		return -ENOMEM;

	input_dev->name = "s3c2410_button";

	set_bit(EV_KEY, input_dev->evbit);
	set_bit(EV_REP, input_dev->evbit);
	
	set_bit(KEY_L, input_dev->keybit);
	set_bit(KEY_R, input_dev->keybit);
	set_bit(KEY_ENTER, input_dev->keybit);
	set_bit(KEY_BACKSLASH, input_dev->keybit);

	err = input_register_device(button_input_dev);
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

