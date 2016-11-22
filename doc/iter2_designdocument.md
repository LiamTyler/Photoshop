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
Our design at the highest level of abstraction views applying any filter as the same operation-- an operation that takes in the current screen, and creates a new image to be displayed by applying the filter to the current screem. To implement this, we created an abstract class as seen in Figure 1.1 for all filters to derive from.


###### Figure 1.1: Class declaration of the base Filter class (src/include/filter.h)
```C++
class Filter {
 public:
  virtual ~Filter() {}
  virtual void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage) = 0;
  virtual std::string name(void) = 0;
};

```

Notice how all the methods are virtual, and two of them are pure virtual. This class defines the basic interface for all of our filters, but provides none of the details of how that is accomplished. The details of how the ApplyFilter() method is realized for the two types of filters: pixel-independent, and convolution-based, is handled by our abstract classes: SimpleFilter, and KernalFilter respectively. The class diagrams for these classes are depicted in Figure 1.2 below.

###### Figure 1.2: The UML class diagram for the Filters.
![Filters UML diagram][FiltersUML]

We will describe the KernalFilter first. The main goal of the KernalFilter is to achieve the convolution-based functionality. We approached the problem with the following mentality: "For each pixel in our display, the new pixel will be composed of its neighboring pixels. We wish to know which neighboring pixels, and how much of each of them to compose our new pixel with." To accomplish this, notice how the KernalFilter class has a Kernal object, whose class declaration is shown in Figure 1.3.


###### Figure 1.3: The Kernal class declaration (src/include/kernal.h)
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

This class seems to have a lot going on, but boils down to a few main components. The first key aspect of this class is the kernal_ member variable. The Kernal object is a similar to the Mask of Tools in iteration 1. It is composed of a two dimensional array of floats, which is pointed to by the kernal_ variable. Each element in the array is the percentage of that pixel we want for our final pixel. To better see this, observe the next key aspect of the Kernal class: the ApplyKernal method (shown in Figure 1.4 below).


###### Figure 1.4: The ApplyKernal method of the Kernal class (src/kernal.cc)
```C++
ColorData Kernal::ApplyKernal(PixelBuffer* oldimage, int start_x, int start_y) {
    int buff_width = oldimage->width();
    int buff_height = oldimage->height();
    int kern_mid_x = width_ / 2;
    int kern_mid_y = height_ / 2;
    ColorData total, tmp;

    total = ColorData(0, 0, 0, 0);
    float max_alpha = 0;
    for (int kr = height_ - 1; kr >= 0; kr--) {
        for (int kc = 0; kc < width_; kc++) {
            int cur_x = start_x + kc - kern_mid_x;
            int cur_y = start_y + (height_ - 1) - kr - kern_mid_y;
            if (0 <= cur_x && cur_x < buff_width &&
                0 <= cur_y && cur_y < buff_height) {
                tmp = oldimage->get_pixel(cur_x, cur_y);
                if (tmp.get_alpha() > max_alpha) {
                    max_alpha = tmp.get_alpha();
                }
                total = total + tmp * kernal_[kr][kc];
            } else {
                tmp = oldimage->get_pixel(
                        std::min(buff_width - 1, std::max(0, cur_x)),
                        std::min(buff_height - 1, std::max(0, cur_y)));
                if (tmp.get_alpha() > max_alpha)
                    max_alpha = tmp.get_alpha();
                total = total + tmp * kernal_[kr][kc];
            }
        }
    }
    ColorData t = total.clamped_color();
    t.alpha(max_alpha);
    return t;
}

```

Notice that this method takes in the location of the pixel we are currently processing. It then centers the kernal_ array over that location, and loops through each pixel, adding that pixel's ColorData multiplied by the corresponding value in our array, and adds it to a running total. This is the value that is returned, which will become the pixel's ColorData on the newimage. The way we create the kernal array itself, is through the Kernal member function InitializeKernal(). The pure virtual InitalizeKernal method is the last key aspect to notice in Fig 1.3. Each filter that is convolution-based has its own kernal which defines the InitializeKernal method to give the filter it's appropriate functionality. To make this more clear, we can examine the BlurFilter.

To blur a pixel, we average out all the colors within a certain radius of a pixel, and set that pixel equal to the average. Observe the implementation of BlurFilter in Figure 1.5 below.

###### Figure 1.5: BlurKernal class definition (src/blur_kernal.cc)
```C++
BlurFilter::BlurFilter(int amount) : KernalFilter(new BlurKernal(amount)) {}
```

Notice how the only thing needed to create the filter is passing a BlurKernal to the parent KernalFilter class. To apply the kernal itself, there is no definition needed because the parent KernalFilter class already defines the ApplyFilter method as follows in Figure 1.6:

###### Figure 1.6: Default ApplyFilter method for KernalFilters (src/kernal_filter.cc)
```C++
void KernalFilter::ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage) {
    int buff_height = oldimage->height();
    int buff_width = oldimage->width();

    for (int r = 0; r < buff_height; r++)
        for (int c = 0; c < buff_width; c++)
            newimage->set_pixel(c, r, kernal_->ApplyKernal(oldimage, c, r));
}
```

For any filter class, the default method is to simply loop through all the pixels and apply the kernal to each pixel. The BlurKernal only overrides the InitializeKernal method as stated before. If we were to create a BlurKernal with a radius of 2, the two dimensional array would be as follows in Figure 1.7:

###### Figure 1.7: Diagram of a BlurKernal with radius of 2.
![BlurKernal result from InitializeKernal with radius of 2][BlurKernal]

Notice how there are 13 pixels within a radius of 2 from the center, so when we apply the kernal as seen in Figure 5, it will return the pixel that is the average of all the pixels within a radius of 2 of the center pixel.


In regards to the pixel-indepenedent filters, we designed them so that each filter derives from a SimpleFilter class depicted in the UML diagram in Figure 2. Notice how the ApplyFilter method is not pure virtual, but the ApplyToColor is. We designed it so that each filter has the same default ApplyFilter method as seen below in Figure 1.8.

###### Figure 1.8: ApplyFilter method definition for SimpleFilters (src/simple_filter.cc)
```C++
void SimpleFilter::ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage) {
    int buff_height = oldimage->height();
    int buff_width = oldimage->width();
    ColorData current;
    ColorData newColor;

    for (int r = 0; r < buff_height; r++) {
        for (int c = 0; c < buff_width; c++) {
            current = oldimage->get_pixel(c, r);
            newColor.red(ApplyToColor("red", current));
            newColor.green(ApplyToColor("green", current));
            newColor.blue(ApplyToColor("blue", current));
            newColor.alpha(current.get_alpha());
            newimage->set_pixel(c, r, newColor);
        }
    }
}
```

As seen in the implementation, pixel-independent filters loop through each pixel in the image and create the new corresponding pixel by performing the ApplyToColor method for each color. Each subclass of SimpleFilter implements that function as needed to return the appropriate value of the color requested.

### 1.2 Design Justification

The design above was created with an emphasis on the following goals: extensibility, understandability, and modularity. We believe that while the design may not be the best, it does a good job at meeting those goals. This section describes the advantages and disadvantages to our design, and proposes a couple alternatives.

The first design we actually used to implement most of the project initially involved having the 2D array for the kernal object be a part of the KernalFilter class. That way there was no need to have another class for each and every KernalFilter created. We quickly found however, that it was not easy to understand. Figure 1.9 depicts the declaration for the KernalFilter class we had previously.

###### Figure 1.9: Alternative declaration for the KernalFiter class we initially used.
```C++
class KernalFilter : public Filter {
public:
 KernalFilter();
  KernalFilter(int width, int height);
  virtual ~KernalFilter();
  virtual void ApplyFilter(PixelBuffer* oldimage, PixelBuffer* newimage);
  virtual void CreateKernal(int width, int height);
  inline int get_width() { return width_; }
  inline int get_height() { return height_; }
  inline float** get_kernal() { return kernal_; }
  virtual std::string name(void) = 0;

 protected:
  void AllocateKernal(int width, int height);
  void DeallocateKernal();
  virtual void InitializeKernal() = 0;

 private:
  KernalFilter(const KernalFilter &f) = delete;
  KernalFilter& operator=(const KernalFilter &f) = delete;
  int width_;
  int height_;
  float** kernal_;
};
```

Notice how this class simultaneously has methods like AllocateKernal and ApplyFitler. Despite writing most of the filters this way initially, we switched because this design presents two levels of abstraction in the same class. The kernal and the filter had very high coupling by putting them in the same class, and the code was not very understandable, because you constantly were doing tasks for two separate abstractions. By separating the filter and the kernal, our code became much more understandable, making it easier to modify and debug. In addition to that, our modularity increased. For any filter, we could just switch out its kernal for a new one. As the code is in Figure 1.9, you would have to rewrite the InitializeKernal function at a minimum, and can not just swap anything out since it is built into the filter. 

Another alternative we considered was not having a kernal object at all and building the functionality of a filter directly into the ApplyFilter method. While this is possible, and you don't have to worry about kernal objects and more files which is a positive, this design has high code duplication, worse efficiency, and low extensibility. For each new filter, you would have to redefine the ApplyFilter method, which in our design, the default definition works for all the KernalFilters. In addition to that, each method would at some level do the exact same thing: loop through all the pixels, applying some algorithm, and placing it on the new image. This design does not take advantage of that, and the code would be duplicated for every filter. Having the kernal also pre-computes many things needed to apply the filter (like finding the pixels within a certain radius). Not having that pre-computed would make the method call slower, which is undesirable since performance is a large concern for this project.

Standing by itself, our final design has many advantages. Observe the BlurFilter definition presented earlier in Figure 1.5. It took only one line to create the BlurFilter. The simplicity of adding that is a large benefit. One could argue that we still had to create a whole BlurKernal class. While that is true, the base Kernal does most of the work in sizing and applying the kernal. To extend it to create a filter, only the InitializeKernal method needs to be defined, which is always going to have to be designed somewhere. Both the ApplyFilter and ApplyKernal methods are merely virtual. This allows for complex filters in the future to be defined, but for most filters, we don't have to write anything for those two methods, making it even more extensible. We felt that these advantages made our design a desirable one.

The disadvantages of our design few. One is that there are many files to keep track of, and to add a convolution-based filter, it's likely that 4 new files need to be created. This admittingly, is a large concern. We felt that this is lessened by the fact that each file is usually very small. As seen in the definition of BlurFitler in Figure 1.5, it was literally one line. The kernal object for the filter only had to define one method. Then there are just two header files to declare, which are usually small. This makes this disadvantage not as impactful, and still easy to add new filters. Another disadvantage is that in our design, everytime a fitler is clicked in the GUI, the corresponding filter object is created at that time. Since it's not pre-computed, this means we have lower efficiency. Our reasoning for this is that most of the time, the parameters needed for the filter are going to change, so most of the work would have to be redone anyways. An example of that is the BlurFilter. If the blur amount changes from one call of it to the next, then the kernal would be remade anyways. By not having it resize or update, calling a new filter is merely two lines: construct the filter object, and apply it. This simplicity is desirable, and we did not notice a performance decrease. We actually do have the methods to implement this design already created, but we think our current design is desirable.

Overall, we feel that our filter design is successful. It is extensible, understandable, and has high modularity, which is what we focused on. There may be a better design, but ours did achieve what we wanted it to.


## 2  Design Question Two
> One common software feature included in this iteration is the undo/redo mechanic, where any modification to the canvas can be reversed, and then optionally re-applied. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description

Below is the UML Diagram that illustrates our HistoryManager design.

###### Figure 2.1: UML diagram of HistoryManager
![HistoryManager UML][HistoryManagerUML]


The design we developed in order to implement the undo/redo feature revolves around maintaining a ring buffer. As you can see in Figure 2.2, when constructing the HistoryManager object, in our Init function, we create an array of pointers to PixelBuffers of size possible_saves_. possible_saves_ dictates how far back or how far forward one can undo or redo respectively. We also save the current, blank canvas to the first position in our array. If the array becomes full, we save the next PixelBuffer at position 0, which gives us the ring buffer structure. 

###### Figure 2.2: Init function in History Manager (src/history_manager.cc)
  ```C++
void HistoryManager::Init(PixelBuffer* buff) {
    saved_buffers_ = new PixelBuffer*[possible_saves_]();
    SaveCanvas(buff);
    oldest_save_ = 0;
}
```

The HistoryManager class has a SaveCanvas method, as seen in Figure 2.3, which gets called each time a filter is applied, an image gets loaded in as the canvas, and the mouse is released. If the next pointer in our ring buffer points to a non-null PixelBuffer, and it's width and height do not match the display (buff) that we are saving, then we delete it, and allocate a new one to the correct size. We also allocate a new PixelBuffer to the according size if the ring buffer currently points to a null value. Then, we copy the current display PixelBuffer we want to save into that PixelBuffer in our ringed buffer.

###### Figure 2.3: SaveCanvas method in History Manager (src/history_manager.cc)
  ```C++
void HistoryManager::SaveCanvas(PixelBuffer* buff) {
    
    ...

    int width = buff->width();
    int height = buff->width();
    ColorData bg = buff->background_color();
    PixelBuffer* curr = saved_buffers_[current_save_];
    // Delete the current pixelbuffer in this spot if there is and old one,
    // and it is of different size than the new one
    if (curr != nullptr) {
        if (width != curr->width() || height != curr->height()) {
            delete curr;
            curr = new PixelBuffer(width, height, bg);
        } else {
            curr->set_background_color(bg);
        }
    } else {
        curr = new PixelBuffer(width, height, bg);
    }

    CopyPixelBuffer(buff, curr, width / 2, height / 2);

    saved_buffers_[current_save_] = curr;
}
```

For obvious reasons, we have Undo and Redo methods, shown in Figure 2.4, which get called when the Undo and Redo buttons are pressed. If there is a canvas available at the position in the array before the current canvas being displayed, the user can use Undo, and that PixelBuffer gets copied, returned, and set as the display_buffer_. The only difference in Redo is that we copy the PixelBuffer pointed to by the next pointer in the ring buffer, if available.

###### Figure 2.4: Undo and Redo methods in History Manager (src/history_manager.cc)
  ```C++
PixelBuffer* HistoryManager::Undo(PixelBuffer* display) {
    // Check to see if we can even redo
    if (current_save_ == oldest_save_)
        return display;

    current_save_ = (current_save_ - 1) % possible_saves_;
    if (current_save_ == -1)
        current_save_ = possible_saves_ - 1;
    
    return ResizeAndCopy(display);
}

PixelBuffer* HistoryManager::Redo(PixelBuffer* display) {
    // Check to see if we can even redo
    if (current_save_ == newest_save_)
        return display;

    current_save_ = (current_save_ + 1) % possible_saves_;
    return ResizeAndCopy(display);
}
```

We keep track of three values that allow us to correctly allow or disallow the use of the Undo and Redo methods. These values are current_save_, oldest_save_, and newest_save_. We mod these values with possible_saves_ in order to wrap around our ring buffer. The current_save_ is the index of the array which contains the pointer to the current PixelBuffer being displayed. When SaveCanvas is called, we add 1 to current_save_ and set newest_save_ to the value of current_save_, as seen in Figure 2.5, since that save is now the newest. To clarify, newest_save_ is not always the same as current_save_. For instance, if there are 10 PixelBuffers in saved_buffers_ and one decides to use the undo function 3 times, newest_save_ will be 9 while curent_save_ will be 6. If current_save_ == oldest_save, we have wrapped around the entire ring buffer and need to add 1 to the oldest_save_, as shown in Figure 2.5. For examples, if we have possible_saves_ set to 10 and current_save_ becomes 10, we set the value of current_save_ to 0 since 10 mod 10 is equal to 0. If oldest_save_ was also 0, we must now add 1, so oldest_save_ is now 1. The previous oldest_save_ is lost, which is fine since, at most, we only need to be able to undo or redo possible_saves_ times.

###### Figure 2.5: Another part of SaveCanvas method in History Manager (src/history_manager.cc)
  ```C++
void HistoryManager::SaveCanvas(PixelBuffer* buff) {
    // Update the positions
    current_save_ = (current_save_ + 1) % possible_saves_;
    newest_save_ = current_save_;
    if (current_save_ == oldest_save_)
        oldest_save_ = (oldest_save_ + 1) % possible_saves_;

    ...
    
}
```
  
If current_save_ is equal to newest_save_, the user cannot Redo, which can be seen above, in Figure 2.4. Likewise, if current_save_ is equal to oldest_save_, the user cannot Undo. An important thing to note is that if a user clicks Undo, and then performs an action, like drawing a line, the canvas gets saved and newest_save_ gets set to current_save_. This means that Redo is now disabled and the user can never get back to the initial canvas that he clicked Undo from. The actual disabling of the button to undo / redo is outside the scope of HistoryManager, and we implemented it in state_manager.cc

One additional function we made is ResizeAndCopy, which can be seen in Figure 2.6, below. This functions determines whether a saved PixelBuffer and the PixelBuffer we want to display have the same dimensions. If they differ, one will be created in the correct size. Then, we then center the PixelBuffer onto the PixelBuffer we are going to return, and copy it over via a CopyPixelBuffer function implemented separately.

###### Figure 2.6: ResizeAndCopy function in History Manager (src/history_manager.cc)
  ```C++
PixelBuffer* HistoryManager::ResizeAndCopy(PixelBuffer* display) {
    int d_height = display->height();
    int d_width = display->width();
    PixelBuffer* curr = saved_buffers_[current_save_];
    int c_height = curr->height();
    int c_width = curr->width();
    ColorData bg = curr->background_color();

    // Check to see if current display is the same dimensions
    // as the saved one. If so, no need to resize it.
    if (c_width != d_width || c_height != d_height) {
        delete display;
        display = new PixelBuffer(c_width, c_height, bg);
    }

    CopyPixelBuffer(curr, display, c_width / 2, c_height / 2);

    return display;
}
```

### 2.2 Design Justification

One decision we had to make was what to save. We decided it would be best to store entire PixelBuffers in an array rather than attempt to save a certain action, like a drawn line.  With the variablilty of the strokes, filters, etc., it is much simpler to save a copy of the PixelBuffer and store it in an array. PixelBuffers are small enough that we can store many instances of them in memory. 

As a group, we decided that a ring buffer would be the best design for our HistoryManager class because it was the simplest design we came up with. This is the biggest advantage to our design. All we had to use was an array, and 3 integers. As seen in Figure 2.4, undo and redo are merely an if statement and a return. No need to think about stacks, or any complicated data structures. Simplicity always has high value, and we felt that this design is the easiest to read and understand.

An alternative we discussed involved using two stacks, rather than a ring buffer. We would have pushed PixelBuffers onto one stack as we saved them. When the user clicked Undo, we would pop a PixelBuffer off of one stack, and push it onto the other. Then, if a user clicked Redo, we would pop the PixelBuffer off of the second stack and push it back onto the first stack.

We saw two challenges with the two stack design that were easily handled with our ring buffer design. The first was that we would have to somehow make sure there was always a blank PixelBuffer at the bottom of the first stack, even if a user clicked Undo all the way back to that PixelBuffer. In our ring buffer design, we have a blank PixelBuffer in the first position of our array, and it never changes. None of the PixelBuffers in our array get changed as we Undo and Redo because they simply get copied over to the display_buffer_.

The second challenge we saw with the two stack design was that it would be more difficult to handle the case where the stack is full and we needed to save another PixelBuffer. In the two stack design, we would have to delete the PixelBuffer at the bottom of the stack and then push the newly saved PixelBuffer onto the top of the stack. In our ring buffer design, when our array is full, we automatically wrap around the ring buffer to position 0, since we mod (current_save_ +1) with possible_saves_.

After comparing the two stack design and the ring buffer design, we decided that the ring buffer was simpler. We thought that the two stack design added unnecessary complexity and had more cons than the ring buffer design.

Lastly, we decided to create a ResizeAndCopy method because we noticed that the Undo and Redo methods are exactly the same except for which PixelBuffer gets chosen to be copied. Therefore, we created the ResizeAndCopy method to make the code easier to read and understand as well as avoid writing the code twice.

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

    ###### src/include/invert_filter.h
      ```C++
    #ifndef SRC_INCLUDE_INVERT_FILTER_H_
    #define SRC_INCLUDE_INVERT_FILTER_H_

    #include <string>
    #include "include/simple_filter.h"
    #include "include/color_data.h"

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

    ###### src/invert_filter.cc
      ```C++
    #include "include/invert_filter.h"
    #include <string>

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

    ###### src/include/filter_manager.h
      ```C++

    ...

    void ApplySpecial(PixelBuffer* oldimage, PixelBuffer* newimage);

    \TODO(Adding A New Filter): Add ApplyInvert here
    void ApplyInvert(PixelBuffer* oldimage, PixelBuffer* newimage);

    ...

      ```

4. Then, add the ApplyInvert method to the filter_manager.cc file in the src folder. Create an InvertFilter object and call the ApplyFilter method. This method is the same for all of the SimpleFilters.

    ###### src/filter_manager.cc
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

    ###### src/filter_manager.cc
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

    ###### src/filter_manager.cc
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

7. In the ui_ctrl.h file, add UI_APPLY_INVERT to the Type enum as shown below. UI_APPLY_INVERT must be placed after UI_APPLY_MOTION_BLUR but before UI_APPLY_SPECIAL_FILTER, since the buffers get switched for filters listed between those two filters, inclusively.

    ###### src/include/ui_ctrl.h
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

    ###### src/flashphoto_app.cc
      ```C++

    ...

    case UICtrl::UI_APPLY_QUANTIZE:
        filter_manager_.ApplyQuantize(display_buffer_, scratch_buffer_);
        break;
    case UICtrl::UI_APPLY_SPECIAL_FILTER:
        filter_manager_.ApplySpecial(display_buffer_, scratch_buffer_);
        break;
    // TODO(Adding A New Filter): Add UICtrl::UI_APPLY_INVERT case here
    case UICtrl::UI_APPLY_INVERT:
        filter_manager_.ApplyInvert(display_buffer_, scratch_buffer_);
        break;

    ...

      ```

[HistoryManagerUML]: https://github.umn.edu/umn-csci-3081F16/repo-group-Bits-Please/blob/master/doc/figures/HistoryManagerNew.png
[FiltersUML]: https://github.umn.edu/umn-csci-3081F16/repo-group-Bits-Please/blob/develop/doc/figures/Filter_UML.png
[BlurKernal]: https://github.umn.edu/umn-csci-3081F16/repo-group-Bits-Please/blob/develop/doc/figures/BlurKernal.png
