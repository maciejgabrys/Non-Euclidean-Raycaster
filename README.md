# Non-Euclidean Raycaster Engine
A non-Euclidean raycaster engine written in C++ and SFML.

## Demonstration
Click to view on YouTube:

[![video](https://img.youtube.com/vi/FhbtU5MOVgA/0.jpg)](https://www.youtube.com/watch?v=FhbtU5MOVgA)

## Achtung!
A few things about this project:
* it does not include rendering floors, ceilings or sprites (yet);
* it is not optimized for performance (to keep the code more readable).

## Building
If you want to use the Visual Studio 19 solution then download and unpack SFML v2.5.1 to C:\SFML\

## How does it work?
Paradoxically, it is not extremely complicated. It is just using a graph instead of the two-dimensional array. Renderer teleports a casted ray between nodes (and some of them are connected in a weird way). The rest is just like in Wolfenstein 3D.
