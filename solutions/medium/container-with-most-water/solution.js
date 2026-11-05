/**
 * @param {number[]} height
 * @return {number}
 */
var maxArea = function(height) {
  let a = 0
  let b = height.length - 1
  let max = 0
  while(a<b){
    let result = Math.min(height[a], height[b]) * (b - a)
    max = Math.max(max, result)

    if(height[a] < height[b]){
        a++
    } else b--
  }  

  return max
};
