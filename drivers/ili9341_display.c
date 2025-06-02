/**
 * @file ili9341_chardev.c
 * @brief Character Device Driver for ILI9341 TFT LCD (240x320)
 * 
 * Implements a character device interface for direct control of ILI9341 displays
 * via SPI interface.
 */

#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/fb.h>

#define DRIVER_NAME         "ili9341"
#define DEVICE_NAME        "ili9341"
#define CLASS_NAME         "ili9341"

/* Display parameters */
#define ILI9341_WIDTH       240
#define ILI9341_HEIGHT      320
#define ILI9341_BPP         16      /* 16 bits per pixel (RGB565) */
#define MAX_CMD_SIZE        32

/* ILI9341 Commands */
#define ILI9341_SWRESET     0x01
#define ILI9341_SLPOUT      0x11
#define ILI9341_DISPOFF     0x28
#define ILI9341_DISPON      0x29
#define ILI9341_CASET       0x2A
#define ILI9341_PASET       0x2B
#define ILI9341_RAMWR       0x2C
#define ILI9341_MADCTL      0x36
#define ILI9341_COLMOD      0x3A
#define ILI9341_PIXFMT      0x55    /* 16-bit color */

/* MADCTL bits */
#define MADCTL_MY          0x80
#define MADCTL_MX          0x40
#define MADCTL_MV          0x20
#define MADCTL_ML          0x10
#define MADCTL_RGB         0x00
#define MADCTL_BGR         0x08
#define MADCTL_MH          0x04

/* Default orientation */
#define ILI9341_ROTATION   (MADCTL_MX | MADCTL_RGB)

/* Delay times */
#define ILI9341_RESET_DELAY 5       /* ms */
#define ILI9341_SWRESET_DELAY 120   /* ms */

struct ili9341_device {
    struct spi_device *spi;
    struct cdev cdev;
    dev_t dev_num;
    struct class *class;
    struct device *device;
    
    int reset_gpio;
    int dc_gpio;
    int cs_gpio;
    u8 rotation;
    
    // /* Buffer for display data */
    // u16 *display_buffer;
    // size_t buffer_size;
};

/* File operations prototypes */
static int ili9341_open(struct inode *inode, struct file *file);
static int ili9341_release(struct inode *inode, struct file *file);
// static ssize_t ili9341_write(struct file *file, const char __user *buf, 
//                            size_t len, loff_t *ppos);
static long ili9341_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/* File operations structure */
static const struct file_operations ili9341_fops = {
    .owner = THIS_MODULE,
    .open = ili9341_open,
    .release = ili9341_release,
    // .write = ili9341_write,
    .unlocked_ioctl = ili9341_ioctl,
};

/* IOCTL commands */
#define ILI9341_CLEAR_DISPLAY   _IO('D', 0)
#define ILI9341_SET_ROTATION    _IOW('D', 1, int)
#define ILI9341_SET_PIXEL       _IOW('D', 2, struct ili9341_pixel)
#define ILI9341_FILL_RECT       _IOW('D', 3, struct ili9341_rect)

/* Pixel structure for IOCTL */
struct ili9341_pixel {
    u16 x;
    u16 y;
    u16 color;
};

/* Rectangle structure for IOCTL */
struct ili9341_rect {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16* color;
};

/**
 * @brief Send command to ILI9341
 * @param dev Device structure
 * @param cmd Command byte
 */
static void ili9341_write_command(struct ili9341_device *dev, u8 cmd)
{
    struct spi_transfer t = {
        .tx_buf = &cmd,
        .len = 1,
    };
    struct spi_message m;

    gpio_set_value(dev->dc_gpio, 0);  /* Command mode */
    spi_message_init(&m);
    spi_message_add_tail(&t, &m);
    spi_sync(dev->spi, &m);
}

/**
 * @brief Send data to ILI9341
 * @param dev Device structure
 * @param data Data buffer
 * @param len Data length
 */
static void ili9341_write_data(struct ili9341_device *dev, u8 *data, int len)
{
    struct spi_transfer t = {
        .tx_buf = data,
        .len = len,
        .speed_hz = 10000000,  /* 10MHz */
    };
    struct spi_message m;

    gpio_set_value(dev->dc_gpio, 1);  /* Data mode */
    spi_message_init(&m);
    spi_message_add_tail(&t, &m);
    spi_sync(dev->spi, &m);
}

/**
 * @brief Set address window for drawing
 * @param dev Device structure
 * @param x0 Start X position
 * @param y0 Start Y position
 * @param x1 End X position
 * @param y1 End Y position
 */
static void ili9341_set_window(struct ili9341_device *dev, u16 x0, u16 y0, u16 x1, u16 y1)
{
    u8 buf[4];
    
    /* Column address set */
    ili9341_write_command(dev, ILI9341_CASET);
    buf[0] = x0 >> 8;
    buf[1] = x0 & 0xFF;
    buf[2] = x1 >> 8;
    buf[3] = x1 & 0xFF;
    ili9341_write_data(dev, buf, 4);

    /* Page address set */
    ili9341_write_command(dev, ILI9341_PASET);
    buf[0] = y0 >> 8;
    buf[1] = y0 & 0xFF;
    buf[2] = y1 >> 8;
    buf[3] = y1 & 0xFF;
    ili9341_write_data(dev, buf, 4);

    /* Memory write */
    ili9341_write_command(dev, ILI9341_RAMWR);
}

/**
 * @brief Initialize ILI9341 display
 * @param dev Device structure
 */
static void ili9341_init_display(struct ili9341_device *dev)
{
    int ret;

    pr_info("[%s - %d] ILI9341 display initialization\n", __func__, __LINE__);

    /* Request GPIO pins */
    ret = gpio_request(dev->reset_gpio, "RST");
    if (ret) {
        pr_err("[%s - %d] Failed to request RST GPIO: %d\n", __func__, __LINE__, ret);
        return;
    }

    ret = gpio_request(dev->dc_gpio, "DC");
    if (ret) {
        pr_err("[%s - %d] Failed to request DC GPIO: %d\n", __func__, __LINE__, ret);
        gpio_free(dev->reset_gpio);
        return;
    }
    
    /* Set GPIO directions */
    gpio_direction_output(dev->reset_gpio, 0);
    gpio_direction_output(dev->dc_gpio, 0);

    /* Hardware reset */
    gpio_set_value(dev->reset_gpio, 0);
    msleep(ILI9341_RESET_DELAY);
    gpio_set_value(dev->reset_gpio, 1);
    msleep(ILI9341_RESET_DELAY);
    
    /* Software reset */
    ili9341_write_command(dev, ILI9341_SWRESET);
    msleep(ILI9341_SWRESET_DELAY);

    /* Exit sleep mode */
    ili9341_write_command(dev, ILI9341_SLPOUT);
    msleep(120);

    /* Set pixel format to 16 bits per pixel (RGB565) */
    ili9341_write_command(dev, ILI9341_COLMOD);
    ili9341_write_data(dev, &(u8){ILI9341_PIXFMT}, 1);

    /* Memory access control (rotation) */
    ili9341_write_command(dev, ILI9341_MADCTL);
    ili9341_write_data(dev, &(u8){dev->rotation}, 1);

    /* Display on */
    ili9341_write_command(dev, ILI9341_DISPON);
    msleep(100);
}

/**
 * @brief Clear the display
 * @param dev Device structure
 * @param color Fill color (RGB565)
 */
static void ili9341_clear_display(struct ili9341_device *dev, u16 color)
{
    int i;
    u16 *buf;
    int pixels = ILI9341_WIDTH * ILI9341_HEIGHT;
    
    /* Allocate buffer for one row */
    buf = kmalloc(ILI9341_WIDTH * sizeof(u16), GFP_KERNEL);
    if (!buf)
        return;
        
    /* Fill buffer with color */
    for (i = 0; i < ILI9341_WIDTH; i++)
        buf[i] = color;
    
    /* Set full window */
    ili9341_set_window(dev, 0, 0, ILI9341_WIDTH-1, ILI9341_HEIGHT-1);
    
    /* Write rows */
    for (i = 0; i < ILI9341_HEIGHT; i++) {
        ili9341_write_data(dev, (u8 *)buf, ILI9341_WIDTH * sizeof(u16));
    }
    
    kfree(buf);
    
    // /* Clear local buffer if exists */
    // if (dev->display_buffer) {
    //     memset(dev->display_buffer, color, dev->buffer_size);
    // }
}

// /**
//  * @brief Set a single pixel
//  * @param dev Device structure
//  * @param x X coordinate
//  * @param y Y coordinate
//  * @param color Pixel color (RGB565)
//  */
// static void ili9341_set_pixel(struct ili9341_device *dev, u16 x, u16 y, u16 color)
// {
//     /* Update local buffer if exists */
//     if (dev->display_buffer) {
//         if (x < ILI9341_WIDTH && y < ILI9341_HEIGHT) {
//             dev->display_buffer[y * ILI9341_WIDTH + x] = color;
//         }
//     }
    
//     /* Update hardware */
//     ili9341_set_window(dev, x, y, x, y);
//     ili9341_write_data(dev, (u8 *)&color, sizeof(u16));
// }

/**
 * @brief Fill a rectangle
 * @param dev Device structure
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Rectangle width
 * @param height Rectangle height
 * @param color Fill color (RGB565)
 */
static void ili9341_fill_rect(struct ili9341_device *dev, u16 x, u16 y, 
                            u16 width, u16 height, u16* color)
{
    int i, j;
    // u16 *row_buf;
    
    /* Validate coordinates */
    if (x >= ILI9341_WIDTH || y >= ILI9341_HEIGHT)
        return;
        
    if (x + width > ILI9341_WIDTH)
        width = ILI9341_WIDTH - x;
        
    if (y + height > ILI9341_HEIGHT)
        height = ILI9341_HEIGHT - y;
        
    /* Update display */
    ili9341_set_window(dev, x, y, x + width - 1, y + height - 1);
    ili9341_write_data(dev, (u8 *)color, width * height * sizeof(u16));
}

/**
 * @brief Open character device
 * @param inode Inode structure
 * @param file File structure
 * @return 0 on success
 */
static int ili9341_open(struct inode *inode, struct file *file)
{
    struct ili9341_device *dev = container_of(inode->i_cdev, 
                                            struct ili9341_device, cdev);
    file->private_data = dev;
    return 0;
}

/**
 * @brief Release character device
 * @param inode Inode structure
 * @param file File structure
 * @return 0 on success
 */
static int ili9341_release(struct inode *inode, struct file *file)
{
    file->private_data = NULL;
    return 0;
}

// /**
//  * @brief Write to character device
//  * @param file File structure
//  * @param buf User buffer
//  * @param len Length to write
//  * @param ppos Position pointer
//  * @return Number of bytes written or error code
//  */
// static ssize_t ili9341_write(struct file *file, const char __user *buf,
//                            size_t len, loff_t *ppos)
// {
//     struct ili9341_device *dev = file->private_data;
//     u16 *pixels;
//     int pixels_count;
//     int ret;
    
//     /* Calculate number of pixels (2 bytes per pixel) */
//     pixels_count = len / sizeof(u16);
//     if (pixels_count == 0)
//         return -EINVAL;
    
//     /* Allocate temporary buffer */
//     pixels = kmalloc(len, GFP_KERNEL);
//     if (!pixels)
//         return -ENOMEM;
    
//     /* Copy data from user space */
//     if (copy_from_user(pixels, buf, len)) {
//         kfree(pixels);
//         return -EFAULT;
//     }
    
    
//     /* Set full window */
//     ili9341_set_window(dev, 0, 0, ILI9341_WIDTH-1, ILI9341_HEIGHT-1);
    
//     /* Write pixel data */
//     ili9341_write_data(dev, (u8 *)pixels, len);
    
//     /* Update local buffer if exists */
//     if (dev->display_buffer) {
//         size_t copy_size = min(len, dev->buffer_size);
//         memcpy(dev->display_buffer, pixels, copy_size);
//     }
    
//     kfree(pixels);
    
//     return len;
// }

/**
 * @brief IOCTL handler
 * @param file File structure
 * @param cmd IOCTL command
 * @param arg Command argument
 * @return 0 on success, error code on failure
 */
static long ili9341_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct ili9341_device *dev = file->private_data;
    struct ili9341_pixel pixel;
    struct ili9341_rect rect;
    int rotation;
    
    switch (cmd) {
    case ILI9341_CLEAR_DISPLAY:
        ili9341_clear_display(dev, (u16)arg);
        break;
        
    // case ILI9341_SET_ROTATION:
    //     if (copy_from_user(&rotation, (int __user *)arg, sizeof(int)))
    //         return -EFAULT;
            
    //     dev->rotation = rotation & 0xFF;
    //     ili9341_write_command(dev, ILI9341_MADCTL);
    //     ili9341_write_data(dev, &dev->rotation, 1);
    //     break;
        
    // case ILI9341_SET_PIXEL:
    //     if (copy_from_user(&pixel, (struct ili9341_pixel __user *)arg, sizeof(pixel)))
    //         return -EFAULT;
            
    //     ili9341_set_pixel(dev, pixel.x, pixel.y, pixel.color);
    //     break;
        
    case ILI9341_FILL_RECT:
        if (copy_from_user(&rect, (struct ili9341_rect __user *)arg, sizeof(rect)))
            return -EFAULT;
            
        ili9341_fill_rect(dev, rect.x, rect.y, rect.width, rect.height, rect.color);
        break;
        
    default:
        return -ENOTTY;
    }
    
    return 0;
}

/**
 * @brief Create character device
 * @param dev Device structure
 * @return 0 on success, error code on failure
 */
static int ili9341_create_cdev(struct ili9341_device *dev)
{
    int ret;

    pr_info("[%s - %d] Creating device file\n", __func__, __LINE__);
    
    /* Allocate device number */
    ret = alloc_chrdev_region(&dev->dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        pr_err("[%s - %d] Cannot register major number: %d\n", __func__, __LINE__, ret);
        goto alloc_dev_failed;
    }

    pr_info("[%s - %d] Registered with major = %d, minor = %d\n", 
        __func__, __LINE__, MAJOR(dev->dev_num), MINOR(dev->dev_num));

    /* Create device class */
    dev->class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(dev->class)) {
        ret = PTR_ERR(dev->class);
        pr_err("[%s - %d] Cannot create device class: %d\n", __func__, __LINE__, ret);
        goto create_class_failed;
    }      

    /* Create device node */
    dev->device = device_create(dev->class, &dev->spi->dev, 
                              dev->dev_num, dev, DEVICE_NAME);
    if (IS_ERR(dev->device)) {
        ret = PTR_ERR(dev->device);
        pr_err("[%s - %d] Cannot create device file: %d\n", __func__, __LINE__, ret);
        goto create_device_failed;
    }    

    /* Initialize character device */
    cdev_init(&dev->cdev, &ili9341_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.dev = dev->dev_num;

    /* Add character device */
    ret = cdev_add(&dev->cdev, dev->dev_num, 1);
    if (ret) {
        pr_err("[%s - %d] Cannot add cdev: %d\n", __func__, __LINE__, ret);
        goto cdev_add_failed;
    }

    pr_info("[%s - %d] Device file created successfully\n", __func__, __LINE__);
    return 0;

cdev_add_failed:
    device_destroy(dev->class, dev->dev_num);
create_device_failed:
    class_destroy(dev->class);
create_class_failed:
    unregister_chrdev_region(dev->dev_num, 1);
alloc_dev_failed:
    return ret;
}

// /**
//  * @brief Initialize display buffer
//  * @param dev Device structure
//  * @return 0 on success, error code on failure
//  */
// static int ili9341_init_buffer(struct ili9341_device *dev)
// {
//     dev->buffer_size = ILI9341_WIDTH * ILI9341_HEIGHT * sizeof(u16);
//     dev->display_buffer = kzalloc(dev->buffer_size, GFP_KERNEL);
//     if (!dev->display_buffer) {
//         dev_err(&dev->spi->dev, "Failed to allocate display buffer\n");
//         return -ENOMEM;
//     }
    
//     return 0;
// }



/**
 * @brief Probe function for SPI driver
 * @param spi SPI device
 * @return 0 on success, error code on failure
 */
static int ili9341_probe(struct spi_device *spi)
{
    struct ili9341_device *dev;
    struct device_node *np = spi->dev.of_node;
    int ret;

    pr_info("[%s - %d] Probing ILI9341 SPI device \n", __func__, __LINE__);
    
    /* Allocate device structure */
    dev = kzalloc(sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;
    
    dev->spi = spi;
    spi_set_drvdata(spi, dev);
    
    /* Get GPIOs from device tree */
    dev->reset_gpio = of_get_named_gpio(np, "reset-gpios", 0);
    if (dev->reset_gpio < 0) {
        pr_err("[%s - %d] Failed to get reset-gpios from DT: %d\n", __func__, __LINE__, dev->reset_gpio);
        ret = dev->reset_gpio;
        goto err_free_module;
    }
    
    dev->dc_gpio = of_get_named_gpio(np, "dc-gpios", 0);
    if (dev->dc_gpio < 0) {
        pr_err("[%s - %d] Failed to get dc-gpios from DT: %d\n", __func__, __LINE__, dev->dc_gpio);
        ret = dev->dc_gpio;
        goto err_free_module;
    }

    dev->cs_gpio = of_get_named_gpio(np, "cs-gpios", 0);
    if (dev->cs_gpio < 0) {
        /* CS is optional, use SPI native CS */
        dev->cs_gpio = -1;
    }
    
    /* Setup rotation */
    dev->rotation = ILI9341_ROTATION;
    
       
    /* Setup SPI */
    spi->bits_per_word = 8;
    spi->mode = SPI_MODE_0;
    if (!spi->max_speed_hz)
        spi->max_speed_hz = 10000000; /* 10MHz default */

    ret = spi_setup(spi);
    if (ret < 0) {
        dev_err(&spi->dev, "Failed to setup SPI: %d\n", ret);
        return ret;
    }
    
    /* Initialize display */
    ili9341_init_display(dev);
    
    // /* Create display buffer */
    // ret = ili9341_init_buffer(dev);
    // if (ret)
    //     return ret;
    
    /* Create character device */
    ret = ili9341_create_cdev(dev);
    if (ret != 0)
    {
        pr_err("[%s - %d] Failed to create device file: %d\n", __func__, __LINE__, ret);
        goto err_free_module;
    }


    // Just to test the display, fill it with red color
    {
        u16 *framebuffer;
        /* Allocate buffer for one row */
        framebuffer = kmalloc(40 * 60 * sizeof(u16), GFP_KERNEL);
        if (!framebuffer)
            return;
        /* Fill framebuffer with red color */
        int i;
        for (i = 0; i < 40 * 60; i++)
            framebuffer[i] = 0xF800; // Red in RGB565 format

        ili9341_fill_rect(dev, 0, 0, 40, 60, framebuffer); // Fill red
        kfree(framebuffer);
    }

    dev_info(&spi->dev, "ILI9341 display initialized\n");

    return 0;
err_free_module:
    kfree(dev);
    return ret;
}

/**
 * @brief Remove function for SPI driver
 * @param spi SPI device
 * @return 0 on success
 */
static int ili9341_remove(struct spi_device *spi)
{
    struct ili9341_device *dev = spi_get_drvdata(spi);
    
    /* Clean up character device */
    device_destroy(dev->class, dev->dev_num);
    class_destroy(dev->class);
    cdev_del(&dev->cdev);
    unregister_chrdev_region(dev->dev_num, 1);
    
    // /* Free display buffer */
    // if (dev->display_buffer)
    //     kfree(dev->display_buffer);
    
    dev_info(&spi->dev, "ILI9341 display removed\n");
    
    return 0;
}

/* Device tree match table */
static const struct of_device_id ili9341_of_match[] = {
    { .compatible = "ili9341", },
    { },
};
MODULE_DEVICE_TABLE(of, ili9341_of_match);

/* SPI driver structure */
static struct spi_driver ili9341_driver = {
    .driver = {
        .name = DRIVER_NAME,
        .of_match_table = ili9341_of_match,
        .owner = THIS_MODULE,
    },
    .probe = ili9341_probe,
    .remove = ili9341_remove,
};

module_spi_driver(ili9341_driver);

MODULE_AUTHOR("Tan Tai Kieu");
MODULE_DESCRIPTION("Character Device Driver for ILI9341 TFT LCD");
MODULE_LICENSE("GPL");