# Filter
A program that applies 4 types of filters to BMPs

Try compiling filter for yourself by going to your terminal and running

$ make filter
Then, you can run the program by running:

$ ./filter -g images/yard.bmp out.bmp <br>
which takes the image at images/yard.bmp, and generates a new image called out.bmp after running the pixels through the grayscale function. grayscale doesn’t do anything just yet, though, so the output image should look the same as the original yard. Instead of -g (grayscale), you can use -s, -r, -b for (sepia, reflect, and blur).

$ make recover <br>
$ ./recover card.raw <br>
