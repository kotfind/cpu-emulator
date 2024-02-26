#pragma once

#include <exception>
#include <string>
#include <unordered_map>

class UndefinedLabelException : public std::exception {
    public:
        UndefinedLabelException(const std::string& label);

        const char* what() const noexcept override;

    private:
        std::string error_msg;
};

class LabelRedefenitionException : public std::exception {
    public:
        LabelRedefenitionException(const std::string& label);

        const char* what() const noexcept override;

    private:
        std::string error_msg;
};

class Labels;

class LabelName {
    public:
        LabelName(const std::string& label);

        static const LabelName BEGIN_LABEL;

    private:
        std::string label;

    friend Labels;
};

class Labels {
    public:
        Labels();

        void insert(const LabelName& label, size_t val);

        size_t operator[](const LabelName& label) const;

        bool contains(const LabelName& label) const;

        std::unordered_map<std::string, size_t> labels;
};
