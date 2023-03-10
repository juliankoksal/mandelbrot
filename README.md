# Mandelbrot Set Plotter

This program plots the Mandelbrot set and Julia sets using OpenGL.

<img src="images/mandelbrot.png" width=400>

You can explore the set by moving the view around and zooming in and out.

<img src="images/mandelbrot_zoom.gif" width=400>

Click any point on the Mandelbrot set to plot the Julia set for that point.

<img src="images/julia1.png" width=200>
<img src="images/julia2.png" width=200>
<img src="images/julia3.png" width=200>
<img src="images/julia4.png" width=200>

Author: Julian Koksal

Date: 2022-02-12

## How to build

Target platform is ARM64 MacOS with GLFW installed via Homebrew.

`CXXFLAGS`, `LDFLAGS`, and `LDLIBS` in the Makefile will need to be changed to build on other platforms.

### Dependencies

- OpenGL
- GLFW


### Configuration

`Constants.hpp` defines some configuration constants which can be adjusted to improve quality or increase performance.

### To build:

```
make
```

## How to use

### To run:

```
./Main
```
### Controls

Use the arrow keys to move the view around.

Use `x` to zoom in and `z` to zoom out.

Use `escape` to reset the view.

Left click on any point to plot the Julia set for that point. Left click again to plot the Mandelbrot set again.
