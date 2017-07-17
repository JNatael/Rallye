//Defines the entry point for the console application.
#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
#include <math.h>
using namespace std;

/*
This function reads a line of int values into a vector function and returns that
vector.
*/
vector<int> readlineofints(int count) {
    // Input values
    vector<int> linevalues(count);
    for (int j = 0; j < count; j++) {
        int val;
        cin >> val;
        linevalues[j] = val;
    }
    return linevalues; // Return line values as a vector
}


//Calculate the sum of a column of the times based on inputs
long time_sum(int (&times)[2][11],int column, int start, int finish) {
    long result = 0;
    for (int i = start; i < finish; i++) {
        result += times[column][i];
    }
    return result;
}

/*Calculate the min time this day takes to run. This is just a brute force approach
*/
long calculate_day_min(int (&times)[2][11],long checkpoints, long &change_time) {
    long min_time = 2147483647; //Set to long max
    for (int i = 0; i <= checkpoints; i++) { //Iterate through checkpoints
        long start_column_0 = time_sum(times, 0, 0, i) + time_sum(times, 1, i, checkpoints + 1); //Add the first column up through i-1 and the second column from i through checkpoints
        long start_column_1 = time_sum(times, 1, 0, i) + time_sum(times, 0, i, checkpoints + 1); //Add the second column up through i-1 and the first column from i through checkpoints
        
        //If we change during this day, add the change time
        if (i != 0) {
            start_column_0 += change_time;
            start_column_1 += change_time;
        }
        min_time = min(min_time, min(start_column_0, start_column_1)); //Set the min time to the smallest of it's previous value and the smaller of the two values from today
    }
    return min_time;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    // get test case count
    int t;
    std::cin >> t;

    //! loop over all the test cases
    for (int i = 1; i <= t; i++) {
        // Read in params
        vector<int> params = readlineofints(3);
        long d = params[0];
        long c = params[1];
        long m = params[2];

        //Loop over inputs
        vector<int> motocross_times, car_times;
        car_times = readlineofints(d*(c + 1));
        motocross_times = readlineofints(d*(c + 1));
        

        long total_time = 0; //Set to long max
        int times_today[2][11];
        //Iterate over days
        for (int j = 0; j < d; j++) {
            //Set up today's times array
            for (int k = 0; k < 11; k++) {
                if (k <= c) { //If we're before or at the day end, add the time
                    times_today[0][k] = car_times[j*(c + 1) + k];
                    times_today[1][k] = motocross_times[j*(c + 1) + k];
                }
                else { //If we're after day end set to 0
                    times_today[0][k] = 0;
                    times_today[1][k] = 0;
                }
            }
            total_time +=calculate_day_min(times_today, c, m); //Add today's min time to the total time
        }


        //Print output
        std::cout << "Case #" << i << ": "<< total_time << std::endl;
    }
    return 0;
}