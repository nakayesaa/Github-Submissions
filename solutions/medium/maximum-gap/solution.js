/**
 * @param {number[]} nums
 * @return {number}
 */

var maximumGap = function(nums) {
    if (nums.length < 2) return 0;

    // Find minimum and maximum values
    let minVal = Math.min(...nums);
    let maxVal = Math.max(...nums);

    // If all elements are the same, the maximum gap is 0
    if (minVal === maxVal) return 0;

    // Bucket size is the integer division of range and the number of buckets
    let bucketSize = Math.ceil((maxVal - minVal) / (nums.length - 1));
    let bucketCount = Math.floor((maxVal - minVal) / bucketSize) + 1;

    // Initialize buckets
    let Bucket = Array.from({ length: bucketCount }, () => ({ min: Infinity, max: -Infinity }));

    // Populate buckets
    for (const num of nums) {
        let bucketIndex = Math.floor((num - minVal) / bucketSize);
        if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1; // Fix index if it is out of bounds
        Bucket[bucketIndex].min = Math.min(Bucket[bucketIndex].min, num);
        Bucket[bucketIndex].max = Math.max(Bucket[bucketIndex].max, num);
    }

    // Calculate the maximum gap
    let maxGap = 0;
    let previousMax = minVal;

    for (const bucket of Bucket) {
        if (bucket.min === Infinity) continue; // Skip empty buckets
        maxGap = Math.max(maxGap, bucket.min - previousMax);
        previousMax = bucket.max;
    }

    return maxGap;
};
