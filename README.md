# ubwt: Uni-path BWT utilities

## Installation
* OS: ubwt currently can only be complied and run on Linux/Unix.

* Dependency: [zlib](https://zlib.net/)

* Toy example of test data are in `test_data`
```
git clone https://github.com/yangao07/ubwt.git
cd ubwt; make
```

## Get started with test data in `test_data`
```
$ ./ubwt unipath ./test_data/test.BWT_STR -fP -o ./test_data/test.unipath
$ ./ubwt index ./test_data/test.BWT_STR -fP
$ ./ubwt query ./test_data/test.BWT_STR ./test_data/test.query1
```

##  Command and options
```
Program: ubwt
Usage:   ubwt <command> [options]

Commands: 
         unipath     generate unipath seq from bwt-str
         index       index unipath's bwt-str
         query       query the unipath with the bwt index
```
## Generate uni-path sequence from BWT string
```
Usage:    ubwt unipath [option] <BWT-STR>

Options:

    -t    [INT] Number of threads. [1]
    -f    [STR] Format of input bwt-str. [B]
                  "B": binary file, 4-bit per bp, 0/1/2/3/4:A/C/G/T/#(first 64-bit: length).
                  "P": plain text.
    -o    [STR] Output file(FASTA format). [stdout]
```
### Example:
```
$ ./ubwt unipath ./test_data/test.BWT_STR -fP -o ./test_data/test.unipath
$ head -n2 ./test_data/test.unipath
>1_12
AGATCCGATGAG
```
### Output format:
```
>uniID_uniLen
uniSeq
```
* uniID: ID of unipath
* uniLen: Length of unipath
* uniSeq: Sequence of unipath

## Build BWT index for uni-path sequences
```
Usage:   ubwt index [option] <BWT-STR>

Options:

    -f    [STR] Format of input bwt-str. [B]
                  "B": binary file, 4-bit per bp, 0/1/2/3/4:A/C/G/T/#(first 64-bit: length).
                  "P": plain text.
    -o    [STR] Prefix of bwt-index file. [<BWT-STR>]
```
### Example
```
$ ./ubwt index ./test_data/test.BWT_STR -fP
[ubwt_dump] Writing ubwt to file ...
[ubwt_dump] Writing index done.
```
* Output index file will have `.ubwt` suffix.

## Find exact match of query sequence on BWT index
```
Usage: ubwt query <BWT-index.prefix> <in-query> > match.out

       Find exact match of input query on BWT-index.
       Return <unipath name> and <offset(1-based)> on unipath.
```
### Example
```
$ ./ubwt query ./test_data/test.BWT_STR ./test_data/test.query1
1_12	4
```
* Output consists two columns: <unipath name> <offset(1-based)> 

