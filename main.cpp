#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    double biology;
    double physics;
    double chemistry;
    double totalMarks;
    double zScoreBiology;
    double zScorePhysics;
    double zScoreChemistry;

    Student(const std::string& n, double bio, double phys, double chem)
        : name(n), biology(bio), physics(phys), chemistry(chem) {
        totalMarks = bio + phys + chem;
        zScoreBiology = 0.0; 
        zScorePhysics = 0.0;  
        zScoreChemistry = 0.0;
    }
};

void calculateRanks(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.totalMarks > b.totalMarks;
    });

    for (size_t i = 0; i < students.size(); ++i) {
        students[i].totalMarks = i + 1;
    }
}

void calculateZScores(std::vector<Student>& students) {
    double meanBiology = 75.0; 
    double stdDevBiology = 5.0;

    double meanPhysics = 80.0; 
    double stdDevPhysics = 6.0;

    double meanChemistry = 85.0;
    double stdDevChemistry = 4.0; 

    for (auto& student : students) {
        student.zScoreBiology = (student.biology - meanBiology) / stdDevBiology;
        student.zScorePhysics = (student.physics - meanPhysics) / stdDevPhysics;
        student.zScoreChemistry = (student.chemistry - meanChemistry) / stdDevChemistry;
    }
}

void printAndWriteRanksAndZScores(const std::vector<Student>& students, const std::string& filename) {
    std::ofstream outputFile(filename);

    std::cout << "Name\t\tTotal Marks\tSchool Rank\tZ-score Biology\tZ-score Physics\tZ-score Chemistry\n";
    outputFile << "Name\t\tTotal Marks\tSchool Rank\tZ-score Biology\tZ-score Physics\tZ-score Chemistry\n";

    for (const auto& student : students) {
        std::cout << student.name << "\t\t" << student.totalMarks << "\t\t" << student.totalMarks
                  << "\t\t" << student.zScoreBiology << "\t\t" << student.zScorePhysics
                  << "\t\t" << student.zScoreChemistry << "\n";
        outputFile << student.name << "\t\t" << student.totalMarks << "\t\t" << student.totalMarks
                   << "\t\t" << student.zScoreBiology << "\t\t" << student.zScorePhysics
                   << "\t\t" << student.zScoreChemistry << "\n";
    }

    outputFile.close();
}

int main() {
    std::vector<Student> bioStudents = {
        {"Student1", 80.5, 75.0, 90.0},
    };

    std::vector<Student> mathStudents = {
        {"Student2", 95.0, 85.5, 78.0},
    };

    calculateRanks(bioStudents);
    calculateRanks(mathStudents);

    std::vector<Student> allStudents;
    allStudents.insert(allStudents.end(), bioStudents.begin(), bioStudents.end());
    allStudents.insert(allStudents.end(), mathStudents.begin(), mathStudents.end());

    calculateZScores(allStudents);

    printAndWriteRanksAndZScores(allStudents, "Output.txt");

    return 0;
}
