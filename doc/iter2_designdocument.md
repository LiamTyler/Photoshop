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

### 1.2 Design Justification


## 2  Design Question Two
> One common software feature included in this iteration is the undo/redo mechanic, where any modification to the canvas can be reversed, and then optionally re-applied. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description

### 2.2 Design Justification


## 3  Design Question Three
> A new developer on your team must add a new filter to FlashPhoto. This filter is called  _Invert._ This filter performs the following conversion to all pixels in the canvas:
> ```
> newColor's red   = 1 - oldColor's red
> newColor's green = 1 - oldColor's green
> newColor's blue  = 1 - oldColor's blue
> ```
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new filter.

### Programming Tutorial: Adding a New Invert Filter to FlashPhoto

1. Begin by creating an Invert Filter header file called invert_filter.h and place it in the include folder. Since the Invert Filter does not need a kernal, Invert Filter will inherit from the Simple Filter class. Filters need a constructor, destructor, an ApplyToColor method, and a name, as shown below.

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

class InvertFilter : public InvertFilter {
 public:
  explicit InvertFilter();
  ~InvertFilter();
  float ApplyToColor(std::string, const ColorData& current);
  std::string name(void) { return "Invert"; }
};

#endif  // SRC_INCLUDE_INVERT_FILTER_H_

  ```

2. Next, create an Invert Filter C++ file called invert_filter.cc and place it in the src folder. Here we define the constructor and destructor. The ApplyToColor method needs to be defined in a way that will give us the desired affect. ApplyToColor gets applied to each color separately. We check which color got passed in to ApplyToColor, then adjust that color accordingly. In this case, for each color that gets passed in, we return 1.0 - the current color.

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
    
    if (amount_ == 0){
        value = 0;
    } else {
        // Calculate amount of current color to be applied
        value = 1.0/amount_;
    }
    
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

3. Third, add the ApplyInvert method to the filter_manager.cc file in the src folder. Create an Invert Filter object and call the ApplyFilter method. This method is the same for all filters. ????????

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
    std::cout << "Apply has been clicked for Special" << std::endl;
    InvertFilter i;
    i.ApplyFilter(oldimage, newimage);
}

...

  ```

4. Be sure to include the invert_filter.h file at the top of the filter_manager.cc file.

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


