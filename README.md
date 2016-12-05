# Image Processing Suite

## Coding guidelines
In any large software project with multiple people contributing, having a
consistent coding style throughout is vital to minimize miscommunications
between collaborators, making code more readable, etc. For this class, we will
be Google's C++ Style Guide (there are other conventations that are also valid,
but this is the one we will be using). We will be checking that all submitted
code will conform to the Google C++ style.

### Running the linter
To that end, we will provide you with a style checking script that will check
the basic elements of Google style. It is assumed that prior to handing in any
iteration of the project, you will run the following command on all source files
(.cc AND .h) in your repository by doing something like this:

    python ext/cpplint/cpplint.py --linelength=81 <source files>

And that this command will report 0 errors found. You will be evaluated on an
all-or-nothing basis for this part of the project, so take care to do this.

### Additional elements of Google C++ style
Unfortunately, the script will NOT catch everything that is needed for Google
C++ style. We will be spot checking code for things not caught by the script,
for things like:
 - Usage of C++, not C-style casts
 - Not using of C-style memory allocation/copy operations
 - Usage of namespaces, including proper naming
 - Initialization of variables when they are declared
 - All 1 parameter constructors are marked explicit
 - All inheritance passes the 'is-a' test
 - All data members are private in each class
 - Proper ordering of declarations within a class (functions->data;
   public->protected->private)
 - All references passed to functions are labelled const.
 - Usage of nullptr, rather than NULL
 - Proper file naming
 - Proper function naming (use your discretion for "cheap")
 - Proper data member naming
 - Minimization of work performed in constructors
 - Not using exceptions
 - Proper commenting throughout the header files and source files

This is not an exhaustive list of what we will be checking for, so please read
the Google C++ style guide!

## Documentation Task
For this iteration you will need to document your code using doxygen style
comments for the following elements:

- Class declarations .h files
- Function declarations (not definitions) in .h files
- Function definitions (if defined in .h file)
- Member variable declarations
- Enum declarations
- Struct declarations

Hopefully you have been commenting your code in the above ways as you have been
going along, and you just need to convert it to the doxygen format. If not, this
is a good exercise in writing for computer science, in that how to explain a
large and/or complex class in a few succinct sentences is a very valuable
skill. Plus, it will enhance your own understanding of what you have created.

For examples of the doxygen comment format you can either google it, or look at
any of the support code we have provided you for iteration 1, 2, or 3 (all 3
have doxygen style comments).

To generate documentation under `doc/`, do the following:

    make documentation

## Application Task

You will need to use your refactored libraries to bring FlashPhoto to life once
again, and to also power a new application, MIA.

## Build Process Task
We have given you the directory structure for libapp, libimgtools, and the
FlashPhoto and MIA applications, as well as Makefiles to build them. However, in
the case of libimgtools and libapp, you will need to fill in the Makefile target
for creating a static (.a library). This is a 1 line change but a very important
one!

*You should not need to modify the build process (i.e. the Makefiles) at all
other than this (if you follow conventions discussed in class for organizing
source code), but if you do, make sure we can still type 'make' after
configuration and the project will build.*

*IMPORTANT*

To build iteration 3 using our build process, you will need to do the following
(assuming you have filled in the library targets):

    cd config
    ./configure --enable-shared=no --prefix=`realpath ../ext`
    cd ..
    mkdir build

If you forget the last step, the build process will fail with very strange
errors. If successful, you will get a set of subdirectories under `build`:

- libimgtools

- FlashPhoto

- MIA

Each containing an `obj` directory with all the object files used to build them,
and either a `lib` directory containing the compiled library, or a `bin`
directory containing the compiled executable.

To get things to appear under `build/bin`, instead of
`build/MIA/bin/MIA`, for example, you will need to also run the following
command:

    make install

This will create symbolic links from the compiled items to pre-specified
locations under `build`. *You should not need to modify the install targets for
any of the provided Makefiles :-).*

## git commit message guidelines
- There should only ever be ONE scope/module affected per commit message.
- If you have an 'and' in a commit subject, break it into 2 commits.
- No "In progress coding/debugging" commit messages

These are examples of the quality of the commit messages we will be expecting.

* feat(onUrlChange): Added new event to $browser
  - forward popstate event if available
  - forward hashchange event if popstate not available
  - do polling when neither popstate nor hashchange available
  Breaks $browser.onHashChange, which was removed (use onUrlChange instead)

* docs(project): Updated fixed docs from Google Docs
  Couple of typos fixed:
  - indentation
  - batchLogbatchLog -> batchLog
  - start periodic checking
  - missing brace


Furthermore, if you want to pair/group program, your git commit messages should
reflect this, so that all members receive participation credit for doing it, not
just the one that actually commits the work. To do so, add a line like this to
the bottom of your commit message:

    Contributors: <x500 for student 1> <x500 for student 2> ...

For example, if Seth and I worked on something, we would do

    Contributors: harw006 joh08230

at the end of our commit.

Usage of our git commit message template is in no way mandatory; it is just
there to help you create detailed, helpful git commit messages. You can use
whatever conventation you like within your group, as long as the messages are
detailed and helpful.


If you have questions about whether something is appropriate, see John.
