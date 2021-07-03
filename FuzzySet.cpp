/*
 * Robotic Research Group (RRG)
 * State University of Piauí (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzySet.cpp
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Dr. Ricardo Lira <ricardor_usp@yahoo.com.br>
 *                      Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzySet.h"
#include "math.h"

// CONTRUCTORS
FuzzySet::FuzzySet()
{
}

/*
FuzzySet::FuzzySet(float a, float b, float c, float d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->pertinence = 0.0;
}*/

FuzzySet::FuzzySet(float a, float b, float c, float d, float nT, float n1, float n2)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->nT = nT;
    this->n1 = n1;
    this->n2 = n2;
    this->pertinence = 0.0;
}

// PUBLIC METHODS

// Method to get the value of point A
float FuzzySet::getPointA()
{
    return this->a;
}

// Method to get the value of point B
float FuzzySet::getPointB()
{
    return this->b;
}

// Method to get the value of point C
float FuzzySet::getPointC()
{
    return this->c;
}

// Method to get the value of point D
float FuzzySet::getPointD()
{
    return this->d;
}

float FuzzySet::getNT()
{
    return this->nT;
}

float FuzzySet::getN1()
{
    return this->n1;
}

float FuzzySet::getN2()
{
    return this->n2;
}

/*
// Method to calculate the pertinence of the FuzzySet, according with the crispValue
bool FuzzySet::calculatePertinence(float crispValue)
{
    // check the crispValue is small then A
    if (crispValue < this->a)
    {
        // check if this FuzzySet represents "everithing small is true"
        if (this->a == this->b && this->b != this->c && this->c != this->d)
        {
            // if so, the pertinence is 1
            this->pertinence = 1.0;
        }
        else
        {
            // else, pertinence is 0
            this->pertinence = 0.0;
        }
    }
    // check if the crispValue is between A and B
    else if (crispValue >= this->a && crispValue < this->b)
    {
        // calculate a slope
        float slope = 1.0 / (this->b - this->a);
        // calculate the value of pertinence
        this->pertinence = slope * (crispValue - this->b) + 1.0;
    }
    // check if the pertinence is between B and C
    else if (crispValue >= this->b && crispValue <= this->c)
    {
        this->pertinence = 1.0;
    }
    // check if the pertinence is between C and D
    else if (crispValue > this->c && crispValue <= this->d)
    {
        // calculate a slope
        float slope = 1.0 / (this->c - this->d);
        // calculate the value of pertinence
        this->pertinence = slope * (crispValue - this->c) + 1.0;
    }
    // check the crispValue is bigger then D
    else if (crispValue > this->d)
    {
        // check if this FuzzySet represents "everithing bigger is true"
        if (this->c == this->d && this->c != this->b && this->b != this->a)
        {
            // if so, the pertinence is 1
            this->pertinence = 1.0;
        }
        else
        {
            // else, pertinence is 0
            this->pertinence = 0.0;
        }
    }
    return true;
}*/

// Method to calculate the pertinence of the FuzzySet, according with the crispValue
bool FuzzySet::calculatePertinence(float crispValue)
{
    // check the crispValue is small then A
    if (crispValue < this->a)
    {
        // check if this FuzzySet represents "everithing small is true"
        if (this->a == this->b && this->b != this->c && this->c != this->d)
        {
            // if so, the pertinence is 1
            this->pertinence = 1.0;
        }
        else
        {
            // else, pertinence is 0
            this->pertinence = 0.0;
        }
        return true;
    }


    //check (b-(b-a)/n1) <= x & x <= (b-nT*(b-a))
    else if ((this->b - ((this->b - this->a)/this->n1)) <= crispValue  && crispValue < (this->b - (this->nT * (this->b - this->a) )) )
    {
        // calculate a slope
        float slope = this->b - this->nT * (this->b - this->a);
        slope = this->n1 * (crispValue - slope);
        slope = slope/(this->b - this->a - (this->nT * (this->b - this->a)));
        slope = 1 + slope;
        this->pertinence = pow(slope, this->n2);
        return true;
    }
    // check (b-nT*(b-a)) <= x & x < (c+nT*(d-c))
    else if ((this->b - (this->nT * (this->b - this->a))) <= crispValue  && crispValue < (this->c + (this->nT * (this->d - this->c))))
    {
        this->pertinence = 1.0;
        return true;
    }
    // check (c+nT*(d-c)) <= x & x <= (c+(d-c)/n1)
    else if ((this->c + (this->nT * (this->d - this->c))) <= crispValue && crispValue < (this->c + ((this->d - this->c) / this->n1)) )
    {
        // calculate a slope
        float slope = this->c + this->nT*(this->d - this->c);
        slope = this->n1 * (slope - crispValue);
        slope = slope / (this->d - this->c + (this->nT * (this->d - this->c)));
        slope = 1 + slope;
        // calculate the value of pertinence
        this->pertinence = pow(slope,this->n2);
        return true;
    }
    // check the crispValue is bigger then D
    else if (crispValue > this->d)
    {
        // check if this FuzzySet represents "everithing bigger is true"
        if (this->c == this->d && this->c != this->b && this->b != this->a)
        {
            // if so, the pertinence is 1
            this->pertinence = 1.0;
        }
        else
        {
            // else, pertinence is 0
            this->pertinence = 0.0;
        }

        return true;
    }
    return true;
}

// Method to set the value of pertinence
void FuzzySet::setPertinence(float pertinence)
{
    // check if the new pertinence is bigger then the current value because it can be called more then once by different FuzzyRuleConsequent
    if (this->pertinence < pertinence)
    {
        this->pertinence = pertinence;
    }
}

// Method to get the value of pertinence
float FuzzySet::getPertinence()
{
    return this->pertinence;
}

// Method to reset the value of pertinence
void FuzzySet::reset()
{
    this->pertinence = 0.0;
}