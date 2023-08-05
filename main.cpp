#include "SeparateChaining.h"
#include "LinearProbing.h"
#include <fstream>
#include <sstream>

using namespace std;


int main() {

    chainingHashMap mapA(1000);
    linearHashMap mapB(1000);



    getline(file, line);
    ifstream file("weather.csv");
    string line;

    while(getline(file, line)){
        stringstream ss(line);
        string token;        
        vector<string> row;
        while (std::getline(ss, token, ',')) {
            // Remove double quotes from the token if they exist
            if (token.front() == '"' && token.back() == '"')
                token = token.substr(1, token.size() - 2);
            row.push_back(token);
        }
        
        string precipitation = row[0];
        string dateFull = row[1];
        string city = row[6];
        string minTemp = row[11];
        string maxTemp = row[12];
        string windSpeed = row[14];

        mapA.insert(dateFull + city, precipitation, windSpeed);  
        mapB.insert(dateFull + city, minTemp, maxTemp);  
    }


    bool interface = true;

    while(interface){
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
        cout << endl;

        if (input == "1"){
            string choice;
            cout << "rain or temp" << endl;
            cin >> choice;

            cout << "Enter the Full Date (YYYY-MM-DD)" << endl;
            cin >> date;
            cout << "Enter the Specific city" << endl;
            cin >> city;
            string key = date + city;

            if(choice == "rain"){
                string precipitation;
                string windSpeed;
                cout << "Enter precipitation: ";
                cin >> precipitation;
                cout << "Enter wind speed: ";
                cin >> windSpeed;
                mapA.insert(key, precipitation, windSpeed);
            } else if(choice == "temp"){
                string minTemp;
                string maxTemp;
                cout << "Enter minimum temperature: ";
                cin >> minTemp;
                cout << "Enter maximum temperature: ";
                cin >> maxTemp;
                mapB.insert(key, minTemp, maxTemp);

                cout << "Data inserted!" << endl;

            }
            cout << endl;
        }

        if (input == "2") {
            cout << "Enter the Full Date (YYYY-MM-DD)" << endl;
            cin >> date;
            cout << "Enter the Specific city" << endl;
            cin >> city;
            string key = date + city;
            mapA.remove(key);
            mapB.remove(key);
            cout << endl;
            cout << "Data removed successfully." << endl;
            cout << endl;
            cout << endl;
        }

        if (input == "3") {
            cout << "Enter the Full Date (YYYY-MM-DD)" << endl;
            cin >> date;
            cout << "Enter the Specific city" << endl;
            cin >> city;
            string key = date + city;
            pair<string, string> temps = mapB.find(key);
            if (temps.first != "-1" && temps.second != "-1") {
                cout << "Min Temp: " << temps.first << "  ||  " << "Max Temp: " << temps.second << endl;
                cout << endl;
                cout << endl;
            } 
            
            else {
                cout << "No data found." << endl;
                cout << endl;
                cout << endl;
            }
        }

        if (input == "4") {
            cout << "Enter the Full Date (YYYY-MM-DD)" << endl;
            cin >> date;
            cout << "Enter the Specific city" << endl;
            cin >> city;
            string key = date + city;
            pair<string, string> weather = mapA.find(key);
            if (weather.first != "-1" && weather.second != "-1") {
                cout << "Precipitation: " << weather.first << "  ||  " << "Wind Speed: " << weather.second << endl;
                cout << endl;
                cout << endl;
            } 
            
            else {
                cout << "No data found." << endl;
                cout << endl;
                cout << endl;
            }
        }

        if (input == "5"){
            cout << "Goodbye for now!" << endl;
            cout << endl;
            cout << "Terminating Program....." << endl;
            interface = false;
        }
    }

    return 0;
}

