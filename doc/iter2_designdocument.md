# Design Justifications for FlashPhoto
#### Group Name:
Bits Please

#### Members:
- Liam Tyler
- Jessica Henderson
- Shashank Yallamraju

#### Instructions 
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.  
> A few tips to maximize the success of your design document:  
>   1. Make sure the **description** of your design decision only contains an objective description of how you structured your design and how it was implemented (specifically how your solution solves the problem given in the prompt). Save any arguments in favor of your design for the **justification** section.
>
>   2. Your justification will probably need to compare against at least one alternative, and you will need to provide a compelling argument for why your solution is better than the alternative.
>
>   3. Edit this file when writing your design document. Do not move or rename this file. Do not direct to any outside resources for your images or code. Place all images and code in this document. Please match the formatting of the [Example Design Document](https://github.umn.edu/umn-csci-3081F16/Example-Design-Document/blob/master/doc/DesignDocument.md) and [its source](https://raw.github.umn.edu/umn-csci-3081F16/Example-Design-Document/master/doc/DesignDocument.md?token=AAADyd5L8wd57F_qLX4Nf-2nVvfRlMj5ks5YH-qHwA%3D%3D) as precisely as possible, especially in regards to:
>     - **Formatting code** (do not include images of your code, make sure that your code is formatted with C++ coloring)
>     - **Inserting images**
>     - **Numbered lists for your tutorial**
>     - **Captioning your Figures**
>     - **Including the original prompts in their original quote form**  
> 
>  This formatting helps us grade your assignments effectively, and thus failure to meet these requirements may result in point deductions. Any material that is not presented in this design document will not be graded.
>   4. When including a class diagram, only show the classes and members that convey the point you're trying to make. For example, showing the class BaseGfxApp in a UML diagram will probably not be appropriate.





## 1  Design Question One
> This iteration of the project introduces the concept of filters. You had to implement several filters, which fell into two types: pixel-independent (where each pixel is filtered independently), and convolution-based (where filtering a pixel requires information about its neighboring pixels by means of a kernel). Naturally, a key design decision is how these filters are represented. Each filter has a different algorithm for modifying the canvas, and only some of these algorithms require kernels. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description
Our design at the highest level views all filters as the same-- something that takes in the current screen, and creates a new image to be displayed by applying the filter to the old image. To implement this, we created an abstract class as seen in Fig 1. for all filters to derive from.


###### include/invert_filter.h
```C++
class Filter {
 public:
  virtual ~Filter() {}
  virtual void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage) = 0;
  virtual std::string name(void) = 0;
};

```
Notice how all the methods are virtual, and two of them are pure virtual. This class defines the basic interface for all of our filters, but provides none of the details of how that is accomplished. The details of how the "ApplyFilter" method is realized for the two types of filters: pixel-independent, and convolution-based, is handled by our abstract classes: SimpleFilter, and KernalFilter respectively. The class diagrams for these classes are depicted in Fig 2 below.

#INSERT FILTER UML

In order to describe the KernalFilter, the class definition is depicted in Fig 3 below.

###### include/kernal_filter.h
```C++
class KernalFilter : public Filter {
 public:
  explicit KernalFilter(Kernal* kernal);
  virtual ~KernalFilter();
  virtual void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage);
  virtual std::string name(void) = 0;


 private:
  KernalFilter(const KernalFilter &f) = delete;
  KernalFilter& operator=(const KernalFilter &f) = delete;
  Kernal* kernal_;
};

```
 
The main goal of the KernalFilter is to achieve the convolution-based functionality. We approached the problem in the following way, "For each pixel in our display, the new pixel will be composed of its neighboring pixels. We wish to know which neighboring pixels, and how much of each of them to compose our new pixel with." To accomplish this, notice how the KernalFilter class has a Kernal object, which is shown in Fig 4.


###### include/kernal.h
```C++
class Kernal {
 public:
  Kernal(int width, int height);
  Kernal();
  virtual ~Kernal();
  Kernal(const Kernal& k);
  Kernal& operator=(const Kernal& k);
  ColorData ApplyKernal(PixelBuffer* oldimage, int start_x, int start_y);
  void Resize(int width, int height);
  inline int get_width() { return width_; }
  inline int get_height() { return height_; }
  inline float** get_kernal() { return kernal_; }
  void print(std::ostream& out) const;

 protected:
  void AllocateKernal(int width, int height);
  void DeallocateKernal();
  virtual void InitializeKernal() = 0;

 private:
  int width_;
  int height_;
  float** kernal_;
};

```

The Kernal object is a similar to the Mask of Tools in iteration 1. It is composed of a two dimensional array of floats, which is pointed to by the kernal_ variable. Each element in the array is the percentage of that pixel we want for our final pixel. To better see this, observe the ApplyKernal method shown in Fig 5 below.


###### kernal.cc
```C++
ColorData Kernal::ApplyKernal(PixelBuffer* oldimage, int start_x, int start_y) {
    int buff_width = oldimage->width();
    int buff_height = oldimage->height();
    int kern_mid_x = width_ / 2;
    int kern_mid_y = height_ / 2;
    ColorData total;

    total = ColorData(0, 0, 0);
    // Center the kernal over the pixel, and apply it by
    // getting the running total of pixel * intensity
    for (int kr = height_ - 1; kr >= 0; kr--) {
        for (int kc = 0; kc < width_; kc++) {
            int cur_x = start_x + kc - kern_mid_x;
            int cur_y = start_y + (height_ - 1) - kr - kern_mid_y;
            if (0 <= cur_x && cur_x < buff_width &&
                0 <= cur_y && cur_y < buff_height) {
                total = total + oldimage->get_pixel(cur_x, cur_y)
                                * kernal_[kr][kc];
            } else {
                // If the pixel is off the screen,
                // then use the nearest valid pixel
                total = total +
                        oldimage->get_pixel(
                        std::min(buff_width - 1, std::max(0, cur_x)),
                        std::min(buff_height - 1, std::max(0, cur_y)))
                        * kernal_[kr][kc];
            }
        }
    }
    return total.clamped_color();
}
```

Notice that this method takes in the location of the pixel we are currently processing. It then centers the kernal_ array over that location, and loops through each pixel, adding that pixel * corresponding value in our array, and adds it to a running total. This is the value that is returned. 


### 1.2 Design Justification


## 2  Design Question Two
> One common software feature included in this iteration is the undo/redo mechanic, where any modification to the canvas can be reversed, and then optionally re-applied. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description

Below is the UML Diagram that illustrates our HistoryManager design.

###### UML diagram of HistoryManager
![History Manager UML][HistoryManagerUML]

The design we developed in order to implement the undo/redo feature revolves around maintaining a ring buffer. When constructing the HistoryManager object, we create an array of pointers to PixelBuffers of size possible_saves_. If the array becomes full, we save the next PixelBuffer at position 0, which gives us the ring buffer structure.

The HistoryManager class has a SaveCanvas method which gets called each time a filter is applied, an image gets loaded in as the canvas, and the mouse is released. If the next pointer in our ring buffer points to NULL or if the PixelBuffer it points to is the wrong size, we delete it and create a new PixelBuffer of the correct size. Then, we copy the PixelBuffer we want to save onto that PixelBuffer.

For obvious reasons, we have Undo and Redo methods, which get called when the Undo and Redo buttons are pressed. If there is a canvas available at the position in the array before the current canvas being displayed, the user can use Undo, and that PixelBuffer gets copied, returned, and set as the display_buffer_. The only difference in Redo is that we copy the PixelBuffer pointed to by the next pointer in the ring buffer, if available.

We keep track of three values that allow us to correctly allow or disallow the use of the Undo and Redo methods. These values are current_save_, oldest_save_, and newest_save_. We mod these values with possible_saves_ in order to wrap around our ring buffer. The current_save_ is the index of the array which contains the pointer to the current PixelBuffer being displayed. When SaveCanvas is called, we add 1 to current_save_ and set newest_save_ to the value of current_save_, since that save is now the newest. If current_save_ == oldest_save, we have wrapped around the entire ring buffer and need to add 1 to the oldest_save_. The previous oldest_save_ is lost, which is fine since, at most, we only need to be able to undo possible_save_ times. So, if current_save_ is equal to newest_save_, the user cannot Redo. Likewise, if current_save_ is equal to oldest_save_, the user cannot Undo.

### 2.2 Design Justification

As a group, we decided that a ring buffer would be the best design for our HistoryManager class because it was the simplest design we came up with. An alternative we discussed involved using two stacks, rather than a ring buffer. We would have pushed PixelBuffers onto one stack as we saved them. When the user clicked Undo, we would pop a PixelBuffer off of one stack, and push it onto the other. Then, if a user clicked Redo, we would pop the PixelBuffer off of the second stack and push it back onto the first stack.

We saw two challenges with the two stack design that were easily handled with our ring buffer design. The first was that we would have to somehow make sure there was always a blank PixelBuffer at the bottom of the first stack, even if a user clicked Undo all the way back to that PixelBuffer. In our ring buffer design, we have a blank PixelBuffer in the first position of our array, and it never changes. None of the PixelBuffers in our array get changed as we Undo and Redo. They simply get copied over to the display_buffer_.

The second challenge we saw with the two stack design was that it would be more difficult to handle the case where the stack is full and we needed to save another PixelBuffer. In the two stack design, we would have to delete the PixelBuffer at the bottom of the stack and then push the newly saved PixelBuffer onto the top of the stack. In our ring buffer design, when our array is full, we automatically wrap around the ring buffer to position 0, since we mod (current_save_ +1) with possible_saves_.

After comparing the two stack design and the ring buffer design, we decided that the ring buffer was simpler. We thought that the two stack design added unnecessary complexity and had more cons than the ring buffer design.

## 3  Design Question Three
> A new developer on your team must add a new filter to FlashPhoto. This filter is called  _Invert._ This filter performs the following conversion to all pixels in the canvas:
> ```
> newColor's red   = 1 - oldColor's red
> newColor's green = 1 - oldColor's green
> newColor's blue  = 1 - oldColor's blue
> ```
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new filter.

### Programming Tutorial: Adding a New Invert Filter to FlashPhoto

1. Begin by creating an InvertFilter header file called invert_filter.h and place it in the include folder. Since the InvertFilter does not need a kernal, InvertFilter will inherit from the SimpleFilter class. Apart from the usual constructor and destructor, filters need an ApplyToColor method and a name, as shown below.

    ###### include/invert_filter.h
      ```C++
    #ifndef SRC_INCLUDE_INVERT_FILTER_H_
    #define SRC_INCLUDE_INVERT_FILTER_H_

    #include <string>
    #include "include/simple_filter.h"
    #include "include/color_data.h"
    #include "include/pixel_buffer.h"

    using image_tools::PixelBuffer;
    using image_tools::ColorData;

    class InvertFilter : public SimpleFilter {
     public:
      InvertFilter();
      ~InvertFilter();
      float ApplyToColor(std::string, const ColorData& current);
      std::string name(void) { return "Invert"; }
    };

    #endif  // SRC_INCLUDE_INVERT_FILTER_H_

      ```

2. Next, create an InvertFilter C++ file called invert_filter.cc and place it in the src folder. The ApplyToColor method needs to be defined in a way that will give us the desired affect from the filter. ApplyToColor gets applied to each color, red, green, and blue, separately. We check which color got passed in to ApplyToColor, then adjust that color accordingly. In this case, for each color that gets passed in, we return 1.0 - the current color.

    ###### invert_filter.cc
      ```C++
    #include "include/invert_filter.h"
    #include <string>
    #include <iostream>
    #include <iomanip>
    #include "include/tool_utilities.h"

    using image_tools::ColorData;

    InvertFilter::InvertFilter() {}

    InvertFilter::~InvertFilter() {}

    float InvertFilter::ApplyToColor(std::string color,
                                       const ColorData& current) {
        float c;
        
        if (color == "red")
            c = 1.0 - current.red();
        else if (color == "green")
            c = 1.0 - current.green();
        else if (color == "blue")
            c = 1.0 - current.blue();
        else
            std::cerr << "WRONG COLOR INPUT" << std::endl;

        return c;
    }

      ```

3. Third, we need to add the ApplyInvert method to the FilterManager class. In the filter_manager header file, add ApplyFilter as shown below.

    ###### include/filter_manager.h
      ```C++

    ...

    void ApplySpecial(PixelBuffer* oldimage, PixelBuffer* newimage);

    \TODO(Adding A New Filter): Add ApplyInvert here
    void ApplyInvert(PixelBuffer* oldimage, PixelBuffer* newimage);

    ...

      ```

4. Then, add the ApplyInvert method to the filter_manager.cc file in the src folder. Create an InvertFilter object and call the ApplyFilter method. This method is the same for all of the SimpleFilters.

    ###### filter_manager.cc
      ```C++
    ...

    void FilterManager::ApplySpecial(PixelBuffer* oldimage,
                                     PixelBuffer* newimage) {
        std::cout << "Apply has been clicked for Special" << std::endl;
        EmbossFilter emb;
        emb.ApplyFilter(oldimage, newimage);
    }

    \TODO(Adding A New Filter): Add ApplyInvert method here
    void FilterManager::ApplyInvert(PixelBuffer* oldimage,
                                     PixelBuffer* newimage) {
        std::cout << "Apply has been clicked for Invert" << std::endl;
        InvertFilter i;
        i.ApplyFilter(oldimage, newimage);
    }

    ...

      ```

5. Be sure to include the invert_filter.h file at the top of the filter_manager.cc file.

    ###### filter_manager.cc
      ```C++
    ...

    #include "include/quantize_filter.h"
    #include "include/threshold_filter.h"
    #include "include/channels_filter.h"
    #include "include/emboss_filter.h"
    #include "include/saturation_filter.h"
    \TODO(Adding A New Filter): Add include header file here
    #include "include/invert_filter.h"

    ...

      ```

6. Next, you need to add the Filter to the User Interface. In filter_manager.cc, we need to add the InvertFilter panel and Apply button.  

    ###### filter_manager.cc
      ```C++

    ...

    GLUI_Panel *edge_det_panel =
        new GLUI_Panel(filter_panel, "Edge Detect");

    {
        new GLUI_Button(edge_det_panel, "Apply",
                UICtrl::UI_APPLY_EDGE, s_gluicallback);
    }

    \TODO(Adding A New Filter): Add InvertFilter panel and Apply button here
    GLUI_Panel *invert_panel =
        new GLUI_Panel(filter_panel, "Invert");

    {
        new GLUI_Button(invert_panel, "Apply",
                UICtrl::UI_APPLY_INVERT, s_gluicallback);
    }

    ...

      ```

7. In the include/ui_ctrl.h file, add UI_APPLY_INVERT to the Type enum as shown below. UI_APPLY_INVERT must be placed after UI_APPLY_MOTION_BLUR but before UI_APPLY_SPECIAL_FILTER, since the buffers get switched for filters listed between those two filters, inclusively.

    ###### include/ui_ctrl.h
      ```C++


    ...

    enum Type {

    ...

    UI_APPLY_CHANNEL,
    UI_APPLY_QUANTIZE,
    UI_APPLY_MOTION_BLUR,
    \TODO(Adding A New Filter): Add UI_APPLY_INVERT_FILTER here
    UI_APPLY_INVERT,
    UI_APPLY_SPECIAL_FILTER,
    UI_UNDO,
    UI_REDO,
    UI_QUIT

    ...

      ```

8. Lastly, in flashphoto_app.cc, add the UICtrl::UI_APPLY_INVERT case to the GluiControl method.

    ###### flashphoto_app.cc
      ```C++

    ...

    case UICtrl::UI_APPLY_QUANTIZE:
        filter_manager_.ApplyQuantize(display_buffer_, scratch_buffer_);
        break;
    case UICtrl::UI_APPLY_SPECIAL_FILTER:
        filter_manager_.ApplySpecial(display_buffer_, scratch_buffer_);
        break;
    \TODO(Adding A New Filter): Add UICtrl::UI_APPLY_INVERT case here
    case UICtrl::UI_APPLY_INVERT:
        filter_manager_.ApplyInvert(display_buffer_, scratch_buffer_);
        break;

    ...

      ```

[HistoryManagerUML]: https://github.umn.edu/umn-csci-3081F16/repo-group-Bits-Please/blob/history_manager/doc/figures/HistoryManager.png
