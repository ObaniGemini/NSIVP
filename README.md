# NSIVP

A yet unworking replacement library for SIVP on scilab, using SDL



Using SDL2, [stb_image.h](https://github.com/nothings/stb#stb_libs) and [stb_image_write.h](https://github.com/nothings/stb#stb_libs)



## Short description

- `initNSIVP()` : init all the subsystems needed for NSIVP to display windows.

- `exitNSIVP()` : exit all the subsystems needed for NSIVP to display, then quitting.

- `storeImage( path )` : store an image in an Image struct, returning it

- `storeHistogram( image )` : store an histogram in an Histogram struct, based off an Image struct, returning it.

- `allocImage( width, height, chans )` : allocate space for an image of size **width** x **height** with **chans** channels per pixel.

- `freeImage( image )` : free the content of an Image struct, returns nothing ( the image needs to be a pointer )

- `saveImage( path, image )` : save **image** at **path**. **path** needs to contain an explicit picture format at the end (supported formats are *png*, *bmp*, *tga* and *jpg*)

- `displayImage( image )` display **image** in an SDL movable window. F12 to save the image.

- `displayHistogram( histogram )` display **histogram** in an SDL movable window. F12 to save the image.