// UMBC - CMSC 341 - Spring 2025 - Proj0
#include "course.h"
class Tester{
    public:
    bool testStudentAveErrorCase();
    bool testConstructorNormalCase();
    bool testConstructorErrorCase();
    bool testCopyConstructorNormalCase();
    bool testCopyConstructorEdgeCase();
    bool testAssignmentOperatorNormalCase();
    bool testAssignmentOperatorEdgeCase();
    bool testStudentAverageNormalCase();
    bool testInsertSectionNormalCase();
    bool testInsertSectionErrorCase();
    bool testRemoveSectionNormalCase();

    /******************************************
    * Test function declarations go here! *
    ******************************************/
};
int main(){
    Tester tester;
    // testing error case for calculation of student average
    cout << "\nTesting studentAverage(...) for an error case:\n\n";
    if (tester.testStudentAveErrorCase() == true)
        cout << "\tError case (student index does not exist) of studentAverage() passed!\n";
    else
        cout << "\tError case (student index does not exist) of studentAverage() failed!\n";
    cout << endl;
    cout << "\nTesting copy constructor normal case: " << (tester.testCopyConstructorNormalCase() ? "Passed" : "Failed") << endl;
    cout << "Testing copy constructor edge case: " << (tester.testCopyConstructorEdgeCase() ? "Passed" : "Failed") << endl;
    cout << "Testing assignment operator normal case: " << (tester.testAssignmentOperatorNormalCase() ? "Passed" : "Failed") << endl;
    cout << "Testing assignment operator edge case: " << (tester.testAssignmentOperatorEdgeCase() ? "Passed" : "Failed") << endl;
    cout << "Testing studentAverage() normal case: " << (tester.testStudentAverageNormalCase() ? "Passed" : "Failed") << endl;
    cout << "Testing insertSection() normal case: " << (tester.testInsertSectionNormalCase() ? "Passed" : "Failed") << endl;
    cout << "Testing insertSection() error case: " << (tester.testInsertSectionErrorCase() ? "Passed" : "Failed") << endl;
    cout << "Testing removeSection() normal case: " << (tester.testRemoveSectionNormalCase() ? "Passed" : "Failed") << endl;

    return 0;
}

bool Tester::testStudentAveErrorCase(){
    bool result = true;
    // create an object with 1 student and 10 grading items
    Section testObject(1000,"John Smith",10,1);
    testObject.simulateData();
    double average = testObject.studentAverage(1);// out of range index
    if (average == 0.0) // expected output
        result = true;
    else
        result = false;
    return result;
}

bool Tester::testConstructorNormalCase() {
    Section test(1000, "John Doe", 5, 10);
    return (test.m_numStudents == 10 && test.m_numGradingItems == 5 && test.m_instructor == "John Doe" && test.m_sectionID == 1000);
}

bool Tester::testConstructorErrorCase(){
    //creates a section with negative students and tests
    Section test(1000, "John Doe", -5, -10);
    return (test.m_numStudents == 0 && test.m_numGradingItems == 0);

}

bool Tester::testCopyConstructorNormalCase(){
    // Create normal object
    Section original(1000, "John Doe", 5, 10);
    original.simulateData();
    original.simulateData();
    
    // Create copy using copy constructor
    Section copy(original);
    
    // Check if m_section points to different memory locations
    bool differentMemory = (original.m_section != copy.m_section);
    
    // Check member variables
    bool membersMatch = (original.m_sectionID == copy.m_sectionID &&
                        original.m_instructor == copy.m_instructor &&
                        original.m_numGradingItems == copy.m_numGradingItems &&
                        original.m_numStudents == copy.m_numStudents);
    
    // Check grades
    bool gradesMatch = true;
    for (int i = 0; i < original.m_numStudents; i++) {
        for (int j = 0; j < original.m_numGradingItems; j++) {
            if (original.m_section[i][j] != copy.m_section[i][j]) {
                gradesMatch = false;
                break;
            }
        }
    }
    
    return differentMemory && membersMatch && gradesMatch;
}

bool Tester::testCopyConstructorEdgeCase(){
    // Create empty object
    Section original(0, "", 0, 0);
    
    // Create copy using copy constructor
    Section copy(original);
    
    // Check if both are empty
    return (copy.m_sectionID == 0 && copy.m_instructor == "" &&
            copy.m_numGradingItems == 0 && copy.m_numStudents == 0 &&
            copy.m_section == nullptr);
}

bool Tester::testAssignmentOperatorNormalCase(){
    Section original(1000, "John Doe", 5, 10);
    original.simulateData();
    Section copy(0, "", 0, 0);
    
    // Use assignment operator
    copy = original;
    
    // Perform same checks as copy constructor
    bool differentMemory = (original.m_section != copy.m_section);
    bool membersMatch = (original.m_sectionID == copy.m_sectionID &&
                        original.m_instructor == copy.m_instructor &&
                        original.m_numGradingItems == copy.m_numGradingItems &&
                        original.m_numStudents == copy.m_numStudents);
    
    bool gradesMatch = true;
    for (int i = 0; i < original.m_numStudents; i++) {
        for (int j = 0; j < original.m_numGradingItems; j++) {
            if (original.m_section[i][j] != copy.m_section[i][j]) {
                gradesMatch = false;
                break;
            }
        }
    }
    
    return differentMemory && membersMatch && gradesMatch;
}

bool Tester::testAssignmentOperatorEdgeCase(){
    Section original(0, "", 0, 0);
    Section copy(1000, "John Doe", 5, 10);
    copy.simulateData();
    
    // Use assignment operator
    copy = original;
    
    return (copy.m_sectionID == 0 && copy.m_instructor == "" &&
            copy.m_numGradingItems == 0 && copy.m_numStudents == 0 &&
            copy.m_section == nullptr);
}

bool Tester::testStudentAverageNormalCase(){
    Section test(1000, "John Doe", 5, 3);
    test.simulateData();
    
    // Calculate expected average
    double expected = 0.0;
    for (int j = 0; j < test.m_numGradingItems; j++) {
        expected += test.m_section[0][j];
    }
    expected /= test.m_numGradingItems;
    
    double actual = test.studentAverage(0);
    
    return abs(expected - actual) == 0;
}

bool Tester::testInsertSectionNormalCase(){
    Course course(3);
    //Makes sure all three insertions happened properly
    bool result1 = course.insertSection(1000, "Prof A", 5, 10);
    bool result2 = course.insertSection(2000, "Prof B", 5, 10);
    bool result3 = course.insertSection(3000, "Prof C", 5, 10);
    
    return result1 && result2 && result3;
}

bool Tester::testInsertSectionErrorCase(){
    Course course(3);
    course.insertSection(1000, "Prof A", 5, 10);
    // Try to insert same section ID again
    bool result = course.insertSection(1000, "Prof B", 5, 10);
    
    return !result; // Should return false for duplicate
}

bool Tester::testRemoveSectionNormalCase(){
    Course course(3);
    course.insertSection(1000, "Prof A", 5, 10);
    bool result = course.removeSection(1000);
    //Checks if the course was removed and the section is now nullptr
    return result && course.getSection(1000) == nullptr;
}