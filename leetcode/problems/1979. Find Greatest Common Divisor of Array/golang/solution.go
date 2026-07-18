package main

import (
	"fmt"
	"time"
)

// uses "Recursion"
func gcd(a, b int) int {
	if b == 0 {
		return a
	}

	return gcd(b, a%b)
}

// uses "Iterations"
func gcd_v2(a, b int) int {
	if a < 0 {
		a = -a
	}
	if b < 0 {
		b = -b
	}

	for b != 0 {
		a, b = b, a%b
	}

	return a
}

func MinMax(nums []int) (minVal, maxVal int) {
	if len(nums) == 0 {
		panic("empty slice")
	}

	n := len(nums)

	// Initialize depending on odd/even length
	start := 1
	if n%2 == 0 {
		if nums[0] < nums[1] {
			minVal = nums[0]
			maxVal = nums[1]
		} else {
			minVal = nums[1]
			maxVal = nums[0]
		}
		start = 2
	} else {
		minVal = nums[0]
		maxVal = nums[0]
	}

	// Process elements in pairs
	for i := start; i < n-1; i += 2 {
		var small, large int

		if nums[i] < nums[i+1] {
			small = nums[i]
			large = nums[i+1]
		} else {
			small = nums[i+1]
			large = nums[i]
		}

		if small < minVal {
			minVal = small
		}
		if large > maxVal {
			maxVal = large
		}
	}

	return
}

func runTest(id int, nums []int, expected int) {
	start := time.Now()

	output := findGCD(nums)

	elapsed := time.Since(start)

	if output == expected {
		fmt.Printf("✅ Test Case %d Passed (%v)\n", id, elapsed)
	} else {
		fmt.Printf("❌ Test Case %d Failed (%v)\n", id, elapsed)
		fmt.Printf("Expected: %d\n", expected)
		fmt.Printf("Output  : %d\n", output)
	}

	fmt.Println("----------------------------------")
}

// func findGCD(nums []int) int {
// 	minv, maxv := 1000, 0
// 	for _, v := range nums {
// 		minv = min(minv, v)
// 		maxv = max(maxv, v)
// 	}
// 	for minv != 0 {
// 		minv, maxv = maxv%minv, minv
// 	}
// 	return maxv
// }

func findGCD(nums []int) int {
	minVal, maxVal := MinMax(nums)

	// now return gcd
	return gcd(minVal, maxVal)
}

func main() {
	nums1 := []int{2, 5, 6, 9, 10}
	expected1 := 2

	nums2 := []int{7, 5, 6, 8, 3}
	expected2 := 1

	nums3 := []int{3, 3}
	expected3 := 3

	runTest(1, nums1, expected1)
	runTest(2, nums2, expected2)
	runTest(3, nums3, expected3)
}
