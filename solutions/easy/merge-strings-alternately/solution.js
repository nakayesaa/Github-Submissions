/**
 * @param {string} word1
 * @param {string} word2
 * @return {string}
 */
var mergeAlternately = function(word1, word2) {
    let i = 0
    let j = 0
    let str = ""
    const sumLength = word1.length + word2.length
    for(let z = 0; z < sumLength; z++){
        if( z < word1.length){
            str += word1[i]
            i++
        }
        if(z < word2.length){
            str += word2[j]
            j++
        }
    }
    return str
};
