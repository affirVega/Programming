// main.h

# include <iostream>
# include <vector>
# include <cstdlib>
# include <ctime>
# include <algorithm>
# include <string>

struct Coin {
    uint count;
};

struct Rune {
    enum class Element { FIRE, WATER, EARTH, AIR } element;
    uint level;
};

std::string to_string(Rune::Element& element);

struct Weapon {
    uint damage;
    uint critical;
    uint durability;
};

struct Armor {
    uint guard;
    uint durability;
};

struct Item;
Item generateItem();

struct Item
{
    enum class ItemType { COIN, RUNE, WEAPON, ARMOR } type;
    union Value { Coin coin; Rune rune; Weapon weapon; Armor armor; } value;

    Item& operator++()
    {
        *this = generateItem();
        return *this;
    }
};

Item GetCoin(uint count);

Item GetRune(Rune::Element element, uint level);
Item GetFireRune(uint level);
Item GetWaterRune(uint level);
Item GetEarthRune(uint level);
Item GetAirRune(uint level);

Item GetWeapon(uint damage, uint critical, uint durability);
Item GetArmor(uint guard, uint durability);

template<class T, class S>
struct Pair
{
    T first;
    S second;
};

std::vector<Pair<Item, double>> chances {
    {GetCoin(1000), 50.0},
    {GetFireRune(1), 6.0},
    {GetWaterRune(1), 13.0},
    {GetEarthRune(1), 7.0},
    {GetAirRune(1), 14.0},
    {GetFireRune(5), 0.6},
    {GetWaterRune(5), 1.3},
    {GetEarthRune(5), 0.7},
    {GetAirRune(5), 1.4},
    {GetFireRune(5), 0.06},
    {GetWaterRune(5), 0.13},
    {GetEarthRune(5), 0.07},
    {GetAirRune(5), 0.14},
    {GetWeapon(100, 0, 100), 1.4},
    {GetWeapon(75, 50, 100), 1.4},
    {GetArmor(50, 100), 2.8},
};

const int precision = 100;  // Точность до сотых в шансах
double count_total_chance() {
    double sum = 0;
    for (auto& pair : chances) {
        sum += pair.second;
    }
    return sum * precision;
}

const double total_chance = count_total_chance();  // сумма всех шансов

using LootBox = std::vector<Item>;

LootBox generateLootBox();

LootBox& operator<<(LootBox& lootbox, Item& item);

std::ostream& operator<<(std::ostream& out, Item& item);

std::ostream& operator<<(std::ostream& out, LootBox& lootbox);

// std::string toLowerCase(std::string str);

// std::string toLowerCase(std::string data) {
//     return std::transform(data.begin(), data.end(), data.begin(),
//     [](unsigned char c){ return std::tolower(c); });
// }

LootBox& operator<<(LootBox& lootbox, Item item) {
    lootbox.push_back(item);
    return lootbox;
}

Item generateItem() {
    double r = double(rand() % int(total_chance)) / 100; // [0.00; 100.00)
    double current_sum = 0;

    for (auto& elem : chances) {
        if (current_sum <= r and r < current_sum + elem.second) {
            return elem.first;
        }
        current_sum += elem.second;
    }
    return chances[0].first;
}

LootBox generateLootBox() {
    LootBox box;
    std::srand(std::time(0));

    for (int i = 0; i < 3; ++i) {
        box << generateItem();
    }
    return box;
}

std::ostream& operator<<(std::ostream& out, Item& item) {
    Item::ItemType& type = item.type;

    if (type == Item::ItemType::COIN) {
        out << item.value.coin.count << " gold";
    }
    else if (type == Item::ItemType::RUNE) {
        Rune& rune = item.value.rune;
        out << "Rune of " << to_string(rune.element) 
            << " level " << rune.level;
    }
    else if (type == Item::ItemType::WEAPON) {
        Weapon& weapon = item.value.weapon;
        out << "Weapon {damage: " << weapon.damage
            << ", critical: " << weapon.critical
            << ", durability: " << weapon.durability
            << "}";
    }
    else if (type == Item::ItemType::ARMOR) {
        Armor& armor = item.value.armor;
        out << "Armor {guard: " << armor.guard
            << ", durability: " << armor.durability
            << "}";
    }
    out << std::flush;
    return out;
}

std::ostream& operator<<(std::ostream& out, LootBox& lootbox) {
    for (auto& elem : lootbox) {
        out << elem << "\n" << std::flush;
    }
    return out;
}

std::string to_string(Rune::Element& element) {
    std::string result;

    switch (element) {
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

Item GetCoin(uint count) {
    return {
        Item {
            Item::ItemType::COIN,
            Item::Value {.coin = Coin{count}}
        }
    };
}
Item GetRune(Rune::Element element, uint level) {
    return {
        Item {
            Item::ItemType::RUNE,
            Item::Value {
                .rune = Rune {
                    element,
                    level
                }
            }
        }
    };
}
Item GetFireRune(uint level) {
    return GetRune(Rune::Element::FIRE, level);
}
Item GetWaterRune(uint level) {
    return GetRune(Rune::Element::WATER, level);
}
Item GetEarthRune(uint level) {
    return GetRune(Rune::Element::EARTH, level);
}
Item GetAirRune(uint level) {
    return GetRune(Rune::Element::AIR, level);
}
Item GetWeapon(uint damage, uint critical, uint durability) {
    return {
        Item {
            Item::ItemType::WEAPON,
            Item::Value{.weapon = Weapon{damage, critical, durability}}
        }
    };
}
Item GetArmor(uint guard, uint durability) {
    return {
        Item {
            Item::ItemType::ARMOR,
            Item::Value{.armor = Armor{guard, durability}}
        }
    };
}
