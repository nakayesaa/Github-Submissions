/**
 * @param {number[]} nums
 * @return {number}
 */
var missingNumber = function(nums) {
    let xor = 0
    let size = nums.length

    for(let i = 0; i<=size; i++){
        xor ^= i
    }  

    for(let babi of nums){
        xor ^= babi
    }
    return xor
};
