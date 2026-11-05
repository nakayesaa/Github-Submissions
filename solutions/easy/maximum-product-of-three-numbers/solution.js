/**
 * @param {number[]} nums
 * @return {number}
 */
var maximumProduct = function(nums) {
    let a = nums.length - 1
    nums.sort((a,b)=> a - b)
    const Result1 = nums[0] * nums[1] * nums[a]
    const Result2 = nums[a] * nums[a-1] * nums[a-2]

    return Math.max(Result1, Result2) 
};
