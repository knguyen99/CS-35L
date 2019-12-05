Khoi Nguyen
#########
readme.txt

The goal of the implementation I wrote was to create a program
that run faster through multithreading. Because each pixel's 
rendering is independent of the rest of the pixels, multithreading
works well. 

A few of the problems I ran into with my implementation was
forgetting to print a new line character after the pixel.
Furthermore, I noticed that in the loop inside the function that
I wrote, I was incrementing px by 1. This produced incorrect 
data, thus I incremented by nthreads so that each thread
would not work over the same pixels.

With 2 threads, performance compared to 1 thread, the real time
decreased to about 1/2 of 1 thread real time. With four threads, the 
real time decreased to about 1/4 of the 1 thread real time. With 8
threads, the real time was decreased to about 1/8 of 1 thread real
time. The correlation is that with x threads, the real time is reduced
to 1/x. 
