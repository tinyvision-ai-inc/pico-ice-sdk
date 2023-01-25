# Spresense exported SDK

Prepared and exported Spresense SDK. To reproduce this, follow the steps below.

## Step 1 - Clone Spresense SDK

    $ git clone --recursive https://github.com/sonydevworld/spresense.git
    $ cd spresense/sdk

## Step 2 - Configure Spresense SDK

    $ tools/config.py -d <path to CircuitPython>/ports/cxd56 circuitpython

## Step 3 - Build and export Spresense SDK

    $ make
    $ make exportsdk

## Step 4 - Extract Spresense SDK and change the name of the folder

    $ tar xvzf sdk-export.tar.gz
    $ mv sdk-export spresense-exported-sdk

## Step 5 - Modify Spresense SDK

In file `spresense-exported-sdk/nuttx/include/nuttx/fs/fs.h` (line 817) comment

    // int file_open(FAR struct file *filep, FAR const char *path, int oflags, ...);
