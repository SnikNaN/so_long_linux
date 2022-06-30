# so_long_linux
## <42 School> project "so_long" linux port

## 2D arcade game
Written in **C** with modified **[MiniLibX](https://github.com/42Paris/minilibx-linux)** graphics library *(which is API to X11)* and **[cute_png](https://github.com/RandyGaul/cute_headers/blob/master/cute_png.h)** library.


### Installation:

*Prereqs: X11 lib + libxext-dev + libxrender-dev + libxrandr-dev*
```
git clone https://github.com/SnikNaN/so_long_linux.git ; cd so_long_linux ; make bonus
```
### Usage:

- **To run:** ./so_long map.ber
- **Controls:** **WASD** for *moving*, **Esc** for *exit*
- **The goal** is to collect all the **eggs** and return to the **nest**, *avoiding contact with other birds*
- You may use **trees** of specific **colour** *(which is randomly generated at start)* as **shelter**

![Screenshot](https://github.com/SnikNaN/so_long_linux/blob/main/screenshot.png "so_long")
