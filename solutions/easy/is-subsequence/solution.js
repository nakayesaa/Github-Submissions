/**
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
var isSubsequence = function(s, t) {
    let a = 0

    for(let i = 0; i<t.length;i ++){
        if(t[i] === s[a]){
            a++
        }
        if(s.length === a){
            return true
        }
    }

    return a === s.length
};
