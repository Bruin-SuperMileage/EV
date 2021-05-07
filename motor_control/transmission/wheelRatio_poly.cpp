//
//  wheelRatio_poly.cpp
//  
//
//  Created by Isha G on 4/29/21.
//

double getRatio (double sensorVal)
{
    return 275.4804*pow(sensorVal,3) - 0.8808*pow(sensorVal,2) + 4.3508*sensorVal + 0.9996;
}


