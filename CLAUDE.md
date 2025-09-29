# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview
This is a fract-ol project, a fractal visualization program that renders Mandelbrot and Julia sets using the MinilibX graphics library. This appears to be a 42 School project.

## Project Requirements (from docs/dev_design.md)

### Rendering Requirements
- Must handle Julia and Mandelbrot sets
- Mouse wheel zoom in/out (nearly infinite within computer limits)
- Zoom centered on click position
- Different Julia sets via command-line parameters
- Multiple colors to represent fractal depth (psychedelic effects encouraged)

### Display and Event Requirements
- Smooth window management (switching, minimizing)
- ESC key closes window and exits cleanly
- Window X button closes and exits cleanly
- Must use MiniLibX image functions

### Command-Line Parameters
- Specify fractal type to display
- Additional parameters for rendering options
- Display usage and exit cleanly on invalid/missing parameters

## Build Commands
```bash
# Build the project
make

# Clean object files
make clean

# Clean everything including the binary
make fclean

# Rebuild from scratch
make re
```

## Running the Program
```bash
# Run Mandelbrot fractal
./fractol mandelbrot

# Run Julia fractal with parameters
./fractol julia <real_part> <imaginary_part>

# Example Julia set
./fractol julia -0.7 0.27015
```

## Project Structure
- **srcs/**: Source files directory
  - `main.c`: Entry point, argument parsing, and usage display
  - Expected files (referenced in Makefile but not yet created):
    - `mandelbrot.c`: Mandelbrot set rendering implementation
    - `julia.c`: Julia set rendering implementation
    - `burning_ship.c`: Burning Ship fractal implementation
    - `utils.c`: Utility functions
    - `hooks.c`: MLX event hooks (keyboard, mouse)
    - `colors.c`: Color palette and rendering functions

- **includes/**: Header files
  - `fractol.h`: Main header with function prototypes and includes

- **libft/**: Custom C library (42 School requirement) - currently empty
- **mlx/**: MinilibX graphics library (needs to be added)

## Dependencies
- MinilibX library (X11 implementation)
- X11 libraries: `-lXext -lX11`
- Math library: `-lm`
- Zlib: `-lz`
- libft library (needs to be populated)

## Development Notes
- The project uses 42 School's coding standard (visible in file headers)
- Compilation flags: `-Wall -Wextra -Werror`
- Functions from libft are expected (ft_strncmp, ft_atof, ft_putstr_fd, ft_printf)
- Japanese comments in the header file indicate placeholder sections for constants, structures, enums, typedefs, and macros

## Missing Components
Before the project can compile:
1. Populate the libft directory with the required library
2. Add the MinilibX library to ./mlx/
3. Implement the missing source files referenced in the Makefile
4. Implement ft_atof function (not standard in libft)

## Function Prototypes
Current function declarations in fractol.h:
- `void print_usage(void)`: Display program usage
- `int run_mandelbrot(void)`: Initialize and run Mandelbrot visualization
- `int run_julia(double real, double imag)`: Initialize and run Julia visualization with given parameters

## Allowed Functions
Standard library functions: open, close, read, write, malloc, free, exit, perror, strerror, gettimeofday
Math library: All functions
libft: Custom library functions
ft_printf: Custom printf implementation
MiniLibX: mlx_init, mlx_loop, mlx_loop_hook, mlx_new_window, mlx_destroy_window, mlx_new_image, mlx_get_data_addr, mlx_put_image_to_window, mlx_destroy_image, mlx_pixel_put, mlx_string_put, mlx_hook