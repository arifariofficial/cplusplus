/*
Develop the xmltemperature_pohja.cpp program further so that it finds and extracts specified items from the xml-string using start
and end tags. Now we find and extract and display first the location information and then the temperature
information. Location can be found between the tags <location> and </location>. The temperature is between
the tags <temp_c> and </temp_c>.

To make it easy to find whatever information from the xml-string write a function that takes the xml-string
and the "inner" text (same for start tag and end tag) of the tags as parameters and returns the text from
between the start tag and end tags. If either start or end tag is not found the function must return "not found".
Note that when you search for the tag you must search for the whole tag (including angle brackets) not just the
tag name that was given as parameter.

For example, if you wanted to find the location information you could call it as follows:
    location = find_field(page, "location");

and to get the temperature you could call it as follows:
    temperature = find_field(page, "temp_c");
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string find_field(const string &xml, const string &tag_name);

int main() {
    string page, line, location, temperature;

    // Open xml file and read its contents into a string
    ifstream inputFile("/Users/ari/Desktop/cplusplus/metropolia/weather.xml");

    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file 'weather.xml'." << endl;
        return 1; // Exit the program with an error code
    }

    // Read the file line by line and append to 'page'
    while (getline(inputFile, line)) {
        page.append(line);
        line.erase();
    }

    // Now page is a string that contains the whole xml page

    // Here you need to write something that finds and
    // extracts location and temperature from the XML
    // data in the string page and stores them in
    // the strings location and temperature respectively

    // Extract location and temperature information
    location = find_field(page, "location");
    temperature = find_field(page, "temp_c");

    // Close the file
    inputFile.close();

    cout << "Location: " << location << endl;
    cout << "Temperature: " << temperature << endl;
}

string find_field(const string &xml, const string &tag_name) {
    // construct start and end tags from the tag name
    // add angle brackets to both tags and also slash to end tag
    // then search for tags
    // if both are found then return the substring between the tags
    const string start_tag = "<" + tag_name + ">";
    const string end_tag = "</" + tag_name + ">";

    size_t pos1 = xml.find(start_tag); // looks for start_tag if not found returns string::npos
    if (size_t pos2 = xml.find(end_tag); pos1 != string::npos && pos2 != string::npos) {
        string inner;
        pos1 += start_tag.size(); // position after start_tag
        pos2 -= pos1; // length of the string between tags
        return inner = xml.substr(pos1, pos2); // string between tags, substr(start, length)
    }

    return "not found"; // return this if tag is not found
}