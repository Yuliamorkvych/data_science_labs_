#include "KeyProcessor.hpp"
KeyProcessor::KeyProcessor() : currentMode(Mode::NORMAL) {}
void KeyProcessor::processKey(int key) {
    if (key <= 0) return;
    char c = static_cast<char>(key & 0xFF);
    switch (c) {
        case '0': currentMode = Mode::NORMAL; break;
        case '1': currentMode = Mode::INVERT; break;
        case '2': currentMode = Mode::CANNY; break;
        case '3': currentMode = Mode::BLUR; break;
    }
}
KeyProcessor::Mode KeyProcessor::getMode() const { return currentMode; }
