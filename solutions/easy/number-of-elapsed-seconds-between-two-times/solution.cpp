class Solution {
public:
    int secondsBetweenTimes(string startTime, string endTime){
        string hour1 = startTime.substr(0,2);
        string hour2 = endTime.substr(0,2);
        if(hour1[0] == '0') hour1 = hour1.substr(1,1);
        if(hour2[0] == '0') hour2 = hour2.substr(1,1);
        int hourdiff = stoi(hour2) - stoi(hour1);
        int hourfar = hourdiff * 60 * 60;

        string minutes1 = startTime.substr(3,2);
        string minutes2 = endTime.substr(3,2);
        if(minutes1[0] == '0') minutes1 = minutes1.substr(1,1);
        if(minutes2[0] == '0') minutes2 = minutes2.substr(1,1);
        int minutesdiff = stoi(minutes2) - stoi(minutes1);
        int minutesfar = minutesdiff * 60;

        
        string second1 = startTime.substr(6,2);
        string second2 = endTime.substr(6,2);
        if(second1[0] == '0') second1 = second1.substr(1,1);
        if(second2[0] == '0') second2 = second2.substr(1,1);
        int seconddiff = stoi(second2) - stoi(second1);

        int res = hourfar +  minutesfar + seconddiff;
        return res;
    }
};
