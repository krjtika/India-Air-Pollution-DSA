#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

struct City {
	string name;
	int aqi;
	int traffic;
	int industry;
	int cropBurning;
	int construction;
};

string getAQICategory(int aqi) {
	if (aqi <= 50) return "Good";
	else if (aqi <= 100) return "Satisfactory";
	else if (aqi <= 200) return "Moderate";
	else if (aqi <= 300) return "Poor";
	else if (aqi <= 400) return "Very Poor";
	else return "Severe";
}

void displayAllCities(const vector<City>& cities) {
	cout << "\nCity-wise AQI Data\n";
	for (int i = 0; i < cities.size(); i++) {
		cout << cities[i].name << " | AQI: " << cities[i].aqi
			 << " | " << getAQICategory(cities[i].aqi) << endl;
	}
}

bool compareAQI(City a, City b) {
	return a.aqi > b.aqi;
}

void showMostPollutedCities(vector<City> cities) {
	sort(cities.begin(), cities.end(), compareAQI);

	cout << "\nMost Polluted Cities (High to Low AQI)\n";
	for (int i = 0; i < cities.size(); i++) {
		cout << i + 1 << ". " << cities[i].name
			 << " (AQI: " << cities[i].aqi << ")\n";
	}
}

void showPollutionPriority(const City& c) {
	priority_queue<pair<int, string>> pq;

	pq.push({c.traffic, "Traffic"});
	pq.push({c.industry, "Industry"});
	pq.push({c.cropBurning, "Crop Burning"});
	pq.push({c.construction, "Construction"});

	cout << "\nPollution Priority for " << c.name << endl;
	while (!pq.empty()) {
		cout << pq.top().second << " -> Impact: "
			 << pq.top().first << endl;
		pq.pop();
	}
}

void suggestSolutions(const City& c) {
	cout << "\nCity: " << c.name << endl;
	cout << "AQI: " << c.aqi << " (" << getAQICategory(c.aqi) << ")\n";

	cout << "\nSuggested Solutions:\n";

	if (c.aqi > 400)
		cout << "- Health Emergency | Work From Home\n";

	if (c.traffic > 70)
		cout << "- Apply Odd-Even Traffic Rule\n";

	if (c.industry > 70)
		cout << "- Reduce Industrial Emissions\n";

	if (c.cropBurning > 70)
		cout << "- Stop Crop Burning, Give Farmer Support\n";

	if (c.construction > 70)
		cout << "- Stop Construction & Control Dust\n";
}

int main() {
	vector<City> cities = {
		{"Delhi", 410, 85, 80, 40, 75},
		{"Mumbai", 160, 70, 60, 20, 65},
		{"Kanpur", 390, 80, 75, 60, 70},
		{"Lucknow", 310, 75, 65, 55, 60},
		{"Bengaluru", 140, 65, 50, 15, 55}
	};

	int choice;
	do {
		cout << "\n===== INDIA AIR POLLUTION DSA SYSTEM =====\n";
		cout << "1. Display AQI Data\n";
		cout << "2. Most Polluted Cities\n";
		cout << "3. Pollution Source Priority\n";
		cout << "4. AQI Based Solutions\n";
		cout << "5. Exit\n";
		cout << "Enter choice: ";
		cin >> choice;

		if (choice == 1)
			displayAllCities(cities);

		else if (choice == 2)
			showMostPollutedCities(cities);

		else if (choice == 3 || choice == 4) {
			string cname;
			cout << "Enter city name (Delhi/Mumbai/etc): ";
			cin >> cname;

			bool found = false;
			for (int i = 0; i < cities.size(); i++) {
				if (cities[i].name == cname) {
					found = true;
					if (choice == 3)
						showPollutionPriority(cities[i]);
					else
						suggestSolutions(cities[i]);
				}
			}
			if (!found)
				cout << "City not found\n";
		}

	} while (choice != 5);

	return 0;
}
