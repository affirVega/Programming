#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

struct Coin {
    uint count;
};

struct Rune {
    enum class Element { FIRE, WATER, EARTH, AIR } element;
    uint level;
};

std::string to_string(Rune& rune) {
    std::string result;

    switch (rune.element) {
        case Rune::Element::FIRE:
            result = "fire";
            break;
        case Rune::Element::WATER:
            result = "water";
            break;
        case Rune::Element::EARTH:
            result = "earth";
            break;
        case Rune::Element::AIR:
            result = "air";
            break;
    }

    return result;
}

struct Weapon {
    uint damage;
    uint critical;
    uint durability;
};

struct Armor {
    uint guard;
    uint durability;
};

struct Item
{
    enum class ItemType { COIN, RUNE, WEAPON, ARMOR } type;
    union Value {
        Coin coin;
        Rune rune;
        Weapon weapon;
        Armor armor;
    } value;

    static Item GetCoin(uint count) {
        return {Item{Item::ItemType::COIN,
            Item::Value{.coin = Coin{count}}}};
    }
    static Item GetRune(Rune::Element element, uint8_t level) {
        return {Item{Item::ItemType::RUNE,
            Item::Value{.rune = Rune{element, level}}}};
    }
    static Item GetWeapon(uint damage, uint8_t critical, uint8_t durability) {
        return {Item{Item::ItemType::WEAPON,
            Item::Value{.weapon = Weapon{damage, critical, durability}}}};
    }
    static Item GetArmor(uint guard, uint8_t durability) {
        return {Item{Item::ItemType::ARMOR,
            Item::Value{.armor = Armor{guard, durability}}}};
    }

    Item& operator++()
    {
        return *this;
    }
};

template<class T, class S>
struct Pair
{
    T first;
    S second;
};

std::vector<Pair<Item, double>> chances {
    {Item::GetCoin(1000), 50.0},
    {Item::GetRune(Rune::Element::FIRE,  1), 6.0},
    {Item::GetRune(Rune::Element::WATER, 1), 13.0},
    {Item::GetRune(Rune::Element::EARTH, 1), 7.0},
    {Item::GetRune(Rune::Element::AIR,   1), 14.0},
    {Item::GetRune(Rune::Element::FIRE,  5), 0.6},
    {Item::GetRune(Rune::Element::WATER, 5), 1.3},
    {Item::GetRune(Rune::Element::EARTH, 5), 0.7},
    {Item::GetRune(Rune::Element::AIR,   5), 1.4},
    {Item::GetRune(Rune::Element::FIRE,  5), 0.06},
    {Item::GetRune(Rune::Element::WATER, 5), 0.13},
    {Item::GetRune(Rune::Element::EARTH, 5), 0.07},
    {Item::GetRune(Rune::Element::AIR,   5), 0.14},
    {Item::GetWeapon(100, 0, 100), 1.4},
    {Item::GetWeapon(75, 50, 100), 1.4},
    {Item::GetArmor(50, 100), 2.8},
};

const double total_chance = 10000;

using LootBox = std::vector<Item>;

LootBox generateLootBox() {
    LootBox box;
    std::srand(std::time(0));

    for (int i = 0; i < 3; ++i) {
        double r = double(rand() % 10000) / 100; // [0.00; 100.00)
        double current_sum = 0;

        for (auto elem : chances) {
            if (current_sum <= r and r < current_sum + elem.second) {
                box.push_back(elem.first);
                break;  // from foreach loop
            }
            current_sum += elem.second;
        }
    }
    return box;
}

std::ostream& operator<<(std::ostream& out, LootBox& lootbox) {
    for (auto elem : lootbox) {
        Item::ItemType& type = elem.type;
        if (type == Item::ItemType::COIN) {
            out << elem.value.coin.count << " gold\n";
        }
        else if (type == Item::ItemType::RUNE) {
            Rune& rune = elem.value.rune;
            out << "Rune of " << to_string(rune) 
                << " level " << rune.level << "\n";
        }
        else if (type == Item::ItemType::WEAPON) {
            Weapon& weapon = elem.value.weapon;
            out << "Weapon {damage: " << elem.value.weapon.damage
                << ", critical: " << elem.value.weapon.critical
                << ", durability: " << elem.value.weapon.durability << "}\n";
        }
        else if (type == Item::ItemType::ARMOR) {
            Armor& armor = elem.value.armor;
            out << "Armor {guard: " << armor.guard
                << ", durability: " << armor.durability << "}\n";
        }
    }
    out << std::flush;
    return out;
}

LootBox& operator<<(LootBox& lootbox, Item& item) {
    lootbox.push_back(item);
    return lootbox;
}


int main() {
    //asdf
    auto box = generateLootBox();
    std::cout << box << std::endl;
};
