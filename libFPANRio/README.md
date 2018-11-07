## libfpanrio v1.0.2

### Installation

Run the following command inside libfpanrio directory:

```bash
   $ autoreconf -i
   $ ./configure
   $ make
   $ sudo make install
```

### Usage

Use `-lfpanrio` when compiling, and import `libfpanrio.h` in your program.
This will enable you to use the conversion functions exposed by the library, which you'll find the signature below :
```c
float fpanrToFloat(const float fpanrVal);
float floatToFpanr(const float floatVal);
float floatToFpanrWithPrec(const float floatVal, const int prec);
unsigned getPrecFromFpanrFloat(const float floatVal);

double fpanrToDouble(const double fpanrVal);
double doubleToFpanr(const double doubleVal);
double doubleToFpanrWithPrec(const double doubleVal, const int prec);
unsigned getPrecFromFpanrDouble(const double doubleVal);
```

### Examples

The `examples/` directory contains various examples of libfpanrio usage.
Run `examples/conversion` to see its usage.
