#pragma once

class NonCopyableMoveable {
protected:
    constexpr NonCopyableMoveable() = default;

    virtual ~NonCopyableMoveable() = default;

    // Delete the copy and copy assignment constructor
    NonCopyableMoveable(const NonCopyableMoveable &) = delete;

    NonCopyableMoveable &operator=(const NonCopyableMoveable &) = delete;

    // Delete the move and move assignment constructor
    NonCopyableMoveable(NonCopyableMoveable &&other) = delete;

    NonCopyableMoveable &operator=(NonCopyableMoveable &&other) = delete;
};