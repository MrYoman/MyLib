<b>Requirements: </b> Visual Studio 2015

If you want to use Matrix in earlier versions of Visual Studio, you should 
<center>#define _DS_MATRIX_SUPPORT_PREV_VS </center>
before 
<center>#include <ds/Matrix.h></center>

You also can use std::vector with Matrix. You should only
<center>#include <vector></center>
before you
<center>#include <ds/Matrix.h></center>
