# Window Demo using the SFML framework

## For macOS

1. Install SFML
2. After cloning this repo, build it with
   ```
   cmake -B build
   cmake --build build
   ```
3. Launch it with these optional arguments
    ```
    build/bin/WindowDemo -x 1400 -y 900 -a 2.0 -c 2000 -r 10 -g 
    ```
    where -x is the width of the window to create
    -y is the height of the window to create
    -a is the antialias amount.  The higher the number, the fuzzier the edges of the objects
    -c is the number of objects to create
    -r is the radius of the objects
    -g displays a grid
9. Enjoy!

## License

The source code is dual licensed under Public Domain and MIT -- choose whichever you prefer.
