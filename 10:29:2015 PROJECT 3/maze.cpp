
//
//  maze.cpp
//
//  Created by 杨博超 on 15/10/27.
//  Copyright © 2015年 杨博超. All rights reserved.
//

#include <iostream>
#include "grid.h"
#include <cassert>
using namespace std;

bool isRouteWellFormed(string route)

// Each iteration of the loop will check one route segment

{
    size_t k = 0;
    while (k != route.size())
    {
        char dir = tolower(route[k]);
        if (dir != 'n' && dir != 'e' && dir != 'w' && dir != 's')  // Route segment must start with a valid direction
        {
            return false;
        }
        k++;
        if (tolower(route[k]) == 'n'  || tolower(route[k]) == 'e' || tolower(route[k]) == 'w' || tolower(route[k]) == 's')
        {
            continue;
        }
        else if (k == route.size())
        {
            return true;
        }
        else if (!isdigit(route[k]))
        {
            return false;
        }
        else if (isdigit(route[k]))
        {
            if (isdigit(route[k+1]))
            {
                k++;
            }
            k++;
        }
    }
    return true;  // If everything is fine
}

int navigateSegment(int r, int c, char dir, int maxSteps)
{
    int nr = getRows();
    int nc = getCols();
    int ns = 0;
    dir = tolower(dir);
    if (r < 1  ||  r > nr  ||  c < 1  ||  c > nc  ||  isWall(r,c))  // Make sure (r,c) is a valid empty grid cell
        return -1;
    
    if (maxSteps < 0)  // Make sure maxSteps is nonnegative
    {
        return -1;
    }
    
    // Calculate the steps taken in different directions, which is ns
    
    if (dir == 'n')
    {
        for (ns = 0; ns < maxSteps; ns++)
        {
            r = r - 1;
            c = c;
            if (r < 1  ||  r > nr  ||  c < 1  ||  c > nc  ||  isWall(r,c))
                break;
        }
    }
    else if(dir == 'e')
    {
        for (ns = 0; ns < maxSteps; ns++)
        {
            r = r;
            c = c + 1;
            if (r < 1  ||  r > nr  ||  c < 1  ||  c > nc  ||  isWall(r,c))
                break;
        }
    }
    else if(dir == 'w')
    {
        for (ns = 0; ns < maxSteps; ns++)
        {
            r = r;
            c = c - 1;
            if (r < 1  ||  r > nr  ||  c < 1  ||  c > nc  ||  isWall(r,c))
                break;
        }
    }
    else if(dir == 's')
    {
        for (ns = 0; ns < maxSteps; ns++)
        {
            r = r + 1;
            c = c;
            if (r < 1  ||  r > nr  ||  c < 1  ||  c > nc  ||  isWall(r,c))
                break;
        }
    }
    else
    {
        return -1;
    }
    
    return ns;  // If everything is fine
}
    

int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)
{
    int nr = getRows();
    int nc = getCols();
    
    // Make sure (sr,sc) and (er,ec) are valid empty grid cells
    
    if (sr < 1 || sr > nr || sc < 1 || sc > nc || isWall(sr,sc))
        return 2;
    if (er < 1 || er > nr || ec < 1 || ec > nc || isWall(er,ec))
        return 2;
    if (!isRouteWellFormed(route))  // Make sure route is syntactically valid
        return 2;
    
    nsteps = 0;
    size_t k = 0;
    
    while (k != route.size())
    {  // Calculate the ShouldBeSteps
        
        int ShouldBeSteps;
        char dir = tolower(route[k]);
        
        if (tolower(route[k+1]) == 'n'  || tolower(route[k+1]) == 'e' || tolower(route[k+1]) == 'w' || tolower(route[k+1]) == 's' || (k+1) == route.size())
        {
            ShouldBeSteps = 1;
        }
        
        else if (isdigit(route[k+1]))
        {
            k++;
            ShouldBeSteps = route[k] - '0';
            
            if (isdigit(route[k+1]))
            {
                k++;
                ShouldBeSteps = 10 * ShouldBeSteps + (route[k] - '0');
            }
        }
        k++;
        
        int TrueSteps = navigateSegment(sr, sc, dir, ShouldBeSteps);  // Calculate the TrueSteps
        nsteps += TrueSteps;
        
        if (TrueSteps < ShouldBeSteps)
        {
            return 3;
        }
        
        if (dir == 'n')  // Calculate (sr, sc)
        {
            sr = sr - TrueSteps;
            sc = sc;
        }
        else if(dir == 'e')
        {
            sr = sr;
            sc = sc + TrueSteps;
        }
        else if(dir == 'w')
        {
            sr = sr;
            sc = sc - TrueSteps;
        }
        else
        {
            sr = sr + TrueSteps;
            sc = sc;
        }
        
    }
    
    // After following all segments, is the robot at the right place?
    if (sr == er && sc == ec)
        return 0;
    else
        return 1;
}

int main()
{
    setSize(3,4);
    setWall(1,4);
    setWall(2,2);
    setWall(3,2);
    draw(3,1, 3,4);
    assert(isRouteWellFormed(""));
    assert(!isRouteWellFormed("1ex"));
    assert(!isRouteWellFormed("1ee"));
    assert(!isRouteWellFormed("ewS1234"));
    assert(isRouteWellFormed("n2e1"));
    assert(isRouteWellFormed("N2eE01n0s2e1"));
    assert(isRouteWellFormed("EE3we"));
    assert(!isRouteWellFormed("3EW"));
    assert(!isRouteWellFormed("e1x"));
    assert(!isRouteWellFormed("a3es"));
    assert(navigateSegment(1, 1, 'a', 1) == -1);
    assert(navigateSegment(2, 4, 'w', 3) == 1);
    assert(navigateSegment(1, 3, 'e', 1) == 0);
    assert(navigateSegment(3, 1, 'N', 2) == 2);
    assert(navigateSegment(1, 3, 's', 2) == 2);
    assert(navigateSegment(2, 2, 'S', 1) == -1);
    assert(navigateSegment(-1, 1, 'N', 2) == -1);
    assert(navigateSegment(3, 1, 'N', -2) == -1);
    assert(navigateSegment(2, 4, 'N', 1) == 0);
    assert(navigateSegment(3, 2, '2', 1) == -1);
    assert(navigateSegment(3, 1, 'x', 1) == -1);
    assert(navigateSegment(3, 1, 'w', -2) == -1);
    assert(navigateSegment(3, 1, 'w', 0) == 0);
    assert(navigateSegment(1, 1, 'e', 2) == 2);
    assert(navigateSegment(3, 1, 'e', 2) == 0);
    assert(navigateSegment(2, 3, 'e', 5) == 1);
    int len;
    len = -999;  // so we can detect whether navigateRoute sets len
    assert(navigateRoute(1,1, 3,4, "e2s2e", len) == 0);  //&&  len == -999);
    len = -999;  // so we can detect whether navigateRoute sets len
    assert(navigateRoute(2,4, 2, 3, "w", len) == 0  &&  len == 1);
    len = -999;  // so we can detect whether navigateRoute sets len
    assert(navigateRoute(3,1, 3,4, "N2eE01n00s2e1", len) == 0  &&  len == 7);
    len = -999;  // so we can detect whether navigateRoute sets len
    assert(navigateRoute(3,1, 3,3, "N2eE01n0s2e1", len) == 1  &&  len == 7);
    len = -999;  // so we can detect whether navigateRoute sets len
    assert(navigateRoute(2,4, 1,1, "w3n1", len) == 3  &&  len == 1);
    len = -999;  // so we can detect whether navigateRoute sets len
    assert(navigateRoute(3,1, 3,4, "e1x", len) == 2  &&  len == -999);
    cout << "All tests succeeded" << endl;
}