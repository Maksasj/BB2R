#ifndef KEYEXIST_F
#define KEYEXIST_F

template <typename T, typename Key>
bool key_exists(const T& container, const Key& key)
{
    return (container.find(key) != std::end(container));
}

#endif