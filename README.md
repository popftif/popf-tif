# popf-tif

### Installation

Get the prerequisites:
```sh
sudo apt-get install cmake coinor-libclp-dev coinor-libcoinutils-dev coinor-libosi-dev doxygen bison flex
```

Create a new directory:
```sh
mkdir popf-tif
cd popf-tif
```

Get the code:
```sh
git clone https://github.com/chiarapiacentini/popf-tif .
```

Configure the sources for building:
```sh
cd planner/src
./build-instructions.txt 
```

Build the planner:
```sh
cd ../release
make popf3-clp 
```

Once POPF-TIF has been compiled, the executable popf3-clp is created in the folder popf.

### Get started

To run the planner:
```sh
./popf3-clp domainfile problemfile
```

To run the planner with the lookahead heuristic:
```sh
./popf3-clp -w domainfile problemfile
```

To run the planner with the external solver:
```sh
./popf3-clp -x domainfile problemfile externalsolver [inputexternalsolver]
```

For more detailed information, please visit our Wiki Page. 
