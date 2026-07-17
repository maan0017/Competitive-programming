# Advanced C++ & Algorithm Optimizations: The GCD Pairs Masterclass

When solving hard array and mathematical problems (like LeetCode 3312: Sorted GCD Pair Queries), having the right logic is only half the battle. To drop your execution time from 500ms down to 1ms, you need to combine mathematical optimizations with low-level C++ tricks. 

Here is a cheat sheet of the concepts to learn and memorize.

---

## 1. Mathematical & Algorithmic Tricks

### The "Sieve" over "Square Root" Trick
**The Problem:** Finding factors of every number using a loop up to `sqrt(N)` takes $\mathcal{O}(N \sqrt{X})$ time. For $10^5$ numbers up to $50,000$, this is ~22 million operations.
**The Solution:** Instead of finding divisors for each number, count the frequencies of the numbers first. Then, iterate through *multiples* like the Sieve of Eratosthenes.
```cpp
// O(M log M) - Blazing Fast
for (int x = 1; x <= max_val; ++x) {
    for (int y = 2 * x; y <= max_val; y += x) {
        divisorCount[x] += divisorCount[y];
    }
}

```

*Takeaway: When a problem involves divisors, multiples, or GCDs across an array, a frequency map combined with a Sieve approach is almost always the optimal route.*

### Inclusion-Exclusion Principle

When you count pairs that share a common divisor `x`, you are also counting pairs whose GCD is a *multiple* of `x` (e.g., counting pairs divisible by 2 will also count pairs whose actual GCD is 4 or 6).

* **Formula:** `Exact_GCD[x] = Total_Divisible_By[x] - Sum(Exact_GCD[multiples of x])`
* Calculate this strictly in reverse (from `max_val` down to 1) so the multiples are already computed by the time you need them.

---

## 2. Memory & Structural Optimizations

### Global Arrays > `std::vector` inside functions

Every time a LeetCode function runs, allocating a large `std::vector` takes OS-level overhead.

* **The Trick:** Declare `int arr[50005]` globally outside the class. The memory is allocated exactly once when the program starts.
* **The Catch:** You must clean it up at the end of the function using `memset` so it's fresh for the next test case.
* *Bonus:* `memset(arr, 0, (max_val + 1) * sizeof(int))` only clears the exact memory you touched, saving even more time.

### Never Use Variable Length Arrays (VLAs)

```cpp
int n = nums.size();
long long arr[n]; // DANGEROUS!

```

This is a VLA. It allocates memory on the Stack instead of the Heap. If `n` is massive ($10^6$), this will cause a Stack Overflow. Standard C++ strictly forbids this (though GCC allows it as an extension). Always use `std::vector` or fixed-size global arrays.

### Let `std::upper_bound` Do The Heavy Lifting

Writing manual binary search `while(l < r)` loops for prefix-sum lookups is prone to off-by-one errors. Use the STL:

```cpp
// Returns the index of the first element strictly greater than 'query'
int index = std::upper_bound(arr.begin(), arr.end(), query) - arr.begin();

```

---

## 3. Competitive Programming (CP) Hacks

### The Fast I/O Lambda

LeetCode synchronizes C and C++ input/output streams by default. Disabling this speeds up how fast the platform feeds test cases into your code. Drop this outside your class:

```cpp
auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

```

### Bitwise Division

Instead of dividing by 2, use a bitwise right-shift. It does the exact same thing but leverages CPU bit-manipulation directly.

```cpp
long long pairs = (cnt * (cnt - 1LL)) >> 1; // Instead of / 2

```

### Compiler Pragmas

Force the judge's compiler to optimize your code to the absolute hardware limit by putting these at the very top of your file. This enables loop unrolling and advanced vector instructions (SIMD/AVX2).

```cpp
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

```

```

<FollowUp label="Want to dive deeper into the Sieve of Eratosthenes?" query="Explain how the harmonic series makes the Sieve of Eratosthenes O(N log N) instead of O(N^2)."/>

```