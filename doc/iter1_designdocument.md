# Design Justifications for BrushWork
#### Group Name:
Bits Please

#### Members:
- Liam Tyler
- Jess Henderson
- Shashank Yallamraju


## 1  Design Question One
### 1.1 Design Description
> In our final design we viewed tools as a form of specialization. The main two features of any tool are: it has a mask, and that mask can be applied to the screen in some way. We created a base class called Tool that creates a default mask and default ApplyTool behavior. We then created subclasses for each one of the six tools, which would initialize the mask to be specific to that tool, and change the ApplyTool behavior as necessary. This design is shown in Figure 1.1.

###### Figure 1.1: UML diagram of the tools
![Tools UML][ToolsUML]

> There are a few key design choices here. First, notice how half of the tools do not override the ApplyTool method from the parent class. This is because the default ApplyTool is generic. Observe the implementation below:

###### Figure 1.2: ApplyTool() for Tool (tool.cc).
```C++
void Tool::ApplyTool(PixelBuffer* buff, ColorData current_color, int x, int y) {
    int mid_x = width_ / 2;
    int mid_y = height_ / 2;
    int screen_h = buff->height();
    int screen_w = buff->width();

    for (int step_x = 0; step_x < width_; step_x++) {
        for (int step_y = 0; step_y < height_; step_y++) {
            int cur_x = x + step_x - mid_x;
            // Account the Y axis being inverted between the buffer and screen
            int cur_y = screen_h - (y + step_y - mid_y);
            if (cur_x >= 0 && cur_x < screen_w && cur_y >= 0 && cur_y < screen_h) {
                    double intensity = mask_[step_x][step_y];
                    buff->set_pixel(cur_x, cur_y, current_color * intensity +
                                    buff->get_pixel(cur_x, cur_y) * (1.0 - intensity));
            }
        }
    }
}
```

> It takes the assumption that the mask is already created, and just needs to be applied with the current color to the screen. It centers the mask over where the mouse is, and then for each pixel of the mask, sets the corresponding pixel on the screen according to the formula given above in set_pixel. For many tools, this is all that is needed, but for other ones like the eraser, rainbow, and highlighter, the method is virtual so those classes can override it with new behavior as needed.

> The next key design point was how we handled our masks. Our masks are 2D float arrays, where each element in the array corresponds to one pixel of the mask, and where the value of the floating point number is how intense we want that pixel to be (0.0 is transparent, and 1.0 is completely opaque). Each tool will specialize the design of the mask, but the first step is that the mask is created in memory at all. To do this, we made this 2D array a member variable of our Tool class, and allocate memory for the mask in the Tool constructor:

###### Figure 1.3: Tool Constructor (tool.cc).
```C++
Tool::Tool(int width, int height) {
    width_ = width;
    height_ = height;
    // Allocate the memory for the 2d mask with height rows and width columns
    mask_ = new double*[height];
    for (int i = 0; i < height; i++) {
         mask_[i] = new double[width];
    }
}
```

> We designed our tools so that every tool will first call the parent constructor to allocate the mask, then each tool will specify the design on that mask. For example, take the pen:

###### Figure 1.4: Pen Constructor (pen.cc).
```C++
Pen::Pen(int width, int height) : Tool(width, height) {
    radius_ = static_cast<double>(width) / 2;
    tool_utilities::CreateCircle(this->getMask(),
                                height,
                                width,
                                radius_);
}

Pen::Pen() : Pen(3, 3) {}
```

> When instantiating a pen, the Tool constructor is called first, then the rest of the pen constructor is to initalize the mask. If the mask was a design that might be desired for multiple tools, we separated out the initialization of the mask from the tool itself into a function. We store these functions in a namespace called tool_utilities. Here, the pen is initialized to an opaque circle.

> The last thing to note is the interpolation of points when the user is moving the mouse quickly. Our ApplyTool methods are designed to handle a single stamp down on the screen. The interpolation part happens in the mouse dragged event of brushwork_app.


### 1.2 Design Justification
> Our goals for this design were: to create a system of tools where common behavior is shared, high simplicity, high understandability, and high extendability for adding new tools. We believe that the design explained above is an effective in accomplishing those goals, and superior compared to other designs.

> The first decision in our design was to views tools as a specialization of a generic tool. To examine why this is effective, note again that the main abstractions of tools are their mask, and how it's applied. Every single tool is going to need a mask, and that mask to be allocated in memory. So, as seen in the tool constructor in figure 1.3, it makes sense to have that mask allocation in the Tool class. We decided to have the mask directly in the Tool class as a 2D floating array, and then have functions that initialize the masks. One counter argument to this approach could be: why not encapsulate masks into their own class? Wouldn't it be better to do that, so that future changes to mask are separated from the Tool class? Well, we didn't think it was worth it.

> The reason for that lies in the fact that one major aspect of software design, is to identify the parts of your design that are likely to change. The key thing here is that we do not forsee many changes happening to the mask. If in the future the mask suddenly needs several added features, then yes, it probably would be better to have a looser coupling between the tools and their masks. As of now though, a mask is really just a container for the intensity and shape. Since we do not believe that is likely to change, we keep it in the Tool. This is beneficial because it gives us higher cohesion; each tool, by itself, has everything a tool needs to function. Yes this causes higher coupling between the mask and ApplyTool method, but we believe that our design still maintains high simplicity and understandability, which were major goals for our design.

> The next major decision we made was on how we initialize the masks. Many of the tools have similar shapes (either circle or rectangle). We decided to make a namespace called tool_utilities, and put functions in here that many of the tools might want to use. As seen below in figure 1.5, we put functions CreateCircle and FillMask in here.

###### Figure 1.5: Tool Utilities (tool_utilities.h).
```C++
namespace tool_utilities {
    void CreateCircle(double** mask, int height, int width, double radius);
    void FillMask(double** mask, int height, int width, double opacity);
}
```

> We call these functions in our tool constructors to intialize the masks. This has the advantage of avoiding code duplication, since the functions are only written once. In fact, only the spray can doesn't use one of these functions, because it has the unique linear falloff aspect. Another counter argument might be again, why not just have a class for cicle masks, and another for rectangular masks? The problem with that is that it limits these functions to just masks. With our design, these functions can be applied to any 2D array. With very little modification, we could make our functions work on the screen itself. This might be useful in the future if we need to draw shapes on the screen, as many photoshop programs allow you to do that.

> The next decision was to have the ApplyTool method have a default implementation in the Tool class. The pro with this is that it avoids code duplication. Most masks, once they are created, merely need to be stamped onto the screen. Half of our tools (rainbow, highlighter, and eraser) override the default ApplyTool method, but even then, most of them barely have to make any modification. Take figure 1.6 as an example.

###### Figure 1.6: Rainbow's ApplyTool (rainbow.cc).
```C++
void Rainbow::ApplyTool(PixelBuffer* buff, ColorData current_color,
                        int x, int y, int last_x, int last_y) {
    double new_r = current_color.red();
    double new_g = current_color.green();
    double new_b = current_color.blue();
    this->UpdateColor(&new_r, &new_g, &new_b);
    ColorData new_c = ColorData(new_r, new_g, new_b);

    this->Tool::ApplyTool(buff, new_c, x, y, last_x, last_y);
}
```

> As shown above, the Rainbow's ApplyTool merely makes a small change ('rainbow-fying' the color) and then the mask and color are all ready to be stamped, so it calls the default ApplyTool. Designing our ApplyTool this way allows for high extensibility, and low code duplication.

> The last design aspect mentioned, was the decision to implement the interpolation in brushwork_app's MouseDragged method. This is effective because the interpolation is independent of what tool is selected. It's merely fixing the illusion that the every pixel is hit when dragging the mouse, and has no real relation to a tool itself. All that has to be done is repeated calls to ApplyTool, so it makes sense that it is outside the scope of our tool design, and handled in brushwork's MouseDragged.


## 2  Design Question Two
### 2.1 Design Description
> We decided to make Eraser a subclass of Tool so that the Eraser would have an ApplyTool() method just like the other tools. The only difference is that the Eraser applies the background color instead of the current color selected by the user. To accomplish this, Eraser overrides the ApplyTool() method, as shown in Figure 2.1 below. Instead of applying the tool with the current_color, Eraser applies iteself with the background_color.

###### Figure 2.1: ApplyTool() for the Eraser (eraser.cc).

```C++
void Eraser::ApplyTool(PixelBuffer* buff, ColorData current_color,
                        int x, int y, int last_x, int last_y) {
    this->Tool::ApplyTool(buff, buff->background_color(), x, y, last_x, last_y);
}
```

> In main, the BrushWorkApp passes the background color to the Init function, which initializes the pixel buffer by calling InitializeBuffers as shown in Figure 2.2 below.

###### Figure 2.2: Init() for the BrushworkApp (brushwork_app.cc).

```C++
void BrushWorkApp::Init(
    int argc,
    char* argv[],
    int x,
    int y,
    ColorData background_color) {

    BaseGfxApp::Init(argc, argv,
                     x, y,
                     GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                     true,
                     width()+51,
                     50);

    // Set the name of the window
    set_caption("BrushWork");

    // Initialize Interface
    InitializeBuffers(background_color, width(), height());

    InitGlui();
    InitGraphics();
}
```

> The method InitializeBuffers() uses the background_color to create a new PixelBuffer called display_buffer_ as shown in Figure 2.3 below.

###### Figure 2.3: InitializeBuffers() for the BrushworkApp (brushwork_app.cc).

```C++
void BrushWorkApp::InitializeBuffers(
    ColorData background_color,
    int width,
    int height) {
    display_buffer_ = new PixelBuffer(width, height, background_color);
}
```

> We get the background color by calling pixel_buffer's background_color() method, shown below in Figure 2.4, on display_buffer_.

###### Figure 2.4: background_color() for the PixelBuffer (pixel_buffer.cc).

```C++
 /**
   * @brief Get the background color that was used to initialize the PixelBuffer
   * @return The background color
   */
  ColorData background_color(void) { return *background_color_; }
```

### 2.2 Design Justification
> Rather than setting the Eraser to a certain color, we decided to get the background_color_ from the PixelBuffer using the background_color() method. This way, no matter what color the background gets set to initially, Eraser will use the correct color. One con is that if the background color was somehow changed while the program was running, Eraser would still use the initial background color. Since there isn't a way for the user to change the background color, we decided getting the initial color would be sufficient at this point. In the future, if we add a way for the user to change the background color, we could add an update_background_color() method that would update the background_color_ in the PixelBuffer.

> Our first implementation of the Eraser involved an if statement within MouseDragged() that determined whether or not the cur_tool_ was the Eraser. If cur_tool_ was the Eraser, current_color_ got changed to the background_color_ rather than the color selected by the user. We decided this was a bad design because anytime you added another tool that used a color other than current_color_, you'd need to add to the if statement. For example, our additional tool is the Rainbow tool, which applies colors to the window in a rainbow pattern.

> Instead of using an if statement within MouseDragged(), we decided to make tool's ApplyTool() method virtual. This way, we could override ApplyTool() when necessary. In the Eraser's ApplyTool() method, we call Tool's ApplyTool() method, since the only difference is the color that gets applied. Making the ApplyTool() method virutal was useful for the Rainbow tool as well as the highlighter.

> By changing the color to be applied within the Eraser class, we do not have to change anything in brushwork_app. As shown below in Figure 2.5, within MouseDragged(), we can simply call ApplyTool() on whatever tool is the cur_tool_, and the tool will be applied properly.

###### Figure 2.5: MouseDragged() for the BrushWorkApp (brushwork_app.cc).

```C++
void BrushWorkApp::MouseDragged(int x, int y) {
    if (last_x_ != -1) {
        /* Find the distance between (last_x_, last_y_) and (x, y) and divide by
        an eigth of the width of the mask to determine the number n times to
        ApplyTool between (last_x_, last_y_) and (x, y) */
        int n = sqrt(pow((last_x_ - x), 2) +
                pow((last_y_ - y), 2))/(cur_tool_ -> get_width() / 8.0);
        float percent_step = 1.0/static_cast<float>(n);
        int base_x = last_x_;
        int base_y = last_y_;
        float dx = x - base_x;
        float dy = y - base_y;

        for (float i = percent_step; i < 1.0; i+=percent_step) {
            int new_x = base_x + (i * dx);
            int new_y = base_y + (i * dy);
            cur_tool_->ApplyTool(display_buffer_, current_color_, new_x, new_y,
                                 last_x_, last_y_);
            last_x_ = new_x;
            last_y_ = new_y;
       }
    }

    cur_tool_->ApplyTool(display_buffer_, current_color_, x, y,
                         last_x_, last_y_);

    last_x_ = x;
    last_y_ = y;
}
```

## 3  Design Question Three
### Programming Tutorial: Adding a New Pencil Tool to BrushWork


> In this tutorial we will walk through how to add a new tool to Brushwork. We will accomplish this feat in four steps and use the tool of pencil as an example.

1) Create a mask of the tool in tool_utilities

> To start, we first need to make a mask of the tool that we would want to create. For the example of the pencil, we will just make it a single, non-transparent pixel that completely replaces the existing colors on the canvas. Since pencil has a similar shape mask to the caligraphy pen, all we need to do is use that same function but tinker with the width and height.

``` C++
void FillMask(double** mask, int height, int width, double opacity) {
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                mask[h][w] = opacity;
            }
        }
    }
```
    
> The snippet of code above makes a rectangular shape mask and sets the opacity to any value we would like. The pencil mask fits this desription which saves the hassle of making a specific mask just for pencil. Something to note, we could just make a default constructor for the pencil that sets the width and height both to one, but we choose to not have one in order to have the freedom to change the size of the pencil mask if we wanted.


2) Create .h file for the tool in include 

> Next, we need to create a header file for the tool. The header file will define the parameters that are needed by the tool. In the case of the pencil tool, we will need the width and height.

``` C++
#include "include/tool.h"

class Pencil : public Tool {
 public:
  Pencil(int width, int height);
  Pencil();
  ~Pencil();
};
```

> Since we already have tool.h which provides a basic outline of any tool, we extended from tool.h to get the width and height as seen from the snippet of code above.

3) Create .cc file for the tool in src

> Now, we must create the .cc file for the tool. This is where we will set the height and width of the tool along with any other variables that the tool may need. This file will also call the function we created specifically for the new tool. With the example of pencil, we will need to set the height and width both to 1 and call the FillMask() fucntion that we made earlier.

```C++
Pencil::Pencil(int width, int height) : Tool(width, height) {
    tool_utilities::FillMask(this->get_mask(), height, width, 1.0);
}

Pencil::Pencil() : Pencil(1, 1) {}
```

> There are a couple things to note from the snippet of code above. One: to meet the requirments that the pencil be a single pixel, we set both the height and width to 1, but this is where we can change the size of the pencil if we want it to be different than a single pixel. Two: we call FillMask() from tool_utilities in order to access the premade mask.

4) Add tool into the tool array in brushwork_app

> Finally, the last step we need to complete is to add the new tool into the array of current tools be used. The current tools being used are stored in brushwork_app in an array called tool_select_. Here, the new tool will be assigned a number and this number will be used to determine the current tool being used.

```C++
tool_select_[0] = new Pen();
tool_select_[1] = new Eraser();
tool_select_[2] = new SprayCan();
tool_select_[3] = new Caligraphy();
tool_select_[4] = new Highlighter();
tool_select_[5] = new Rainbow();
tool_select_[6] = new Pencil();
cur_tool_ = tool_select_[0];
```

> The portion of code from  brushwork_app above demonstrates that pencil gets assigned a number 6 which is used to identify the tool. This is how we keep track of the tools. Also, in burshwork.h we will need to make the array one size larger to accommodate for the new tool. 

[ToolsUML]: https://github.umn.edu/umn-csci-3081F16/repo-group-Bits-Please/blob/develop/doc/figures/tools.png
