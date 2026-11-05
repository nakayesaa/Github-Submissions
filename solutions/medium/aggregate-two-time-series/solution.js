/**
 * @param {number[][]} series1
 * @param {number[][]} series2
 * @return {number[][]}
 */
var aggregateTimeSeries = function(series1, series2){
    let time = [
        ...series1.map(item => item[0]),
        ...series2.map(item => item[0])
    ];

    time.sort((a, b) => a - b);
    let timeSort = [];
    
    for(let i = 0; i < time.length; i++){
        if(i === 0 || time[i] !== time[i - 1]) timeSort.push(time[i]);
    }

    let counter = 0;
    let result = [];

    let indexA = 0;
    let indexB = 0;

    while(counter < timeSort.length){
        let current = timeSort[counter];

        while(indexA < series1.length && series1[indexA][0] < current)indexA++;
        while(indexB < series2.length && series2[indexB][0] < current) indexB++;

        let resA = 0;
        let resB = 0;

        if(indexA < series1.length) resA = series1[indexA][1];
        if(indexB < series2.length) resB = series2[indexB][1];
        
        result.push([current, resA + resB]);
        counter++;
    }

    return result;
};
