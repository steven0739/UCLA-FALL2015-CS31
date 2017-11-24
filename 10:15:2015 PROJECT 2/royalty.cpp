//
//  main.cpp
//
//  Created by 杨博超 on 15/10/8.
//  Copyright © 2015年 杨博超. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "Units sent: ";  //Get and validate units sent
    int unitsSent;
    cin >> unitsSent;
    cin.ignore(10000, '\n');
    if (unitsSent < 0)
    {
        cout << "---" << "The number of units sent must be nonnegative." << endl;
    }
    
    cout << "Title: ";  //Get and validate title
    string title;
    getline(cin, title);
    if (title == "")
    {
        cout << "---" << "You must enter a title." << endl;
    }
    
    cout << "Base price: ";  //Get and validate base price
    double basePrice;
    cin >> basePrice;
    cin.ignore(10000, '\n');
    if (basePrice < 0)
    {
        cout << "---" << "The base price must be nonnegative." << endl;
    }
    
    cout << "Premium item? (y/n): ";  //Get and validate premium status
    string premium;
    getline(cin, premium);
    if (premium != "y" && premium != "n")
    {
        cout << "---" << "You must enter y or n." << endl;
    }
    
    const double lowVolume = 400;  //Clarify boundaries
    const double highVolume = 1200;
    
    const double lowRate = 0.09;  //Clarify rates
    const double nonpremiumMediumRate = 0.13;
    const double premiumMediumRate = 0.16;
    const double highRate = 0.14;
    
    double royalties;
    cout.setf(ios::fixed);
    cout.precision(2);
    
    if (unitsSent <= lowVolume)
    {
        royalties = lowRate * basePrice * unitsSent;  //Express royalties in terms of rates, base price and units sent.
        cout << "---" << "\n" << title << " earned $" << royalties << " in royalties." << endl;
    }
    
    if ((unitsSent > lowVolume) && (unitsSent <= highVolume) && (premium == "n"))
    {
        royalties = nonpremiumMediumRate * basePrice * (unitsSent - lowVolume) + lowRate * lowVolume * basePrice;
        cout << "---" << "\n" << title << " earned $" << royalties << " in royalties." << endl;
    }
    
    if ((unitsSent > lowVolume) && (unitsSent <= highVolume) && (premium == "y"))
    {
        royalties = premiumMediumRate * basePrice * (unitsSent - lowVolume) + lowRate * lowVolume * basePrice;
        cout << "---" << "\n" << title << " earned $" << royalties << " in royalties." << endl;
    }
    
    if ((unitsSent > highVolume) && (premium == "n"))
    {
        royalties = highRate * (unitsSent - highVolume) * basePrice + nonpremiumMediumRate * basePrice * (highVolume - lowVolume) + lowRate * lowVolume * basePrice;
        cout << "---" << "\n" << title << " earned $" << royalties << " in royalties." << endl;
    }
    
    if ((unitsSent > highVolume) && (premium == "y"))
    {
        royalties = highRate * (unitsSent - highVolume) * basePrice + premiumMediumRate * basePrice * (highVolume - lowVolume) + lowRate * lowVolume * basePrice;
        cout << "---" << "\n" << title << " earned $" << royalties << " in royalties." << endl;
    }
}
