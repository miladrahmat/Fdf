<p align="center">
<img src="https://github.com/user-attachments/assets/3966bdaf-3b1c-48f7-877c-ab8a11b492c8">
</p>
<p align="center">
<img src="https://github.com/miladrahmat/42-badges/blob/master/badges/fdfm.png"><img width="144" src="https://github.com/user-attachments/assets/4e035140-2413-4531-9f91-1bc869bdf4ef">
</p>
<p align="center">
<b>The first graphical project at the 42 network</b>
  
#
## Content
- [Introduction](#introduction)
- [Examples](#examples)
- [Bonus](#bonus)
- [Installation](#installation)

## Introduction

The goal of this project is to introduce you to computer graphics, and especially rendering and transformations. Basically we are given a map as a file, and are tasked to transform that map into a 2D graphical representation.

For this project, I utilized the [MLX42](https://github.com/codam-coding-college/MLX42) library, which is a modern, student-made alternative to MiniLibX — a graphical library that offers essential tools for opening windows, creating images, and handling keyboard and mouse events.

I chose MLX42 over MiniLibX because it is actively maintained, well-documented, performs efficiently, and is cross-platform, ensuring compatibility with various operating systems.

## Examples

Example map:

```
0 0 0
0 10 0
0 0 0
```
Executing the program using the example map:
```
./fdf example_map.fdf
```

The map is displayed in a window in isometric projection:

![Screenshot from 2024-08-27 11-59-53](https://github.com/user-attachments/assets/5d5414f4-1c60-4723-b1e2-b3f68b6b5c5f)

A map has the following rules:
- A map has to be stored in a `.fdf` file.
- A map has to be a rectangle.
- The horizontal position corresponds to its axis.
- The vertical position corresponds to its ordinate.
- The value corresponds to its altitude.

You can also create maps with custom colors by specifying colors as hexadecimal numbers in your map file. For example:
```
0,0x810202 0,0x810202 0,0x810202
0,0x810202 10,0xFFFFFF 0,0x810202
0,0x810202 0,0x810202 0,0x810202
```

This allows you to control the color of each point on the map. The program will display your map using gradient colors for enhanced visual depth.

![image](https://github.com/user-attachments/assets/3d325b37-0850-4ad9-8f58-3633e42c5aee)

## Bonus

For the bonus part of the project, the following features were implemented:
- Added an additional projection mode.
- Enabled zoom functionality to allow zooming in and out.
- Implemented model translation for repositioning the model.
- Integrated model rotation for dynamic viewing.

As an extra bonus, I included an introduction section within the window itself, providing users with instructions on which keys can be pressed for interaction. Additionally, I added the ability to resize the window for a more flexible user experience.

## Installation

To test the program, you'll need to follow the setup instructions provided in the official [MLX42 repository.](https://github.com/codam-coding-college/MLX42?tab=readme-ov-file#general-compilation) Once the library is successfully compiled on your system, you can compile the program with the following commands:
```
git clone https://github.com/miladrahmat/Fdf.git
cd Fdf
make
```

After compiling, you can run the program using maps that you create. Refer to the examples provided [here](#examples) for guidance on how to format your own maps.
