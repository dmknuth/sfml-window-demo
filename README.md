# Window Demo using the SFML framework

## For macOS.

1. Install SFML and CMake, if needed
2. After cloning this repo, build it with
   ```
   cmake -B build
   cmake --build build
   ```
3. Launch it with these optional arguments
    ```
    build/bin/WindowDemo -x 1400 -y 900 -a 10.0 -c 100 -r 40 -g

    build/bin/WindowDemo -h
    usage:
    -a set the antialias amount.  The higher the number, the fuzzier the edges of the objects. The default is 1.1.
    -c set the number of objects to create. The default is 1.
    -g to display a grid. The default is no grid.
    -h or any other character to display this message.
    -r set the radius of the objects. The default is 20.
    -v display version of this application.
    -x set the width of the window to create. The default is 640.
    -y set the height of the window to create. The default is 480.
    ```
It should look like this.
![Alt text](https://github.com/dmknuth/sfml-window-demo/blob/main/doc/screenshot.png "screenshot")
4. Enjoy!

## License

The source code is dual licensed under Public Domain and MIT -- choose whichever you prefer.
