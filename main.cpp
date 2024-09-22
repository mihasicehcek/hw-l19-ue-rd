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
    [[nodiscard]] float GetDamage() const override {
        return 10.f;
    }

    [[nodiscard]] std::string GetName() const override {
        return "Sword";
    }

    ~Sword() override {
        std::cout << "Sword destroyed" << std::endl;
    }
};

class Staff : public Weapon {
public:
    [[nodiscard]] float GetDamage() const override {
        return 3.f;
    }

    [[nodiscard]] std::string GetName() const override {
        return "Staff";
    }

    ~Staff() override {
        std::cout << "Staff destroyed" << std::endl;
    }
};

class Dagger : public Weapon {
public:
    [[nodiscard]] float GetDamage() const override {
        return 4.f;
    }

    [[nodiscard]] std::string GetName() const override {
        return "Dagger";
    }

    ~Dagger() override {
        std::cout << "Dagger destroyed" << std::endl;
    }
};

class Character {
    std::map<std::string, std::unique_ptr<Weapon>> weapons;
    Weapon* selectedWeapon = nullptr;

public:
    void AddWeapon(std::unique_ptr<Weapon> weapon) {
        const std::string& weaponName = weapon->GetName();
        auto result = weapons.emplace(weaponName, std::move(weapon));
        if (result.second) {
            selectedWeapon = result.first->second.get();
        }
    }

    [[nodiscard]] Weapon* GetSelectedWeapon() const {
        return selectedWeapon;
    }

    void equip(const std::string& weaponName) {
        auto it = weapons.find(weaponName);
        if (it != weapons.end()) {
            selectedWeapon = it->second.get();
        } else {
            selectedWeapon = nullptr;
        }
    }

    void unequip() {
        selectedWeapon = nullptr;
    }
};

void printSelectedWeapon(const std::unique_ptr<Character>& character) {
    if (character->GetSelectedWeapon() == nullptr) {
        std::cout << "No weapon selected" << std::endl;
        return;
    }
    std::cout << "Selected weapon: " << character->GetSelectedWeapon()->GetName() << std::endl;
}

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
