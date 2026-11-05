/**
 * @param {number[]} candies
 * @param {number} extraCandies
 * @return {boolean[]}
 */
var kidsWithCandies = function(candies, extraCandies) {
    let maxCandies = Math.max(...candies)
    let array = []
    for(let i = 0; i<candies.length;i++){
        array.push(candies[i] + extraCandies>= maxCandies)
    }
    return array
};
