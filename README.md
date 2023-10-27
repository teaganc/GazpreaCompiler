# Gazprea Compiler

A compiler using Antlr4 that compiles to LLVM IR. Matrix, vectors and tuple are first class data types. Purely functional functions and non-pure procedures allow for aggressive constant folding. 


```
function generate_vector(real[*] x) returns real[*];

function generate_matrix() returns real[*, *] {
	real[3, 2] m = [];
	loop i = 1..2, j = 1..3 {
		m[i,j] = i * j;
	}
	return m;
}

function square(integer x) returns integer = x * x;

function fib(integer x) returns integer {
	if (x <= 1) {
		return 1;
	}
	return fib(x - 1) + fib(x - 2);
}

procedure main() returns integer {
	// inteligent casting. x = [1,1]
	real[2] x = as<real[*]>(1);
	
	// dot product/ matrix multiply operator
	real[*,*] m = generate_matrix() ** generate_vector(x);
	
	// print 
	m[2,2] -> std_output;
	return 0;
}

function generate_vector(real[*] x) returns real[*] {
	// Integer type deduced. This is a range, filter and map
	var[*] v = [i in 1..5 & i % 2 = 0 | square(fib(i))];
	
	// cast and element wise multiply
	return as<real[*]>(v) * x;
}

```

Due to the pure nature of functions our constant folding can aggressively target the calls in main and generate run time code which is simply a single number to print. Dead code elimination can completely remove all functions but main. All this while compiling in an amount of time on the same maginitude as it would take to run without this optimization. 