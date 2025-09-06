// UMBC - CMSC 341 - Spring 2025 - Proj0
#include "course.h"
Course::Course(){
    //Default constructor
    m_numSections = 0;
    m_maxNumSections = DEFNUMSECTIONS;
    m_course = new Section*[m_maxNumSections];
    for (int i = 0; i < m_maxNumSections; i++) {
        m_course[i] = nullptr;  // Initialize all section pointers to null to avoid uninitialization errors
    }
}
Course::Course(int maxNumSections){
    //Overloaded constructor
    m_numSections = 0;
    m_maxNumSections = maxNumSections;
    m_course = new Section*[m_maxNumSections];
    for (int i = 0; i < m_maxNumSections; i++) {
        m_course[i] = nullptr;  // Initialize all section pointers to null to avoid uninitialization errors
    }
}
Course::~Course(){
    if (m_course != nullptr) {
        for(int i = 0; i < m_numSections; i++){
            if (m_course[i] != nullptr){
                delete m_course[i];
                m_course[i] = nullptr;
            }
        }
        delete [] m_course;
        m_course = nullptr;
    }
}
bool Course::insertSection(int ID, string instructor, int numItems, int numStudents){  
    if(numStudents < 1 || numItems <1){
        return false;   //Makes sure the section being added has a real number of students and items
    } 
    if(m_maxNumSections == m_numSections){
        return false;   //Checks if the course has enough space for a new section
    }
    if (getSection(ID) != nullptr){
        return false;   //Makes sure this ID doesn't already exist in the course
    }
    //Allocates memory for a new section object and adds it to course
    m_course[m_numSections] = new Section(ID,instructor, numItems, numStudents);
    ++m_numSections;
    return true;
}
bool Course::insertSection(Section * & aSection){
    if(aSection == nullptr){
        return false;   //Checks to see if the pointer points to anything
    }
    if(aSection->m_numStudents < 1 || aSection->m_numGradingItems < 1){
        return false;   //Makes sure the section being added has a real number of students and items
    }
    if(m_maxNumSections == m_numSections){
        return false;   //Checks if the course has enough space for a new section
    }
    if (getSection(aSection->m_sectionID) != nullptr){
        return false;   //Makes sure this ID doesn't already exist in the course
    }

    m_course[m_numSections] = aSection;
    ++m_numSections;
    return true;
}
bool Course::removeSection(int sectionID){
    for (int i = 0; i < m_numSections; i++ ){
        if (m_course[i]->m_sectionID == sectionID){
            // Properly delete the section
            delete m_course[i];
            // Shift remaining sections down
            for (int j = i; j < m_numSections - 1; j++) {
                m_course[j] = m_course[j + 1];
            }
            m_course[m_numSections - 1] = nullptr;
            m_numSections--;
            return true;
        }
    }
    return false;
}
double Course::courseAverage(){
    double average = 0;
    int numOfItems = 0;
    //If there are no sections than the average is 0
    if(m_numSections == 0){
        return average;
    }else{
        for (int i = 0; i< m_numSections; i++ ){
            for (int j = 0; j < m_course[i]->m_numStudents; j++){
                for (int y = 0; y < m_course[i]->m_numGradingItems; y++){
                    average += m_course[i]->m_section[j][y];
                    ++numOfItems;
                }
            } 
        }
        average = average/numOfItems;
        return average;
    }

}
Section * Course::getSection(int sectionID) const{
    //loops through the sections till the specific id is found
    for (int i = 0; i< m_numSections; i++ ){
        if (m_course[i]->m_sectionID == sectionID){
            return m_course[i];
        }
    }
    return nullptr;
}
Section::Section(){
    m_sectionID = 0;
    m_instructor = "none";
    m_numGradingItems = 0;
    m_numStudents = 0;
    m_section = nullptr;
}
Section::Section(int ID, string instructor, int items, int students){
    //If any parameters are invaild than the whole object is set to default values
    if(items < 0 || students < 0){
        m_sectionID = 0;
        m_instructor = "none";
        m_numGradingItems = 0;
        m_numStudents = 0;
        m_section = nullptr; 
    }else{
        m_sectionID = ID;
        m_instructor = instructor;
        m_numGradingItems = items;
        m_numStudents = students; 
        m_section = new double*[m_numStudents];
        //allocates space for each student in the section
        for (int i = 0; i < m_numStudents; i++) {
            m_section[i] = new double[m_numGradingItems];
        }
    }
}
Section::~Section(){
    if (m_section != nullptr) {
        for (int i = 0; i < m_numStudents; i++) {
            if (m_section[i] != nullptr) {
                delete[] m_section[i];
                m_section[i] = nullptr; // Set to nullptr after deletion
            }
        }
        delete[] m_section;
        m_section = nullptr; // Set to nullptr after deletion
    }
}
void Section::clear(){
    if(m_section != nullptr){
        if(m_numStudents > 0){
            for (int i = 0; i < m_numStudents; i++){
                if(m_section[i] != nullptr){
                delete [] m_section[i];
                }
            }
            delete [] m_section;
        }
    }
    //after deleting all the current data it sets everything to default
    m_sectionID = 0;
    m_instructor = "none";
    m_numGradingItems = 0;
    m_numStudents = 0;
    m_section = nullptr;
}
void Section::simulateData(){
    //Generates random numbers from 1-100
    Random seed(0,99);
    seed.setSeed(100);
    for(int i =0; i < m_numStudents; i++){
        for(int j = 0; j < m_numGradingItems; j++)
            m_section[i][j] = (seed.getRandNum() + seed.getRealRandNum());
    }
}

double Section::studentAverage(int student){
    double average = 0;
    //Makes sure the student exists
    if (student >= m_numStudents || student < 0){
        return average;
    }
    //Adds up all the scores for this student
    for(int i = 0; i < m_numGradingItems; i++){
        average += m_section[student][i];
    }
    return average/m_numGradingItems;
}
double Section::testAverage(int test){
    double average = 0;
    //Makes sure this test exists
    if (test >= m_numGradingItems || test < 0){
        return average;
    }
    //Adds up all the scores from each student on this specific test.
    for(int i = 0; i < m_numStudents; i++){
        average += m_section[i][test];
    }
    return average/m_numStudents;
}
double Section::classAverage(){
    double average = 0;
    for(int i = 0; i < m_numStudents; i++){
        for(int j = 0; j < m_numGradingItems; j++){
            average += m_section[i][j];
        }
    }
    return average/(m_numStudents*m_numGradingItems);
}
Section::Section(const Section& rhs){
    // Copy constructor for deep copy
    m_sectionID = rhs.m_sectionID;
    m_instructor = rhs.m_instructor;
    m_numGradingItems = rhs.m_numGradingItems;
    m_numStudents = rhs.m_numStudents;
    if(rhs.m_section == nullptr || rhs.m_numStudents == 0){
        m_section = nullptr;
        return;
    }
    //alocates new memory and copies the data
    m_section = new double*[m_numStudents];
    for(int i = 0; i < m_numStudents; i++){
        m_section[i] = new double[m_numGradingItems];
        for(int j = 0; j < m_numGradingItems; j++){
            m_section[i][j] = rhs.m_section[i][j];
        }
    }

}
const Section& Section::operator=(const Section& rhs){
    //assignment operator
    if(this != &rhs){
        //Deletes all the existing data
        if (m_section != nullptr) {
            for (int i = 0; i < m_numStudents; i++) {
                if (m_section[i] != nullptr) {
                    delete[] m_section[i];
                    m_section[i] = nullptr; // Set to nullptr after deletion
                }
            }
            delete[] m_section;
            m_section = nullptr; // Set to nullptr after deletion
        }

        m_sectionID = rhs.m_sectionID;
        m_instructor = rhs.m_instructor;
        m_numGradingItems = rhs.m_numGradingItems;
        m_numStudents = rhs.m_numStudents;

        if(rhs.m_section == nullptr || rhs.m_numStudents == 0){
            m_section = nullptr;
            return *this;
        }
        m_section = new double*[m_numStudents];
        for(int i = 0; i < m_numStudents; i++){
            m_section[i] = new double[m_numGradingItems];
        for(int j = 0; j < m_numGradingItems; j++){
            m_section[i][j] = rhs.m_section[i][j];
        }
    }
    }
    return *this;
}
void Section::dump(){
    if (m_numGradingItems > 0 && m_numStudents > 0 && m_section != nullptr){
        cout << setw(8) << "        ";
        for (int a=1;a<=m_numGradingItems;a++)
            cout << setw(8) << "Test" << a;
        cout << endl;
        for (int i=1;i <= m_numStudents;i++){
            cout << setw(8) << "Student" << i << " ";
            for (int j=1;j<=m_numGradingItems;j++){
                cout << setw(8) << m_section[i-1][j-1] << " ";
            }
            cout << endl;
        }
    }
}