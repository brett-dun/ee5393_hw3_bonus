# Brett Duncan
# dunca384@umn.edu

class Var:
    def __init__(self, sym):
        self.sym = sym
    def __repr__(self):
        return self.sym

class Not:
    def __init__(self, exp):
        self.exp = exp
    def __repr__(self):
        return f'Not({self.exp})'

class And:
    def __init__(self, exp0, exp1):
        self.exp0 = exp0
        self.exp1 = exp1
    def __repr__(self):
        return f'And({self.exp0}, {self.exp1})'

class Nand:
    def __init__(self, exp0, exp1):
        self.exp0 = exp0
        self.exp1 = exp1
    def __repr__(self):
        return f'Nand({self.exp0}, {self.exp1})'

class Or:
    def __init__(self, exp0, exp1):
        self.exp0 = exp0
        self.exp1 = exp1
    def __repr__(self):
        return f'Or({self.exp0}, {self.exp1})'

class Nor:
    def __init__(self, exp0, exp1):
        self.exp0 = exp0
        self.exp1 = exp1
    def __repr__(self):
        return f'Nor({self.exp0}, {self.exp1})'

class Xor:
    def __init__(self, exp0, exp1):
        self.exp0 = exp0
        self.exp1 = exp1
    def __repr__(self):
        return f'Xor({self.exp0}, {self.exp1})'

class Xnor:
    def __init__(self, exp0, exp1):
        self.exp0 = exp0
        self.exp1 = exp1
    def __repr__(self):
        return f'Xnor({self.exp0}, {self.exp1})'


"""
Print an expression tree using a depth first search
"""
def decompose(exp, indent=0):
    t = type(exp)
    if t == Var:
        print(' '*indent, exp)
    elif t == Not:
        print(' '*indent, 'Not')
        decompose(exp.exp, indent+1)
    elif t == And:
        print(' '*indent, 'And')
        decompose(exp.exp0, indent+1)
        decompose(exp.exp1, indent+1)
    elif t == Nand:
        print(' '*indent, 'Nand')
        decompose(exp.exp0, indent+1)
        decompose(exp.exp1, indent+1)
    elif t == Or:
        print(' '*indent, 'Or')
        decompose(exp.exp0, indent+1)
        decompose(exp.exp1, indent+1)
    elif t == Nor:
        print(' '*indent, 'Nor')
        decompose(exp.exp0, indent+1)
        decompose(exp.exp1, indent+1)
    elif t == Xor:
        print(' '*indent, 'Xor')
        decompose(exp.exp0, indent+1)
        decompose(exp.exp1, indent+1)
    elif t == Xnor:
        print(' '*indent, 'Xnor')
        decompose(exp.exp0, indent+1)
        decompose(exp.exp1, indent+1)


# permuations given for the homework
# (this could be generated dynamically)
permuations = {
    "A": [1, 4, 3, 5, 2],
    "B": [1, 4, 5, 2, 3],
    "C": [1, 3, 4, 2, 5],
    "D": [1, 2, 4, 5, 3],
    "E": [1, 4, 2, 3, 5],
}

# map of permutations to their inverses
inverses = {
    "A": "A'",
    "B": "B'",
    "C": "C'",
    "D": "D'",
    "E": "E'"
}

# lookup table of permutation definitions
lookup = {
    "A": ["C", "B", "C'", "B'"],
    "A'": ["B", "C", "B'", "C'"],
    "B": ["C", "D", "C'", "D'"],
    "B'": ["D", "C", "D'", "C'"],
    "C": ["D", "E", "D'", "E'"],
    "C'": ["E", "D", "E'", "D'"],
    "D": ["E", "B", "E'", "B'"],
    "D'": ["B", "E", "B'", "E'"],
    "E": ["D", "A", "D'", "A'"],
    "E'": ["A", "D", "A'", "D'"]
}

# map permutations to a variable name for the c++ code
var_lookup = {
    "A": "A",
    "A'": "A_inv",
    "B": "B",
    "B'": "B_inv",
    "C": "C",
    "C'": "C_inv",
    "D": "D",
    "D'": "D_inv",
    "E": "E",
    "E'": "E_inv",
    "*": "I"
}


"""
Build an expression using Nand, And, and Not
"""
def build_exp(exp):
    t = type(exp)
    if t == Var:
        return exp
    elif t == Not:
        ex = exp.exp
        tt = type(ex)
        if tt == Var:
            return Not(ex)
        elif tt == Not:
            return build_exp(ex.exp)
        elif tt == And:
            # And -> Nand
            return build_exp(Nand(ex.exp0, ex.exp1))
        elif tt == Nand:
            # Nand -> And
            return build_exp(And(ex.exp0, ex.exp1))
        elif tt == Or:
            # Or -> Nor
            return build_exp(Nor(ex.exp0, ex.exp1))
        elif tt == Nor:
            # Nor -> Or
            return build_exp(Or(ex.exp0, ex.exp1))
        elif tt == Xor:
            # Xor -> Xnor
            return build_exp(Xnor(ex.exp0, ex.exp1))
        elif tt == Xnor:
            # Xnor -> Xor
            return build_exp(Xor(ex.exp0, ex.exp1))
    elif t == And:
        return And(build_exp(exp.exp0), build_exp(exp.exp1))
    elif t == Nand:
        return Nand(build_exp(exp.exp0), build_exp(exp.exp1))
    elif t == Or:
        return build_exp(Nand(Not(exp.exp0), Not(exp.exp1)))
    elif t == Nor:
        return build_exp(And(Not(exp.exp0), Not(exp.exp1)))
    elif t == Xor:
        return build_exp(And(Nand(Not(exp.exp0), Not(exp.exp1)), Nand(exp.exp0, exp.exp1)))
    elif t == Xnor:
        return build_exp(Nand(Nand(Not(exp.exp0), Not(exp.exp1)), Nand(exp.exp0, exp.exp1)))


"""
Build a sequence of conditional permutations given an expression containing only the following:
- variables
- nots of variables
- and
- nand

perm is the permutation to start with.
"""
def build_seq(exp, perm='A'):
    t = type(exp)
    p = lookup[perm]
    if t == Var:
        return [(exp, (perm, '*'))]
    elif t == Not:
        ex = exp.exp
        tt = type(ex)
        if tt == Var:
            return [(ex, ('*', perm))]
        else:
            # Not(expression) is not valid here
            raise TypeError()
    elif t == And:
        return build_seq(exp.exp0, p[0]) + \
                    build_seq(exp.exp1, p[1]) + \
                    build_seq(exp.exp0, p[2]) + \
                    build_seq(exp.exp1, p[3])
    elif t == Nand:
        return build_seq(exp.exp0, p[1]) + \
                    build_seq(exp.exp1, p[0]) + \
                    build_seq(exp.exp0, p[3]) + \
                    build_seq(exp.exp1, p[2]) + \
                    [('*', (perm, perm))]
    else:
        # raise an error if we run into some other type
        raise TypeError()


"""
Build the transition arrays
"""
def build_transitions():
    d = {}
    for key,val in permuations.items():
        # [1, 5] -> [0, 4] for indexing in code
        nums = [v-1 for v in val]

        # generate transition pairs
        pairs = [((v,nums[i+1]) if i != len(nums)-1 else (v,nums[0])) for i,v in enumerate(nums)]

        # sort by second element
        arr = [v[0] for v in sorted(pairs, key=lambda x:x[1])]
        # sort by first element
        arr_inv = [v[1] for v in sorted(pairs, key=lambda x:x[0])]

        # add these transitions to the dictionary
        d[key] = arr
        d[inverses[key]] = arr_inv
    return d

"""
Build the C++ code
"""
def build_cc(seq, vs):
    consts = '\n    '.join(f'const d_type {var.sym} = _{var.sym} ? TRUE : FALSE;' for var in vs)

    states = []
    for i,perm in enumerate(seq):
        prev = 's' if i == 0 else f's{i}'
        key = perm[0]
        left = var_lookup[perm[1][0]]
        right = var_lookup[perm[1][1]]
        if key != '*':
            new_state = f"""
    const std::array<d_type, len> s{i+1} = {{
        ({prev}[{left}[0]] & {key}) | ({prev}[{right}[0]] & ~{key}),
        ({prev}[{left}[1]] & {key}) | ({prev}[{right}[1]] & ~{key}),
        ({prev}[{left}[2]] & {key}) | ({prev}[{right}[2]] & ~{key}),
        ({prev}[{left}[3]] & {key}) | ({prev}[{right}[3]] & ~{key}),
        ({prev}[{left}[4]] & {key}) | ({prev}[{right}[4]] & ~{key})
    }};
"""
            states.append(new_state)
        else:
            new_state = f"""
    const std::array<d_type, len> s{i+1} = {{
        {prev}[{left}[0]],
        {prev}[{left}[1]],
        {prev}[{left}[2]],
        {prev}[{left}[3]],
        {prev}[{left}[4]]
    }};
"""
            states.append(new_state)

    last = i
    s = ''.join(states)

    transistions = []
    for k,v in build_transitions().items():
        idk = ", ".join([str(s) for s in v])
        transistions.append((f'constexpr std::array<std::size_t, len> {var_lookup[k]} = {{{idk}}};'))
    t = '\n'.join(transistions)

    code = f"""
#include <array>
#include "stdint.h"
#include "stdio.h"

// Data type to use. (This is arbitrary.)
typedef uint8_t d_type;


// Note: constexpr is used here to make the logic more clear. At compile time constexpr is removed
// by the compiler and replaced with the literal values that were determined at compile time. I
// used c++ 14 when writing/testing this program.


// Length of the states and permuations
constexpr std::size_t len = 5;

{t}

constexpr std::array<std::size_t, len> I = {{0, 1, 2, 3, 4}};

// Function to compute the resulting permutation given an input state and variables.
std::array<d_type, len> func(const std::array<d_type, len> s, {', '.join(f'const bool _{var.sym}' for var in vs)}) {{

    // true and false values where all bits are true or false
    constexpr d_type TRUE = 0xFF;
    constexpr d_type FALSE = 0x00;

    {consts}

    {s}

    // return the last state we calculated
    return s{last+1};
}}

int main() {{
    std::array<d_type, len> state = {{1, 2, 3, 4, 5}}; // starting state
    for (int i = 0; i < {2**len(vs)}; i++) {{
        std::array<d_type, len> result = func(state, {', '.join(reversed([f'i&{2**i}' for i,_ in enumerate(vs)]))});
        printf("%d %d %d %d %d\\n", result[0], result[1], result[2], result[3], result[4]);
    }}
}}
"""
    return code


"""
Generate code and write to file. Inputs are the expression, variable list, and file name.
"""
def generate(exp, var_list, file):
    # print out the expression
    print(exp)

    # Rebuild the expression using only NAND and AND
    exp = build_exp(exp)

    # print out the new expression
    print(exp)

    # print out the new expression as a tree to make it easier to read/understand
    decompose(exp)

    # build the sequence of conditional permutations
    seq = build_seq(exp, "A")

    # print out the sequence of conditional permutations
    for p in seq:
        print(p)

    # generate the c++ code from the sequence + list of variables
    code = build_cc(seq, var_list)

    # write the generated code to a file
    with open(file, 'w') as f:
        f.write(code)


# Define are variables
x = Var('x')
y = Var('y')
z = Var('z')
x1 = Var('x1')
x2 = Var('x2')
x3 = Var('x3')
x4 = Var('x4')

expressions_to_generate = [
    (Or(x, y), [x,y], 'or.cc'),
    (Nor(x, y), [x,y], 'nor.cc'),
    (And(x, y), [x,y], 'and.cc'),
    (Nand(x, y), [x,y], 'nand.cc'),
    (Xor(x, y), [x,y], 'xor.cc'),
    (Xnor(x, y), [x,y], 'xnor.cc'),
    (Or(And(Not(x), Not(y)), And(Not(y), z)), [x,y,z], 'f1.cc'),
    (Xor(Xor(Not(x1), x2), Xor(Not(x3), Not(x4))), [x1,x2,x3,x4], 'f2.cc')
]

# uncomment this to generate all of the expressions
# for exp, var_list, file in expressions_to_generate:
#     generate(exp, var_list, file)

generate(*expressions_to_generate[-1])
