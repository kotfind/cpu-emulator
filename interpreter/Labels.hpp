#pragma once

#include "Exception.hpp"

#include <string>
#include <unordered_map>

class UndefinedLabelException : public Exception {
    public:
        UndefinedLabelException(const std::string& label)
          : Exception("undefined label: " + label)
        {}
};

class LabelRedefenitionException : public Exception {
    public:
        LabelRedefenitionException(const std::string& label)
          : Exception("label redefenition: " + label)
        {}
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
