#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdlib>
//#include <ranges>
#include "bozosort.hpp"

struct Student
{
    std::map<std::string, int> m_exams;
    std::string m_name;
    int m_group;
    
    Student(std::string name, int group,
        int math, int phys, int hist, int prog)
    {
        using std::to_string;
        if (group < 1 or group > 9) 
            throw std::invalid_argument("Invalid group. Got " + to_string(group));
        if (math < 0 or math > 9 or phys < 0 or phys > 9 or hist < 0 or hist > 9
            or prog < 0 or prog > 9)
            throw std::invalid_argument("Invalid notes. Got " +
                to_string(math) + ", " + to_string(phys) + ", " + to_string(hist)
                + ", " + to_string(prog));

        m_exams = {{"math", math}, {"phys", phys}, {"hist", hist}, {"prog", prog}};
        m_name = name;
        m_group = group;
    }

    friend
    std::ostream& operator << (std::ostream& out, const Student& student)
    {
        auto name_len = std::max(int(student.m_name.length()), 4);
        auto name_delim = std::string(name_len, '-');
        out << "+-" << name_delim << "-+-------+------+------+------+------+\n"
            << "| Name " << std::string(name_len - 4, ' ') 
            << "| Group | Math | Phys | Hist | Prog |\n"
            << "+-" << name_delim << "-+-------+------+------+------+------+\n"
            << "| " << student.m_name << " | " << student.m_group
            << "     | " << student.m_exams.at("math")
            << "    | "  << student.m_exams.at("phys")
            << "    | "  << student.m_exams.at("hist")
            << "    | "  << student.m_exams.at("prog")
            << "    |\n"
            << "+-" << name_delim << "-+-------+------+------+------+------+\n";
        return out;
    }

    bool operator < (const Student& other) const
    {
        return m_name < other.m_name;
    }
    bool operator > (const Student& other) const
    {
        return m_name > other.m_name;
    }
};

std::ostream& operator << (std::ostream& out, const std::vector<Student>& student_vec)
{
    auto name_len = student_vec.at(0).m_name.length();
    for (auto itr = student_vec.begin() + 1; itr != student_vec.end(); ++itr)
    {
        if (itr->m_name.length() > name_len)
        {
            name_len = itr->m_name.length();
        }
    }
    auto name_delim = std::string(name_len, '-');
    out << "+-" << name_delim << "-+-------+------+------+------+------+\n"
        << "| Name " << std::string(name_len - 4, ' ') 
        << "| Group | Math | Phys | Hist | Prog |\n"
        << "+-" << name_delim << "-+-------+------+------+------+------+\n";

    for (auto& student : student_vec) {
        out << "| " << student.m_name 
            << std::string(name_len - student.m_name.length(), ' ')
            << " | " << student.m_group
            << "     | " << student.m_exams.at("math")
            << "    | "  << student.m_exams.at("phys")
            << "    | "  << student.m_exams.at("hist")
            << "    | "  << student.m_exams.at("prog")
            << "    |\n"
            << "+-" << name_delim << "-+-------+------+------+------+------+\n";
    }
    return out;
};

int main()
{
    std::srand(std::time(0));
    std::vector<Student> students = {
        Student("Misha",        4, 3, 3, 2, 5),
        Student("Alexander",    4, 3, 3, 3, 5),
        Student("Alphred",      4, 3, 5, 2, 5),
        Student("Femenistka",   4, 3, 3, 4, 5),
        Student("Kirkorov",     4, 3, 2, 3, 5),
        Student("Immanuil",     2, 4, 3, 4, 5),
        Student("Pert",         3, 4, 5, 3, 5),
        Student("Artyom",       2, 2, 5, 3, 5),
        Student("Sizigmud",     2, 3, 3, 4, 5),
        Student("Potap",        2, 3, 3, 4, 5),
    };
    //students = BozoSort::BozoSort(students);

    auto has_failed = [](Student& student) -> bool {
        for (auto& pair : student.m_exams)
        {
            if (pair.second == 2)
            {
                return true;
            }
        }
        return false;
    };
    
    // std::cout << students << std::endl;
	
    // c++20
    //std::cout << students | std::views::filter(has_failed) << std::endl;
    std::vector<Student> failed;
    for (auto& student : students)
    {
        if (has_failed(student))
        {
            failed.push_back(student);
        }
    }
    if (failed.size() > 0)
    {
        std::cout << failed << std::endl;

        std::cout << "\nExplusion\n" 
            << failed.at(std::rand() % failed.size()) << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }
}
