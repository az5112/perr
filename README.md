## perr

`perr` - or pretty error - a possibly convenient (if a bit slow) replacement for `std::cerr`.
Decorates output with source points and handles STL containers out of the box.
Excellent for toy projects and debugging homework :-)

### Source file location

Messages printed to the standard error are prefixed with the file name and the line number, for example:

```cpp
#include "perr.h"

int main() {
	perr << "Hello world";
};
```

This prints the hello-world message prefixed with the source location:

```
hello-world.cpp : 4    Hello world
```

The new line at the end is inserted automatically.

Tweak the message prefix to your liking inside the `stream` method.
You can change colors, add timestamps or the function name.

To disable colors, compile with `-DNOCOLOR`.


### Printing of STL containers

The header also contains overloads that allow convenient printing of STL containers,
such as a vector, a map, or a set.

```cpp
#include <vector>
#include "perr.h"

int main() {
	std::vector< int > v = { 1, 2, 3 };
	perr << v;

	v.push_back(44);
	perr << v;

	v.clear();
	perr << v;
};
```

This prints:

```
vector-int.cpp : 6    V[1, 2, 3]
vector-int.cpp : 9    V[1, 2, 3, 44]
vector-int.cpp : 12   V[]
```

To print a vector of structs, define `operator<<` only for the struct,
like so:

```cpp
#include <vector>
#include "perr.h"

struct Rectangle {
	int height;
	int width;
};

std::ostream& operator<< (std::ostream& os, Rectangle const& r) {
	os << "{" << r.height << "x" << r.width << "}";
	return os;
};

int main() {
	std::vector< Rectangle > vr = { {2, 3}, {4, 5} };
	perr << vr;
}
```

The output will be:

```
vector-struct.cpp : 16   V[{2x3}, {4x5}]
```

### Under the hood

`perr` is a macro that creates a temporary `PrettyStream` object and
calls the `.stream()` method immediately after.
A call to the `stream()` method returns `std::cerr`.

```cpp
  #define perr PrettyStream( std::cerr, __PRETTY_FUNCTION__, __FILE__, __LINE__ ).stream()
```

The constructor captures the name of the function and the file and the line number.
The `.stream()` method pretty-prints this information to the underlying `std::cerr` stream before returning it.
The caller gets `std::cerr` but with a nice line prefix.

When the `PrettyStream` object is destroyed, the destructor prints `std::endl` to the stream.
This is neat and simple (and predates `std::basic_stacktrace` by a few years).

### History

I have been using `perr.h` for debugging toy projects and competitive coding tasks.
The current version is sprinkled with new language features (parameter packs, `requires` clauses, etc).
Compile with `-std=c++20` (gcc/clang).

Some functionality - such as printing out heaps as ASCII art - has been removed.
I may restore it in the future.
