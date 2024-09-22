#include <iostream>
#include <map>
#include <memory>
#include <vector>

class Weapon {
public:
    virtual ~Weapon() = default;
    [[nodiscard]] virtual float GetDamage() const = 0;
    [[nodiscard]] virtual std::string GetName() const = 0;
};

class Sword : public Weapon {
public:
    [[nodiscard]] float GetDamage() const override;

    [[nodiscard]] std::string GetName() const override;

    ~Sword() override;
};

class Staff : public Weapon {
public:
    [[nodiscard]] float GetDamage() const override;

    [[nodiscard]] std::string GetName() const override;

    ~Staff() override;
};

class Dagger : public Weapon {
public:
    [[nodiscard]] float GetDamage() const override;

    [[nodiscard]] std::string GetName() const override;

    ~Dagger() override;
};

class Character {
    std::map<std::string, std::unique_ptr<Weapon>> weapons;
    Weapon* selectedWeapon = nullptr;

public:
    void AddWeapon(std::unique_ptr<Weapon> weapon);

    [[nodiscard]] Weapon* GetSelectedWeapon() const;

    void equip(const std::string& weaponName);

    void unequip();
};

void printSelectedWeapon(const std::unique_ptr<Character>& character);

int main() {
    auto character = std::make_unique<Character>();
    printSelectedWeapon(character);

    auto sword = std::make_unique<Sword>();
    character->AddWeapon(std::move(sword));

    printSelectedWeapon(character);

    auto dagger = std::make_unique<Dagger>();
    character->AddWeapon(std::move(dagger));

    printSelectedWeapon(character);

    auto staff = std::make_unique<Staff>();
    character->AddWeapon(std::move(staff));

    printSelectedWeapon(character);

    std::string weaponName = "Sword";
    character->equip(weaponName);
    printSelectedWeapon(character);

    auto staff2 = std::make_unique<Staff>();
    character->AddWeapon(std::move(staff2));
    printSelectedWeapon(character);

    character->unequip();
    printSelectedWeapon(character);
    return 0;
}

Sword::~Sword() {
    std::cout << "Sword destroyed" << std::endl;
}

float Sword::GetDamage() const {
    return 10.f;
}

std::string Sword::GetName() const {
    return "Sword";
}

Staff::~Staff() {
    std::cout << "Staff destroyed" << std::endl;
}

float Staff::GetDamage() const {
    return 3.f;
}

std::string Staff::GetName() const {
    return "Staff";
}

Dagger::~Dagger() {
    std::cout << "Dagger destroyed" << std::endl;
}

float Dagger::GetDamage() const {
    return 4.f;
}

std::string Dagger::GetName() const {
    return "Dagger";
}

void Character::AddWeapon(std::unique_ptr<Weapon> weapon) {
    const std::string& weaponName = weapon->GetName();
    auto result = weapons.emplace(weaponName, std::move(weapon));
    if (result.second) {
        selectedWeapon = result.first->second.get();
    }
}

Weapon* Character::GetSelectedWeapon() const {
    return selectedWeapon;
}

void Character::equip(const std::string& weaponName) {
    auto it = weapons.find(weaponName);
    if (it != weapons.end()) {
        selectedWeapon = it->second.get();
    } else {
        selectedWeapon = nullptr;
    }
}

void Character::unequip() {
    selectedWeapon = nullptr;
}

void printSelectedWeapon(const std::unique_ptr<Character>& character) {
    if (character->GetSelectedWeapon() == nullptr) {
        std::cout << "No weapon selected" << std::endl;
        return;
    }
    std::cout << "Selected weapon: " << character->GetSelectedWeapon()->GetName() << std::endl;
}