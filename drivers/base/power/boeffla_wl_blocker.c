/*
<<<<<<< HEAD
 * Author: andip71, 01.09.2017
 *
 * Version 1.1.0
=======
 * Author: andip71, 28.08.2017
 *
 * Version 1.0.0
>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/*
 * Change log:
 *
<<<<<<< HEAD
 * 1.1.0 (01.09.2017)
 *   - By default, the following wakelocks are blocked in an own list
 *     qcom_rx_wakelock, wlan, wlan_wow_wl, wlan_extscan_wl, NETLINK
 *
 * 1.0.1 (29.08.2017)
 *   - Add killing wakelock when currently active
 *
=======
>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0
 * 1.0.0 (28.08.2017)
 *   - Initial version
 *
 */

#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/printk.h>
<<<<<<< HEAD
#include "boeffla_wl_blocker.h"
=======


#define BOEFFLA_WL_BLOCKER_VERSION	"1.0.0"
>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0


/*****************************************/
// Variables
/*****************************************/

<<<<<<< HEAD
char list_wl[LENGTH_LIST_WL] = {0};
char list_wl_default[LENGTH_LIST_WL_DEFAULT] = {0};

extern char list_wl_search[LENGTH_LIST_WL_SEARCH];
=======
extern char list_wl[255];
extern char list_wl_search[257];
>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0
extern bool wl_blocker_active;
extern bool wl_blocker_debug;


/*****************************************/
<<<<<<< HEAD
// internal functions
/*****************************************/

static void build_search_string(char *list1, char *list2)
{
	// store wakelock list and search string (with semicolons added at start and end)
	sprintf(list_wl_search, ";%s;%s;", list1, list2);

	// set flag if wakelock blocker should be active (for performance reasons)
	if (strlen(list_wl_search) > 5)
		wl_blocker_active = true;
	else
		wl_blocker_active = false;
}


/*****************************************/
// sysfs interface functions
/*****************************************/

// show list of user configured wakelocks
=======
// sysfs interface functions
/*****************************************/

>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0
static ssize_t wakelock_blocker_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	// return list of wakelocks to be blocked
	return sprintf(buf, "%s\n", list_wl);
}


<<<<<<< HEAD
// store list of user configured wakelocks
=======
>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0
static ssize_t wakelock_blocker_store(struct device * dev, struct device_attribute *attr,
			     const char * buf, size_t n)
{
	int len = n;

<<<<<<< HEAD
	// check if string is too long to be stored
	if (len > LENGTH_LIST_WL)
		return -EINVAL;

	// store user configured wakelock list and rebuild search string
	sscanf(buf, "%s", list_wl);
	build_search_string(list_wl_default, list_wl);

	return n;
}


// show list of default, predefined wakelocks
static ssize_t wakelock_blocker_default_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	// return list of wakelocks to be blocked
	return sprintf(buf, "%s\n", list_wl_default);
}


// store list of default, predefined wakelocks
static ssize_t wakelock_blocker_default_store(struct device * dev, struct device_attribute *attr,
			     const char * buf, size_t n)
{
	int len = n;

	// check if string is too long to be stored
	if (len > LENGTH_LIST_WL_DEFAULT)
		return -EINVAL;

	// store default, predefined wakelock list and rebuild search string
	sscanf(buf, "%s", list_wl_default);
	build_search_string(list_wl_default, list_wl);
=======
	// only strings up to 255 characters are allowed
	if (len > 255)
		return -EINVAL;

	// set flag if wakelock blocker should be active (for performance reasons)
	if (len > 1)
		wl_blocker_active = true;
	else
		wl_blocker_active = false;

	// store wakelock list and search string (with semicolons added at start and end)
	sscanf(buf, "%s", list_wl);
	sprintf(list_wl_search, ";%s;", list_wl);
>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0

	return n;
}


<<<<<<< HEAD
// show debug information of driver internals
static ssize_t debug_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	// return current debug status
	return sprintf(buf, "Debug status: %d\n\nUser list: %s\nDefault list: %s\nSearch list: %s\nActive: %d\n",
					wl_blocker_debug, list_wl, list_wl_default, list_wl_search, wl_blocker_active);
}


// store debug mode on/off (1/0)
=======
static ssize_t debug_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	// return current debug status
	return sprintf(buf, "Debug status: %d\n\nList: %s\nSearch list: %s\nActive: %d\n",
					wl_blocker_debug, list_wl, list_wl_search, wl_blocker_active);
}


>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0
static ssize_t debug_store(struct device *dev, struct device_attribute *attr,
						const char *buf, size_t count)
{
	unsigned int ret = -EINVAL;
	unsigned int val;

	// check data and store if valid
	ret = sscanf(buf, "%d", &val);

	if (ret != 1)
		return -EINVAL;

	if (val == 1)
		wl_blocker_debug = true;
	else
		wl_blocker_debug = false;

	return count;
}


static ssize_t version_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	// return version information
	return sprintf(buf, "%s\n", BOEFFLA_WL_BLOCKER_VERSION);
}



/*****************************************/
// Initialize sysfs objects
/*****************************************/

// define objects
static DEVICE_ATTR(wakelock_blocker, 0644, wakelock_blocker_show, wakelock_blocker_store);
<<<<<<< HEAD
static DEVICE_ATTR(wakelock_blocker_default, 0644, wakelock_blocker_default_show, wakelock_blocker_default_store);
=======
>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0
static DEVICE_ATTR(debug, 0664, debug_show, debug_store);
static DEVICE_ATTR(version, 0664, version_show, NULL);

// define attributes
static struct attribute *boeffla_wl_blocker_attributes[] = {
	&dev_attr_wakelock_blocker.attr,
<<<<<<< HEAD
	&dev_attr_wakelock_blocker_default.attr,
=======
>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0
	&dev_attr_debug.attr,
	&dev_attr_version.attr,
	NULL
};

// define attribute group
static struct attribute_group boeffla_wl_blocker_control_group = {
	.attrs = boeffla_wl_blocker_attributes,
};

// define control device
static struct miscdevice boeffla_wl_blocker_control_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "boeffla_wakelock_blocker",
};


/*****************************************/
// Driver init and exit functions
/*****************************************/

static int boeffla_wl_blocker_init(void)
{
	// register boeffla wakelock blocker control device
	misc_register(&boeffla_wl_blocker_control_device);
	if (sysfs_create_group(&boeffla_wl_blocker_control_device.this_device->kobj,
				&boeffla_wl_blocker_control_group) < 0) {
		printk("Boeffla WL blocker: failed to create sys fs object.\n");
		return 0;
	}

<<<<<<< HEAD
	// initialize default list
	sprintf(list_wl_default, "%s", LIST_WL_DEFAULT);
	build_search_string(list_wl_default, list_wl);

=======
>>>>>>> 4eaf081... boeffla_wl_blocker: add generic wakelock blocker driver v1.0.0
	// Print debug info
	printk("Boeffla WL blocker: driver version %s started\n", BOEFFLA_WL_BLOCKER_VERSION);

	return 0;
}


static void boeffla_wl_blocker_exit(void)
{
	// remove boeffla wakelock blocker control device
	sysfs_remove_group(&boeffla_wl_blocker_control_device.this_device->kobj,
                           &boeffla_wl_blocker_control_group);

	// Print debug info
	printk("Boeffla WL blocker: driver stopped\n");
}


/* define driver entry points */
module_init(boeffla_wl_blocker_init);
module_exit(boeffla_wl_blocker_exit);
