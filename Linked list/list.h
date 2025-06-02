#pragma once

struct list_elem
{
    long long value;  // Changed from double to long long
    list_elem* next = nullptr;
    list_elem* prev = nullptr;
};

struct list
{
    list_elem* border = nullptr;
};

void add(list& lst, long long value);
void clear(list& lst);  // Added for memory cleanup