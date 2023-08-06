#include "SeparateChaining.h"
#include "LinearProbing.h"
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

int main() {
    // Create two hash maps, one for rain data, and one for temperature data
    chainingHashMap mapA(1000);
    linearHashMap mapB(1000);
    string line;

    // Open the weather.csv file
    ifstream file("weather.csv");

    if (file.is_open()) {
        
        
        while(getline(file, line)){ // Read each line from the file
            stringstream ss(line);
            string token;
            vector<string> row;
            
            // Break each line into tokens separated by commas
            while (std::getline(ss, token, ',')) {
                // Remove double quotes from the token if they exist
                if (token.front() == '"' && token.back() == '"')
                    token = token.substr(1, token.size() - 2);
                // Add each token to the row vector
                row.push_back(token);
            }
            
            if (row.size() < 15) { // Change the number to match your column count
                continue; // Skip this iteration of the loop if the row is too short
            }

            // Parse the needed values from each row
            string precipitation = row[0];  //0: precipitation
            string dateFull = row[1];       //1: dateFull
            string city = row[5];           //5:city
            string maxTemp = row[11];       //10:max temp
            string minTemp = row[12];       //11: min temp
            string windSpeed = row[14];     //13: wind speed
            // the rows are off becuase theres a comma in row 8 that extends the row value by 1 after it
            
            // Insert parsed values into the hash maps
            mapA.insert(dateFull + city, precipitation, windSpeed);  
            mapB.insert(dateFull + city, minTemp, maxTemp);  
        }

        file.close();
    }

    else {
        cout << "Unable to open the file." << endl;
        return 1;
    }


    bool interface = true;
    while(interface){    // Interface loop
        string input;
        string date;
        string city;
        
        cout << " Welcome to the Weather Almanac " << endl
             << "--------------------------------" << endl 
             << "1. Insert your own findings" << endl
             << "2. Remove errors found in data" << endl
             << "3. Find recorded temperatures" << endl
             << "4. Find recorded downpours" << endl    
             << "5. Exit" << endl
             << "--------------------------------" << endl;

        cin >> input;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cout << endl;

        if (input == "1"){ // If the user chooses to insert their own findings
            string choice;
            cout << "rain or temp" << endl;
            getline(cin, choice);

            // Get the date and city for the data the user wants to insert
            cout << "Enter the Full Date (YYYY-MM-DD)" << endl;
            getline(cin, date);
            cout << "Enter the Specific city" << endl;
            getline(cin, city);
            string key = date + city;

            
            if(choice == "rain"){ // If the user is inserting rain data
                string precipitation;
                string windSpeed;
                cout << "Enter precipitation: ";
                getline(cin, precipitation);
                cout << "Enter wind speed: ";
                getline(cin, windSpeed);
                mapA.insert(key, precipitation, windSpeed);
            } 

            else if(choice == "temp"){ // If the user is inserting temperature data

                string minTemp;
                string maxTemp;
                cout << "Enter minimum temperature: ";
                getline(cin, minTemp);
                cout << "Enter maximum temperature: ";
                getline(cin, maxTemp);
                // Insert the data into the temperature data hash map
                mapB.insert(key, minTemp, maxTemp);

                cout << "Data inserted!" << endl;

            }
            
            cout << endl;
        }

        if (input == "2") { // If the user chooses to remove data
            cout << "Enter the Full Date (YYYY-MM-DD)" << endl;
            getline(cin, date);
            cout << "Enter the Specific city" << endl;
            getline(cin, city);
            string key = date + city;
            mapA.remove(key);
            mapB.remove(key);
            cout << endl;
            cout << "Data removed successfully." << endl;
            cout << endl;
            cout << endl;
        }

        if (input == "3") { // If the user chooses to find temperature data
            cout << "Enter the Full Date (YYYY-MM-DD)" << endl;
            getline(cin, date);
            cout << "Enter the Specific city" << endl;
            getline(cin, city);
            string key = date + city;
            pair<string, string> temps = mapB.find(key);

            if (temps.first != "-1" && temps.second != "-1") {
                cout << "Min Temp: " << temps.first << "  ||  " << "Max Temp: " << temps.second << endl;
                cout << endl;
                cout << endl;
            } 
                        
            else { // If the data was not found, print a message saying so
                cout << "No data found." << endl;
                cout << endl;
                cout << endl;
            }
        }

        
        if (input == "4") { // If the user chooses to find rain data
            // Get the date and city for the data the user wants to find
            cout << "Enter the Full Date (YYYY-MM-DD)" << endl;
            getline(cin, date);
            cout << "Enter the Specific city" << endl;
            getline(cin, city);
            string key = date + city;
            // Find the rain data in the rain data hash map
            pair<string, string> weather = mapA.find(key);
            // If the data was found, print it
            if (weather.first != "-1" && weather.second != "-1") {
                cout << "Precipitation: " << weather.first << "  ||  " << "Wind Speed: " << weather.second << endl;
                cout << endl;
                cout << endl;
            } 
            
            // If the data was not found, print a message saying so
            else {
                cout << "No data found." << endl;
                cout << endl;
                cout << endl;
            }
        }

        // If the user chooses to exit
        if (input == "5"){
            cout << "Goodbye for now!" << endl;
            cout << endl;
            cout << "Terminating Program....." << endl;
            // End the interface loop
            interface = false;
        }
    }

    return 0;
}




