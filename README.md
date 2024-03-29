## Author
**Brett Duncan** (dunca384@umn.edu)


## Usage

Run `ee5393_hw3_bonus.py` to generate the C++ files.

Modify `expressions_to_generate` to change the functions that get generated by the script.

## Example Outputs
### or.cc
`Or(x, y)`
```
1 2 3 4 5
2 5 4 1 3
2 5 4 1 3
2 5 4 1 3
```

### nor.cc
`Nor(x, y)`
```
2 5 4 1 3
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
```

### and.cc
`And(x, y)`
```
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
2 5 4 1 3
```

### nand.cc
`Nand(x, y)`
```
2 5 4 1 3
2 5 4 1 3
2 5 4 1 3
1 2 3 4 5
```

### xor.cc
`Xor(x, y)`
```
1 2 3 4 5
2 5 4 1 3
2 5 4 1 3
1 2 3 4 5
```

### xnor.cc
`Xnor(x, y)`
```
2 5 4 1 3
1 2 3 4 5
1 2 3 4 5
2 5 4 1 3
```

### f1.cc
`Or(And(Not(x), Not(y)), And(Not(y), z))`
```
2 5 4 1 3
2 5 4 1 3
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
2 5 4 1 3
1 2 3 4 5
1 2 3 4 5
```

### f2.cc
`Xor(Xor(Not(x1), x2), Xor(Not(x3), Not(x4)))`
```
2 5 4 1 3
1 2 3 4 5
1 2 3 4 5
2 5 4 1 3
1 2 3 4 5
2 5 4 1 3
2 5 4 1 3
1 2 3 4 5
1 2 3 4 5
2 5 4 1 3
2 5 4 1 3
1 2 3 4 5
2 5 4 1 3
1 2 3 4 5
1 2 3 4 5
2 5 4 1 3
```
