#pragma once
class KeyProcessor {
public:
    enum class Mode { NORMAL, INVERT, CANNY, BLUR };
private:
    Mode currentMode;
public:
    KeyProcessor();
    void processKey(int key);
    Mode getMode() const;
};
