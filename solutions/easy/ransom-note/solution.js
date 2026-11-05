/**
 * @param {string} ransomNote
 * @param {string} magazine
 * @return {boolean}
 */
var canConstruct = function(ransomNote, magazine) {

    for(result of magazine){
        ransomNote = ransomNote.replace(result, "")
    }
    if(!ransomNote) return true
    else{
        return false
    }
};
