/* based on code posted at: http://stackoverflow.com/questions/15031983/usb-webcam-image-capture-in-c-without-opencv-linux */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <getopt.h>             /* getopt_long() */

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>

#define CLEAR(x) memset (&(x), 0, sizeof (x))

static int xioctl(int fh, int request, void *arg)
{
    int r;
    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);
    return r;
}

void allocCamera(const char* file) 
{
    struct v4l2_capability cap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;

    int camera_fd = open(file, O_RDONLY);

    if (-1 == xioctl (camera_fd, VIDIOC_QUERYCAP, &cap)) {
        if (EINVAL == errno) {
            fprintf (stderr, "%s is no V4L2 device\n", file);
            exit (EXIT_FAILURE);
        } else {
            printf("\nError in ioctl VIDIOC_QUERYCAP\n\n");
            exit(0);
        }
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        fprintf (stderr, "%s is no video capture device\n",
                file);
        exit (EXIT_FAILURE);
    }

    if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
        fprintf (stderr, "%s does not support read i/o\n",
                file);
        exit (EXIT_FAILURE);
    }

    CLEAR(fmt);

    fmt.type    = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = 640; 
    fmt.fmt.pix.height      = 480;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
    
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
    //fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;

    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;
    if (-1 == xioctl(camera_fd, VIDIOC_S_FMT, &fmt)) {
        printf("VIDIOC_S_FMT");
    }
}
