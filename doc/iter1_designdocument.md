# Design Justifications for BrushWork
#### Group Name:
<Group Name Here>

#### Members:
- <Member 1>
- <Member 2>
- <Member 3>

#### Instructions 
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.


## 1  Design Question One
> This iteration of the project is all about tools. Naturally, a key design decision is how these tools are represented. Each tool has several characteristics, including the shape of the tool, its size, and the way it blends with the canvas when the tool is applied. Some tools share characteristics with other tools, such as how the pen and calligraphy pen tools blend with the canvas in the same manner. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description

### 1.2 Design Justification


## 2  Design Question Two
> Unlike most of the tools, the Eraser returns the canvas to its original color. One of the challenges in this iteration is giving the eraser the authority or information required to have this effect while having minimal impact on the way the rest of the tools are defined. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description
> We decided to make Eraser a subclass of Tool so that the Eraser applies itself just like any other tool using the applyTool() method. The only difference is that the Eraser applies the background color instead of the current color selected by the user. To accomplish this, we check whether the current tool (cur_tool_) is the Eraser or not. If cur_tool_ is not the Eraser, current_color gets set to the current color stored in brushwork_app as cur_color_red_ cur_color_green_, cur_color_blue_. If cur_tool_ is the Eraser, current_color gets set to background_color.

> **Insert code snippet (Figure 1)**

> In main, the BrushWorkApp passes the background color to the Init function, which initializes the pixel buffer by calling InitializeBuffers as shown in Figure 2 below.

###### Figure 2: Init() for the BrushworkApp (brushwork_app.cc).

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

> The method InitializeBuffers() uses the background_color to create a new PixelBuffer called display_buffer_ as shown in Figure 3 below.

###### Figure 3: InitializeBuffers() for the BrushworkApp (brushwork_app.cc).

```C++
void BrushWorkApp::InitializeBuffers(
    ColorData background_color,
    int width,
    int height) {
    display_buffer_ = new PixelBuffer(width, height, background_color);
}
```

> We get the background color by calling pixel_buffer's background_color() method, shown below in Figure 4, on display_buffer_.

###### Figure 4: background_color() for the PixelBuffer (pixel_buffer.cc).

```C++
 /**
   * @brief Get the background color that was used to initialize the PixelBuffer
   * @return The background color
   */
  ColorData background_color(void) { return *background_color_; }
```

### 2.2 Design Justification
> **Where should we select the current color for the tools to apply and why??**

> Rather than setting the Eraser to a certain color, we decided to get the background_color from the PixelBuffer using the background_color() method. This way, no matter what color the background gets set to initially, Eraser will use the correct color. One con is that if the background color was somehow changed while the program was running, Eraser would still use the initial background color. Since there isn't a way for the user to change the background color, we decided getting the initial color would be sufficient at this point.

## 3  Design Question Three
> A new developer on your team must add a new tool to BrushWork. This tool is called  _Pencil._ This tool is a single, non-transparent pixel that completely replaces the existing colors on the canvas in the same way as the pen or calligraphy pen blend.  
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new tool.

### Programming Tutorial: Adding a New Pencil Tool to BrushWork

1. <Step 1>
2. <Step 2>
<etc>
