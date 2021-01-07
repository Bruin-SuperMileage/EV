### Documentation for string parsing.
main.ino currently prints all received data values in a single string, with each datum spanning 6 contiguous characters (4 for the label and 2 for the value). This allows [main.py](https://github.com/Bruin-SuperMileage/EV/blob/master/daq/panda/main.py) to read the string in 6 character increments, thereby restoring the original data.

##### Areas for improvement
- There is no guarantee that the received data values will span only 2 characters. Provisions must be made so that all data values are measured to the same number of digits without any losses in precision
