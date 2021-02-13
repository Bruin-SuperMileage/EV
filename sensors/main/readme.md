### Documentation for string parsing.
main.ino currently prints all received data values in a single string, with each datum spanning a varying number of characters separated by semicolons. This allows [main.py](https://github.com/Bruin-SuperMileage/EV/blob/master/daq/panda/main.py) to parse the string between semicolons, thereby restoring the original data.

##### Data Formatting
Each datum is comprised of a label, a colon, and the data value.
Ex: Lat:19.4;Lon:92.4;
