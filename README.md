# Fract-ol

A beautiful fractal visualization program that renders Mandelbrot and Julia sets with stunning colors and smooth animations.

## 🌟 Features

- **High-quality fractal rendering** with smooth color transitions
- **Interactive exploration** with zoom and pan controls
- **Multiple color schemes** - Psychedelic, Sunset, and Ocean themes
- **Real-time parameter adjustment** for Julia sets
- **Optimized performance** for smooth user experience

## 🎯 Supported Fractals

### Mandelbrot Set
The iconic fractal defined by the iterative formula: z = z² + c

### Julia Sets
Beautiful fractal patterns with customizable complex parameters

## 🎮 Controls

| Key/Action | Function |
|------------|----------|
| `ESC` | Exit program |
| `↑↓←→` | Pan/move view |
| `Mouse Wheel` | Zoom in/out (centered on cursor) |
| `+/-` | Increase/decrease iteration count |
| `R` | Reset view to default |
| `C` | Cycle through color schemes |

## 🚀 Usage

```bash
# Compile
make

# Display Mandelbrot set
./fractol mandelbrot

# Display Julia set with custom parameters
./fractol julia <real_part> <imaginary_part>

# Examples of beautiful Julia sets
./fractol julia -0.7 0.27015
./fractol julia -0.8 0.156
./fractol julia -0.4 0.6
./fractol julia 0.285 0.01
```

## 🎨 Color Schemes

1. **Psychedelic** - Vibrant rainbow gradients with high contrast
2. **Sunset** - Warm colors transitioning from purple to red to yellow
3. **Ocean** - Cool blue tones reminiscent of deep ocean depths

## 🛠️ Technical Details

### Requirements
- Linux/Unix environment
- X11 development libraries
- Math library support
- C compiler (gcc)

### Dependencies
- **MinilibX** - Graphics library for window management and rendering
- **libft** - Custom C utility library
- **X11 libraries** - For display functionality

### Installation
```bash
git clone <repository>
cd fract-ol
make
```

## 🔧 Implementation Highlights

- **Smooth coloring algorithm** for eliminating color banding
- **Optimized calculation loops** with early escape conditions  
- **Precise zoom positioning** centered on mouse cursor
- **Memory-safe operations** with proper cleanup
- **Input validation** for robust error handling

## 🎯 42 School Compliance

- ✅ **Norminette** compliant code
- ✅ **Memory leak free** (valgrind tested)
- ✅ **Error handling** for all edge cases
- ✅ **Makefile** with standard rules
- ✅ **No forbidden functions** used

## 📊 Performance

- Efficient calculation with squared term reuse
- Smooth real-time zooming up to extreme magnifications
- Responsive controls even at high iteration counts
- Optimized color computation algorithms

## 🐛 Troubleshooting

**Program won't start:**
- Ensure X11 libraries are installed
- Check display environment variable: `echo $DISPLAY`

**Julia set parameters not working:**
- Parameters must be valid decimal numbers
- Use format: `./fractol julia -0.7 0.27015`

**Performance issues:**
- Lower iteration count with `-` key
- Reset zoom level with `R` key

## 🎉 Fun Facts

- The Mandelbrot set boundary has infinite complexity
- Julia sets are named after mathematician Gaston Julia
- Fractals exhibit self-similarity at different scales
- The color schemes use mathematical functions for smooth transitions

## 👨‍💻 Author

**mirokugo** - 42 Tokyo Student

---

*Explore the infinite beauty of mathematics with fract-ol!* ✨