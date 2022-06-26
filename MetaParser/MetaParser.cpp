#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <iostream>

inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}

struct Animation
{
    std::string Name_;
};

int main() 
{
    std::filesystem::directory_iterator DirIter(std::filesystem::current_path() / "Input");

    while (DirIter != std::filesystem::end(DirIter))
    {
        const std::filesystem::directory_entry& Entry = *DirIter;
        
        std::filesystem::path Path_ = Entry.path();

        std::string Result;

        for (size_t i = 1; i < Path_.string().length(); i++)
        {
            size_t Pos = Path_.string().length() - i;
            std::string NameTemp = Path_.string().substr(Pos, 1);

            const char* Char = "\\";

            if (Char == NameTemp)
            {
                break;
            }

            else
            {
                Result += NameTemp;
            }
        }

        std::string ChangeStr;

        for (size_t i = 0; i < Result.length() + 1; i++)
        {
            ChangeStr += Result.substr(Result.length() - i, 1);
        }

        std::string FileName_ = ChangeStr;

        std::vector<Animation> Animations_;
        std::vector<std::string> VectorName_;
        std::vector<std::string> VectorX_;
        std::vector<std::string> VectorY_;
        std::vector<std::string> VecHeight_;
        std::vector<std::string> VecWidth_;
        std::vector<std::string> VecPivot_;

        std::ifstream InputFile_("Input\\" + FileName_);
        std::string Input_;

        std::string Str_;

        if (false == InputFile_.is_open())
        {
            std::cout << "입력 파일을 찾을 수 없습니다." << std::endl;
            break;
        }

        InputFile_.seekg(0, std::ios::end);
        size_t size = InputFile_.tellg();
        Str_.resize(size);
        InputFile_.seekg(0, std::ios::beg);
        InputFile_.read(&Str_[0], size);

        std::stringstream RealStr_{ Str_ };
        std::string Token_;

        const char* Second = "second:";
        const char* Name = "name:";
        const char* X = "x:";
        const char* Y = "y:";
        const char* Width = "width:";
        const char* Height = "height:";
        const char* Pivot = "pivot:";

        while (std::getline(RealStr_, Token_, '\n'))
        {
            InputFile_ >> Token_;
            std::cout << Token_ << std::endl;

            std::string Temp = ltrim(Token_);

            if (true == Temp.starts_with(Second))
            {
                Animation NewAnimation;
                NewAnimation.Name_ = Token_;
                Animations_.push_back(NewAnimation);
            }

            else if (true == Temp.starts_with(Name))
            {
                VectorName_.push_back(Temp);
            }

            else if (true == Temp.starts_with(X))
            {
                VectorX_.push_back(Temp);
            }

            else if (true == Temp.starts_with(Y))
            {
                VectorY_.push_back(Temp);
            }

            else if (true == Temp.starts_with(Height))
            {
                VecHeight_.push_back(Temp);
            }

            else if (true == Temp.starts_with(Width))
            {
                VecWidth_.push_back(Temp);
            }

            else if (true == Temp.starts_with(Pivot))
            {
                VecPivot_.push_back(Temp);
            }
        }

        std::ofstream OutFile_("Output\\" + FileName_);

        if (false == OutFile_.is_open())
        {
            std::cout << "출력 파일을 찾을 수 없습니다." << std::endl;
            break;
        }

        for (size_t i = 0; i < VectorName_.size(); i++)
        {
            OutFile_ << VectorName_[i] << std::endl;
            OutFile_ << VectorX_[i] << std::endl;
            OutFile_ << VectorY_[i] << std::endl;
            OutFile_ << VecHeight_[i] << std::endl;
            OutFile_ << VecWidth_[i] << std::endl;
            OutFile_ << VecPivot_[i] << std::endl;
        }

        OutFile_ << std::endl;

        for (size_t i = 0; i < Animations_.size(); i++)
        {
            OutFile_ << Animations_[i].Name_ << std::endl;
        }

        ++DirIter;
    }

    return 0;
}

