<b>Requirements: </b> Visual Studio 2015

Matrix may also working on other versions of Visual Studio and Qt. As for other programming environments, there exists also a chance that Matrix will be working.

If you want to use Matrix in earlier versions of Visual Studio, you should <b>#define _DS_MATRIX_SUPPORT_PREV_VS</b> before <b>#include ds/Matrix.h</b>

You also can use <b>std::vector</b> with <b>Matrix</b>. You should only <b>#define _DS_MATRIX_SUPPORT_STL_VECTOR</b> before you <b>#include ds/Matrix.h</b>

If you do not work in Visual Studio 2015 there is possibility that explicit casts won't be working. So you can <b>#define _DS_MATRIX_NOT_SUPPORT_EXPLICIT_CAST</b> before <b>#include ds/Matrix.h</b> to remove this cast from template class code. If you define this, there will be created class methods that will be able to do these casts if you need.


If you don't want to use satndart variable definitions in class like 
<b>#define ZERO static_cast<T>(0)
<br>#define ONE static_cast<T>(1)
<br>#define DEFAULT_EPS static_cast<T>(0.00001)</b> 
you can just <b>#define _DS_MATRIX_NOT_USE_STANDART_VALUES_DEF</b> and then define your own 
<b>#define ZERO
<br>#define ONE
<br>#define DEFAULT_EPS</b>
