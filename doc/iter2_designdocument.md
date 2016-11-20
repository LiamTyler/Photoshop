# Design Justifications for FlashPhoto
#### Group Name:
<Group Name Here>

#### Members:
- <Member 1>
- <Member 2>
- <Member 3>

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
> To address the challenge of redo/undo, we created a separate HistoryManager class. In this class we created an array to store each buffer that has been made.
> First, we created a constructor which we prepare a PixelBuffer* object to represent a buffer and an int called possible_saves_ to represent the maximum size of an array of buffers. possible_saves_ dictates how far back or how far forward one can undo/redo respectively. Also, there is saved_buffers_ which is the array in which the buffers will be saved into, current_save_ which keeps track of the index in which the current buffer is saved, newest_save_ which holds the index of the buffer which was most recently saved. To clarify, newest_save_ is not neccessarily the same as current_save_. For instance, if there are 10 buffers in saved_buffers_ and one decides to use the undo function 3 times, newest_save_ will be 9 while curent_save_ will be 6. These variables are used to keep track of the buffers in saved_buffers_. In addition, this is where we initialize the PixelBuffer* object which creates a new buffer array, but notice this is settled with the Init function.

```C++
HistoryManager::HistoryManager(PixelBuffer* buff, int possible_saves) :
                                saved_buffers_(nullptr),
                                possible_saves_(possible_saves),
                                current_save_(-1),
                                oldest_save_(0),
                                newest_save_(0) {
    Init(buff);
}
```
> Second, we have a destructor that deletes all the buffers in saved_buffers_ and then proceeds to delete the array as well. This helps to free up resources an objects may have acquired during its lifetime.
> Then, we have an Init function which takes in no arguments and created saved_buffers_ of the size of possible_saves_, saves the current canvas into the first index of the array, and sets oldest_save_ to 0. This is used to clear saved_buffers_. Thus, actions such as Redo and Undo will have no effect. 

```C++
void HistoryManager::Init(PixelBuffer* buff) {
    saved_buffers_ = new PixelBuffer*[possible_saves_]();
    SaveCanvas(buff);
    oldest_save_ = 0;
}
```
> Next, the SaveCanvas function is there to store a the current buffer into saved_buffers_ and proceedingly update the values current_save_, oldest_save_, and newest_save_. Usually, for current_save_ and newest_save_, we would add 1 to thir curretn value and keep oldest_save as is. However, oldest_save_ does change if we reach the end of saved_buffers_ we must store the buffer into the first index of saved_buffers_ and so we update the value accordingly as seen below.

```C++
    // Update the positions
    current_save_ = (current_save_ + 1) % possible_saves_;
    newest_save_ = current_save_;
    if (current_save_ == oldest_save_)
        oldest_save_ = (oldest_save_ + 1) % possible_saves_;
```

> When this happens, we reach a situation where we will have to replace the buffers currently in saved_buffers_ with the current buffer. Hence, we delete the old buffer, and insert the current buffer. This is  accomplished by obtaining the height and width of the current buffer, the background color and the current buffer itself, and then copying the data into a new buffer in which we store in saved_buffers_. Underneath, you can see that we check if a replacement needs to occur and then copy the new buffer.

```C++
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

    // Copy the actual pixels over into the buffer, now that it has the
    // correct size and bg color
    for (int r = 0; r < height; r++)
        for (int c = 0; c < width; c++)
            curr->set_pixel(r, c, buff->get_pixel(r, c));
    saved_buffers_[current_save_] = curr;
```

> After that, we have the Undo function which will change the current buffer to the previous buffer stored in saved_buffers_. We check to see if we can even Undo which means that there is more than 1 buffer in saved_buffers_. If we can Undo, we decrement the value of current_save_ and display the previous buffer throught the use of a funciton called ResizeAndCopy, which will be discussed later. If we cannot Undo, we return the current buffer. In the case that the current_save_ is at the beginning of saved_buffers_ and there is more than one buffer in saved_buffers_, we must ensure that current_save_ arrives at the end of saved_buffers_. Beneath we see how Undo() works.

```C++
    PixelBuffer* HistoryManager::Undo(PixelBuffer* display) {
    // Check to see if we can even redo
    if (current_save_ == oldest_save_)
        return display;

    current_save_ = (current_save_ - 1) % possible_saves_;
    return ResizeAndCopy(display);
}
```

> Along with that, we have the Redo function which reverses the functionality of Undo. To illustrate, if we have saved_buffers_ with 10 buffers in it and we Undo 2 times, we decremented current_save_ and idsplayed the according buffer. However, if we Redo 2 times, we increment current_save_ and we are back to where we have started. So, we first check if a Redo is possible and if so, we decrement current_save and use ResizeAndCopy to display the awarded buffer. If not, we reutrn the current buffer. Hoever, similar to Undo, there is a speicial case that needs to be addressed. If there is more than 1 buffer in saved_buffers_ and a Redo is possible and current_save is at the end of saved_buffers_, we must update current_save_ to correspond with beginning of saved_buffers_ and present the specified buffer. Another thing about the Redo function is that if one decided to undo and then make an action such as use the pen or a filter, the Redo function no longer is able the work. The code is quite similar to Undo except that it must increase the value of current_save_.
> The final function we made is ResizeAndCopy. This functions determines whether the two buffers have the same dimensions and if they differ, one will be resized and then returned. We have two buffers; one is the current buffer and one is the buffer we wan to display. We start by retrieving the height and width of the display buffer and the height and width of the current buffer. If they are the same, there is no need to resize the current buffer. If not, we take the values of the display buffer and resize the current buffer as well as copy the current buffer into the display buffer all the while maintaing the background color of the current buffer. Down below we see the retrieval of data from both display buffer and current buffer.

```C++
    int d_height = display->height();
    int d_width = display->width();
    PixelBuffer* curr = saved_buffers_[current_save_];
    int c_height = curr->height();
    int c_width = curr->width();
    ColorData bg = curr->background_color();
```
> Then we resize if needed and copy the saved buffer into the display buffer

### 2.2 Design Justification
> There were essentially two ways to implement Undo/Redo; with a separate class or have it lie in flash_photo_app.cc. We decided with the separate class since the functions in history_manager.cc have nothing to do with flash_photo_app.cc. All of the functions were made to impact only other functions in that class. This way also allowed for easier removal of the process without affecting other classes. From here we had to make another design decision in how we would keep track of the different actions. We decided the best way would be through an array that would store buffers of each consecutive action. The alterantive would have been to keep track of the individual strokes or actions made by the user. However, with the variablilty of the strokes, filters, etc., is it much simpler to save a copy of the PixelBuffer and store those into an array. The next decision we made was to create a separate function that initialized the objects rather than keeping it in the constructor. By creating a separate function we can easily see what objects we will be dealing with and the Init function clearly demonstrates that they will be initialized. In addition this allows for the use of Init outside of the countructor if one would chose to do so. The last decision made was the ResizeAndCopy function. This was the smarter choice than writing it individually within the Undo/Redo functions. If you venture above, you will see the code for Undo which is minimal and easy to understand. It would be muddled if ResizeAndCopy did not exist. Since having diferent dimension between multiple buffers is a possibility, we must check for it and act according. Thus, creating a separate function to handle such cases makes the code easiler to read and understand as well as creating less busy work in writing the code twice. In summation, having a separate class to deal with an array of PixelBuffers in which there is a separate function to ensure smooth buffer transitioning provided readable, easy-to-follow, and simpler code. 

## 3  Design Question Three
> A new developer on your team must add a new filter to FlashPhoto. This filter is called  _Invert._ This filter performs the following conversion to all pixels in the canvas:
> ```
> newColor's red   = 1 - oldColor's red
> newColor's green = 1 - oldColor's green
> newColor's blue  = 1 - oldColor's blue
> ```
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new filter.

### Programming Tutorial: Adding a New Pencil Tool to FlashPhoto

1. <Step 1>
2. <Step 2>
<etc>
