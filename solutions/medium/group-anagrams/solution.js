/**
 * @param {string[]} strs
 * @return {string[][]}
 */
var groupAnagrams = function(strs) {
  let anagram = new Map()

  for(let copy of strs){
    let sorted = copy.split('').sort().join('')

    if(!anagram.has(sorted)){
        anagram.set(sorted, [])
    }
    anagram.get(sorted).push(copy)
  }  

  return Array.from(anagram.values())
};
