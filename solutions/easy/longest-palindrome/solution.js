/**
 * @param {string} s
 * @return {number}
 */
 var longestPalindrome = function(s) {
    let map = new Map()

    for(let string of s){
        if(map.has(string)){
            map.set(string, map.get(string) + 1 )
        } else{
        map.set(string, 1)}
    }
    let totaleven = 0
    let odd  = false
    for(value of map.values()){
        if(value %2 === 0){
            totaleven += value
        } else {
            totaleven += value - 1
            odd = true
        }
    }
    return odd? totaleven + 1 : totaleven
};
