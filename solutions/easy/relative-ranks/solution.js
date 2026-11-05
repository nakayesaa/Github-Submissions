/**
 * @param {number[]} score
 * @return {string[]}
 */
var findRelativeRanks = function(score) {
    let Sorting = [...score].sort((a,b) => b - a)
    let Map = {}

    for(let i = 0; i<Sorting.length; i++){
        if(i  === 0) Map[Sorting[i]] = "Gold Medal"
        else if(i === 1) Map[Sorting[i]] = "Silver Medal"
        else if(i === 2) Map[Sorting[i]] = "Bronze Medal"
        else Map[Sorting[i]] = (i+1).toString()
    }

    return score.map(s => Map[s])
};
