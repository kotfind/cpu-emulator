#include "Labels.hpp"

// -------------------- UndefinedLabelException --------------------

UndefinedLabelException::UndefinedLabelException(const std::string& label) {
    error_msg = "undefined label: ";
    error_msg += label;
}

const char* UndefinedLabelException::what() const noexcept {
    return error_msg.c_str();
}

// -------------------- LabelRedefenitionException --------------------

LabelRedefenitionException::LabelRedefenitionException(const std::string& label) {
    error_msg = "label redefenition: ";
    error_msg += label;
}

const char* LabelRedefenitionException::what() const noexcept {
    return error_msg.c_str();
}

// -------------------- LabelName --------------------

LabelName::LabelName(const std::string& label) : label(label) {}

const LabelName LabelName::BEGIN_LABEL = LabelName("begin");

// -------------------- Labels --------------------

Labels::Labels() {}

void Labels::insert(const LabelName& label, size_t val) {
    if (labels.count(label.label)) {
        throw LabelRedefenitionException(label.label);
    }
    labels[label.label] = val;
}

size_t Labels::operator[](const LabelName& label) const {
    if (!labels.count(label.label)) {
        throw UndefinedLabelException(label.label);
    }
    return labels.at(label.label);
}
