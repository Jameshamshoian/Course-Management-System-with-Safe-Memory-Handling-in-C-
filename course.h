// UMBC - CMSC 341 - Spring 2025 - Proj0
#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <iomanip>  // required for output formatting such as setw()
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>     //used to get the current time
using namespace std;
class Grader;//this class is for grading purposes, no need to do anything
class Tester;//this is your tester class, you add your test functions in this class
const int DEFNUMSECTIONS = 10; // the default number of sections for a course
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL, SHUFFLE};
class Random {
public:
    Random(){}
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = mt19937(10);// 10 is the fixed seed value
            m_unidist = uniform_int_distribution<>(min,max);
        }
        else if (type == UNIFORMREAL) { //the case of UNIFORMREAL to generate real numbers
            m_generator = mt19937(10);// 10 is the fixed seed value
            m_uniReal = uniform_real_distribution<double>((double)min,(double)max);
        }
        else { //the case of SHUFFLE to generate every number only once
            m_generator = mt19937(m_device());
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = mt19937(seedNum);
    }
    void init(int min, int max){
        m_min = min;
        m_max = max;
        m_type = UNIFORMINT;
        m_generator = mt19937(10);// 10 is the fixed seed value
        m_unidist = uniform_int_distribution<>(min,max);
    }
    void getShuffle(vector<int> & array){
        // the user program creates the vector param and passes here
        // here we populate the vector using m_min and m_max
        for (int i = m_min; i<=m_max; i++){
            array.push_back(i);
        }
        shuffle(array.begin(),array.end(),m_generator);
    }

    void getShuffle(int array[]){
        // the param array must be of the size (m_max-m_min+1)
        // the user program creates the array and pass it here
        vector<int> temp;
        for (int i = m_min; i<=m_max; i++){
            temp.push_back(i);
        }
        shuffle(temp.begin(), temp.end(), m_generator);
        vector<int>::iterator it;
        int i = 0;
        for (it=temp.begin(); it != temp.end(); it++){
            array[i] = *it;
            i++;
        }
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = floor(result*100.0)/100.0;
        return result;
    }

    string getRandString(int size){
        // the parameter size specifies the length of string we ask for
        // to use ASCII char the number range in constructor must be set to 97 - 122
        // and the Random type must be UNIFORMINT (it is default in constructor)
        string output = "";
        for (int i=0;i<size;i++){
            output = output + (char)getRandNum();
        }
        return output;
    }
    
    int getMin(){return m_min;}
    int getMax(){return m_max;}
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    random_device m_device;
    mt19937 m_generator;
    normal_distribution<> m_normdist;//normal distribution
    uniform_int_distribution<> m_unidist;//integer uniform distribution
    uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

class Section{
    public:
    friend class Grader;
    friend class Tester;
    friend class Course;
    Section();
    Section(int ID, string instructor, int items, int students);
    ~Section();
    void clear();
    void simulateData();//inserts random real numbers as grades
    void dump();//for debugging purposes
    double studentAverage(int student);
    double testAverage(int test);
    double classAverage();
    Section(const Section& rhs);
    const Section& operator=(const Section& rhs);
    private:
    int m_numStudents;      // number of rows
    int m_numGradingItems;  // number of columns
    int m_sectionID;        // must be greater than zero
    string m_instructor;
    double ** m_section;    // the 2d structure to store grades

    /******************************************
    * Private function declarations go here! *
    ******************************************/
};

class Course{
    public:
    friend class Grader;
    friend class Tester;
    Course();
    Course(int maxNumSections);
    ~Course();
    bool insertSection(int ID, string instructor, int numItems, int numStudents);
    bool insertSection(Section * & aSection);
    double courseAverage(); // returns the average of all sections
    bool removeSection(int sectionID);
    Section * getSection(int sectionID) const;
    void dump();
    private:
    Section ** m_course;    // stores pointers to sections
    int m_numSections;      // number of current sections
    int m_maxNumSections;   // the array size

    /******************************************
    * Private function declarations go here! *
    ******************************************/
};
#endif