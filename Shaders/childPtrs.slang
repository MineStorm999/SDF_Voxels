import common;

struct ChildPtr {
    bool Empty() {
        return value == INVALID;
    }
    uint value;
}