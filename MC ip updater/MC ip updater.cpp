#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	system("title IP updatinator by Ori Shamir");
    std::cout << "\n    Finding your Ipv4 address... \n\n";
	system("ipconfig | findstr IPv4 > ipconfigOutput.txt");

	std::ifstream ipconfigOutput("ipconfigOutput.txt");
	std::string tempIpconfigOutput;
	string finalIpOutput = "";
	string onlyIp;
	while (ipconfigOutput >> tempIpconfigOutput) {		
		finalIpOutput += tempIpconfigOutput;		
	}
	ipconfigOutput.close();
	system("del ipconfigOutput.txt");
	// get only the IP.
	onlyIp = finalIpOutput.substr(23, finalIpOutput.size() - 23);

	std::cout << "    Your IP is: " << onlyIp << "\n\n\n    Checking the IP in your \"server.properties\" file...\n\n";

	// check for the ip in server.properties file	
	ifstream serverProperties("server.properties");
	if (!serverProperties) exit(EXIT_FAILURE);
	string tempServerOutput;
	string finalServerOutput = "";
	string onlyServerIp = "";
	while (serverProperties >> tempServerOutput) {
		if (tempServerOutput.substr(0, 9) == "server-ip")
			finalServerOutput = tempServerOutput;		
	}	
	serverProperties.close(); // close the file.

	onlyServerIp = finalServerOutput.substr(10, finalServerOutput.size() - 10); // get only the IP itself.	
	
	cout << "    The IP in your server.properties is: " << onlyServerIp << "\n\n\n";

	if (onlyIp == onlyServerIp) { // if they are the same, nothing is needed to be changed.
		cout << "    Your server.properties and your local IP address are the same. you dont need to do anything. goodbye!\n";
		cout << " Press Any Key To Exit.";
		system("pause >nul");
		exit(EXIT_SUCCESS);
	}

	//if they aint the same...
	cout << "    Whoopsie! your local ip address and your server.properties one are NOT the same.\n";
	cout << "    This could be a problem. Would you like me to fix that for you? (Y/n): ";
	char answer;
	cin >> answer;
	if (answer == 'N' || answer == 'n') {
		cout << "    You can fix it manually then. just open your \"server.properties\" file and change it.\n";
		cout << "Press Any Key To Exit...\n";
		system("pause >nul");
		exit(EXIT_SUCCESS);
	}
	cout << "    Great. I will fix it now.\n";	

	ofstream newServerP("server.properties", ios::app);
	newServerP << "server-ip=" << onlyIp << '\n';	
}