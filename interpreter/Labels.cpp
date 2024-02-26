#include "Labels.hpp"

// -------------------- LabelName --------------------

LabelName::LabelName(const std::string& label) : label(label) {}

const LabelName LabelName::BEGIN_LABEL = LabelName("begin");

// -------------------- Labels --------------------

Labels::Labels() {}

void Labels::insert(const LabelName& label, size_t val) {
    if (contains(label)) {
        throw LabelRedefenitionException(label.label);
    }
    labels[label.label] = val;
}

size_t Labels::operator[](const LabelName& label) const {
    if (!contains(label)) {
        throw UndefinedLabelException(label.label);
    }
    return labels.at(label.label);
}

bool Labels::contains(const LabelName& label) const {
    return labels.count(label.label);
}
