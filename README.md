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
$ ./ubwt unipath ./test_data/test.BWT_STR -fP -g -e ./test_data/test.edge -o ./test_data.gfa
$ ./ubwt index ./test_data/test.BWT_STR -fP
$ ./ubwt query ./test_data/test.BWT_STR ./test_data/test.query1
```

##  Commands and options
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
    -e    [STR] Edge sequence file in binary format. Required when output GFA format. [NULL]
    -k    [INT] Length of k-mer. Required when output GFA format.
    -o    [STR] Output file. [stdout]
    -a          Format of output file. [F]
                  "F": FASTA format.
                  "G": GFA format.
```
### Example:
```
# FASTA output
$ ./ubwt unipath ./test_data/chr20.ubwt -o ./test_data/chr20.unipath.fa
$ head -n4 ./test_data/chr20.unipath.fa
>1_246
GGCCAACATGGTGAAACCCCATCTCTACTAAAAATACAAAAATTAGCTGGGCGTCATGGCGGGCGCCTGTAGTCCCAGCTACCTGGGAGGTTGAGGTGGGAGAATCGCTTGAACCCGGGAGGCGGAGGCTGCAGCAGCTGAGATTGTGCCACTGCACTCCAGCCTTGGCCACAGAGCAAGACCTTGTCTCCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATATATATATAT
>2_55
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATATATATATATATATATATA

# GFA output
$ ./ubwt unipath ./test_data/chr20.ubwt -e ./test_data/chr20.edges -k 55 -o ./test_data/chr20.unipath.gfa -a G
$ head -n4 ./test_data/chr20.unipath.gfa
S	1	GGCCAACATGGTGAAACCCCATCTCTACTAAAAATACAAAAATTAGCTGGGCGTCATGGCGGGCGCCTGTAGTCCCAGCTACCTGGGAGGTTGAGGTGGGAGAATCGCTTGAACCCGGGAGGCGGAGGCTGCAGCAGCTGAGATTGTGCCACTGCACTCCAGCCTTGGCCACAGAGCAAGACCTTGTCTCCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATATATATATAT	LN:i:246
L	1	+	6	+	54M
S	2	AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATATATATATATATATATATA	LN:i:55
L	2	+	3	+	54M
```
### FASTA output format:
```
>uniID_uniLen
uniSeq
```
* uniID: ID of unipath
* uniLen: Length of unipath
* uniSeq: Sequence of unipath

### GFA output format:
```
S   uniID   uniSeq  LN:i:uniLen
L   uniID1  +   uniID2  +   xxxM
```
* uniID: ID of unipath
* uniSeq: Sequence of unipath
* uniLen: Length of unipath
* xxx: k-1


## Build BWT index for uni-path sequences
```
Usage:   ubwt index [option] <BWT-STR>

Options:

    -t    [INT] Number of threads. [1].
    -f    [STR] Format of input bwt-str. [B]
                  "B": binary file, 4-bit per bp, 0/1/2/3/4:A/C/G/T/#(first 64-bit: length).
                  "P": plain text.
    -o    [STR] Prefix of bwt-index file. [<BWT-STR>]
```
### Example
```
$ ./ubwt index -t2 ./test_data/chr20.ubwt
```
* Output index file will have `.ubwti` suffix, For example, `./test_data/chr20.ubwt.ubwti`

## Find exact match of query sequence on BWT index
```
Usage: ubwt query <BWT-index.prefix> <in-query> > match.out

       Find exact match of input query on BWT-index.
       Return <unipath name> and <offset(1-based)> on unipath.
```
### Example
```
$ ./ubwt query ./test_data/chr20.ubwt ./test_data/in.query
$ 9_661	11
```
* Output consists two columns: <unipath_name> <offset(1-based)> 

