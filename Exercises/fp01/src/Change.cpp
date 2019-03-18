/*
 * Change.cpp
 */

#include "Change.h"

string calcChange(int m, int numCoins, int *coinValues)
{
	// Create the vectors for the calculations of minimum ammount of coins and last coin inserted
    vector<int> min(m+1,0);
    vector<int> last(m+1,0);

    // Exit if there is no change to give
    if(m == 0)
    	return "";

    // Cycle through all coin "types"
    for(int i = 1; i <= numCoins;i++){

    	// Cycle through all changes up to final change. Note: we can skip the k's leading to the value of the current
    	// top-coin value.
    	for(int k = coinValues[i-1]; k <= m;k++){

    		// Calculate the new minimum value
    		int newMin = 1 + min.at(k-coinValues[i-1]);

    		// Check if we got a new minimum
    		if(newMin >= min.at(k) && min.at(k) != 0)
    			continue;
    		else{
    			// Fill the vectors
    			min.at(k) = newMin;
    			last.at(k) = i;
    		}
    	}
    }

    // Get the final result

    stringstream result;
    int total = m;

    // If the total is zero, then we can't make the desired change with the given coins and return "-"
    if(last.at(total) == 0)
    	return "-";

    // Build the string containing the result
    do{
    	result << coinValues[last.at(total)-1] << ';';
    	total -=coinValues[last.at(total)-1];

    }while(total > 0);

    return result.str();
}


