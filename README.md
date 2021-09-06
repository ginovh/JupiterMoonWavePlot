## JupiterMoonWavePlot

### Graphical show Jupiter moons position

Plots the position of the Galilean moons. This is a very early version with many todo's ( e.g. add menu bar, export to pdf etc.)

![Screenshot](Screenshot.png)

**Dependencies :**
- Qt 4.8.0 and above 
- AA+ v2.33 and above (http://www.naughter.com/aa.html)

AA+ implements the algorithms from the book "Astronomical algortihms" by Jean Meeus. (http://www.willbell.com/math/mc1.htm)
You may find comments in the code refering to this book.

**Build:**

Below are instructions to build from the command line. It assumes Qt is properly installed.

```
./getaaplus.bash
mkdir build
cd build/
cmake ../
make -j4
```

As an alternative to building from the command line, open the CMakeLists.txt file in QtCreator and build the project in the IDE.

**Supported platforms:**
- Every platform that Qt supports
