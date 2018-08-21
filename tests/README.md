# FPANR_tests

Project designed to test FPANR library.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

### Prerequisites

Autotools, gcc, and check. Feel free to tell me if you find some others.

```
sudo apt-get install gcc autoconf automake autotools-dev libtool pkg-config check
```

### Installing

Compiling with autotools
```
autoreconf -i
```
Building the projet
```
make
```

## Running the tests
```
make check
```

## Built With
* [Automake](https://www.gnu.org/software/automake) - Building tool
* [Check](https://libcheck.github.io/check) - C Test Framework used

## Contributing

Please send me an email at christophe.pont@univ-perp.Fr if you wish yo contribute

## Authors
* **David Defour** - *Concept and complete scientific work*
* **Christophe Pont** - *Implementation of solutions* - [christof337](https://github.com/christof337)

See also the list of [contributors](https://github.com/christof337/FPANR/contributors) who participated in this project.

## License

This project is licensed under GPL - see the [LICENSE.md](../LICENSE.md) file for details

## Acknowledgments

* Thanks to check documentation
* THanks to autotools configuration made accessible
* All the design goes to David Defour



